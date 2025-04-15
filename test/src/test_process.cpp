#include "di/test/prelude.h"
#include "dius/system/process.h"

namespace process {
static void arg_passing() {
    for (auto use_fork : di::Array { false, true }) {
        auto args = di::Array { FIXTURE_PATH "process_arg_passing_fixture"_tsv.to_owned(), "hello"_tsv.to_owned(),
                                "world"_tsv.to_owned() } |
                    di::to<di::Vector>();
        auto process = dius::system::Process(di::move(args));

        auto result =
            di::move(process).with_current_working_directory(FIXTURE_PATH ""_p).use_fork(use_fork).spawn_and_wait();
        ASSERT(result);
        ASSERT(result->exited());
        ASSERT_EQ(result->exit_code(), 0);
    }
}

TEST(process, arg_passing)
}
