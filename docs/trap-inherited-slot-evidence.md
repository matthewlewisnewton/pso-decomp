# Trap inherited virtual slots

This bounded change starts at ancient-trap checkpoint
`d7fc5d55a489baa9747e17c6661b5fefcf5942e2`. It repairs inherited dispatch
contracts without changing TObjChara or the shared player lookup helpers.

The original Ancient01 vtable uses the following implementations, counting its
two leading null words. The native table previously inherited the Chara targets
for slots 20, 21, 23, 24 and 27, and an undefined TOTrap slot 87.

| Slot | Original address | Native override |
| --- | --- | --- |
| 20 | 0x801792E4 | select_melee_contact_body(void*, f32) |
| 21 | 0x801792FC | calc_distance_accuracy_penalty(void*, void*, void*, f32) |
| 23 | 0x80179314 | receive_direct_attack(void*, DirectAttackPayload, void*, s32, s32) |
| 24 | 0x80179358 | receive_weapon_special_attack(void*, void*) |
| 27 | 0x801792CC | roll_physical_accuracy(void*, s32, f32) |
| 87 | 0x80178B78 | vfunc_87(f32) |

Slots 20/21/27 compare the source argument in r4 with the receiver's target at
0x2A8 and return whether they differ. Slots 23/24 perform the same comparison,
conditionally dispatch physical attack with null source and 1.0f, and return
0.0f. They now use native target storage and virtual dispatch. Unused parameters
retain the inherited signatures. In particular slot 21 returns `int`, exactly
as declared by TObjChara; using s32 instead makes this compiler append a slot.
Slot 87 performs the existing difficulty-table scaling; its old static spelling
was referenced only by two existing legacy tables, while Ancient02 calls the
virtual slot. Those table references are updated mechanically; their tables
are not newly authored or claimed as native recovered representations.

The three simple predicates now use the inherited full-register return types.
This is supported by their original emitted code and the Chara contracts, not
an inference from the old u8 standalone declarations alone. The original six
function addresses and bodies remain exact after symbol mapping updates.

## Validation of this bounded checkpoint

Fresh GC/2.6 compilation of all 14 units transitively including TOTrap succeeds
using each unit's configured flags. Independently compiled the unchanged base
for comparison. After normalizing the six symbol renames, 13 units have no
objdiff symbol differences. Ancient01 changes only the intended inherited
vtable targets; its code is unchanged. Direct original comparison shows TOTrap,
Ancient02 and Seabed01 code/data remain 100%. Independent ELF relocation audit
finds no remaining target differences in Ancient01's 360-byte native vtable.

The object-level tests do not complete PR102. Ancient01's vtable placement,
play_sounds scheduling, update extra branch and scalar ordering still differ;
its legacy source boundaries and shared nearest-player receiver remain open.
No fresh full DOL build, check_pr or link selection is claimed. Source is a
fork checkpoint for separate targeted independent review, not merge-ready.

Local artifacts are under task-8/slot-probes: compile summaries, fresh baseline
and candidate objects, before-after-summary.json, vtable-final.json and the
original comparison. Original game objects remain local and are not committed.
