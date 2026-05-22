#include "dius/linux/inotify.h"

#include "dius/c_definitions.h"
#include "dius/platform_process.h"
#include "dius/sync_file.h"
#include "dius/system/system_call.h"

namespace dius::linux {
auto Inotify::read() const -> di::Result<Event> {
    auto bytes = di::Array<byte, sizeof(inotify_event) + NAME_MAX + 1> {};
    TRY(read_some(bytes));
    auto* ev = (inotify_event*) bytes.data();
    return Event {
        .token = ev->wd,
        .event = EventType(ev->mask),
    };
}

auto Inotify::add_watch(di::Path const& path, EventType events) -> di::Result<i32> {
    return system::system_call<i32>(system::Number::inotify_add_watch, file_descriptor(), path.c_str(),
                                    di::to_underlying(events) | IN_ONESHOT);
}

auto Inotify::remove_watch(i32 token) -> di::Result<> {
    return system::system_call<u32>(system::Number::inotify_rm_watch, file_descriptor(), token) % di::into_void;
}

auto create_inotify(OpenFlags open_flags) -> di::Result<Inotify> {
    auto flags = i32(IN_CLOEXEC);
    if (!!(open_flags & OpenFlags::KeepAfterExec)) {
        flags &= ~IN_CLOEXEC;
    }
    if (!!(open_flags & OpenFlags::NonBlocking)) {
        flags |= IN_NONBLOCK;
    }
    auto fd = TRY(system::system_call<i32>(system::Number::inotify_init1, flags));
    return Inotify(Inotify::Owned::Yes, fd);
}
}
