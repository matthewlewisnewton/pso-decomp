# Complete quest-download provider

The claimed `803E6970..803F0C50` range now has **173/173 exact C++ functions**,
covering all 41,696 native instruction bytes. All owned read-only data,
compiler-generated switch tables and BSS match. All three recovered object
groups are admitted to the production source link. The full linked DOL retains
its original SHA-1, `0d85744b51d7379efb025a943d0cd5aaae2191a3`.

## Native object layout

| Source suffix | Text range (exclusive end) | Functions | Read-only data | Switch tables | BSS |
| --- | --- | ---: | ---: | ---: | ---: |
| `803E6970` | `803E6970..803E9A24` | 59 | 1,744 | 156 | 0 |
| `803E9A24` | `803E9A24..803ED0CC` | 59 | 0 | 1,044 | 40,000 |
| `803ED0CC` | `803ED0CC..803F0C50` | 55 | 0 | 36 | 9,336 |

Ordinary compiler-generated switch tables align each object contribution to
eight bytes. This reproduces the original four-byte gaps at
`804FC8F4..804FC8F8` and `804FCD0C..804FCD10`. A combined object cannot retain
these boundaries with its ordinary table emission. No hand-written switch
tables, artificial references or padding objects are used. The first object's
1,738 emitted constant bytes plus six alignment bytes cover its 1,744-byte
read-only range. The pool belongs with its initializer in the second group;
the final group owns the remaining BSS.

These are evidence-backed layout groups, not claims about original filenames.
`QuestDownloadInternal.h` shares real layouts, declarations and inline helpers.
Function definitions follow native address order. The final group's BSS
follows its functions: moving it earlier changes address materialization in
`803EE580`, `803EE718` and `803EE828`. Every native function, allocated section,
alignment and relocation is checked against freshly split original objects.
The inherited GC/1.2.5 middleware profile is unchanged.

## Reconstruction and matching

Initial C and C++ bodies were compiled for all missing routines, followed by
comparison-driven revisions of the cache, parser, candidate, selection and
request paths. The final fourteen newly exact functions relative to current
main are the cache mover/replacement/rebuild/rotation/initializer, candidate
builder, selector, display formatter, input decoder, lookahead converter,
request accumulator/emitter, primary-record remover and entry enumerator.
The previously exact functions and neighboring frontend functions are retained.

The principal source constraints are:

- Cache initialization uses the real page array and canonical name index.
  Independent node-end calculations preserve the native unrolled stores.
  Bounded name lookup returns both the stopping node and its link. The caller
  copies and terminates the name before the search; distinct input and record
  lengths restore rotation's native register lifetimes.
- Rebuild forwards through fixed-image and byte-count ARAM read boundaries.
  The cache mover borrows a non-owning record view. These actual call boundaries
  reproduce the native temporary and name-buffer stack offsets.
- Replacement sequences the length arithmetic before the tail move. Six
  inherited scalar declarations remain an explicit matching constraint:
  removing them shrinks the frame from 104 to 80 bytes. They do not establish
  original source declarations; ports should remove them.
- The header parser advances the output through a borrowed live cursor; the
  input decoder carries its actual pending lead-byte state. Their scoped
  inlining and propagation settings preserve the native copies and stores.
- Candidate construction retains the shared backward emission branch,
  signed minimum spans, list-tail handoffs and the real workspace address.
- Selection separates validation and pruning cursors and consumes the result
  of the actual best-entry call through `select_download_length`. The leading
  slot is assigned to `walk`, and both its span and flag are read through that
  cursor. Reading the flag through `slot` instead lets the forward peephole
  pass fold its load into an earlier address addition. The final 1,004 bytes
  and 80-byte frame match.
- Request emission preserves the native unsigned-halfword comparison with
  integer minus one. It is not silently changed into a comparison with
  `0xFFFF`. Scratch construction begins the real ID-array lifetime.
- Whole-record removal uses the actual negative displacement and a borrowed
  length boundary. Its source is strictly after the backing page's first byte
  because this path follows a nonempty record. Even the helper's backward
  branch can therefore form `source - 1` within that same page. This is a
  bounded tail-shift interface, not a generic array-start copy routine.

### Resolving the last four bytes

The earlier accumulator had every body instruction and register correct, but
its two buffer-address materializations were reversed. A complete private
source link differed in only four bytes. Another source form had the right
instruction order but rotated three saved registers. Read-only traces of the
unmodified compiler and an allocator replay reproduced these alternatives.
Declaration permutations, typed views, call boundaries, expression forms,
scheduling models and neighboring compiler releases did not solve both effects.

The successful alternative disables automatic lifetime splitting as well as
propagation for this function. The first copy and encoding retain their actual
branch-local pointers; wide conversion and the final request use the real
global buffers directly. Removing the obsolete wide-pointer declaration is
essential: leaving it unused retains a four-byte stack slot and enlarges the
frame to 112 bytes. The cleaned source has no such local or pointer-borrowing
helper and matches all **652 bytes**, including the native **104-byte frame**.
The former accumulator inlining controls are also removed. Only the two
scoped optimizer controls remain, registered in `porting-exceptions.md`.

