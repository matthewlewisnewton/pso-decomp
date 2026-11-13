# Gryphon shockwave constant ownership

Base: fork main `7ebf37b81371f6c04b17fceb9120716255d4f02d`.

`TBoss5GryphonShockWave.cpp` already supplied six exact functions (912 code
bytes), its compiler-generated vtable (24 bytes), and its signed conversion
bias (8 bytes). Its three float loads still referenced an original-only
`.sdata2` fragment. The original assembly has exactly these readers:

| Constant | Value | Read |
|---|---:|---|
| `0x805D8EE8` | `1.0f` | `run_task`, `0x80066850`, particle-model argument |
| `0x805D8EEC` | `5.0f` | constructor, `0x800669B8`, control-point Y store |
| `0x805D8EF0` | `0.07f` | constructor, `0x800669FC`, distance-to-duration scale |

Replacing the external loads with literals first preserved every instruction
but changed those three relocation targets: objdiff scored `run_task`
99.95763% and the constructor 99.84615%. Assigning
`0x805D8EE8..0x805D8EF8` to the source unit made both functions 100%.
The default GC/2.6 compiler settings emit the three floats in that order;
no compiler override or named duplicate constants are needed.

This follows the literal-pool recovery described in
[conversion-pool constants](conversion-pool-constants.md) and the distinction
between constants and trailing alignment in
[window effect light recovery](window-effect-light-recovery-evidence.md).
The old eight-byte extent of `lbl_805D8EF0` combined one float with four zero
alignment bytes. The original uses a single `lfs`, and the neighboring
`TBoss5GryphonSnarl` pool begins at `0x805D8EF8` with eight-byte alignment.
The corrected symbol is four bytes. The compiled pool has 12 bytes, and
linker alignment recreates the four-byte tail. No padding array is written
in source. The four zero bytes at `0x805D8EE4` precede the pool and become
unowned alignment padding when the old generated fragment disappears.

After a fresh split and build, the repository localization tool checked all
8,563 active original and compiled objects, including original fallback
units. No outside object references any of the three labels. They are now
local, allowing the compiler-generated literal symbols to own the bytes.

The complete unit retains all six exact functions and its vtable and
conversion bias, and gains 16 matched and source-linked data bytes including
the recreated alignment tail. The original DOL SHA-1 remains
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The four preceding padding bytes
leave report coverage; no function, live data, or linked unit is lost.
