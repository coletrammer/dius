#pragma once

#include "dius/c_definitions.h"
#include "dius/sync_file.h"

namespace dius::linux {
class Inotify : public SyncFile {
public:
    enum class EventType : u32 {
        None = 0,
        WriteClosed = IN_CLOSE_WRITE,
    };

    struct Event {
        i32 token { 0 };
        EventType event { EventType::None };
    };

    constexpr explicit Inotify(Owned owned, i32 fd) : SyncFile(owned, fd) {}

    auto read() const -> di::Result<Event>;
    auto add_watch(di::Path const& path, EventType events) -> di::Result<i32>;
    auto remove_watch(i32 token) -> di::Result<>;
};

DI_DEFINE_ENUM_BITWISE_OPERATIONS(Inotify::EventType)

auto create_inotify(OpenFlags open_flags = OpenFlags::None) -> di::Result<Inotify>;
}
