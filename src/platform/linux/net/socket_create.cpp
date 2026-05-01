#include "dius/c_definitions.h"
#include "dius/net/socket.h"
#include "dius/sync_file.h"
#include "dius/system/system_call.h"

namespace dius::net {
static auto get_socket_flags(OpenFlags open_flags) -> i32 {
    auto result = SOCK_CLOEXEC;
    if (!!(open_flags & OpenFlags::KeepAfterExec)) {
        result &= ~SOCK_CLOEXEC;
    }
    if (!!(open_flags & OpenFlags::NonBlocking)) {
        result |= SOCK_NONBLOCK;
    }
    return result;
}

auto SyncSocket::accept(OpenFlags open_flags) -> di::Result<SyncSocket> {
    auto const flags = get_socket_flags(open_flags);
    auto fd = TRY(system::system_call<i32>(system::Number::accept4, file_descriptor(), nullptr, 0, flags));
    return SyncSocket(SyncSocket::Owned::Yes, fd);
}

auto make_unix_socket_sync(OpenFlags open_flags) -> di::Result<SyncSocket> {
    auto const flags = get_socket_flags(open_flags);
    auto fd = TRY(system::system_call<i32>(system::Number::socket, AF_UNIX, SOCK_STREAM | flags, 0));
    return SyncSocket(SyncSocket::Owned::Yes, fd);
}
}
