# PPP control rework: natural frames and remaining sender recovery

This rework starts at PR #573 head `0b3f5f5666` and merges main
`f1227326c4`. Round three replaces the staging LCP aggregate with consumed
configuration readers. It remains a partial improvement: the sender source patterns are not approved by this evidence record.
All scores below use the unit's existing GC/1.2.5n options. No compiler
flags, unit overrides, assembly, alignment directives or link tools change.

## Native stack storage

At `NetIPv4WriteHeader` (0x803FEBFC), the native frame is 0x78 bytes.
The 64-byte header occupies 0x20..0x5F, saved r26..r31 occupy
0x60..0x77, and LR is restored from 0x7C. The target does not access
0x08..0x1F as local state. Removing the inherited eight-byte padding array
alone yields a 0x70 frame, header at 0x18 and 99.810524%.

The retained implementation uses two ordinary inline helpers: one acquires
the packet checksum, and one folds and complements its carry. Their
computed return values are both consumed. GC/1.2.5n's inline return homes
reproduce the frame and header placement without an unused object, an
alias-only local, or a field invented to fill the unused stack area.
The entire function, including stack accesses, is 100% exact.

At `TLobby__sub_80400744` (0x80400744), the target frame is 0x30 bytes.
Only the prologue/epilogue access the stack: the back chain, LR, and saved
r29/r30/r31 at 0x24/0x28/0x2C. LR is restored from 0x34. No target
instruction reads or writes local state at 0x08..0x23. There are no
outgoing stack arguments or pointers to that area. Removing the guarded
array and alias gives a 0x20 frame and moves the three saved registers to
0x14/0x18/0x1C, with LR at 0x24: 99.937930%. Every difference is a stack
frame/save offset. The original local declarations cannot be inferred from
these unused slots alone. The round-two aggregate was filled and immediately
copied into scalar/pointer temporaries; round three removes it rather than
claiming that it establishes real native state.

Two ordinary inline readers consume the configuration's unsigned halfword
MRU and signed word magic value. The MRU result feeds its existing signed
range check and option write; the magic reader is used for each side's
option mask and value. Both returned values are consumed. Their inline return
homes produce the native 0x30 frame, with no local stack accesses, at 100%.
A direct-field implementation without helpers gives 0x20/99.937930%; an MRU
reader alone gives 0x28/99.937930%; reading both magic values as unsigned
words gives 0x30/99.689650%. With the signed word reader, all instructions
are exact. Signedness does not change the magic bit pattern: the result is
assigned to the existing unsigned option value. This is a plausible ordinary
source form, not evidence of the original helper names or spelling.

The two inline controls have individual removal measurements: removing either
makes LCP 90.558624%. Every setting and restoration is independently measured
in the §4 PPP register. Equivalent inline scopes are shared across the
sender/IPv4 writer, LCP initializer/setup, and adjacent LCP response handlers;
separate lifetime/propagation resets keep the intended controls bounded.
Versus main, the final source adds 44 pragmas and removes 90, including
push/pop, within the requested +44/-86 ceiling. There are still 59 setting
and reset directives, with no new pragma kind, flag, unit override or alignment.

Section 4's EXI receiver precedent is historical only; no padding exception
is claimed for either PPP function.

## Natural alternatives measured

| Function | Alternative | Function match |
|---|---|---:|
| IPv4 writer | Remove padding only | 99.810524% |
| IPv4 writer | Inline folding helper, mutate checksum argument | 99.863160% |
| IPv4 writer | Folding helper with separate sum local | 99.863160% |
| IPv4 writer | Folding helper taking high/low halves | 99.863160% |
| IPv4 writer | Helper writes checksum into header | 99.810524% |
| IPv4 writer | Nested checksum acquisition and folding (retained) | 100% |
| LCP setup | Remove padding only | 99.937930% |
| LCP setup | Shared mask-return helper for four compression flags | 85.413795% |
| LCP setup | Shared two-flag compression helper | 99.248276% |
| LCP setup | Halfword MRU and signed MRU locals | 97.731030% |
| LCP setup | Real local configuration aggregate copy | 92.800000% |
| Sender | Separate typed frame/word length, direct length clear | 90.741170% |
| Sender | Simple pointer-return length-clear helper | 99.294120% |
| Sender | Reference-return length-clear helper | 99.294120% |
| Sender | Separate word wire length (existing clear helper) | 95.682350% |
| Sender | Word argument to wire writer | 96.329414% |
| Sender | Word writer with lifetime optimization enabled | 96.329414% |
| Sender | Inline header-prepend helper and word writer | 96.152940% |

