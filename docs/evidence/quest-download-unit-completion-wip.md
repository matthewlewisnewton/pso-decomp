# Quest-download unit completion investigation (in progress)

The claimed unit is `pso/misc/TQuestVmDownLoadServer_803E6970.cpp`, based on
fork main `554d21699c873ccf9be1b2268eba37cd3a32e48b`. All 173 native functions
now have C++ bodies, but only 161 match exactly. **This unit remains unlinked
and is not ready for a completion PR.** The exact display milestone is
recorded in [display recovery](quest-download-display-recovery.md).

## Assembly reconstruction and iteration

Initial bodies were compiled for all five missing routines. Candidate building
(`803EA428`) classifies input runs, appends synthetic or dictionary item chains,
and searches decreasing candidate lengths. Its run-emission block is shared by
several branches, including backward branches. Restoring that position and a
signed minimum count improves the relocation-sensitive comparison from roughly
74% to 94.19162%, with the original 1,336-byte extent.

Selection (`803EA9E8`) initializes tokens, constructs item/entry chains, selects
lengths, releases discarded entries, and consolidates groups. Keeping the
selection cases nested and advancing the consolidation cursor in its consuming
expression reproduces the original 1,004-byte extent. Declaration-order probes
reach 96.88844%. This is not an exactness claim.

Request accumulation (`803EE2F4`) and emission (`803EE580`) retain their native
fallbacks, name/text conversion and ID-list traversal. Their initial bodies
remain partial. The latter preserves the original unsigned-halfword comparison
with integer minus one; it is not silently normalized to `0xFFFF`.

The repository precedents studied include the earlier quest investigations,
[inline entry merge](quest-download-pr295-sol61.md),
[movie-frame allocation](pack-movie-frame-unit-flags.md),
[shape blending](creation-shape-blending.md), and
[copy propagation](indirect-scroll-offset-propagation.md). Local compiler
backend research also used the `doldecomp/mweppc` coloring implementation.
Reduced C and C++ probes, readonly-reference helper inputs, declaration orders,
address-expression forms, explicit header temporaries and supported scoped
optimization switches were compiled and compared. Adjacent compiler releases
provided no new exact functions; the pinned compiler/profile remains unchanged.
Ineffective experimental helper and optimization scopes were removed.

## Shared types and scratch lifetime

`QuestDownloadQueryTypes.h` gives the provider and data unit one definition of
the six-byte query entries, 32-entry result, and 0x990-byte workspace. Layout
assertions cover the 0x8C0 result offset, 14-byte entry offset and complete
extents. The following slot array remains a separate actual object. Native-only
address adapters retain the observed workspace-relative addressing; their
non-MWCC branches use the actual slot array directly.

`QuestDownloadScratch.h` gives the frontend, provider and data owner consistent
scratch, string-buffer and display-prefix declarations. The display prefix is
still its actual 12-character object. Two native routines retain its address
when reaching the following scratch allocation; the portable adapter names
that separate byte array directly. No encompassing aggregate is fabricated.

The existing aligned `u8[0x404]` provides storage for complete trivial scratch
objects. Before the conversion producer writes words, tagged placement
construction begins `QuestDownloadScratchWords` with 514 signed halfwords.
The producer writes at most 512, preserving the four trailing bytes. The
consumer borrows the corresponding unsigned-halfword view. Before request
emission writes IDs, placement construction begins the complete 257-word ID
array. Construction performs no initialization stores. These phases reuse
storage rather than declaring incompatible external arrays over one symbol.

The conversion borrows its input only during the synchronous call. Keyword and
fallback lookups return readonly table pointers, not input pointers. The ID
consumers synchronously walk the supplied list and do not retain that pointer.
These changes do not establish reentrant or concurrent use of this global
scratch, arbitrary malformed-input bounds, or new ownership for the remaining
opaque variable-record interfaces. Existing engine preconditions remain.

The selector return declaration is a full signed word, matching its native
sign-extended returns and caller use. Its function remains exact.

## Current comparison and validation

Direct comparisons use `functionRelocDiffs=data_value` with the unchanged
GC/1.2.5 profile. Remaining functions are:

| Native suffix/name | Match % | Compiled/original bytes |
| --- | ---: | ---: |
| `803E8924` | 98.10317 | 504/504 |
| `803E8DA0` | 95.051544 | 780/776 |
| `803E93DC` | 95.281815 | 448/440 |
| `803E95BC` | 97.5566 | 424/424 |
| `803EA428` | 94.19162 | 1336/1336 |
| `803EA9E8` | 96.88844 | 1004/1004 |
| `803EDC20` | 94.41237 | 388/388 |
| `803EDF64` | 78.625 | 888/896 |
| `803EE2F4` | 82.36196 | 668/652 |
| `803EE580` | 92.35294 | 412/408 |
| `803EF208` | 95.303925 | 808/816 |
| `803F03B4` | 99.75903 | 332/332 |

A fresh full build and `tools/check_pr.py` pass against the starting-main
baseline: +1 exact function, +704 matched code bytes, no exact-function,
matched-data or source-linkage losses; all 3,626 linked units remain exact.
The built DOL retains its original SHA-1. The new scoped placement inlining
and native address boundaries are registered in `porting-exceptions.md`;
the generated inventory is refreshed.

A private PPC differential harness loads the verified executable, relocates
only the recovered conversion routine to another address, and calls the actual
original mapping and lookup helpers. The 134,296-case run passes all
single low bytes, all 65,536 low-byte pairs in both modes, 2,000 longer
random inputs, 200 inputs of 512 words, and keyword-derived inputs with all
case combinations and four attribute patterns. Return-site observations
confirm all six keyword rows are hit on both sides. The comparison includes
the meaningful result, output bytes/count, readonly input representation and
stack/nonvolatile restoration. This bounded execution evidence does not prove
exact code or whole-unit linkage. Original binaries, table contents and
extracted instructions remain private and are not committed.

Completion still requires all twelve function differences, full allocated
section layout and relocations, source-link eligibility, and fresh complete
link/no-loss verification. No incomplete unit is added to `linked_units.txt`.

## Cache initializer exact recovery

The follow-up initializer now matches all 628 native bytes. An MWCC-only
integer address adapter reaches the actual index immediately after the actual
8,192-byte cache, without claiming an enclosing C++ object. Other compilers name
the actual index directly. The existing canonical index layout supplies the
80 bucket heads and 512 nodes. A scoped `opt_common_subs off` preserves the
native independent node-end calculation. Unsigned bucket indexing reproduces
the straight unrolled stores. After clearing the eight pages, the page cursor
is rewound to the first page's end before publishing the append bound; this
preserves its native register handoff without dummy storage or extra writes.

This iteration also tested natural inlined cache-search boundaries and parser
header/body splits; they did not improve exactness and were discarded. A private
read-only trace of the pinned compiler under retrowin32/GDB exposes the parser's
remaining four-word header difference: the offset addition reuses the output
cursor's virtual register, whereas the target needs a separate intermediate.
No compiler state or generated instructions are patched.

The same address adapter and separately scoped CSE setting improve replacement
to 95.051544%, reload to 95.281815%, and rotation to 97.5566%. Rotation uses a
bounded name-search helper that returns the stopping node and its link. It now
has the native 424-byte extent, with stack offsets and registers still differing.
The checked native initializer is an exact milestone, not whole-unit completion.
