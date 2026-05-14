#include "dius/linux/pidfd.h"

#include "dius/c_definitions.h"
#include "dius/platform_process.h"
#include "dius/sync_file.h"
#include "dius/system/system_call.h"

namespace dius::linux {
#ifndef P_PIDFD
constexpr inline auto P_PIDFD = 3;
#endif

auto Pidfd::sync_wait(bool nonblocking) const -> di::Result<system::ProcessResult> {
    auto siginfo = siginfo_t {};
    auto flags = WEXITED | (nonblocking ? WNOHANG : 0);
    TRY(system::system_call<i32>(system::Number::waitid, P_PIDFD, file_descriptor(), &siginfo, flags, nullptr));

    if (siginfo.si_pid == 0) {
        return di::Unexpected(PosixError::ResourceUnavailableTryAgain);
    }
    auto const signalled = siginfo.si_code != CLD_EXITED;
    return system::ProcessResult { siginfo.si_status, signalled };
}

auto Pidfd::signal(Signal signal) const -> di::Result<> {
#ifdef DIUS_PIDFD_SEND_SIGNAL
    return system::system_call<i32>(system::Number::pidfd_send_signal, file_descriptor(), signal, nullptr, 0) %
           di::into_void;
#else
    return di::Unexpected(dius::PosixError::FunctionNotSupported);
#endif
}

auto create_pidfd(ProcessId id) -> di::Result<di::Arc<Pidfd>> {
#ifdef DIUS_PIDFD_OPEN
    auto fd = TRY(system::system_call<i32>(system::Number::pidfd_open, id, 0));
    return di::make_arc<Pidfd>(Pidfd::Owned::Yes, fd);
#else
    return di::Unexpected(dius::PosixError::FunctionNotSupported);
#endif
}
}
