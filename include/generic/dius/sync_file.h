#pragma once

#include "di/container/path/path.h"
#include "di/function/container/function.h"
#include "di/util/prelude.h"
#include "di/util/scope_exit.h"
#include "dius/c_definitions.h"
#include "dius/error.h"
#include "dius/memory_region.h"
#include "dius/tty.h"

namespace dius {
#ifdef PROT_NONE
enum class Protection : int {
    None = PROT_NONE,
    Executable = PROT_EXEC,
    Readable = PROT_READ,
    Writeable = PROT_WRITE,
};

DI_DEFINE_ENUM_BITWISE_OPERATIONS(Protection)

enum class MapFlags : int {
    None = 0,
    Shared = MAP_SHARED,
    Private = MAP_PRIVATE,
    Fixed = MAP_FIXED,
    Anonymous = MAP_ANONYMOUS,
#ifdef MAP_POPULATE
    Stack = MAP_STACK,
#endif
#ifdef MAP_POPULATE
    Populate = MAP_POPULATE,
#endif
};

DI_DEFINE_ENUM_BITWISE_OPERATIONS(MapFlags)
#endif

class SyncFile {
public:
    enum class Owned { Yes, No };

    constexpr SyncFile() = default;

    constexpr explicit SyncFile(Owned owned, int fd) : m_owned(owned), m_fd(fd) {}

    constexpr SyncFile(SyncFile&& other)
        : m_owned(di::exchange(other.m_owned, Owned::No)), m_fd(di::exchange(other.m_fd, -1)) {}

    constexpr ~SyncFile() {
        if (m_owned == Owned::No) {
            return;
        }
        (void) this->close();
    }

    auto operator=(SyncFile&& other) -> SyncFile& {
        (void) this->close();
        m_owned = di::exchange(other.m_owned, Owned::No);
        m_fd = di::exchange(other.m_fd, -1);
        return *this;
    }

    constexpr auto valid() const -> bool { return m_fd != -1; }
    constexpr explicit operator bool() const { return valid(); }

    constexpr auto file_descriptor() const -> int { return m_fd; }
    constexpr auto leak_file_descriptor() -> int {
        m_owned = Owned::No;
        return m_fd;
    }

    auto close() -> di::Expected<void, di::GenericCode>;

    auto read_some(u64 offset, di::Span<di::Byte>) const -> di::Expected<size_t, di::GenericCode>;
    auto read_some(di::Span<di::Byte>) const -> di::Expected<size_t, di::GenericCode>;
    auto write_some(u64 offset, di::Span<di::Byte const>) const -> di::Expected<size_t, di::GenericCode>;
    auto write_some(di::Span<di::Byte const>) const -> di::Expected<size_t, di::GenericCode>;

    auto read_exactly(u64 offset, di::Span<di::Byte>) const -> di::Expected<void, di::GenericCode>;
    auto read_exactly(di::Span<di::Byte>) const -> di::Expected<void, di::GenericCode>;
    auto write_exactly(u64 offset, di::Span<di::Byte const>) const -> di::Expected<void, di::GenericCode>;
    auto write_exactly(di::Span<di::Byte const>) const -> di::Expected<void, di::GenericCode>;

    auto resize_file(u64 new_size) const -> di::Expected<void, di::GenericCode>;

#ifdef PROT_NONE
    auto map(u64 offset, size_t size, Protection protection, MapFlags flags) const
        -> di::Expected<MemoryRegion, di::GenericCode>;
#endif

    auto flush() const -> di::Expected<void, di::GenericCode> { return {}; }

    auto interactive_device() const -> bool { return true; }

    auto set_tty_window_size(tty::WindowSize size) -> di::Expected<void, di::GenericCode>;
    auto get_tty_window_size() -> di::Expected<tty::WindowSize, di::GenericCode>;
    auto get_psuedo_terminal_path() -> di::Expected<di::Path, di::GenericCode>;

    using RawModeToken = di::ScopeExit<di::Function<void()>>;
    auto enter_raw_mode() -> di::Expected<RawModeToken, di::GenericCode>;

    auto get_termios_restorer() -> di::Expected<di::Function<void()>, di::GenericCode>;

private:
    Owned m_owned { Owned::No };
    int m_fd { -1 };
};

enum class OpenMode { Readonly, WriteNew, WriteClobber, ReadWrite, AppendOnly, ReadWriteClobber, AppendReadWrite };

enum class OpenFlags {
    None = 0,
    NoControllingTerminal = 1,
    KeepAfterExec = 2,
};

DI_DEFINE_ENUM_BITWISE_OPERATIONS(OpenFlags)

auto open_sync(di::PathView path, OpenMode open_mode, u16 create_mode = 0666, OpenFlags flags = OpenFlags::None)
    -> di::Expected<SyncFile, di::GenericCode>;

/// @brief Open a pipe
///
/// @param flags The open flags allow specifying that the pipes should not be closed when executing a new process, and
/// as such, are necessary for communicating with a sub-process.
///
/// @return A Expected<Tuple>, where the first file is the read end of the pipe and the second file is
/// the write end of the pipe.
auto open_pipe(OpenFlags flags) -> di::Expected<di::Tuple<SyncFile, SyncFile>, di::GenericCode>;

auto open_psuedo_terminal_controller(OpenMode open_mode) -> di::Expected<SyncFile, di::GenericCode>;
auto open_tempory_file() -> di::Expected<SyncFile, di::GenericCode>;
auto read_to_string(di::PathView path) -> di::Result<di::String>;

inline auto stdin = SyncFile { SyncFile::Owned::No, 0 };
inline auto stdout = SyncFile { SyncFile::Owned::No, 1 };
inline auto stderr = SyncFile { SyncFile::Owned::No, 2 };
}
