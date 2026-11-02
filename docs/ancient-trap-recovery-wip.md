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

The original `.data` extent is `0x804B4820..0x804B4AD8`, or 696 bytes. The
native payload occupies 692 bytes through `0x804B4AD4`. The next real data
owner, `TOTrapAncient02`, starts at `0x804B4AD8` with alignment eight, producing
four bytes of natural linker fill. Keep all 696 bytes in original coverage;
the fill does not represent another C++ object or another table entry.

The override at `0x80179784` returns the floating-point result of the qualified
`TOTrap::receive_physical_attack` call. The player-lookup boundary uses the
shared character position at offset `0x2FC`; changes to its receiver contract
require checking the shared declaration and callers.

The reconstructed original object has `.sdata2` flags 2, while the matching
GC/2.0 native object has flags 3. Source adoption must preserve the actual
linked section's bytes, flags, addresses and alignment, both SDA bases, all
relocation targets and the original DOL. Object similarity alone does not
establish these link properties. Validation summaries belong to the exact
commit and target recorded in the pull request.
