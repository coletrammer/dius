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

static auto sys_rt_sigprocmask(int how, kernel_sigset_t const* set, kernel_sigset_t* old) -> di::Result<void> {
    return system::system_call<int>(system::Number::rt_sigprocmask, how, set, old, sizeof(kernel_sigset_t)) %
           di::into_void;
}

static auto sys_rt_sigtimedwait(kernel_sigset_t const* set, void* info, void* timeout) -> di::Result<Signal> {
    return system::system_call<Signal>(system::Number::rt_sigtimedwait, set, info, timeout, sizeof(kernel_sigset_t));
}

auto Process::spawn() && -> di::Result<ProcessHandle> {
    return di::move(*this).spawn_with_fork();
}

auto mask_signal(Signal signal) -> di::Result<> {
    auto mask = kernel_sigset_t(1) << (kernel_sigset_t(signal) - 1);
    return sys_rt_sigprocmask(SIG_BLOCK, &mask, nullptr);
}

auto unmask_signal(Signal signal) -> di::Result<> {
    auto mask = kernel_sigset_t(1) << (kernel_sigset_t(signal) - 1);
    return sys_rt_sigprocmask(SIG_UNBLOCK, &mask, nullptr);
}

auto set_signal_mask(di::Span<Signal> signals) -> di::Result<> {
    auto mask = kernel_sigset_t(0);
    for (auto signal : signals) {
        mask |= kernel_sigset_t(1) << (kernel_sigset_t(signal) - 1);
    }
    return sys_rt_sigprocmask(SIG_SETMASK, &mask, nullptr);
}

auto unmask_all_signals() -> di::Result<> {
    auto mask = kernel_sigset_t(-1);
    return sys_rt_sigprocmask(SIG_SETMASK, &mask, nullptr);
}

auto mask_all_signals() -> di::Result<> {
    auto mask = kernel_sigset_t(0);
    return sys_rt_sigprocmask(SIG_SETMASK, &mask, nullptr);
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
