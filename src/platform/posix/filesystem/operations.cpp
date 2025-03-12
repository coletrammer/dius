#include "di/assert/prelude.h"
#include "di/container/algorithm/prelude.h"
#include "di/vocab/error/prelude.h"
#include "dius/c_definitions.h"
#include "dius/filesystem/prelude.h"
#include "dius/posix/syscalls.h"

namespace dius::filesystem::detail {
auto CreateRegularFileFunction::operator()(di::PathView path) const -> di::Result<bool> {
    auto result = syscalls::sys_mknod(path, u32(S_IFREG), u32(Perms::All));
    if (!result) {
        if (result.error() == PosixError::FileExists) {
            return false;
        }
        return di::Unexpected(result.error());
    }
    return true;
}

auto CreateDirectoryFunction::operator()(di::PathView path) const -> di::Result<bool> {
    auto result = syscalls::sys_mkdir(path, u32(Perms::All));
    if (!result) {
        if (result.error() == PosixError::FileExists) {
            return false;
        }
        return di::Unexpected(result.error());
    }
    return true;
}
}
