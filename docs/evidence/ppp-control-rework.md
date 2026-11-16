# PPP control rework: partial recovery

This rework starts at PR #573 head `0b3f5f5666` and merges main
`f1227326c4`. It is a partial improvement; the remaining LCP padding and
sender source patterns are not approved by this evidence record.
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
these unused slots. The inherited array/alias remain unresolved; this is
not a claim that natural recovery is impossible.

Section 4's `TLobby_80429598` EXI receiver precedent records "four guarded
unused byte arrays." It is relevant history, not approval of the LCP array.
Only Matt can rule on retaining this construct.

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
Legacy byte-pointer buffer boundaries remain where their broader interface
has not been recovered. The comma-operator receiver is removed.

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
