#pragma once

#include "di/assert/prelude.h"
#include "di/chrono/duration/duration_literals.h"
#include "di/function/prelude.h"
#include "di/meta/util.h"
#include "di/sync/stop_token/prelude.h"
#include "di/util/prelude.h"
#include "dius/error.h"
#include "dius/platform_thread.h"
#include "steady_clock.h"

namespace dius {
namespace this_thread {
    void sleep_for(di::Nanoseconds duration);
    void sleep_until(SteadyClock::TimePoint time_point);
}

/// @brief Class representing a single thread of execution.
///
/// This class is modeled after the C++ standard library
/// [std::jthread](https://dev.cppreference.com/cpp/thread/jthread).
class Thread {
private:
    static auto do_start(di::Function<void()>, di::Box<di::InPlaceStopSource>) -> di::Result<Thread>;

    explicit Thread(di::Box<PlatformThread, PlatformThreadDeleter> platform_thread,
                    di::Box<di::InPlaceStopSource> stop_source)
        : m_platform_thread(di::move(platform_thread)), m_stop_source(di::move(stop_source)) {}

public:
    using Id = di::ThreadId;

    template<di::concepts::MovableValue F, di::concepts::MovableValue... Args>
    requires(di::concepts::InvocableTo<F, void, Args...> ||
             di::concepts::InvocableTo<F, void, di::InPlaceStopToken, Args...>)
    static auto create(F&& function, Args&&... args) -> di::Result<Thread> {
        auto stop_source = di::make_box<di::InPlaceStopSource>();
        auto copied_function = [&] {
            if constexpr (di::concepts::InvocableTo<F, void, di::InPlaceStopToken, Args...>) {
                return di::bind_front(di::forward<F>(function), stop_source->get_stop_token(),
                                      di::forward<Args>(args)...);
            } else {
                return di::bind_front(di::forward<F>(function), di::forward<Args>(args)...);
            }
        }();
        auto erased_function = di::make_function<void()>(di::move(copied_function));
        return do_start(di::move(erased_function), di::move(stop_source));
    }

    Thread() = default;

    Thread(Thread const&) = delete;
    Thread(Thread&& other) = default;

    ~Thread() {
        if (joinable()) {
            request_stop();
            (void) join();
        }
    }

    auto operator=(Thread const&) -> Thread& = delete;
    auto operator=(Thread&& other) -> Thread& {
        if (this != &other) {
            auto temp = di::move(other);
            di::swap(*this, temp);
        }
        return *this;
    }

    [[nodiscard]] auto joinable() const -> bool { return Id() != get_id(); }
    [[nodiscard]] auto get_id() const -> Id { return m_platform_thread ? m_platform_thread->id() : Id(); }

    /// @brief Wait for the spawned thread's execution to terminate
    ///
    /// @warning It is undefined behavior to call this method concurrently from different threads.
    ///
    /// @return Returns an error if the operation failed.
    auto join() -> di::Result<void> {
        if (!m_platform_thread) {
            return di::Unexpected(PosixError::InvalidArgument);
        }
        auto guard = di::ScopeExit([&] {
            m_platform_thread.reset();
        });
        return m_platform_thread->join();
    }

    auto get_stop_source() const& -> di::InPlaceStopSource const& {
        ASSERT(m_stop_source);
        return *m_stop_source;
    }

    auto get_stop_token() const& -> di::InPlaceStopToken {
        ASSERT(m_stop_source);
        return m_stop_source->get_stop_token();
    }

    void request_stop() {
        ASSERT(m_stop_source);
        m_stop_source->request_stop();
    }

private:
    friend void tag_invoke(di::Tag<di::swap>, Thread& a, Thread& b) {
        di::swap(a.m_platform_thread, b.m_platform_thread);
        di::swap(a.m_stop_source, b.m_stop_source);
    }

    di::Box<PlatformThread, PlatformThreadDeleter> m_platform_thread;
    di::Box<di::InPlaceStopSource> m_stop_source;
};
}

namespace di::platform {
using Thread = dius::Thread;
}
