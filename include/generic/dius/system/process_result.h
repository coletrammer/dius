#pragma once

#include "di/assert/prelude.h"

namespace dius::system {
class ProcessResult {
public:
    explicit ProcessResult(int exit_code_or_signal, bool signaled)
        : m_exit_code_or_signal(exit_code_or_signal), m_signaled(signaled) {}

    auto signaled() const -> bool { return m_signaled; }
    auto exited() const -> bool { return !m_signaled; }

    auto exit_code() const -> int {
        ASSERT(exited());
        return m_exit_code_or_signal;
    }

    auto signal() const -> int {
        ASSERT(signaled());
        return m_exit_code_or_signal;
    }

private:
    int m_exit_code_or_signal { 0 };
    bool m_signaled { false };
};
}
