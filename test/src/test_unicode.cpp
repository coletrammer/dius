#include "di/test/prelude.h"
#include "dius/unicode/unicode.h"

namespace unicode {
using namespace dius::unicode;

static void east_asian_width() {
    struct Case {
        c32 input { 0 };
        EastAsianWidth expected {};
    };

    auto cases = di::Array {
        Case(U'\0', EastAsianWidth::Neutral),    Case(U' ', EastAsianWidth::Narrow),
        Case(U'¡', EastAsianWidth::Ambiguous),   Case(0xFF63, EastAsianWidth::Halfwidth),
        Case(0xFF5F, EastAsianWidth::Fullwidth), Case(0x323B0, EastAsianWidth::Wide),
    };

    for (auto [input, expected] : cases) {
        auto result = lookup_east_asian_width(input);
        ASSERT_EQ(result, expected);
    }
}

TEST(unicode, east_asian_width)
}
