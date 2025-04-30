// This file was generated automatically by unicode.py

#pragma once

#include "di/reflect/prelude.h"
#include "dius/unicode/property_range.h"

namespace dius::unicode {
enum class RegionalIndicator {
    No,
    Yes,
};

constexpr auto tag_invoke(di::Tag<di::reflect>, di::InPlaceType<RegionalIndicator>) {
    using enum RegionalIndicator;
    return di::make_enumerators<"RegionalIndicator">(di::enumerator<"No", No>, di::enumerator<"Yes", Yes>);
}

namespace detail {
    auto regional_indicator_ranges() -> di::Span<PropertyRange<RegionalIndicator> const>;
}

inline auto regional_indicator =
    detail::LookupProperty<RegionalIndicator, RegionalIndicator::No>(detail::regional_indicator_ranges());
}
