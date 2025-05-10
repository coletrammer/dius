// This file was generated automatically by unicode.py

#include "dius/unicode/default_ignorable_code_point.h"

#include "dius/unicode/property_range.h"

namespace dius::unicode {
using R = PropertyRange<DefaultIgnorableCodePoint>;
using enum DefaultIgnorableCodePoint;
constexpr static auto s_ranges = di::Array {
    R(0xad, 0xae, Yes),       R(0x34f, 0x350, Yes),   R(0x61c, 0x61d, Yes),     R(0x115f, 0x1161, Yes),
    R(0x17b4, 0x17b6, Yes),   R(0x180b, 0x1810, Yes), R(0x200b, 0x2010, Yes),   R(0x202a, 0x202f, Yes),
    R(0x2060, 0x2070, Yes),   R(0x3164, 0x3165, Yes), R(0xfe00, 0xfe10, Yes),   R(0xfeff, 0xff00, Yes),
    R(0xffa0, 0xffa1, Yes),   R(0xfff0, 0xfff9, Yes), R(0x1bca0, 0x1bca4, Yes), R(0x1d173, 0x1d17b, Yes),
    R(0xe0000, 0xe1000, Yes),
};

namespace detail {
    auto default_ignorable_code_point_ranges() -> di::Span<PropertyRange<DefaultIgnorableCodePoint> const> {
        return s_ranges;
    }
}
}
