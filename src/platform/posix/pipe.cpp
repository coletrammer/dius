#include "dius/sync_file.h"

namespace dius {
auto open_pipe_sync(OpenFlags flags) -> di::Expected<di::Tuple<SyncFile, SyncFile>, di::GenericCode> {
    int fds[2];
    if (pipe(fds) < 0) {
        return di::Unexpected(di::BasicError(errno));
    }

    // Make the result first, so we will automatically close files on errors below.
    auto result = di::Tuple { SyncFile(SyncFile::Owned::Yes, fds[0]), SyncFile(SyncFile::Owned::Yes, fds[1]) };
    TRY(result.get<0>().set_open_flags(flags));
    TRY(result.get<1>().set_open_flags(flags));
    return result;
}
}
