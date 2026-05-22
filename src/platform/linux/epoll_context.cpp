#include "dius/linux/epoll_context.h"

#include "di/assert/prelude.h"
#include "di/container/algorithm/lower_bound.h"
#include "di/util/defer_construct.h"
#include "dius/linux/epoll.h"
#include "dius/linux/eventfd.h"
#include "dius/linux/inotify.h"
#include "dius/linux/signalfd.h"
#include "dius/sync_file.h"
#include "dius/system/process.h"

namespace dius::linux::epoll {
auto Context::create() -> di::Result<Context> {
    auto epoll_handle = TRY(Handle::create());
    auto eventfd = TRY(create_eventfd(0));
    auto signalfd = TRY(create_signalfd());
    auto inotify = TRY(create_inotify(OpenFlags::NonBlocking));

    // Register the eventfd permanently for read events, to allow wake ups.
    epoll_handle.request_notification(eventfd.file_descriptor(), EventType::Read);

    // Register the signalfd permanently for read events, to allow for signal notifications.
    epoll_handle.request_notification(signalfd.file_descriptor(), EventType::Read);

    // Register the inotify instance permanently for read events, to allow for file change notifications.
    epoll_handle.request_notification(inotify.file_descriptor(), EventType::Read);

    return di::Result<Context>(di::in_place, di::DeferConstruct([&] {
                                   return Context(di::move(epoll_handle), di::move(eventfd), di::move(signalfd),
                                                  di::move(inotify));
                               }));
}

Context::Context(Handle epoll_handle, Eventfd eventfd, Signalfd signalfd, Inotify inotify)
    : m_epoll_handle(di::move(epoll_handle))
    , m_eventfd(di::move(eventfd))
    , m_signalfd(di::move(signalfd))
    , m_inotify(di::move(inotify)) {}

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
        auto const now = SteadyClock::now();
        auto timeout = m_timeout_operations.front().transform([&](TimeoutOperationBase& op) -> SteadyClock::Duration {
            auto duration = op.deadline - now;
            return di::max(duration, SteadyClock::Duration::zero());
        });
        auto result = m_epoll_handle.wait(events.span(), timeout);
        ASSERT(result);

        m_need_wake.store(false, di::MemoryOrder::Release);
        for (auto const& event : result.value()) {
            dispatch_event(i32(event.data.u64), EventType(event.events));
        }
        process_timeouts();
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
    for (auto& [_, inotify_waiters] : m_inotify_waiters) {
        while (auto op = inotify_waiters.pop_front()) {
            op.value().terminate();
        }
    }
    while (auto op = m_timeout_operations.pop_front()) {
        op.value().terminate();
    }
}

