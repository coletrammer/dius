#include <spawn.h>

#include "dius/filesystem/directory_iterator.h"
#include "dius/posix/open_mode_flags.h"
#include "dius/posix/syscalls.h"
#include "dius/posix/utils.h"
#include "dius/system/process.h"

namespace dius::system {
auto Process::spawn_with_posix_spawn() && -> di::Result<ProcessHandle> {
    // NOTE: TransparentString objects are guaranteed to be null-terminated on Linux.
    auto null_terminated_args =
        di::concat(m_arguments | di::transform(di::cdata), di::single(nullptr)) | di::to<di::Vector>();

    auto file_actions = posix_spawn_file_actions_t {};
    posix_spawn_file_actions_init(&file_actions);
    auto file_action_cleanup = di::ScopeExit([&] {
        posix_spawn_file_actions_destroy(&file_actions);
    });

    // Current working directory
    auto working_directory = di::Optional<filesystem::DirectoryIterator> {};
    for (auto& path : m_current_working_directory) {
        auto result = filesystem::DirectoryIterator::create(di::move(path));
        if (m_require_current_working_directory && !result) {
            return di::Unexpected(di::move(result).error());
        }
        if (result) {
            // Even though this is marked as "non-portable", I think pretty much every system supports it.
            // Posix also standardized it as seen here:
            // https://pubs.opengroup.org/onlinepubs/9799919799/functions/posix_spawn_file_actions_addchdir.html
            // If there was such a system which didn't support this, we'd want to fallback to the fork
            // implementation.
            auto fd = result.value().file_descriptor();
            posix_spawn_file_actions_addfchdir_np(&file_actions, fd);
            posix_spawn_file_actions_addclose(&file_actions, fd);

            // Save the working directory in the outer scope so we don't close the file until after running spawn.
            working_directory = di::move(result).value();
        }
    }

    for (auto const& action : m_file_actions) {
        switch (action.type) {
            case FileAction::Type::Open:
                posix_spawn_file_actions_addopen(
                    &file_actions, action.arg0, action.path.c_str(),
                    detail::open_mode_flags(static_cast<OpenMode>(action.arg1), OpenFlags::KeepAfterExec), action.arg2);
                break;
            case FileAction::Type::Close:
                posix_spawn_file_actions_addclose(&file_actions, action.arg0);
                break;
            case FileAction::Type::Dup:
                posix_spawn_file_actions_adddup2(&file_actions, action.arg0, action.arg1);
                break;
            default:
                return di::Unexpected(di::BasicError::InvalidArgument);
        }
    }

    auto attrs = posix_spawnattr_t {};
    posix_spawnattr_init(&attrs);
    auto attrs_guard = di::ScopeExit([&] {
        posix_spawnattr_destroy(&attrs);
    });
    auto attr_flags = short(m_new_session ? POSIX_SPAWN_SETSID : 0);
    posix_spawnattr_setflags(&attrs, attr_flags);

    auto pid = pid_t(-1);
    auto [_, env] = posix::make_env(posix::get_env(), m_extra_env_vars);
    auto result = posix_spawnp(&pid, null_terminated_args[0], &file_actions, &attrs,
                               const_cast<char**>(null_terminated_args.data()), env.data());
    if (result != 0) {
        return di::Unexpected(di::BasicError(result));
    }
    return ProcessHandle(pid);
}
}
