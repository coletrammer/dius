#include "dius/filesystem/operations.h"

#include "di/assert/prelude.h"
#include "di/container/algorithm/prelude.h"
#include "di/vocab/error/prelude.h"
#include "dius/c_definitions.h"
#include "dius/config.h"
#include "dius/filesystem/directory_iterator.h"
#include "dius/filesystem/prelude.h"
#include "dius/filesystem/query/status.h"
#include "dius/posix/syscalls.h"
#include "dius/sync_file.h"

namespace dius::filesystem::detail {
auto CreateRegularFileFunction::operator()(di::PathView path) -> di::Result<bool> {
#ifdef DIUS_USE_MKNOD_TO_CREATE_FILES
    auto result = syscalls::sys_mknod(path, u32(S_IFREG), u32(Perms::All));
#else
    auto result = dius::open_sync(path, OpenMode::WriteNew, u16(Perms::All));
#endif

    if (!result) {
        if (result.error() == PosixError::FileExists) {
            return false;
        }
        return di::Unexpected(result.error());
    }
    return true;
}

auto CreateDirectoryFunction::operator()(di::PathView path) -> di::Result<bool> {
    auto result = syscalls::sys_mkdir(path, u32(Perms::All));
    if (!result) {
        if (result.error() == PosixError::FileExists) {
            return false;
        }
        return di::Unexpected(result.error());
    }
    return true;
}

auto CreateDirectoryFunction::operator()(di::PathView path, di::PathView existing_path) -> di::Result<bool> {
    auto perms = TRY(status(existing_path)).permissions();
    auto result = syscalls::sys_mkdir(path, u32(perms));
    if (!result) {
        if (result.error() == PosixError::FileExists) {
            return false;
        }
        return di::Unexpected(result.error());
    }
    return true;
}

auto CreateDirectoriesFunction::operator()(di::PathView path) -> di::Result<bool> {
    for (auto it = di::next(path.begin(), 1, path.end()); it != path.end(); ++it) {
        auto prefix = di::PathView(path.begin(), it);

        // Skip trying to create '/', but try and create all other components.
        if (prefix != "/"_pv) {
            TRY(create_directory(prefix));
        }
    }
    return TRY(create_directory(path));
}

auto RemoveFunction::operator()(di::PathView path) -> di::Result<bool> {
    auto result = syscalls::sys_unlink(path);
    if (!result) {
        // On Linux, EISDIR is returned, while on MacOS, EPERM is returned.
        if (result.error() == PosixError::IsADirectory || result.error() == PosixError::OperationNotPermitted) {
            TRY(syscalls::sys_rmdir(path));
            return true;
        }
        if (result.error() == PosixError::NoSuchFileOrDirectory) {
            return false;
        }
        return di::Unexpected(result.error());
    }
    return true;
}

auto RemoveAllFunction::operator()(di::PathView path) -> di::Result<umax> {
    auto result = umax(0);

    auto handle_error = [&](di::Error error) -> di::Result<umax> {
        if (error == PosixError::NotADirectory) {
            result += TRY(remove(path));
            return result;
        }
        return di::Unexpected(di::move(error));
    };

    auto it = DirectoryIterator::create(path.to_owned());
    if (!it) {
        if (it.error() == PosixError::NoSuchFileOrDirectory) {
            return result;
        }
        return handle_error(di::move(it).error());
    }
    for (auto entry : it.value()) {
        if (!entry) {
            return handle_error(di::move(entry).error());
        }
        result += TRY(remove_all(entry.value().path_view()));
    }
    result += TRY(remove(path));
    return result;
}
}
