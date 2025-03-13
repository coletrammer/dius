#include "dius/posix/open_mode_flags.h"
#include "dius/posix/syscalls.h"
#include "dius/posix/utils.h"
#include "dius/system/process.h"

namespace dius::system {
auto Process::spawn_with_fork() && -> di::Result<ProcessHandle> {
    // NOTE: TransparentString objects are guaranteed to be null-terminated on Linux.
    auto null_terminated_args =
        di::concat(m_arguments | di::transform(di::cdata), di::single(nullptr)) | di::to<di::Vector>();
    auto [_, env] = posix::make_env(posix::get_env(), m_extra_env_vars);

    auto pid = TRY(syscalls::sys_fork());

    // Child
    if (pid == 0) {
        // Any failures will cause the child process to exit with status 127.
        (void) ([&] -> di::Result<> {
            if (m_new_session) {
                TRY(syscalls::sys_setsid());
            }

            for (auto const& action : m_file_actions) {
                switch (action.type) {
                    case FileAction::Type::Open: {
                        // Always try to close the destination file descriptor.
                        (void) syscalls::sys_close(action.arg0);

                        auto flags =
                            detail::open_mode_flags(static_cast<OpenMode>(action.arg1), OpenFlags::KeepAfterExec);
                        auto fd = TRY(syscalls::sys_open(action.path, flags, action.arg2));
                        if (fd != action.arg0) {
                            TRY(syscalls::sys_dup2(fd, action.arg0));
                            TRY(syscalls::sys_close(fd));
                        }
                        break;
                    }
                    case FileAction::Type::Close: {
                        TRY(syscalls::sys_close(action.arg0));
                        break;
                    }
                    case FileAction::Type::Dup: {
                        TRY(syscalls::sys_dup2(action.arg0, action.arg1));
                        break;
                    }
                }
            }

            // No handle tty actions.
            if (m_controlling_tty) {
                TRY(syscalls::sys_ioctl(m_controlling_tty.value(), TIOCSCTTY, 0));
            }
            if (m_tty_window_size) {
                auto [fd, size] = m_tty_window_size.value();
                auto file = SyncFile(SyncFile::Owned::No, fd);
                TRY(file.set_tty_window_size(size));
            }

            if (m_arguments[0].contains(U'/')) {
                (void) syscalls::sys_execve(null_terminated_args[0], const_cast<char**>(null_terminated_args.data()),
                                            env.data());
            } else {
                // Read PATH env variable, and use it.
                auto path = "/bin:/usr/bin"_tsv;
                for (auto const* const* env_var = env.data(); *env_var != nullptr; env_var++) {
                    auto zstring = di::ZCString(*env_var);
                    if (di::starts_with(zstring, "PATH="_tsv)) {
                        auto begin = di::next(zstring.begin(), 5);
                        auto end = di::next(zstring.begin(), zstring.end());
                        path = { &*begin, &*end };
                        break;
                    }
                }

                // Instead of a normal String object, use a stack allocated one via StaticVector. This prevents heap
                // allocations.
                using StackPath = di::container::string::StringImpl<di::TransparentString::Encoding,
                                                                    di::StaticVector<char, di::Constexpr<4097>>>;
                auto absolute_program = StackPath();
                for (auto prefix : path | di::split(':')) {
                    absolute_program.clear();
                    if (!absolute_program.append(prefix)) {
                        continue;
                    }
                    if (!absolute_program.ends_with('/')) {
                        if (!absolute_program.push_back('/')) {
                            continue;
                        }
                    }
                    if (!absolute_program.append(m_arguments[0])) {
                        continue;
                    }
                    (void) syscalls::sys_execve(absolute_program.c_str(),
                                                const_cast<char**>(null_terminated_args.data()), env.data());
                }
            }
            return {};
        }());
        exit_process(127);
    }

    return ProcessHandle(pid);
}
}
