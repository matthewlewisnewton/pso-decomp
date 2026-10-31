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

## Static action-array emission experiment

In an isolated temporary compile, a function-local static array of the 22
observed `TWindowKeyBoardSoft::vt0` through `vt21` member pointers produced
92.90% for `0x80260904` (1,356 candidate bytes against 1,324 original), versus
57.49% for the checked-in explicit copy. CodeWarrior emitted 22 three-word
initial descriptors followed by a 264-byte runtime array in `.data`, and a
one-byte static initialization guard in `.sbss`. This matches the observed
structure of the original action-data range and the guard's use, but not yet
the complete instruction sequence, symbol names, section layout or linkage.

The experiment was not committed as implementation because adopting the static
array changes ownership of the shared window descriptor/action object and its
guard. The independent constructor owner should evaluate it alongside the
`0x804CFDE0` data split and `0x805D6458` symbol-localization plan. Its object
was compiled only in `/tmp/pso-keyboard-work`; the fork branch retains the
validated explicit-copy implementation.

## Unsigned glyph-loop emission experiment

Original glyph loops at `0x8026176C`, `0x80261984`, `0x80261AC4` and
`0x80261C50` use unsigned comparisons. In an isolated temporary compile,
using unsigned loop indices improved the glyph function from 81.26% to 83.74%
(1,860 candidate bytes versus 1,820 original), but added the unsigned-to-float
constant currently outside the split at `0x8044F260`. The original references
to that constant are confined to this unit.

With the proposed type-name and geometry block starting at `0x8044F110` and
the unsigned constant included through `0x8044F268`, the temporary object's
344 bytes of `.rodata` were byte-identical to the original. The experiment is
not in the source branch: integration must first agree on the shared type-name
boundary and the resulting exported-symbol and linker layout. Scores alone do
not establish semantic correctness or a linkable unit.

A follow-up temporary compile placed a 20-byte window descriptor before that
static action array. The resulting `.data` object was 548 bytes, matching the
original `0x804CFDE0..0x804D0004` bytes exactly; all 22 member-function
relocation offsets and targets also matched after accounting for the original
automatic object's leading `0x1c` bytes. The dispatcher comparison was 93.12%
(1,356 candidate bytes versus 1,324 original). This remains an emission
experiment: the descriptor's source-level type, initialization guard symbol,
section ownership and linkage must be reviewed before adoption.

## Native descriptor, geometry and actions (WIP)

Following the independent UI ownership review, this checkpoint claims the
observed type-name and geometry range `0x8044F110..0x8044F268` and the
window-descriptor/action range `0x804CFDE0..0x804D0004`. The exported descriptor
is a 20-byte size-checked prefix; the 22 action descriptors, runtime array and
one-byte guard are generated by CodeWarrior from a function-local static array.
The seven-byte tail before the next aligned `.sbss` object is not an explicit
second guard. The constructor takes the exported descriptor address and its
ignored-result dispatcher declaration now agrees with the definition.

The native-data checkpoint passed standalone compilation and the regression
checks below. Its original constructor base-call conflict was subsequently
resolved by the coordinated caller change documented in
`keyboard-constructor-abi-evidence.md`.

### Native-data verification

The initial one-byte `.sbss` split endpoint caused dtk to reject the following
automatic split's alignment. The final split retains the aligned eight-byte
range `0x805D6458..0x805D6460`, but marks the single-byte guard local. The
compiled unit emits one guard byte; `link_units.py` accepts the remaining seven
bytes as alignment padding, with no duplicate guard object.

The locked rebuild passed the original DOL SHA-1. `check_pr.py --no-build`
passed against the assigned base (+892 matched data bytes, no lost exact code,
data or linked units) and `report_delta.py --check` passed against the earlier
WIP checkpoint (+884 matched data bytes). All 3,536 linked units remain valid.
The unit's `.data` (548 bytes), `.rodata` (344 bytes) and `.sbss` (8-byte split)
compare at 100%; `.data` and `.rodata` section alignment is eight bytes. A
separate source-object layout check found no alignment, extra-section, global
data-layout, function-order or exported-descriptor mismatch. The unit is not
linkable yet: `.text` is non-exact and 20 original `.sdata2` symbols remain
missing from the source object. The original DOL still uses fallback for this
unit, so its hash does not validate runtime behavior of these new bodies.

The latest report scores the dispatcher, glyph renderer and grid renderer at
95.22%, 79.10% and 95.51% respectively. Earlier percentage figures describe
individual experiments and are not the scores of this combined object. The
constructor declaration and use of the 20-byte descriptor compile with all
three functions exact. The subsequent base-constructor ABI repair and its
validation are documented separately. Independent review is required for
both checkpoints.

### Remaining small constants and constructor constraint

The original `0x805DD078..0x805DD0C8` section contains twenty floats. A
standalone experiment defining all twenty exported constants in source emitted
those 80 bytes followed by another 80 bytes of compiler-generated literals.
That 160-byte `.sdata2` is not linkable at the original 80-byte split, so the
experiment was not adopted. The zero float at `0x805DD090` is also referenced
by the neighboring constructor; original code references to the other nineteen
are confined to this unit. Reconciling the literal pool and exported zero
constant needs an emission-aware follow-up, not a second hand-written table.

The actual base constructor is `TWindowDD::construct_base(u8 *, s16, u8 *)`.
A direct member call with the existing `s16` keyboard-constructor parameter
changes the original `extsh r5,r31` to `mr r5,r31`, losing the constructor's
exact match. An isolated test with a 32-bit incoming parameter and an explicit
short conversion restored the exact constructor, but caused the already
source-linked `TKeyBoardControl__ct` caller to gain an `extsh` instruction.
The subsequent coordinated caller solution preserves both constructors and
the chat caller. It replaces the free declaration with the typed member call;
see `keyboard-constructor-abi-evidence.md` for the full evidence and limits.
