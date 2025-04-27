#pragma once

#include "di/parser/prelude.h"
#include "di/reflect/prelude.h"

namespace dius::unicode {
enum class EastAsianWidth {
    Ambiguous,
    Fullwidth,
    Halfwidth,
    Neutral,
    Narrow,
    Wide,
};

constexpr static auto tag_invoke(di::Tag<di::reflect>, di::InPlaceType<EastAsianWidth>) {
    using enum EastAsianWidth;
    return di::make_enumerators<"EastAsianWidth">(
        di::enumerator<"Ambiguous", Ambiguous>, di::enumerator<"Fullwidth", Fullwidth>,
        di::enumerator<"Halfwidth", Halfwidth>, di::enumerator<"Neutral", Neutral>, di::enumerator<"Narrow", Narrow>,
        di::enumerator<"Wide", Wide>);
}

struct Range {
    u32 start { 0 };
    u32 end { 0 };
    EastAsianWidth east_asian_width { EastAsianWidth::Neutral };

    constexpr auto contains(c32 code_point) const -> bool { return code_point >= start && code_point < end; }

    auto operator==(Range const&) const -> bool = default;
    constexpr auto operator==(c32 code_point) const -> bool { return contains(code_point); }

    auto operator<=>(Range const&) const = default;
    constexpr auto operator<=>(c32 code_point) const {
        if (contains(code_point)) {
            return di::strong_ordering::equal;
        }
        return start <=> code_point;
    }

    constexpr friend auto tag_invoke(di::Tag<di::reflect>, di::InPlaceType<Range>) {
        return di::make_fields<"Range">(di::field<"start", &Range::start>, di::field<"end", &Range::end>,
                                        di::field<"east_asian_width", &Range::east_asian_width>);
    }
};

auto east_asian_width_ranges() -> di::Span<Range const>;

auto lookup_east_asian_width(c32 code_point) -> EastAsianWidth;
}
