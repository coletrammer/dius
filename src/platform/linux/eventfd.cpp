#include <linux/eventfd.h>

#include "dius/linux/eventfd.h"
#include "dius/sync_file.h"
#include "dius/system/system_call.h"

namespace dius::linux {
auto create_eventfd(u64 initial_value) -> di::Result<SyncFile> {
    auto fd = TRY(system::system_call<i32>(system::Number::eventfd2, initial_value, EFD_CLOEXEC | EFD_NONBLOCK));
    return SyncFile(SyncFile::Owned::Yes, fd);
}
}
