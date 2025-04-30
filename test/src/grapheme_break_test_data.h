// This file was generated automatically by unicode.py

#pragma once

#include "di/format/prelude.h"
#include "di/types/prelude.h"
#include "di/vocab/array/prelude.h"
#include "di/vocab/span/prelude.h"

namespace dius::unicode {

struct GraphemeBreakTestCodePoint {
    u32 code_point { 0 };
    bool is_break { false };

    auto operator==(GraphemeBreakTestCodePoint const&) const -> bool = default;

    auto to_string() const { return *di::present("{} {:04X} "_sv, is_break ? U'÷' : U'×', code_point); }
};

namespace detail {
    using T = GraphemeBreakTestCodePoint;
    constexpr inline auto test_0 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x20, true) };
    constexpr inline auto test_1 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_2 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0xd, true) };
    constexpr inline auto test_3 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_4 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0xa, true) };
    constexpr inline auto test_5 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_6 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x1, true) };
    constexpr inline auto test_7 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_8 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x200c, false) };
    constexpr inline auto test_9 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_10 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x1f1e6, true) };
    constexpr inline auto test_11 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_12 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x600, true) };
    constexpr inline auto test_13 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_14 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0xa03, false) };
    constexpr inline auto test_15 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_16 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x1100, true) };
    constexpr inline auto test_17 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_18 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x1160, true) };
    constexpr inline auto test_19 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_20 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x11a8, true) };
    constexpr inline auto test_21 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_22 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0xac00, true) };
    constexpr inline auto test_23 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_24 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0xac01, true) };
    constexpr inline auto test_25 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_26 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x903, false) };
    constexpr inline auto test_27 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_28 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x904, true) };
    constexpr inline auto test_29 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_30 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0xd4e, true) };
    constexpr inline auto test_31 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_32 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x915, true) };
    constexpr inline auto test_33 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_34 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x231a, true) };
    constexpr inline auto test_35 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_36 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x300, false) };
    constexpr inline auto test_37 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_38 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x900, false) };
    constexpr inline auto test_39 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_40 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x94d, false) };
    constexpr inline auto test_41 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_42 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x200d, false) };
    constexpr inline auto test_43 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_44 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x20, true), T(0x378, true) };
    constexpr inline auto test_45 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_46 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x20, true) };
    constexpr inline auto test_47 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x20, true) };
    constexpr inline auto test_48 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0xd, true) };
    constexpr inline auto test_49 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0xd, true) };
    constexpr inline auto test_50 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0xa, false) };
    constexpr inline auto test_51 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0xa, true) };
    constexpr inline auto test_52 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x1, true) };
    constexpr inline auto test_53 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x1, true) };
    constexpr inline auto test_54 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x200c, true) };
    constexpr inline auto test_55 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x200c, false) };
    constexpr inline auto test_56 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x1f1e6, true) };
    constexpr inline auto test_57 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x1f1e6, true) };
    constexpr inline auto test_58 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x600, true) };
    constexpr inline auto test_59 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x600, true) };
    constexpr inline auto test_60 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0xa03, true) };
    constexpr inline auto test_61 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0xa03, false) };
    constexpr inline auto test_62 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x1100, true) };
    constexpr inline auto test_63 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x1100, true) };
    constexpr inline auto test_64 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x1160, true) };
    constexpr inline auto test_65 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x1160, true) };
    constexpr inline auto test_66 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x11a8, true) };
    constexpr inline auto test_67 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x11a8, true) };
    constexpr inline auto test_68 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0xac00, true) };
    constexpr inline auto test_69 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0xac00, true) };
    constexpr inline auto test_70 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0xac01, true) };
    constexpr inline auto test_71 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0xac01, true) };
    constexpr inline auto test_72 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x903, true) };
    constexpr inline auto test_73 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x903, false) };
    constexpr inline auto test_74 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x904, true) };
    constexpr inline auto test_75 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x904, true) };
    constexpr inline auto test_76 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0xd4e, true) };
    constexpr inline auto test_77 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0xd4e, true) };
    constexpr inline auto test_78 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x915, true) };
    constexpr inline auto test_79 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x915, true) };
    constexpr inline auto test_80 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x231a, true) };
    constexpr inline auto test_81 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x231a, true) };
    constexpr inline auto test_82 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x300, true) };
    constexpr inline auto test_83 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x300, false) };
    constexpr inline auto test_84 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x900, true) };
    constexpr inline auto test_85 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x900, false) };
    constexpr inline auto test_86 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x94d, true) };
    constexpr inline auto test_87 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x94d, false) };
    constexpr inline auto test_88 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x200d, true) };
    constexpr inline auto test_89 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x200d, false) };
    constexpr inline auto test_90 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd, true), T(0x378, true) };
    constexpr inline auto test_91 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd, true), T(0x308, true), T(0x378, true) };
    constexpr inline auto test_92 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x20, true) };
    constexpr inline auto test_93 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x20, true) };
    constexpr inline auto test_94 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0xd, true) };
    constexpr inline auto test_95 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0xd, true) };
    constexpr inline auto test_96 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0xa, true) };
    constexpr inline auto test_97 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0xa, true) };
    constexpr inline auto test_98 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x1, true) };
    constexpr inline auto test_99 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x1, true) };
    constexpr inline auto test_100 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x200c, true) };
    constexpr inline auto test_101 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x200c, false) };
    constexpr inline auto test_102 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x1f1e6, true) };
    constexpr inline auto test_103 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x1f1e6, true) };
    constexpr inline auto test_104 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x600, true) };
    constexpr inline auto test_105 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x600, true) };
    constexpr inline auto test_106 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0xa03, true) };
    constexpr inline auto test_107 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0xa03, false) };
    constexpr inline auto test_108 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x1100, true) };
    constexpr inline auto test_109 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x1100, true) };
    constexpr inline auto test_110 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x1160, true) };
    constexpr inline auto test_111 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x1160, true) };
    constexpr inline auto test_112 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x11a8, true) };
    constexpr inline auto test_113 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x11a8, true) };
    constexpr inline auto test_114 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0xac00, true) };
    constexpr inline auto test_115 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0xac00, true) };
    constexpr inline auto test_116 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0xac01, true) };
    constexpr inline auto test_117 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0xac01, true) };
    constexpr inline auto test_118 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x903, true) };
    constexpr inline auto test_119 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x903, false) };
    constexpr inline auto test_120 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x904, true) };
    constexpr inline auto test_121 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x904, true) };
    constexpr inline auto test_122 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0xd4e, true) };
    constexpr inline auto test_123 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0xd4e, true) };
    constexpr inline auto test_124 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x915, true) };
    constexpr inline auto test_125 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x915, true) };
    constexpr inline auto test_126 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x231a, true) };
    constexpr inline auto test_127 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x231a, true) };
    constexpr inline auto test_128 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x300, true) };
    constexpr inline auto test_129 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x300, false) };
    constexpr inline auto test_130 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x900, true) };
    constexpr inline auto test_131 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x900, false) };
    constexpr inline auto test_132 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x94d, true) };
    constexpr inline auto test_133 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x94d, false) };
    constexpr inline auto test_134 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x200d, true) };
    constexpr inline auto test_135 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x200d, false) };
    constexpr inline auto test_136 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa, true), T(0x378, true) };
    constexpr inline auto test_137 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa, true), T(0x308, true), T(0x378, true) };
    constexpr inline auto test_138 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x20, true) };
    constexpr inline auto test_139 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x20, true) };
    constexpr inline auto test_140 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0xd, true) };
    constexpr inline auto test_141 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0xd, true) };
    constexpr inline auto test_142 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0xa, true) };
    constexpr inline auto test_143 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0xa, true) };
    constexpr inline auto test_144 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x1, true) };
    constexpr inline auto test_145 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x1, true) };
    constexpr inline auto test_146 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x200c, true) };
    constexpr inline auto test_147 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x200c, false) };
    constexpr inline auto test_148 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x1f1e6, true) };
    constexpr inline auto test_149 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x1f1e6, true) };
    constexpr inline auto test_150 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x600, true) };
    constexpr inline auto test_151 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x600, true) };
    constexpr inline auto test_152 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0xa03, true) };
    constexpr inline auto test_153 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0xa03, false) };
    constexpr inline auto test_154 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x1100, true) };
    constexpr inline auto test_155 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x1100, true) };
    constexpr inline auto test_156 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x1160, true) };
    constexpr inline auto test_157 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x1160, true) };
    constexpr inline auto test_158 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x11a8, true) };
    constexpr inline auto test_159 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x11a8, true) };
    constexpr inline auto test_160 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0xac00, true) };
    constexpr inline auto test_161 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0xac00, true) };
    constexpr inline auto test_162 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0xac01, true) };
    constexpr inline auto test_163 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0xac01, true) };
    constexpr inline auto test_164 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x903, true) };
    constexpr inline auto test_165 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x903, false) };
    constexpr inline auto test_166 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x904, true) };
    constexpr inline auto test_167 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x904, true) };
    constexpr inline auto test_168 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0xd4e, true) };
    constexpr inline auto test_169 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0xd4e, true) };
    constexpr inline auto test_170 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x915, true) };
    constexpr inline auto test_171 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x915, true) };
    constexpr inline auto test_172 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x231a, true) };
    constexpr inline auto test_173 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x231a, true) };
    constexpr inline auto test_174 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x300, true) };
    constexpr inline auto test_175 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x300, false) };
    constexpr inline auto test_176 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x900, true) };
    constexpr inline auto test_177 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x900, false) };
    constexpr inline auto test_178 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x94d, true) };
    constexpr inline auto test_179 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x94d, false) };
    constexpr inline auto test_180 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x200d, true) };
    constexpr inline auto test_181 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x200d, false) };
    constexpr inline auto test_182 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1, true), T(0x378, true) };
    constexpr inline auto test_183 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1, true), T(0x308, true), T(0x378, true) };
    constexpr inline auto test_184 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x20, true) };
    constexpr inline auto test_185 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_186 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0xd, true) };
    constexpr inline auto test_187 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_188 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0xa, true) };
    constexpr inline auto test_189 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_190 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x1, true) };
    constexpr inline auto test_191 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_192 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x200c, false) };
    constexpr inline auto test_193 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_194 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x1f1e6, true) };
    constexpr inline auto test_195 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_196 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x600, true) };
    constexpr inline auto test_197 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_198 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0xa03, false) };
    constexpr inline auto test_199 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_200 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x1100, true) };
    constexpr inline auto test_201 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_202 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x1160, true) };
    constexpr inline auto test_203 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_204 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x11a8, true) };
    constexpr inline auto test_205 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_206 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0xac00, true) };
    constexpr inline auto test_207 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_208 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0xac01, true) };
    constexpr inline auto test_209 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_210 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x903, false) };
    constexpr inline auto test_211 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_212 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x904, true) };
    constexpr inline auto test_213 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_214 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0xd4e, true) };
    constexpr inline auto test_215 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_216 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x915, true) };
    constexpr inline auto test_217 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_218 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x231a, true) };
    constexpr inline auto test_219 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_220 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x300, false) };
    constexpr inline auto test_221 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_222 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x900, false) };
    constexpr inline auto test_223 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_224 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x94d, false) };
    constexpr inline auto test_225 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_226 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x200d, false) };
    constexpr inline auto test_227 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_228 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200c, true), T(0x378, true) };
    constexpr inline auto test_229 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200c, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_230 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x20, true) };
    constexpr inline auto test_231 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_232 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0xd, true) };
    constexpr inline auto test_233 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_234 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0xa, true) };
    constexpr inline auto test_235 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_236 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x1, true) };
    constexpr inline auto test_237 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_238 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x200c, false) };
    constexpr inline auto test_239 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_240 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x1f1e6, false) };
    constexpr inline auto test_241 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_242 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x600, true) };
    constexpr inline auto test_243 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_244 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0xa03, false) };
    constexpr inline auto test_245 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_246 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x1100, true) };
    constexpr inline auto test_247 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_248 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x1160, true) };
    constexpr inline auto test_249 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_250 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x11a8, true) };
    constexpr inline auto test_251 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_252 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0xac00, true) };
    constexpr inline auto test_253 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_254 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0xac01, true) };
    constexpr inline auto test_255 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_256 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x903, false) };
    constexpr inline auto test_257 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_258 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x904, true) };
    constexpr inline auto test_259 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_260 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0xd4e, true) };
    constexpr inline auto test_261 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_262 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x915, true) };
    constexpr inline auto test_263 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_264 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x231a, true) };
    constexpr inline auto test_265 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_266 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x300, false) };
    constexpr inline auto test_267 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_268 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x900, false) };
    constexpr inline auto test_269 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_270 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x94d, false) };
    constexpr inline auto test_271 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_272 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x200d, false) };
    constexpr inline auto test_273 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_274 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1f1e6, true), T(0x378, true) };
    constexpr inline auto test_275 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f1e6, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_276 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x20, false) };
    constexpr inline auto test_277 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_278 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0xd, true) };
    constexpr inline auto test_279 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_280 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0xa, true) };
    constexpr inline auto test_281 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_282 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x1, true) };
    constexpr inline auto test_283 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_284 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x200c, false) };
    constexpr inline auto test_285 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_286 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x1f1e6, false) };
    constexpr inline auto test_287 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_288 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x600, false) };
    constexpr inline auto test_289 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_290 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0xa03, false) };
    constexpr inline auto test_291 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_292 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x1100, false) };
    constexpr inline auto test_293 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_294 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x1160, false) };
    constexpr inline auto test_295 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_296 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x11a8, false) };
    constexpr inline auto test_297 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_298 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0xac00, false) };
    constexpr inline auto test_299 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_300 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0xac01, false) };
    constexpr inline auto test_301 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_302 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x903, false) };
    constexpr inline auto test_303 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_304 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x904, false) };
    constexpr inline auto test_305 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_306 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0xd4e, false) };
    constexpr inline auto test_307 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_308 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x915, false) };
    constexpr inline auto test_309 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_310 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x231a, false) };
    constexpr inline auto test_311 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_312 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x300, false) };
    constexpr inline auto test_313 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_314 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x900, false) };
    constexpr inline auto test_315 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_316 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x94d, false) };
    constexpr inline auto test_317 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_318 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x200d, false) };
    constexpr inline auto test_319 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_320 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x600, true), T(0x378, false) };
    constexpr inline auto test_321 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x600, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_322 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x20, true) };
    constexpr inline auto test_323 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_324 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0xd, true) };
    constexpr inline auto test_325 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_326 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0xa, true) };
    constexpr inline auto test_327 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_328 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x1, true) };
    constexpr inline auto test_329 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_330 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x200c, false) };
    constexpr inline auto test_331 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_332 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x1f1e6, true) };
    constexpr inline auto test_333 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_334 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x600, true) };
    constexpr inline auto test_335 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_336 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0xa03, false) };
    constexpr inline auto test_337 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_338 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x1100, true) };
    constexpr inline auto test_339 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_340 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x1160, true) };
    constexpr inline auto test_341 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_342 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x11a8, true) };
    constexpr inline auto test_343 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_344 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0xac00, true) };
    constexpr inline auto test_345 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_346 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0xac01, true) };
    constexpr inline auto test_347 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_348 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x903, false) };
    constexpr inline auto test_349 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_350 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x904, true) };
    constexpr inline auto test_351 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_352 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0xd4e, true) };
    constexpr inline auto test_353 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_354 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x915, true) };
    constexpr inline auto test_355 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_356 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x231a, true) };
    constexpr inline auto test_357 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_358 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x300, false) };
    constexpr inline auto test_359 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_360 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x900, false) };
    constexpr inline auto test_361 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_362 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x94d, false) };
    constexpr inline auto test_363 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_364 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x200d, false) };
    constexpr inline auto test_365 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_366 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xa03, true), T(0x378, true) };
    constexpr inline auto test_367 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xa03, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_368 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x20, true) };
    constexpr inline auto test_369 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_370 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0xd, true) };
    constexpr inline auto test_371 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_372 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0xa, true) };
    constexpr inline auto test_373 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_374 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x1, true) };
    constexpr inline auto test_375 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_376 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x200c, false) };
    constexpr inline auto test_377 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_378 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x1f1e6, true) };
    constexpr inline auto test_379 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_380 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x600, true) };
    constexpr inline auto test_381 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_382 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0xa03, false) };
    constexpr inline auto test_383 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_384 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x1100, false) };
    constexpr inline auto test_385 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_386 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x1160, false) };
    constexpr inline auto test_387 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_388 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x11a8, true) };
    constexpr inline auto test_389 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_390 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0xac00, false) };
    constexpr inline auto test_391 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_392 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0xac01, false) };
    constexpr inline auto test_393 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_394 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x903, false) };
    constexpr inline auto test_395 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_396 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x904, true) };
    constexpr inline auto test_397 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_398 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0xd4e, true) };
    constexpr inline auto test_399 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_400 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x915, true) };
    constexpr inline auto test_401 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_402 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x231a, true) };
    constexpr inline auto test_403 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_404 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x300, false) };
    constexpr inline auto test_405 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_406 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x900, false) };
    constexpr inline auto test_407 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_408 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x94d, false) };
    constexpr inline auto test_409 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_410 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x200d, false) };
    constexpr inline auto test_411 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_412 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x378, true) };
    constexpr inline auto test_413 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1100, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_414 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x20, true) };
    constexpr inline auto test_415 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_416 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0xd, true) };
    constexpr inline auto test_417 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_418 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0xa, true) };
    constexpr inline auto test_419 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_420 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x1, true) };
    constexpr inline auto test_421 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_422 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x200c, false) };
    constexpr inline auto test_423 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_424 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x1f1e6, true) };
    constexpr inline auto test_425 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_426 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x600, true) };
    constexpr inline auto test_427 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_428 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0xa03, false) };
    constexpr inline auto test_429 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_430 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x1100, true) };
    constexpr inline auto test_431 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_432 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x1160, false) };
    constexpr inline auto test_433 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_434 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x11a8, false) };
    constexpr inline auto test_435 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_436 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0xac00, true) };
    constexpr inline auto test_437 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_438 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0xac01, true) };
    constexpr inline auto test_439 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_440 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x903, false) };
    constexpr inline auto test_441 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_442 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x904, true) };
    constexpr inline auto test_443 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_444 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0xd4e, true) };
    constexpr inline auto test_445 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_446 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x915, true) };
    constexpr inline auto test_447 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_448 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x231a, true) };
    constexpr inline auto test_449 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_450 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x300, false) };
    constexpr inline auto test_451 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_452 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x900, false) };
    constexpr inline auto test_453 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_454 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x94d, false) };
    constexpr inline auto test_455 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_456 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x200d, false) };
    constexpr inline auto test_457 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_458 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1160, true), T(0x378, true) };
    constexpr inline auto test_459 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1160, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_460 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x20, true) };
    constexpr inline auto test_461 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_462 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0xd, true) };
    constexpr inline auto test_463 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_464 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0xa, true) };
    constexpr inline auto test_465 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_466 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x1, true) };
    constexpr inline auto test_467 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_468 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x200c, false) };
    constexpr inline auto test_469 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_470 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x1f1e6, true) };
    constexpr inline auto test_471 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_472 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x600, true) };
    constexpr inline auto test_473 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_474 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0xa03, false) };
    constexpr inline auto test_475 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_476 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x1100, true) };
    constexpr inline auto test_477 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_478 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x1160, true) };
    constexpr inline auto test_479 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_480 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x11a8, false) };
    constexpr inline auto test_481 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_482 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0xac00, true) };
    constexpr inline auto test_483 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_484 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0xac01, true) };
    constexpr inline auto test_485 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_486 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x903, false) };
    constexpr inline auto test_487 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_488 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x904, true) };
    constexpr inline auto test_489 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_490 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0xd4e, true) };
    constexpr inline auto test_491 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_492 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x915, true) };
    constexpr inline auto test_493 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_494 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x231a, true) };
    constexpr inline auto test_495 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_496 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x300, false) };
    constexpr inline auto test_497 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_498 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x900, false) };
    constexpr inline auto test_499 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_500 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x94d, false) };
    constexpr inline auto test_501 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_502 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x200d, false) };
    constexpr inline auto test_503 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_504 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x11a8, true), T(0x378, true) };
    constexpr inline auto test_505 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x11a8, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_506 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x20, true) };
    constexpr inline auto test_507 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_508 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0xd, true) };
    constexpr inline auto test_509 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_510 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0xa, true) };
    constexpr inline auto test_511 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_512 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x1, true) };
    constexpr inline auto test_513 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_514 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x200c, false) };
    constexpr inline auto test_515 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_516 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x1f1e6, true) };
    constexpr inline auto test_517 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_518 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x600, true) };
    constexpr inline auto test_519 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_520 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0xa03, false) };
    constexpr inline auto test_521 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_522 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x1100, true) };
    constexpr inline auto test_523 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_524 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x1160, false) };
    constexpr inline auto test_525 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_526 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x11a8, false) };
    constexpr inline auto test_527 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_528 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0xac00, true) };
    constexpr inline auto test_529 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_530 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0xac01, true) };
    constexpr inline auto test_531 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_532 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x903, false) };
    constexpr inline auto test_533 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_534 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x904, true) };
    constexpr inline auto test_535 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_536 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0xd4e, true) };
    constexpr inline auto test_537 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_538 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x915, true) };
    constexpr inline auto test_539 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_540 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x231a, true) };
    constexpr inline auto test_541 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_542 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x300, false) };
    constexpr inline auto test_543 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_544 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x900, false) };
    constexpr inline auto test_545 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_546 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x94d, false) };
    constexpr inline auto test_547 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_548 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x200d, false) };
    constexpr inline auto test_549 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_550 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac00, true), T(0x378, true) };
    constexpr inline auto test_551 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_552 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x20, true) };
    constexpr inline auto test_553 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_554 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0xd, true) };
    constexpr inline auto test_555 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_556 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0xa, true) };
    constexpr inline auto test_557 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_558 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x1, true) };
    constexpr inline auto test_559 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_560 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x200c, false) };
    constexpr inline auto test_561 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_562 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x1f1e6, true) };
    constexpr inline auto test_563 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_564 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x600, true) };
    constexpr inline auto test_565 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_566 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0xa03, false) };
    constexpr inline auto test_567 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_568 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x1100, true) };
    constexpr inline auto test_569 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_570 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x1160, true) };
    constexpr inline auto test_571 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_572 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x11a8, false) };
    constexpr inline auto test_573 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_574 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0xac00, true) };
    constexpr inline auto test_575 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_576 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0xac01, true) };
    constexpr inline auto test_577 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_578 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x903, false) };
    constexpr inline auto test_579 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_580 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x904, true) };
    constexpr inline auto test_581 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_582 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0xd4e, true) };
    constexpr inline auto test_583 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_584 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x915, true) };
    constexpr inline auto test_585 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_586 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x231a, true) };
    constexpr inline auto test_587 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_588 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x300, false) };
    constexpr inline auto test_589 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_590 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x900, false) };
    constexpr inline auto test_591 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_592 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x94d, false) };
    constexpr inline auto test_593 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_594 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x200d, false) };
    constexpr inline auto test_595 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_596 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xac01, true), T(0x378, true) };
    constexpr inline auto test_597 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_598 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x20, true) };
    constexpr inline auto test_599 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_600 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0xd, true) };
    constexpr inline auto test_601 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_602 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0xa, true) };
    constexpr inline auto test_603 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_604 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x1, true) };
    constexpr inline auto test_605 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_606 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x200c, false) };
    constexpr inline auto test_607 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_608 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x1f1e6, true) };
    constexpr inline auto test_609 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_610 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x600, true) };
    constexpr inline auto test_611 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_612 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0xa03, false) };
    constexpr inline auto test_613 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_614 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x1100, true) };
    constexpr inline auto test_615 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_616 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x1160, true) };
    constexpr inline auto test_617 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_618 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x11a8, true) };
    constexpr inline auto test_619 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_620 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0xac00, true) };
    constexpr inline auto test_621 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_622 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0xac01, true) };
    constexpr inline auto test_623 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_624 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x903, false) };
    constexpr inline auto test_625 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_626 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x904, true) };
    constexpr inline auto test_627 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_628 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0xd4e, true) };
    constexpr inline auto test_629 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_630 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x915, true) };
    constexpr inline auto test_631 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_632 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x231a, true) };
    constexpr inline auto test_633 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_634 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x300, false) };
    constexpr inline auto test_635 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_636 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x900, false) };
    constexpr inline auto test_637 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_638 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x94d, false) };
    constexpr inline auto test_639 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_640 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x200d, false) };
    constexpr inline auto test_641 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_642 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x903, true), T(0x378, true) };
    constexpr inline auto test_643 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x903, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_644 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x20, true) };
    constexpr inline auto test_645 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_646 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0xd, true) };
    constexpr inline auto test_647 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_648 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0xa, true) };
    constexpr inline auto test_649 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_650 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x1, true) };
    constexpr inline auto test_651 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_652 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x200c, false) };
    constexpr inline auto test_653 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_654 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x1f1e6, true) };
    constexpr inline auto test_655 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_656 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x600, true) };
    constexpr inline auto test_657 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_658 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0xa03, false) };
    constexpr inline auto test_659 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_660 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x1100, true) };
    constexpr inline auto test_661 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_662 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x1160, true) };
    constexpr inline auto test_663 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_664 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x11a8, true) };
    constexpr inline auto test_665 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_666 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0xac00, true) };
    constexpr inline auto test_667 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_668 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0xac01, true) };
    constexpr inline auto test_669 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_670 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x903, false) };
    constexpr inline auto test_671 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_672 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x904, true) };
    constexpr inline auto test_673 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_674 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0xd4e, true) };
    constexpr inline auto test_675 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_676 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x915, true) };
    constexpr inline auto test_677 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_678 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x231a, true) };
    constexpr inline auto test_679 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_680 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x300, false) };
    constexpr inline auto test_681 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_682 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x900, false) };
    constexpr inline auto test_683 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_684 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x94d, false) };
    constexpr inline auto test_685 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_686 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x200d, false) };
    constexpr inline auto test_687 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_688 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x904, true), T(0x378, true) };
    constexpr inline auto test_689 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x904, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_690 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x20, false) };
    constexpr inline auto test_691 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_692 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0xd, true) };
    constexpr inline auto test_693 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_694 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0xa, true) };
    constexpr inline auto test_695 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_696 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x1, true) };
    constexpr inline auto test_697 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_698 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x200c, false) };
    constexpr inline auto test_699 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_700 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x1f1e6, false) };
    constexpr inline auto test_701 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_702 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x600, false) };
    constexpr inline auto test_703 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_704 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0xa03, false) };
    constexpr inline auto test_705 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_706 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x1100, false) };
    constexpr inline auto test_707 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_708 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x1160, false) };
    constexpr inline auto test_709 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_710 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x11a8, false) };
    constexpr inline auto test_711 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_712 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0xac00, false) };
    constexpr inline auto test_713 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_714 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0xac01, false) };
    constexpr inline auto test_715 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_716 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x903, false) };
    constexpr inline auto test_717 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_718 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x904, false) };
    constexpr inline auto test_719 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_720 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0xd4e, false) };
    constexpr inline auto test_721 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_722 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x915, false) };
    constexpr inline auto test_723 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_724 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x231a, false) };
    constexpr inline auto test_725 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_726 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x300, false) };
    constexpr inline auto test_727 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_728 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x900, false) };
    constexpr inline auto test_729 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_730 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x94d, false) };
    constexpr inline auto test_731 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_732 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x200d, false) };
    constexpr inline auto test_733 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_734 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0xd4e, true), T(0x378, false) };
    constexpr inline auto test_735 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xd4e, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_736 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x20, true) };
    constexpr inline auto test_737 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_738 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0xd, true) };
    constexpr inline auto test_739 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_740 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0xa, true) };
    constexpr inline auto test_741 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_742 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x1, true) };
    constexpr inline auto test_743 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_744 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x200c, false) };
    constexpr inline auto test_745 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_746 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x1f1e6, true) };
    constexpr inline auto test_747 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_748 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x600, true) };
    constexpr inline auto test_749 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_750 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0xa03, false) };
    constexpr inline auto test_751 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_752 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x1100, true) };
    constexpr inline auto test_753 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_754 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x1160, true) };
    constexpr inline auto test_755 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_756 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x11a8, true) };
    constexpr inline auto test_757 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_758 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0xac00, true) };
    constexpr inline auto test_759 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_760 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0xac01, true) };
    constexpr inline auto test_761 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_762 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x903, false) };
    constexpr inline auto test_763 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_764 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x904, true) };
    constexpr inline auto test_765 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_766 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0xd4e, true) };
    constexpr inline auto test_767 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_768 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x915, true) };
    constexpr inline auto test_769 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_770 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x231a, true) };
    constexpr inline auto test_771 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_772 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x300, false) };
    constexpr inline auto test_773 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_774 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x900, false) };
    constexpr inline auto test_775 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_776 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x94d, false) };
    constexpr inline auto test_777 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_778 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x200d, false) };
    constexpr inline auto test_779 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_780 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x378, true) };
    constexpr inline auto test_781 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_782 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x20, true) };
    constexpr inline auto test_783 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_784 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0xd, true) };
    constexpr inline auto test_785 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_786 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0xa, true) };
    constexpr inline auto test_787 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_788 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x1, true) };
    constexpr inline auto test_789 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_790 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x200c, false) };
    constexpr inline auto test_791 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_792 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x1f1e6, true) };
    constexpr inline auto test_793 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_794 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x600, true) };
    constexpr inline auto test_795 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_796 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0xa03, false) };
    constexpr inline auto test_797 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_798 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x1100, true) };
    constexpr inline auto test_799 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_800 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x1160, true) };
    constexpr inline auto test_801 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_802 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x11a8, true) };
    constexpr inline auto test_803 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_804 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0xac00, true) };
    constexpr inline auto test_805 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_806 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0xac01, true) };
    constexpr inline auto test_807 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_808 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x903, false) };
    constexpr inline auto test_809 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_810 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x904, true) };
    constexpr inline auto test_811 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_812 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0xd4e, true) };
    constexpr inline auto test_813 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_814 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x915, true) };
    constexpr inline auto test_815 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_816 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x231a, true) };
    constexpr inline auto test_817 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_818 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x300, false) };
    constexpr inline auto test_819 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_820 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x900, false) };
    constexpr inline auto test_821 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_822 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x94d, false) };
    constexpr inline auto test_823 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_824 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x200d, false) };
    constexpr inline auto test_825 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_826 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x231a, true), T(0x378, true) };
    constexpr inline auto test_827 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x231a, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_828 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x20, true) };
    constexpr inline auto test_829 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_830 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0xd, true) };
    constexpr inline auto test_831 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_832 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0xa, true) };
    constexpr inline auto test_833 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_834 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x1, true) };
    constexpr inline auto test_835 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_836 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x200c, false) };
    constexpr inline auto test_837 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_838 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x1f1e6, true) };
    constexpr inline auto test_839 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_840 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x600, true) };
    constexpr inline auto test_841 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_842 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0xa03, false) };
    constexpr inline auto test_843 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_844 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x1100, true) };
    constexpr inline auto test_845 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_846 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x1160, true) };
    constexpr inline auto test_847 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_848 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x11a8, true) };
    constexpr inline auto test_849 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_850 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0xac00, true) };
    constexpr inline auto test_851 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_852 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0xac01, true) };
    constexpr inline auto test_853 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_854 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x903, false) };
    constexpr inline auto test_855 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_856 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x904, true) };
    constexpr inline auto test_857 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_858 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0xd4e, true) };
    constexpr inline auto test_859 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_860 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x915, true) };
    constexpr inline auto test_861 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_862 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x231a, true) };
    constexpr inline auto test_863 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_864 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x300, false) };
    constexpr inline auto test_865 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_866 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x900, false) };
    constexpr inline auto test_867 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_868 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x94d, false) };
    constexpr inline auto test_869 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_870 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x200d, false) };
    constexpr inline auto test_871 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_872 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x300, true), T(0x378, true) };
    constexpr inline auto test_873 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x300, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_874 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x20, true) };
    constexpr inline auto test_875 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_876 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0xd, true) };
    constexpr inline auto test_877 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_878 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0xa, true) };
    constexpr inline auto test_879 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_880 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x1, true) };
    constexpr inline auto test_881 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_882 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x200c, false) };
    constexpr inline auto test_883 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_884 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x1f1e6, true) };
    constexpr inline auto test_885 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_886 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x600, true) };
    constexpr inline auto test_887 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_888 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0xa03, false) };
    constexpr inline auto test_889 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_890 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x1100, true) };
    constexpr inline auto test_891 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_892 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x1160, true) };
    constexpr inline auto test_893 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_894 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x11a8, true) };
    constexpr inline auto test_895 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_896 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0xac00, true) };
    constexpr inline auto test_897 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_898 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0xac01, true) };
    constexpr inline auto test_899 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_900 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x903, false) };
    constexpr inline auto test_901 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_902 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x904, true) };
    constexpr inline auto test_903 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_904 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0xd4e, true) };
    constexpr inline auto test_905 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_906 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x915, true) };
    constexpr inline auto test_907 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_908 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x231a, true) };
    constexpr inline auto test_909 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_910 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x300, false) };
    constexpr inline auto test_911 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_912 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x900, false) };
    constexpr inline auto test_913 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_914 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x94d, false) };
    constexpr inline auto test_915 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_916 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x200d, false) };
    constexpr inline auto test_917 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_918 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x900, true), T(0x378, true) };
    constexpr inline auto test_919 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x900, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_920 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x20, true) };
    constexpr inline auto test_921 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_922 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0xd, true) };
    constexpr inline auto test_923 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_924 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0xa, true) };
    constexpr inline auto test_925 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_926 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x1, true) };
    constexpr inline auto test_927 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_928 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x200c, false) };
    constexpr inline auto test_929 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_930 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x1f1e6, true) };
    constexpr inline auto test_931 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_932 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x600, true) };
    constexpr inline auto test_933 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_934 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0xa03, false) };
    constexpr inline auto test_935 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_936 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x1100, true) };
    constexpr inline auto test_937 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_938 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x1160, true) };
    constexpr inline auto test_939 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_940 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x11a8, true) };
    constexpr inline auto test_941 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_942 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0xac00, true) };
    constexpr inline auto test_943 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_944 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0xac01, true) };
    constexpr inline auto test_945 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_946 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x903, false) };
    constexpr inline auto test_947 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_948 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x904, true) };
    constexpr inline auto test_949 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_950 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0xd4e, true) };
    constexpr inline auto test_951 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_952 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x915, true) };
    constexpr inline auto test_953 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_954 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x231a, true) };
    constexpr inline auto test_955 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_956 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x300, false) };
    constexpr inline auto test_957 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_958 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x900, false) };
    constexpr inline auto test_959 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_960 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x94d, false) };
    constexpr inline auto test_961 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_962 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x200d, false) };
    constexpr inline auto test_963 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_964 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x94d, true), T(0x378, true) };
    constexpr inline auto test_965 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x94d, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_966 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x20, true) };
    constexpr inline auto test_967 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_968 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0xd, true) };
    constexpr inline auto test_969 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_970 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0xa, true) };
    constexpr inline auto test_971 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_972 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x1, true) };
    constexpr inline auto test_973 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_974 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x200c, false) };
    constexpr inline auto test_975 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_976 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x1f1e6, true) };
    constexpr inline auto test_977 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_978 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x600, true) };
    constexpr inline auto test_979 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_980 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0xa03, false) };
    constexpr inline auto test_981 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_982 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x1100, true) };
    constexpr inline auto test_983 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_984 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x1160, true) };
    constexpr inline auto test_985 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_986 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x11a8, true) };
    constexpr inline auto test_987 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_988 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0xac00, true) };
    constexpr inline auto test_989 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_990 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0xac01, true) };
    constexpr inline auto test_991 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_992 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x903, false) };
    constexpr inline auto test_993 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_994 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x904, true) };
    constexpr inline auto test_995 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_996 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0xd4e, true) };
    constexpr inline auto test_997 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_998 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x915, true) };
    constexpr inline auto test_999 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_1000 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x231a, true) };
    constexpr inline auto test_1001 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_1002 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x300, false) };
    constexpr inline auto test_1003 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_1004 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x900, false) };
    constexpr inline auto test_1005 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_1006 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x94d, false) };
    constexpr inline auto test_1007 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_1008 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x200d, false) };
    constexpr inline auto test_1009 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_1010 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x200d, true), T(0x378, true) };
    constexpr inline auto test_1011 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x200d, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_1012 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x20, true) };
    constexpr inline auto test_1013 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x20, true) };
    constexpr inline auto test_1014 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0xd, true) };
    constexpr inline auto test_1015 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0xd, true) };
    constexpr inline auto test_1016 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0xa, true) };
    constexpr inline auto test_1017 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0xa, true) };
    constexpr inline auto test_1018 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x1, true) };
    constexpr inline auto test_1019 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x1, true) };
    constexpr inline auto test_1020 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x200c, false) };
    constexpr inline auto test_1021 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x200c, false) };
    constexpr inline auto test_1022 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x1f1e6, true) };
    constexpr inline auto test_1023 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x1f1e6, true) };
    constexpr inline auto test_1024 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x600, true) };
    constexpr inline auto test_1025 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x600, true) };
    constexpr inline auto test_1026 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0xa03, false) };
    constexpr inline auto test_1027 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0xa03, false) };
    constexpr inline auto test_1028 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x1100, true) };
    constexpr inline auto test_1029 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x1100, true) };
    constexpr inline auto test_1030 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x1160, true) };
    constexpr inline auto test_1031 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x1160, true) };
    constexpr inline auto test_1032 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x11a8, true) };
    constexpr inline auto test_1033 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x11a8, true) };
    constexpr inline auto test_1034 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0xac00, true) };
    constexpr inline auto test_1035 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0xac00, true) };
    constexpr inline auto test_1036 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0xac01, true) };
    constexpr inline auto test_1037 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0xac01, true) };
    constexpr inline auto test_1038 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x903, false) };
    constexpr inline auto test_1039 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x903, false) };
    constexpr inline auto test_1040 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x904, true) };
    constexpr inline auto test_1041 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x904, true) };
    constexpr inline auto test_1042 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0xd4e, true) };
    constexpr inline auto test_1043 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0xd4e, true) };
    constexpr inline auto test_1044 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x915, true) };
    constexpr inline auto test_1045 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x915, true) };
    constexpr inline auto test_1046 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x231a, true) };
    constexpr inline auto test_1047 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x231a, true) };
    constexpr inline auto test_1048 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x300, false) };
    constexpr inline auto test_1049 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x300, false) };
    constexpr inline auto test_1050 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x900, false) };
    constexpr inline auto test_1051 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x900, false) };
    constexpr inline auto test_1052 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x94d, false) };
    constexpr inline auto test_1053 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x94d, false) };
    constexpr inline auto test_1054 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x200d, false) };
    constexpr inline auto test_1055 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x200d, false) };
    constexpr inline auto test_1056 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x378, true), T(0x378, true) };
    constexpr inline auto test_1057 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x378, true), T(0x308, false), T(0x378, true) };
    constexpr inline auto test_1058 =
        di::Array<GraphemeBreakTestCodePoint, 5> { T(0xd, true), T(0xa, false), T(0x61, true), T(0xa, true),
                                                   T(0x308, true) };
    constexpr inline auto test_1059 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x61, true), T(0x308, false) };
    constexpr inline auto test_1060 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x20, true), T(0x200d, false), T(0x646, true) };
    constexpr inline auto test_1061 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x646, true), T(0x200d, false), T(0x20, true) };
    constexpr inline auto test_1062 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x1100, true), T(0x1100, false) };
    constexpr inline auto test_1063 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac00, true), T(0x11a8, false), T(0x1100, true) };
    constexpr inline auto test_1064 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0xac01, true), T(0x11a8, false), T(0x1100, true) };
    constexpr inline auto test_1065 = di::Array<GraphemeBreakTestCodePoint, 4> { T(0x1f1e6, true), T(0x1f1e7, false),
                                                                                 T(0x1f1e8, true), T(0x62, true) };
    constexpr inline auto test_1066 =
        di::Array<GraphemeBreakTestCodePoint, 5> { T(0x61, true), T(0x1f1e6, true), T(0x1f1e7, false), T(0x1f1e8, true),
                                                   T(0x62, true) };
    constexpr inline auto test_1067 =
        di::Array<GraphemeBreakTestCodePoint, 6> { T(0x61, true),    T(0x1f1e6, true), T(0x1f1e7, false),
                                                   T(0x200d, false), T(0x1f1e8, true), T(0x62, true) };
    constexpr inline auto test_1068 =
        di::Array<GraphemeBreakTestCodePoint, 6> { T(0x61, true),    T(0x1f1e6, true),  T(0x200d, false),
                                                   T(0x1f1e7, true), T(0x1f1e8, false), T(0x62, true) };
    constexpr inline auto test_1069 =
        di::Array<GraphemeBreakTestCodePoint, 6> { T(0x61, true),    T(0x1f1e6, true),  T(0x1f1e7, false),
                                                   T(0x1f1e8, true), T(0x1f1e9, false), T(0x62, true) };
    constexpr inline auto test_1070 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x61, true), T(0x200d, false) };
    constexpr inline auto test_1071 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x61, true), T(0x308, false), T(0x62, true) };
    constexpr inline auto test_1072 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x61, true), T(0x903, false), T(0x62, true) };
    constexpr inline auto test_1073 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x61, true), T(0x600, true), T(0x62, false) };
    constexpr inline auto test_1074 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f476, true), T(0x1f3ff, false), T(0x1f476, true) };
    constexpr inline auto test_1075 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x61, true), T(0x1f3ff, false), T(0x1f476, true) };
    constexpr inline auto test_1076 =
        di::Array<GraphemeBreakTestCodePoint, 5> { T(0x61, true), T(0x1f3ff, false), T(0x1f476, true), T(0x200d, false),
                                                   T(0x1f6d1, false) };
    constexpr inline auto test_1077 =
        di::Array<GraphemeBreakTestCodePoint, 6> { T(0x1f476, true), T(0x1f3ff, false), T(0x308, false),
                                                   T(0x200d, false), T(0x1f476, false), T(0x1f3ff, false) };
    constexpr inline auto test_1078 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x1f6d1, true), T(0x200d, false), T(0x1f6d1, false) };
    constexpr inline auto test_1079 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x61, true), T(0x200d, false), T(0x1f6d1, true) };
    constexpr inline auto test_1080 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x2701, true), T(0x200d, false), T(0x2701, false) };
    constexpr inline auto test_1081 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x61, true), T(0x200d, false), T(0x2701, true) };
    constexpr inline auto test_1082 = di::Array<GraphemeBreakTestCodePoint, 2> { T(0x915, true), T(0x924, true) };
    constexpr inline auto test_1083 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x94d, false), T(0x924, false) };
    constexpr inline auto test_1084 =
        di::Array<GraphemeBreakTestCodePoint, 4> { T(0x915, true), T(0x94d, false), T(0x94d, false), T(0x924, false) };
    constexpr inline auto test_1085 =
        di::Array<GraphemeBreakTestCodePoint, 4> { T(0x915, true), T(0x94d, false), T(0x200d, false), T(0x924, false) };
    constexpr inline auto test_1086 =
        di::Array<GraphemeBreakTestCodePoint, 5> { T(0x915, true), T(0x93c, false), T(0x200d, false), T(0x94d, false),
                                                   T(0x924, false) };
    constexpr inline auto test_1087 =
        di::Array<GraphemeBreakTestCodePoint, 5> { T(0x915, true), T(0x93c, false), T(0x94d, false), T(0x200d, false),
                                                   T(0x924, false) };
    constexpr inline auto test_1088 =
        di::Array<GraphemeBreakTestCodePoint, 5> { T(0x915, true), T(0x94d, false), T(0x924, false), T(0x94d, false),
                                                   T(0x92f, false) };
    constexpr inline auto test_1089 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x915, true), T(0x94d, false), T(0x61, true) };
    constexpr inline auto test_1090 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x61, true), T(0x94d, false), T(0x924, true) };
    constexpr inline auto test_1091 =
        di::Array<GraphemeBreakTestCodePoint, 3> { T(0x3f, true), T(0x94d, false), T(0x924, true) };
    constexpr inline auto test_1092 =
        di::Array<GraphemeBreakTestCodePoint, 4> { T(0x915, true), T(0x94d, false), T(0x94d, false), T(0x924, false) };
}

