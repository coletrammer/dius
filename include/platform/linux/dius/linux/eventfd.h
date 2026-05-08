#pragma once

#include "dius/sync_file.h"

namespace dius::linux {
class Eventfd : public SyncFile {
public:
    constexpr explicit Eventfd(Owned owned, int fd) : SyncFile(owned, fd) {}

    auto read() const -> di::Result<u64>;
    auto write(u64 value) const -> di::Result<>;
};

auto create_eventfd(u64 initial_value) -> di::Result<Eventfd>;
}
