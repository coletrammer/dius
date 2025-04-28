#include "di/test/prelude.h"
#include "dius/print.h"
#include "dius/unicode/east_asian_width.h"
#include "dius/unicode/general_category.h"
#include "dius/unicode/name.h"
#include "dius/unicode/width.h"

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

static void code_point_width() {
    struct Case {
        c32 input { 0 };
        di::Optional<i8> expected {};
    };

    auto cases = di::Array {
        Case(U'\0', 0),                          // Null
        Case(U' ', 1),                           // Space (normal)
        Case(U'\r', {}),                         // C0 control (low)
        Case(U'\x7f', {}),                       // C0 control (high)
        Case(U'\x80', {}),                       // C1 control
        Case(0xfdd0, {}),                        // Invalid
        Case(dius::unicode::ZeroWidthJoiner, 0), // Emoji ZWJ
        Case(0x1F3F4, 2),                        // Emoji black flag
        Case(U'聲', 2),                          // East asian character
        Case(0x1f1e6, 2),                        // Emoji regional indicator
        Case(0x300, 0),                          // Non spacing mark
        Case(0x61c, 0),                          // Format general category
        Case(0x1f3fb, 2),                        // Emoji skin tone modifier (this is marked as east-asian wide...)
    };

    for (auto [input, expected] : cases) {
        auto result = dius::unicode::code_point_width(input);
        if (result != expected) {
            dius::println("FAIL: {:x} =? {}"_sv, input, expected);
        }
        ASSERT_EQ(result, expected);
    }
}

TEST(unicode, east_asian_width)
TEST(unicode, general_category)
TEST(unicode, code_point_width)
}
