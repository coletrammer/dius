#pragma once

#include "asm/unistd.h"
#include "di/util/prelude.h"
#include "dius/arch_system_call.h"
#include "dius/c_definitions.h"
#include "dius/error.h"

namespace dius::system {
enum class Number : int {
    io_uring_enter = __NR_io_uring_enter,
    io_uring_setup = __NR_io_uring_setup,
    io_uring_register = __NR_io_uring_register,
    pread = __NR_pread64,
    pwrite = __NR_pwrite64,
    read = __NR_read,
    write = __NR_write,
    close = __NR_close,
    openat = __NR_openat,
    mmap = __NR_mmap,
    munmap = __NR_munmap,
    getdents64 = __NR_getdents64,
    fstatat64 = __NR_newfstatat,
    ftruncate = __NR_ftruncate,
#ifdef __NR_arch_prctl
    arch_prctl = __NR_arch_prctl,
#endif
    brk = __NR_brk,
    exit_group = __NR_exit_group,
    clone3 = __NR_clone3,
    execve = __NR_execve,
    wait4 = __NR_wait4,
    waitid = __NR_waitid,
    exit = __NR_exit,
    futex = __NR_futex,
    lseek = __NR_lseek,
    mknodat = __NR_mknodat,
    mkdirat = __NR_mkdirat,
    bind = __NR_bind,
    listen = __NR_listen,
    accept4 = __NR_accept4,
    socket = __NR_socket,
    connect = __NR_connect,
    shutdown = __NR_shutdown,
    getsoockopt = __NR_getsockopt,
    ioctl = __NR_ioctl,
    rt_sigprocmask = __NR_rt_sigprocmask,
    rt_sigtimedwait = __NR_rt_sigtimedwait,
    kill = __NR_kill,
    getpid = __NR_getpid,
    clock_nanosleep = __NR_clock_nanosleep,
    clock_gettime = __NR_clock_gettime,
    setsid = __NR_setsid,
    dup3 = __NR_dup3,
    pipe2 = __NR_pipe2,
    chdir = __NR_chdir,
    fchdir = __NR_fchdir,
    unlinkat = __NR_unlinkat,
    uname = __NR_uname,
    fcntl = __NR_fcntl,
    epoll_create1 = __NR_epoll_create1,
    epoll_ctl = __NR_epoll_ctl,
    epoll_pwait = __NR_epoll_pwait,
#ifdef __NR_epoll_pwait2
#define DIUS_LINUX_PWAIT2
    epoll_pwait2 = __NR_epoll_pwait2,
#endif
    eventfd2 = __NR_eventfd2,
    signalfd4 = __NR_signalfd4,
#ifdef __NR_pidfd_open
#define DIUS_PIDFD_OPEN
    pidfd_open = __NR_pidfd_open,
#endif
#ifdef __NR_pidfd_send_signal
#define DIUS_PIDFD_SEND_SIGNAL
    pidfd_send_signal = __NR_pidfd_send_signal,
#endif
    inotify_init1 = __NR_inotify_init1,
    inotify_add_watch = __NR_inotify_add_watch,
    inotify_rm_watch = __NR_inotify_rm_watch,
};

using SystemCallArg = unsigned long;
using SystemCallResult = long;

namespace detail {
    template<typename T>
    concept SystemCallArgument = di::concepts::ConstructibleFrom<SystemCallArg, T>;

