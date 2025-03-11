#include "di/assert/prelude.h"
#include "di/container/algorithm/prelude.h"
#include "dius/c_definitions.h"
#include "dius/filesystem/prelude.h"
#include "dius/posix/syscalls.h"
#include "dius/system/system_call.h"

namespace dius::filesystem {
static auto stat_to_file_status(dius::syscalls::Stat const& info) -> FileStatus {
    auto type = [&] {
        if (S_ISREG(info.st_mode)) {
            return FileType::Regular;
        }
        if (S_ISDIR(info.st_mode)) {
            return FileType::Directory;
        }
        if (S_ISBLK(info.st_mode)) {
            return FileType::Block;
        }
        if (S_ISCHR(info.st_mode)) {
            return FileType::Character;
        }
        if (S_ISFIFO(info.st_mode)) {
            return FileType::Fifo;
        }
        if (S_ISSOCK(info.st_mode)) {
            return FileType::Socket;
        }
        if (S_ISLNK(info.st_mode)) {
            return FileType::Symlink;
        }
        return FileType::Unknown;
    }();
    return FileStatus(type, Perms(info.st_mode) & Perms::Mask);
}

namespace detail {
    auto IsEmptyFunction::operator()(di::PathView path) const -> di::Result<bool> {
        auto info = TRY(syscalls::sys_stat(path));
        if (!S_ISDIR(info.st_mode) && !S_ISREG(info.st_mode)) {
            return di::Unexpected(PosixError::OperationNotSupported);
        }
        if (S_ISDIR(info.st_mode)) {
            auto it = TRY(di::create<DirectoryIterator>(di::create<di::Path>(path)));
            return it == DirectoryIterator();
        }
        return info.st_size == 0;
    }

    auto StatusFunction::operator()(di::PathView path) const -> di::Result<FileStatus> {
        auto result = syscalls::sys_stat(path);
        if (result == di::Unexpected(PosixError::NoSuchFileOrDirectory)) {
            return FileStatus(FileType::NotFound);
        }
        if (!result) {
            return di::Unexpected(di::move(result).error());
        }

        return stat_to_file_status(result.value());
    }

    auto SymlinkStatusFunction::operator()(di::PathView path) const -> di::Result<FileStatus> {
        auto result = syscalls::sys_lstat(path);
        if (result == di::Unexpected(PosixError::NoSuchFileOrDirectory)) {
            return FileStatus(FileType::NotFound);
        }
        if (!result) {
            return di::Unexpected(di::move(result).error());
        }

        return stat_to_file_status(result.value());
    }

    auto FileSizeFunction::operator()(di::PathView path) const -> di::Result<umax> {
        auto result = TRY(syscalls::sys_lstat(path));
        if (S_ISDIR(result.st_mode)) {
            return di::Unexpected(PosixError::IsADirectory);
        }
        if (!S_ISREG(result.st_mode)) {
            return di::Unexpected(PosixError::OperationNotSupported);
        }
        return result.st_size;
    }

    auto HardLinkCountFunction::operator()(di::PathView path) const -> di::Result<umax> {
        auto result = TRY(syscalls::sys_lstat(path));
        return result.st_nlink;
    }
}
}
