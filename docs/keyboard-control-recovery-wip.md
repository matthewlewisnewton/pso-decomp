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
the local original split object reported 91.09% for this function (856 original
bytes versus the candidate). This is not an exact match; register
allocation, code layout and data/relocations require further work. The initial candidate failed the regression check because its unsigned
conversion introduced an extra eight-byte .rodata constant. The current signed
conversion preserves the original unit data in a targeted comparison; the
locked two-job rebuild and `tools/check_pr.py --no-build` passed: no exact
functions, data ranges or linked units regressed, and all 3,536 linked units
passed. The baseline DOL hash passed; this unit still uses original fallback
for linking, so that hash does not establish correctness of the new body. The unit is not linked from source and the new bodies are not exact.
No original binaries or generated objects are included in this checkpoint.

## Input dispatch candidate at 0x80260904

The original data object's first 22 three-word member-function descriptors
refer to `vt0` through `vt21`, and the function copies them to a second array
on first use, guarded by a byte at `0x805D6458`. The candidate accesses that
existing object through a size-checked local view and retains the observed
controller, character filtering, sound, and child-dispatch paths. The data
object and child class ownership remain provisional shared interfaces; no
shared definitions are changed.

The targeted GC/2.6 compile succeeds. Its input dispatcher is 704 bytes against
1,324 original bytes, with objdiff reporting 40.28%; a loop expresses the
original expanded copy and this is not an exact-code claim. The previous
grid renderer remains 91.09%, and targeted `.rodata` comparison remains 100%.
The locked two-job rebuild and regression checks passed with no lost exact
functions, data or linked units. This does not validate runtime behavior of the
source body, which is still linked from original fallback.

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
grid frame renderer remain 40.28% and 91.09% respectively. The targeted
`.rodata` comparison is 100%. The locked two-job incremental rebuild and
`tools/check_pr.py --no-build` passed with no lost exact functions, data or
linked units (3,536 linked units checked). None of these scores proves exact
code, relocations or runtime semantics; the DOL still uses the original unit.
