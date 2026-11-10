# Native LoadItemTexture lifetime and helper receivers

This follows PR #268 checkpoint
`0074c2955e74768cefd260e7c44f417d8c53cd01`.

## Construction and producers

The 0x74-byte window has Base, two state bytes at 0x60/0x61, float scales
at 0x64/0x68, a TItemTexLoad pointer at 0x6C and a borrowed GinjaTextureList
pointer at 0x70. Size and field-offset assertions preserve that image.
The camera switch retains its original cases and no default; no speculative
initialization is added.

Original relocation inspection finds exactly two zero-addend constructor
calls, no address-taken references and no descendants. Both producers now
use ordinary new with the shared position/extent/word-client constructor.
The constructor narrows explicitly at Base initialization; Main's Base
client type is unchanged. The standalone factory has one SubMag caller.
The second factory's former receiver is actually the position argument;
it is now static create(position, client), with its one ShopJudgment caller.
Shop's explicit u16 conversion is preserved before word transport. Existing
word-valued layout lookup and outer controller storage remain qualified
interfaces rather than a claim of complete portable controller recovery.

## Managed loader and borrowed list

Construction creates the actual TItemTexLoad resource under tl_07, through
the shared task-layer pointer declaration. It is not parented to the window.
Destruction queues that task's destruction before automatic Base cleanup;
it does not immediately delete it or add a new task-queue implementation.
Field 0x70 borrows the loader's internal texture list. State begins at 2;
only a successful item request sets state 1. Render assigns field 0x70 from
the readiness result before testing it and before invoking the bind helper.
No unproved initial value of field 0x70 is read or invented.

## Helper ownership and exact boundaries

The request at 80262814 formerly belonged to SubMag. All three original
zero-addend callers actually pass this texture window: two SubMag slotwin
receivers and ShopJudgment's m160, each from the factories above. It is now
address-named LoadItemTexture::sub_80262814(s32), with matching declaration,
definition, catalog and callers. The word-valued upstream SubMag getter is
preserved; interpretation as TItemData* stays at the existing load_item_icon
boundary. This does not settle that getter's broader owner/type.

The binding helper 8026287C has only the window render caller. Its typed
receiver installs the address of field 0x70 into the sprite, not the texture
list value. The flag helper 80262C2C has only the standalone factory caller
and sets byte 0x61. Shared declarations close both receiver boundaries.
The generic sprite-entry prefix remains opaque.

## Data and compiler emission

The existing provisional WindowLayoutDescriptor schema represents
[804D0058,804D006C): extent 0/0, order 38000, original entry-table reference
lbl_804D0020 and flags 0x2B. The compiler emits the native four-function
24-byte vtable at [804D006C,804D0084). The old 28-byte catalog size is
corrected; no extra virtual slot or manual table is introduced. Together
they form 44 bytes, naturally aligned to eight, with table offset 0x14.
The entry table stays original input. The zero word at 804D0084 remains
with the following opaque original suffix, including the LockOn layout
parameters. It is not assigned to this class or claimed as padding.

The key function and descriptor share the existing window unit. This is
compiler-emission evidence, not proof of an original translation-unit
boundary. Existing opt_common_subs-off and the factory's fp_contract-on
scope are retained; no compiler control, artificial reference or padding
is added. Existing wider raw ABI, ChoiceSetting, global, Snapshot,
ChallengeResult and CustomSelect holds remain intact.

## Validation

The complete text sections remain byte-identical: LoadItemTexture 892,
SubMag_802627D8 232, SubMag 3716 and ShopJudgment 4668 bytes. New data matches
its original range. Full link, exact DOL hash, address-based regression
checks, retention/port inventory, actual selected input provenance and
protected original remainders are checked before publication. This change
adds 44 matched and source-linked data bytes without code or function loss.

Current main `387621104107ed1ff8c650bf2f50ef00c6859ba4` is merged.
Its independent DHCP progress is retained: compared with the prior published
checkpoint the integrated branch has +2180 matched code, +12220 linked code,
+44 matched data and +4844 linked data bytes, three additional exact functions
and one additional exact linked unit. The LoadItemTexture family alone adds
44 matched/linked data bytes and no code/function delta. Against fresh current
main, the combined PR has +600 matched code, +1220 linked code and +1000
matched/linked data bytes, one extra exact function and two extra linked units.

Final checks report 27,390 exact functions and 3,589 exact linked units, with
17,765 retention names and no retention drift. No new padding coverage gap is
introduced. The raw Base/Addition ABI boundary is reduced to 48 calls in 24
units (20 Base and four Addition construction/cleanup pairs). Four shared raw
ABI bindings remain. Both full builds reproduce DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

Actual selected inputs contain each of the four affected source objects once,
and no corresponding original text fallback. The newly divided original data
prefix remains 84 bytes at 804D0004, and the opaque suffix remains 580 bytes
at 804D0084 through the already-source-owned LockOn table at 804D02C8. Both
are selected exactly once and match current-main original bytes. The protected
1,044-byte text remainder and data remainders 204, 532 and 204 bytes remain
original inputs once; their resolved DOL ranges are also unchanged. The original
Room, FaceType and CustomEquip data prefixes remain selected original inputs.
