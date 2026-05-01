#pragma once

#include <asm/ioctls.h>
#include <asm/socket.h>
#include <asm/termios.h>
#include <asm/unistd.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/mman.h>
#include <linux/sched.h>
#include <linux/signal.h>
#include <linux/socket.h>
#include <linux/stat.h>
#include <linux/time.h>
#include <linux/types.h>
#include <linux/un.h>
#include <linux/utsname.h>
#include <linux/wait.h>

#include "di/types/integers.h"
#include "di/vocab/array/prelude.h"

namespace dius::syscalls {
// Linux stat64 structure, with correct padding.
struct Stat {
    u64 st_dev;
    u64 st_ino;
    u64 st_nlink;
    u32 st_mode;
    u32 st_uid;
    u32 st_gid;
    di::Array<di::Byte, 4> pading;
    u64 st_rdev;
    i64 st_size;
    i64 st_blksize;
    i64 st_blocks;
    timespec st_atime;
    timespec st_mtime;
    timespec st_ctime;
    di::Array<di::Byte, 24> padding_end;
};

using UtsName = struct ::new_utsname;
}

namespace dius {
using socklen_t = u32;

// Unclear why the linux kernel headers don't define these...
constexpr inline auto AF_UNIX = 1;
constexpr inline auto SOCK_STREAM = 1;
constexpr inline auto SOCK_CLOEXEC = 0x80000;
constexpr inline auto SOCK_NONBLOCK = 0x800;
}
