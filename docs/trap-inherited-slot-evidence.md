# Trap inherited virtual slots

These declarations repair Ancient01's inherited dispatch without changing
TObjChara or the shared player lookup helpers.

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
retain the inherited signatures.
Slot 87 performs the existing difficulty-table scaling; its old static spelling
was referenced only by two existing legacy tables, while Ancient02 calls the
virtual slot. Those table references are updated mechanically; their tables
are not newly authored or claimed as native recovered representations.

The three simple predicates use the inherited full-register return types.
Their original code stays exact with those signatures. Slot 21 returns `int`,
as declared by TObjChara; using `s32` makes this compiler append a slot.

Ancient02 and Seabed01 keep hand-written vtables. GC/2.6 rejects a cast from
these virtual member pointers to a function address, so those tables name the
CodeWarrior symbols with C linkage. That names the existing functions; it is
not the original source spelling.
