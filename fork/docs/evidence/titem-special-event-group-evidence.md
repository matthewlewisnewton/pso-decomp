# TItemSpecialEvent event-item group evidence

`TItemSpecialEvent` has no class-name string or vtable RTTI entry in `PsoV3.dol`.
The name is an explicit inferred name adopted for the special-event item group,
not a recovered symbol. Its item group is recoverable from the item factory and
ItemPMT data.

## Factory index

- `item_tool_factory_table` is at `.data:0x8049EE00`, 24 entries (`0x60` bytes).
- Entry 20 at `0x8049EE50` is `0x80353414`, `TItemSpecialEvent::create`.
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
effect. The class name `TItemSpecialEvent` is an inferred name adopted as an
explicit exception for this unit; the executable does not provide the original
class-name string, so the name is not recovered evidence.

## Use-effect dispatch

`apply_use_effect` (`0x803531FC`) selects one of nine steps by technique index
and calls it with `(this->*handler)()`. The steps (`0x8035307C`-`0x803531F8`)
and `send_obj_position_event` (`0x80353018`) use the typed `TItem::owner`
(`TObjPlayer*` at `+0xF0`), so they are members of this item. The original split placed these steps in `TEndingPic.cpp`. The
[ending-picture recovery](ending-picture-recovery.md) moves them next to the
use-effect dispatcher, with their separate floating-point pool; the old split
was not evidence of their historical translation-unit ownership.

`send_obj_position_event` keeps the name already assigned to `0x80353018`.
The other steps stay `sub_<addr>`. `set_phase_18`, `update_player_object`, and
`update_shield` had no name evidence in the executable.
