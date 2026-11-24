# Df2 Bringer shared scalar pool

Base: fork main `2344b179717a97c9604db931189ad6d7dc6a9cc8`.

`Df2BringerConstants.cpp` supplies the complete original-only
`auto_11_805D97D8_sdata2` range, `0x805D97D8..0x805D9850`: thirty
four-byte scalar objects, 120 bytes total. The existing range and exported
identities remain intact. The filename describes the observed consumers;
it does not recover the original source filename or historical object boundary.
This is a data-only recovery and adds no function matches.

## Original loads and declarations

A census of all 8,679 configured original and compiled objects finds exactly
two consumers. Their original objects have 58 references to this pool, all
single-precision `lfs` loads:

| Consumer | Original references | Functions | Code bytes |
| --- | ---: | ---: | ---: |
| `TObjEneDf2Bringer_80097100.cpp` | 3 | 2 | 432 |
| `TObjEneDf2Bringer_800972B0.cpp` | 55 | 41 | 11,336 |

The first consumer loads 400 and 15 for its visibility call and zero for
its animation-frame clamp. The larger consumer uses the remaining scalars
in state transitions, movement, particle timing and sampled trail geometry.
Its final two values, 0.4 and 0.7, scale trail segment control points.
`TBreakUpMdl.cpp` uses the preceding pool ending at `0x805D97D8`; it does
not reference this range.

Both consumers and the provider now include one shared declaration header.
The 300 scalar at `0x805D9820` previously had a mutable declaration and
local macros casting it to const. All four original references are loads;
the shared declaration is now `const f32`, and those macros are removed.
Both complete compiled consumer objects remain byte-identical to the fresh
baseline, including their symbols, data, and relocations.

## C/C++ trials and related recoveries

With the stock game GC/2.0 flags, handwritten C `const f32` definitions
and C++ explicitly external definitions both reproduce the exact 120-byte
`.sdata2` section with alignment eight. All thirty exported names, bindings,
sizes and offsets agree. There are no runtime relocations in this provider.
A plain C++ `const` control has internal linkage and emits no allocated
storage because it has no local uses. The production C++ definitions use
explicit external linkage and the consumers' existing C symbol linkage.
No compiler override, pragma, intrinsic, assembly or padding object is needed.

After those first compiler comparisons, the fork's
[Mylla](photon-mylla-constant-pool.md) and
[laser-light](laser-light-constant-pool.md) recoveries were checked for the
named-constant versus private-literal distinction. In those cases, moving
named definitions into their consumers could emit writable storage or
additional literal copies. Here the separate provider preserves all shared
exports without changing either consumer's expressions or pooling.

Upstream commit
[`52030419ed6fcdd6fe5010a25e32b6c782f99246`](https://github.com/zeroz41/pso-decomp/commit/52030419ed6fcdd6fe5010a25e32b6c782f99246)
folds the two Bringer code ranges together, but still declares these
scalars externally and does not assign this `.sdata2` range to that folded
unit. Its fold therefore does not supply a completed scalar provider or
establish this fork's historical ownership. No upstream source is copied.

## Complete-unit validation

The fresh unchanged-main baseline and retention check pass. After adding
the source range and running the link scanner, the native build and
`tools/check_pr.py` pass. Original and rebuilt DOL SHA-1 are
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

The complete new unit scores 100%. Allocated bytes, section size/alignment,
and all thirty four-byte global symbol sizes/bindings/offsets match.
The expanded Ninja linker command selects its compiled object exactly once
and excludes both its original object and the former automatic fallback.
Both complete consumer objects are unchanged from the baseline.

Matched data increases from 1,506,652 to 1,506,772 bytes; source-linked
data increases from 1,504,804 to 1,504,924 bytes. Linked units increase
from 3,615 to 3,616. Function, code, data and linked coverage have no
regressions; all coverage denominators are unchanged. All 3,616 linked
units remain exact, and the 20,396-name retention block has no drift.
The provider passes GCC C++98 syntax checking, and the shared header
passes C99 syntax checking. Changed-line whitespace checks pass.
