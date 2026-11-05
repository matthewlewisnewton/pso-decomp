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
0.0f. They use native target storage and virtual dispatch. Unused parameters
retain the inherited signatures.

Slots 20, 21, 23 and 24 are inline in `TOTrap.h`. `TOTrap::~TOTrap` is defined
in `TOTrap.cpp`, so `TOTrap.o` emits `__vt__6TOTrap` (`.data`
`0x804B46B8..0x804B4820`) and weak copies of the four inline slots at the end
of its `.text`, in vtable order. That is where the original has them
(`0x801792E4..0x8017939C`). Every unit whose native vtable references an
inherited inline slot emits its own weak copy. The linker keeps the copy that
links first, `TOTrap.o`'s, and discards the rest. Ancient01's discarded copies
still leave their `1.0f`/`0.0f` literals at the head of its `.sdata2`, which is
the original pool. `tools/link_units.py` accepts a weak symbol that an
earlier-linked unit also defines weak, because the linker discards that copy.

Slot 21 returns `int`, as declared by TObjChara; using `s32` makes this
compiler append a slot. Slot 27 stays out of line in `TOTrap.cpp`.

Slot 87 performs the existing difficulty-table scaling; its old static spelling
was referenced only by two existing legacy tables, while Ancient02 calls the
virtual slot. Those table references are updated mechanically; their tables
are not newly authored or claimed as native recovered representations.

Ancient02 and Seabed01 keep hand-written vtables. GC/2.6 rejects a cast from
these virtual member pointers to a function address, so those tables name the
CodeWarrior symbols with C linkage. That names the existing functions; it is
not the original source spelling.
