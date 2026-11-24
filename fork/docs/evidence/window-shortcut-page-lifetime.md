# ShortCutList and its separate page-indicator lifetime

This follows PR #268 checkpoint
`ce49598e556910ad347b1574739363a873a4ec34`, including main
`fe6cdb14138b2413778c08f21fd1851170c22ab5`. It resolves the bounded
ShortCutList deferral from the equipment-window follow-up.

## Plain page-indicator ownership

The initializer at 8026CB44 belongs to a separate 12-byte allocation, not the
0xA0-byte TWindowSubComCardList window. Six original zero-addend REL24 calls
come from global `new(12)` sites: SubComCardList twice, then ShortCutList,
StatusDisp, DuelResult and HelpItem. No address-taken initializer reference or
incompatible receiver was found. Five draw/input/release caller families
correspond to those owners; release results are ignored and the flags are 1.

The new address-based `PageIndicator_8026CB44` has signed page/count bytes
at 0/1, two padding bytes, a signed client word at 4, and a float animation
phase at 8. Size and offset assertions cover the layout. It has no TObject
base, virtual function, custom destructor or invented original semantic name.
The initializer becomes its genuine constructor and all six allocation sites
use ordinary `new`. Its implicit destructor is trivial. The generic nullable
release keeps the positive-flag check, calls actual global `operator delete`,
and returns the original storage pointer. Its shared interface now takes and
returns pointers, replacing the integer transport and implicit live-r3 delete
call; no deleting-destructor identity is invented.

The constructor uses actual signed-byte page/count parameters and a word client.
This is an evidence-supported reconstruction, not unique proof of the original
signature: the stores and consumers are byte-wide, all constant arguments fit
signed bytes, and every dynamic original caller explicitly sign-extends its
value. ShortCut's row and both SubComCard counts retain their explicit `s8`
narrowing. The actual compiler-generated symbol is
`__ct__22PageIndicator_8026CB44FScScl`; no alternate-width alias is borrowed.

A word/word constructor variant reproduced the helper body and most callers
but changed register homes in the extended SubComCard constructor. The signed
byte variant preserves every observed call boundary and reproduces that unit
as well. The width interpretation is supported by the caller/field evidence
above, not inferred from this register allocation result alone.

Drawing, input and phase decay use one shared page type; drawing also uses
the existing real TWindowDrawContext fields, replacing local layout replicas.
The five owning windows share these declarations. Their existing word-valued
allocation handles remain unchanged. Existing byte-prefix reset/selection and
byte-zero reader interfaces remain bounded legacy helpers; this change does
not assign their current window-owner labels to the new class or claim those
wider interfaces are fully recovered.

## Native ShortCutList window

ShortCutList now initializes MenuIconLine directly and uses a native destructor
with automatic base cleanup. It releases its separate page allocation before
the base destroys its own children. Rendering uses the actual window members;
the task explicitly calls the base task implementation. Its state remains
size 0x8C, with the page handle at 0x88. No default constructor is introduced.

The selected-index argument is a signed word, used for `/4` and `%4`, not a
pointer. The factory is a real static `(void *position, s32 selection)`
function. Its sole caller fetches layout slot 0x72 and passes that pointer
explicitly, replacing the false member call on a cast layout pointer.
The factory uses ordinary `new`; the native window constructor creates its
own page indicator with the observed row narrowing.

The compiler owns the 28-byte table `[804D1A20,804D1A3C)`. It contains five
function slots: destructor, task, render, inherited TObject shadow and inherited
MenuIconLine vfunc_6. The old 32-byte catalog entry included a separate zero
tail. The four bytes `[804D1A3C,804D1A40)` remain outside the claim, in the
selected original input `auto_07_804D1A3C_data.o` (28-byte data, alignment 4).
Its first four bytes are zero with no relocation; the following table is
unchanged. No padding/table bytes or alignment override are written by hand,
and this checkpoint introduces no address-coverage loss.

## Qualification and remaining holds

Complete original/compiled unrelocated text is identical, and every listed
unit is selected as a source link input:

| Unit | Bytes |
| --- | ---: |
| text_8026C664 | 1,272 |
| TWindowSubComCardList | 1,744 |
| TWindowSubStatusDisp_80281198 | 1,660 |
| TWindowDuelResult | 1,868 |
| TWindowHelpItem_80255AB4 | 832 |
| TWindowSubShortCutList | 936 |
| TWindowSubShortCut | 1,880 |

The complete DOL reproduces SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr retains
all 27,384 exact functions and 3,585 exact linked units with zero code or
address-coverage regressions. The new table adds 28 matched/linked data bytes.
Retention is clean at 17,668 names (+5 additions, -1 renamed stale initializer);
the porting inventory passes. Against fresh main fe6cdb141 the combined PR
retains +600 matched code, +728 linked code and now +460 matched/linked data
bytes, with the previously qualified five four-byte padding gaps unchanged.

The raw ABI inventory drops from 79 calls across 41 source units to 77 across
40 units, removing ShortCut's MenuIconLine construction/cleanup pair. The six
additional auxiliary raw initializer calls also disappear. The header's four
constructor and three destructor bindings remain needed elsewhere. Parent
window lifetimes outside ShortCut, the existing prefix interfaces, ChoiceSetting's
unknown 0x7C producer and task-global word 805D5D94 remain held. The PR stays
draft and must not be marked ready or merged on this checkpoint.
