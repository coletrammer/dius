#pragma once

#include "di/container/algorithm/lower_bound.h"
#include "di/reflect/prelude.h"

namespace dius::unicode {
template<di::concepts::Enum Property>
struct PropertyRange {
    u32 start { 0 };
    u32 end { 0 };
    Property property {};

    constexpr auto contains(c32 code_point) const -> bool { return code_point >= start && code_point < end; }

    auto operator==(PropertyRange const&) const -> bool = default;
    constexpr auto operator==(c32 code_point) const -> bool { return contains(code_point); }

    auto operator<=>(PropertyRange const&) const = default;
    constexpr auto operator<=>(c32 code_point) const {
        if (contains(code_point)) {
            return di::strong_ordering::equal;
        }
        return start <=> code_point;
    }

    constexpr friend auto tag_invoke(di::Tag<di::reflect>, di::InPlaceType<PropertyRange>) {
        return di::make_fields<"Range">(di::field<"start", &PropertyRange::start>,
                                        di::field<"end", &PropertyRange::end>,
                                        di::field<"property", &PropertyRange::property>);
    }
};

namespace detail {
    template<di::concepts::Enum Property, Property fallback>
    struct LookupProperty {
        di::Span<PropertyRange<Property> const> ranges;

        constexpr auto operator()(c32 code_point) const {
            auto const* range = di::lower_bound(ranges, code_point);
            if (range == ranges.end() || !range->contains(code_point)) {
                return fallback;
            }
            return range->property;
        }
    };
}
}
