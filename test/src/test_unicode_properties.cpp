#include "di/test/prelude.h"
#include "dius/print.h"
#include "dius/unicode/east_asian_width.h"
#include "dius/unicode/general_category.h"

namespace unicode_properties {
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
        auto result = dius::unicode::east_asian_width(input);
        ASSERT_EQ(result, expected);
    }
}

static void general_category() {
    struct Case {
        c32 input { 0 };
        GeneralCategory expected {};
    };

    auto cases = di::Array {
        Case(U'\0', GeneralCategory::Control),
        Case(U' ', GeneralCategory::SpaceSeparator),
    };

    for (auto [input, expected] : cases) {
        auto result = dius::unicode::general_category(input);
        ASSERT_EQ(result, expected);
    }
}

TEST(unicode_properties, east_asian_width)
TEST(unicode_properties, general_category)
}
