#include "dius/sync_file.h"
#include "dius/system/system_call.h"

namespace dius {
auto open_pipe(OpenFlags flags) -> di::Expected<di::Tuple<SyncFile, SyncFile>, di::GenericCode> {
    auto pipe_flags = !!(flags & OpenFlags::KeepAfterExec) ? 0 : O_CLOEXEC;
    int fds[2];
    if (auto rv = system::system_call<int>(system::Number::pipe2, fds, pipe_flags); !rv) {
        return di::Unexpected(rv.error());
    }
    return di::Tuple { SyncFile(SyncFile::Owned::Yes, fds[0]), SyncFile(SyncFile::Owned::Yes, fds[1]) };
}
}
