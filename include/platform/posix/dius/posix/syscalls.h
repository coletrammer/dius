#pragma once

#include "di/container/path/path.h"
#include "di/container/path/path_view.h"
#include "di/vocab/error/prelude.h"
#include "di/vocab/expected/prelude.h"
#include "di/vocab/span/prelude.h"
#include "dius/c_definitions.h"
#include "dius/platform_process.h"

namespace dius::syscalls {
template<typename T = void>
using Result = di::Expected<T, di::GenericCode>;

auto sys_read(int fd, di::Span<byte> data) -> Result<usize>;
auto sys_write(int fd, di::Span<byte const> data) -> Result<usize>;
auto sys_pread(int fd, u64 offset, di::Span<byte> data) -> Result<usize>;
auto sys_pwrite(int fd, u64 offset, di::Span<byte const> data) -> Result<usize>;
auto sys_close(int fd) -> Result<>;
auto sys_dup2(int old_fd, int new_fd) -> Result<>;

auto sys_open(di::PathView path, int flags, u16 create_mode) -> Result<int>;
auto sys_ftruncate(int fd, u64 size) -> Result<>;

auto sys_munmap(byte* data, usize length) -> Result<>;
auto sys_mmap(void* addr, usize length, int prot, int flags, int fd, u64 offset) -> Result<byte*>;

auto sys_ioctl(int fd, unsigned long code, void* arg) -> Result<>;

auto sys_setsid() -> Result<>;
auto sys_fork() -> Result<ProcessId>;
auto sys_execve(char const* path, char** args, char** env) -> Result<>;

auto sys_ptsname(int fd) -> Result<di::Path>;
auto sys_grantpt(int fd) -> Result<>;
auto sys_unlockpt(int fd) -> Result<>;
auto sys_tcgetattr(int fd) -> Result<termios>;
auto sys_tcsetattr(int fd, termios const& termios) -> Result<>;

auto sys_mkdir(di::PathView path, u32 perms) -> Result<>;
auto sys_mknod(di::PathView path, u32 type, u32 perms) -> Result<>;
auto sys_fchdir(i32 fd) -> Result<>;
auto sys_unlink(di::PathView path) -> Result<>;
auto sys_rmdir(di::PathView path) -> Result<>;

auto sys_stat(di::PathView path) -> Result<Stat>;
auto sys_lstat(di::PathView path) -> Result<Stat>;

auto sys_clock_nanosleep(int clock, int flags, timespec timespec) -> Result<::timespec>;
}
