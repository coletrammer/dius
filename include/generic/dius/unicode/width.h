#pragma once

#include "di/container/string/string_view.h"
#include "di/vocab/optional/prelude.h"

namespace dius::unicode {
/// @brief Return the print width a code point
///
/// @return A width value (0, 1, or 2) for printable characters. And nullopt otherwise.
///
/// This function is useful for determining the width of a string but not
/// sufficient. To determine the actual width of a string, grapheme segmentation
/// is needed.
auto code_point_width(c32 code_point) -> di::Optional<u8>;

/// @brief Return the print width of an individual grapheme
///
/// @return A width value (1, or 2) for "printable" graphemes. And nullopt otherwise.
///
/// This function is useful in conjunction with segmenting a string into a list of
/// graphemes. The width of a grapheme is defined as the width of the first non-zero
/// width code point in the cluster, with some special handling for variation
/// selector 15 and 16. These code points can cause the width to change based
/// on the character immediately preceding it.
auto grapheme_cluster_width(di::StringView grapheme_cluster) -> u8;

/// @brief Return the print width of a string
///
/// @return The print width of the string.
///
/// This function returns the sum of the print width across all grapheme clusters
/// in the string.
auto text_width(di::StringView string) -> usize;
}
