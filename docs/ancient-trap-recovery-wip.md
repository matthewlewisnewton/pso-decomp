# Ancient trap layout and matching constraints

`TOTrapAncient01` owns the resource group beginning at `0x804B4820`: four
model-name pointers and a null terminator, a BML descriptor, and a collision
body. The descriptor references the null motion-name array at `0x805D31A0`.
The class-name pointer is at `0x805D31A4`, and the resource slot at `0x805D5AD0`
occupies eight original bytes. This unit accesses only its first word; the
remaining word has no assigned semantic meaning.

The owned `.rodata` range is `0x80442CE0..0x80442E70`. It contains resource
strings and three independent `0x4C` debris parameter records at `0x80442D80`,
`0x80442DCC`, and `0x80442E18`. Each record takes the actor's position, with Y
also used for its floor field. Preserve record layout, initialization and
call order when changing the source.

The native derived destructor and four `RenderFadeState` members emit the
derived vtable. Reverse source definitions with deferred generation place
its 360 bytes at `.data` offset `0x50`, ahead of the switch tables at
`0x804B49D8`, `0x804B4A1C`, and `0x804B4A78`. Inherited override signatures
must remain compatible with `TObjChara`; see
[Trap inherited virtual slots](trap-inherited-slot-evidence.md).

The original `.data` extent is `0x804B4820..0x804B4AD8`, 696 bytes. The last
named object ends at `0x804B4AD4`. The split object records the remaining
four bytes as a zero gap and has no relocation there. `TOTrapAncient02`'s
`.data` starts at `0x804B4AD8` with alignment 8. The linked DOL contains
`00 00 00 00` at `0x804B4AD4` and Ancient02's first word at `0x804B4AD8`.
The compiler object emits 692 `.data` bytes, identical to that payload, and
does not contain the gap. This unit stays on the original object, so the DOL
still includes the gap. Do not add a C++ object for those four bytes.

The override at `0x80179784` returns the floating-point result of the qualified
`TOTrap::receive_physical_attack` call. The player-lookup boundary uses the
shared character position at offset `0x2FC`; changes to its receiver contract
require checking the shared declaration and callers.

The original object's `.sdata2` flags are 2 (`SHF_ALLOC`). The GC/2.6 object
built with this unit's flags has flags 3 (`SHF_ALLOC|SHF_WRITE`). Linking
the unit has to preserve the original section flags, both SDA bases, the
relocations and the DOL. A function or data score does not show those
properties.
