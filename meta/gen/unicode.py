#!/usr/bin/env python

import argparse
import bisect
import copy
import os
import re
import subprocess
from collections import defaultdict
from dataclasses import dataclass, field
from typing import Dict, List, Self

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

    # Mapping from short value aliases to long aliases
    values_map: Dict[str, str] = field(default_factory=lambda: {})

    # Property table derived from parsing the UCD
    values_table: List[UnicodePropertyRange] = field(default_factory=lambda: [])

    def cpp_enum_name(self) -> str:
        return self.name.title().replace("_", "")

    def cpp_file_name(self) -> str:
        return self.name.lower()

    def lookup_value(self, short: str) -> str:
        return self.values_map[short]

    def values(self) -> List[str]:
        return list(self.values_map.values())


UNICODE_PROPERTIES = [
    UnicodeProperty("East_Asian_Width", "EastAsianWidth.txt", "Neutral"),
    UnicodeProperty(
        "General_Category", "extracted/DerivedGeneralCategory.txt", "Unassigned"
    ),
    UnicodeProperty("Emoji", "emoji/emoji-data.txt", "No", True),
    UnicodeProperty("Extended_Pictographic", "emoji/emoji-data.txt", "No", True),
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


def parse_property_file(path: str, prop: UnicodeProperty) -> List[UnicodePropertyRange]:
    result = []
    with open(path, "r") as file:
        for line in file.readlines():
            line = re.sub(re.compile("#.*"), "", line.strip())
            if line == "":
                continue

            sequence, property = line.split(";")
            sequence = [
                CodePointRange.from_code_points(x) for x in sequence.strip().split(" ")
            ]
            if prop.boolean:
                if property.strip() == prop.name:
                    result.append(UnicodePropertyRange(sequence, "Yes"))
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


def gen_name_header(path: str, property: UnicodeProperty, category: UnicodeProperty):
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
            cat = "Unassigned"
            i = bisect.bisect_left(
                category.values_table,
                value.range().start,
                key=lambda x: x.range().end - 1,
            )
            if i < len(category.values_table) and category.values_table[
                i
            ].range().contains(value.range().start):
                cat = category.values_table[i].property
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

        for value in property.values():
            file.write(
                f"{value},\n",
            )

        file.write(
            "};\n"
            "\n"
            f"constexpr auto tag_invoke(di::InPlaceType<{property.cpp_enum_name()}>) {{\n"
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


def main():
    args = parser.parse_args()

    input_path = lambda path: f"{args.input}/{path}"
    output_path = lambda path: f"{args.output}/{path}"

    property_aliases = parse_property_aliases(input_path(PROPERTY_ALIASES_INPUT))
    value_aliases = parse_property_value_aliases(
        input_path(PROPERTY_VALUE_ALIASES_INPUT)
    )

    for prop in UNICODE_PROPERTIES:
        prop.values_map = value_aliases[property_aliases[prop.name]]
        prop.values_table = parse_property_file(
            input_path(prop.input_file),
            prop,
        )
        # Sort by range start, so we can use binary search for the lookup
        prop.values_table.sort(key=lambda x: x.sequence[0].start)

        if prop.name == "Name":
            general_category = None
            for p in UNICODE_PROPERTIES:
                if p.name == "General_Category":
                    general_category = p
            if general_category is None:
                raise Exception("Failed to find General_Category")
            gen_name_header(
                output_path(f"include/generic/dius/unicode/{prop.cpp_file_name()}.h"),
                prop,
                general_category,
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


if __name__ == "__main__":
    main()
