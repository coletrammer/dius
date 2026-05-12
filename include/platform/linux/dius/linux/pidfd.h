#pragma once

#include "dius/platform_process.h"
#include "dius/sync_file.h"
#include "dius/system/process_result.h"

namespace dius::linux {
class Pidfd
    : public SyncFile
    , public di::IntrusiveRefCount<Pidfd> {
public:
    constexpr explicit Pidfd(Owned owned, int fd) : SyncFile(owned, fd) {}

    auto sync_wait() const -> di::Result<system::ProcessResult>;

    auto signal(Signal signal) const -> di::Result<>;
};

auto create_pidfd(ProcessId id) -> di::Result<di::Arc<Pidfd>>;
}
