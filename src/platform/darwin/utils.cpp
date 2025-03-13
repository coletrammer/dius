#include "dius/posix/utils.h"

#include <crt_externs.h>

namespace dius::posix {
static auto s_envp = static_cast<char**>(nullptr);

[[gnu::constructor]] static void get_env_on_init() {
    s_envp = *_NSGetEnviron();
}

auto get_env() -> char** {
    return s_envp;
}
}
