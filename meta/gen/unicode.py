#!/usr/bin/env python

import argparse
import bisect
import copy
import os
import re
import subprocess
from collections import defaultdict
from dataclasses import dataclass, field
from typing import Dict, List, Self, Tuple

parser = argparse.ArgumentParser(
    description="Generates C++ source files from the Unicode Database for the dius library",
)
parser.add_argument("-i", "--input", default=os.getenv("DIUS_UNICODE_DATABASE_DIR"))
parser.add_argument("-o", "--output", default="./")

PROPERTY_ALIASES_INPUT = "PropertyAliases.txt"
PROPERTY_VALUE_ALIASES_INPUT = "PropertyValueAliases.txt"


@dataclass
class CodePointRange:
    start: int
    end: int  # exclusive

    @classmethod
    def from_code_points(cls, input: str) -> Self:
        input = input.strip()
        if ".." in input:
            l, r = input.split("..")
            return cls(int(l, 16), int(r, 16) + 1)
        a = int(input, 16)
        return cls(a, a + 1)

    def contains(self, c: int) -> bool:
        return c >= self.start and c < self.end


@dataclass
class UnicodePropertyRange:
    sequence: List[CodePointRange]
    property: str

    def range(self) -> CodePointRange:
        return self.sequence[0]


@dataclass
class UnicodeProperty:
    name: str
    input_file: str

    # Default value for the property
    fallback: str = ""

    # Property has no values and is a simple yes/no
    boolean: bool = False

    # Property file defines multiple properties
    multi_file: bool = False

    # Short name found via PropertyAlias.txt
    short_name: str = ""

    # Mapping from short value aliases to long aliases
    values_map: Dict[str, str] = field(default_factory=lambda: {})

    # Property table derived from parsing the UCD
    values_table: List[UnicodePropertyRange] = field(default_factory=lambda: [])

    def cpp_enum_name(self) -> str:
        return self.name.title().replace("_", "")

    def cpp_file_name(self) -> str:
        return self.name.lower()

    def lookup_value(self, short: str) -> str:
        if short not in self.values_map:
            return short.replace("_", "")
        return self.values_map[short]

    def values(self) -> List[str]:
        return list(self.values_map.values())

    def lookup_code_point(self, code_point: int) -> str:
        res = self.fallback
        i = bisect.bisect_left(
            self.values_table,
            code_point,
            key=lambda x: x.range().end - 1,
        )
        if i < len(self.values_table) and self.values_table[i].range().contains(
            code_point
        ):
            res = self.values_table[i].property
        return res


GENERAL_CATEGORY = UnicodeProperty(
    "General_Category", "extracted/DerivedGeneralCategory.txt", "Unassigned"
)
GRAPHEME_CLUSTER_BREAK = UnicodeProperty(
    "Grapheme_Cluster_Break", "auxiliary/GraphemeBreakProperty.txt", "Other"
)
EXTENDED_PICTOGRAPHIC = UnicodeProperty(
    "Extended_Pictographic", "emoji/emoji-data.txt", "No", True
)

INDIC_CONJUNCT_BREAK = UnicodeProperty(
    "Indic_Conjunct_Break", "DerivedCoreProperties.txt", "None", False, True
)

UNICODE_PROPERTIES = [
    GENERAL_CATEGORY,
    EXTENDED_PICTOGRAPHIC,
    INDIC_CONJUNCT_BREAK,
    GRAPHEME_CLUSTER_BREAK,
    UnicodeProperty("East_Asian_Width", "EastAsianWidth.txt", "Neutral"),
    UnicodeProperty("Emoji", "emoji/emoji-data.txt", "No", True),
    UnicodeProperty("Name", "extracted/DerivedName.txt"),
]


def combine_properties(
    properties: List[UnicodePropertyRange],
) -> List[UnicodePropertyRange]:
    result: List[UnicodePropertyRange] = []
    prev = None
    for property in properties:
        if (
            prev is not None
            and prev.sequence[1:] == property.sequence[1:]
            and prev.sequence[0].end == property.sequence[0].start
            and prev.property == property.property
        ):
            result[-1].sequence[0].end = property.sequence[0].end
            continue

        result.append(copy.deepcopy(property))
        prev = result[-1]
    return result


def parse_property_aliases(path: str) -> Dict[str, str]:
    result = {}
    with open(path, "r") as file:
        for line in file.readlines():
            line = re.sub(re.compile("#.*"), "", line.strip())
            if line == "":
                continue

            short, long = line.split(";")[:2]
            result[long.strip()] = short.strip()
    return result


