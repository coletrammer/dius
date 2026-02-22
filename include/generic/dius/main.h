#pragma once

#include "di/cli/prelude.h"
#include "di/container/string/prelude.h"
#include "di/container/vector/prelude.h"
#include "di/format/prelude.h"
#include "di/meta/core.h"
#include "dius/print.h"

namespace dius::main::detail {
template<typename T>
concept HasHelp = requires(T const& value) { value->help; };
}

#define DIUS_MAIN(Type, NS)                                                                                \
    auto main(int argc, char** argv) -> int {                                                              \
        auto args = ::di::Vector<::di::TransparentStringView> {};                                          \
        for (int i = 0; i < argc; i++) {                                                                   \
            char* arg = argv[i];                                                                           \
            size_t len = 0;                                                                                \
            while (arg[len] != '\0') {                                                                     \
                len++;                                                                                     \
            }                                                                                              \
            args.push_back({ arg, len });                                                                  \
        }                                                                                                  \
                                                                                                           \
        auto as_span = args.span();                                                                        \
        auto parser = ::di::get_cli_parser<Type>();                                                        \
        auto result = parser.parse(as_span, ::dius::std_err);                                              \
        using ParserResult = decltype(result);                                                             \
        constexpr bool has_help = ::dius::main::detail::HasHelp<ParserResult>;                             \
        if (!result) {                                                                                     \
            if (result.error().success()) {                                                                \
                return 0;                                                                                  \
            }                                                                                              \
            ::dius::eprintln("{}: {}"_sv, ::di::Styled("error"_sv, di::FormatColor::Red), result.error()); \
            if constexpr (has_help) {                                                                      \
                ::dius::eprintln("\nRun with '{}' for a list of valid options"_sv,                         \
                                 ::di::Styled("--help"_sv, di::FormatColor::Cyan));                        \
            }                                                                                              \
            return 2;                                                                                      \
        }                                                                                                  \
                                                                                                           \
        using Result = decltype(NS::main(*result));                                                        \
        if constexpr (::di::concepts::Expected<Result>) {                                                  \
            auto main_result = NS::main(*result);                                                          \
            if (!main_result) {                                                                            \
                ::dius::eprintln("{}: {}"_sv, ::di::Styled("error"_sv, di::FormatColor::Red),              \
                                 main_result.error().message());                                           \
                return 1;                                                                                  \
            }                                                                                              \
        } else {                                                                                           \
            (void) NS::main(*result);                                                                      \
        }                                                                                                  \
        return 0;                                                                                          \
    }
