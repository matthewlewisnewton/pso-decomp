# DD collision and random helper unit

Recovery base: fork `main` `7ebf37b81371f6c04b17fceb9120716255d4f02d`.
The bounded `pso/enemy/TObjEneDD.cpp` unit owns five functions at
`0x800B9FE8..0x800BA138` (336 bytes). Its code already matched and linked.
This change removes its duplicate collision-array views and brings its remaining
eight constant bytes into source. It does not establish the boundaries of the
other DD units or the original names of the numbered virtual functions.

## Shared layout and behavior

The collision loops at `0x800BA030` and `0x800BA084` load the array at actor
+0xA4, compare a signed index against the count at +0xA8 on each iteration,
and advance through 0x2C-byte records. These are the existing shared
`TObjCollidable::bodies`, `body_count`, and `CollisionBody`. Both loops now
use those fields directly instead of two duplicate object and record structs.
They retain the original per-iteration loads and signed comparison.

The contact helpers still have the shared `u8 *` interface declared in
`TObjEneDD_800BA754.h`. Only the body address crosses that byte-pointer
boundary; no alternate class layout or function signature is introduced.
Recovering the helper definitions and their other callers is outside this unit.

`vfunc_96` calls the existing virtual slots +0x170 and +0x174 in that order,
then clears actor flag bits 0x04000000 and 0x00040000. `vfunc_99` returns
0 or 1 for bit 0x10. The random helper forwards its actual receiver to
`TObjChara::random_ratio`, then computes `2.0f * (ratio - 0.5f)`.
The [scaled-random receiver evidence](dd-scaled-random-evidence.md) explains
why this family must preserve the receiver.

## Compile, compare, research, and refine

The initial native-field reconstruction preserved both loops and `vfunc_96`
exactly. A direct bit predicate compiled to 12 bytes against the original 24
and scored 40%; replacing external floats with literals scored 99.166664%
until their data range belonged to the unit.

The [Dragon fireball recovery](dragon-fireball-unit.md) and
[main-phase predicate evidence](main-phase-predicate-evidence.md) distinguish
integer normalization from byte-valued Boolean results. Isolated GC/2.6 C and
C++ probes tested a direct bit test, a byte cast, equality with 0x10, ternary
normalization, and subtraction followed by a zero comparison. The first four
forms all emitted the shorter rotate/mask sequence. The explicit subtraction
and byte cast reproduced the original subtract, count-leading-zero, and
byte-extraction instructions in both languages. The implementation retains
that ordinary arithmetic expression with a matching comment; no intrinsic,
pragma, assembly, or compiler override is needed.

The [constant-pool investigation](conversion-pool-constants.md) explains why
literal pools need correct ownership and symbol scope. The two floats at
`0x805D9E98..0x805D9EA0` are 2.0 and 0.5 in that order. A fresh census of
the active original and compiled objects found no consumers outside this unit.
After assigning the range, `localize_split_globals.py` independently accepted
both exports as private. The literals now emit the exact eight-byte pool.
No named duplicate data objects are added.

## Validation

A fresh unchanged-main baseline and the final candidate both build to original
DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
`tools/check_pr.py` passes: no exact function, code, data, or linked range is
lost; all 3,616 linked units remain exact and retention is current.

All five functions and all eight owned data bytes match and link from source.
An independent ELF comparison verifies identical allocated payload bytes,
section sizes and alignments (`.text`: 336/4; `.sdata2`: 8/8), function order,
and all five relocation offsets, types, and resolved targets. Compiler-only
metadata and local symbol spellings are not asserted identical.

Matched and linked data each gain eight bytes. Matched and linked code,
function counts, unit counts, and coverage denominators do not change.
`linked_units.txt` and generated retention remain unchanged because the code
unit already linked and neither private pool entry needs retention.
Raw objects, disassembly, reports, and probes remain local.