    template<typename T>
    concept SystemCallResult = di::concepts::ConstructibleFrom<T, dius::system::SystemCallResult>;
}

template<detail::SystemCallResult R>
auto system_call(Number number) -> di::Expected<R, di::BasicError> {
    auto register res asm(DIUS_SYSTEM_CALL_ASM_RESULT) = SystemCallResult(0);
    auto register num asm(DIUS_SYSTEM_CALL_ASM_NUMBER) = di::to_underlying(number);
    asm volatile(DIUS_SYSTEM_CALL_INSTRUCTION : "=r"(res) : "r"(num) : DIUS_SYSTEM_CALL_CLOBBER);
    if (res < 0) {
        return di::Unexpected(di::BasicError(-res));
    }
    return R(res);
}

template<detail::SystemCallResult R, detail::SystemCallArgument T1>
auto system_call(Number number, T1&& a1) -> di::Expected<R, di::BasicError> {
    auto register res asm(DIUS_SYSTEM_CALL_ASM_RESULT) = SystemCallResult(0);
    auto register num asm(DIUS_SYSTEM_CALL_ASM_NUMBER) = di::to_underlying(number);
    auto register x1 asm(DIUS_SYSTEM_CALL_ASM_ARG1) = SystemCallArg(a1);
    asm volatile(DIUS_SYSTEM_CALL_INSTRUCTION : "=r"(res) : "r"(num), "r"(x1) : DIUS_SYSTEM_CALL_CLOBBER);
    if (res < 0) {
        return di::Unexpected(di::BasicError(-res));
    }
    return R(res);
}

template<detail::SystemCallResult R, detail::SystemCallArgument T1, detail::SystemCallArgument T2>
auto system_call(Number number, T1&& a1, T2&& a2) -> di::Expected<R, di::BasicError> {
    auto register res asm(DIUS_SYSTEM_CALL_ASM_RESULT) = SystemCallResult(0);
    auto register num asm(DIUS_SYSTEM_CALL_ASM_NUMBER) = di::to_underlying(number);
    auto register x1 asm(DIUS_SYSTEM_CALL_ASM_ARG1) = SystemCallArg(a1);
    auto register x2 asm(DIUS_SYSTEM_CALL_ASM_ARG2) = SystemCallArg(a2);
    asm volatile(DIUS_SYSTEM_CALL_INSTRUCTION : "=r"(res) : "r"(num), "r"(x1), "r"(x2) : DIUS_SYSTEM_CALL_CLOBBER);
    if (res < 0) {
        return di::Unexpected(di::BasicError(-res));
    }
    return R(res);
}

template<detail::SystemCallResult R, detail::SystemCallArgument T1, detail::SystemCallArgument T2,
         detail::SystemCallArgument T3>
auto system_call(Number number, T1&& a1, T2&& a2, T3&& a3) -> di::Expected<R, di::BasicError> {
    auto register res asm(DIUS_SYSTEM_CALL_ASM_RESULT) = SystemCallResult(0);
    auto register num asm(DIUS_SYSTEM_CALL_ASM_NUMBER) = di::to_underlying(number);
    auto register x1 asm(DIUS_SYSTEM_CALL_ASM_ARG1) = SystemCallArg(a1);
    auto register x2 asm(DIUS_SYSTEM_CALL_ASM_ARG2) = SystemCallArg(a2);
    auto register x3 asm(DIUS_SYSTEM_CALL_ASM_ARG3) = SystemCallArg(a3);
    asm volatile(DIUS_SYSTEM_CALL_INSTRUCTION
                 : "=r"(res)
                 : "r"(num), "r"(x1), "r"(x2), "r"(x3)
                 : DIUS_SYSTEM_CALL_CLOBBER);
    if (res < 0) {
        return di::Unexpected(di::BasicError(-res));
    }
    return R(res);
}

template<detail::SystemCallResult R, detail::SystemCallArgument T1, detail::SystemCallArgument T2,
         detail::SystemCallArgument T3, detail::SystemCallArgument T4>
auto system_call(Number number, T1&& a1, T2&& a2, T3&& a3, T4&& a4) -> di::Expected<R, di::BasicError> {
    auto register res asm(DIUS_SYSTEM_CALL_ASM_RESULT) = SystemCallResult(0);
    auto register num asm(DIUS_SYSTEM_CALL_ASM_NUMBER) = di::to_underlying(number);
    auto register x1 asm(DIUS_SYSTEM_CALL_ASM_ARG1) = SystemCallArg(a1);
    auto register x2 asm(DIUS_SYSTEM_CALL_ASM_ARG2) = SystemCallArg(a2);
    auto register x3 asm(DIUS_SYSTEM_CALL_ASM_ARG3) = SystemCallArg(a3);
    auto register x4 asm(DIUS_SYSTEM_CALL_ASM_ARG4) = SystemCallArg(a4);
    asm volatile(DIUS_SYSTEM_CALL_INSTRUCTION
                 : "=r"(res)
                 : "r"(num), "r"(x1), "r"(x2), "r"(x3), "r"(x4)
                 : DIUS_SYSTEM_CALL_CLOBBER);
    if (res < 0) {
        return di::Unexpected(di::BasicError(-res));
    }
    return R(res);
}

template<detail::SystemCallResult R, detail::SystemCallArgument T1, detail::SystemCallArgument T2,
         detail::SystemCallArgument T3, detail::SystemCallArgument T4, detail::SystemCallArgument T5>
auto system_call(Number number, T1&& a1, T2&& a2, T3&& a3, T4&& a4, T5&& a5) -> di::Expected<R, di::BasicError> {
    auto register res asm(DIUS_SYSTEM_CALL_ASM_RESULT) = SystemCallResult(0);
    auto register num asm(DIUS_SYSTEM_CALL_ASM_NUMBER) = di::to_underlying(number);
    auto register x1 asm(DIUS_SYSTEM_CALL_ASM_ARG1) = SystemCallArg(a1);
    auto register x2 asm(DIUS_SYSTEM_CALL_ASM_ARG2) = SystemCallArg(a2);
    auto register x3 asm(DIUS_SYSTEM_CALL_ASM_ARG3) = SystemCallArg(a3);
    auto register x4 asm(DIUS_SYSTEM_CALL_ASM_ARG4) = SystemCallArg(a4);
    auto register x5 asm(DIUS_SYSTEM_CALL_ASM_ARG5) = SystemCallArg(a5);
    asm volatile(DIUS_SYSTEM_CALL_INSTRUCTION
                 : "=r"(res)
                 : "r"(num), "r"(x1), "r"(x2), "r"(x3), "r"(x4), "r"(x5)
                 : DIUS_SYSTEM_CALL_CLOBBER);
    if (res < 0) {
        return di::Unexpected(di::BasicError(-res));
    }
    return R(res);
}

template<detail::SystemCallResult R, detail::SystemCallArgument T1, detail::SystemCallArgument T2,
         detail::SystemCallArgument T3, detail::SystemCallArgument T4, detail::SystemCallArgument T5,
         detail::SystemCallArgument T6>
auto system_call(Number number, T1&& a1, T2&& a2, T3&& a3, T4&& a4, T5&& a5, T6&& a6)
    -> di::Expected<R, di::BasicError> {
    auto register res asm(DIUS_SYSTEM_CALL_ASM_RESULT) = SystemCallResult(0);
    auto register num asm(DIUS_SYSTEM_CALL_ASM_NUMBER) = di::to_underlying(number);
    auto register x1 asm(DIUS_SYSTEM_CALL_ASM_ARG1) = SystemCallArg(a1);
    auto register x2 asm(DIUS_SYSTEM_CALL_ASM_ARG2) = SystemCallArg(a2);
    auto register x3 asm(DIUS_SYSTEM_CALL_ASM_ARG3) = SystemCallArg(a3);
    auto register x4 asm(DIUS_SYSTEM_CALL_ASM_ARG4) = SystemCallArg(a4);
    auto register x5 asm(DIUS_SYSTEM_CALL_ASM_ARG5) = SystemCallArg(a5);
    auto register x6 asm(DIUS_SYSTEM_CALL_ASM_ARG6) = SystemCallArg(a6);
    asm volatile(DIUS_SYSTEM_CALL_INSTRUCTION
                 : "=r"(res)
                 : "r"(num), "r"(x1), "r"(x2), "r"(x3), "r"(x4), "r"(x5), "r"(x6)
                 : DIUS_SYSTEM_CALL_CLOBBER);
    if (res < 0) {
        return di::Unexpected(di::BasicError(-res));
    }
    return R(res);
}
}
