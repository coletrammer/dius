#include "dius/posix/syscalls.h"
#include "dius/system/process.h"

namespace dius::system {
auto get_hostname() -> di::Result<di::TransparentString> {
    auto utsname = TRY(syscalls::sys_uname());

    return di::ZCString(utsname.nodename) | di::to<di::Vector<char>>() | di::to<di::TransparentString>();
}
}
