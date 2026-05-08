#include "dius/linux/epoll_context.h"

#include "di/assert/prelude.h"
#include "di/util/defer_construct.h"
#include "dius/linux/epoll.h"
#include "dius/linux/eventfd.h"
#include "dius/linux/signalfd.h"
#include "dius/system/process.h"

namespace dius::linux::epoll {
auto Context::create() -> di::Result<Context> {
    auto epoll_handle = TRY(Handle::create());
    auto eventfd = TRY(create_eventfd(0));
    auto signalfd = TRY(create_signalfd());

    // Register the eventfd permanently for read events, to allow wake ups.
    epoll_handle.request_notification(eventfd.file_descriptor(), EventType::Read);

    // Register the signalfd permanently for read events, to allow for signal notifications.
    epoll_handle.request_notification(signalfd.file_descriptor(), EventType::Read);

    return di::Result<Context>(di::in_place, di::DeferConstruct([&] {
                                   return Context(di::move(epoll_handle), di::move(eventfd), di::move(signalfd));
                               }));
}

Context::Context(Handle epoll_handle, Eventfd eventfd, Signalfd signalfd)
    : m_epoll_handle(di::move(epoll_handle)), m_eventfd(di::move(eventfd)), m_signalfd(di::move(signalfd)) {}

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

        if (di::exchange(m_signal_set_changed, false)) {
            auto signals = di::keys(m_signal_operations) | di::to<di::Vector>();
            ASSERT(system::set_signal_mask(signals.span()));
            ASSERT(m_signalfd.listen(signals.span()));
        }

        auto events = di::Array<epoll_event, max_event_count> {};
        auto result = m_epoll_handle.wait(events.span(), {});
        ASSERT(result);

        m_need_wake.store(false, di::MemoryOrder::Release);
        for (auto const& event : result.value()) {
            dispatch_event(i32(event.data.u64), EventType(event.events));
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
    for (auto& [_, signal_waiters] : m_signal_operations) {
        while (auto op = signal_waiters.pop_front()) {
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

void Context::add_waiter(WaitableOperationBase& op) {
    auto const fd = op.fd;
    auto events = op.events;
    auto& waiting_ops = m_waiting_operations[fd];
    for (auto& op : waiting_ops) {
        events |= op.events;
    }
    m_epoll_handle.request_notification(fd, events);
    waiting_ops.push_back(op);
}

void Context::add_waiter(SignalOperationBase& op) {
    auto& waiting_ops = m_signal_operations[op.signal];
    waiting_ops.push_back(op);
    m_signal_set_changed = true;
}

void Context::cancel(WaitableOperationBase& op) {
    auto const fd = op.fd;
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
        m_waiting_operations.erase(outer_it);
    }
}

void Context::cancel(SignalOperationBase& op) {
    auto outer_it = m_signal_operations.find(op.signal);
    ASSERT_NOT_EQ(outer_it, m_signal_operations.end());

    // Erase the signal operation.
    auto& waiting_ops = outer_it->get<1>();
    for (auto it = waiting_ops.before_begin(); it != waiting_ops.before_end();) {
        auto& current = *di::next(it);
        if (&op == &current) {
            waiting_ops.erase_after(it);
        } else {
            ++it;
        }
    }

    // Clean up the waiting operations entry if possible.
    if (waiting_ops.empty()) {
        m_signal_operations.erase(outer_it);
        m_signal_set_changed = true;
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

    ASSERT(m_eventfd.write(1));
}

void Context::dispatch_signal() {
    auto signal_result = m_signalfd.read();
    ASSERT(signal_result);

    auto it = m_signal_operations.find(signal_result.value());
    if (it == m_signal_operations.end()) {
        return;
    }

    // The signal notification is broadcast to all listeners.
    auto& ops = it->get<1>();
    while (auto op = ops.pop_front()) {
        op.value().notify();
    }
    m_signal_operations.erase(it);
    m_signal_set_changed = true;
}

void Context::dispatch_event(i32 fd, EventType events) {
    // Special case for the eventfd, where we simply read the eventfd to stop the notification
    // until the next wakeup.
    if (fd == m_eventfd.file_descriptor()) {
        (void) m_eventfd.read();
        return;
    }

    if (fd == m_signalfd.file_descriptor()) {
        dispatch_signal();
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
