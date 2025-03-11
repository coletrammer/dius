#include "dius/posix/syscalls.h"
#include "dius/steady_clock.h"
#include "dius/thread.h"

namespace dius::this_thread {
void sleep_for(di::Nanoseconds duration) {
    timespec timespec;
    timespec.tv_sec = di::duration_cast<di::Seconds>(duration).count();
    timespec.tv_nsec = duration.count() % long(di::Nanoseconds::Period::den);
    (void) ::nanosleep(&timespec, nullptr);
}

void sleep_until(SteadyClock::TimePoint time_point) {
    sleep_for(SteadyClock::now() - time_point);
}
}
