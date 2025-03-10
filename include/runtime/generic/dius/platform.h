#pragma once

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
using ThreadId = i32;

auto get_current_thread_id() -> ThreadId;

using DefaultLock = dius::Mutex;
using DefaultAllocator = container::InfallibleAllocator;
using DefaultFallibleAllocator = container::FallibleAllocator;
}
