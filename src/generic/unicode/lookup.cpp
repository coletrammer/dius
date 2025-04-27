#include "di/container/algorithm/lower_bound.h"
#include "dius/unicode/unicode.h"

namespace dius::unicode {
auto lookup_east_asian_width(c32 code_point) -> EastAsianWidth {
    auto const ranges = east_asian_width_ranges();
    auto const* range = di::lower_bound(ranges, code_point);
    if (range == ranges.end() || !range->contains(code_point)) {
        return EastAsianWidth::Neutral;
    }
    return range->east_asian_width;
}
}
