# Native ShortCut window lifetime with original setup helper retained

This follows PR #268 checkpoint
`cc0ebdc2644cd6576f38b48d249f0bfb7f37fc52`, including current main
`387621104107ed1ff8c650bf2f50ef00c6859ba4`.

## Window construction and actual producer

This is the 0x74-byte TWindowShortCut, distinct from ShortCutList and its
page indicator. It consists of Base, an opaque heading at 0x60, optional
message/symbol windows at 0x64/0x68, index word at 0x6C and borrowed shortcut
record at 0x70. Existing size and new offset assertions preserve the image.
The index remains a word value; it is not relabeled as a borrowed pointer.
The borrowed record is not assigned a speculative complete type.

Original reference inspection finds one zero-addend constructor call and no
address-taken constructor reference or descendant. In SubShortCut state 7,
the 0x74-byte producer supplies position lookup 0x73, its selected index word
and record at controller+0x40. That site now uses ordinary new through the
shared position/index/record constructor. Existing outer controller word
storage and layout lookup remain qualified interfaces.

The native constructor initializes Base with the existing descriptor, client
4 and actual position. It retains class-name assignment, global-new 0x24-byte
heading allocation, the existing type-1 heading initialization with message
0x35 and actual client, zero child slots, saved index/record and original
setup-helper call in the same order. No default Base lifetime is introduced.

## Child ownership and cleanup order

The original setup helper's text branches create a MessageQuest through
create_quest_message_window_at and store its result at 0x64. Its symbol branch
allocates 0x68 bytes, invokes ChatSymbol's existing constructor and stores the
result at 0x68. Both are existing Base-derived windows, supporting Base-window
pointer fields without inventing a different child class.

The native destructor preserves deferred close of the symbol window, then
message window, clearing each pointer afterward. It does not immediately
delete them. It then releases the opaque heading through its existing
nullable flag-1 protocol before automatic Base cleanup. The full heading
class and the children's wider legacy interfaces are not recovered here.
Native render explicitly forwards its actual receiver to the shared draw entry
point, then context to frame, entries and the qualified heading renderer.
Task update retains the existing heading protocol and Base entry/fade updates.

## Protected original helper and bounded ABI

[8026E1D4,8026E5E8) remains the original 1,044-byte input, not a source body.
Its one direct caller is this constructor; no address-taken helper reference
was found. The observed machine contract is receiver, index word and borrowed
record pointer. The call-site declaration now states those actual inputs,
while retaining the historical TWindowSubStatusDisp__sub_8026E1D4 symbol and
existing unused word-result view. No return semantics, semantic owner/name,
complete record type or original translation-unit identity is asserted.
No wrapper, alias body or implementation is fabricated for that entry.

The selected original text object remains exactly once, with identical raw
text and resolved DOL bytes. In particular, activating the ShortCut window's
own lifetime does not claim source linkage or portable completion of that
setup helper or its child constructor interfaces.

## Native data and preserved original suffix

The provisional WindowLayoutDescriptor represents [804D0AE0,804D0AF4):
extent 405/188, order 50100, entry reference lbl_804D0968 and flags 0x63.
The compiler emits the normal four-function 24-byte table at
[804D0AF4,804D0B0C); its old catalog size changes from 28 to 24 rather than
inventing a slot. Descriptor and table naturally form 44 bytes, alignment
eight and table offset 0x14. Their organization is compiler-emission evidence,
not proof of an original translation-unit boundary.

The preceding original input at [804D0964,804D0AE0) remains 380 bytes,
including the leading zero word and 376-byte entry table. The following
original input at [804D0B0C,804D0B28) remains 28 bytes, including its zero
word and ShortListCtrl table. Each is selected once and matches the original
range. Neither zero word is reassigned as padding. No manual table/padding,
alignment override or compiler control is added. Existing callback, ownership
and interface holds remain.

## Validation

Complete ShortCut text (500 bytes) and SubShortCut producer unit (1880 bytes)
are byte-identical to original objects, including constructor 180, destructor
152, render 92 and task 76 bytes. Each source object is selected once without
its original text fallback. Raw 44-byte data and resolved native text/data
ranges match current main. The setup helper and all protected original
remainders/prefixes/suffixes are verified as original inputs exactly once,
with matching bytes.

Full build reproduces DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against the previous
published checkpoint passes with +44 matched/linked data bytes and unchanged
code/function/link counts: 27,390 exact functions and 3,589 exact linked units.
Retention is clean at 17,780 names and port inventory passes. No additional
padding coverage gap occurs. Against fresh current main, the combined PR has
+600 matched code, +1220 linked code and +1132 matched/linked data bytes.

Raw Base/Addition ABI usage falls to 42 calls across 21 units (17 Base and four
Addition construction/cleanup pairs), retaining four shared bindings. This
checkpoint does not resolve the protected setup implementation, broader record
and child interfaces, CallBack's mixed callback signatures, ChoiceSetting,
task-global, Snapshot, ChallengeResult, CustomSelect or other standing holds.
PR remains draft and portable completion is not claimed.
