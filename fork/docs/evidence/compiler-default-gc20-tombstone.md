# Tombstone and De Rol Le in the GC/2.0 default migration

Investigation date: 2026-11-16. Source baseline `08c178922f`.
This investigation changes no production source or shared header.

## Tombstone: use the retained GC/1.3.2 compiler

Unchanged `pso/object/TObjTombstone.cpp`, with its existing flags, produces
an object under **GC/1.3.2 equivalent to its GC/2.6 baseline**. Allocated
section bytes, sizes and ELF alignment, defined external/weak symbol layout,
and normalized relocations all agree. Independent comparison against the
original split object finds **37/37 exact functions**. The compiler emits
no diagnostics. This removes the need for a GC/2.6 compiler exception
without source rewrites; integrated validation remains the root migration's
responsibility.

GC/2.0 instead differs only in the implicit assignment operator
`TObjTombstoneRecord::operator=` at original address `0x80076390`. Both
versions emit 172 bytes. GC/2.0 pipelines scalar loads across preceding
stores, using alternating registers; the baseline keeps most scalar
load/store pairs adjacent. The two array-copy loops already match.
The GC/2.0 operator's comparison score is 85.23256%.

A bounded repair pass before the successful GC/1.3.2 test tried ordinary
member copies, byte loops, standard and compiler-intrinsic memory copies,
scoped scheduling, and several optimizer settings. An explicit operator
using scalar members and intrinsic copies for the vector/arrays reproduced
the same GC/2.0 discrepancy. Const-removing local reference access did not
change the result and was not adopted. Whole-record copies changed the
instruction structure substantially. Scheduling disabled for the whole
unit and disabling peephole optimization regressed many unrelated
functions. Propagation and pointer-analysis controls did not fix the
operator. `-schedule once` was rejected by the command-line parser;
`#pragma scheduling once` was separately accepted for explicit operators
but did not restore the baseline. Scoped settings around the declaration
of the implicitly generated operator did not alter its output.

These exploratory rewrites are unnecessary now that unchanged GC/1.3.2
matches. GC/1.3 changes `update_render_flags` instead; GC/1.2.5n fails to
compile a `TRaderMapCore.h` base-class construction. Those are not preferred
alternatives to the complete GC/1.3.2 candidate.

## De Rol Le: GC/2.0 preserves all existing exact matches

The unit is currently not source-linked and already has two unmatched
functions. Fresh candidate compilation and original-object comparisons give:

| Compiler | Exact original functions | `sub_8002FE60` | `update_pulsing_colors` |
|---|---:|---:|---:|
| GC/2.6 | 108/110 | 97.96943% | 95.8% |
| GC/2.0 | 108/110 | 98.58079% | 95.8% |
| GC/1.3.2 | 87/110 | 85.96943% | 95.8% |

GC/2.0 changes only the already-unmatched `TBoss2DeRolLe__sub_8002FE60`.
It uses r5 rather than r6 for a stack descriptor copy's destination and
loads `TBoss2DeRolLe__data_805D4BA0` before the copy's final store, rather
than after it. The relocation follows that moved global load. Function
size, allocated data, section sizes/alignment and defined symbol layout
remain unchanged. The higher similarity score is not a new exact match,
but there is **no lost exact function** and no loss of source linkage.

Retaining GC/2.6 solely to freeze this unmatched output does not preserve
an exact match that GC/2.0 loses. Adopting GC/2.0 here is a reasonable
migration candidate, subject to combined no-loss and original-DOL checks.
GC/1.3.2 is worse for this unit, losing 21 currently exact functions, and
was not pursued. No source repair was needed for the GC/2.0 candidate.

## Reproduction

Artifacts live under `/tmp/pso-gc20-tombstone-repair/`:

- `tombstone_probe.py`, `more.py`: isolated source/header and flag variants;
  the original basename is preserved for every scratch translation unit.
- `older.py`: unchanged-source compiler comparisons.
- `unchanged-1.3.2/{out.o,diff.json,original-1.3.2.json,argv.json,log.txt}`:
  the successful Tombstone candidate, complete baseline and original
  comparisons, invocation and diagnostics.
- `derolle.py` and `derolle/{2.0,1.3.2}/`: De Rol Le unchanged-source
  probes, complete objects, invocations and comparisons.

The helpers use the same normalized-object comparison implementation as
`/tmp/pso-compiler-consolidation-20261113/normalize.py`. Fresh original
split objects come from that audit. GC/2.6 reference objects and production
argv come from `/tmp/pso-gc20-default-impact/objects/`. Installed compiler
executables, tool binaries and generated include files were read-only
inputs from `/home/matt/workspace/pso-decomp/build`.

No handwritten assembly, shared API edits, production source changes, or
new compiler flags are proposed. These results do not establish which
compiler Sega originally used.

## Combined acceptance

The final [GC/2.0 adoption](compiler-default-gc20-adoption.md) integrates
these compiler choices and passes the original DOL hash and all no-loss
checks. No experimental source changes are included.
