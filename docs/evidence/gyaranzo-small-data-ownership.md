# Gyaranzo resource and volley-state ownership

The previous 12-byte proposal stopped before the shared timer at `0x805D520C`.
Together with the accepted Merillia range beginning `0x805D5210`, that left a
named object undefined. Recover the complete meaningful four-object range
`.sbss 0x805D5200–0x805D5210` instead:

| Existing type/name | Offset | Original address |
|---|---:|---:|
| `NJS_OBJECT *lbl_805D5200` | 0 | `0x805D5200` |
| `NJS_OBJECT *lbl_805D5204` | 4 | `0x805D5204` |
| `TUnk_8048FA00 *gyaranzo_breakup_model_obj` | 8 | `0x805D5208` |
| `s32 gyaranzo_missile_volley_end_time` | 12 | `0x805D520C` |

A fresh census of all 5,064 original objects configured for the initial
candidate finds 3/3/4 references to the pointers, exclusively in Gyaranzo.
The timer has one Gyaranzo store and one missile load, both with zero addend;
the original instructions are `stw` and `lwz`. No SBSS target is unresolved.
The node lookups, model-node updates, breakup-object creation/destruction,
volley lifecycle and contiguous companion storage support this owner.
The shared timer remains externally visible. Its existing header, included by
both consumers, now supplies their common C-linkage `s32` declaration.

Compiled SBSS is exactly 16 bytes with alignment 8. All four exported symbols
are four bytes at the original offsets. No padding, enlarged type, localization,
function-body change or compiler override is introduced. Independent comparison
of the two compiled objects preserves every prior allocated section and all
636 relocation records/physical targets, including 493 code relocations.

## Validation

The initial source was verified against freshly built main `f1227326c4`.
The branch then incorporates main `f9b6cf76d9171b3dce5082b1484a85f4579855cd`
(the concurrently merged ending-controller work) and is revalidated against
that fresh baseline. Native output reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. PR checks, retention,
actual source-link inputs, strict original-address no-loss checks including
padding, and both port-exception inventories pass. Matched and source-linked
data each gain 16 bytes; existing function/code counts and denominators remain
unchanged. Retention adds the three pointer names, removes none, and sorts
three existing bone-rotation entries. The timer is retained by its external use.

## Other combined-only cases still deferred

DHCP lease fields conflict with network packet state in original section order.
The player-effect field reverses the order of the material and player units.
The DD element count and character-selection state similarly conflict with
already-owned neighboring state. Their individually matching definitions do
not resolve original translation-unit ownership. Keep the larger accepted
ranges; do not introduce padding, arbitrary owners or layout-only helper units.
