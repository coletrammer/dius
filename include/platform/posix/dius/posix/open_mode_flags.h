#pragma once

#include "dius/c_definitions.h"
#include "dius/sync_file.h"

namespace dius::detail {
inline auto open_mode_flags(OpenMode open_mode, OpenFlags flags) -> int {
    auto base = O_CLOEXEC;
    if (!!(flags & OpenFlags::NoControllingTerminal)) {
        base |= O_NOCTTY;
    }
    if (!!(flags & OpenFlags::KeepAfterExec)) {
        base &= ~O_CLOEXEC;
    }
    switch (open_mode) {
        case OpenMode::Readonly:
            return base | O_RDONLY;
        case OpenMode::WriteNew:
            return base | O_WRONLY | O_EXCL | O_CREAT;
        case OpenMode::WriteClobber:
            return base | O_WRONLY | O_TRUNC | O_CREAT;
        case OpenMode::ReadWrite:
            return base | O_RDWR;
        case OpenMode::AppendOnly:
            return base | O_WRONLY | O_APPEND | O_CREAT;
        case OpenMode::ReadWriteClobber:
            return base | O_RDWR | O_TRUNC | O_CREAT;
        case OpenMode::AppendReadWrite:
            return base | O_RDWR | O_APPEND | O_CREAT;
        default:
            di::unreachable();
    }
}
}
