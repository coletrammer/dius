#include "dius/sync_file.h"

#include "di/assert/prelude.h"
#include "di/container/algorithm/prelude.h"
#include "di/function/prelude.h"
#include "dius/posix/open_mode_flags.h"
#include "dius/posix/syscalls.h"

namespace dius {
auto SyncFile::close() -> di::Expected<void, di::GenericCode> {
    auto owned = di::exchange(m_owned, Owned::No);
    auto fd = di::exchange(m_fd, -1);

    if (owned == Owned::Yes && fd != -1) {
        return syscalls::sys_close(fd);
    }
    return {};
}

auto SyncFile::read_some(di::Span<byte> data) const -> di::Expected<usize, di::GenericCode> {
    return syscalls::sys_read(m_fd, data);
}

auto SyncFile::read_some(u64 offset, di::Span<byte> data) const -> di::Expected<usize, di::GenericCode> {
    return syscalls::sys_pread(m_fd, offset, data);
}

auto SyncFile::write_some(di::Span<byte const> data) const -> di::Expected<usize, di::GenericCode> {
    return syscalls::sys_write(m_fd, data);
}

auto SyncFile::write_some(u64 offset, di::Span<byte const> data) const -> di::Expected<usize, di::GenericCode> {
    return syscalls::sys_pwrite(m_fd, offset, data);
}

auto SyncFile::resize_file(u64 new_size) const -> di::Expected<void, di::GenericCode> {
    return syscalls::sys_ftruncate(file_descriptor(), new_size);
}

auto SyncFile::map(u64 offset, usize size, Protection protection, MapFlags flags) const
    -> di::Expected<MemoryRegion, di::GenericCode> {
    auto* base = TRY(syscalls::sys_mmap(nullptr, size, int(protection), int(flags), m_fd, offset));
    return MemoryRegion(di::Span { base, size });
}

auto SyncFile::set_tty_window_size(tty::WindowSize size) -> di::Expected<void, di::GenericCode> {
    ::winsize ws {};
    ws.ws_row = size.rows;
    ws.ws_col = size.cols;
    ws.ws_xpixel = size.pixel_width;
    ws.ws_ypixel = size.pixel_height;
    return syscalls::sys_ioctl(file_descriptor(), TIOCSWINSZ, &ws);
}

auto SyncFile::get_tty_window_size() -> di::Expected<tty::WindowSize, di::GenericCode> {
    ::winsize ws {};
    TRY(syscalls::sys_ioctl(file_descriptor(), TIOCGWINSZ, &ws));
    return tty::WindowSize { ws.ws_row, ws.ws_col, ws.ws_xpixel, ws.ws_ypixel };
}

auto SyncFile::get_psuedo_terminal_path() -> di::Expected<di::Path, di::GenericCode> {
    return syscalls::sys_ptsname(file_descriptor());
}

auto SyncFile::enter_raw_mode() -> di::Expected<RawModeToken, di::GenericCode> {
    auto original = TRY(syscalls::sys_tcgetattr(file_descriptor()));
    auto with_raw_mode = original;

    with_raw_mode.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    with_raw_mode.c_oflag &= ~(OPOST);
    with_raw_mode.c_cflag |= (CS8);
    with_raw_mode.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    TRY(syscalls::sys_tcsetattr(file_descriptor(), with_raw_mode));

    return RawModeToken(di::make_function<void()>([fd = file_descriptor(), original] {
        (void) syscalls::sys_tcsetattr(fd, original);
    }));
}

auto open_sync(di::PathView path, OpenMode open_mode, u16 create_mode) -> di::Expected<SyncFile, di::GenericCode> {
    auto flags = detail::open_mode_flags(open_mode);
    auto fd = TRY(syscalls::sys_open(path, flags, create_mode));
    return SyncFile { SyncFile::Owned::Yes, fd };
}

auto open_psuedo_terminal_controller(OpenMode open_mode, tty::WindowSize size)
    -> di::Expected<SyncFile, di::GenericCode> {
    auto flags = detail::open_mode_flags(open_mode);
    auto fd = TRY(syscalls::sys_open("/dev/ptmx"_pv, flags, 0));
    auto result = SyncFile { SyncFile::Owned::Yes, fd };

    // Set window size, and call grantpt() + unlockpt().
    TRY(syscalls::sys_grantpt(result.file_descriptor()));
    TRY(syscalls::sys_unlockpt(result.file_descriptor()));
    TRY(result.set_tty_window_size(size));

    return result;
}
}
