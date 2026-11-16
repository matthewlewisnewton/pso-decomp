# Native item-menu and effect helpers

The unit `pso/item/TItemMenuCtrl_80115AF0.cpp` covers
`80115AF0..80115C24`: five functions and 308 code bytes. At fork-main base
`7ebf37b81371f6c04b17fceb9120716255d4f02d`, its functions already match and
link from source, but the zero literal at `805DABE8` remains in an original
fallback pool. This recovery preserves the existing code coverage, replaces
raw call adapters with native C++, removes one scheduling pragma, and links
the four-byte literal from its consuming unit.

## Interfaces supported by the original calls

The entry at `80115AF0` adds `1C` to its receiver and forwards the incoming
mask in r4 to `FlagWord::set`. Its caller, `TItemMenuCtrl::open_menu` at
`80115A78`, supplies `1 << arg0` in that register. The existing constructor
at `80115A28` constructs a `FlagWord` at `this + 1C`; the flag query at
`801059E8` reads the same word. A `FlagWord menu_flags` member and
`void set_menu_flags(u32 mask)` replace the no-argument, integer-returning
adapter. Compile-time assertions check the `1C` member offset and `20` size.
This does not recover the other menu-controller construction interfaces.

The factory at `80115B14` checks split-screen mode, allocates `4C` bytes,
checks allocation failure, and calls the established `TEffStarLight2D`
constructor with its three incoming arguments. The shared effect declaration
already checks that class size and its members. Native `new TEffStarLight2D`
reproduces the entire 108-byte function, including the null path, without
scheduling control. Its three original callers are in
`SpecialProjectileWeapons.cpp`, `TItemShootGun_ctor.cpp`, and
`TItemAttackCol.cpp`; they now include the shared factory declaration.

The position and parameter arguments retain the constructor's existing
`void *` compatibility boundary. The [starlight recovery](starlight-native-unit.md)
documents that boundary and the established object layout. This change does
not recover all caller parameter-block types or initialization, and the
projectile follower retains its existing integer-held effect pointer.
The signature names at the two entries change at their original addresses;
they express observed interfaces rather than recovered original mangling.

## Compile, compare, research

The first native version matches four functions exactly. The float clamp
at `80115B80` scores 99.6875% because replacing the exported constant read
with `0.0f` introduces a local pool relocation; its instructions and size
are unchanged. Whole text initially scores 99.93507%.

After that comparison, the repository's
[starlight compiler comparison](starlight-native-unit.md),
[scalar-constant emission notes](tboss6type1-sdata2-constants.md), and
[conversion-pool investigation](conversion-pool-constants.md) supplied the
relevant precedents: compiler-generated literals can stay local once their
real owner and absence of external consumers are established. No external
source or compiler workaround is needed here.

The original instruction is a four-byte `lfs` from `805DABE8`. The active
original object inventory has exactly one reader of `lbl_805DABE8`, this unit.
The initial fallback allocation groups that zero with four trailing zero
bytes up to `805DABF0`; no symbol or reader identifies a second value.
The normal literal produces a four-byte `.sdata2` section aligned to eight.
Claiming `805DABE8..805DABEC`, correcting the symbol extent to four, and
using the guarded `localize_split_globals.py` check makes its relocation
and data match. The linker recreates the four-byte gap before the next
aligned contribution. No synthetic padding object or explicit data dump is
introduced. The previous fallback pool disappears.

## Validation

A fresh baseline was built from the stated main commit with the repository's
GC/2.6 compiler, decomp-toolkit 1.8.4 and objdiff-cli 3.6.1; unchanged retention
metadata passed before editing. All five final functions, both allocated
sections, their alignments, and the five text relocations match the newly
split original object. All four caller units remain exact.

`tools/check_pr.py` passes: the original DOL SHA-1 is reproduced, no exact
function/code/data/link coverage is lost, and all 3,616 source-linked units
remain exact. Matched and linked data each gain four bytes; matched code and
functions are unchanged. Total reported data decreases by the four bytes of
alignment padding that leave the old fallback pool. Link selection and
retention metadata remain unchanged. The generated porting inventory records
the removed scheduling pragma; no new compiler exception is introduced.
