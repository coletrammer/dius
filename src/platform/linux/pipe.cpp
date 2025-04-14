#include "dius/sync_file.h"

namespace dius {
auto open_pipe(OpenFlags flags) -> di::Expected<di::Tuple<SyncFile, SyncFile>, di::GenericCode> {
    auto pipe_flags = !!(flags & OpenFlags::KeepAfterExec) ? 0 : O_CLOEXEC;
    int fds[2];
    if (pipe2(fds, pipe_flags) < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return di::Tuple { SyncFile(SyncFile::Owned::Yes, fds[0]), SyncFile(SyncFile::Owned::Yes, fds[1]) };
}
}
