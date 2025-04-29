// This file was generated automatically by unicode.py

#pragma once

#include "di/reflect/prelude.h"
#include "dius/unicode/property_range.h"

namespace dius::unicode {
enum class GeneralCategory {
    Control,
    Format,
    Unassigned,
    PrivateUse,
    Surrogate,
    CasedLetter,
    LowercaseLetter,
    ModifierLetter,
    OtherLetter,
    TitlecaseLetter,
    UppercaseLetter,
    SpacingMark,
    EnclosingMark,
    NonspacingMark,
    DecimalNumber,
    LetterNumber,
    OtherNumber,
    ConnectorPunctuation,
    DashPunctuation,
    ClosePunctuation,
    FinalPunctuation,
    InitialPunctuation,
    OtherPunctuation,
    OpenPunctuation,
    CurrencySymbol,
    ModifierSymbol,
    MathSymbol,
    OtherSymbol,
    LineSeparator,
    ParagraphSeparator,
    SpaceSeparator,
};

constexpr auto tag_invoke(di::Tag<di::reflect>, di::InPlaceType<GeneralCategory>) {
    using enum GeneralCategory;
    return di::make_enumerators<"GeneralCategory">(
        di::enumerator<"Control", Control>, di::enumerator<"Format", Format>, di::enumerator<"Unassigned", Unassigned>,
        di::enumerator<"PrivateUse", PrivateUse>, di::enumerator<"Surrogate", Surrogate>,
        di::enumerator<"CasedLetter", CasedLetter>, di::enumerator<"LowercaseLetter", LowercaseLetter>,
        di::enumerator<"ModifierLetter", ModifierLetter>, di::enumerator<"OtherLetter", OtherLetter>,
        di::enumerator<"TitlecaseLetter", TitlecaseLetter>, di::enumerator<"UppercaseLetter", UppercaseLetter>,
        di::enumerator<"SpacingMark", SpacingMark>, di::enumerator<"EnclosingMark", EnclosingMark>,
        di::enumerator<"NonspacingMark", NonspacingMark>, di::enumerator<"DecimalNumber", DecimalNumber>,
        di::enumerator<"LetterNumber", LetterNumber>, di::enumerator<"OtherNumber", OtherNumber>,
        di::enumerator<"ConnectorPunctuation", ConnectorPunctuation>,
        di::enumerator<"DashPunctuation", DashPunctuation>, di::enumerator<"ClosePunctuation", ClosePunctuation>,
        di::enumerator<"FinalPunctuation", FinalPunctuation>, di::enumerator<"InitialPunctuation", InitialPunctuation>,
        di::enumerator<"OtherPunctuation", OtherPunctuation>, di::enumerator<"OpenPunctuation", OpenPunctuation>,
        di::enumerator<"CurrencySymbol", CurrencySymbol>, di::enumerator<"ModifierSymbol", ModifierSymbol>,
        di::enumerator<"MathSymbol", MathSymbol>, di::enumerator<"OtherSymbol", OtherSymbol>,
        di::enumerator<"LineSeparator", LineSeparator>, di::enumerator<"ParagraphSeparator", ParagraphSeparator>,
        di::enumerator<"SpaceSeparator", SpaceSeparator>);
}

constexpr auto category_other(GeneralCategory category) -> bool {
    using enum GeneralCategory;
    return category == OtherLetter || category == OtherNumber || category == OtherPunctuation ||
           category == OtherSymbol;
}

constexpr auto category_letter(GeneralCategory category) -> bool {
    using enum GeneralCategory;
    return category == CasedLetter || category == LowercaseLetter || category == ModifierLetter ||
           category == OtherLetter || category == TitlecaseLetter || category == UppercaseLetter ||
           category == LetterNumber;
}

constexpr auto category_mark(GeneralCategory category) -> bool {
    using enum GeneralCategory;
    return category == SpacingMark || category == EnclosingMark || category == NonspacingMark;
}

constexpr auto category_number(GeneralCategory category) -> bool {
    using enum GeneralCategory;
    return category == DecimalNumber || category == LetterNumber || category == OtherNumber;
}

constexpr auto category_punctuation(GeneralCategory category) -> bool {
    using enum GeneralCategory;
    return category == ConnectorPunctuation || category == DashPunctuation || category == ClosePunctuation ||
           category == FinalPunctuation || category == InitialPunctuation || category == OtherPunctuation ||
           category == OpenPunctuation;
}

constexpr auto category_symbol(GeneralCategory category) -> bool {
    using enum GeneralCategory;
    return category == CurrencySymbol || category == ModifierSymbol || category == MathSymbol ||
           category == OtherSymbol;
}

constexpr auto category_separator(GeneralCategory category) -> bool {
    using enum GeneralCategory;
    return category == LineSeparator || category == ParagraphSeparator || category == SpaceSeparator;
}

namespace detail {
    auto general_category_ranges() -> di::Span<PropertyRange<GeneralCategory> const>;
}

inline auto general_category =
    detail::LookupProperty<GeneralCategory, GeneralCategory::Unassigned>(detail::general_category_ranges());
}
