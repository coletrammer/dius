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
}
