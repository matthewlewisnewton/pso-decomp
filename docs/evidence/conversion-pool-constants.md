# Conversion-pool constants

Follow-up to [issue #233](https://github.com/matthewlewisnewton/pso-decomp/issues/233).
This records how the original executable shares the two integer-to-double
biases, what this compiler can and cannot reproduce, and how the link tools
treat the symbols decomp-toolkit exports for them.

## Current status after technique recovery (2026-11-09)

The TTecCtrl fold on main base `224eb99838471c243b20c305eddac75e7ff76c8f`
retires the per-unit `name_pool_symbols.py` hook described below. The original
cross-split readers now share one source object; both conversion biases are
compiler-generated locals, and the object links without rewriting symbols.
The remaining sections record the earlier split investigation, not a current
requirement to retain that hook. See [technique recovery](upstream-technique-control.md).

## The two values

PowerPC has no integer-to-double instruction. GC/2.6 builds a double whose
high word is `0x43300000` and whose low word is the integer with its top bit
flipped, then subtracts a bias. The unsigned bias is `2^52`
(`0x4330000000000000`). The signed bias is `2^52 + 2^31`
(`0x4330000080000000`). A cast in C is enough to emit that sequence. The load
of the bias is a pair of `lis`/`lfd` relocations, or an `lfd` against a local
`@N` pool symbol.

Those bytes are not, by themselves, proof that a symbol is compiler-generated.
A named object can hold the same value. The tools treat a symbol as a
conversion-pool constant only when the original split object and `symbols.txt`
both say it is an 8-byte object in `.rodata` or `.sdata2` and those eight
bytes are exactly one of the two biases. A larger object that merely contains
the pattern is left alone.

## What GC/2.6 does with them

The compiler used here is Metrowerks Embedded PowerPC 2.4.7 build 107, the
repo's GC/2.6, run through the same wibo wrapper as
[the conversion-pool probe](../../tools/probes/conversion_pool/README.md).
Game code is compiled one translation unit at a time with `-O4,s`,
`-inline off`, and `-sdata2 4`. An 8-byte pool entry then lands in `.rodata`
as a local `@N` object. It is not a global, and it is not shared with another
file.

Checked on 2026-11-04, with the compiler and linker hashes recorded in the
probe README:

- `#pragma merge_float_consts on` is an illegal pragma. The 2015 Freescale
  Power Architecture manual describes that pragma as putting each floating-point
  constant in its own variable so the linker can merge equal values, and says
  the default is off. This GameCube compiler does not implement it.
- `-ipa` is an unknown option. There is no program-wide IPA mode to turn on.
- `-pool off` still emits the signed bias as a local `.rodata` object. That
  switch does not stop conversion pools.
- Linking two translation units, each converting an `int` to `double`, and
  keeping both functions with `FORCEACTIVE`, produced a `.rodata` of 24 bytes:
  the first unit's bias, that unit's `6.0`, and the second unit's own copy of
  the same bias. The linker did not collapse the two biases into one.

A named `const double` in the same translation unit is not merged into the
pool either. Used by value, the compiler copies it into the pool and also
emits the global. Used only through a pointer, it emits the global and not a
pool entry. That is a separate object, not a renamed pool slot. Defining the
bias by hand therefore cannot recreate a single 8-byte pool, and it cannot
make a later translation unit's conversion relocate to this one.

The probe's linker-script alias (`synthetic_pool_export = _f_rodata`) lands
on the pool only when that pool is the first and only thing in `.rodata`.
The alias is an absolute symbol of size 0, not an 8-byte `.rodata` object.
Putting another double ahead of the pool moves the alias onto the wrong
bytes. `TObjBoss2Tunnel_8007C5C0` is that shape: 8 bytes of `6.0`, then the
signed bias. An alias of the section start would name `6.0`.

## What the DOL shows

decomp-toolkit splits the linked executable back into objects and gives a
global name to each relocation target. A load in one split whose address falls
in another split becomes an undefined reference to that name. That is a fact
about the finished DOL, not a fact about the `.o` files the compiler wrote.

Several of these 8-byte biases are loaded from a different split than the one
that contains the bytes. The finished DOL therefore has a shared address that
per-file GC/2.6 does not reproduce: each file gets its own local pool for a
cast. The original program did end up with one shared address, and this
compiler, with the flags it actually accepts, will not do that again from
source. No source arrangement tried here produces a global pool entry of the
original size and a second file whose cast relocates to it.

`scope:local` is the end state for a bias that nothing else loads. It tells
decomp-toolkit to stop exporting the split's copy, which is what the compiler
emits on its own. A bias that another split loads has to stay a real exported
definition. Two such cases were found in the original DOL, and both are now
handled without a second copy:

- `TObjBoss2Tunnel_8007CF0C` used to load
  `TObjBoss2Tunnel__data_80438A90` from `TObjBoss2Tunnel_8007C5C0`'s split.
  The two ranges are now the consolidated `pso/boss/TObjBoss2Tunnel.cpp`
  unit, so the bias is `scope:local` there and the cross-unit load is gone.
- `TTecCtrl` still loads `lbl_8044D078` from
  `TTecCtrl_8022C444`'s split. That unit links, and its compiled object names
  the emitted pool object as the split's global (see below).

## Naming a referenced pool

Source cannot turn the local `@N` pool object into the split's global without
changing the object, so a referenced bias uses a post-process instead.
`tools/name_pool_symbols.py` runs after MWCC, before the link. For each
missing non-function object that `link_units.conversion_pool_kind` identifies
as one of the two biases, it finds the local 8-byte pool object at the split
symbol's section and offset with identical bytes, renames it to the split's
name with `objcopy`, and makes it global. The section contents and every
relocation are unchanged; the symbol name and binding are now the ones the
original split exports.

`pso/misc/TTecCtrl_8022C444.cpp` uses the hook. Its `.rodata` is only the
unsigned bias, and the compiled object's `@50` is at the same offset as
`lbl_8044D078`. The renamed object defines `lbl_8044D078` as an 8-byte global
at `.rodata:0`, so `TTecCtrl`'s undefined reference resolves to the existing
pool bytes. The unit is now in `linked_units.txt`, and the DOL still hashes to
the original `0d85744b51d7379efb025a943d0cd5aaae2191a3`. The hook refuses a
`symbols.txt` bias that has no matching local pool object, rather than
inventing a definition.

This is a per-unit build exception (`post_object` in `configure.py`); a port
drops it and keeps the cast. It is not a way to localize an unreferenced pool
or to waive a section-size check.

## Duplicate copies that hide a size mismatch

`src/pso/object/TObjFish_8033CCC8.cpp` defined the signed bias as
`lbl_80477F08`. The cast in `render_fade_model` already emits that bias as a
local pool entry, so the compiled `.rodata` was 16 bytes of the same pattern
twice. The original section is 8 bytes. objdiff scored the section 100%
because the first 8 bytes match. The same file defined `lbl_805DFA64` (`0.7f`)
and `lbl_805DFA68` (`179.0f`, `0.0f`) and also wrote those values as literals,
so `.sdata2` grew a second copy ahead of the named symbols (20 bytes against
the original 12).

The named double is gone. The cast supplies the only `.rodata` entry, 8
bytes, and `render_fade_model` still matches. `lbl_80477F08` is
`scope:local`: no other split object names it.

`run_task` adds `0.7f` and clamps at `179.0f`. Writing those as the named
floats `lbl_805DFA64` and `lbl_805DFA68` puts the right 12 bytes in `.sdata2`
but changes seven register fields at the start of `run_task`. Keeping `0.7f`
as a literal and `179.0f` as `lbl_805DFA68[0]` matches those instructions and
the bytes `0.7f`, `179.0f`, `0.0f`. The literal occupies the original
`lbl_805DFA64` slot, so that symbol is `scope:local` too. Nothing else loads
it. The unit still does not link. `TObjFish__sub_8033D1AC` is part of the
original object and is only declared in this file. The compiled `.sdata2`
section is aligned to 8 bytes and the original section is aligned to 4; the
12 data bytes match, and this unit is not linked.

A scan of compiled objects against their original splits, looking for a
`.rodata` or `.sdata2` that was longer than the original and held more
aligned copies of either bias, found this Fish unit and no other. After the
fix, the same scan finds none. It only sees objects that were actually built.
The size check in `link_units.py` remains the gate.

`lbl_805D9620` in `TObjPlayer_8008DCF0` is a 4-byte `.sdata2` float, not one
of these biases. A missing symbol with a similar name is not a conversion
constant unless the bytes say so. `TObjPlayer_8008DCF0` is already matched;
its float is a real named zero, not a pool entry to localize.

## Referenced biases and remaining units

The two referenced biases found on the DOL are resolved. `TObjBoss2Tunnel`'s
signed bias became local when its two splits were consolidated. `TTecCtrl`'s
unsigned bias is the pool named by the post-process above, and
`TTecCtrl_8022C444` is linked. `TLobby_801E2F94`'s signed bias was
unreferenced; it is `scope:local` and that unit is linked too.

`TWindowSubSymbolChatParts` matches and its `.rodata` is the signed bias
`lbl_8044FC08`. Nothing else loads that symbol, so it is `scope:local`. The
unit still does not link: its compiled object references `lbl_805DD7F8`, and
the other missing symbols stay exported until each one has a definition.

`TObjPlayer_801C7430` now links with its compiler-generated signed bias
`TObjPlayer__data_80447130`. Using the five unit-owned floats as C++ literals
lets GC/2.6 emit the original 20-byte `.sdata2` pool in order and reuse those
entries for loads that already used literals. The split marks the bias and
the five floats local after checking that no other object refers to them.

`lbl_8043FFE0` in `TNpcPlayer` and `lbl_80440390` / `lbl_804403A0` in
`TOBoss4Rock_801589E8` are now `scope:local`; `TNpcPlayer` links and the
remaining `TOBoss4Rock` unit fails for reasons other than the bias.

`TObjPlayer_8008DCF0` is not in this set. Its missing-looking float is the
4-byte zero above.

## What the tools do

`link_units.py scan` prints every missing symbol whose original object is one
of these two biases. `localize_split_globals.py` labels the same symbols.
An unreferenced bias is marked `scope:local` even when another missing symbol
in that unit is referenced elsewhere. A referenced bias is not marked, and
the plan names the object that loads it. `--pools-only` limits a run to the
biases, so a sweep does not also localize unrelated missing symbols.

`name_pool_symbols.py` is the one post-process for a referenced bias. It runs
from `configure.py` through `post_object` on a compiled object, names the
matching local pool entry as the split global, and fails if the bytes,
section, or offset do not match. Use it only for a unit whose bias the DOL
references from another split; unreferenced biases stay `scope:local`.

The `scope:local` label is not a size waiver and not a reason to link a unit.
After a write, rebuild and check the original bytes, the section size, the
relocations, and the DOL hash.

`TBoss6Demo11_TYPE1_DEAD_progress_limit` (0x805DFA68, formerly `lbl_805DFA68`)
is the original 8-byte `.sdata2` object `{ 179.0f, 0.0f }`. `run_task` reads
`[0]` as its clamp limit instead of a `179.0f` literal, because a literal would
emit a second copy; `0.7f` stays a literal. Approved by Matt on 2026-11-04.
