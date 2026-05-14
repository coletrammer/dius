#include "di/test/prelude.h"
#include "dius/system/process.h"

namespace process {
static void arg_passing() {
#ifdef __linux__
    constexpr auto N = 2u;
#else
    constexpr auto N = 1u;
#endif
    for (auto i : di::range(N)) {
        for (auto use_fork : di::Array { false, true }) {
            auto args = di::Array { FIXTURE_PATH "process_arg_passing_fixture"_tsv.to_owned(), "hello"_tsv.to_owned(),
                                    "world"_tsv.to_owned() } |
                        di::to<di::Vector>();
            auto process = dius::system::Process(di::move(args));

            auto handle =
                di::move(process).with_current_working_directory(FIXTURE_PATH ""_p).use_fork(use_fork).spawn();
            ASSERT(handle);
#ifdef __linux__
            if (i == 1) {
                handle.value().internal_clear_pidfd();
            }
#endif
            auto result = handle->sync_wait();
            ASSERT(result);
            ASSERT(result->exited());
            ASSERT_EQ(result->exit_code(), 0);
        }
    }
}

static void hostname() {
    auto rv = dius::system::get_hostname();
    ASSERT(rv);
    ASSERT(!rv.value().empty());
}

static void env() {
    auto program_name = dius::system::get_program_name();
    ASSERT(program_name.ends_with("dius_test"_pv));

    auto const& environ = dius::system::get_environment();
    ASSERT(environ.contains("PATH"_tsv));
}

TEST(process, arg_passing)
TEST(process, hostname)
TEST(process, env)
}
