#include "dius/posix/utils.h"

namespace dius::posix {
static auto s_envp = static_cast<char**>(nullptr);
static auto s_program_name = static_cast<char const*>(nullptr);

[[gnu::constructor]] static void get_env_on_init(int, char** argv, char** envp) {
    // This works according to the SYS-V ABI. Other platforms may provide a custom
    // implementation to fetch the environment on startup.
    s_envp = envp;
    s_program_name = argv[0];
}

auto get_program_name() -> char const* {
    return s_program_name;
}

auto get_env() -> char** {
    return s_envp;
}
}
