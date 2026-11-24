# Gryphon behavior scalar constant unit

Base: fork main `2344b179717a97c9604db931189ad6d7dc6a9cc8`.

The complete original-only unit `auto_11_805D8E28_sdata2` covers
`0x805D8E28..0x805D8ED0`: 41 single-precision constants and four trailing
zero alignment bytes. `Boss5GryphonConstants.cpp` supplies this existing
range as ordinary externally linked `const f32` definitions. This preserves
the data boundary; the consumer establishes the Gryphon association, not a
historical source filename or a recovered original object boundary.

## Consumer and types

A census of all 8,680 active configured original and compiled objects finds
undefined references to these symbols only in the original and compiled
`Boss5GryphonBehavior` objects. Both reference all 41 symbols. The original
89 SDA21 relocations all belong to `lfs` instructions; the current declarations
agree on `f32`.
Examples include:

| Instruction address | Constant | Use |
| --- | --- | --- |
| `0x80061264` | `0x805D8E28`, 16384 | Takeoff angle scaling before the cosine lookup |
| `0x80061744` | `0x805D8E3C`, 2.1 | Dive-motion speed |
| `0x80064F34` | `0x805D8EC8`, 1000 | `update_linked_ground_position` argument |

The last symbol's former eight-byte extent combined the `1000.0f` load
with four zero bytes. Its corrected extent is four. The compiled section
contains 164 bytes with alignment eight; the native linker recreates the
tail before the following original contribution at `0x805D8ED0`. The split
retains the complete 168-byte range. There is no padding variable or array.

## Compiler comparisons

The fresh unchanged-main build and retention check passed before editing.
The initial GC/2.0 trial defined the constants after their readers in
`Boss5GryphonBehavior.cpp`. It preserved the instructions but emitted the
new objects in writable `.sdata`, leaving `.sdata2` unchanged. The
[Mylla](photon-mylla-constant-pool.md) and
[loading-particle](now-loading-constant-pool.md) investigations record the
same late-definition issue.

Following those investigations, replacing the external reads with literals
emitted a 356-byte `.sdata2` section: the new constants preceded the existing
184-byte pool, and constant folding added `-66.5f` and `-116.5f`. It also
changed instructions. That trial was discarded.

Small C and C++ probes under GC/2.0 and GC/2.6 confirmed that separate
initialized external constants naturally use `.sdata2`. Following the
[standalone scalar-unit precedent](scalar-constants-805d8200.md), compiling
the definitions separately reproduces all 41 values, exported object names,
four-byte sizes, offsets, and section alignment. No source postprocessing,
new compiler override, intrinsic, section attribute, or pragma is needed.
The existing behavior source is unchanged, and its complete compiled object
is byte-identical to the baseline, including its relocations.

## Validation

The complete constant unit scores 100% and links from its compiled source
object. The active original-object inventory and actual linker inputs no
longer contain `auto_11_805D8E28_sdata2.o`. The behavior unit retains all
168 exact functions, 34,984 code bytes, and 3,948 owned data bytes.

The native build and `tools/check_pr.py` pass. Matched and linked data both
increase by 168 bytes, and linked units increase from 3,615 to 3,616. There
is no code, function, data, or linkage loss; total data coverage remains
1,761,096 bytes. The existing generated retention metadata is unchanged.
The rebuilt DOL retains SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. This is complete data-unit
recovery and does not add function matches.