The single folding helper puts the header at 0x1C in a 0x78 frame;
the retained nested helpers place it at 0x20. Alternatives listed above
were reverted unless explicitly marked retained. Two exploratory scripted
edits initially failed compilation (an overbroad replacement in the checksum
helper and an incomplete compression-branch extraction); their corrected
versions are the scored alternatives above.

## Buffer interface

`alloc_from_buffer(B_803FADA0 *, s16)` at 0x80401B8C consumes the real
cursor/length prefix. It measures available headroom after that prefix,
moves the cursor back, increments length, and returns the same allocation.
`buffer_length(B_803FADA0 *)` at 0x80401CE0 reads its length. Both are
ordinary C++ free functions with compiler-emitted names reflected in
`symbols.txt`; neither is an extern-C stand-in for a member symbol.
The buffer prefix is shared in `PacketBuffer.h`. Every old allocation and
length caller was updated, including the other TLobby units and
`NetworkRuntime.cpp`; no buffer is cast to `TLobby` for these operations.
Round two makes the allocator return `B_803FADA0 *`, its actual argument
type, and retypes the IPv4 writer's frame argument and return similarly.
The FSM reply path reads `newbuf->buf` directly. `Strm_80405A74` is now an alias of that canonical buffer type in all five
affected TLobby units. Its cursor member is consistently `buf`; allocation,
length and IPv4-header calls no longer cast between those identical prefixes. No symbol rename is necessary: allocator
parameter types (the mangled portion) are unchanged, and the IPv4 writer
already has C linkage. No linkage or compiler symbol is newly invented. The comma-operator receiver is removed.

The sender still reuses the payload formal for the word length and still
uses the containing-prefix expression in its clear helper. Those patterns
are explicitly unresolved, not endorsed by this partial commit. The word
writer experiment was reverted; the shared wire-writer ABI is unchanged.

## Pragma measurements

Against main `f1227326c4`, added/removed `#pragma` lines in `src` change
from 69/11 to 44/86 (these counts include push/pop). Within the PPP source,
48 setting directives were removed and two checksum inline controls added:
105 settings become 59. Empty restores and redundant nested push stacks
were removed as well. In particular, `optimization_level 0` is gone.

Section 4's PPP-01 through PPP-59 rows identify every remaining directive,
function/address, independent score without that directive, and port action.
The two existing `optimization_level 3` scopes are inherited from main;
no new pragma kind is introduced. Each remaining setting was tested against
the final source, not inferred from a successful whole-unit score.
The first reduction sweep was greedy; the final measurement sweep removed
one directive at a time and restored it before the next trial.

## Final validation

`configure.py`, `ninja -k 0`, linked-unit checking, force-active generation
and checking, exception generation and checking, and `check_pr.py` against
main `f1227326c4` all pass. DOL SHA-1:
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.
The delta is +10 exact functions, +8,704 matched code bytes, +128 matched
data bytes, +34,672 linked code bytes, +1,544 linked data bytes, +1 linked
unit, and zero regressions. There are 3,617 linked units; retention remains
20,304 entries (+0/-0).

