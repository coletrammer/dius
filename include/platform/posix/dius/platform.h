#pragma once

#include <pthread.h>

#include "di/container/allocator/forward_declaration.h"
#include "di/sync/dumb_spinlock.h"
#include "di/vocab/error/result.h"
#include "di/vocab/error/status_code_forward_declaration.h"
#include "dius/error.h"
#include "dius/mutex.h"

namespace di::sync {
class DumbSpinlock;
}

namespace di::platform {
using ThreadId = pthread_t;

inline auto get_current_thread_id() -> ThreadId {
    return pthread_self();
}

using DefaultLock = dius::Mutex;
using DefaultAllocator = container::InfallibleAllocator;
using DefaultFallibleAllocator = container::FallibleAllocator;
}
