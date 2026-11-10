# Native CustomEquip lifetime and CustomSelect helper ownership

This follows PR #268 checkpoint
`badb5f5a181b272ca3ec458e1eab4101105a5871`, including current main
`224eb99838471c243b20c305eddac75e7ff76c8f`.

## Actual window construction and allocation producer

TWindowSubCustomEquip is 0x70 bytes: Base, its existing flag/selection
bytes, halfword counter, word at 0x68 and opaque heading pointer at 0x6C.
The existing size and new heading-offset assertions preserve the image.
No descendant or additional constructor/address-taken reference was found.

The sole original producer is TWindowSubEquip_80275C0C, allocating 0x70
and forwarding its controller's word client/slot. That site now uses ordinary
new TWindowSubCustomEquip through the shared s32 constructor declaration.
The native constructor narrows explicitly at Base initialization and retains
the original halfword assignment at 0x20. Main's Base client types are not
widened. Descriptor, position lookup 0xF, class name, own fields and palette
refresh retain their original order.

Native destruction releases the heading through its existing protocol and
automatically cleans up Base. Render is a genuine native method, forwarding
its actual receiver to the shared draw-context entry point. No default Base
lifetime or additional virtual slot is introduced.

## Opaque owned heading protocol

The heading producer allocates 0x24 bytes with global new, then invokes the
existing type-1 initializer with message 0x23 and client. The returned storage
is assigned to the pointer at 0x6C. Destruction invokes the existing nullable
release with flag 1 before Base cleanup. The native constructor explicitly
forwards storage/text/client through that initializer and shared message
lookup; no complete child class is invented.

Field 0x6C is void* rather than an integer or speculative SubStatusDisp*.
Historical SubStatusDisp names remain qualified legacy interfaces for child
initialization, rendering, state update and release. This does not claim a
full 0x74-byte SubStatusDisp object in the 0x24-byte allocation, nor recover
its complete portable C++ lifetime. The window's ownership and matching
initializer/release protocol are preserved without replacing them with a
native delete of an unproved type.

## Correct selection-helper receiver and result

The function at 80277290 formerly belonged to CustomEquip, although it reads
0x70, 0x71 and 0x78, beyond that class's 0x70-byte extent. Original reference
inspection finds exactly two direct zero-addend calls, both in SubComCardList
state 4. Both pass f2C, whose positive producer in state 3 allocates 0x84 and
initializes the existing TWindowSubCustomSelect object.

Those offsets are CustomSelect's grid bytes and action-table word. The helper
returns that table address plus a four-byte cell offset; the consumers use
its result as an action-record pointer for help and binding updates. It is
now the address-named CustomSelect member sub_80277290(), returning void*.
The declaration, definition, both callers and catalog agree. Its source unit
and address are retained; no original translation-unit boundary is asserted.
The callers preserve their existing four-byte record-prefix view and outer
word-valued controller fields. The complete action-table type is not invented.

This ownership correction does not activate CustomSelect's native lifetime.
Its existing constructor can return before initializing its child slots, and
current evidence does not establish a complete lifetime for those paths.
No extra stores or assumption of per-allocation heap zeroing is added. The
existing CustomSelect constructor/destructor and all its text remain unchanged.

The later [CustomSelect native-code recovery](window-custom-select-native-code.md)
reproduces the native constructor/destructor, ordinary-new producer and compiler
table. It preserves these early returns and uninitialized slots exactly. The
partial-initialization safety hold above remains unresolved; native code and
table recovery do not establish safe destruction on every path.

## Descriptor, compiler table and original data

The constructor input at [804D1488,804D149C) has extent 212/188, order
50050, flags 3 and an entry relocation to lbl_804D1198. The existing
provisional WindowLayoutDescriptor schema represents those fields. The
opaque entry table stays original input.

The native key function emits the four-function 24-byte table at
[804D149C,804D14B4). Its catalog size is corrected from 28 to 24; the
following zero word is not an extra slot. Descriptor and table naturally form
44 bytes, alignment eight and table offset 0x14. Raw data and the full link
match, with no manual table, padding definition or alignment override.

The following opaque data at 804D14B8 is not source-owned here. Its preceding
zero word remains original input, rather than being called linker padding.
The selected auto_07_804D14B4_data.o contains 204 bytes, equal to offset 796
onward in main's original 1,000-byte auto_07_804D1198_data.o. The preceding
entry-data object retains the original 752-byte prefix. Both pieces are
selected once, with unchanged unrelocated and resolved bytes. No coverage
leaves the report.

## Verification and standing holds

Complete original/compiled unrelocated text is identical in the three changed
units and six header-dependent units, each actual source link input once:

| Unit | Bytes |
| --- | ---: |
| TWindowSubCustomEquip | 3,472 |
| TWindowSubEquip_80275C0C | 376 |
| TWindowSubComCardList | 1,744 |
| TWindowSubCustomSelect_80275D84 | 24 |
| TWindowSubCustomEquip_802760AC | 104 |
| TWindowSubCustomEquip_80275D9C | 784 |
| TWindowSubCustomEquip_80276114 | 1,044 |
| TWindowSubCustomSelect | 2,488 |
| text_8027C13C | 240 |

CustomEquip's 44-byte data also matches. The full DOL reproduces SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr passes:
all 27,387 exact functions and 3,588 exact linked units retained, no code,
function, data or coverage loss, and 44 additional matched/linked data bytes.
Retention is clean at 17,752 names (+5, no removals); the porting inventory
passes. Against fresh main 224eb9983, the combined PR retains +600 matched
code, +1,220 linked code and +956 matched/linked data bytes. The eleven
previously qualified alignment gaps are unchanged. No compiler control is added.

One more Base construction/cleanup pair leaves the raw interface. It now
has 50 calls across 25 source units: 21 Base pairs and four Addition pairs.
The four bindings remain.

Protected original Help/SoundBalance suffixes of 204/532 bytes and the
separate 1,044-byte text remainder [8026E1D4,8026E5E8) remain original
inputs once, with unchanged unrelocated and resolved bytes. ChoiceSetting's
unknown 0x7C producer, task-global word 805D5D94, Snapshot separation,
ChallengeResult activation, CustomSelect lifetime and broader child/interface
holds remain. The PR stays draft and must not be marked ready or merged.
