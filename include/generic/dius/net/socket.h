#pragma once

#include "dius/c_definitions.h"
#include "dius/net/address.h"
#include "dius/sync_file.h"

namespace dius::net {
enum class Shutdown {
    Read = 0,
    Write = 1,
    ReadWrite = 2,
};

class SyncSocket : public SyncFile {
public:
    SyncSocket() = default;

    constexpr explicit SyncSocket(Owned owned, int fd) : SyncFile(owned, fd) {}

    auto listen(i32 backlog = 5) -> di::Result<>;
    auto bind(net::UnixAddress const& address) -> di::Result<>;
    auto accept(OpenFlags open_flags = OpenFlags::None) -> di::Result<SyncSocket>;
    auto shutdown(Shutdown mode) -> di::Result<>;
    auto connect(net::UnixAddress const& address) -> di::Result<>;
    auto get_error() -> di::Result<>;
};

auto make_unix_socket_sync(OpenFlags flags = OpenFlags::None) -> di::Result<SyncSocket>;
}
