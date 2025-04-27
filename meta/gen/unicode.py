#!/usr/bin/env python

import argparse
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
class UnicodeProperty:
    name: str
    input_file: str
    fallback: str
    values: List[str] = field(default_factory=lambda: [])

    def cpp_enum_name(self) -> str:
        return self.name.title().replace("_", "")

    def cpp_file_name(self) -> str:
        return self.name.lower()


UNICODE_PROPERTIES = [
    UnicodeProperty("East_Asian_Width", "EastAsianWidth.txt", "Neutral"),
]


@dataclass
class UnicodeRange:
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


@dataclass
class UnicodePropertyRange:
    sequence: List[UnicodeRange]
    property: str


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
            result[prop.strip()][short.strip()] = long.strip()
    return result


def parse_property_file(
    path: str, mapping: Dict[str, str]
) -> List[UnicodePropertyRange]:
    result = []
    with open(path, "r") as file:
        for line in file.readlines():
            line = re.sub(re.compile("#.*"), "", line.strip())
            if line == "":
                continue

            sequence, property = line.split(";")
            sequence = [
                UnicodeRange.from_code_points(x) for x in sequence.strip().split(" ")
            ]
            result.append(UnicodePropertyRange(sequence, mapping[property.strip()]))
    return result


def gen_property_header(path: str, unicode_property: UnicodeProperty):
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
            f"enum class {unicode_property.cpp_enum_name()} {{\n"
        )

        for value in unicode_property.values:
            file.write(
                f"{value},\n",
            )

        file.write(
            "};\n"
            "\n"
            f"constexpr auto tag_invoke(di::InPlaceType<{unicode_property.cpp_enum_name()}>) {{\n"
            f"    using enum {unicode_property.cpp_enum_name()};\n"
            f'    return di::make_enumerators<"{unicode_property.cpp_enum_name()}">(\n'
        )

        file.write(
            ",\n".join([f'di::enumerator<"{v}", {v}>' for v in unicode_property.values])
        )

        file.write(
            "    );\n"
            "}\n"
            "\n"
            "namespace detail {\n"
            f"auto {unicode_property.cpp_file_name()}_ranges() -> di::Span<PropertyRange<{unicode_property.cpp_enum_name()}> const>;\n"
            "}\n"
            "\n"
            f"inline auto {unicode_property.cpp_file_name()} = detail::LookupProperty<{unicode_property.cpp_enum_name()}, {unicode_property.cpp_enum_name()}::{unicode_property.fallback}>(detail::{unicode_property.cpp_file_name()}_ranges());\n"
            "}\n"
        )

    # Auto-format
    subprocess.run(["clang-format", "-i", path])


def gen_property_implementation(
    path: str, unicode_property: UnicodeProperty, properties: List[UnicodePropertyRange]
):
    # The default property value is N, so we can just ignore it.
    properties = [x for x in properties if x.property != unicode_property.fallback]

    # Consolidate ranges for efficency
    properties = combine_properties(properties)

    # Write the file
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as file:
        file.write(
            "// This file was generated automatically by unicode.py\n"
            "\n"
            f'# include "dius/unicode/{unicode_property.cpp_file_name()}.h"\n'
            "\n"
            '# include "dius/unicode/property_range.h"\n'
            "\n"
            "namespace dius::unicode {\n"
            f"using R = PropertyRange<{unicode_property.cpp_enum_name()}>;"
            f"using enum {unicode_property.cpp_enum_name()};\n"
            "constexpr static auto s_ranges = di::Array {\n"
        )

        for property in properties:
            file.write(
                f"R({hex(property.sequence[0].start)}, {hex(property.sequence[0].end)}, {property.property}),\n"
            )

        file.write(
            "};\n"
            "\n"
            "namespace detail {\n"
            f"auto {unicode_property.cpp_file_name()}_ranges() -> di::Span<PropertyRange<{unicode_property.cpp_enum_name()}> const> {{\n"
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
        prop.values.extend(value_aliases[property_aliases[prop.name]].values())
        table = parse_property_file(
            input_path(prop.input_file),
            value_aliases[property_aliases[prop.name]],
        )
        gen_property_header(
            output_path(f"include/generic/dius/unicode/{prop.cpp_file_name()}.h"),
            prop,
        )
        gen_property_implementation(
            output_path(f"src/generic/unicode/{prop.cpp_file_name()}.cpp"),
            prop,
            table,
        )


if __name__ == "__main__":
    main()
