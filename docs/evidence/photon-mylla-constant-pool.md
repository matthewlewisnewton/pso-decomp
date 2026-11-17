# Photon Mylla scalar pool

Base: fork main `8e27ed9a61756b650fde9788d356785e68929402`.

The original `TPhotonMylla.cpp` range is `0x801AD4A8..0x801ADC6C`.
Its five functions already match and link, but the adjacent fallback unit
`auto_11_805DC1F8_sdata2` supplies their scalar constants. A census of all
8,557 configured original and compiled objects finds references to these
eleven symbols only in the original and compiled Mylla objects. Assigning
`0x805DC1F8..0x805DC224` to this existing owner therefore removes the whole
scalar fallback. This recovers data ownership, not an original source filename
or the complete Photon Blast class hierarchy.

## Original loads

| Address | Float | Use |
|---|---:|---|
| `805DC1F8` | 0 | Four float material channels reset at `801AD4A8` |
| `805DC1FC` | 30 | Summon effect's vertical offset in task update and constructor |
| `805DC200` | 0.5 | Magic-square constructor argument in both callers |
| `805DC204` | 100 | Task counter comparison before changing summon state |
| `805DC208` | 118 | First particle event counter comparison |
| `805DC20C` | 45 | Vertical offset shared by three particle events |
| `805DC210` | 120 | Second particle event counter comparison |
| `805DC214` | 122 | Third particle event and hit counter comparison |
| `805DC218` | 116 | Counter threshold before fading the first material channel |
| `805DC21C` | -1 | First-channel fade threshold |
| `805DC220` | 0.15 | Per-update first-channel decrement |

The reset uses the existing float-color view also passed to
`set_constant_material` by render. Its four stores remain at object offsets
`0x184`, `0x188`, `0x18C`, and `0x190`. Other provisional layouts and external
call boundaries in this unit remain outside the constant-pool recovery.

## Compiler comparisons

The first probe defined the existing extern constants after their uses.
GC/2.6 with the unit's existing flags retained all five exact functions but
emitted 44 bytes of writable `.sdata`, rather than `.sdata2`. The
[loading-particle investigation](now-loading-constant-pool.md) records the
same placement issue; [laser-light recovery](laser-light-constant-pool.md)
uses ordinary float literals to recover a private pool.

Replacing all eleven loads with literals emits the exact 44 scalar bytes
in address order. Two functions initially differ: `run_task` has
`fadds f0,f0,f1` instead of `fadds f0,f1,f0`, and the constructor loads the
constant before the stack value. The
[character-select investigation](chr-select-confirm-cell-store.md)
describes parse-time commutative-expression ordering, and the
[window-light investigation](window-effect-light-recovery-evidence.md)
records how source expression shape affects float scheduling.

Measured alternatives for the two vertical-offset updates:

| Form | Task update | Constructor | Scalar bytes |
|---|---:|---:|---|
| `value = value + 30.0f` | 99.95025% | 99.37173% | Exact |
| `value = 30.0f + value` | 99.95025% | 99.37173% | Exact |
| `value = value - -30.0f` | 99.70149% | 99.68587% | Different |
| `value += 30.0f` | 100% | 100% | Exact |

Compound assignment retains the original operand and load order without
introducing a compiler setting, intrinsic, padding object, or assembly.

## Layout and validation

The last original symbol described eight bytes although only its first four
are loaded as a float. Correct its extent to four. The four zero bytes at
`0x805DC224..0x805DC228` are alignment before the following Pilla pool, whose
compiled section has alignment eight. As in the loading-particle case, leave
these bytes to the native linker rather than defining a padding variable.
The private labels are localized with `localize_split_globals.py` only after
its complete configured-consumer check passes.

The completed owner has five exact functions (1,988 code bytes), eight bytes
of `.rodata`, and 44 bytes of `.sdata2`. All allocated section bytes, sizes,
and alignments match, and all 132 normalized runtime relocations agree.
The linker selects the compiled Mylla object and no original scalar fallback.
The existing source linkset and generated retention block remain unchanged.

The fresh baseline and final native builds reproduce DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. `tools/check_pr.py` passes with
44 additional matched and linked data bytes and no function, code, or linked-unit
regression. The only coverage removal is the four zero alignment bytes,
recreated by the linker. No new porting exception is introduced.
