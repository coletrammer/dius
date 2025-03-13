#include "dius/posix/utils.h"

namespace dius::posix {
static auto s_envp = static_cast<char**>(nullptr);

[[gnu::constructor]] static void get_env_on_init(int, char**, char** envp) {
    // This works according to the SYS-V ABI. Other platforms may provide a custom
    // implementation to fetch the environment on startup.
    s_envp = envp;
}

auto get_env() -> char** {
    return s_envp;
}
}
