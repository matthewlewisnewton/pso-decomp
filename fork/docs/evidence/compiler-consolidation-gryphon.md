# Gryphon compiler consolidation blocker

Investigation date: 2026-11-13. Baseline source revision:
`08c178922f` (the compiler audit's unchanged source tree).

`pso/boss/Boss5GryphonBehavior.cpp` still needs its GC/2.0 profile. A
compiler-only change to GC/2.6 preserves the allocated data sections, symbol
layout and relocation targets, but changes three of its 168 functions:

| Function | Original size | GC/2.6 match |
|---|---:|---:|
| `TBoss8Dragon__sub_80063FB8` | 116 bytes | 92.06896% |
| `TBoss8Dragon__sub_8006402C` | 120 bytes | 92.333336% |
| `TBoss8Dragon__sub_800640A4` | 112 bytes | 91.78571% |

The complete `.text` section remains 34,984 bytes and scores 99.921104%.
All three functions currently match the freshly split original under GC/2.0.
GC/1.3.2 is less promising for this unit: the initial audit changes 38 function
outputs. No production source or compiler setting was changed by this
investigation.

## Common difference

Each helper copies a 20-byte effect template to the stack, replaces one or two
float fields using `boss5_gryphon_behavior_params[2]` and its arguments, and
passes the local descriptor to `TObjEneDD::setup_instance`.

Under GC/2.0, the copy loop's destination uses r7. Following its final load,
the global parameter-table address uses r5; the pointer load into r7 precedes
the `addi r5,r1,8` that prepares the descriptor argument. GC/2.6 uses r8 for
the loop destination and r7 for the global-table address, and moves the stack
argument address before the global pointer load. The functions retain their
sizes and relocation positions. The discrepancy is register allocation and
instruction scheduling, not a different descriptor layout.

## Tested source forms and settings

Scratch copies replaced the raw byte buffers and pointer casts in these three
helpers with the existing `EffectGeometryParameters` type and ordinary
`BattleMovementParams` member access. This cleanup alone produces the same
three differences. Other bounded comparisons included:

- Copy initialization, assignment and `__memcpy`; const template declarations;
  parameter pointers/references before and after the copy; and named scalar
  parameter values.
- Read-only views of the global pointer table, including combinations with
  propagation, CSE and lifetime analysis disabled locally. The array-reference
  forms failed to compile and are not evidence of a compiler-codegen result.
- Typed inline helpers returning the descriptor by value, using a source
  reference, source pointer or a local `__memcpy` result. The reference and
  pointer forms inline without emitting another helper and retain the same
  three discrepancies; the local-copy return form is worse.
- Sixteen complete-unit flag profiles: scheduling off; individual propagation,
  CSE, lifetime, peephole, dead-store, dead-code, strength and loop switches;
  pooling off; `-O3,s`, `-O3,p`, `-O4,p`; deferred inlining; and 750/604
  processor scheduling. None preserves the full object. Several retain the
  original three differences while changing additional functions.
- Scoped diagnostic pragmas for pointer analysis, block assignment, unrolling,
  strict strength reduction, optimization level and size optimization. None
  fixes the three helpers. Numeric `opt_pointer_analysis_mode` probes reported
  illegal-token diagnostics and were discarded rather than treated as
  successful setting changes. The source's existing missing-return warnings
  were also retained in the probe logs.

Capturing and using the pointer returned by `__memcpy` improves the three
scores to 95.17242%, 95.333336% and 95.0%. It gives the copy loop the desired
r7 destination, but puts the global-table address in r6 and moves `li r6,0`
later. It is not a preserving candidate and was not landed.

## Measured compiler trace

A follow-up traced `TBoss8Dragon__sub_80063FB8` in the original GC/2.6
executable, first with unchanged production source and then with the best
natural `__memcpy` return-value candidate. Both runs finished compilation.
Their complete object files are byte-identical to ordinary Wibo compilation
of the same sources, not merely equivalent in allocated sections:

| Source form | SHA-256, both traced and normal object |
|---|---|
| Unchanged source | `27f8f56f03d96f7d06ceff5a7f45d042c267310753960fdb0671a33269cbdc1d` |
| Captured `__memcpy` return | `cd56d6c3e1a61c8caad5d176ec580e85d330a63bac4c0d9ca33f22d554768af4` |

The trace reads frontend trees, PCode, alias objects and the interference
graph. It does not call functions in the inferior, alter optimizer state or
patch compiler instructions. A copied debugger script removes its original
`CMangler_GetLinkName` inferior call and selects the helper by its existing
C-linkage name. The installed retrowin32 hardcodes its debugger port, so a
task-local `bind` wrapper redirects only its IPv6 listener from 9001 to
19031; this changes emulator networking, not compiler behavior.

Both forms give the copy loop's loads/stores and its final word store the
same worst-case alias set. Its members include the 20-byte local descriptor,
the 12-byte `boss5_gryphon_behavior_params` pointer table, the 20-byte source
template and the compiler's `@worst_case@` object. The following global
pointer load has a precise table alias at offset 8, size 4, which overlaps
that set. Capturing the `__memcpy` return does **not** recover a more precise
copy-destination alias.

The PCode and allocation logs explain the register change:

| Value | Unchanged source | Captured `__memcpy` return |
|---|---|---|
| Copy-loop destination | virtual r36 → r8 | virtual r35 → r7 |
| Global-table address | virtual r43 → r7 | virtual r44 → r6 |
| Loaded movement pointer | virtual r44 → r7 | virtual r45 → r7 |
| Captured destination pointer | absent | virtual r34 (`output`) coalesced into r5 |

In the unchanged source, the first scheduling pass places the fixed r5
descriptor argument and fixed r6 zero argument before the global pointer
load. The global-table address therefore interferes with both fixed
registers and is assigned r7. It also overlaps the copy-loop destination,
which is assigned r8. The return-value form introduces virtual r34 early
and later coalesces it into r5. Its global-table address can use r6 instead,
and the copy-loop destination gets r7, but the final argument setup and
global-address instructions still differ from the target.

Eight trace-guided follow-ups named the global-table address before or after
the template copy, with ordinary optimization, propagation disabled,
lifetime splitting disabled, or both disabled locally. None preserved the
object. The early-address form with propagation disabled worsened the three
scores to 81.034485%, 81.666664% and 80.35714%; the other forms retained the
original differences. No follow-up source or pragma was landed.

## Compiler-source evidence and remaining question

The locally available versioned mweppc source at
`/tmp/tombstone-mweppc-reference-20261101/src/optimizer/Alias.c` documents
GC/2.5-and-later changes in `make_distinct_virtual_alias` and
`add_aliased_locals_to_worst_case`: distinct pointer aliases now depend on a
read-only pointee or `restrict`, and address-exposed locals are added to the
worst-case set without the earlier const-local exclusion. These changes are a
relevant historical hypothesis. The runtime traces establish the GC/2.6
alias set and resulting interference described above; they do not directly
trace GC/2.0's internal decisions.

The remaining question is whether an evidence-backed source contract can
retain precise identity for the compiler-generated loop's destination,
without an artificial data dependency, qualifier change or extra runtime
operation. Merely changing the buffer type or naming the table address did
not do so. The workflow in [Moja compiler tracing](moja-compiler-tracing.md)
provides a method for checking a new hypothesis. This finite investigation
does not establish that no natural GC/2.6 form exists.

## Reproduction artifacts and validation boundary

Local scratch artifacts are under `/tmp/pso-gc20-gryphon/`. The runners are
`probe.py`, `flags.py`, `more.py`, `returns.py`, `return_variants.py`,
`helpers.py`, `pragmas.py` and `readonly.py`; each saves its complete scratch
source, compiler diagnostics, object and objdiff JSON. They run from the
repository root, one compiler process at a time, and do not modify project
source. For example:

```sh
python3 /tmp/pso-gc20-gryphon/helpers.py
python3 /tmp/pso-gc20-gryphon/flags.py
```

The focused traces are under `/tmp/pso-gc20-gryphon/trace/{original,copy_return}/`.
`backend-*-before-regalloc.txt`, `regalloc-gpr-pass-1-all.txt` and
`regalloc-gpr-pass-1-assigned.txt` contain the relevant alias and allocation
records. `trace/parity.json` records the complete-object identity check.
`trace/debugger.py`, `trace/run.py`, `trace/port.c`, the task-local emulator
wrapper and per-run argv JSON preserve the tracing setup. Reproduction uses
the existing `/tmp/pr318o/bin/gdb` and
`/tmp/opencode/retrowin32/target/lto/retrowin32` installations:

```sh
python3 /tmp/pso-gc20-gryphon/trace/run.py original
python3 /tmp/pso-gc20-gryphon/trace/run.py copy_return
python3 /tmp/pso-gc20-gryphon/trace_guided.py
```

The captured baseline compile argv is in
`/tmp/pso-compiler-consolidation-20261113/objects/pso__boss__Boss5GryphonBehavior.cpp/GC_2.6.argv.json`.
It uses GC/2.6 with the current unit flags, including `-O4,s`, `-inline off`
and `-sdata2 4`. The compiler executable's SHA-256 is
`316e2a98236c23f3fc902243b157eaebf8ef2ad6edb88cfd632a15b6676fa9a8`.
The tools and generated includes are read from
`/home/matt/workspace/pso-decomp/build/`; all probe outputs stay under `/tmp`.

The prior audit's `original-comparison.json` compares the unchanged GC/2.0
object and the GC/2.6 candidate against an original object freshly split with
this checkout's metadata. Its original DOL SHA-1 is
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The new probes compare whole
objects with `objdiff-cli diff -c functionRelocDiffs=data_value`, rather than
scoring only the three target functions. These are isolated investigation
results. No candidate from this note passed a complete linked-build
acceptance gate, and GC/2.0 must remain until a replacement preserves the
original matches and source linkage.
