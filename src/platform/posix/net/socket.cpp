#include "dius/net/socket.h"

#include "dius/platform_error.h"
#include "dius/posix/syscalls.h"
#include "dius/sync_file.h"

namespace dius::net {
auto SyncSocket::listen(i32 backlog) -> di::Result<> {
    return syscalls::sys_listen(file_descriptor(), backlog);
}

auto SyncSocket::bind(UnixAddress const& address) -> di::Result<> {
    return syscalls::sys_bind(file_descriptor(), address);
}

auto SyncSocket::connect(UnixAddress const& address) -> di::Result<> {
    return syscalls::sys_connect(file_descriptor(), address);
}

auto SyncSocket::shutdown(Shutdown mode) -> di::Result<> {
    return syscalls::sys_shutdown(file_descriptor(), mode);
}

auto SyncSocket::get_error() -> di::Result<> {
    i32 value = 0;
    TRY(syscalls::sys_getsockopt(file_descriptor(), SOL_SOCKET, SO_ERROR, &value, sizeof(value)));
    if (value == 0) {
        return {};
    }
    return di::Unexpected(PosixError(value));
}
}
