# Native numeric-readout window lifetimes

This follows PR #268 checkpoint
`2205b0b428ac39dfd7e2ba6ec05f2cf848168d6c`, including main
`fe6cdb14138b2413778c08f21fd1851170c22ab5`. The bounded family is
TWindowMeseta, its existing TWindowCost descendant, and TWindowQuantity.

## Genuine construction and supported field types

Meseta and Quantity now initialize Base directly and use native destructors
with automatic cleanup. Cost initializes its real Meseta base with position,
client and text; its already native empty destructor keeps automatic cleanup.
The old one-argument Cost/Meseta declarations depended on live argument
registers and are removed. No default constructor or extra TObject lifetime
is invented. Meseta's task calls its real value getter directly.

Original constructors store floats at Meseta offsets 0x6C/0x70 and Quantity
offsets 0x64/0x68. Render passes each pair's address to the draw-context path,
which consumes float scales. No pointer use was found in the inspected owners
or Cost descendant. The old pointer/opaque declarations become actual f32
fields. Sizes remain 0x74 for Meseta/Cost and 0x6C for Quantity; explicit
offset assertions cover both pairs. Meseta's client and value words at
0x64/0x68 are retained, separately from Quantity's different owned fields.

Both Base clients are word carriers, narrowed only at Base construction.
Meseta additionally stores the complete incoming client word at 0x64. Its
text argument remains an explicit word carrier through the existing text-entry
interface; this does not recover its broader semantic pointer type. The
underlying entry-widget and other unrelated window protocols remain held.

## Closed factory and value-update boundaries

All three factories use ordinary `new`. Shared declarations return the actual
window pointers and take word clients. The twelve original factory references
(Meseta six, Quantity two, Cost four) are zero-addend REL24 calls; no
address-taken factory reference was found. All known callers use the shared
headers, removing local return/parameter disagreements. The eight call sites
previously declared with short clients retain their explicit u16 narrowing,
while existing word-valued stored handles remain unchanged. These casts
expose the existing storage boundary rather than pretending it is portable
to a wider-pointer port.

The wrapper at 803094E8 is a value update, not a shop controller getter. Its
ten direct callers are Cost construction once, EquipmentSell three times,
and ItemList/Armor/EquipmentList twice each. All discard the result. Receiver
provenance is the Cost factory: named cost fields, Armor/Equipment offset 0x3C,
and ItemList's two local replicas at offset 0x40.

It becomes ordinary address-named `fn_803094E8(TWindowCost *, s32)`, explicitly
forwarding both arguments to the actual value setter. No Cost member ownership
is invented. The false shop-class method and local mismatched prototypes are
removed. The underlying setter retains its separate broader receiver contract.
The wrapper's complete 32-byte body and every caller retain original bytes.

## Descriptor, compiler tables and original padding

Meseta's 24-byte compiler table is claimed at `[804D06E0,804D06F8)`. Its
existing descriptor remains original input. Cost's already source-owned
24-byte table `[804E7530,804E7548)` is unchanged.

Quantity's actual table is 24 bytes, not the catalog's 28 bytes. Its address
804D0884 is four modulo eight, so claiming the table alone would not reproduce
its natural compiler section. The evidenced preceding 20-byte descriptor
belongs to this constructor input. Using the existing provisional
WindowLayoutDescriptor schema, it defines extent 160/27, order 50100, an
opaque pointer to lbl_804D0830, and flags 0x82B. The original relocation at
offset 0xC identifies that entry table, which remains original input. These
are program layout fields, not an asset byte dump.

The compiler naturally emits the descriptor then its four-function table:
`[804D0870,804D089C)`, 44 bytes, section alignment eight and table offset
0x14. Both data sections compare identically before relocation, and the full
link verifies their targets. No manual table, extra virtual slot, padding,
alignment override or new compiler control is introduced. The existing
Meseta factory scheduling pragma is retained; no new pragma is added.

The separate zero tail `[804D089C,804D08A0)` stays outside the claim and
leaves report coverage. It is zero in both original and rebuilt DOLs. The
following ReturnCity source data has natural eight-byte alignment and size
24, so normal linker alignment reproduces it. No meaningful data is lost.

## Qualification and remaining holds

Complete original/compiled unrelocated text is identical in all seventeen
listed objects, all selected as actual source link inputs:

| Unit | Bytes |
| --- | ---: |
| TWindowMeseta | 456 |
| TWindowMeseta_802690B4 | 208 |
| text_8026934C | 104 |
| TWindowQuantity | 672 |
| TWindowCost | 168 |
| TAdLoadQuestGC | 416 |
| TShopEquipmentSellWindow_803094E8 | 88 |
| TShopEquipmentSequence | 1,804 |
| TCheckRoomSequence | 9,664 |
| TShopItemTecSequence | 1,912 |
| TJudgmentSequence | 1,252 |
| TMedicalCenterSequence | 2,752 |
| TShopEquipmentGearSequence_8021B438 | 1,340 |
| TShopEquipmentSellWindow | 3,252 |
| TShopItemListWindow | 3,384 |
| TShopArmorListWindow | 3,796 |
| TShopEquipmentListWindow | 3,836 |

The complete DOL reproduces SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr retains
all 27,384 exact functions and 3,586 exact linked units with zero code or
non-padding coverage loss. Matched/linked data gains 68 bytes: Meseta's table
and Quantity's descriptor/table. Retention is clean at 17,684 entries (+8,
-1 stale renamed entry); the refreshed porting inventory passes. Against fresh
main fe6cdb141, the combined PR retains +600 matched code, +1,220 linked code
and +640 matched/linked data bytes. Nine qualified four-byte alignment gaps
account for the 36 bytes outside report coverage.

Two more Base construction/cleanup pairs leave the raw interface, reducing it
to 66 calls across 34 source units. The four Base/Addition bindings remain.
The separate 1,044-byte original remainder at `[8026E1D4,8026E5E8)` remains
selected exactly once, with unchanged unrelocated and resolved bytes. Its
source and ownership are not fabricated. ChoiceSetting's unknown 0x7C
producer, task-global word 805D5D94 and the broader legacy interfaces stay
held. The PR remains draft and must not be marked ready or merged here.