No compiler state, generated instruction, object or executable was patched.
No diagnostic mask intrinsic, dummy search mutation or experimental wrapper
is retained. The source itself produces the exact result with the stock tools.

## Shared types, storage and ABI

`QuestDownloadQueryTypes.h` unifies six-byte query entries, the 32-entry result
and the 0x990-byte workspace across the provider and data owner. Assertions
cover the 0x8C0 result offset, 14-byte entry offset and complete extents.
The following slot array remains its own object. Native-only integer-address
adapters preserve the observed workspace-relative calculation; other compilers
name the actual slot array directly.

`QuestDownloadScratch.h` gives the frontend, provider and data owner consistent
scratch, string-buffer and display-prefix declarations. The prefix remains
its actual twelve-character object. Native address adapters preserve access
to the following allocation; portable branches name the separate byte array.
No encompassing owner is fabricated.

Tagged placement construction starts complete trivial objects in the existing
aligned 0x404-byte scratch allocation. Conversion uses 514 signed halfwords,
writing at most 512 and preserving the trailing four bytes. Its consumer reads
the corresponding unsigned-halfword representation. Request emission starts
the complete 257-word ID array. Construction adds no initialization stores.
These phases reuse real storage rather than declaring incompatible arrays over
one symbol. The synchronous consumers do not retain the borrowed input/list.

`QuestDownloadCharacter.h` shares the recovered converter and classifier
interfaces with all affected frontend callers. The helper at `803E6188`
explicitly receives the conversion result in r3; the old no-argument declaration
had relied on the previous call leaving it there. The selector's signed-word
return declaration agrees with its native sign extension and caller use.
All sixteen neighboring frontend functions remain exact.

The recovery retains engine preconditions for page bounds, variable records,
shared global scratch and serialized use. It does not claim general malformed
input validation, reentrancy, or complete ownership recovery for opaque legacy
interfaces. Existing direct ARAM/clock boundaries and provisional names remain
bounded porting obligations, documented in the exception register.

## Validation

Fresh original objects and `build/GPOE8P/config.json` were generated from the
checked-in splits and symbols with the pinned tools and original input DOL.
The three direct comparisons use `functionRelocDiffs=data_value` and report
59/59, 59/59 and 55/55 exact functions, with every allocated section at 100%.
`link_units.py scan --write` admits exactly these three source groups and adds
71 required retention names, with no stale removals.

The production link succeeds and passes the original DOL SHA-1 check.
`tools/check_pr.py` passes against a freshly rebuilt and validated current-main
baseline, `b10ff5980cc382f189530cc462b7e77289eae54d`:

- 14 newly exact functions and 9,308 newly matched instruction bytes;
- 2,980 newly matched data bytes;
- 41,696 instruction bytes and 52,316 data/BSS bytes newly source-linked;
- all 3,626 linked units exact, zero regressions and zero pending candidates;
- 19,276 retention names with zero missing or stale entries;
- generated porting-exception inventory current, retaining all 521 upstream
  catch-up records.

The reported total-data count decreases by eight because the two four-byte
inter-object alignment gaps no longer belong to the old combined data range.
The address-based checker classifies both as padding; their actual linked bytes
and every executable section address/extent are preserved. This is no data loss.
The glyph tables were already present in the source; their existing objects
are named in the split symbol map without adding extracted assets.

Additional bounded differential checks performed during reconstruction:

- 3,000 final accumulator cases: native `strlen`/`strncpy`, controlled
  conversion/emission callbacks, callback arguments, buffers, multi-entry
  requests and nonvolatile/stack restoration all agree.
- 3,000 final selector cases: allocation failures, candidate selection,
  consolidation, callback arguments, slot/node state and preserved registers.
- 134,296 converter cases using actual original mapping/lookup helpers:
  all low bytes, every low-byte pair in both modes, longer/random and maximum
  length inputs, and all keyword rows under case/attribute combinations.
- 91,455 portable record-tail helper comparisons with `memmove` under
  AddressSanitizer and UndefinedBehaviorSanitizer, within its documented
  strictly-after-array-start source precondition.

These execution checks supplement exact object and full-link validation;
they are not proofs of arbitrary-input safety. Extracted binaries, data tables,
debugger dumps and search artifacts remain private.

## Research used

Repository precedents include [inline entry merging](quest-download-pr295-sol61.md),
[movie-frame register allocation](pack-movie-frame-unit-flags.md),
[copy propagation](indirect-scroll-offset-propagation.md),
[full-width argument temporaries](twindowdd-member-standins.md), and
[cast-technique register allocation](cast-technique-6x47-register-allocation.md).
The [display recovery](quest-download-display-recovery.md) and earlier quest
cache/parser evidence retain their bounded behavioral findings.

External primary references include [TWW register allocation notes](https://github.com/zeldaret/tww/blob/main/docs/regalloc.md),
[mwcc-debugger](https://github.com/cadmic/mwcc-debugger),
[MWCC compiler notes](https://github.com/MarkMcCaskey/decomp-scripts/blob/main/mwcc-compiler-notes.md),
and the reconstructed compiler backend in [mweppc](https://github.com/doldecomp/mweppc).
Compiler traces informed hypotheses; only successful stock-compiler source
comparisons establish the final matching result.