void Context::finish() {
    // Prevent new operations from being added by writing -1 to the m_staring_operations.
    auto expected = 0;
    while (!m_staring_operations.compare_exchange_weak(expected, -1, di::MemoryOrder::AcquireRelease,
                                                       di::MemoryOrder::Relaxed)) {
        ASSERT_NOT_EQ(expected, -1);
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

void Context::add_waiter(TimeoutOperationBase& op) {
    // Its more efficient to use an intrusive heap here, but its some work
    // to implement and is only necessary for large number of timeouts.
    auto it = m_timeout_operations.before_begin();
    while (it != m_timeout_operations.before_end()) {
        auto next = di::next(it);
        if (op.deadline < next->deadline) {
            break;
        }
    }
    m_timeout_operations.insert_after(it, op);
}

void Context::add_waiter(InotifyOperationBase& op) {
    auto existing = m_inotify_tokens.find(op.path);
    if (existing != m_inotify_tokens.end()) {
        auto const token = existing->get<1>();
        auto current_events = m_inotify_state[token];
        if ((op.events & current_events) == op.events) {
            return;
        }

        update_inotify(token, op.events | current_events, m_inotify_waiters.find(token));
        return;
    }

    auto token = m_inotify.add_watch(op.path, op.events);
    if (!token) {
        op.error = di::move(token).error();
        op.notify();
        return;
    }

    m_inotify_state[token.value()] = op.events;
    m_inotify_waiters[token.value()].push_back(op);
    m_inotify_tokens[op.path] = token.value();
    m_inotify_paths[token.value()] = op.path.clone();
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
            waiting_events |= current.events;
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
    di::erase_if(waiting_ops, [&](SignalOperationBase const& other) {
        return &op == &other;
    });

    // Clean up the waiting operations entry if possible.
    if (waiting_ops.empty()) {
        m_signal_operations.erase(outer_it);
        m_signal_set_changed = true;
    }
}

void Context::cancel(TimeoutOperationBase& op) {
    di::erase_if(m_timeout_operations, [&](TimeoutOperationBase const& other) {
        return &op == &other;
    });
}

void Context::cancel(InotifyOperationBase& op) {
    auto const token = op.token;
    auto outer_it = m_inotify_waiters.find(token);
    ASSERT_NOT_EQ(outer_it, m_inotify_waiters.end());

    // Erase the waitable operation.
    auto& waiting_ops = outer_it->get<1>();
    auto waiting_events = Inotify::EventType::None;
    for (auto it = waiting_ops.before_begin(); it != waiting_ops.before_end();) {
        auto& current = *di::next(it);
        if (&op == &current) {
            waiting_ops.erase_after(it);
        } else {
            waiting_events |= current.events;
            ++it;
        }
    }

    // If there are other waiters do nothing.
    if (waiting_events == m_inotify_state[token]) {
        return;
    }

    // Since we making a new token delete the old one.
    ASSERT(m_inotify.remove_watch(token));

    // Update the inotify waiter.
    update_inotify(token, waiting_events, outer_it);
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

void Context::update_inotify(i32 token, Inotify::EventType new_events,
                             di::TreeMap<i32, di::IntrusiveForwardList<InotifyOperationBase>>::Iterator outer_it) {
    auto& waiting_ops = outer_it->get<1>();
    auto path = di::move(m_inotify_paths[token]);
    m_inotify_paths.erase(token);
    m_inotify_state.erase(token);
    if (new_events != Inotify::EventType::None) {
        auto new_token = m_inotify.add_watch(path, new_events);
        if (!new_token) {
            m_inotify_tokens.erase(path);
            while (auto op = waiting_ops.pop_front()) {
                op.value().error = new_token.error().generic_code();
                op.value().notify();
            }
        } else {
            m_inotify_tokens[path] = new_token.value();
            m_inotify_paths[new_token.value()] = di::move(path);
            m_inotify_state[new_token.value()] = new_events;
            m_inotify_waiters[new_token.value()] = di::move(waiting_ops);
        }
    } else {
        m_inotify_tokens.erase(path);
    }
    m_inotify_waiters.erase(outer_it);
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

void Context::dispatch_inotify(Inotify::Event const& event) {
    auto outer_it = m_inotify_waiters.find(event.token);
    if (outer_it == m_inotify_waiters.end()) {
        return;
    }

    // Matching events are broadcast to all current waiters.
    auto& waiting_ops = outer_it->get<1>();
    auto waiting_events = Inotify::EventType::None;
    for (auto it = waiting_ops.before_begin(); it != waiting_ops.before_end();) {
        auto& current = *di::next(it);
        if ((current.events & event.event) == Inotify::EventType::None) {
            ++it;
            waiting_events |= current.events;
            continue;
        }
        waiting_ops.erase_after(it);
        current.notify();
    }

    // We don't need to call remove_watch() since events are single shot.
    update_inotify(event.token, waiting_events, outer_it);
}

void Context::dispatch_event(i32 fd, EventType events) {
    // Special case for the managed file descriptors, where we simply dispatch using another
    // per-fd mechanism.
    if (fd == m_eventfd.file_descriptor()) {
        // Do nothing: this was just to wakeup the epoll wait.
        (void) m_eventfd.read();
        return;
    }

    if (fd == m_signalfd.file_descriptor()) {
        dispatch_signal();
        return;
    }

    if (fd == m_inotify.file_descriptor()) {
        auto event = m_inotify.read();
        ASSERT(event);
        dispatch_inotify(event.value());
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

void Context::process_timeouts() {
    auto const now = SteadyClock::now();
    while (auto op = m_timeout_operations.front()) {
        if (op.value().deadline <= now) {
            m_timeout_operations.pop_front();
            op.value().notify();
            continue;
        }
        break;
    }
}
}
