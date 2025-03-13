#include "dius/system/process.h"

#include <csignal>
#include <errno.h>
#include <pthread.h>
#include <spawn.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "di/container/algorithm/find.h"
#include "di/container/iterator/next.h"
#include "di/container/string/string.h"
#include "di/container/string/string_view.h"
#include "di/container/string/zstring.h"
#include "di/container/tree/tree_set.h"
#include "di/util/scope_exit.h"
#include "dius/posix/open_mode_flags.h"
#include "dius/posix/syscalls.h"
#include "dius/posix/utils.h"
#include "dius/sync_file.h"

namespace dius::system {
auto ProcessHandle::self() -> ProcessHandle {
    return ProcessHandle(getpid());
}

auto ProcessHandle::wait() -> di::Result<ProcessResult> {
    if (id() == -1) {
        return di::Unexpected(di::BasicError::NoSuchProcess);
    }

    auto status = 0;
    auto wait_result = waitpid(id(), &status, 0);
    if (wait_result == -1) {
        return di::Unexpected(di::BasicError(errno));
    }
    if (WIFEXITED(status)) {
        return ProcessResult { WEXITSTATUS(status), false };
    }
    return ProcessResult { WTERMSIG(status), true };
}

auto ProcessHandle::signal(Signal signal) -> di::Result<> {
    if (id() == -1) {
        return di::Unexpected(di::BasicError::NoSuchProcess);
    }

    auto res = kill(id(), int(signal));
    if (res < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return {};
}

auto Process::spawn() && -> di::Result<ProcessHandle> {
    // Using fork() is necessary under certain cases because certain actions aren't doable via posix_spawn().
    // Namely, calling ioctl(TIOCSCTTY), to set the controlling terminal of a process.
    if (m_use_fork) {
        return di::move(*this).spawn_with_fork();
    }
    return di::move(*this).spawn_with_posix_spawn();
}

auto mask_signal(Signal signal) -> di::Result<void> {
    auto set = sigset_t {};
    sigemptyset(&set);
    sigaddset(&set, int(signal));
    int res = pthread_sigmask(SIG_BLOCK, &set, nullptr);
    if (res < 0) {
        return di::Unexpected(di::BasicError(-res));
    }
    return {};
}

auto wait_for_signal(Signal signal) -> di::Result<Signal> {
    auto set = sigset_t {};
    sigemptyset(&set);
    sigaddset(&set, int(signal));
    int sig_out = 0;
    auto res = sigwait(&set, &sig_out);
    if (res < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return Signal(sig_out);
}

void exit_thread() {
    pthread_exit(nullptr);
}

void exit_process(int code) {
    exit(code);
}
}
