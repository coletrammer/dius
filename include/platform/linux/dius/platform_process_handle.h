#pragma once

#include "di/vocab/error/result.h"
#include "dius/linux/pidfd.h"
#include "dius/platform_process.h"
#include "dius/system/process_result.h"

namespace dius::system {
class ProcessHandle {
public:
    static auto self() -> ProcessHandle;

    ProcessHandle() = default;
    explicit ProcessHandle(ProcessId id);

    constexpr auto id() const -> ProcessId { return m_id; }

    auto sync_wait() -> di::Result<ProcessResult>;

    auto signal(Signal signal) -> di::Result<>;

    // Used for testing the fallback case.
    void internal_clear_pidfd() { m_pidfd = {}; }

private:
    constexpr explicit ProcessHandle(di::InPlace, ProcessId id) : m_id(id) {}

    ProcessId m_id { -1 };
    di::Arc<linux::Pidfd> m_pidfd;
};
}
