// This file was generated automatically by unicode.py

#pragma once

#include "di/reflect/prelude.h"
#include "dius/unicode/property_range.h"

namespace dius::unicode {
enum class ExtendedPictographic {
    No,
    Yes,
};

constexpr auto tag_invoke(di::InPlaceType<ExtendedPictographic>) {
    using enum ExtendedPictographic;
    return di::make_enumerators<"ExtendedPictographic">(di::enumerator<"No", No>, di::enumerator<"Yes", Yes>);
}

namespace detail {
    auto extended_pictographic_ranges() -> di::Span<PropertyRange<ExtendedPictographic> const>;
}

inline auto extended_pictographic =
    detail::LookupProperty<ExtendedPictographic, ExtendedPictographic::No>(detail::extended_pictographic_ranges());
}
