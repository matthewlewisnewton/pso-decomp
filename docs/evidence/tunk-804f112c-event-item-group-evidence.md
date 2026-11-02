# TUnk_804F112C event-item group evidence

`TUnk_804F112C` has no class-name string or vtable RTTI entry in `PsoV3.dol`, so
the class keeps its vtable-address placeholder. Its item group is recoverable
from the item factory and ItemPMT data.

## Factory index

- `item_tool_factory_table` is at `.data:0x8049EE00`, 24 entries (`0x60` bytes).
- Entry 20 at `0x8049EE50` is `0x80353414`, `TUnk_804F112C::create`.
- `TLobby__sub_8010440C` (`.text:0x8010440C`) returns
  `item_tool_factory_table[item[1]]` for `item[1] < 0x18`. `TItem` stores byte 1
  as `item_group`, so group `0x14` (20) constructs this class.

## ItemPMT type 20

The decompressed `ItemPMT.prs` root points at a 24-entry type table at root
`+0x0C`; each entry is `{count, records}` and each record is 20 bytes. Type 20
has 12 records at payload offset `0x2A5C`. Each record's first word is its text
ID:

| Text ID | Item |
|---|---|
| `0x78` | Chocolate |
| `0x79` | Candy |
| `0x7A` | Cake |
| `0x7C` | Siver Badge (retail spelling) |
| `0x7D` | Gold Badge |
| `0x7E` | Crystal Badge |
| `0x7F` | Iron Badge |
| `0x80` | Aluminum Badge |
| `0x81` | Leather Badge |
| `0x82` | Bone Badge |
| `0x83` | Bouquet |
| `0x84` | Decoction |

Text ID `0x7B` is Copper Weapons Badge but type 20 does not select it;
`0x85` (Christmas Present) belongs to type 21. `get_text_collection(id)`
(`.text:0x8010EEDC`) resolves these through the first text group's pointer
array, which is at payload offset `0x17810` in the decompressed `TextEnglish`
pair. Type 0's IDs 0/1/2 resolve to Monmate (retail spelling)/Dimate/Trimate and type 21's
`0x85`/`0x86`/`0x87` resolve to Christmas Present/Easter Egg/Jack-O'-Lantern,
confirming the array order.

The group therefore identifies the class semantically as the event-item use
effect, but it does not supply the original class name. Keep `TUnk_804F112C`
until the executable provides a class-name string or other naming evidence.
