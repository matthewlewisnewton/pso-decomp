# Dragon compiler consolidation investigation

Date: 2026-11-13. Source baseline: `08c178922f`, with the existing
`TBoss8Dragon.cpp` GC/2.0 profile. This investigation found no acceptable
GC/2.6 replacement and makes no source change. Retain GC/2.0 for this unit
until the two regressions below are repaired.

## Measured blocker

The current GC/2.0 source matches 138 of the original unit's 141 functions.
Changing only the compiler to GC/2.6 loses two previously exact functions:

| Function | GC/2.0 size | GC/2.6 size | GC/2.6 original match |
|---|---:|---:|---:|
| `TBoss8Dragon__sub_802FB1B0` | 112 | 116 | 88.89286% |
| `TBoss8Dragon__sub_802FB220` | 112 | 116 | 87.14286% |

Both functions copy a 20-byte `S_802FB220` template to the stack, replace
dynamic fields, and pass the record to `setup_instance`. The generated copy
uses a two-iteration pair-copy loop and a trailing word. GC/2.0 schedules
the load of `TBoss8Dragon__data_80541DDC[0]` before the final copy store,
using `lis` followed by `lwz` with the symbol's low relocation. GC/2.6
instead emits `lis` and `addi` for the global address, then a separate
`lwz` after the final copy store. Argument-address and zero-register
preparation also move around this sequence.

The low relocation consequently belongs to an `addi` rather than the
original `lwz`; the extra instruction changes subsequent offsets. This is
a code and relocation-position difference, not merely anonymous-symbol
renaming. Against the compiled GC/2.0 baseline, only these two function
outputs change. The existing `.rodata`, `.data`, `.bss`, and `.sdata2`
contents retain their baseline matches. That does not establish that this
still-unlinked unit's data fully matches the original.

The broader audit also tested GC/1.3.2: it changes 60 function outputs
relative to GC/2.0, so it does not provide a straightforward alternative.

## Source and setting probes

Isolated full-unit candidates tested direct pointer-array access instead
of the global overlay cast; typed and const pointer snapshots; an early
float snapshot; const-correct external template declarations; const
template temporaries and pointers; separate declaration and assignment;
ordinary `memcpy` and the existing `__memcpy` form; consistent global
pointer-block declarations; and earlier BSS definitions with their
relative order retained. None preserved the two functions under GC/2.6.
An early float snapshot moves the load before the copy loop, also unlike
the original.

Supported flag probes included scheduling, propagation, common
subexpression elimination, lifetimes, peephole optimization, strength
reduction, loop invariants, dead stores, data pooling, optimization levels,
debug symbols, common storage, small-data thresholds, deferred inlining,
and processor selection. Some regress many additional functions; none
solves the pair. GC/2.6 rejects `-ipa`.

Temporary scoped `opt_pointer_analysis` on/off and propagation,
common-subexpression, and lifetime controls also failed, including
combinations with the ordinary pointer snapshots. No new pragma was
landed. Unsupported pragma diagnostics were excluded as evidence of a
working optimization mode. The local archive contains 66 compiled variant
objects and their diagnostics; it is a finite experiment, not a proof
that no ordinary source form or supported setting can match.

A focused follow-up added five candidates guided by the alias implementation.
Three inline helpers return the parameter aggregate by value from a const
reference, a const pointer, or a by-value argument. All three actually inline
under `-inline on,deferred` without emitting helper bodies, but retain the
same two differences. A helper returning the record after setting its dynamic
float field produces larger differences. Substituting the existing shared
`EffectGeometryParameters` type also retains the original pair of differences.
These candidates do not justify a production helper or type change.

## Comparing exposed defaults

The stock executables were queried with
`-help all,normal,obsolete,deprecated,ignored,meaningless,compatible`.
Their complete option help is identical except for the version/build-date
banner: both identify as Embedded PowerPC 2.4.7, with GC/2.0 reporting build
92 and GC/2.6 reporting build 107.

Actual compilation with the unchanged Dragon production flags and
`-opt display` appended **after** `-O4,s` and the other options reports the
same active profile in both compilers:

