#include "di/execution/algorithm/sync_wait.h"
#include "di/execution/algorithm/use_resources.h"
#include "di/execution/algorithm/when_all.h"
#include "di/execution/coroutine/lazy.h"
#include "di/test/prelude.h"
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

TEST(io_context, read_write)
TEST(io_context, cancel)
TEST(io_context, signal)
TEST(io_context, timed)
}
