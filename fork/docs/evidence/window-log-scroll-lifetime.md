# Native Log construction and bounded auxiliary storage

This follows published PR #268 checkpoint
`034308446b77aba2c1df8808860a1ed81d64b4df`, including main
`6e880491f335b26239b4553f0882c04676a0a6e7`.

Log now has a real word/word constructor initializing
`TWindowMessage(layout, 30, client)`. Removing the decompiler receiver alias
and using actual members directly resolves the previously measured four
instruction vptr-installation difference. The constructor is 168/168 bytes
identical. Its existing controller-registration helper keeps its ordinary C
identity and receives `this`; no speculative member ownership is added. The
factory uses ordinary `new`. The last Message constructor ABI binding is
removed; no default constructor, pragma, compiler flag or manual table is added.

## Twelve-byte auxiliary object

The existing address-based `Scroll_8026D790` name identifies a plain object
with two floats at 0/4 and a signed frame counter at 8. Five original global
12-byte allocations invoke the same initializer. The copy routine reads the
two-float prefix synchronously and the constructor clears the counter. These
are now genuine class methods and all five allocations use ordinary `new`:
SubComCardList, MenuIconLine, Log, CustomSelect, and SymbolChatParts. Size and
field-offset assertions cover the observed layout. No TObject base, vptr,
original semantic class name, or custom destructor is inferred. The implicit
destructor is trivial. The two-float input remains an opaque `void *` carrier;
this does not assert input mutation. A const-qualified input probe changed
load/store ordering. No particular vector type or compiler override is invented.

A scan of original split relocations found 24 direct calls, all REL24 with
zero addend: five constructor calls, five copy calls (including construction),
eight counter calls, and six release calls. There were no address-taken
references. The helper addresses are 80266B04 (copy), 8026DA0C (construction),
8026D9C0 (counter), and 8026D9D0 (release). The old TWindowMenu/SubStatusDisp
method owners were incompatible with these allocations and are removed.

The counter and release protocol deliberately remain address-named, type-erased
functions. ChoiceSetting's field at 0x7C has an unrecovered positive producer;
its observed consumers do not establish complete Scroll class identity. The
counter increments a signed word at offset 8. Release tests the pointer and
positive signed flag, calls ordinary global `operator delete`, and returns the
original pointer. Both reproduce their original 16/60-byte bodies. For the
known plain scalar allocations no nontrivial destruction is required. No native
Scroll destructor or typed deletion is assigned to the unknown producer. This
retains the original protocol without pretending that caller ownership is solved.

## Qualification and remaining boundary

Complete original and compiled unrelocated text compares identically:

| Unit | Bytes | Link input |
| --- | ---: | --- |
| TWindowMessageLog_8026AA38 | 536 | source |
| text_8026A93C | 252 | source |
| TWindowSetLevelUp | 1,696 | source |
| TWindowSubComCard_80265410 | 6,068 | source |
| TWindowSubStatusDisp_802671F0 | 5,496 | source |
| TWindowSubCustomSelect | 2,488 | source |
| TWindowSubSymbolChatParts | 4,620 | original, unchanged |
| TWindowChoiceSetting | 2,160 | source |
| TWindowChoiceSetting_80249240 | 956 | source |
| TWindowSubStatusDisp_80248BE8 | 1,052 | source |
| TWindowMessageLog | 352 | source |

SymbolChatParts has matching text but remains outside the linked set because
its other sections are not recovered. Its edited source is not represented as
a newly linked implementation. The generated link rule selects the other ten
source objects. The complete DOL reproduces SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr passes
with all 27,370 exact functions and 3,576 exact linked units retained, no
code/data/address-coverage change, and clean retention at 17,612 entries.
Against fresh main 6e880491f, the combined PR retains its one extra exact
function, 600 matched code bytes, 728 linked code bytes and 328 matched/linked
data bytes. The previously qualified two four-byte linker-padding coverage
changes are unchanged.

The ABI header now has four constructor and three destructor declarations.
A source inventory finds 85 calls in 45 source units: Base 31 construction /
31 cleanup, Addition 5 / 5, and MenuIconLine 7 construction (six three-argument
calls and one four-argument call) / 6 cleanup. These functions still accept external storage
and call native entry symbols; they need genuine owner-by-owner recovery,
not mechanical casts or an invented common default constructor. This change
removes Log's final Message call and the five auxiliary raw initializers, not
that entire legacy boundary.

The [task-global second-word audit](window-task-owner.md) remains unchanged:
805D5D94 is unclaimed, not assumed padding or another pointer. The unknown
ChoiceSetting producer and broader historical interface holds also remain.
The PR stays draft and must not be marked ready or merged on this evidence.

## Subsequent main integration

Fork main `fe6cdb14138b2413778c08f21fd1851170c22ab5` is normally merged
after the published Log checkpoint
`c8302f469b23b66de719e3e1403e11fe3a1e12bd`. Both a fresh main worktree
and the integrated PR reproduce the original DOL hash and pass check_pr.
Main has 27,383 exact functions / 3,584 exact linked units; the PR has
27,384 / 3,585. Against that main snapshot the combined PR contribution
remains +600 matched code, +728 linked code and +328 matched/linked data
bytes, with the same two previously qualified four-byte padding differences.
Against the published Log checkpoint, all 14 new exact functions and nine
new linked units from main are retained with no regressions. Main's existing
four-byte StarLight conversion-pool padding coverage change is independently
reproduced by the fresh main baseline.

Retention is clean at 17,650 entries for the integrated PR (17,617 on main).
The porting inventory passes. No window source/type change or hold relaxation
is part of the merge. This qualifies that immutable main snapshot; the broader
legacy lifetime and unknown-producer boundaries above remain open.
