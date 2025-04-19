#include "dius/posix/syscalls.h"

#include "dius/system/system_call.h"

namespace dius::syscalls {
auto sys_read(int fd, di::Span<byte> data) -> Result<usize> {
    return system::system_call<usize>(system::Number::read, fd, data.data(), data.size());
}

auto sys_write(int fd, di::Span<byte const> data) -> Result<usize> {
    return system::system_call<usize>(system::Number::write, fd, data.data(), data.size());
}

auto sys_pread(int fd, u64 offset, di::Span<byte> data) -> Result<usize> {
    return system::system_call<usize>(system::Number::pread, fd, data.data(), data.size(), offset);
}

auto sys_pwrite(int fd, u64 offset, di::Span<byte const> data) -> Result<usize> {
    return system::system_call<usize>(system::Number::pwrite, fd, data.data(), data.size(), offset);
}

auto sys_dup2(int old_fd, int new_fd) -> Result<> {
    return system::system_call<int>(system::Number::dup2, old_fd, new_fd) % di::into_void;
}

auto sys_close(int fd) -> Result<> {
    return system::system_call<int>(system::Number::close, fd) % di::into_void;
}

auto sys_open(di::PathView path, int flags, u16 create_mode) -> Result<int> {
    auto raw_data = path.data();
    char null_terminated_string[4097];
    if (raw_data.size() > sizeof(null_terminated_string) - 1) {
        return di::Unexpected(di::BasicError::FilenameTooLong);
    }

    di::copy(raw_data, null_terminated_string);
    null_terminated_string[raw_data.size()] = '\0';

    return system::system_call<int>(system::Number::openat, AT_FDCWD, null_terminated_string, flags, create_mode);
}

auto sys_ftruncate(int fd, u64 size) -> Result<> {
    return system::system_call<int>(system::Number::ftruncate, fd, size) % di::into_void;
}

auto sys_munmap(byte* data, size_t length) -> Result<> {
    return system::system_call<int>(system::Number::munmap, data, length) % di::into_void;
}

auto sys_mmap(void* addr, usize length, int prot, int flags, int fd, u64 offset) -> Result<byte*> {
    return system::system_call<byte*>(system::Number::mmap, addr, length, prot, flags, fd, offset);
}
auto sys_ioctl(int fd, unsigned long code, void* arg) -> Result<> {
    return system::system_call<int>(system::Number::ioctl, fd, code, arg) % di::into_void;
}

auto sys_setsid() -> Result<> {
    return system_call<int>(system::Number::setsid) % di::into_void;
}

auto sys_fork() -> Result<ProcessId> {
    auto args = ::clone_args {
        .flags = CLONE_CLEAR_SIGHAND,
        .pidfd = 0,
        .child_tid = 0,
        .parent_tid = 0,
        .exit_signal = SIGCHLD,
        .stack = 0,
        .stack_size = 0,
        .tls = 0,
        .set_tid = 0,
        .set_tid_size = 0,
        .cgroup = 0,
    };
    return system_call<ProcessId>(system::Number::clone3, &args, sizeof(args));
}

auto sys_execve(char const* path, char** args, char** env) -> Result<> {
    return system_call<int>(system::Number::execve, path, args, env) % di::into_void;
}

auto sys_ptsname(int fd) -> Result<di::Path> {
    u32 pty_number = 0;
    TRY(syscalls::sys_ioctl(fd, TIOCGPTN, &pty_number));

    auto result = "/dev/pts"_p;
    auto pty = di::to_string(pty_number) | di::transform([](c32 code_point) {
                   return char(code_point);
               }) |
               di::to<di::TransparentString>();
    result /= pty;
    return result;
}

auto sys_grantpt(int fd) -> Result<> {
    u32 pty_number = 0;
    return sys_ioctl(fd, TIOCGPTN, &pty_number);
}

auto sys_unlockpt(int fd) -> Result<> {
    int unlock = 0;
    return sys_ioctl(fd, TIOCSPTLCK, &unlock);
}

auto sys_tcgetattr(int fd) -> Result<termios> {
    termios result;
    TRY(sys_ioctl(fd, TCGETS, &result));
    return result;
}

auto sys_tcsetattr(int fd, termios const& termios) -> Result<> {
    return sys_ioctl(fd, TCSETS, di::voidify(&termios));
}

auto sys_mknod(di::PathView path, u32 type, u32 perms) -> Result<> {
    auto raw_data = path.data();
    char null_terminated_string[4097];
    if (raw_data.size() > sizeof(null_terminated_string) - 1) {
        return di::Unexpected(di::BasicError::FilenameTooLong);
    }

    di::copy(raw_data, null_terminated_string);
    null_terminated_string[raw_data.size()] = '\0';

    return system::system_call<int>(system::Number::mknodat, AT_FDCWD, null_terminated_string, perms | u32(type), 0) %
           di::into_void;
}

auto sys_mkdir(di::PathView path, u32 perms) -> Result<> {
    auto raw_data = path.data();
    char null_terminated_string[4097];
    if (raw_data.size() > sizeof(null_terminated_string) - 1) {
        return di::Unexpected(di::BasicError::FilenameTooLong);
    }

    di::copy(raw_data, null_terminated_string);
    null_terminated_string[raw_data.size()] = '\0';

    return system::system_call<int>(system::Number::mkdirat, AT_FDCWD, null_terminated_string, perms) % di::into_void;
}

auto sys_rmdir(di::PathView path) -> Result<> {
    auto raw_data = path.data();
    char null_terminated_string[4097];
    if (raw_data.size() > sizeof(null_terminated_string) - 1) {
        return di::Unexpected(di::BasicError::FilenameTooLong);
    }

    di::copy(raw_data, null_terminated_string);
    null_terminated_string[raw_data.size()] = '\0';

    return system::system_call<int>(system::Number::rmdir, null_terminated_string) % di::into_void;
}

auto sys_unlink(di::PathView path) -> Result<> {
    auto raw_data = path.data();
    char null_terminated_string[4097];
    if (raw_data.size() > sizeof(null_terminated_string) - 1) {
        return di::Unexpected(di::BasicError::FilenameTooLong);
    }

    di::copy(raw_data, null_terminated_string);
    null_terminated_string[raw_data.size()] = '\0';

    return system::system_call<int>(system::Number::unlink, null_terminated_string) % di::into_void;
}

auto sys_fchdir(i32 fd) -> Result<> {
    return system::system_call<int>(system::Number::fchdir, fd) % di::into_void;
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
    TRY(system::system_call<int>(system::Number::fstatat64, AT_FDCWD, null_terminated_string, &output, 0));
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
    TRY(system::system_call<int>(system::Number::fstatat64, AT_FDCWD, null_terminated_string, &output,
                                 AT_SYMLINK_NOFOLLOW));
    return output;
}

auto sys_clock_nanosleep(int clock, int flags, timespec timespec) -> Result<::timespec> {
    ::timespec rem;
    (void) system::system_call<i32>(system::Number::clock_nanosleep, clock, flags, &timespec, &rem);
    return rem;
}
}
