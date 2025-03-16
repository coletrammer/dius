#include "di/container/string/encoding.h"
#include "di/math/prelude.h"
#include "di/platform/compiler.h"
#include "di/sync/scoped_lock.h"
#include "di/test/prelude.h"
#include "dius/mutex.h"
#include "dius/print.h"
#include "dius/system/process.h"

#if !defined(DIUS_USE_RUNTIME) && __has_include(<stacktrace>) && defined(DI_GCC)
#include <stacktrace>
#endif

namespace di::assert::detail {
static auto zstring_to_string_view(char const* s) -> di::StringView {
    return { di::encoding::assume_valid, reinterpret_cast<c8 const*>(s),
             di::to_unsigned(di::distance(di::ZCString(s))) };
}

static auto lock = dius::Mutex {};

void assert_fail(char const* source_text, char const* lhs_message, char const* rhs_message, util::SourceLocation loc) {
    auto _ = di::ScopedLock(lock);

    auto source_text_view = zstring_to_string_view(source_text);

    dius::eprintln("{}: {:?}"_sv, di::Styled("ASSERT"_sv, di::FormatColor::Red | di::FormatEffect::Bold),
                   source_text_view);

    dius::eprintln("{}: {}(): {}:{}:{}"_sv, di::Styled("AT"_sv, di::FormatEffect::Bold),
                   zstring_to_string_view(loc.function_name()), zstring_to_string_view(loc.file_name()), loc.line(),
                   loc.column());
    if (lhs_message) {
        auto lhs_message_view = zstring_to_string_view(lhs_message);
        dius::eprintln("{}: {}"_sv, di::Styled("LHS"_sv, di::FormatEffect::Bold), lhs_message_view);
    }
    if (rhs_message) {
        auto rhs_message_view = zstring_to_string_view(rhs_message);
        dius::eprintln("{}: {}"_sv, di::Styled("RHS"_sv, di::FormatEffect::Bold), rhs_message_view);
    }

#if !defined(DIUS_USE_RUNTIME) && __has_include(<stacktrace>) && defined(DI_GCC)
    auto backtrace = std::stacktrace::current();
    dius::eprintln("{}"_sv, zstring_to_string_view(std::to_string(backtrace).c_str()));
#endif

    auto& test_manager = di::test::TestManager::the();
    if (test_manager.is_test_application()) {
        test_manager.handle_assertion_failure();
    }

    dius::system::exit_process(42);
}
}
