# Character-creation fade constant ownership

Validated against fork main `7ebf37b81371f6c04b17fceb9120716255d4f02d` with
CodeWarrior GC/2.6 and the pinned native build tools.

`TChCrEffFade.cpp` owns `0x8029400C..0x8029427C`: render, opacity update,
task update, destructor and constructor. Its update at `0x80294084` is the
only consumer of the fallback pool `0x805DD9F8..0x805DDA00`. Both loads use
`1.0f`: opacity remains one through frame 3, then follows
`1 - (frame - 3) / (duration - 3)`. A literal reproduces the compiler-owned
four-byte `.sdata2` value with alignment eight. The final four bytes of the
original range are zero alignment padding, supplied by the native link.
The split retains the entire eight-byte range; the symbol describes just the
four-byte value and is local because no other unit refers to it.

The constructor at `0x802941AC` establishes direction at `0x1C`, duration at
`0x20`, current frame at `0x24`, and render mode at `0x2C`. The opacity update
stores a float at `0x28`. Task update advances the frame by direction and
queues destruction at either interval endpoint. These accesses support the
shared class fields. Render passes its receiver to `draw_fade_strip`, so the
shared declaration is an instance method; the separately owned strip body
remains unchanged. `fn_80293E58` and `TCameraCtrl__sub_80068EF0` retain their
provisional names and existing call boundaries.

All five functions (624 code bytes), the eight-byte conversion constant in
`.rodata`, and the compiler-generated 24-byte vtable retain their original
bytes and alignment. All 25 runtime relocations retain section offsets,
types and normalized targets (including all four vtable slots). The new
`.sdata2` literal plus final alignment matches the complete eight-byte range.
Expanded linker inputs select the compiled fade object and contain no
`auto_11_805DD9F8_sdata2.o`; the active split inventory also lacks that fallback.
The report gains eight matched and linked data bytes with unchanged code,
function and data denominators. The original DOL SHA-1 and `tools/check_pr.py`
pass, including the unchanged-main and final retention checks. The unit was
already listed in `linked_units.txt`, so no linkset or retention change is needed.
