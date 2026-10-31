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
full regression check for that correction is pending. The baseline DOL hash
passed and the initial linked-unit check passed. Functions at `0x80260904` and
`0x802616BC` still have no source body, and the unit is not linked from source.
No original binaries or generated objects are included in this checkpoint.
