#include "dius/posix/syscalls.h"

#include "di/container/string/zstring.h"
#include "dius/c_definitions.h"
#include "dius/config.h"

namespace dius::syscalls {
auto sys_read(int fd, di::Span<byte> data) -> Result<usize> {
    auto result = ::read(fd, data.data(), data.size());
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return usize(result);
}

auto sys_write(int fd, di::Span<byte const> data) -> Result<usize> {
    auto result = ::write(fd, data.data(), data.size());
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return usize(result);
}

auto sys_pread(int fd, u64 offset, di::Span<byte> data) -> Result<usize> {
    auto result = ::pread(fd, data.data(), data.size(), off_t(offset));
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return usize(result);
}

auto sys_pwrite(int fd, u64 offset, di::Span<byte const> data) -> Result<usize> {
    auto result = ::pwrite(fd, data.data(), data.size(), off_t(offset));
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return usize(result);
}

auto sys_close(int fd) -> Result<> {
    auto result = ::close(fd);
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return {};
}

auto sys_dup2(int old_fd, int new_fd) -> Result<> {
    auto result = ::dup2(old_fd, new_fd);
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return {};
}

auto sys_open(di::PathView path, int flags, u16 create_mode) -> Result<int> {
    auto raw_data = path.data();
    char null_terminated_string[4097];
    if (raw_data.size() > sizeof(null_terminated_string) - 1) {
        return di::Unexpected(di::BasicError::FilenameTooLong);
    }

    di::copy(raw_data, null_terminated_string);
    null_terminated_string[raw_data.size()] = '\0';

    auto result = ::open(null_terminated_string, flags, create_mode);
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return result;
}

auto sys_ftruncate(int fd, u64 size) -> Result<> {
    auto result = ::ftruncate(fd, off_t(size));
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return {};
}

auto sys_munmap(byte* data, size_t length) -> Result<> {
    auto result = ::munmap(data, length);
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return {};
}

auto sys_mmap(void* addr, usize length, int prot, int flags, int fd, u64 offset) -> Result<byte*> {
    auto* result = ::mmap(addr, length, prot, flags, fd, off_t(offset));
    if (result == MAP_FAILED) {
        return di::Unexpected(di::BasicError(errno));
    }
    return static_cast<byte*>(result);
}
auto sys_ioctl(int fd, unsigned long code, void* arg) -> Result<> {
    auto result = ::ioctl(fd, code, arg);
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return {};
}

auto sys_setsid() -> Result<> {
    auto result = ::setsid();
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return {};
}

auto sys_fork() -> Result<ProcessId> {
    auto result = ::fork();
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return result;
}

auto sys_execve(char const* path, char** args, char** env) -> Result<> {
    auto result = execve(path, args, env);
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    di::unreachable();
    return {};
}

auto sys_ptsname(int fd) -> Result<di::Path> {
    auto* result = ::ptsname(fd);
    if (result == nullptr) {
        return di::Unexpected(di::BasicError(errno));
    }

    auto zstring = di::ZCString(result);
    auto zstring_end = di::next(zstring.begin(), zstring.end());
    return di::TransparentStringView(&*zstring.begin(), &*zstring_end) | di::to<di::Path>();
}

auto sys_grantpt(int fd) -> Result<> {
    auto result = ::grantpt(fd);
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return {};
}

auto sys_unlockpt(int fd) -> Result<> {
    auto result = ::unlockpt(fd);
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return {};
}

auto sys_tcgetattr(int fd) -> Result<termios> {
    termios output;
    auto result = ::tcgetattr(fd, &output);
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return output;
}

auto sys_tcsetattr(int fd, termios const& termios) -> Result<> {
    auto result = ::tcsetattr(fd, 0, &termios);
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return {};
}

auto sys_mknod(di::PathView path, u32 type, u32 perms) -> Result<> {
    auto raw_data = path.data();
    char null_terminated_string[4097];
    if (raw_data.size() > sizeof(null_terminated_string) - 1) {
        return di::Unexpected(di::BasicError::FilenameTooLong);
    }

    di::copy(raw_data, null_terminated_string);
    null_terminated_string[raw_data.size()] = '\0';

    auto result = ::mknod(null_terminated_string, type | perms, 0);
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return {};
}

auto sys_mkdir(di::PathView path, u32 perms) -> Result<> {
    auto raw_data = path.data();
    char null_terminated_string[4097];
    if (raw_data.size() > sizeof(null_terminated_string) - 1) {
        return di::Unexpected(di::BasicError::FilenameTooLong);
    }

    di::copy(raw_data, null_terminated_string);
    null_terminated_string[raw_data.size()] = '\0';

    auto result = ::mkdir(null_terminated_string, perms);
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return {};
}

auto sys_stat(di::PathView path) -> Result<Stat> {
    auto raw_data = path.data();
    char null_terminated_string[4097];
    if (raw_data.size() > sizeof(null_terminated_string) - 1) {
        return di::Unexpected(di::BasicError::FilenameTooLong);
    }

    di::copy(raw_data, null_terminated_string);
    null_terminated_string[raw_data.size()] = '\0';

    auto output = Stat {};
    auto result = ::stat(null_terminated_string, &output);
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return output;
}

auto sys_lstat(di::PathView path) -> Result<Stat> {
    auto raw_data = path.data();
    char null_terminated_string[4097];
    if (raw_data.size() > sizeof(null_terminated_string) - 1) {
        return di::Unexpected(di::BasicError::FilenameTooLong);
    }

    di::copy(raw_data, null_terminated_string);
    null_terminated_string[raw_data.size()] = '\0';

    auto output = Stat {};
    auto result = ::lstat(null_terminated_string, &output);
    if (result < 0) {
        return di::Unexpected(di::BasicError(errno));
    }
    return output;
}

#ifdef DIUS_HAVE_CLOCK_NANOSLEEP
auto sys_clock_nanosleep(int clock, int flags, timespec timespec) -> Result<::timespec> {
    ::timespec rem;
    (void) clock_nanosleep(clock, flags, &timespec, &rem);
    return rem;
}
#endif
}
