# Native AreaMapDisp lifetime with retained interface holds

This follows PR #268 checkpoint
`3c0c5698a2ed42e77ea7a8a820e6d0413968ab83`, including current main
`387621104107ed1ff8c650bf2f50ef00c6859ba4`.

## Window lifetime and actual producer

The 0x78-byte AreaMapDisp window consists of Base, three float scroll/zoom
values at 0x60/0x64/0x68, radar-active state at 0x6C, an opaque heading
pointer at 0x70 and owned text storage at 0x74. Existing size and added offset
assertions preserve that image. Scroll fields now have their actual float
types in both visibility and manual-scroll units.

Original reference inspection finds one zero-addend constructor reference,
from AreaMap's allocation of 0x78 bytes, no address-taken constructor reference
and no descendant. That actual producer now uses ordinary new through the
shared no-argument constructor. Base receives the existing descriptor,
explicitly narrowed local client and layout position 0x59; Main's client
types are unchanged. The native destructor performs the existing own cleanup
before automatic Base cleanup, without a default Base lifetime.

## Text, opaque heading and radar ownership

The constructor obtains either the generated count label or current floor
name, measures it, obtains length+1 bytes, and copies the terminator-inclusive
text into field 0x74. This is its only observed positive producer. Destruction
releases that storage and clears the field before radar and heading cleanup.
The char* field expresses character storage; allocation/release remain the
original direct global operator new[]/operator delete[] protocol. This is not
an activated typed-array new/delete expression or a complete portable string
interface recovery. Original allocation-failure behavior is preserved.

The heading is opaque global-new 0x24 storage, initialized by the existing
type-1 heading protocol using the copied text and actual client. Destruction
retains the nullable flag-1 release protocol. No complete child class is
invented. The original order of releasing text, clearing active radar state,
releasing heading and Base cleanup is retained.

Field 0x6C is initialized to zero, set/cleared by visibility transitions and
tested by the destructor. Radar/controller globals are cleared only when
active. The actual receiver is now explicit at both visibility getter calls.

## Measured interface holds, not matching exceptions

The shared Base getter returns u8. Using that declaration changes the two
original word comparisons into low-byte tests. The existing legacy s32
result view is retained with an explicit Base receiver, while Base's shared
u8 type stays unchanged. The callee computes a boolean result, but this is
still a qualified machine ABI boundary, not a complete portable C++ contract.

The existing local string-copy declaration `s32 strncpy(int,int,void*)` and
its word transports remain held. A canonical char*/const-char*/size_t probe,
even with direct raw allocation, combined length+1 into a saved register and
changed three constructor instructions. A typed new-char-array probe did
not reproduce the original either. These variants are not activated, and no
volatile storage, artificial reference or compiler control is introduced to
force their layout. The legacy length helper's explicit const-char* input
reflects observed text access; its historical owner/name remains qualified.

Existing render is retained, including its no-argument draw-context view and
legacy helper casts. Explicit canonical draw forwarding preserves size and
semantics but exchanges the two saved registers, so it is not activated here.
The window lifetime recovery does not settle those pre-existing interfaces.
The heading, entry prefixes and surrounding helper ownership also remain
qualified. This checkpoint must not be described as portable completion.

CallBack was investigated but deferred: its six factory callers and dynamic
wrapper's two targets mix no-argument and window/context drawing declarations.
Closing only the allocation site would not establish one source-correct
callback contract; no function-pointer casts are added to conceal it.

## Native data and retained original suffix

The provisional WindowLayoutDescriptor represents [804D0FC0,804D0FD4):
extent 610/188, order 50150, literal null entries and flags 3. The native key
function emits the ordinary four-function 24-byte table at
[804D0FD4,804D0FEC). The catalog's old 28-byte size is corrected rather than
inventing an extra slot. Descriptor and table naturally form 44 bytes,
alignment eight and table offset 0x14. No manual table or padding is added.
This source organization does not prove an original translation-unit boundary.

The following original input is 28 bytes at [804D0FEC,804D1008), including
the zero word and SubComCard's table at 804D0FF0. It remains selected once,
byte-identical to the corresponding original suffix; the zero word is not
claimed as padding. All previously protected original remainders and prefixes
remain unchanged and selected once.

## Validation

The entire AreaMapDisp text (1604 bytes) and AreaMap producer/manual-scroll
unit (828 bytes) are identical to original objects, including native constructor
252 bytes, destructor 148 and actual allocation producer 112. Each source
object is selected once with no original text fallback. Raw 44-byte data
matches its original range. Resolved lifetime, helper/data and protected DOL
ranges also match current main.

Full build reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against the previous
published checkpoint passes with +44 matched/linked data bytes and unchanged
code/function/link counts: 27,390 exact functions, 3,589 exact linked units.
Retention is clean at 17,770 names and port inventory passes. No new padding
coverage gap appears. Against fresh current main, the combined PR has +600
matched code, +1220 linked code and +1044 matched/linked data bytes.

The raw Base/Addition ABI boundary is reduced to 46 calls across 23 units
(19 Base and four Addition construction/cleanup pairs), retaining the four
shared bindings. All ChoiceSetting, task-global, Snapshot, ChallengeResult,
CustomSelect, callback and wider interface holds remain; PR stays draft.
