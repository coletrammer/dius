// This file was generated automatically by unicode.py

#pragma once

#include "di/reflect/prelude.h"
#include "dius/unicode/property_range.h"

namespace dius::unicode {
enum class DefaultIgnorableCodePoint {
    No,
    Yes,
};

constexpr auto tag_invoke(di::Tag<di::reflect>, di::InPlaceType<DefaultIgnorableCodePoint>) {
    using enum DefaultIgnorableCodePoint;
    return di::make_enumerators<"DefaultIgnorableCodePoint">(di::enumerator<"No", No>, di::enumerator<"Yes", Yes>);
}

namespace detail {
    auto default_ignorable_code_point_ranges() -> di::Span<PropertyRange<DefaultIgnorableCodePoint> const>;
}

inline auto default_ignorable_code_point =
    detail::LookupProperty<DefaultIgnorableCodePoint, DefaultIgnorableCodePoint::No>(
        detail::default_ignorable_code_point_ranges());
}
