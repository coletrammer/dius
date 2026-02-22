#include "dius/posix/utils.h"

#include <errno.h>
#include <unistd.h>

namespace dius::posix {
auto get_program_name() -> char const* {
    return program_invocation_name;
}

auto get_env() -> char** {
    return environ;
}
}
