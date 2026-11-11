# TCP protocol unit recovery (in progress)

The selected unit owns text `8041A1D8..8041ED8C` (19,380 bytes) and BSS
`805C1D48..805C1DF0` (168 bytes). Development started from fork main
`37eab6e173f40350e82c51ea91babc0507fe0317` in an isolated worktree. Its fresh
native build reproduced the original DOL and passed the generated retention
check before source changes. This is a development baseline, not final
current-main PR acceptance.

The branch was subsequently rebased onto `5146327538`. An untouched checkout
of that commit rebuilt with the pinned tools and original inputs, reproduced
the original DOL, and passed `tools/check_pr.py`. The rebased development branch
also passes that check: three new exact functions, zero regressions, all 3,622
linked units exact, and retention unchanged at 19,177 entries. TCP is still
unlinked; these checks do not waive the two remaining exact-match requirements.

The starting unit had 40 of 45 exact functions (9,756 code bytes). The current
source has all 45 definitions and 43 exact functions (10,808 code bytes), with
BSS still exact. The unit remains unlinked. Output `8041A9AC` and packet input
`8041B974` still require exact native matches; function similarity is not
claimed as recovered or source-linked code. Whole-object, source-link, DOL,
no-regression and current-main checks remain required before publication.

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

## Exact bodies and remaining native constraints

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
- Output uses one receive-window workspace. Both update-threshold tests are
  within the positive receive-space condition, as the target branch destination
  requires. Its 650-instruction stream, including every branch destination, now
  agrees apart from register choices. A previous phase split was removed after
  this control-flow audit; an identical opcode list alone was insufficient.
  The SYN option fields and final padding retain their distinct pointers.
- Packet input's best candidate has the original instruction count and differs
  in two constant/address instruction positions. A complete compiler trace shows
  the target sequence through register allocation, frame generation and final
  peephole optimization; the last scheduling pass exchanges those positions.

Output's native zero predicate uses guarded `__cntlzw` followed by an unsigned
shift. The ordinary C++ boolean conversion extracts a different bit range. Its
non-MWERKS branch uses the scalar equality comparison.

The output frame is `0x80` bytes. MWCC-only unused homes reproduce the measured
stack layout: segment bounds at `0x24`/`0x20`, MSS scratch at `0x1C`, SACK words
at `0x18`/`0x14`, and the nonvolatile save area at `0x3C`. They are compiler
storage, neither read nor initialized, and do not claim original local fields.
A port omits them. This follows the documented EXI frame-home precedent.

Scoped CSE/propagation and the inherited `-opt nocse`, `dont_inline off` and
`inline_depth(4)` settings are native emission constraints. A port should
remove these constraints, consolidate the record/API views and supply explicit
TCP sequence arithmetic, byte order and pointer-sized runtime interfaces.

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