| Unit | Exact functions | Section scores | Linked |
|---|---:|---|---|
| misc/TLobby_803F8794 | 32/32 | .bss: 100.000000% (61888 bytes); .text: 100.000000% (1652 bytes) | yes |
| protocol/NetworkRuntime | 53/53 | .bss: 100.000000% (7928 bytes); .sbss: 100.000000% (8 bytes); .text: 100.000000% (8344 bytes) | yes |
| misc/TLobby_803FAEA0 | 16/16 | .bss: 100.000000% (536 bytes); .text: 100.000000% (4824 bytes) | yes |
| misc/TLobby_803FC178 | 129/129 | .bss: 100.000000% (1368 bytes); .data: 100.000000% (168 bytes); .sdata2: 100.000000% (8 bytes); .text: 100.000000% (34672 bytes) | yes |
| misc/TLobby_804048E8 | 3/3 | .bss: 100.000000% (5120 bytes); .data: 100.000000% (64 bytes); .text: 100.000000% (2036 bytes) | yes |
| misc/TLobby_804050DC | 244/281 | .bss: 100.000000% (376 bytes); .data: 100.000000% (132 bytes); .text: 67.965820% (84260 bytes) | no (unchanged) |

## Round-two probes and validation

All 59 remaining pragma settings were independently removed and rebuilt
against the round-two source; their ablation scores are unchanged, and none
is redundant. PPP-01..PPP-59 remain the individual register entries. Pragma
additions/removals versus main remain 44/86, with no new setting or scope.

The sender remains unresolved. Ordinary clear-and-return differs at the
initial reply assignment (`mr r30,r4` instead of native `addi r30,r4,0`),
99.294120% in a 0x40 frame. Direct initialization gives 99.235290% with a
0x38 frame. The native sender touches only the ABI back chain, saved LR
(old-SP+4, restored at new-SP+0x44), and r26..r31 at 0x28..0x3C. No local
state or outgoing arguments occupy 0x08..0x27. Separate typed wire lengths
and prepend-header helpers also change register allocation/lifetimes. The
retained sender remains 100%, with its original formal reuse and containing-
prefix helper unchanged; this does not establish impossibility or approval.

Every scored round-two alternative follows. Names correspond to saved
source, build log and instruction/section comparison in the external round2
log directory. LCP alternatives start `lcp-`; sender alternatives start
`sender-` or `clear-`. Frames are from the compiled side, not the target.

