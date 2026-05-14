#include "dius/linux/pidfd.h"
#include "dius/platform_process.h"
#include "dius/platform_process_handle.h"
#include "dius/system/process_result.h"
#include "dius/system/system_call.h"

namespace dius::system {
static auto sys_kill(ProcessId id, int signal) -> di::Result<void> {
    return system::system_call<int>(system::Number::kill, id, signal) % di::into_void;
}

static auto sys_getpid() -> di::Result<ProcessId> {
    return system::system_call<ProcessId>(system::Number::getpid);
}

ProcessHandle::ProcessHandle(ProcessId id) : m_id(id) {
    // Errors are ignored because older kernels do not support pidfd, and we will
    // fallback to the base operations in this case.
    auto pidfd = linux::create_pidfd(id);
    if (pidfd) {
        m_pidfd = di::move(pidfd).value();
    }
}

auto ProcessHandle::self() -> ProcessHandle {
    // This really shouldn't fail...
    return ProcessHandle(di::in_place, sys_getpid().value());
}

auto ProcessHandle::sync_wait(bool nonblocking) -> di::Result<ProcessResult> {
    if (id() == -1) {
        return di::Unexpected(di::BasicError::NoSuchProcess);
    }

    auto flags = nonblocking ? WNOHANG : 0;
    if (m_pidfd) {
        // On ENOSYS or ECHILD just try the fallback path.
        auto result = m_pidfd->sync_wait(nonblocking);
        if (result != di::Unexpected(PosixError::FunctionNotSupported) &&
            result != di::Unexpected(PosixError::NoChildProcess)) {
            return result;
        }
    }

    int status;
    auto result = TRY(system_call<ProcessId>(Number::wait4, id(), &status, flags, nullptr));
    if (result == 0) {
        return di::Unexpected(PosixError::ResourceUnavailableTryAgain);
    }

    // NOTE: Linux's wait.h header does not define WIFEXITED, WEXITSTATUS, WIFSIGNALED, and WTERMSIG, so it is done
    //       manually here. In the future, it would be nice to take these definitions from libccpp's headers.
    auto const signal = (status & 0x7F);
    if (signal == 0) {
        // Exited.
        return ProcessResult { (status & 0xFF00) >> 8, false };
    }
    // Signaled.
    return ProcessResult { (status & 0x7F), true };
}

auto ProcessHandle::signal(Signal signal) -> di::Result<> {
    if (id() == -1) {
        return di::Unexpected(di::BasicError::NoSuchProcess);
    }
    if (m_pidfd) {
        // On ENOSYS just try the fallback path.
        auto result = m_pidfd->signal(signal);
        if (result != di::Unexpected(PosixError::FunctionNotSupported)) {
            return result;
        }
    }
    return sys_kill(id(), int(signal));
}
}
