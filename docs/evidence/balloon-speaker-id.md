# Balloon speaker ID and constructor call

The balloon constructor at `0x80252B74` now calls the real
`TUnk_804CF0B8::sub_80251DF0` member at `0x80251DF0`. The former word-valued,
hand-mangled declaration of that member is removed. This change does not
recover the native balloon destructor or its constant-pool layout.

## Types and ownership

The speaker is an unsigned 16-bit entity ID throughout this path:

`TWindowCtrl::open` → `show_chat_balloon` → `acquire_balloon_slot` →
`TUnk_804CF0B8` constructor → `sub_80251DF0`.

The initializer stores the ID with `sth` at `0x80251E3C`, at balloon offset
`0x76`. The accessor at `0x8024C5E8` loads that field with `lhz`; its callers
operate on the controller's four balloon pointers at offset `0x84`, not on
controller objects. It is therefore declared as
`TUnk_804CF0B8::get_speaker_id`. The initializer also passes the ID directly
to `set_color(u16)`. Both its argument and its stored field must be unsigned
shorts to reproduce the original register copies with that direct call.

`get_speaker_balloon_anchor` (`0x8024A5AC`),
`find_farthest_balloon_slot` (`0x8024A714`) and
`acquire_balloon_slot` (`0x8024A800`) are ordinary controller members.
The anchor helper forwards the same ID to `find_entity_by_id(u16)`;
the farthest-slot search compares distances to those same entity IDs.
The constructor's client argument is word-sized: it narrows that argument
for the base constructor but forwards it unchanged to `sub_80251DF0`.

The constructor has one caller (`0x8024A8FC`). Acquire is called by show
(`0x8024A9F0`) and `open_balloon` (`0x8024B520`); show is called by open
(`0x8024B5A8`). The default-open wrapper at `0x8024B5E0` is static and receives
the speaker ID in `r3`, rather than receiving a controller object there.

## Upstream boundaries

Word-select display and its language formatters forward the same 16-bit
speaker ID. Packed and computed IDs use explicit `u16` conversions at their
boundaries. Quest opcode arguments remain word-sized until that extraction;
the quest speaker selector can also designate an NPC by a different key.

The immediate object/NPC callers declare `get_entity_id` with its actual
`u16` result. Its definition at `0x800195B0` loads the entity field at `+0x1C`
with `lhz`. In the NPC unit, the arrival-coordinate declaration consequently
also uses its real `void(u16, s32, f32, f32, f32)` signature. Companion creation
uses the slot just written into the outgoing packet for arrival setup. MWCC
forwards that stored value with the original normalization at `0x8034EB80`
and `0x8034EBF4`; using the raw parameter instead removes those instructions.

The SinBoard caller increments its existing counter before calling
`get_entity_id` directly. The counter remains live; it is no longer passed
as a spurious extra argument through a function-pointer cast.

## Validation

Every function in the affected units and every owned data section matches.
The controller's emitted order remains anchor, distance, farthest, count,
acquire, show. The balloon tail remains render, run_task, destructor,
constructor, across the existing unit pieces.

The full DOL SHA-1 is `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
No compiler flag, pragma, alignment override or porting exception is added.
The remaining raw destructor site in `WindowConstructorAbi.h` is unchanged.
