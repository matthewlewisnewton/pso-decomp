# Scalar constants at 805D8200

`pso/unk/data_805D8200.cpp` replaces the complete automatic fallback
`auto_11_805D8200_sdata2`: `.sdata2` at `0x805D8200..0x805D8278`, 120 bytes.
It defines the 30 existing exported four-byte objects as `const f32` with C
linkage. The boundary follows the existing automatic split, between
`TBoss8Dragon_8002CC48.cpp`'s constant range and `TBoss2DeRolLe.cpp`'s range.
The historical translation-unit owner is unresolved, so the source retains an
address-based name and does not merge the consuming code units.

The original split objects contain 54 `R_PPC_EMB_SDA21` references to this
range, all on `lfs` instructions. Every object is referenced. The nine reader
units are `TObjBoss1Rock`, `text_8002E090`, `text_8002E174`,
`TObjPlayer_8002E784`, `TBoss2PhotonBullet_80038DCC`, `TBoss2Joint`,
`TBoss2Fin`, `TObjBoss2CeilJunk_8003A81C`, and `TObjBoss2Tunnel_8003B138`.
Their existing source uses the values for opacity, gravity, damping, random
angle scaling, debris scale and collision bounds. These are scalar program
constants, not an asset image or an opaque byte array.

Equal-valued objects keep their separate exported identities and offsets;
for example, `lbl_805D8200` and `lbl_805D8228` both hold `1.0f`. The random
scale constants use the exact expression `1.0f / 32768.0f`. The arrangement
follows the separate named definitions in `DelDepthConstants.cpp` and the
object-layout checks in [compiler emission evidence](compiler-emission-evidence.md).

On fork-main base `1563389ef33299da5f8ebf2e6228cf1947aaa2df`, the first
GC/2.6 compile with the normal game flags reproduced all section bytes,
all 30 global symbol bindings, sizes and offsets, and the original eight-byte
section alignment. No compiler override or new porting exception is needed.
This is data recovery only; it adds no function matches.

The source-linked build preserves DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. After that gated full build,
`tools/check_pr.py --no-build` passes against the unchanged-main baseline:
120 additional matched and linked data bytes, one additional linked unit,
and no code, function, data or linkage regressions. The generated retention
list is unchanged: all 30 objects already have references.