def parse_property_value_aliases(path: str) -> Dict[str, Dict[str, str]]:
    result = defaultdict(lambda: {})
    with open(path, "r") as file:
        for line in file.readlines():
            line = re.sub(re.compile("#.*"), "", line.strip())
            if line == "":
                continue

            prop, short, long = line.split(";")[:3]
            result[prop.strip()][short.strip()] = long.strip().replace("_", "")
    return result


def parse_grapheme_break_test(path: str) -> List[List[Tuple[int, bool]]]:
    result = []
    with open(path, "r") as file:
        for line in file.readlines():
            res = []
            line = re.sub(re.compile("#.*"), "", line.strip())
            if line == "":
                continue

            is_break = False
            for item in line.replace("\t", "").split(" "):
                if item == "÷":
                    is_break = True
                elif item == "×":
                    is_break = False
                else:
                    c = int(item, 16)
                    res.append((c, is_break))
            result.append(res)

    return result


def parse_property_file(path: str, prop: UnicodeProperty) -> List[UnicodePropertyRange]:
    result = []
    with open(path, "r") as file:
        for line in file.readlines():
            line = re.sub(re.compile("#.*"), "", line.strip())
            if line == "":
                continue

            sequence, property = line.split(";")[:2]
            sequence = [
                CodePointRange.from_code_points(x) for x in sequence.strip().split(" ")
            ]
            if prop.boolean:
                if property.strip() == prop.name:
                    result.append(UnicodePropertyRange(sequence, "Yes"))
            elif prop.multi_file:
                if property.strip() == prop.name or property.strip() == prop.short_name:
                    value = line.split(";")[2]
                    result.append(
                        UnicodePropertyRange(sequence, prop.lookup_value(value.strip()))
                    )
            elif prop.name == "Name":
                result.append(
                    UnicodePropertyRange(
                        sequence,
                        property.strip().title().replace(" ", "").replace("-", "_"),
                    )
                )
            else:
                result.append(
                    UnicodePropertyRange(sequence, prop.lookup_value(property.strip()))
                )
    return result


def gen_grapheme_break_test_data(path: str, data: List[List[Tuple[int, bool]]]):
    # Write the file
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as file:
        file.write(
            "// This file was generated automatically by unicode.py\n"
            "\n"
            "#pragma once\n"
            "\n"
            '#include "di/types/prelude.h"\n'
            '#include "di/vocab/array/prelude.h"\n'
            '#include "di/vocab/span/prelude.h"\n'
            '#include "di/format/prelude.h"\n'
            "\n"
            "namespace dius::unicode {\n"
            "\n"
            "struct GraphemeBreakTestCodePoint {\n"
            "    u32 code_point { 0 };\n"
            "    bool is_break { false };\n"
            "\n"
            "    auto operator==(GraphemeBreakTestCodePoint const&) const -> bool = default;\n"
            "\n"
            "    auto to_string() const {\n"
            "        return *di::present(\"{} {:04X} \"_sv, is_break ? U'÷' : U'×', code_point);\n"
            "    }\n"
            "};\n"
            "\n"
            "namespace detail {\n"
            "using T = GraphemeBreakTestCodePoint;\n"
        )
        for i, case in enumerate(data):
            as_str = f", ".join([f"T({hex(c)}, {str(b).lower()})" for c, b in case])
            file.write(
                f"    constexpr inline auto test_{i} = di::Array<GraphemeBreakTestCodePoint, {len(case)}>{{{as_str}}};\n"
            )
        file.write(
            "}\n"
            "\n"
            f"constexpr inline auto grapheme_break_test_data = di::Array<di::Span<GraphemeBreakTestCodePoint const>, {len(data)}> {{\n"
        )
        for i, _ in enumerate(data):
            file.write(f"    detail::test_{i},")
        file.write("};\n" "}\n")

    # Auto-format
    subprocess.run(["clang-format", "-i", path])


def gen_name_header(path: str, property: UnicodeProperty):
    # Write the file
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as file:
        file.write(
            "// This file was generated automatically by unicode.py\n"
            "\n"
            "#pragma once\n"
            "\n"
            '#include "di/types/prelude.h"\n'
            "\n"
            "namespace dius::unicode {\n"
        )

        for value in property.values_table:
            cat = GENERAL_CATEGORY.lookup_code_point(value.range().start)
            if "Format" in cat or "Separator" in cat:
                file.write(
                    f"constexpr inline auto {value.property} = c32({hex(value.range().start)});\n",
                )

        file.write("}\n")

    # Auto-format
    subprocess.run(["clang-format", "-i", path])