| Setting | GC/2.0 and GC/2.6 |
|---|---|
| Global optimizer level | 4 |
| Optimization goal | Size |
| Extra global optimizations | None |
| Peephole optimizations | On |
| Instruction scheduling | GEKKO |

The help also expands `-O4` to optimization level 4, peephole optimization,
and scheduling, and the `s` modifier to optimize-for-space in both executables.
There is no exposed option/default discrepancy in these measurements to
correct by spelling out the same profile. Identical reported options do
not establish identical hidden internal state or optimizer implementation.
The alias-analysis version branches below are compile-time implementation
choices, not documented switches selecting an older algorithm. Disabling
the entire scheduler changes many additional functions and does not recover
this pair.

The exact help, banners, and active-profile diagnostics are archived under
`/tmp/pso-gc20-dragon/defaults/{2.0,2.6}-{help,version,opt-display}.txt`.

## Compiler implementation evidence

Static inspection used the local mweppc checkout at commit
`19365baddf770e61fce8a2909419d844c5eef29d`, under
`/tmp/tombstone-mweppc-reference-20261101`. Its
`src/optimizer/Alias.c` has explicit GC/2.5 version boundaries:

- `add_aliased_locals_to_worst_case` and `is_address_load` add escaped
  `DLOCAL` objects to `worst_case_ptr` unconditionally on newer versions;
  older branches check `!is_safe_const`.
- `gather_instruction_alias` uses a different implementation after that
  boundary.
- `src/backend/CodeGen.c` and `make_distinct_virtual_alias` attach distinct
  alias identities to incoming readonly/restrict pointer parameters.
- `src/optimizer/StructMoves.c` selects `move_block_via_inline_loop` for a
  20-byte aggregate under optimize-for-size. `load_displaced_address` clears
  the operand's object identity, and the loop's word loads/stores use a null
  object argument. The trailing `copy_chunk` operates through the resulting
  updated pointers. Merely renaming the aggregate or introducing an inlined
  value-return helper does not avoid that expansion in the tested objects.

These changes support investigating the dependency between the stack-copy
tail and global load. They do **not** prove which branch the stock compiler
takes for these particular non-const locals: this investigation did not
trace the executable. A focused next step is to trace alias propagation
and load-address fusion for these two functions, using the method in
[the Moja compiler investigation](moja-compiler-tracing.md), before trying
further source forms. A faithful readonly/parameter contract would need
independent evidence; adding qualifiers solely to move instructions is
not an established repair.

## Reproduction and validation boundary

The parent audit verified the original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3` and freshly split it using this
checkout's symbols and splits. Its local archive is
`/tmp/pso-compiler-consolidation-20261113`:

- `objects/pso__boss__TBoss8Dragon.cpp/GC_2.0.o` is the fresh source baseline.
- The same directory's `GC_2.6.argv.json` records the exact compiler command;
  `GC_2.6.original.json` records its original-object comparison.
- `original/obj/pso/boss/TBoss8Dragon.o` is the fresh original split object.

Probe scripts, candidate sources, objects, and diagnostic/diff files are
under `/tmp/pso-gc20-dragon`. They use the installed tools read-only and
write only isolated outputs. A candidate comparison can be replayed with:

```sh
/home/matt/workspace/pso-decomp/build/tools/objdiff-cli diff \
  -1 /tmp/pso-compiler-consolidation-20261113/objects/pso__boss__TBoss8Dragon.cpp/GC_2.0.o \
  -2 /tmp/pso-gc20-dragon/candidate.o \
  -o /tmp/pso-gc20-dragon/replay.json \
  -c functionRelocDiffs=data_value
```

Use the fresh original object as `-1` to verify original-match preservation.
The stock GC/2.6 executable has SHA-256
`316e2a98236c23f3fc902243b157eaebf8ef2ad6edb88cfd632a15b6676fa9a8`.
No full build was run for these failing candidates. Any eventual repair
still needs complete-object and integrated no-loss validation from
[CONTRIBUTING.md](../../CONTRIBUTING.md). Extracted objects and compiler
outputs remain local and must not be committed.
