#include "di/container/algorithm/prelude.h"
#include "di/exec/elf/prelude.h"
#include "dius/system/process.h"
#include "dius/system/system_call.h"
#include "dius/thread.h"

#ifdef __linux__
#include <asm/prctl.h>
#endif

namespace dius::runtime {
extern "C" {
extern void (*__preinit_array_start[])(int, char**, char**);
extern void (*__preinit_array_end[])(int, char**, char**);
extern void (*__init_array_start[])(int, char**, char**);
extern void (*__init_array_end[])(int, char**, char**);

extern void (*__fini_array_start[])(void);
extern void (*__fini_array_end[])(void);
}

extern "C" auto main(int, char**, char**) -> int;

extern "C" di::exec::ElfHeader<> __ehdr_start;

static constinit dius::runtime::TlsInfo s_tls_info {};

auto get_tls_info() -> dius::runtime::TlsInfo {
    return s_tls_info;
}

extern "C" [[noreturn]] void dius_entry(int argc, char** argv, char** envp) {
    auto* elf_header = di::addressof(__ehdr_start);

    // FIXME: also consider the program header size.
    auto program_header_offset = elf_header->program_table_off;
    auto program_header_count = elf_header->program_entry_count;

    // NOTE: we don't need to validate the executable since the kernel already did, and the worst we can do is crash.
    auto program_headers = di::Span { reinterpret_cast<di::exec::ElfProgramHeader<> const*>(
                                          reinterpret_cast<byte const*>(elf_header) + program_header_offset),
                                      program_header_count };

    s_tls_info = [&] -> dius::runtime::TlsInfo {
        auto const* tls_segment = di::find_if(program_headers, [](auto const& header) {
            return header.type == di::exec::ElfProgramHeaderType::Tls;
        });

        if (tls_segment == program_headers.end()) {
            return { di::Span<byte const> {}, 0, 16 };
        }
        auto address = tls_segment->virtual_addr;
        auto data_size = tls_segment->file_size;
        auto size = tls_segment->memory_size;
        auto alignment = tls_segment->align;
        return { di::Span { reinterpret_cast<byte const*>(address.value()), data_size }, size, alignment };
    }();

    // Setup TLS.
    auto thread_control_block = dius::PlatformThread::create(get_tls_info());
    ASSERT(thread_control_block);

    (void) dius::system::system_call<i32>(dius::system::Number::arch_prctl, ARCH_SET_FS, thread_control_block->get());

    iptr preinit_size = __preinit_array_end - __preinit_array_start;
    for (iptr i = 0; i < preinit_size; i++) {
        (*__preinit_array_start[i])(argc, argv, envp);
    }

    iptr init_size = __init_array_end - __init_array_start;
    for (iptr i = 0; i < init_size; i++) {
        (*__init_array_start[i])(argc, argv, envp);
    }

    dius::system::exit_process(__extension__ main(argc, argv, envp));
}

extern "C" [[noreturn]] [[gnu::naked]] void _start() {
    asm volatile("xor %rbp, %rbp\n"
                 "mov (%rsp), %edi\n"
                 "lea 8(%rsp), %rsi\n"
                 "lea 16(%rsp ,%rdi ,8), %rdx\n"
                 "call dius_entry\n");
}
}
