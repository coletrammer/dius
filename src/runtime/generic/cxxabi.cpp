#include "di/assert/prelude.h"
#include "di/sync/prelude.h"
#include "di/util/prelude.h"

namespace __cxxabiv1 {
extern "C" [[gnu::weak]] [[noreturn]] void __cxa_pure_virtual() {
    ASSERT(false);
    di::unreachable();
}

extern "C" auto __cxa_atexit(void (*)(void*), void*, void*) -> int {
    return 0;
}

__extension__ using __guard = long __attribute__((mode(__DI__)));

extern "C" [[gnu::weak]] auto __cxa_guard_acquire(__guard* guard) -> int {
    __guard expected = 0;
    if (di::AtomicRef(*guard).compare_exchange_strong(expected, 1, di::MemoryOrder::AcquireRelease)) {
        return 1;
    }

    while (expected == 1) {
        expected = di::AtomicRef(*guard).load(di::MemoryOrder::Acquire);
    }

    return 0;
}

extern "C" [[gnu::weak]] void __cxa_guard_release(__guard* guard) {
    di::AtomicRef(*guard).store(2, di::MemoryOrder::Release);
}
}
