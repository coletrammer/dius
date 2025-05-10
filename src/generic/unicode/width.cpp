#include "dius/unicode/width.h"

#include "dius/unicode/default_ignorable_code_point.h"
#include "dius/unicode/east_asian_width.h"
#include "dius/unicode/emoji.h"
#include "dius/unicode/emoji_presentation.h"
#include "dius/unicode/general_category.h"
#include "dius/unicode/grapheme_cluster.h"
#include "dius/unicode/name.h"
#include "dius/unicode/regional_indicator.h"

namespace dius::unicode {
auto code_point_width(c32 code_point) -> di::Optional<u8> {
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
        category == GeneralCategory::Invalid) {
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

    // Default ignorable code points have width 0. This must be checked after
    // east-asian width to not give certain characters like U+115f width 0.
    if (default_ignorable_code_point(code_point) == DefaultIgnorableCodePoint::Yes) {
        return 0;
    }

    // Emoji case: Emojis which are presented as emoji by default have width 2. Non-default
    // emojis, like '#' can become emojis with variation selectors.
    if (emoji_presentation(code_point) == EmojiPresentation::Yes) {
        return 2;
    }

    // Base case (all other code points): return 1
    return 1;
}

auto grapheme_cluster_width(di::StringView grapheme_cluster) -> u8 {
    for (auto it = grapheme_cluster.begin(); it != grapheme_cluster.end(); ++it) {
        auto code_point = *it;
        for (auto width : code_point_width(code_point)) {
            if (width == 0) {
                continue;
            }

            // Look-ahead to see if there is a variation selector.
            if (++it != grapheme_cluster.end()) {
                auto lookahead = *it;
                switch (lookahead) {
                    // Requests a text presentation of an emoji character
                    // For now, we'll ignore variation selector 15, but in the future
                    // we can enable handling of it. This will depend on the adoption
                    // by terminals.
                    // case VariationSelector_15:
                    //     if (emoji_presentation(code_point) == EmojiPresentation::Yes &&
                    //         regional_indicator(code_point) == RegionalIndicator::No) {
                    //         return 1;
                    //     }
                    //     break;
                    // Requests an emoji presentation for a text character
                    case VariationSelector_16:
                        if (emoji(code_point) == Emoji::Yes) {
                            return 2;
                        }
                        break;
                    default:
                        break;
                }
            }
            return width;
        }
    }
    return 0;
}

auto text_width(di::StringView string) -> usize {
    return grapheme_clusters(string) | di::transform(grapheme_cluster_width) |
           di::transform([](di::Optional<u8> value) {
               return usize(value.value_or(0));
           }) |
           di::sum;
}
}
