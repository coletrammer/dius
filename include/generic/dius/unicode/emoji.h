// This file was generated automatically by unicode.py

#pragma once

#include "di/reflect/prelude.h"
#include "dius/unicode/property_range.h"

namespace dius::unicode {
enum class Emoji {
    No,
    Yes,
};

constexpr auto tag_invoke(di::Tag<di::reflect>, di::InPlaceType<Emoji>) {
    using enum Emoji;
    return di::make_enumerators<"Emoji">(di::enumerator<"No", No>, di::enumerator<"Yes", Yes>);
}

namespace detail {
    auto emoji_ranges() -> di::Span<PropertyRange<Emoji> const>;
}

inline auto emoji = detail::LookupProperty<Emoji, Emoji::No>(detail::emoji_ranges());
}
