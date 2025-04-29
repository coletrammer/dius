// This file was generated automatically by unicode.py

#pragma once

#include "di/reflect/prelude.h"
#include "dius/unicode/property_range.h"

namespace dius::unicode {
enum class GraphemeClusterBreak {
    Control,
    CR,
    Extend,
    L,
    LF,
    LV,
    LVT,
    Prepend,
    RegionalIndicator,
    SpacingMark,
    T,
    V,
    Other,
    ZWJ,
    Other_ExtendedPictographic,
    Extend_IndicConjunctBreak_Extend,
    Extend_IndicConjunctBreak_Linker,
    Other_IndicConjunctBreak_Consonant,
};

constexpr auto tag_invoke(di::InPlaceType<GraphemeClusterBreak>) {
    using enum GraphemeClusterBreak;
    return di::make_enumerators<"GraphemeClusterBreak">(
        di::enumerator<"Control", Control>, di::enumerator<"CR", CR>, di::enumerator<"Extend", Extend>,
        di::enumerator<"L", L>, di::enumerator<"LF", LF>, di::enumerator<"LV", LV>, di::enumerator<"LVT", LVT>,
        di::enumerator<"Prepend", Prepend>, di::enumerator<"RegionalIndicator", RegionalIndicator>,
        di::enumerator<"SpacingMark", SpacingMark>, di::enumerator<"T", T>, di::enumerator<"V", V>,
        di::enumerator<"Other", Other>, di::enumerator<"ZWJ", ZWJ>,
        di::enumerator<"Other_ExtendedPictographic", Other_ExtendedPictographic>,
        di::enumerator<"Extend_IndicConjunctBreak_Extend", Extend_IndicConjunctBreak_Extend>,
        di::enumerator<"Extend_IndicConjunctBreak_Linker", Extend_IndicConjunctBreak_Linker>,
        di::enumerator<"Other_IndicConjunctBreak_Consonant", Other_IndicConjunctBreak_Consonant>);
}

namespace detail {
    auto grapheme_cluster_break_ranges() -> di::Span<PropertyRange<GraphemeClusterBreak> const>;
}

inline auto grapheme_cluster_break =
    detail::LookupProperty<GraphemeClusterBreak, GraphemeClusterBreak::Other>(detail::grapheme_cluster_break_ranges());
}
