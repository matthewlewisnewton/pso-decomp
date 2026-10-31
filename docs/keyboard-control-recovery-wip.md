# Soft keyboard unit recovery (WIP)

Base: `beaa7f52af2a7360e18deafc771648f51b709531` (fork PR #100).
This is an intermediate checkpoint, not a complete or validated unit.

The original `0x8026227C` walks seven rows and sixteen columns, advances by
key width, draws the selected frame, then draws the language-page selector
and two controls. The candidate expresses those calls and the observed page
range and colors in C++. The existing 0x64/0x68 object fields remain bounded
views: their owner and names have not been established. The control drawing
and texture interfaces are existing provisional declarations.

A standalone CodeWarrior GC/2.6 compile succeeded. An objdiff comparison to
the local original split object reported 95.51% for this function (856 original
bytes versus 860 candidate bytes). This is not an exact match; register
allocation, code layout and data/relocations require further work. The initial
candidate failed the regression check because its unsigned
conversion introduced an extra eight-byte .rodata constant. The current signed
conversion preserves the original unit data in a targeted comparison; the
locked two-job rebuild and `tools/check_pr.py --no-build` passed: no exact
functions, data ranges or linked units regressed, and all 3,536 linked units
passed. The baseline DOL hash passed; this unit still uses original fallback
for linking, so that hash does not establish correctness of the new body. The
unit is not linked from source and the new bodies are not exact.
No original binaries or generated objects are included in this checkpoint.

## Input dispatch candidate at 0x80260904

The original data object's first 22 three-word member-function descriptors
refer to `vt0` through `vt21`, and the function copies them to a second array
on first use, guarded by a byte at `0x805D6458`. The candidate accesses that
existing object through a size-checked local view and retains the observed
controller, character filtering, sound, and child-dispatch paths. The data
object and child class ownership remain provisional shared interfaces; no
shared definitions are changed.

The targeted GC/2.6 compile succeeds. Individual descriptor copies reproduce
the original expanded initialization more closely than a loop: the dispatcher
is 1,320 bytes against 1,324 original bytes, with objdiff reporting 57.49%.
This is not an exact-code claim. The
grid renderer is 95.51%, and targeted `.rodata` comparison remains 100%.
The expanded version passed the locked two-job rebuild and regression checks.
This does not validate runtime behavior of the fallback-linked source body.

## Glyph rendering candidate at 0x802616BC

The original first walks the selected language page as a 7-by-16 grid and
filters characters according to the three input flags. It then draws twelve
control glyphs, the page selector glyphs, and ten icon rectangles using the
external position, size and texture tables at `0x8044F164`, `0x8044F1B4` and
`0x8044F204`. The candidate follows these paths through existing rendering
interfaces and local views; shared UI and rendering declarations remain
provisional.

The standalone GC/2.6 compile succeeds. Objdiff reports 81.26% for the new
body (1,820 original versus 1,864 candidate bytes). The input dispatcher and
grid frame renderer are 57.49% and 95.51% respectively. The targeted
`.rodata` comparison is 100%. The locked two-job incremental rebuild and
`tools/check_pr.py --no-build` passed with no lost exact functions, data or
linked units (3,536 linked units checked), including after the pointer-typed
cursor helper change. None of these scores proves exact code, relocations or
runtime semantics; the DOL still uses the original unit.

## Data ownership audit

The original split marks `0x805D6458..0x805D6460` as automatic `.sbss`.
Only `0x80260904` references it: a one-byte read and write guard the action
table initialization. The source now defines the eight-byte split symbol,
with only its first byte named; the other seven bytes remain reserved and
unclassified. The targeted object emits an eight-byte `.sbss` symbol with no
change in the dispatcher comparison. The locked rebuild and regression check passed: matched data increased by
eight bytes, and no existing exact functions, data or linked units were lost.

The action object at `0x804CFDE0..0x804D0004` is currently automatic data.
Its first 20 bytes are also passed as the window descriptor by the neighboring
constructor at `0x80262740` in `TWindowKeyBoardSoft_80261440.cpp`; the same
object contains the 22 initial and 22 runtime member-action descriptors used
by `0x80260904`. Its shared descriptor and action storage should be assigned as
one object only after the constructor owner and integration coordinator agree
on the split and C++ declaration.

The icon position, size and UV tables at `0x8044F164..0x8044F258` have no
original references outside this unit. The adjacent key-offset and frame-UV
tables at `0x8044F124..0x8044F164` likewise have only this unit as an original
code consumer. A targeted definition emitted the data in the observed order,
but the object's eight-byte `.rodata` alignment inserted four extra bytes before
the existing double constant: the inferred start `0x8044F124` is only four-byte
aligned. The preceding `TWindowKeyBoardSoft` type name at `0x8044F110` is used
via an external type-name pointer and may be part of the same original object.
A second temporary compile included the preceding type name and emitted a
336-byte block at the proposed `0x8044F110..0x8044F260` boundary, byte-identical
to the original name, geometry tables and existing double constant. The name
is referenced by the automatic `keyboard_soft_type_name_pointer` in sdata,
which the neighboring constructor reads. Confirm assignment of this shared
type-name boundary with that owner before claiming it; the experiment is not
in the source branch.

## Frame clipping call

At `0x80262098` the original passes the draw context in the second integer
argument register to `0x802614DC`. The existing source cast the function to a
signature without that parameter, relying on a register being left unchanged.
The candidate passes the context explicitly with the actual declared argument
list. The targeted instruction comparison is unchanged, and the locked two-job
rebuild and regression checks passed without lost exact or linked coverage.

## Controller-button call

The helper at `0x801A6DA0` takes a controller pointer and button mask. The
unit previously declared three parameters and cast several calls to incompatible
function-pointer types. The candidate uses the observed two-argument interface
locally. A targeted object comparison retains 100% for `0x80260808`,
`0x8026088C` and `0x80261204`, and leaves the new dispatcher unchanged. The locked two-job rebuild and
regression checks passed with eight matched data bytes gained and no loss of
existing exact functions, data or linked units.
