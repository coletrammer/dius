#pragma once

namespace dius::filesystem {
enum class FileType {
    // TODO: what should these be...
    None = 64,
    NotFound = 32,
    Regular = 8,
    Directory = 4,
    Symlink = 10,
    Block = 6,
    Character = 2,
    Fifo = 1,
    Socket = 12,
    Unknown = 0,
};
}
