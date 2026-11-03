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

The 90.91% `.sdata2` score is the 44-byte contents. The original words are
`1.0`, `0.0`, `1.25`, `15`, `400`, `20`, `0.1`, `3.0517578125e-05`, `0.05`,
`30`, `0.5`. Deferred generation compiles `play_sounds` before `vfunc_82`, so
the literal pool is `1.25`, `1.0`, `0.0`, then that same tail. Naming those
eleven objects in `.sdata2` and loading them makes the section and its symbols
match, and it changes `TOTrapAncient01__ct`: the literal
`fmadds f1, f3, f2, f1` allocation becomes a generic load allocation and the
function drops from 100% to 99.25%. Literal constants keep the constructor
exact. The original section flags are 2 (`SHF_ALLOC`); this GC/2.6 object has
flags 3 (`SHF_ALLOC|SHF_WRITE`). That flag bit is already true of linked
`TOTrap` and `TOTrapSeabed01`, and it is not the 90.91% score.

`play_sounds` remains 92.71%. The mismatch is the schedule of the three
position fills against the tail of the `0x4C` copy, not the calls. Writing
`position.x`, `position.y`, and `position.z` directly scores 91.09%. The
local copies of those fields score 92.71%. Neither is exact. `#pragma
pool_data off` around that function keeps the copy prologue close to the
original; without it the prologue uses `stmw` and the function is farther
from the original.
