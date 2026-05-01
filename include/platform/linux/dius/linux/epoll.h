#pragma once

#include <linux/eventpoll.h>

#include "di/container/tree/tree_map.h"
#include "di/container/tree/tree_set.h"
#include "dius/steady_clock.h"
#include "dius/sync_file.h"

namespace dius::linux::epoll {
enum class EventType : __poll_t {
    None = 0,
    Read = EPOLLIN,
    Write = EPOLLOUT,
};

DI_DEFINE_ENUM_BITWISE_OPERATIONS(EventType)

class Handle {
public:
    static auto create() -> di::Result<Handle>;

    explicit Handle(SyncFile epoll_fd, bool m_use_epoll_pwait2);

    void request_notification(i32 fd, EventType type);
    void unrequest_notification(i32 fd);

    auto wait(di::Span<epoll_event> events, di::Optional<SteadyClock::Duration> timeout)
        -> di::Result<di::Span<epoll_event>>;

private:
    auto update_interest_list() -> di::Result<>;

    SyncFile m_epoll_fd;
    di::TreeSet<i32> m_dirty_fds;
    di::TreeMap<i32, EventType> m_desired_interest_list {};
    di::TreeMap<i32, EventType> m_current_interest_list {};
    bool m_use_epoll_pwait2 { false };
};
}
