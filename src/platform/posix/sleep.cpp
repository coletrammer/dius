#include "dius/posix/syscalls.h"
#include "dius/thread.h"

namespace dius::this_thread {
void sleep_for(di::Nanoseconds duration) {
    timespec timespec;
    timespec.tv_sec = di::duration_cast<di::Seconds>(duration).count();
    timespec.tv_nsec = duration.count() % long(di::Nanoseconds::Period::den);
    (void) syscalls::sys_clock_nanosleep(CLOCK_MONOTONIC, 0, timespec);
}

void sleep_until(SteadyClock::TimePoint time_point) {
    timespec timespec;
    timespec.tv_sec = di::duration_cast<di::Seconds>(time_point.time_since_epoch()).count();
    timespec.tv_nsec =
        di::duration_cast<di::Nanoseconds>(time_point.time_since_epoch()).count() % long(di::Nanoseconds::Period::den);
    (void) syscalls::sys_clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, timespec);
}
}
