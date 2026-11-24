# Ancient trap layout and matching constraints

`TOTrapAncient01` owns the resource group beginning at `0x804B4820`: four
model-name pointers and a null terminator, a BML descriptor, and a collision
body. The descriptor references the null motion-name array at `0x805D31A0`.
The class-name pointer is at `0x805D31A4`, and the resource slot at `0x805D5AD0`
occupies eight original bytes. This unit accesses only its first word, a
`BmlResource *`; the remaining word has no assigned semantic meaning.

The owned `.rodata` range is `0x80442CE0..0x80442E70`. It contains resource
strings and the initializer templates of the three `0x4C` debris records that
`play_sounds` builds at `0x80442D80`, `0x80442DCC`, and `0x80442E18`. Each
record takes the actor's position, with Y also used for its floor field.
Preserve record layout, initialization and call order when changing the source.

The native derived destructor and four `RenderFadeState` members emit the
derived vtable. Reverse source definitions with deferred generation place
its 360 bytes at `.data` offset `0x50`, ahead of the switch tables at
`0x804B49D8`, `0x804B4A1C`, and `0x804B4A78`. Inherited override signatures
must remain compatible with `TObjChara`; see
[Trap inherited virtual slots](trap-inherited-slot-evidence.md).

The unit's `.data` is `0x804B4820..0x804B4AD4`, the 692 bytes the compiler
emits. The four zero bytes at `0x804B4AD4` are alignment padding:
`TOTrapAncient02`'s `.data` starts at `0x804B4AD8` with alignment 8, and the
linker inserts the padding. The original has no symbol or relocation there.
Linked units commonly end their `.data` split before such padding.

The override at `0x80179784` returns the floating-point result of the qualified
`TOTrap::receive_physical_attack` call. The player-lookup boundary uses the
shared character position at offset `0x2FC`; changes to its receiver contract
require checking the shared declaration and callers.

`.sdata2` is `0x805DBA48..0x805DBA78`: `1.0`, `0.0`, `1.25`, `15`, `400`,
`20`, `0.1`, `3.0517578125e-05`, `0.05`, `30`, `0.5`, `0.33`. The leading
`1.0` and `0.0` belong to the inline `TOTrap` slots 23 and 24 (see the slot
evidence). This vtable references them, so the compiler emits weak copies here
first and pools their literals before `play_sounds`' `1.25`. The linker keeps
`TOTrap.o`'s copies and drops these, but the literals stay in this unit's pool,
as in the original. The constructor's `0.33` (`m_350` scaling in main phase
`0xE`) is the last word; it is a literal, not a named constant.

`play_sounds` builds each debris record as a `const TObjChipParams` brace
initializer, which the compiler copies from the `.rodata` template and then
fills with the position, floor and resource values. Because the records are
`const`, those stores cannot alias `position`. GC/2.0 therefore loads `x`,
`y` and `z` into `f2`/`f1`/`f0` before the template's tail word store, as the
original does. GC/2.6 stores the tail first and alternates the loads and
stores (91.09%), as does a non-`const` record on GC/2.0 (94.24%). The sibling
`TOExplosiveMachine` builds its records the same way on GC/2.0. The
constructor takes a non-`const` pointer, so each record is passed through
`const_cast`. The unit's `-pooldata=off` keeps the copy prologue; without it
the prologue uses `stmw`. The per-flag evidence is in
[porting exceptions](porting-exceptions.md).