| Probe (source and JSON in `round2/toys/`) | Function score | Compiled frame |
|---|---:|---:|
| `clear-assign-before-clear` | 99.235290% | 0x38 |
| `clear-assign-first` | 99.235290% | 0x38 |
| `clear-opt_common_subs-on-helper` | 99.294120% | 0x40 |
| `clear-opt_common_subs-on-sender` | 98.000000% | 0x40 |
| `clear-opt_dead_assignments-off-helper` | 99.294120% | 0x40 |
| `clear-opt_dead_assignments-off-sender` | 98.941180% | 0x30 |
| `clear-opt_lifetimes-off-helper` | 99.294120% | 0x40 |
| `clear-opt_lifetimes-off-sender` | 99.294120% | 0x40 |
| `clear-opt_propagation-off-helper` | 99.294120% | 0x40 |
| `clear-opt_propagation-off-sender` | 95.882355% | 0x30 |
| `clear-reference-local` | 99.235290% | 0x38 |
| `clear-reset-pointer-out` | 99.294120% | 0x40 |
| `clear-reset-reference-out` | 99.294120% | 0x40 |
| `clear-reset-reference` | 99.235290% | 0x38 |
| `clear-reset-return-reference` | 99.294120% | 0x40 |
| `lcp-auth-block` | 99.937930% | 0x28 |
| `lcp-clean-direct-fields` | 95.634480% | 0x28 |
| `lcp-clean-mru-out-half` | 100.000000% | 0x30 |
| `lcp-clean-remove-id` | 97.144830% | 0x28 |
| `lcp-clean-remove-t` | 96.448270% | 0x30 |
| `lcp-clean-scoped-type` | 100.000000% | 0x30 |
| `lcp-compression-struct` | 95.820690% | 0x30 |
| `lcp-initialize-nested` | 99.110344% | 0x28 |
| `lcp-magic-get` | 99.627590% | 0x28 |
| `lcp-mru-block` | 96.448270% | 0x30 |
| `lcp-mru-get` | 99.662070% | 0x28 |
| `lcp-mru-half` | 100.000000% | 0x30 |
| `lcp-mru-out` | 99.937930% | 0x20 |
| `lcp-mru-reverse` | 99.724140% | 0x30 |
| `lcp-mru-signed` | 100.000000% | 0x30 |
| `lcp-mru-struct-local` | 99.724140% | 0x30 |
| `lcp-mru-struct-out` | 99.724140% | 0x30 |
| `lcp-mru-struct-return` | 93.586205% | 0x48 |
| `lcp-nested-state-s32` | 99.524140% | 0x28 |
| `lcp-nested-state-u32` | 99.937930% | 0x28 |
| `lcp-nested-state-u8` | 99.937930% | 0x28 |
| `lcp-no-padding` | 99.937930% | 0x20 |
| `lcp-options-out` | 99.006900% | 0x20 |
| `lcp-out-auth` | 99.937930% | 0x28 |
| `lcp-peer-config` | 99.627590% | 0x28 |
| `lcp-set-magic` | 99.627590% | 0x28 |
| `lcp-start-calls-s32` | 98.696550% | 0x28 |
| `lcp-start-calls-u32` | 99.110344% | 0x28 |
| `lcp-start-calls-u8` | 99.110344% | 0x28 |
| `lcp-start-out` | 99.937930% | 0x28 |
| `lcp-start-state` | 99.937930% | 0x28 |
| `lcp-state-auth` | 99.937930% | 0x28 |
| `lcp-wrapper-config-state` | 96.082756% | 0x28 |
| `lcp-wrapper-config` | 96.082756% | 0x20 |
| `lcp-wrapper-whole-out` | 96.082756% | 0x28 |
| `lcp-wrapper-whole-state` | 96.082756% | 0x28 |
| `lcp-wrapper-whole` | 96.082756% | 0x20 |
| `sender-clear-out` | 99.235290% | 0x38 |
| `sender-clear-reference` | 99.294120% | 0x40 |
| `sender-header-int-out` | 95.388240% | 0x48 |
| `sender-header-int-ref-lifetimes-cse` | 95.741170% | 0x48 |
| `sender-header-int-ref-lifetimes-propagation` | 94.388240% | 0x38 |
| `sender-header-int-ref-lifetimes` | 96.152940% | 0x48 |
| `sender-header-int-ref-no-saved` | 96.152940% | 0x48 |
| `sender-header-int-ref` | 96.152940% | 0x48 |
| `sender-header-int-return-lifetimes-cse` | 95.741170% | 0x50 |
| `sender-header-int-return-lifetimes-propagation` | 94.388240% | 0x38 |
| `sender-header-int-return-lifetimes` | 96.152940% | 0x50 |
| `sender-header-int-return-no-saved` | 96.152940% | 0x50 |
| `sender-header-int-return-word-writer` | 95.505880% | 0x50 |
| `sender-header-int-return` | 96.152940% | 0x50 |
| `sender-header-s32-out` | 95.388240% | 0x48 |
| `sender-header-s32-ref` | 96.152940% | 0x48 |
| `sender-header-s32-return-word-writer` | 95.505880% | 0x50 |
| `sender-header-s32-return` | 96.152940% | 0x50 |
| `sender-header-u16-out` | 94.741170% | 0x48 |
| `sender-header-u16-ref` | 95.505880% | 0x48 |
| `sender-header-u16-return-lifetimes-cse` | 95.094120% | 0x50 |
| `sender-header-u16-return-lifetimes-propagation` | 93.741170% | 0x38 |
| `sender-header-u16-return-lifetimes` | 95.505880% | 0x50 |
| `sender-header-u16-return-no-saved` | 95.505880% | 0x50 |
| `sender-header-u16-return-word-writer` | 95.505880% | 0x50 |
| `sender-header-u16-return` | 95.505880% | 0x50 |
| `sender-header-u32-out` | 95.388240% | 0x48 |
| `sender-header-u32-ref` | 96.152940% | 0x48 |
| `sender-header-u32-return-lifetimes-cse` | 95.741170% | 0x50 |
| `sender-header-u32-return-lifetimes-propagation` | 94.388240% | 0x38 |
| `sender-header-u32-return-lifetimes` | 96.152940% | 0x50 |
| `sender-header-u32-return-no-saved` | 96.152940% | 0x50 |
| `sender-header-u32-return-word-writer` | 95.505880% | 0x50 |
| `sender-header-u32-return` | 96.152940% | 0x50 |
| `sender-length-int-increment` | 97.223526% | 0x40 |
| `sender-length-int-point-direct-result` | 96.941180% | 0x40 |
| `sender-length-int-point-lifetimes-cse` | 96.470590% | 0x40 |
| `sender-length-int-point-lifetimes-propagation` | 95.823530% | 0x30 |
| `sender-length-int-point-lifetimes` | 97.647060% | 0x40 |
| `sender-length-int-point-no-saved` | 96.329414% | 0x40 |
| `sender-length-int-point` | 97.647060% | 0x40 |
| `sender-length-int-top` | 97.647060% | 0x40 |
| `sender-length-s32-increment` | 97.223526% | 0x40 |
| `sender-length-s32-point` | 97.647060% | 0x40 |
| `sender-length-s32-top` | 97.647060% | 0x40 |
| `sender-length-s64-increment` | 94.505880% | 0x48 |
| `sender-length-s64-point` | 97.647060% | 0x40 |
| `sender-length-s64-top` | 97.647060% | 0x40 |
| `sender-length-u16-increment` | 95.176470% | 0x40 |
| `sender-length-u16-point-direct-result` | 97.000000% | 0x40 |
| `sender-length-u16-point-lifetimes-cse` | 95.823530% | 0x40 |
| `sender-length-u16-point-lifetimes-propagation` | 95.176470% | 0x30 |
| `sender-length-u16-point-lifetimes` | 97.000000% | 0x40 |
| `sender-length-u16-point-no-saved` | 95.682350% | 0x40 |
| `sender-length-u16-point` | 97.000000% | 0x40 |
| `sender-length-u16-top` | 97.000000% | 0x40 |
| `sender-length-u32-increment` | 97.223526% | 0x40 |
| `sender-length-u32-point-direct-result` | 96.941180% | 0x40 |
| `sender-length-u32-point-lifetimes-cse` | 96.470590% | 0x40 |
| `sender-length-u32-point-lifetimes-propagation` | 95.823530% | 0x30 |
| `sender-length-u32-point-lifetimes` | 97.647060% | 0x40 |
| `sender-length-u32-point-no-saved` | 96.329414% | 0x40 |
| `sender-length-u32-point` | 97.647060% | 0x40 |
| `sender-length-u32-top` | 97.647060% | 0x40 |
| `sender-packet-s32-frame-length-off` | 97.117645% | 0x48 |
| `sender-packet-s32-frame-length-on` | 97.117645% | 0x48 |
| `sender-packet-s32-length-frame-off` | 97.117645% | 0x48 |
| `sender-packet-s32-length-frame-on` | 97.117645% | 0x48 |
| `sender-packet-s32-length-only-off` | 97.882355% | 0x40 |
| `sender-packet-s32-length-only-on` | 97.882355% | 0x40 |
| `sender-packet-u16-frame-length-off` | 97.176470% | 0x48 |
| `sender-packet-u16-frame-length-on` | 97.176470% | 0x48 |
| `sender-packet-u16-length-frame-off` | 97.176470% | 0x48 |
| `sender-packet-u16-length-frame-on` | 97.176470% | 0x48 |
| `sender-packet-u16-length-only-off` | 97.235290% | 0x40 |
| `sender-packet-u16-length-only-on` | 97.235290% | 0x40 |
| `sender-packet-u32-frame-length-off` | 97.117645% | 0x48 |
| `sender-packet-u32-frame-length-on` | 97.117645% | 0x48 |
| `sender-packet-u32-length-frame-off` | 97.117645% | 0x48 |
| `sender-packet-u32-length-frame-on` | 97.117645% | 0x48 |
| `sender-packet-u32-length-only-off` | 97.882355% | 0x40 |
| `sender-packet-u32-length-only-on` | 97.882355% | 0x40 |
| `sender-reset-global` | 99.294120% | 0x40 |
| `sender-reset-return` | 99.235290% | 0x48 |

