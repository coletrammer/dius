#include "di/test/prelude.h"
#include "dius/print.h"
#include "dius/unicode/grapheme_cluster_break.h"
#include "dius/unicode/name.h"
#include "dius/unicode/width.h"

namespace unicode_width {
using namespace dius::unicode;

static void code_point_width() {
    struct Case {
        c32 input { 0 };
        di::Optional<u8> expected {};
    };

    auto cases = di::Array {
        Case(U'\0', 0),                               // Null
        Case(U' ', 1),                                // Space (normal)
        Case(U'\r', {}),                              // C0 control (low)
        Case(U'\x7f', {}),                            // C0 control (high)
        Case(U'\x80', {}),                            // C1 control
        Case(0xfdd0, {}),                             // Invalid
        Case(U'®', 1),                                // "Emoji" but only when using variation selector
        Case(dius::unicode::ZeroWidthJoiner, 0),      // Emoji ZWJ
        Case(dius::unicode::VariationSelector_15, 0), // Variation selector 15
        Case(dius::unicode::VariationSelector_16, 0), // Variation selector 16
        Case(0x1F3F4, 2),                             // Emoji black flag
        Case(U'聲', 2),                               // East asian character
        Case(0x1f1e6, 2),                             // Emoji regional indicator
        Case(0x300, 0),                               // Non spacing mark
        Case(0x61c, 0),                               // Format general category
        Case(0x1f3fb, 2),                             // Emoji skin tone modifier (this is marked as east-asian wide...)
        Case(U'͸', 1),                               // Unassigned but valid character defaults to width 1
        Case(U'\u1160', 0),                           // Default ignorable code points have width 0, even if not a mark
    };

    for (auto [input, expected] : cases) {
        auto result = dius::unicode::code_point_width(input);
        if (result != expected) {
            dius::println("FAIL: {:x} =? {}"_sv, input, expected);
        }
        ASSERT_EQ(result, expected);
    }
}

static void grapheme_cluster_width() {
    struct Case {
        di::StringView input {};
        u8 expected {};
    };

    auto cases = di::Array {
        Case(""_sv, 0), Case("a"_sv, 1), Case("#"_sv, 1),

        Case(u8"#️"_sv, 2), // # with Variation Selector 16 has width 2
        // Case(u8"🐈︎"_sv, 1),        // Emoji with text presentation has width 1
        Case(u8"\xd8\x80j"_sv, 1), // Text with leading 0 width characters works
    };

    for (auto [input, expected] : cases) {
        auto result = dius::unicode::grapheme_cluster_width(input);
        if (result != expected) {
            dius::println("FAIL: {:?} =? {}"_sv, input, expected);
        }
        ASSERT_EQ(result, expected);
    }
}

static void text_width() {
    struct Case {
        di::StringView input {};
        u8 expected {};
    };

    auto cases = di::Array {
        Case(""_sv, 0), Case("abcd"_sv, 4),

        Case(u8"👩🏿‍🔧🇦🇴"_sv, 4), // Complex emoji + flag
    };

    for (auto [input, expected] : cases) {
        auto result = dius::unicode::text_width(input);
        if (result != expected) {
            dius::println("FAIL: {:?} =? {}"_sv, input, expected);
        }
        ASSERT_EQ(result, expected);
    }
}

TEST(unicode_width, code_point_width)
TEST(unicode_width, grapheme_cluster_width)
TEST(unicode_width, text_width)
}
