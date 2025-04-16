#include "dius/posix/utils.h"

#include <crt_externs.h>

namespace dius::posix {
static auto s_envp = static_cast<char**>(nullptr);
static auto s_program_name = static_cast<char const*>(nullptr);

[[gnu::constructor]] static void get_env_on_init() {
    s_envp = *_NSGetEnviron();
    s_program_name = *_NSGetProgname();
}

auto get_program_name() -> char const* {
    return s_program_name;
}

auto get_env() -> char** {
    return s_envp;
}
}