def gen_property_header(path: str, property: UnicodeProperty):
    # Write the file
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as file:
        file.write(
            "// This file was generated automatically by unicode.py\n"
            "\n"
            "#pragma once\n"
            "\n"
            '# include "di/reflect/prelude.h"\n'
            '# include "dius/unicode/property_range.h"\n'
            "\n"
            "namespace dius::unicode {\n"
            f"enum class {property.cpp_enum_name()} {{\n"
        )

        combined_categories = []
        if property.name == "General_Category":
            combined_categories = [
                property.lookup_value(x)
                for x in property.values_map.keys()
                if len(x) == 1
            ]
            property.values_map = {
                k: v for k, v in property.values_map.items() if len(k) > 1
            }
        if property.name == "Grapheme_Cluster_Break":
            # These are unused
            for k in ["EB", "EM", "GAZ", "EBG"]:
                del property.values_map[k]

        for value in property.values():
            file.write(
                f"{value},\n",
            )

        file.write(
            "};\n"
            "\n"
            f"constexpr auto tag_invoke(di::Tag<di::reflect>, di::InPlaceType<{property.cpp_enum_name()}>) {{\n"
            f"    using enum {property.cpp_enum_name()};\n"
            f'    return di::make_enumerators<"{property.cpp_enum_name()}">(\n'
        )

        file.write(
            ",\n".join([f'di::enumerator<"{v}", {v}>' for v in property.values()])
        )

        file.write("    );\n" "}\n" "\n")

        if property.name == "General_Category":
            for combined_category in combined_categories:
                concrete_categories = [
                    x for x in property.values() if combined_category in x
                ]
                file.write(
                    f"constexpr auto category_{combined_category.lower()}(GeneralCategory category) -> bool {{\n"
                    "    using enum GeneralCategory;"
                    f"    return {" || ".join([f"category == {x}" for x in concrete_categories])};"
                    "}\n\n"
                )

        file.write(
            "namespace detail {\n"
            f"auto {property.cpp_file_name()}_ranges() -> di::Span<PropertyRange<{property.cpp_enum_name()}> const>;\n"
            "}\n"
            "\n"
            f"inline auto {property.cpp_file_name()} = detail::LookupProperty<{property.cpp_enum_name()}, {property.cpp_enum_name()}::{property.fallback}>(detail::{property.cpp_file_name()}_ranges());\n"
            "}\n"
        )

    # Auto-format
    subprocess.run(["clang-format", "-i", path])


def gen_property_implementation(path: str, property: UnicodeProperty):
    # The default property doesn't need to be stored, so we can just ignore it.
    table = property.values_table
    table = [x for x in table if x.property != property.fallback]

    # Consolidate ranges for efficency
    table = combine_properties(table)

    # Write the file
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as file:
        file.write(
            "// This file was generated automatically by unicode.py\n"
            "\n"
            f'# include "dius/unicode/{property.cpp_file_name()}.h"\n'
            "\n"
            '# include "dius/unicode/property_range.h"\n'
            "\n"
            "namespace dius::unicode {\n"
            f"using R = PropertyRange<{property.cpp_enum_name()}>;"
            f"using enum {property.cpp_enum_name()};\n"
            "constexpr static auto s_ranges = di::Array {\n"
        )

        for entry in table:
            file.write(
                f"R({hex(entry.range().start)}, {hex(entry.range().end)}, {entry.property}),\n"
            )

        file.write(
            "};\n"
            "\n"
            "namespace detail {\n"
            f"auto {property.cpp_file_name()}_ranges() -> di::Span<PropertyRange<{property.cpp_enum_name()}> const> {{\n"
            "    return s_ranges;\n"
            "}\n"
            "}\n"
            "}\n"
        )

    # Auto-format
    subprocess.run(["clang-format", "-i", path])


def validate_grapheme_cluster_assumptions():
    # Verify all extended pictographs have grapheme property other
    pictographs = set()
    for r in EXTENDED_PICTOGRAPHIC.values_table:
        for c in range(r.range().start, r.range().end):
            pictographs.add(GRAPHEME_CLUSTER_BREAK.lookup_code_point(c))
    assert pictographs == {"Other"}

    # Verify all pictographs don't have indic properties
    pictographs_indic = set()
    for r in EXTENDED_PICTOGRAPHIC.values_table:
        for c in range(r.range().start, r.range().end):
            pictographs_indic.add(INDIC_CONJUNCT_BREAK.lookup_code_point(c))
    assert pictographs_indic == {"None"}

    # Verify indic consonants are "Other", while indic=extend and indic=linker are "Extend". ZWJ is a special case.
    indic_grapheme_properties = defaultdict(lambda: set())
    for r in INDIC_CONJUNCT_BREAK.values_table:
        for c in range(r.range().start, r.range().end):
            indic_grapheme_properties[r.property].add(
                GRAPHEME_CLUSTER_BREAK.lookup_code_point(c)
            )
    assert indic_grapheme_properties == {
        "Extend": {"Extend", "ZWJ"},
        "Consonant": {"Other"},
        "Linker": {"Extend"},
    }


