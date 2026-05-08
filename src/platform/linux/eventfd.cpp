#include "dius/linux/eventfd.h"

#include "dius/sync_file.h"
#include "dius/system/system_call.h"

namespace dius::linux {
auto Eventfd::read() const -> di::Result<u64> {
    auto bytes = di::Array<byte, sizeof(u64)> {};
    TRY(read_exactly(bytes.span()));
    return di::bit_cast<u64>(bytes);
}

auto Eventfd::write(u64 value) const -> di::Result<> {
    auto bytes = di::bit_cast<di::Array<byte, sizeof(u64)>>(value);
    return write_exactly(bytes.span());
}

auto create_eventfd(u64 initial_value) -> di::Result<Eventfd> {
    auto fd = TRY(system::system_call<i32>(system::Number::eventfd2, initial_value, EFD_CLOEXEC | EFD_NONBLOCK));
    return Eventfd(Eventfd::Owned::Yes, fd);
}
}
