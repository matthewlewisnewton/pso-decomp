# TCP protocol unit recovery

The selected unit owns text `8041A1D8..8041ED8C` (19,380 bytes, 45 functions)
and BSS `805C1D48..805C1DF0` (168 bytes). All 45 functions and the BSS match
with the unmodified pinned GC/1.2.5n compiler. The complete unit is linked from
C++ source; no assembly or patched compiler/object output is used.

Development started from fork main
`37eab6e173f40350e82c51ea91babc0507fe0317` in an isolated worktree, then rebased
onto `5146327538ef67c0077c30664309f9cd48fabc86`. An untouched checkout of that
commit rebuilt with the pinned tools and original inputs, reproduced the
original DOL, and passed `tools/check_pr.py`; its report is the final comparison
baseline. The starting unit had 40 exact functions (9,756 code bytes).

Final acceptance checks are recorded below. Function similarity alone is not
used to establish whole-object ownership or source linkage.

## Investigation and provenance

The initial close body was written from the original instructions and tested
as C++ and C. Subsequent recovery adapts upstream `NetTcp.c` and
`NetTcpState.h` at
[`b0b44cbda23b206e1e5457a0e3711e0c0dd48bb8`](https://github.com/zeroz41/pso-decomp/commit/b0b44cbda23b206e1e5457a0e3711e0c0dd48bb8).
The MIT contributor notice is retained under `third_party/LICENSES/` and the
adaptation is listed in `third_party/README.md`.

The reconstructed control-block stride is `0x544`; the global state is
`0xA8` bytes. These are bounded native record views, not evidence that the
legacy `TLobby` and `TUdpSocket` names own TCP state or packet objects.
The new output, close and input bodies call unresolved native exports through
explicit C ABI declarations instead of casting TCP and packet records to
legacy C++ classes. Their linker spellings remain provisional. Existing
overlapping private views and 32-bit callback/address words remain
interface debt. In particular the SACK lookahead at `0x320` overlaps the
following accounting fields; the typed five-entry active array does not
establish a separately allocated sixth active range.

The original assembly corrects two upstream draft boundaries: the options
parser passes the TCP header to `8041D584`, and output passes both sequence
endpoints to `8041D398`. Neither draft's omitted/misidentified argument is
used as ABI evidence. The raw draft also misplaced the no-send return inside
the retransmit-counter condition; its corrected research variant returns before
the send label when no send condition applies.

Relevant prior investigations include
[pack_movie_frame](pack-movie-frame-unit-flags.md),
[character-select inline temporaries](chr-select-slot-clamp-inline.md),
[Moja compiler traces](moja-compiler-tracing.md),
[EXI Ethernet](exi-ethernet-unit.md), and the adjacent
[socket runtime draft](https://github.com/matthewlewisnewton/pso-decomp/pull/457).
The compiler pass logic was also inspected in `doldecomp/mweppc`.
Auxiliary GC/1.2.5 debugger traces explain allocation and scheduling; all
acceptance comparisons use the unmodified pinned GC/1.2.5n executable.

## Exact bodies and native constraints

- Close `8041B5C0` is exact. Its local event record carries the handle and
  callback context through both publications and reproduces the native frame.
  The listener index retains its original signed-short extension before the
  comparison with `0xFFFF`.
- Sequence accounting `8041D398` is exact and retains signed sequence-difference
  comparisons and the native segment walk.
- Options parsing `8041D0C8` is exact. Byte indexing of the eight-byte SACK
  records with scoped common-subexpression optimization produces the native
  strength-reduced cursor. The typed indexed trial and the direct named cursor
  trial have different register assignments. Ordinary C mode does not fix them.
- Output `8041A9AC` is exact (2,600 bytes). Both update-threshold tests stay
  within the positive receive-space condition. A branch-destination audit
  removed an incorrect phase split; an identical opcode list alone was
  insufficient. SYN option fields and final padding retain distinct pointers.
  A signed-word retransmission-result temporary preserves call timing and
  value while producing the final native register allocation.
- Packet input `8041B974` is exact (5,972 bytes). The branch audit corrected
  two upstream draft scopes: overlapping data still clears FIN and requests an
  ACK when no reassembly call is needed, and repeated FIN does not advance the
  receive sequence again. Signed-short option length, short reassembly offset,
  and the short segment-length snapshot retain the native narrowing boundaries.

## Accept notification boundary

`SocketEvents.h` now declares `80422AB8` for both input and its provider in the
already-linked socket runtime. Both index arguments are signed shorts. The
caller's index calculations remain `int` until the call; the provider keeps an
explicit word promotion in the callback-index copy, `i2 = (int)idx`. The
provider's complete 42-function object remains exact, so this is a shared
interface correction rather than an incompatible private call view.

This boundary resolves input's final two instruction positions. With short
caller locals and a word-width first formal parameter, the initial scheduler
already produces the target sequence. Register allocation then deletes two
argument moves and clears the block's `fScheduled` flag; the last scheduler
exchanges the constant load and low-address instruction. With word-width
calculations and short formal parameters, argument normalization does not leave
those moves. The native callback block retains its initial schedule. Traces of
GC/1.2.5 explain this mechanism; the unmodified pinned GC/1.2.5n validates the
complete input match and the unchanged provider.

Output's native zero predicate uses guarded `__cntlzw` followed by an unsigned
shift. The ordinary C++ boolean conversion extracts a different bit range. Its
non-MWERKS branch uses the scalar equality comparison.

The output frame is `0x80` bytes. MWCC-only unused homes reproduce the measured
stack layout: segment bounds at `0x24`/`0x20`, MSS scratch at `0x1C`, SACK words
at `0x18`/`0x14`, and the nonvolatile save area at `0x3C`. They are compiler
storage, neither read nor initialized, and do not claim original local fields.
A port omits them. This follows the documented EXI frame-home precedent.

Output uses scoped CSE/propagation constraints, speed optimization, and disables
loop-invariant motion, strength reduction and loop unrolling. Direct byte
addressing of the state flags and a named fragment-length byte offset retain
the native indexed loads/stores under those settings. A `u16` header-length
workspace preserves the measured 20-byte header operations. Distinct SACK
length and receive-window workspaces, and declaration ordering of uninitialized
locals, reproduce allocation without binding physical registers. The connection
index is ordinary subtraction of two pointers into the control-block array;
the compiler emits the native constant division by its `0x544` element stride.

The experiments first compiled C++ and C, then compared instruction operands,
branch targets, frame layout and native compiler traces. Repo precedents above
informed trials of inline helpers, scalar temporaries, scoped passes and frame
homes. All optimizer-pass combinations tested with the older expression forms
still differed; disabling the loop passes required the explicit indexed address
forms before temporary lifetime and declaration-order trials reached an exact
match. These are measured emission constraints, not a claim to the original
source spelling or original pragma choices. No inline assembly, register-bound
variables, or post-compile instruction edits are involved.

The scoped settings and inherited `-opt nocse`, `dont_inline off` and
`inline_depth(4)` are native emission constraints. A port should remove them,
consolidate the record/API views and supply explicit TCP sequence arithmetic,
byte order and pointer-sized runtime interfaces.

## Native result-view debt

The local route-send declaration retains the signed-short result view already
used by the matched reset sender. Its current provider definition returns
`s32`. Output and its native callers also retain the measured short-status
normalization. A trial using a full-word route result with explicit short
checks, and a full-word output result, changed output, reset, send and connect
instructions. This is a bounded inherited interface discrepancy, not evidence
that the provider has a different source-level signature. A port must give the
provider and every caller one shared declaration and make the protocol status
conversion explicit.

## Final native acceptance

Against the independently rebuilt current-main baseline `5146327538`:

- `tools/check_pr.py`: PASS, including the native build and original DOL SHA-1
  `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- Five new exact functions, +9,624 matched code bytes, zero regressions.
- Complete source-linked coverage gains the full 19,380 code bytes and 168 BSS
  bytes; all 3,623 linked units are exact. No further unlinked exact candidates.
- Whole-object checks pass for owned sections, global symbols, data layout,
  section sizes/alignment and function order. Native instruction comparisons
  include relocations; the final DOL hash checks the resolved linked result.
- The independent unfiltered raw-report audit (`require_zero_loss`) finds zero
  lost code/data/function ranges for coverage, exactness and source linkage.
- Source-only checks pass: Python syntax, all 346 synthetic tool tests,
  portable behavior tests and AddressSanitizer/UndefinedBehaviorSanitizer runs.
  The generated porting-exceptions inventory is current and changed-line
  whitespace checks pass. Portable tests cover their existing test targets;
  TCP acceptance above is native binary verification.
- Generated retention has 19,205 entries: all 19,177 main entries remain and
  28 TCP symbols are added. `force-active --check` reports no drift.

The shared accept-event provider remains exact across all 42 functions. Existing
native layout and route-send result-view debt above remains explicit; binary
acceptance does not claim a complete portable networking implementation.