def main():
    args = parser.parse_args()

    input_path = lambda path: f"{args.input}/{path}"
    output_path = lambda path: f"{args.output}/{path}"

    property_aliases = parse_property_aliases(input_path(PROPERTY_ALIASES_INPUT))
    value_aliases = parse_property_value_aliases(
        input_path(PROPERTY_VALUE_ALIASES_INPUT)
    )

    for prop in UNICODE_PROPERTIES:
        prop.short_name = property_aliases[prop.name]
        prop.values_map = value_aliases[prop.short_name]
        prop.values_table = parse_property_file(
            input_path(prop.input_file),
            prop,
        )
        # Sort by range start, so we can use binary search for the lookup
        prop.values_table.sort(key=lambda x: x.sequence[0].start)

        if (
            prop.name == "Indic_Conjunct_Break"
            or prop.name == "Extended_Pictographic"
            or prop.name == "Grapheme_Cluster_Break"
        ):
            continue
        elif prop.name == "Name":
            gen_name_header(
                output_path(f"include/generic/dius/unicode/{prop.cpp_file_name()}.h"),
                prop,
            )
        else:
            gen_property_header(
                output_path(f"include/generic/dius/unicode/{prop.cpp_file_name()}.h"),
                prop,
            )
            gen_property_implementation(
                output_path(f"src/generic/unicode/{prop.cpp_file_name()}.cpp"),
                prop,
            )

    # Create test data for grapheme cluster
    grapheme_tests = parse_grapheme_break_test(
        input_path("auxiliary/GraphemeBreakTest.txt")
    )
    gen_grapheme_break_test_data(
        output_path("test/src/grapheme_break_test_data.h"), grapheme_tests
    )

    # We extend the grapheme cluster properties to include the extended pictographic
    # property as well as the indic conjunct break property, to allow for grapheme
    # segmentation using only a single lookup. This also simplifies the internal
    # state machine inputs.
    validate_grapheme_cluster_assumptions()

    GRAPHEME_CLUSTER_BREAK.values_map["oep"] = "Other_ExtendedPictographic"
    GRAPHEME_CLUSTER_BREAK.values_map["eie"] = "Extend_IndicConjunctBreak_Extend"
    GRAPHEME_CLUSTER_BREAK.values_map["eil"] = "Extend_IndicConjunctBreak_Linker"
    GRAPHEME_CLUSTER_BREAK.values_map["oic"] = "Other_IndicConjunctBreak_Consonant"

    # Now rebuild the lookup table by iterating over every possible code point
    new_values: List[UnicodePropertyRange] = []
    for c in range(0x10FFFF + 1):
        orig = GRAPHEME_CLUSTER_BREAK.lookup_code_point(c)
        indic = INDIC_CONJUNCT_BREAK.lookup_code_point(c)
        pictographic = EXTENDED_PICTOGRAPHIC.lookup_code_point(c)
        new = orig
        if indic == "Extend" and orig != "ZWJ":
            new = "Extend_IndicConjunctBreak_Extend"
        elif indic == "Linker":
            new = "Extend_IndicConjunctBreak_Linker"
        elif indic == "Consonant":
            new = "Other_IndicConjunctBreak_Consonant"
        elif pictographic == "Yes":
            new = "Other_ExtendedPictographic"
        p = None
        if len(new_values) > 0:
            p = new_values[-1]
        if p is not None and p.property == new:
            p.range().end += 1
            continue
        new_values.append(UnicodePropertyRange([CodePointRange(c, c + 1)], new))
    GRAPHEME_CLUSTER_BREAK.values_table = new_values

    gen_property_header(
        output_path(
            f"include/generic/dius/unicode/{GRAPHEME_CLUSTER_BREAK.cpp_file_name()}.h"
        ),
        GRAPHEME_CLUSTER_BREAK,
    )
    gen_property_implementation(
        output_path(
            f"src/generic/unicode/{GRAPHEME_CLUSTER_BREAK.cpp_file_name()}.cpp"
        ),
        GRAPHEME_CLUSTER_BREAK,
    )


if __name__ == "__main__":
    main()
