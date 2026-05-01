#include "dius/linux/epoll.h"

#include "dius/print.h"
#include "dius/steady_clock.h"
#include "dius/sync_file.h"
#include "dius/system/system_call.h"

namespace dius::linux::epoll {
static auto sys_epoll_create1(i32 flags) -> di::Result<SyncFile> {
    auto fd = TRY(system::system_call<i32>(system::Number::epoll_create1, flags));
    return SyncFile(SyncFile::Owned::Yes, fd);
}

static auto sys_epoll_ctl(i32 epoll_fd, i32 op, i32 fd, epoll_event* event = nullptr) -> di::Result<> {
    return system::system_call<i32>(system::Number::epoll_ctl, epoll_fd, op, fd, event) % di::into_void;
}

static auto sys_epoll_wait(i32 epoll_fd, di::Span<epoll_event> events, i32 timeout = -1)
    -> di::Result<di::Span<epoll_event>> {
    auto count =
        TRY(system::system_call<i32>(system::Number::epoll_wait, epoll_fd, events.data(), i32(events.size()), timeout));
    return *events.first(count);
}

static auto sys_epoll_pwait2(i32 epoll_fd, di::Span<epoll_event> events, timespec const* timeout = nullptr,
                             void* sigmask = nullptr) -> di::Result<di::Span<epoll_event>> {
#ifdef DIUS_LINUX_PWAIT2
    auto count = TRY(system::system_call<i32>(system::Number::epoll_pwait2, epoll_fd, events.data(), i32(events.size()),
                                              timeout, sigmask));
    return *events.first(count);
#else
    return di::Unexpected(dius::PosixError::FunctionNotSupported);
#endif
}

auto Handle::create() -> di::Result<Handle> {
    auto epoll_fd = TRY(sys_epoll_create1(EPOLL_CLOEXEC));
    auto use_epoll_pwait2 = sys_epoll_pwait2(-1, {}) != di::Unexpected(PosixError::FunctionNotSupported);
    return Handle(di::move(epoll_fd), use_epoll_pwait2);
}

Handle::Handle(SyncFile epoll_fd, bool use_epoll_pwait2)
    : m_epoll_fd(di::move(epoll_fd)), m_use_epoll_pwait2(use_epoll_pwait2) {}

void Handle::request_notification(i32 fd, EventType type) {
    m_desired_interest_list[fd] = type;
    m_dirty_fds.insert(fd);
}

void Handle::unrequest_notification(i32 fd) {
    // This is always handled synchronously as the fd may be closed before we call wait().
    if (!m_current_interest_list.contains(fd)) {
        return;
    }

    m_desired_interest_list.erase(fd);
    m_current_interest_list.erase(fd);
    m_dirty_fds.erase(fd);

    epoll_event event {};
    ASSERT(sys_epoll_ctl(m_epoll_fd.file_descriptor(), EPOLL_CTL_DEL, fd, &event));
}

auto Handle::wait(di::Span<epoll_event> events, di::Optional<SteadyClock::Duration> timeout)
    -> di::Result<di::Span<epoll_event>> {
    TRY(update_interest_list());
    if (!m_use_epoll_pwait2) {
        auto const timeout_ms =
            timeout
                .and_then([](SteadyClock::Duration value) -> di::Optional<i32> {
                    auto as_millis = di::duration_cast<di::Milliseconds>(value).count();
                    return di::representable_as<i32>(as_millis) ? di::Optional(as_millis) : di::nullopt;
                })
                .value_or(-1);
        return sys_epoll_wait(m_epoll_fd.file_descriptor(), events, timeout_ms);
    }

    auto timespec_storage = timespec {};
    auto* timespec_p = (timespec*) nullptr;
    for (auto t : timeout) {
        timespec_storage.tv_sec = di::duration_cast<di::Seconds>(t).count();
        timespec_storage.tv_nsec = t.count() % long(di::Nanoseconds::Period::den);
        timespec_p = &timespec_storage;
    }
    return sys_epoll_pwait2(m_epoll_fd.file_descriptor(), events, timespec_p);
}

auto Handle::update_interest_list() -> di::Result<> {
    // Conceptually we are diffing current vs. desired but as an optimization we only
    // look at file descriptors which we know possibly changed.
    for (auto fd : m_dirty_fds) {
        auto desired_it = m_desired_interest_list.find(fd);
        auto current_it = m_current_interest_list.find(fd);

        if (desired_it == m_desired_interest_list.end() && current_it != m_current_interest_list.end()) {
            // Remove
            TRY(sys_epoll_ctl(m_epoll_fd.file_descriptor(), EPOLL_CTL_DEL, fd));
            m_current_interest_list.erase(current_it);
        } else if (desired_it != m_desired_interest_list.end()) {
            // Add or update
            auto op = EPOLL_CTL_ADD;
            auto desired_events = desired_it->get<1>();
            if (current_it != m_current_interest_list.end()) {
                if (current_it->get<1>() == desired_events) {
                    continue;
                }
                op = EPOLL_CTL_MOD;
            }
            auto event = epoll_event {
                .events = di::to_underlying(desired_events),
                .data = u64(fd),
            };
            TRY(sys_epoll_ctl(m_epoll_fd.file_descriptor(), op, fd, &event));
            m_current_interest_list[fd] = desired_events;
        }
    }
    m_dirty_fds.clear();

    return {};
}
}
