#include "dius/sync_file.h"

namespace dius {
auto open_pipe(OpenFlags flags) -> di::Expected<di::Tuple<SyncFile, SyncFile>, di::GenericCode> {
    int fds[2];
    if (pipe(fds) < 0) {
        return di::Unexpected(di::BasicError(errno));
    }

    // Make the result first, so we will automatically close files on errors below.
    auto result = di::Tuple { SyncFile(SyncFile::Owned::Yes, fds[0]), SyncFile(SyncFile::Owned::Yes, fds[1]) };
    if (!(flags & OpenFlags::KeepAfterExec)) {
        if (fcntl(fds[0], F_SETFD, FD_CLOEXEC) < 0) {
            return di::Unexpected(di::BasicError(errno));
        }
        if (fcntl(fds[1], F_SETFD, FD_CLOEXEC) < 0) {
            return di::Unexpected(di::BasicError(errno));
        }
    }
    return result;
}
}
