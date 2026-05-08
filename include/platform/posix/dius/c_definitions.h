#pragma once

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "di/types/integers.h"
#if __has_include(<sys/epoll.h>)
#include <sys/epoll.h>
#endif
#if __has_include(<sys/eventfd.h>)
#include <sys/eventfd.h>
#endif
#if __has_include(<sys/signalfd.h>)
#include <sys/signalfd.h>
#endif

namespace dius::syscalls {
using Stat = struct ::stat;
using UtsName = struct ::utsname;
}

namespace dius {
// I'm not sure why this isn't a u128.
using kernel_sigset_t = u64;
}
