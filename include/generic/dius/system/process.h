#pragma once

#include "di/assert/prelude.h"
#include "di/container/path/path.h"
#include "di/container/string/prelude.h"
#include "di/container/tree/tree_map.h"
#include "di/container/vector/prelude.h"
#include "di/util/prelude.h"
#include "dius/error.h"
#include "dius/platform_process.h"
#include "dius/sync_file.h"
#include "dius/tty.h"

namespace dius::system {
class ProcessResult {
public:
    explicit ProcessResult(int exit_code_or_signal, bool signaled)
        : m_exit_code_or_signal(exit_code_or_signal), m_signaled(signaled) {}

    auto signaled() const -> bool { return m_signaled; }
    auto exited() const -> bool { return !m_signaled; }

    auto exit_code() const -> int {
        ASSERT(exited());
        return m_exit_code_or_signal;
    }

    auto signal() const -> int {
        ASSERT(signaled());
        return m_exit_code_or_signal;
    }

private:
    int m_exit_code_or_signal { 0 };
    bool m_signaled { false };
};

class ProcessHandle {
public:
    static auto self() -> ProcessHandle;

    ProcessHandle() = default;
    constexpr explicit ProcessHandle(ProcessId id) : m_id(id) {}

    constexpr auto id() const -> ProcessId { return m_id; }

    auto wait() -> di::Result<ProcessResult>;

    auto signal(Signal signal) -> di::Result<>;

private:
    ProcessId m_id { -1 };
};

class Process {
    struct FileAction {
        enum class Type {
            Open,
            Dup,
            Close,
        };

        Type type { Type::Dup };
        i32 arg0 = 0;
        i32 arg1 = 0;
        i32 arg2 = 0;
        di::Path path;
    };

public:
    explicit Process(di::Vector<di::TransparentString> arguments) : m_arguments(di::move(arguments)) {}

    auto with_file_open(i32 fd, di::Path path, OpenMode open_mode, u16 create_mode = 0666) && -> Process {
        m_file_actions.push_back(
            { FileAction::Type::Open, fd, static_cast<i32>(open_mode), i32(create_mode), di::move(path) });
        return di::move(*this);
    }

    auto with_file_close(i32 fd) && -> Process {
        m_file_actions.push_back({ FileAction::Type::Close, fd, 0, 0, {} });
        return di::move(*this);
    }

    auto with_file_dup(i32 old_fd, i32 new_fd) && -> Process {
        m_file_actions.push_back({ FileAction::Type::Dup, old_fd, new_fd, 0, {} });
        return di::move(*this);
    }

    auto with_tty_window_size(int fd, tty::WindowSize const& size) && -> Process {
        m_tty_window_size = { fd, size };
        return di::move(*this).use_fork();
    }

    auto with_controlling_tty(int fd) && -> Process {
        m_controlling_tty = fd;
        return di::move(*this).use_fork();
    }

    auto with_new_session() && -> Process {
        m_new_session = true;
        return di::move(*this);
    }

    auto with_env(di::TransparentString key, di::TransparentString value) && -> Process {
        m_extra_env_vars.insert_or_assign(di::move(key), di::move(value));
        return di::move(*this);
    }

    /// @brief Attempt to spawn the process with this directory, but continue on failure.
    ///
    /// This is useful when the working directory is best effort (user provided, but may
    /// not exist).
    auto with_optional_current_working_directory(di::Path path) && -> Process {
        m_current_working_directory = di::move(path);
        m_require_current_working_directory = false;
        return di::move(*this);
    }

    /// @brief Spawn the process with the provided working directory.
    auto with_current_working_directory(di::Path path) && -> Process {
        m_current_working_directory = di::move(path);
        m_require_current_working_directory = true;
        return di::move(*this);
    }

    auto use_fork(bool b = true) && -> Process {
        m_use_fork = b;
        return di::move(*this);
    }

    auto spawn() && -> di::Result<ProcessHandle>;

    auto spawn_and_wait() && -> di::Result<ProcessResult> {
        auto handle = TRY(di::move(*this).spawn());
        return handle.wait();
    }

private:
    auto spawn_with_fork() && -> di::Result<ProcessHandle>;
    auto spawn_with_posix_spawn() && -> di::Result<ProcessHandle>;

    di::Vector<di::TransparentString> m_arguments;
    di::Vector<FileAction> m_file_actions;
    di::Optional<di::Path> m_current_working_directory;
    bool m_require_current_working_directory { false };
    di::TreeMap<di::TransparentString, di::TransparentString> m_extra_env_vars;
    di::Optional<di::Tuple<i32, tty::WindowSize>> m_tty_window_size;
    di::Optional<i32> m_controlling_tty;
    bool m_new_session { false };
    bool m_use_fork { false };
};

void install_dummy_signal_handler(Signal signal);
auto mask_signal(Signal signal) -> di::Result<void>;
auto wait_for_signal(Signal signal) -> di::Result<Signal>;

/// @brief Get the executed program name (argv[0])
auto get_program_name() -> di::PathView;

/// @brief Get the environment variables, as a read-only map
auto get_environment() -> di::TreeMap<di::TransparentString, di::TransparentString> const&;

/// @brief Get the hostname of the current system
auto get_hostname() -> di::Result<di::TransparentString>;

/// @brief Exit the currently executing thread.
///
/// @warning It is undefined behavior to call this function when there exists RAII stack-allocated variables
[[noreturn]] void exit_thread();

[[noreturn]] void exit_process(int status_code);
}
