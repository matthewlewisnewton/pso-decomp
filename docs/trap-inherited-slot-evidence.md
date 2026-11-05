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

Slot 87 performs the existing difficulty-table scaling. Ancient02 calls it as
the virtual slot.

Seabed01's vtable is native. It is TOTrap's with nine overrides: the
destructor, `render`, `vfunc_6`, slot 22 (`receive_physical_attack`, formerly
`TOTrapSeabed01__vt20`), `vfunc_67`, `vfunc_81`, `vfunc_82`, `vfunc_84` and
slot 85 (`play_sounds`, formerly `TOTrapSeabed01__vt83`). The four bytes after
it are alignment padding before the next unit's `.data`. The original `.sdata2`
pool starts with `1.0`, `0.0`, the literals of the weak slot copies, so the
original generated those copies first, as deferred generation does. The unit
is therefore built with deferred generation and reversed definitions; see
[porting exceptions](porting-exceptions.md).

Ancient02R keeps a hand-written table in `TOTrapAncient02.cpp`. GC/2.6
rejects a cast from a virtual member pointer to a function address, so the
table names `vfunc_87__6TOTrapFf` with C linkage, like its other entries. That
names the existing function; it is not the original source spelling.