constexpr inline auto grapheme_break_test_data = di::Array<di::Span<GraphemeBreakTestCodePoint const>, 1093> {
    detail::test_0,    detail::test_1,    detail::test_2,    detail::test_3,    detail::test_4,    detail::test_5,
    detail::test_6,    detail::test_7,    detail::test_8,    detail::test_9,    detail::test_10,   detail::test_11,
    detail::test_12,   detail::test_13,   detail::test_14,   detail::test_15,   detail::test_16,   detail::test_17,
    detail::test_18,   detail::test_19,   detail::test_20,   detail::test_21,   detail::test_22,   detail::test_23,
    detail::test_24,   detail::test_25,   detail::test_26,   detail::test_27,   detail::test_28,   detail::test_29,
    detail::test_30,   detail::test_31,   detail::test_32,   detail::test_33,   detail::test_34,   detail::test_35,
    detail::test_36,   detail::test_37,   detail::test_38,   detail::test_39,   detail::test_40,   detail::test_41,
    detail::test_42,   detail::test_43,   detail::test_44,   detail::test_45,   detail::test_46,   detail::test_47,
    detail::test_48,   detail::test_49,   detail::test_50,   detail::test_51,   detail::test_52,   detail::test_53,
    detail::test_54,   detail::test_55,   detail::test_56,   detail::test_57,   detail::test_58,   detail::test_59,
    detail::test_60,   detail::test_61,   detail::test_62,   detail::test_63,   detail::test_64,   detail::test_65,
    detail::test_66,   detail::test_67,   detail::test_68,   detail::test_69,   detail::test_70,   detail::test_71,
    detail::test_72,   detail::test_73,   detail::test_74,   detail::test_75,   detail::test_76,   detail::test_77,
    detail::test_78,   detail::test_79,   detail::test_80,   detail::test_81,   detail::test_82,   detail::test_83,
    detail::test_84,   detail::test_85,   detail::test_86,   detail::test_87,   detail::test_88,   detail::test_89,
    detail::test_90,   detail::test_91,   detail::test_92,   detail::test_93,   detail::test_94,   detail::test_95,
    detail::test_96,   detail::test_97,   detail::test_98,   detail::test_99,   detail::test_100,  detail::test_101,
    detail::test_102,  detail::test_103,  detail::test_104,  detail::test_105,  detail::test_106,  detail::test_107,
    detail::test_108,  detail::test_109,  detail::test_110,  detail::test_111,  detail::test_112,  detail::test_113,
    detail::test_114,  detail::test_115,  detail::test_116,  detail::test_117,  detail::test_118,  detail::test_119,
    detail::test_120,  detail::test_121,  detail::test_122,  detail::test_123,  detail::test_124,  detail::test_125,
    detail::test_126,  detail::test_127,  detail::test_128,  detail::test_129,  detail::test_130,  detail::test_131,
    detail::test_132,  detail::test_133,  detail::test_134,  detail::test_135,  detail::test_136,  detail::test_137,
    detail::test_138,  detail::test_139,  detail::test_140,  detail::test_141,  detail::test_142,  detail::test_143,
    detail::test_144,  detail::test_145,  detail::test_146,  detail::test_147,  detail::test_148,  detail::test_149,
    detail::test_150,  detail::test_151,  detail::test_152,  detail::test_153,  detail::test_154,  detail::test_155,
    detail::test_156,  detail::test_157,  detail::test_158,  detail::test_159,  detail::test_160,  detail::test_161,
    detail::test_162,  detail::test_163,  detail::test_164,  detail::test_165,  detail::test_166,  detail::test_167,
    detail::test_168,  detail::test_169,  detail::test_170,  detail::test_171,  detail::test_172,  detail::test_173,
    detail::test_174,  detail::test_175,  detail::test_176,  detail::test_177,  detail::test_178,  detail::test_179,
    detail::test_180,  detail::test_181,  detail::test_182,  detail::test_183,  detail::test_184,  detail::test_185,
    detail::test_186,  detail::test_187,  detail::test_188,  detail::test_189,  detail::test_190,  detail::test_191,
    detail::test_192,  detail::test_193,  detail::test_194,  detail::test_195,  detail::test_196,  detail::test_197,
    detail::test_198,  detail::test_199,  detail::test_200,  detail::test_201,  detail::test_202,  detail::test_203,
    detail::test_204,  detail::test_205,  detail::test_206,  detail::test_207,  detail::test_208,  detail::test_209,
    detail::test_210,  detail::test_211,  detail::test_212,  detail::test_213,  detail::test_214,  detail::test_215,
    detail::test_216,  detail::test_217,  detail::test_218,  detail::test_219,  detail::test_220,  detail::test_221,
    detail::test_222,  detail::test_223,  detail::test_224,  detail::test_225,  detail::test_226,  detail::test_227,
    detail::test_228,  detail::test_229,  detail::test_230,  detail::test_231,  detail::test_232,  detail::test_233,
    detail::test_234,  detail::test_235,  detail::test_236,  detail::test_237,  detail::test_238,  detail::test_239,
    detail::test_240,  detail::test_241,  detail::test_242,  detail::test_243,  detail::test_244,  detail::test_245,
    detail::test_246,  detail::test_247,  detail::test_248,  detail::test_249,  detail::test_250,  detail::test_251,
    detail::test_252,  detail::test_253,  detail::test_254,  detail::test_255,  detail::test_256,  detail::test_257,
    detail::test_258,  detail::test_259,  detail::test_260,  detail::test_261,  detail::test_262,  detail::test_263,
    detail::test_264,  detail::test_265,  detail::test_266,  detail::test_267,  detail::test_268,  detail::test_269,
    detail::test_270,  detail::test_271,  detail::test_272,  detail::test_273,  detail::test_274,  detail::test_275,
    detail::test_276,  detail::test_277,  detail::test_278,  detail::test_279,  detail::test_280,  detail::test_281,
    detail::test_282,  detail::test_283,  detail::test_284,  detail::test_285,  detail::test_286,  detail::test_287,
    detail::test_288,  detail::test_289,  detail::test_290,  detail::test_291,  detail::test_292,  detail::test_293,
    detail::test_294,  detail::test_295,  detail::test_296,  detail::test_297,  detail::test_298,  detail::test_299,
    detail::test_300,  detail::test_301,  detail::test_302,  detail::test_303,  detail::test_304,  detail::test_305,
    detail::test_306,  detail::test_307,  detail::test_308,  detail::test_309,  detail::test_310,  detail::test_311,
    detail::test_312,  detail::test_313,  detail::test_314,  detail::test_315,  detail::test_316,  detail::test_317,
    detail::test_318,  detail::test_319,  detail::test_320,  detail::test_321,  detail::test_322,  detail::test_323,
    detail::test_324,  detail::test_325,  detail::test_326,  detail::test_327,  detail::test_328,  detail::test_329,
    detail::test_330,  detail::test_331,  detail::test_332,  detail::test_333,  detail::test_334,  detail::test_335,
    detail::test_336,  detail::test_337,  detail::test_338,  detail::test_339,  detail::test_340,  detail::test_341,
    detail::test_342,  detail::test_343,  detail::test_344,  detail::test_345,  detail::test_346,  detail::test_347,
    detail::test_348,  detail::test_349,  detail::test_350,  detail::test_351,  detail::test_352,  detail::test_353,
    detail::test_354,  detail::test_355,  detail::test_356,  detail::test_357,  detail::test_358,  detail::test_359,
    detail::test_360,  detail::test_361,  detail::test_362,  detail::test_363,  detail::test_364,  detail::test_365,
    detail::test_366,  detail::test_367,  detail::test_368,  detail::test_369,  detail::test_370,  detail::test_371,
    detail::test_372,  detail::test_373,  detail::test_374,  detail::test_375,  detail::test_376,  detail::test_377,
    detail::test_378,  detail::test_379,  detail::test_380,  detail::test_381,  detail::test_382,  detail::test_383,
    detail::test_384,  detail::test_385,  detail::test_386,  detail::test_387,  detail::test_388,  detail::test_389,
    detail::test_390,  detail::test_391,  detail::test_392,  detail::test_393,  detail::test_394,  detail::test_395,
    detail::test_396,  detail::test_397,  detail::test_398,  detail::test_399,  detail::test_400,  detail::test_401,
    detail::test_402,  detail::test_403,  detail::test_404,  detail::test_405,  detail::test_406,  detail::test_407,
    detail::test_408,  detail::test_409,  detail::test_410,  detail::test_411,  detail::test_412,  detail::test_413,
    detail::test_414,  detail::test_415,  detail::test_416,  detail::test_417,  detail::test_418,  detail::test_419,
    detail::test_420,  detail::test_421,  detail::test_422,  detail::test_423,  detail::test_424,  detail::test_425,
    detail::test_426,  detail::test_427,  detail::test_428,  detail::test_429,  detail::test_430,  detail::test_431,
    detail::test_432,  detail::test_433,  detail::test_434,  detail::test_435,  detail::test_436,  detail::test_437,
    detail::test_438,  detail::test_439,  detail::test_440,  detail::test_441,  detail::test_442,  detail::test_443,
    detail::test_444,  detail::test_445,  detail::test_446,  detail::test_447,  detail::test_448,  detail::test_449,
    detail::test_450,  detail::test_451,  detail::test_452,  detail::test_453,  detail::test_454,  detail::test_455,
    detail::test_456,  detail::test_457,  detail::test_458,  detail::test_459,  detail::test_460,  detail::test_461,
    detail::test_462,  detail::test_463,  detail::test_464,  detail::test_465,  detail::test_466,  detail::test_467,
    detail::test_468,  detail::test_469,  detail::test_470,  detail::test_471,  detail::test_472,  detail::test_473,
    detail::test_474,  detail::test_475,  detail::test_476,  detail::test_477,  detail::test_478,  detail::test_479,
    detail::test_480,  detail::test_481,  detail::test_482,  detail::test_483,  detail::test_484,  detail::test_485,
    detail::test_486,  detail::test_487,  detail::test_488,  detail::test_489,  detail::test_490,  detail::test_491,
    detail::test_492,  detail::test_493,  detail::test_494,  detail::test_495,  detail::test_496,  detail::test_497,
    detail::test_498,  detail::test_499,  detail::test_500,  detail::test_501,  detail::test_502,  detail::test_503,
    detail::test_504,  detail::test_505,  detail::test_506,  detail::test_507,  detail::test_508,  detail::test_509,
    detail::test_510,  detail::test_511,  detail::test_512,  detail::test_513,  detail::test_514,  detail::test_515,
    detail::test_516,  detail::test_517,  detail::test_518,  detail::test_519,  detail::test_520,  detail::test_521,
    detail::test_522,  detail::test_523,  detail::test_524,  detail::test_525,  detail::test_526,  detail::test_527,
    detail::test_528,  detail::test_529,  detail::test_530,  detail::test_531,  detail::test_532,  detail::test_533,
    detail::test_534,  detail::test_535,  detail::test_536,  detail::test_537,  detail::test_538,  detail::test_539,
    detail::test_540,  detail::test_541,  detail::test_542,  detail::test_543,  detail::test_544,  detail::test_545,
    detail::test_546,  detail::test_547,  detail::test_548,  detail::test_549,  detail::test_550,  detail::test_551,
    detail::test_552,  detail::test_553,  detail::test_554,  detail::test_555,  detail::test_556,  detail::test_557,
    detail::test_558,  detail::test_559,  detail::test_560,  detail::test_561,  detail::test_562,  detail::test_563,
    detail::test_564,  detail::test_565,  detail::test_566,  detail::test_567,  detail::test_568,  detail::test_569,
    detail::test_570,  detail::test_571,  detail::test_572,  detail::test_573,  detail::test_574,  detail::test_575,
    detail::test_576,  detail::test_577,  detail::test_578,  detail::test_579,  detail::test_580,  detail::test_581,
    detail::test_582,  detail::test_583,  detail::test_584,  detail::test_585,  detail::test_586,  detail::test_587,
    detail::test_588,  detail::test_589,  detail::test_590,  detail::test_591,  detail::test_592,  detail::test_593,
    detail::test_594,  detail::test_595,  detail::test_596,  detail::test_597,  detail::test_598,  detail::test_599,
    detail::test_600,  detail::test_601,  detail::test_602,  detail::test_603,  detail::test_604,  detail::test_605,
    detail::test_606,  detail::test_607,  detail::test_608,  detail::test_609,  detail::test_610,  detail::test_611,
    detail::test_612,  detail::test_613,  detail::test_614,  detail::test_615,  detail::test_616,  detail::test_617,
    detail::test_618,  detail::test_619,  detail::test_620,  detail::test_621,  detail::test_622,  detail::test_623,
    detail::test_624,  detail::test_625,  detail::test_626,  detail::test_627,  detail::test_628,  detail::test_629,
    detail::test_630,  detail::test_631,  detail::test_632,  detail::test_633,  detail::test_634,  detail::test_635,
    detail::test_636,  detail::test_637,  detail::test_638,  detail::test_639,  detail::test_640,  detail::test_641,
    detail::test_642,  detail::test_643,  detail::test_644,  detail::test_645,  detail::test_646,  detail::test_647,
    detail::test_648,  detail::test_649,  detail::test_650,  detail::test_651,  detail::test_652,  detail::test_653,
    detail::test_654,  detail::test_655,  detail::test_656,  detail::test_657,  detail::test_658,  detail::test_659,
    detail::test_660,  detail::test_661,  detail::test_662,  detail::test_663,  detail::test_664,  detail::test_665,
    detail::test_666,  detail::test_667,  detail::test_668,  detail::test_669,  detail::test_670,  detail::test_671,
    detail::test_672,  detail::test_673,  detail::test_674,  detail::test_675,  detail::test_676,  detail::test_677,
    detail::test_678,  detail::test_679,  detail::test_680,  detail::test_681,  detail::test_682,  detail::test_683,
    detail::test_684,  detail::test_685,  detail::test_686,  detail::test_687,  detail::test_688,  detail::test_689,
    detail::test_690,  detail::test_691,  detail::test_692,  detail::test_693,  detail::test_694,  detail::test_695,
    detail::test_696,  detail::test_697,  detail::test_698,  detail::test_699,  detail::test_700,  detail::test_701,
    detail::test_702,  detail::test_703,  detail::test_704,  detail::test_705,  detail::test_706,  detail::test_707,
    detail::test_708,  detail::test_709,  detail::test_710,  detail::test_711,  detail::test_712,  detail::test_713,
    detail::test_714,  detail::test_715,  detail::test_716,  detail::test_717,  detail::test_718,  detail::test_719,
    detail::test_720,  detail::test_721,  detail::test_722,  detail::test_723,  detail::test_724,  detail::test_725,
    detail::test_726,  detail::test_727,  detail::test_728,  detail::test_729,  detail::test_730,  detail::test_731,
    detail::test_732,  detail::test_733,  detail::test_734,  detail::test_735,  detail::test_736,  detail::test_737,
    detail::test_738,  detail::test_739,  detail::test_740,  detail::test_741,  detail::test_742,  detail::test_743,
    detail::test_744,  detail::test_745,  detail::test_746,  detail::test_747,  detail::test_748,  detail::test_749,
    detail::test_750,  detail::test_751,  detail::test_752,  detail::test_753,  detail::test_754,  detail::test_755,
    detail::test_756,  detail::test_757,  detail::test_758,  detail::test_759,  detail::test_760,  detail::test_761,
    detail::test_762,  detail::test_763,  detail::test_764,  detail::test_765,  detail::test_766,  detail::test_767,
    detail::test_768,  detail::test_769,  detail::test_770,  detail::test_771,  detail::test_772,  detail::test_773,
    detail::test_774,  detail::test_775,  detail::test_776,  detail::test_777,  detail::test_778,  detail::test_779,
    detail::test_780,  detail::test_781,  detail::test_782,  detail::test_783,  detail::test_784,  detail::test_785,
    detail::test_786,  detail::test_787,  detail::test_788,  detail::test_789,  detail::test_790,  detail::test_791,
    detail::test_792,  detail::test_793,  detail::test_794,  detail::test_795,  detail::test_796,  detail::test_797,
    detail::test_798,  detail::test_799,  detail::test_800,  detail::test_801,  detail::test_802,  detail::test_803,
    detail::test_804,  detail::test_805,  detail::test_806,  detail::test_807,  detail::test_808,  detail::test_809,
    detail::test_810,  detail::test_811,  detail::test_812,  detail::test_813,  detail::test_814,  detail::test_815,
    detail::test_816,  detail::test_817,  detail::test_818,  detail::test_819,  detail::test_820,  detail::test_821,
    detail::test_822,  detail::test_823,  detail::test_824,  detail::test_825,  detail::test_826,  detail::test_827,
    detail::test_828,  detail::test_829,  detail::test_830,  detail::test_831,  detail::test_832,  detail::test_833,
    detail::test_834,  detail::test_835,  detail::test_836,  detail::test_837,  detail::test_838,  detail::test_839,
    detail::test_840,  detail::test_841,  detail::test_842,  detail::test_843,  detail::test_844,  detail::test_845,
    detail::test_846,  detail::test_847,  detail::test_848,  detail::test_849,  detail::test_850,  detail::test_851,
    detail::test_852,  detail::test_853,  detail::test_854,  detail::test_855,  detail::test_856,  detail::test_857,
    detail::test_858,  detail::test_859,  detail::test_860,  detail::test_861,  detail::test_862,  detail::test_863,
    detail::test_864,  detail::test_865,  detail::test_866,  detail::test_867,  detail::test_868,  detail::test_869,
    detail::test_870,  detail::test_871,  detail::test_872,  detail::test_873,  detail::test_874,  detail::test_875,
    detail::test_876,  detail::test_877,  detail::test_878,  detail::test_879,  detail::test_880,  detail::test_881,
    detail::test_882,  detail::test_883,  detail::test_884,  detail::test_885,  detail::test_886,  detail::test_887,
    detail::test_888,  detail::test_889,  detail::test_890,  detail::test_891,  detail::test_892,  detail::test_893,
    detail::test_894,  detail::test_895,  detail::test_896,  detail::test_897,  detail::test_898,  detail::test_899,
    detail::test_900,  detail::test_901,  detail::test_902,  detail::test_903,  detail::test_904,  detail::test_905,
    detail::test_906,  detail::test_907,  detail::test_908,  detail::test_909,  detail::test_910,  detail::test_911,
    detail::test_912,  detail::test_913,  detail::test_914,  detail::test_915,  detail::test_916,  detail::test_917,
    detail::test_918,  detail::test_919,  detail::test_920,  detail::test_921,  detail::test_922,  detail::test_923,
    detail::test_924,  detail::test_925,  detail::test_926,  detail::test_927,  detail::test_928,  detail::test_929,
    detail::test_930,  detail::test_931,  detail::test_932,  detail::test_933,  detail::test_934,  detail::test_935,
    detail::test_936,  detail::test_937,  detail::test_938,  detail::test_939,  detail::test_940,  detail::test_941,
    detail::test_942,  detail::test_943,  detail::test_944,  detail::test_945,  detail::test_946,  detail::test_947,
    detail::test_948,  detail::test_949,  detail::test_950,  detail::test_951,  detail::test_952,  detail::test_953,
    detail::test_954,  detail::test_955,  detail::test_956,  detail::test_957,  detail::test_958,  detail::test_959,
    detail::test_960,  detail::test_961,  detail::test_962,  detail::test_963,  detail::test_964,  detail::test_965,
    detail::test_966,  detail::test_967,  detail::test_968,  detail::test_969,  detail::test_970,  detail::test_971,
    detail::test_972,  detail::test_973,  detail::test_974,  detail::test_975,  detail::test_976,  detail::test_977,
    detail::test_978,  detail::test_979,  detail::test_980,  detail::test_981,  detail::test_982,  detail::test_983,
    detail::test_984,  detail::test_985,  detail::test_986,  detail::test_987,  detail::test_988,  detail::test_989,
    detail::test_990,  detail::test_991,  detail::test_992,  detail::test_993,  detail::test_994,  detail::test_995,
    detail::test_996,  detail::test_997,  detail::test_998,  detail::test_999,  detail::test_1000, detail::test_1001,
    detail::test_1002, detail::test_1003, detail::test_1004, detail::test_1005, detail::test_1006, detail::test_1007,
    detail::test_1008, detail::test_1009, detail::test_1010, detail::test_1011, detail::test_1012, detail::test_1013,
    detail::test_1014, detail::test_1015, detail::test_1016, detail::test_1017, detail::test_1018, detail::test_1019,
    detail::test_1020, detail::test_1021, detail::test_1022, detail::test_1023, detail::test_1024, detail::test_1025,
    detail::test_1026, detail::test_1027, detail::test_1028, detail::test_1029, detail::test_1030, detail::test_1031,
    detail::test_1032, detail::test_1033, detail::test_1034, detail::test_1035, detail::test_1036, detail::test_1037,
    detail::test_1038, detail::test_1039, detail::test_1040, detail::test_1041, detail::test_1042, detail::test_1043,
    detail::test_1044, detail::test_1045, detail::test_1046, detail::test_1047, detail::test_1048, detail::test_1049,
    detail::test_1050, detail::test_1051, detail::test_1052, detail::test_1053, detail::test_1054, detail::test_1055,
    detail::test_1056, detail::test_1057, detail::test_1058, detail::test_1059, detail::test_1060, detail::test_1061,
    detail::test_1062, detail::test_1063, detail::test_1064, detail::test_1065, detail::test_1066, detail::test_1067,
    detail::test_1068, detail::test_1069, detail::test_1070, detail::test_1071, detail::test_1072, detail::test_1073,
    detail::test_1074, detail::test_1075, detail::test_1076, detail::test_1077, detail::test_1078, detail::test_1079,
    detail::test_1080, detail::test_1081, detail::test_1082, detail::test_1083, detail::test_1084, detail::test_1085,
    detail::test_1086, detail::test_1087, detail::test_1088, detail::test_1089, detail::test_1090, detail::test_1091,
    detail::test_1092,
};
}
