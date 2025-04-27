#!/usr/bin/env python

import argparse
import copy
import os
import re
import subprocess
from dataclasses import dataclass
from typing import Dict, List, Self

EAST_ASIAN_WIDTH_INPUT = "EastAsianWidth.txt"
EAST_ASIAN_WIDTH_OUTPUT = "src/generic/unicode/east_asian_width.cpp"
EAST_ASIAN_WIDTH_PROPERTIES = {
    "A": "Ambiguous",
    "F": "Fullwidth",
    "H": "Halfwidth",
    "W": "Wide",
    "Na": "Narrow",
    "N": "Neutral",
}

parser = argparse.ArgumentParser(
    description="Generates C++ source files from the Unicode Database for the dius library",
)
parser.add_argument("-i", "--input", default=os.getenv("DIUS_UNICODE_DATABASE_DIR"))
parser.add_argument("-o", "--output", default="./")


def main():
    args = parser.parse_args()
    east_asian_width = parse_file(
        f"{args.input}/{EAST_ASIAN_WIDTH_INPUT}", EAST_ASIAN_WIDTH_PROPERTIES
    )
    gen_east_asian_width(f"{args.output}/{EAST_ASIAN_WIDTH_OUTPUT}", east_asian_width)


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
class UnicodeProperty:
    sequence: List[UnicodeRange]
    property: str


def combine_properties(properties: List[UnicodeProperty]) -> List[UnicodeProperty]:
    result: List[UnicodeProperty] = []
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


def parse_file(path: str, mapping: Dict[str, str]) -> List[UnicodeProperty]:
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
            result.append(UnicodeProperty(sequence, mapping[property.strip()]))
    return result


def gen_east_asian_width(path: str, properties: List[UnicodeProperty]):
    # The default property value is N, so we can just ignore it.
    properties = [x for x in properties if x.property != "N"]

    # Consolidate ranges for efficency
    properties = combine_properties(properties)

    # Write the file
    with open(path, "w") as file:
        file.write(
            """
            #include "dius/unicode/unicode.h"

            namespace dius::unicode {
            using enum EastAsianWidth;
            constexpr static auto s_ranges = di::Array {
            """
        )

        for property in properties:
            file.write(
                f"Range({hex(property.sequence[0].start)}, {hex(property.sequence[0].end)}, {property.property}),\n"
            )

        file.write(
            """};

            auto east_asian_width_ranges() -> di::Span<Range const> {
                return s_ranges;
            }
            }
        """
        )

    # Auto-format
    subprocess.run(["clang-format", "-i", path])


if __name__ == "__main__":
    main()
