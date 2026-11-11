#!/usr/bin/env python3
"""Characterize a local Zako snapshot experiment without original game inputs.

This deliberately requires an explicit experimental source file. It does not
rewrite or compile the production renderer, which retains an unresolved call
contract. It extracts the actual setup and final restore statements, stubs the
two-input material helper and checks only the resulting 32-bit state transaction.
It is not evidence of native matching, ABI, GPU or complete renderer correctness.
"""

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile


SCOPE = (
    "Actual experimental source setup/restore statements only, with a two-input "
    "helper stub. Not native codegen, ABI, pointer layout, complete rendering, "
    "GPU behavior or float-rounding proof."
)


def extract(source):
    functions = re.findall(
        r"(?ms)^void TObjPlayer__sub_8030A9B0\(\) \{(.*?)^\}", source
    )
    if len(functions) != 1:
        raise ValueError("Expected exactly one unfolded Zako shadow function")
    body = functions[0]
    start = body.index("    old = model_render_flags;")
    end = body.index("    tbl =", start)
    setup = body[start:end]
    if not setup.rstrip().endswith(
        "set_chunk_material_override_pair(0xFF00, 0x900);"
    ) or "((void" in setup:
        raise ValueError("Expected the direct two-input experimental call")
    start = body.index(
        "    chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;",
        end,
    )
    restore = body[start:]
    for declaration in ("u32 old;", "s32 old_and_mask;", "s32 old_or_mask;"):
        if declaration not in body[:body.index("    old = model_render_flags;")]:
            raise ValueError(f"Missing expected snapshot declaration: {declaration}")
    return setup, restore


def harness(setup, restore):
    return r'''
#include <cassert>
#include <cstdint>
using u32 = std::uint32_t;
using s32 = std::int32_t;
u32 model_render_flags, saved_model_render_flags, lbl_805DF138;
s32 chunk_polygon_flags_and_mask, chunk_polygon_flags_or_mask;
s32 saved_chunk_polygon_flags_and_mask, saved_chunk_polygon_flags_or_mask;
void set_chunk_material_override_pair(s32 a, s32 b) {
    chunk_polygon_flags_and_mask = a;
    chunk_polygon_flags_or_mask = b;
}
void setup() {
    u32 old;
    s32 old_and_mask, old_or_mask;
''' + setup + '\n}\nvoid restore() {\n' + restore + r'''
}
int main() {
    u32 rng = 0x1c4e793b;
    for (int i = 0; i < 10000; ++i) {
        rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5;
        u32 f = rng, a = rng * 0x9e3779b9u, o = ~rng;
        model_render_flags = f;
        chunk_polygon_flags_and_mask = s32(a);
        chunk_polygon_flags_or_mask = s32(o);
        lbl_805DF138 = 0x82c;
        setup();
        assert(model_render_flags == ((f & ~u32(0x10)) | 0x82c));
        assert(saved_model_render_flags == f);
        assert(u32(saved_chunk_polygon_flags_and_mask) == a);
        assert(u32(saved_chunk_polygon_flags_or_mask) == o);
        assert(chunk_polygon_flags_and_mask == 0xff00);
        assert(chunk_polygon_flags_or_mask == 0x900);
        // Intervening draws can replace these shared backups. Restoration must
        // observe their current values, not keep the entry snapshots alive.
        saved_model_render_flags = o;
        saved_chunk_polygon_flags_and_mask = s32(f);
        saved_chunk_polygon_flags_or_mask = s32(a);
        restore();
        assert(model_render_flags == o);
        assert(u32(chunk_polygon_flags_and_mask) == f);
        assert(u32(chunk_polygon_flags_or_mask) == a);
    }
}
'''


def characterize(source, compiler, sanitize=False):
    setup, restore = extract(source)
    compiler = shutil.which(compiler)
    if compiler is None:
        raise ValueError("A host C++ compiler is required")
    version = subprocess.run(
        [compiler, "--version"], check=True, capture_output=True, text=True,
        timeout=10,
    ).stdout.splitlines()[0]
    flags = ["-std=c++17", "-O1" if sanitize else "-O2"]
    if sanitize:
        flags += ["-fsanitize=address,undefined", "-fno-sanitize-recover=undefined",
                  "-fno-omit-frame-pointer"]
    with tempfile.TemporaryDirectory() as temp:
        path = Path(temp)
        cpp, binary = path / "snapshot.cpp", path / "snapshot"
        cpp.write_text(harness(setup, restore))
        subprocess.run(
            [compiler, *flags, str(cpp), "-o", str(binary)], check=True, timeout=30,
        )
        env = os.environ.copy()
        if sanitize:
            env["ASAN_OPTIONS"] = "detect_leaks=0"
        subprocess.run([str(binary)], check=True, env=env, timeout=10)
    sha = lambda value: hashlib.sha256(value.encode()).hexdigest()
    return {
        "source_sha256": sha(source),
        "setup_excerpt_sha256": sha(setup),
        "restore_excerpt_sha256": sha(restore),
        "host_compiler": version,
        "host_compiler_flags": flags,
        "states_checked": 10000,
        "sanitizers": sanitize,
        "result": "pass",
        "scope": SCOPE,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, required=True,
                        help="Trusted local experimental C++ source to characterize")
    parser.add_argument("--cxx", default="g++")
    parser.add_argument("--sanitize", action="store_true")
    parser.add_argument("--json", type=Path)
    args = parser.parse_args()
    result = characterize(args.source.read_text(), args.cxx, args.sanitize)
    output = json.dumps(result, indent=2) + "\n"
    if args.json:
        args.json.write_text(output)
    print(output, end="")


if __name__ == "__main__":
    main()
