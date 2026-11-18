#!/usr/bin/env python3
"""Generate the MusyX firmware initializer from the original DOL's split object."""

import argparse
from pathlib import Path

from link_units import elf_section_bytes


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("split_object", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()

    image = elf_section_bytes(args.split_object, ".data")
    if image is None or len(image) != 0x19E0:
        parser.exit(1, f"{args.split_object}: expected a 0x19E0-byte MusyX DSP image\n")

    lines = [
        "    " + ", ".join(f"0x{byte:02X}" for byte in image[offset:offset + 16]) + ",\n"
        for offset in range(0, len(image), 16)
    ]
    text = "".join(lines)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    if not args.output.exists() or args.output.read_text(encoding="utf-8") != text:
        args.output.write_text(text, encoding="utf-8")


if __name__ == "__main__":
    main()
