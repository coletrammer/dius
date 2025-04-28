#pragma once

#include "di/vocab/optional/prelude.h"

namespace dius::unicode {
/// @brief Return the print width a code point
///
/// @return A width value (0, 1, or 2) for printable characters. And nullopt otherwise.
///
/// This function is useful for determining the width of a string but not
/// sufficient. To determine the actual width of a string, grapheme segmentation
/// is needed.
auto code_point_width(c32 code_point) -> di::Optional<i8>;
}
