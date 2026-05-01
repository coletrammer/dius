#include "dius/linux/epoll_context.h"

#include "di/assert/prelude.h"
#include "di/util/defer_construct.h"
#include "dius/linux/epoll.h"
#include "dius/linux/eventfd.h"

namespace dius::linux::epoll {
auto Context::create() -> di::Result<Context> {
    auto epoll_handle = TRY(Handle::create());
    auto eventfd = TRY(create_eventfd(0));

    // Register the eventfd permanently for read events, to allow wake ups.
    epoll_handle.request_notification(eventfd.file_descriptor(), EventType::Read);

    return di::Result<Context>(di::in_place, di::DeferConstruct([&] {
                                   return Context(di::move(epoll_handle), di::move(eventfd));
                               }));
}

Context::Context(Handle epoll_handle, SyncFile eventfd)
    : m_epoll_handle(di::move(epoll_handle)), m_eventfd(di::move(eventfd)) {}

void Context::run() {
    constexpr auto max_event_count = 256u;

    while (m_staring_operations.load(di::MemoryOrder::Acquire) != -1) {
        m_need_wake.store(true, di::MemoryOrder::Release);

        // After loading all operations, we need to ensure to remove the operation before
        // executing, because the instrusive list pointers are re-used for waiting as well.
        auto new_ops = m_queued_operations.batch_pop();
        while (auto op = new_ops.pop_front()) {
            op.value().execute();
        }

        auto events = di::Array<epoll_event, max_event_count> {};
        auto result = m_epoll_handle.wait(events.span(), {});
        ASSERT(result);

        m_need_wake.store(false, di::MemoryOrder::Release);
        for (auto const& event : result.value()) {
            dispatch_event(i32(event.data), EventType(event.events));
        }
    }

    // Execute all currently pending operations. No new operations can be queued.
    auto new_ops = m_queued_operations.batch_pop();
    while (auto op = new_ops.pop_front()) {
        op.value().execute();
    }

    // Cancel all waiters.
    for (auto& [_, waiters] : m_waiting_operations) {
        while (auto op = waiters.pop_front()) {
            op.value().terminate();
        }
    }
}

void Context::finish() {
    // Prevent new operations from being added by writing -1 to the m_staring_operations.
    auto expected = 0;
    while (!m_staring_operations.compare_exchange_weak(expected, -1, di::MemoryOrder::AcquireRelease,
                                                       di::MemoryOrder::Relaxed)) {
        expected = 0;
    }

    // Wakeup the context so it will exit.
    wake();
}

auto Context::try_start(OperationBase& op) -> bool {
    // First we need to synchronize against calls to finish() by incrementing the number of starting operations.
    // This is to ensure that all started operations complete.
    auto expected = m_staring_operations.load(di::MemoryOrder::Relaxed);
    while (expected != -1 && !m_staring_operations.compare_exchange_weak(
                                 expected, expected + 1, di::MemoryOrder::AcquireRelease, di::MemoryOrder::Relaxed)) {}
    if (expected == -1) {
        return false;
    }

    // Enqueue the operation and then wake up the context.
    auto _ = di::ScopeExit([&] {
        m_staring_operations.fetch_sub(1, di::MemoryOrder::AcquireRelease);
    });
    m_queued_operations.push(op);
    wake();
    return true;
}

void Context::add_waiter(i32 fd, WaitableOperationBase& op) {
    auto events = op.events;
    auto& waiting_ops = m_waiting_operations[fd];
    for (auto& op : waiting_ops) {
        events |= op.events;
    }
    m_epoll_handle.request_notification(fd, events);
    waiting_ops.push_back(op);
}

void Context::cancel(i32 fd, WaitableOperationBase& op) {
    auto outer_it = m_waiting_operations.find(fd);
    ASSERT_NOT_EQ(outer_it, m_waiting_operations.end());

    // Erase the waitable operation.
    auto& waiting_ops = outer_it->get<1>();
    auto waiting_events = EventType::None;
    for (auto it = waiting_ops.before_begin(); it != waiting_ops.before_end();) {
        auto& current = *di::next(it);
        if (&op == &current) {
            waiting_ops.erase_after(it);
        } else {
            ++it;
        }
    }

    // Update the epoll handle with the new desired notifications.
    if (waiting_events == EventType::None) {
        m_epoll_handle.unrequest_notification(fd);
    } else {
        m_epoll_handle.request_notification(fd, waiting_events);
    }

    // Clean up the waiting operations entry if possible.
    if (waiting_ops.empty()) {
        m_waiting_operations.erase(fd);
    }
}

void Context::wake() {
    // As an optimization, we skip calling the event fd unless we need to. We take care to update this field to true
    // in run() before reading operations, as false wakeups() are infinitely better than missing wake ups. We could
    // prevent false wakeups by fully synchronizing with run(), but that's inefficient.
    auto expected = true;
    if (!m_need_wake.compare_exchange_weak(expected, false, di::MemoryOrder::AcquireRelease,
                                           di::MemoryOrder::Relaxed)) {
        return;
    }

    auto wakeup_value = di::bit_cast<di::Array<byte, sizeof(i64)>>(1_i64);
    ASSERT(m_eventfd.write_exactly(wakeup_value.span()));
}

void Context::dispatch_event(i32 fd, EventType events) {
    // Special case for the eventfd, where we simply read the eventfd to stop the notification
    // until the next wakeup.
    if (fd == m_eventfd.file_descriptor()) {
        auto bytes = di::Array<byte, sizeof(i64)> {};
        (void) m_eventfd.read_exactly(bytes.span());
        return;
    }

    auto outer_it = m_waiting_operations.find(fd);
    ASSERT_NOT_EQ(outer_it, m_waiting_operations.end());

    // Try to match at most one operation before event type this iteration. We also
    // keep track of the new desired list of events to wait for so we can update the
    // epoll context.
    auto& waiting_ops = outer_it->get<1>();
    auto waiting_events = EventType::None;
    for (auto it = waiting_ops.before_begin(); it != waiting_ops.before_end();) {
        auto& current = *di::next(it);
        if ((current.events & events) == EventType::None) {
            ++it;
            waiting_events |= current.events;
            continue;
        }
        events &= ~current.events;
        waiting_ops.erase_after(it);
        current.notify();
    }

    // Update the epoll handle with the new desired notifications.
    if (waiting_events == EventType::None) {
        m_epoll_handle.unrequest_notification(fd);
    } else {
        m_epoll_handle.request_notification(fd, waiting_events);
    }

    // Clean up the waiting operations entry if possible.
    if (waiting_ops.empty()) {
        m_waiting_operations.erase(outer_it);
    }
}
}
