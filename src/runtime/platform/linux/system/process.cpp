#include "dius/system/process.h"

#include <linux/signal.h>
#include <linux/wait.h>

#include "di/container/string/zstring.h"
#include "di/container/tree/tree_set.h"
#include "dius/print.h"
#include "dius/system/system_call.h"

namespace dius::system {
static auto s_envp = static_cast<char**>(nullptr);

[[gnu::constructor]] static void get_env_on_init(int, char**, char** envp) {
    s_envp = envp;
}

// I'm not sure why this isn't a u128.
using kernel_sigset_t = u64;

static auto sys_rt_sigprocmask(int how, kernel_sigset_t const* set, kernel_sigset_t* old) -> di::Result<void> {
    return system::system_call<int>(system::Number::rt_sigprocmask, how, set, old, sizeof(kernel_sigset_t)) %
           di::into_void;
}

static auto sys_rt_sigtimedwait(kernel_sigset_t const* set, void* info, void* timeout) -> di::Result<Signal> {
    return system::system_call<Signal>(system::Number::rt_sigtimedwait, set, info, timeout, sizeof(kernel_sigset_t));
}

static auto sys_kill(ProcessId id, int signal) -> di::Result<void> {
    return system::system_call<int>(system::Number::kill, id, signal) % di::into_void;
}

static auto sys_getpid() -> di::Result<ProcessId> {
    return system::system_call<ProcessId>(system::Number::getpid);
}

auto ProcessHandle::self() -> ProcessHandle {
    // This really shouldn't fail...
    return ProcessHandle(sys_getpid().value());
}

auto ProcessHandle::wait() -> di::Result<ProcessResult> {
    if (id() == -1) {
        return di::Unexpected(di::BasicError::NoSuchProcess);
    }

    int status;
    TRY(system_call<ProcessId>(Number::wait4, id(), &status, 0, nullptr));

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
    return sys_kill(id(), int(signal));
}

auto Process::spawn() && -> di::Result<ProcessHandle> {
    return di::move(*this).spawn_with_fork();
}

void install_dummy_signal_handler(Signal) {}

auto mask_signal(Signal signal) -> di::Result<void> {
    auto mask = kernel_sigset_t(1) << (kernel_sigset_t(signal) - 1);
    return sys_rt_sigprocmask(SIG_BLOCK, &mask, nullptr);
}

auto wait_for_signal(Signal signal) -> di::Result<Signal> {
    auto mask = kernel_sigset_t(1) << (kernel_sigset_t(signal) - 1);
    return sys_rt_sigtimedwait(&mask, nullptr, nullptr);
}

void exit_thread() {
    (void) dius::system::system_call<i32>(dius::system::Number::exit, 0);
    di::unreachable();
}

void exit_process(int code) {
    (void) dius::system::system_call<i32>(dius::system::Number::exit_group, code);
    di::unreachable();
}
}
