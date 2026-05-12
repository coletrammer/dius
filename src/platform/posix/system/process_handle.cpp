#include <csignal>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "dius/platform_process_handle.h"

namespace dius::system {
auto ProcessHandle::self() -> ProcessHandle {
    return ProcessHandle(getpid());
}

auto ProcessHandle::sync_wait() -> di::Result<ProcessResult> {
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
}
