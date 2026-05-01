#include <sys/socket.h>

#include "dius/net/socket.h"
#include "dius/platform_error.h"
#include "dius/posix/syscalls.h"
#include "dius/sync_file.h"

namespace dius::net {
auto SyncSocket::accept(OpenFlags open_flags) -> di::Result<SyncSocket> {
    auto fd = ::accept(file_descriptor(), nullptr, 0);
    if (fd < 0) {
        return di::Unexpected(PosixError(fd));
    }
    auto result = SyncSocket(SyncSocket::Owned::Yes, fd);
    TRY(result.set_open_flags(open_flags));
    return result;
}

auto make_unix_socket_sync(OpenFlags open_flags) -> di::Result<SyncSocket> {
    auto fd = ::socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        return di::Unexpected(PosixError(fd));
    }
    auto result = SyncSocket(SyncSocket::Owned::Yes, fd);
    TRY(result.set_open_flags(open_flags));
    return result;
}
}
