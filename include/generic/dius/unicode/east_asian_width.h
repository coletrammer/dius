// This file was generated automatically by unicode.py

#pragma once

#include "di/reflect/prelude.h"
#include "dius/unicode/property_range.h"

namespace dius::unicode {
enum class EastAsianWidth {
    Ambiguous,
    Fullwidth,
    Halfwidth,
    Neutral,
    Narrow,
    Wide,
};

constexpr auto tag_invoke(di::Tag<di::reflect>, di::InPlaceType<EastAsianWidth>) {
    using enum EastAsianWidth;
    return di::make_enumerators<"EastAsianWidth">(
        di::enumerator<"Ambiguous", Ambiguous>, di::enumerator<"Fullwidth", Fullwidth>,
        di::enumerator<"Halfwidth", Halfwidth>, di::enumerator<"Neutral", Neutral>, di::enumerator<"Narrow", Narrow>,
        di::enumerator<"Wide", Wide>);
}

namespace detail {
    auto east_asian_width_ranges() -> di::Span<PropertyRange<EastAsianWidth> const>;
}

inline auto east_asian_width =
    detail::LookupProperty<EastAsianWidth, EastAsianWidth::Neutral>(detail::east_asian_width_ranges());
}