## Round-three sender and return-width probes

The sender remains a source blocker, with its payload formal reused as a wire
length, payload-to-buffer casts, and the length-member-minus-offset helper.
A real containing allocation whose first member is the packet-buffer prefix
was tested with direct/member/array/nested-prefix addresses, pointer/reference
helpers and member accessors. The ordinary helper remains 99.294120%/0x40:
`mr r30,r4` replaces native `addi r30,r4,0`. Direct forms give
99.235290%/0x38. Existing control combinations do not make those forms exact.

Typed buffer formals with separate halfword/word/signed lengths, declaration
positions and orders, frame reassignment, inline header writers/prependers,
pointer/reference outputs, real wire-header aggregates and metadata-reset
aggregates were compiled and scored. No complete natural exact sender was
found. The 98.117645%/0x48 exploratory out-parameter candidate retained unused
inherited declarations; removing those declarations changes its result, so
that score is not evidence of an acceptable natural solution. No experimental
padding, alias-only local, control, compiler flag or type pun is retained.
The original exact sender is unchanged by round three. This does not prove
that a natural exact form is impossible or authorize the remaining constructs.

At 0x80403F4C, returning `buffer_length` naturally from the current `s16`
function gives 99.009900%. A signed/unsigned word return makes that provider
100%, but its native caller at 0x80405A74 requires a signed-halfword check.
An explicit signed-halfword conversion gives 99.738150% there: the compiler
emits `extsh` followed by `extsh.` instead of the single native `extsh.`.
Narrow local, assignment and expression variants were also tested. Retyping
`buffer_length` itself to unsigned halfword fixes the VJ return but regresses
the sender to 97.411766% and NetPapDispatch to 99.270836%. The inherited
`(s16)(s64)buffer_length(...)` therefore remains unresolved, with its old
normalization-steering comment removed.

All round-three candidate sources, successful instruction comparisons,
compiled frame sizes, per-control measurements
and gate logs are in the supplied external `round3` log directory. Its
REPORT.md and probe-table.md enumerate every scored probe. The cumulative
PR also retains legacy C-linkage spellings of five TLobby callbacks and old
opaque/offset-based callback interfaces; round three introduces none of them.
The report inventories these separately from the unresolved sender and VJ
normalization patterns. This remains a partial local rework.

The additional method/base-prefix reset probes also give 99.294120%/0x40.
The `addi ...,0` instruction is not unique evidence for a zero-offset member:
for example, exact `TLobby__sub_803FC1CC` copies its ordinary timeout formal
with `addi r29,r4,0`. Its source has no containing-member expression there.

A cumulative source audit also found the inherited alias-return local in
`pap_message_destination_80402E68`. Returning the actual message member
address directly gives NetPapDispatch 99.479164% in the same 0x38 frame;
only register allocation changes. Pointer/reference owner arguments,
reference returns, const pointer slots, and independent cast-removal probes
were tested. The alias-return local remains, is not newly introduced in round
three, and is an additional unresolved source pattern rather than an approved
exception. No claim that all PR source blockers are fixed is made.
