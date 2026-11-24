# Ending wall controller

Baseline: fork main `f1227326c4b7deaa4c33186978ad623862b590d5`.
The four existing `TEndingAB` fragments already matched and linked. This
change recovers their shared layout and native constructor, consolidates the
contiguous code into `pso/misc/TEndingAB.cpp`, and owns the remaining scalar
pool and two small-state objects. It adds no newly matched functions or code.

## Ownership and layout

The contiguous code range is `0x8008C9FC..0x8008D00C`: fade advancement,
overlay drawing, texture-list selection, the empty `0x8008CCC0` hook, quad
initialization, render and task wrappers, destructor, constructor, texture
release, and `TScene::bind_ending_wall_textures`. The class-name string and
native four-slot vtable identify `TEndingAB`; the scene texture binder uses
the same four wall-texture sets. This supports consolidating these fragments,
without proving the historical source filename or translation-unit boundary.

The constructor at `0x8008CE80` passes its incoming second register directly
to `TObject(TObject *)`. Its caller in `TEnding` allocates `0xF0` bytes and
passes the ending object as parent. The recovered constructor therefore takes
`TObject *`, and its symbol becomes `__ct__9TEndingABFP7TObject` at the same
address and size. The caller now uses `new TEndingAB(this)`.

The state fields occupy `0x1C..0x2C`: elapsed ticks, the unresolved word
initialized to 255, picture index, and wall index. Forty-eight float stores
fill six rectangles at `0x2C..0xEC`; the timing rate at `0xEC` is 30 or 25
according to the video-mode getter. The renderer passes the first four
rectangles to `draw_textured_quad_at_depth`, whose reads establish the
position and UV field order. Compile-time guards check both offsets and the
`0xF0` object size. The nearby `TEndingPic` supplies an independently recovered
sibling layout and the same state-machine arithmetic.

The empty hook retains its existing provisional free-function name. Its call
passes the controller pointer, but an empty body cannot establish original
ownership or purpose. The word at `0x20` likewise keeps an offset name.

The wall-texture sets use the shared `GinjaTextureEntry` and
`GinjaTextureList` declarations. Their names remain immutable archive lookup
keys; the explicit const casts accommodate the existing entry type's mutable
name field, while the loader updates texture handles. The shared wall-list
storage and its getter now carry a texture-list pointer throughout
`TEndingAB` and `TEndingPic`, replacing the integer carrier and duplicate
layout declarations.

## Compilation experiments

The first complete typed C++ implementation retained all eleven instruction
streams and the native compiler-generated vtable. Simplifying the state
machine, replacing offset stores with rectangle fields, using the shared
texture types, and removing the old `fp_contract` pragma preserved those
matches. No handwritten vtable, assembly, new compiler flag, or new steering
pragma is used.

A standalone C version of the rectangle initializer also emits the same
252-byte instruction stream and constant values. Its first comparison scored
98.888885% because its anonymous pool starts at a different object offset;
using the repository's `functionRelocDiffs=data_value` comparison gives 100%.
The complete C++ object has the correct pool offsets as well.

The initial link scan rejected fourteen missing exported float names. The
fresh active object inventory found no other unit referring to any of them;
`localize_split_globals.py` localized those fourteen symbols. This follows
the [contributor linkage workflow](../../CONTRIBUTING.md) and the
[existing constant-pool recovery evidence](fukidasi-name-plate-recovery.md).
The compiler now generates the fourteen literals after the overlay's depth
literal in the exact original order.

Four inherited archive-name section attributes remain necessary in the
measured source arrangement. Removing them while keeping definitions after
their users moved 84 bytes into `.data`: `.rodata` became 746 bytes and
`.data` became 812. Defining ordinary const arrays before their users restored
the data layout but shortened the scene binder from 188 to 180 bytes by
sharing address materialization. An unnamed-namespace declaration/definition
variant retained the 188-byte binder but still misplaced the strings.
Restoring the existing attributes and definitions after their users restores
all bytes and relocation targets. The
[compiler-emission evidence](compiler-emission-evidence.md) and
[upstream placement notes](upstream-catchup-207.md) explain why both code and
data must be checked; source order is not historical-source evidence.

## Complete object and validation

| Section | Original range | Reported bytes |
| --- | --- | ---: |
| `.text` | `0x8008C9FC..0x8008D00C` | 1,552 |
| `.rodata` | `0x804395A0..0x804398E0` | 832 |
| `.data` | `0x8048E840..0x8048EB18` | 728 |
| `.sdata` | `0x805D2958..0x805D2960` | 8 |
| `.sbss` | `0x805D4F10..0x805D4F18` | 8 |
| `.sdata2` | `0x805D9580..0x805D95BC` | 60 |

All eleven functions match, totaling 1,552 code bytes. All 1,636 reported
data bytes match. Raw allocated section bytes and alignments agree, allowing
only the original three-byte `.rodata` and four-byte `.sdata` zero alignment
tails. All 158 relocation locations, types, and physical targets agree
(93 code, 64 data, one small-data pointer), independently of symbol indices
and relocation-table ordering. Ninja's actual linker input is the compiled
controller object, and the complete DOL reproduces original SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

Relative to the clean, retention-fresh baseline:

- Matched functions and code remain 27,508 and 4,302,440 bytes.
- Linked code remains 4,153,448 bytes.
- Matched data increases from 1,505,140 to 1,505,204 bytes; linked data
  increases from 1,502,920 to 1,502,984 bytes. The gain is fourteen float
  literals (56 bytes) and two state objects (eight bytes).
- Four previously linked fragments become one linked unit: 3,616 to 3,613.
  No function, code, or non-padding data coverage is lost.
- The last scalar's extent is corrected from eight to four bytes; the four
  zero bytes at `0x805D95BC` are linker padding before the next aligned unit.
- Retention generation adds six controller names and removes none. It also
  sorts three existing bone-rotation names without changing their membership.
- `check_pr.py --no-build` passes following the coordinated full native build.
  All 347 source-tool tests and existing portable behavior and ASan/UBSan
  suites pass. The generated exception inventory loses one `fp_contract` site.

A direct host syntax probe remains limited by pre-existing duplicate static
and nonstatic declarations in `TWindowSubStatusDisp.h`. The portable suites
above do not claim to compile this complete unit on a host ABI. Original
binaries, proprietary tools, object comparisons, and build receipts stay local.
