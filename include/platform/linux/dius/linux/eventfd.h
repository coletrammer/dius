#pragma once

#include "dius/sync_file.h"

namespace dius::linux {
auto create_eventfd(u64 initial_value) -> di::Result<SyncFile>;
}
