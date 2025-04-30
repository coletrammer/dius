// This file was generated automatically by unicode.py

#include "dius/unicode/regional_indicator.h"

#include "dius/unicode/property_range.h"

namespace dius::unicode {
using R = PropertyRange<RegionalIndicator>;
using enum RegionalIndicator;
constexpr static auto s_ranges = di::Array {
    R(0x1f1e6, 0x1f200, Yes),
};

namespace detail {
    auto regional_indicator_ranges() -> di::Span<PropertyRange<RegionalIndicator> const> {
        return s_ranges;
    }
}
}
