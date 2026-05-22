#include "di/execution/algorithm/sync_wait.h"
#include "di/execution/algorithm/use_resources.h"
#include "di/execution/algorithm/when_all.h"
#include "di/execution/algorithm/with_env.h"
#include "di/execution/coroutine/lazy.h"
#include "di/test/prelude.h"
#include "dius/filesystem/operations.h"
#include "dius/io.h"
#include "dius/linux/epoll_context.h"
#include "dius/platform_process.h"
#include "dius/steady_clock.h"
#include "dius/sync_file.h"
#include "dius/system/process.h"

namespace io_context {
namespace ex = di::execution;

static void read_write() {
    auto context = *dius::linux::epoll::Context::create();
    auto sched = context.get_scheduler();

    auto [rd, wr] = *dius::open_pipe_sync(dius::OpenFlags::None);

    auto result = 0_b;
    auto expected = 1_b;

    auto task = ex::use_resources(
        [&](auto r, auto w) {
            return ex::when_all(dius::read_exactly(r, di::Span { &result, 1 }),
                                dius::write_exactly(w, di::Span { &expected, 1 }));
        },
        dius::adopt_file(sched, di::move(rd)), dius::adopt_file(sched, di::move(wr)));

    ASSERT(ex::sync_wait_on(context, di::move(task)));

    ASSERT_EQ(result, expected);
}

static void cancel() {
    auto context = *dius::linux::epoll::Context::create();
    auto sched = context.get_scheduler();

    auto [rd, wr] = *dius::open_pipe_sync(dius::OpenFlags::None);

    auto result = 0_b;

    auto task = ex::use_resources(
        [&](auto r) {
            return ex::when_all(dius::read_exactly(r, di::Span { &result, 1 }), ex::schedule_after(sched, 10_s),
                                dius::signalled(sched, dius::Signal::User1), ex::schedule(sched) | ex::let_value([] {
                                                                                 return di::stopped;
                                                                             }));
        },
        dius::adopt_file(sched, di::move(rd)));

    ASSERT_EQ(ex::sync_wait_on(context, di::move(task)), di::Unexpected(dius::PosixError::OperationCanceled));

    ASSERT_EQ(result, 0_b);
}

static void signal() {
    auto context = *dius::linux::epoll::Context::create();
    auto sched = context.get_scheduler();

    auto ran = false;
    auto task = ex::when_all(dius::signalled(sched, dius::Signal::User1) | ex::then([&] {
                                 ran = true;
                             }),
                             ex::schedule(sched) | ex::let_value([&] {
                                 return ex::schedule(sched) | ex::then([] {
                                            ASSERT(dius::system::ProcessHandle::self().signal(dius::Signal::User1));
                                        });
                             }));

    ASSERT(ex::sync_wait_on(context, di::move(task)));

    ASSERT(ran);
}

static void timed() {
    {
        auto context = *dius::linux::epoll::Context::create();
        auto sched = context.get_scheduler();

        auto start = dius::SteadyClock::now();
        auto ran_at = start;
        auto task = di::execution::schedule_at(sched, start + 10_ms) | ex::then([&] {
                        ran_at = dius::SteadyClock::now();
                    });

        ASSERT(ex::sync_wait_on(context, di::move(task)));
        ASSERT_GT_EQ(ran_at, start + 10_ms);
    }

    {
        auto context = *dius::linux::epoll::Context::create();
        auto sched = context.get_scheduler();

        auto start = dius::SteadyClock::now();
        auto ran_at = start;
        auto task = di::execution::schedule_after(sched, 10_ms) | ex::then([&] {
                        ran_at = dius::SteadyClock::now();
                    });

        ASSERT(ex::sync_wait_on(context, di::move(task)));
        ASSERT_GT_EQ(ran_at, start + 10_ms);
    }
}

static void wait() {
#ifdef __linux__
    constexpr auto N = 2u;
#else
    constexpr auto N = 1u;
#endif
    for (auto i : di::range(N)) {
        auto context = *dius::linux::epoll::Context::create();
        auto sched = context.get_scheduler();

        auto process = dius::system::Process(di::Array { "sh"_ts, "-c"_ts, "sleep 0.5 && exit 1"_ts } | di::as_rvalue |
                                             di::to<di::Vector>())
                           .spawn();
        ASSERT(process);

#ifdef __linux__
        if (i == 1) {
            process.value().internal_clear_pidfd();
        }
#endif

        auto task = ex::with_debug_env(dius::wait(sched, di::move(process).value()));
        auto expected = dius::system::ProcessResult(1, false);
        ASSERT_EQ(ex::sync_wait_on(context, di::move(task)), expected);
    }
}

static void modified() {
    auto path = "/tmp/dius_io_context_modified.txt"_pv;
    ASSERT(dius::filesystem::create_regular_file(path));
    auto _ = di::ScopeExit([&] {
        ASSERT(dius::filesystem::remove(path));
    });

    auto context = *dius::linux::epoll::Context::create();
    auto sched = context.get_scheduler();

    auto write_task = ex::use_resources(
        [&](auto w) {
            auto b = byte(0);
            return ex::schedule_after(sched, 100_ms) | ex::let_value([=] {
                       return dius::write_exactly(w, di::Span { &b, 1 });
                   });
        },
        dius::open(sched, path.to_owned(), dius::OpenMode::AppendOnly));

    auto executed = false;
    auto start = dius::SteadyClock::now();
    auto modified_task = dius::modified(sched, path.to_owned()) | ex::then([&] {
                             executed = true;
                             ASSERT_GT_EQ(dius::SteadyClock::now(), start + 100_ms);
                         });
    auto task = ex::when_all(di::move(write_task), di::move(modified_task));
    ASSERT(ex::sync_wait_on(context, di::move(task)));
    ASSERT(executed);
}

TEST(io_context, read_write)
TEST(io_context, cancel)
TEST(io_context, signal)
TEST(io_context, timed)
TEST(io_context, wait)
TEST(io_context, modified)
}
