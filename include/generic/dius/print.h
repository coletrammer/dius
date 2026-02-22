#pragma once

#include "di/format/prelude.h"
#include "di/io/prelude.h"
#include "dius/sync_file.h"

namespace dius {
namespace detail {
    struct PrintFunction {
        template<typename... Args>
        static void operator()(di::fmt::FormatStringImpl<di::container::string::Utf8Encoding, Args...> format_string,
                               Args&&... args) {
            (void) di::writer_print<di::container::string::Utf8Encoding>(dius::std_out, format_string,
                                                                         di::forward<Args>(args)...);
        }
    };

    struct PrintlnFunction {
        template<typename... Args>
        static void operator()(di::fmt::FormatStringImpl<di::container::string::Utf8Encoding, Args...> format_string,
                               Args&&... args) {
            (void) di::writer_println<di::container::string::Utf8Encoding>(dius::std_out, format_string,
                                                                           di::forward<Args>(args)...);
        }
    };

    struct EPrintFunction {
        template<typename... Args>
        static void operator()(di::fmt::FormatStringImpl<di::container::string::Utf8Encoding, Args...> format_string,
                               Args&&... args) {
            (void) di::writer_print<di::container::string::Utf8Encoding>(dius::std_err, format_string,
                                                                         di::forward<Args>(args)...);
        }
    };

    struct EPrintlnFunction {
        template<typename... Args>
        static void operator()(di::fmt::FormatStringImpl<di::container::string::Utf8Encoding, Args...> format_string,
                               Args&&... args) {
            (void) di::writer_println<di::container::string::Utf8Encoding>(dius::std_err, format_string,
                                                                           di::forward<Args>(args)...);
        }
    };
}

constexpr inline auto print = detail::PrintFunction {};
constexpr inline auto eprint = detail::PrintFunction {};

constexpr inline auto println = detail::PrintlnFunction {};
constexpr inline auto eprintln = detail::EPrintlnFunction {};
}
