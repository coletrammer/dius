#pragma once

#include "dius/platform_process.h"
#include "dius/sync_file.h"

namespace dius::linux {
class Signalfd : public SyncFile {
public:
    constexpr explicit Signalfd(Owned owned, int fd) : SyncFile(owned, fd) {}

    auto read() const -> di::Result<Signal>;

    auto listen(di::Span<Signal> signals) const -> di::Result<>;
};

auto create_signalfd() -> di::Result<Signalfd>;
}
