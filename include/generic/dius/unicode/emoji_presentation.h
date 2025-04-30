// This file was generated automatically by unicode.py

#pragma once

#include "di/reflect/prelude.h"
#include "dius/unicode/property_range.h"

namespace dius::unicode {
enum class EmojiPresentation {
    No,
    Yes,
};

constexpr auto tag_invoke(di::Tag<di::reflect>, di::InPlaceType<EmojiPresentation>) {
    using enum EmojiPresentation;
    return di::make_enumerators<"EmojiPresentation">(di::enumerator<"No", No>, di::enumerator<"Yes", Yes>);
}

namespace detail {
    auto emoji_presentation_ranges() -> di::Span<PropertyRange<EmojiPresentation> const>;
}

inline auto emoji_presentation =
    detail::LookupProperty<EmojiPresentation, EmojiPresentation::No>(detail::emoji_presentation_ranges());
}
