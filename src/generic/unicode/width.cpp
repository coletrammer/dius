#include "dius/unicode/width.h"

#include "dius/unicode/east_asian_width.h"
#include "dius/unicode/emoji.h"
#include "dius/unicode/general_category.h"

namespace dius::unicode {
auto code_point_width(c32 code_point) -> di::Optional<i8> {
    // Fast path for ASCII:
    if (code_point >= 0x20 && code_point < 0x7f) {
        return 1;
    }
    if (code_point == 0) {
        return 0;
    }

    auto category = general_category(code_point);

    // Control characters, surrogates, and non-codepoints are not considered valid.
    if (category == GeneralCategory::Control || category == GeneralCategory::Surrogate ||
        category == GeneralCategory::Unassigned) {
        return {};
    }

    // Marks and format characters have width 0.
    if (category_mark(category) || category == GeneralCategory::Format) {
        return 0;
    }

    // East asian width: wide and full width characters have width 2.
    switch (east_asian_width(code_point)) {
        case EastAsianWidth::Fullwidth:
        case EastAsianWidth::Wide:
            return 2;
        default:
            break;
    }

    // Emoji case: Emojis have width 2 (the emoji property includes regional indicators)
    if (emoji(code_point) == Emoji::Yes) {
        return 2;
    }

    // Base case (all other code points): return 1
    return 1;
}
}
