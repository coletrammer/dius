#include "dius/memory_region.h"

#include "di/function/prelude.h"
#include "dius/posix/syscalls.h"

namespace dius {
MemoryRegion::~MemoryRegion() {
    if (!empty()) {
        (void) syscalls::sys_munmap(data(), size());
    }
}
}
