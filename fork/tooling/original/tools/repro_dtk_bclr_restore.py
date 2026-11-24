#!/usr/bin/env python3
"""Reproduce DTK 1.8.4's orphaned-restore analysis with synthetic DOLs.

No game input, compiler or target execution is used. The two generated images
differ only in the link bit of an unconditional branch through LR. This tests
inference behavior, not the ownership or original extent of a game function.
"""

import argparse
import hashlib
import json
from pathlib import Path
import struct
import subprocess


REVISION = "a0c455e46cab58e1d2e0885623f85089ff0499db"
INIT = 0x81000000
TEXT = 0x81001000
DATA = 0x81002000
BSS = 0x81003000
TEXT_OFFSET = 0x500
BRANCH_WORD = 7


def image(linking: bool) -> bytes:
    # Constructed PowerPC fixture; these words were not extracted from a game.
    words = [
        0x7C0802A6,  # mflr r0
        0x90010004,  # stw r0,4(r1)
        0x9421FFF0,  # stwu r1,-16(r1)
        0x93E1000C,  # stw r31,12(r1)
        0x3FE08100,  # lis r31,0x8100
        0x63FF1034,  # ori r31,r31,0x1034: address of the trailing leaf
        0x7FE803A6,  # mtlr r31
        0x4E800020 | int(linking),  # blr / blrl: the only variant bit
        0x83E1000C,  # lwz r31,12(r1): restore begins at TEXT+0x20
        0x80010014,  # lwz r0,20(r1)
        0x7C0803A6,  # mtlr r0
        0x38210010,  # addi r1,r1,16
        0x4E800020,  # blr: restore ends at TEXT+0x34
        0x38600001,  # li r3,1: trailing leaf
        0x4E800020,  # blr
    ]
    text = struct.pack(">15I", *words)
    init = bytearray(struct.pack(">I", 0x60000000) * 256)
    struct.pack_into(">2I", init, 0, 0x48001001, 0x4E800020)  # bl TEXT; blr
    # Minimal ROM-copy and BSS-init metadata, found by the stock DOL reader.
    struct.pack_into(
        ">16I", init, 0x2C0,
        INIT, INIT, len(init), TEXT, TEXT, len(text), DATA, DATA, 64,
        0, 0, 0, BSS, 64, 0, 0,
    )
    header = bytearray(0x100)
    for index, offset, address, size in (
        (0, 0x100, INIT, len(init)),
        (1, TEXT_OFFSET, TEXT, len(text)),
        (7, TEXT_OFFSET + len(text), DATA, 64),
    ):
        for field, value in (
            (index * 4, offset),
            (0x48 + index * 4, address),
            (0x90 + index * 4, size),
        ):
            struct.pack_into(">I", header, field, value)
    struct.pack_into(">3I", header, 0xD8, BSS, 64, INIT)
    return bytes(header) + init + text + struct.pack(">16I", *([0x01234567] * 16))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dtk", required=True, type=Path)
    parser.add_argument("--out-dir", type=Path, default=Path("build/dtk-bclr-repro"))
    args = parser.parse_args()
    dtk = args.dtk.resolve(strict=True)
    dtk_sha256 = hashlib.sha256(dtk.read_bytes()).hexdigest()
    version = subprocess.check_output([str(dtk), "--version"], text=True).strip()
    if "1.8.4" not in version or REVISION not in version:
        parser.error(f"requires DTK 1.8.4 at {REVISION}; observed {version!r}")

    images = {"nonlinking": image(False), "linking": image(True)}
    left, right = images.values()
    differences = [i for i, (a, b) in enumerate(zip(left, right)) if a != b]
    changed_byte = TEXT_OFFSET + BRANCH_WORD * 4 + 3
    if (
        len(left) != len(right)
        or differences != [changed_byte]
        or (left[changed_byte] ^ right[changed_byte]) != 1
    ):
        raise RuntimeError("fixture differs by more than the branch link bit")
    try:
        args.out_dir.mkdir(parents=True, exist_ok=False)
    except FileExistsError:
        parser.error("--out-dir must name a new directory")

    results = {}
    for name, data in images.items():
        path = args.out_dir / f"{name}.dol"
        path.write_bytes(data)
        proc = subprocess.run(
            [str(dtk), "dol", "info", str(path)],
            text=True, capture_output=True, timeout=30,
        )
        log = proc.stdout + proc.stderr
        (args.out_dir / f"{name}.log").write_text(log)
        results[name] = {
            "returncode": proc.returncode,
            "image_sha256": hashlib.sha256(data).hexdigest(),
            "unpaired_epilogue": "Unpaired epilogue" in log,
        }
        if name == "nonlinking":
            results[name]["expected_diagnostic_address"] = "0x81001028" in log

    reproduced = (
        results["nonlinking"]["returncode"] == 1
        and results["nonlinking"]["unpaired_epilogue"]
        and results["nonlinking"]["expected_diagnostic_address"]
        and results["linking"]["returncode"] == 0
        and not results["linking"]["unpaired_epilogue"]
    )
    if hashlib.sha256(dtk.read_bytes()).hexdigest() != dtk_sha256:
        raise RuntimeError("DTK executable changed during reproduction")
    report = {
        "dtk_version": version,
        "dtk_sha256": dtk_sha256,
        "only_changed_file_byte": f"0x{changed_byte:X}",
        "changed_bit_xor": 1,
        "synthetic_restore_range": ["0x81001020", "0x81001034"],
        "results": results,
        "reproduced": reproduced,
        "scope": "Tool inference only; no game data, target execution, original ownership or extent proof.",
    }
    (args.out_dir / "result.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
    return 0 if reproduced else 1


if __name__ == "__main__":
    raise SystemExit(main())
