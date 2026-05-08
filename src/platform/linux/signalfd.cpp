#include "dius/linux/signalfd.h"

#include "dius/c_definitions.h"
#include "dius/platform_process.h"
#include "dius/sync_file.h"
#include "dius/system/system_call.h"

namespace dius::linux {
auto Signalfd::read() const -> di::Result<Signal> {
    auto info = signalfd_siginfo {};
    auto bytes = di::Span { (byte*) &info, sizeof(info) };
    TRY(this->read_exactly(bytes));
    return Signal(info.ssi_signo);
}

auto Signalfd::listen(di::Span<Signal> signals) const -> di::Result<> {
    auto sigset = kernel_sigset_t {};
    for (auto signal : signals) {
        sigset |= kernel_sigset_t(1) << (kernel_sigset_t(signal) - 1);
    }
    TRY(system::system_call<i32>(system::Number::signalfd4, file_descriptor(), &sigset, sizeof(sigset),
                                 SFD_NONBLOCK | SFD_CLOEXEC));
    return {};
}

auto create_signalfd() -> di::Result<Signalfd> {
    auto sigset = kernel_sigset_t {};
    auto fd = TRY(
        system::system_call<i32>(system::Number::signalfd4, -1, &sigset, sizeof(sigset), SFD_NONBLOCK | SFD_CLOEXEC));
    return Signalfd(Signalfd::Owned::Yes, fd);
}
}
