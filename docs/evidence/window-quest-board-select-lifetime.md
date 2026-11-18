# Native QuestBoardSelect lifetime and explicit text forwarding

This follows PR #268 checkpoint
`0843bf00eb1cd65426dc72f0f584a17d268a5a84`, including current main
`387621104107ed1ff8c650bf2f50ef00c6859ba4`.

## Actual construction, heading and allocation producer

The 0x68-byte Base-derived window contains flags at 0x60, selection at 0x61
and its opaque heading pointer at 0x64. The existing size and new heading
offset assertion preserve the image. Original reference inspection finds one
zero-addend constructor call, from SubQuestBoard's 0x68-byte allocation,
no address-taken constructor reference and no descendant. That producer now
uses ordinary new through the shared no-argument constructor.

The native constructor initializes Base with the existing descriptor, client
4 and layout position 0x70; no default Base lifetime is introduced. It retains
class-name assignment, global-new allocation of 0x24 heading bytes, the
existing type-1 heading initialization with message 0x2B and actual client,
then flag/text/selection initialization and slot updates in original order.
The native destructor releases that opaque heading through the existing
nullable flag-1 protocol before automatic Base cleanup. No complete child
class or immediate delete of an invented type is introduced.

Selection has a signed -1 sentinel and signed index uses. An s8 field expresses
that observed state range and reproduces the original signed-byte store,
where assignment to the former u8 field changed li -1 to li 255. Existing
unsigned byte argument views and signed index casts retain their instructions;
this is not a claim that the original source declaration is uniquely proved.
All observed initialization/increment/wrap states remain in signed-byte range.

## Explicit constructor text chain and genuine slot update

Entry 0 receives the current quest name. Its existing word getter at 8024477C
now receives that entry explicitly; the returned text carrier is passed to
the shared calc_text_width(char*) declaration. Centering uses the same unsigned
width conversion and 210 - 0.5*width expression under the existing scoped
fp_contract-on control. The entry prefix is still opaque; the historical
SubComCard getter name does not establish a complete SubComCard object at that
address or uniquely recover widget ownership.

Original inspection finds one call to update_slot_display_flags, from this
constructor. Its body uses only the receiver and integer/entry operations.
The constructor now calls the actual no-argument member. The local declaration
with two floating arguments had no implementation evidence and is removed;
floating values left in registers by centering are not invented formals.
Native construction, getter/width forwarding and this member call all preserve
original bytes. Shared heading-message lookup replaces its local alias view.

Existing calls to the actual is_open/is_shortcut_active members now pass the
receiver through their shared declarations rather than no-argument C views.
Their original integer result types and all caller instructions are preserved.
The native render method uses its actual receiver directly, explicitly forwards
it to shared TWindowDD::draw_default_entry, then forwards context to frame,
heading, selection and entry drawing. A first receiver-alias rendering probe
swapped saved registers; direct native member use reproduces the original.
No compiler control or artificial reference is added to obtain that result.

## Compiler-owned data and retained original inputs

The provisional WindowLayoutDescriptor schema represents
[804D19A8,804D19BC): extent 434/184, order 50150, original entry reference
lbl_804D1848 and flags 3. The native key function emits the ordinary
four-function 24-byte table at [804D19BC,804D19D4). The catalog size changes
from 28 to 24 rather than inventing an extra slot. Descriptor and table
naturally form 44 bytes, alignment eight and table offset 0x14. This does not
prove an original translation-unit boundary. No manual table/padding,
alignment override, new pragma, intrinsic or assembly is introduced.

The 352-byte entry prefix at 804D1848 remains original. The following 28-byte
suffix at [804D19D4,804D19F0) retains its zero word and SubShortCut table at
804D19D8 as one original input. Both are selected exactly once and match the
corresponding current-main original bytes. The zero word is not claimed as
padding. Existing LoadItemTexture/AreaMap suffixes and all protected text/data
remainders and prefixes remain original inputs once, with resolved DOL bytes
unchanged.

## Validation and remaining boundaries

The entire QuestBoardSelect text (2288 bytes) and producer/getter unit
SubQuestBoard_8027D148 (160 bytes) match original objects, including native
constructor 268 bytes, destructor 104 and actual allocation producer 128.
The neighboring getter unit SubQuestBoard_8027D1E8 (72 bytes) and SubShortCut
(1880 bytes) also remain identical. Each of these four source objects is
selected once with no corresponding original text fallback. Raw 44-byte data
and resolved native text/data ranges match current main.

Full build reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against the published
checkpoint passes: +44 matched/linked data bytes, unchanged code/function/link
counts, 27,390 exact functions and 3,589 exact linked units. Retention is clean
at 17,775 names and port inventory passes. No new padding coverage gap appears.
Against fresh current main the combined PR has +600 matched code, +1220 linked
code and +1088 matched/linked data bytes.

Raw Base/Addition ABI usage falls to 44 calls across 22 units (18 Base and four
Addition construction/cleanup pairs), with four shared bindings retained.
Heading/entry-prefix ownership qualifications and the wider slot-flag/controller
interfaces remain; no unrelated controller owner is inferred from those casts.
CallBack's mixed callback signatures and the ChoiceSetting, task-global,
Snapshot, ChallengeResult, CustomSelect, AreaMap interface and other existing
holds stay open. PR remains draft; portable completion is not claimed.
