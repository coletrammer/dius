#pragma once

#include "di/vocab/error/result.h"
#include "dius/platform_process.h"

namespace dius {
class ProcessResult;

class ProcessHandle {
public:
    static auto self() -> ProcessHandle;

    ProcessHandle() = default;
    constexpr explicit ProcessHandle(ProcessId id) : m_id(id) {}

    constexpr auto id() const -> ProcessId { return m_id; }

    auto sync_wait() -> di::Result<ProcessResult>;

    auto signal(Signal signal) -> di::Result<>;

private:
    ProcessId m_id { -1 };
};
}
