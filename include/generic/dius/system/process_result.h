#pragma once

#include "di/assert/prelude.h"
#include "di/reflect/prelude.h"

namespace dius::system {
class ProcessResult {
public:
    ProcessResult() = default;

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

    auto operator==(ProcessResult const&) const -> bool = default;

private:
    constexpr friend auto tag_invoke(di::Tag<di::reflect>, di::InPlaceType<ProcessResult>) {
        return di::make_fields<"ProcessResult">(di::field<"exit_code_or_signal", &ProcessResult::m_exit_code_or_signal>,
                                                di::field<"signalled", &ProcessResult::m_signaled>);
    }

    int m_exit_code_or_signal { 0 };
    bool m_signaled { false };
};
}
