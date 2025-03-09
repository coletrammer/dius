#pragma once

#include <signal.h>
#include <sys/types.h>

namespace dius {
using ProcessId = pid_t;

enum class Signal {
    Hangup = SIGHUP,
    Interrupt = SIGINT,
    Quit = SIGQUIT,
    IllegalInstruction = SIGILL,
    Trap = SIGTRAP,
    Abort = SIGABRT,
    IOTimeout = Abort,
    Bus = SIGBUS,
    FloatingPointException = SIGFPE,
    Kill = SIGKILL,
    User1 = SIGUSR1,
    SegmentationViolation = SIGSEGV,
    User2 = SIGUSR2,
    Pipe = SIGPIPE,
    Alarm = SIGALRM,
    Terminal = SIGTERM,
    Child = SIGCHLD,
    Continue = SIGCONT,
    Stop = SIGSTOP,
    TerminalStop = SIGTSTP,
    TerminalInput = SIGTTIN,
    TerminalOutput = SIGTTOU,
    Urgent = SIGURG,
    XCPU = SIGXCPU,
    VTAlarm = SIGVTALRM,
    Profile = SIGPROF,
    WindowChange = SIGWINCH,
    IO = SIGIO,
    Poll = IO,
    System = SIGSYS,
};
}
