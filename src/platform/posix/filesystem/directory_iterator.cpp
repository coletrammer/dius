#include "dius/filesystem/directory_iterator.h"

#include "di/assert/prelude.h"
#include "di/math/prelude.h"
#include "dius/c_definitions.h"
#include "dius/filesystem/prelude.h"

namespace dius::filesystem {
void detail::DirDeleter::operator()(DIR* dir) {
    if (dir) {
        ::closedir(dir);
    }
}

auto DirectoryIterator::create(di::Path path, DirectoryOptions options)
    -> di::Expected<DirectoryIterator, di::GenericCode> {
    // FIXME: handle the directory options.
    (void) options;
    auto* dir = ::opendir(path.c_str());
    if (!dir) {
        return di::Unexpected(di::BasicError(errno));
    }

    auto result = DirectoryIterator(di::move(path), detail::Dir(dir));
    ++result;

    return result;
}

void DirectoryIterator::advance_one() {
    // If the result is an actual error object, simply advance to the end.
    if (!m_current && m_current != di::Unexpected(PosixError::Success)) {
        m_at_end = true;
        return;
    }

    for (;;) {
        advance();

        if (m_at_end || !m_current) {
            break;
        }

        if (m_current->path_view().filename() == "."_tsv || m_current->path_view().filename() == ".."_tsv) {
            continue;
        }
        break;
    }
}

void DirectoryIterator::advance() {
    ASSERT(m_dir);

    errno = 0;
    auto* dirent = ::readdir(m_dir.get());
    if (!dirent && errno == 0) {
        // EOF case.
        m_at_end = true;
        return;
    }
    if (!dirent) {
        // Error case.
        m_current = di::Unexpected(di::BasicError(errno));
        return;
    }

    auto type = FileType(dirent->d_type);
    auto path = di::clone(m_path);
    auto name = di::ZCString(dirent->d_name);
    path.append(di::TransparentStringView { name.data(), di::to_unsigned(di::distance(name)) });
    m_current.emplace(DirectoryEntry(di::move(path), type));
}
}
