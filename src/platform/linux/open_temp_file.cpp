#include "dius/posix/syscalls.h"
#include "dius/sync_file.h"

namespace dius {
auto open_tempory_file() -> di::Expected<SyncFile, di::GenericCode> {
    auto fd = TRY(syscalls::sys_open("/tmp"_pv, O_TMPFILE | O_RDWR, 0666));
    return SyncFile { SyncFile::Owned::Yes, fd };
}
}
