#pragma once

#include "di/container/path/path.h"
#include "di/container/path/path_view.h"
#include "di/vocab/error/prelude.h"
#include "di/vocab/expected/prelude.h"
#include "di/vocab/span/prelude.h"

namespace dius::syscalls {
template<typename T = void>
using Result = di::Expected<T, di::GenericCode>;

auto sys_read(int fd, di::Span<byte> data) -> Result<usize>;
auto sys_write(int fd, di::Span<byte const> data) -> Result<usize>;
auto sys_pread(int fd, u64 offset, di::Span<byte> data) -> Result<usize>;
auto sys_pwrite(int fd, u64 offset, di::Span<byte const> data) -> Result<usize>;
auto sys_close(int fd) -> Result<>;

auto sys_open(di::PathView path, int flags, u16 create_mode) -> Result<int>;
auto sys_ftruncate(int fd, u64 size) -> Result<>;

auto sys_munmap(byte* addr, usize length) -> Result<>;
auto sys_mmap(void* addr, usize length, int prot, int flags, int fd, u64 offset) -> Result<byte*>;

auto sys_ioctl(int fd, unsigned long code, void* arg) -> Result<>;

auto sys_ptsname(int fd) -> Result<di::Path>;
auto sys_grantpt(int fd) -> Result<>;
auto sys_unlockpt(int fd) -> Result<>;
auto sys_tcgetattr(int fd) -> Result<termios>;
auto sys_tcsetattr(int fd, termios const& termios) -> Result<>;
}
