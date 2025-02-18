#include "dius/system/process.h"

#include "dius/system/system_call.h"

namespace dius::system {
auto Process::spawn_and_wait() && -> di::Result<ProcessResult> {
    auto arguments_as_view = m_arguments | di::transform([](di::TransparentString const& arg) {
                                 return arg.view();
                             }) |
                             di::to<di::Vector>();

    auto tid = TRY(system_call<i32>(Number::create_task));
    TRY(system_call<i32>(Number::set_task_arguments, tid, arguments_as_view.data(), arguments_as_view.size(), nullptr,
                         0));
    TRY(system_call<i32>(Number::load_executable, tid, m_arguments[0].data(), m_arguments[0].size()));
    auto exit_code = TRY(system_call<i32>(Number::start_task_and_block, tid));

    return ProcessResult { exit_code, false };
}

auto get_process_id() -> ProcessId {
    return ProcessId(0);
}

auto mask_signal(Signal) -> di::Result<void> {
    return di::Unexpected(di::BasicError::NotSupported);
}

auto send_signal(ProcessId, Signal) -> di::Result<void> {
    return di::Unexpected(di::BasicError::NotSupported);
}

auto wait_for_signal(Signal) -> di::Result<Signal> {
    return di::Unexpected(di::BasicError::NotSupported);
}

void exit_thread() {
    (void) system_call<i32>(Number::exit_task);
    di::unreachable();
}

void exit_process(int code) {
    // FIXME: exit the entire process instead of just the current task.
    (void) system_call<i32>(Number::exit_task, code);
    di::unreachable();
}
}
