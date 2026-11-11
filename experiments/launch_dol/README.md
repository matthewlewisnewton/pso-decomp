# LaunchDol recovery experiments

`LaunchDolHandoff.cpp` reproduces **all 332 bytes and ten call relocations**
at `[0x8042E8C4, 0x8042EA10)` with stock GC/2.6 and the normal game compiler
flags. The body is typed C++ with `__isync()` and a two-instruction assembly
handoff: `mtlr entry; blr`. This is an exact target-specific candidate, not
100% portable C++ recovery.

The current `LaunchDol` symbol and unit end after 312 bytes at `0x8042E9FC`.
The remaining 20 bytes belong to the next split and are tracked by #285.
Consequently, the new candidate is **not a drop-in object for the current
link graph**. It remains outside the production inventory, guarded by
`PSO_LAUNCH_DOL_EXPERIMENT` and `__MWERKS__`. Production still uses its exact
generated-assembly provider. No host fallback or runtime execution is claimed.

`LaunchDol.cpp` preserves the earlier C++-only comparison control. It emits
the same size, but its entry load and linking CTR call differ from the
original nonlinking LR transfer. It is not a behavior-equivalent fallback.
The two files define the same symbol and must be compiled separately.

## What made the handoff match

The new candidate uses the production `-O4,s -inline off -sdata2 4` profile.
Three pragmas are scoped with `push`/`pop` around the helper and wrapper:

| Pragma | Observed requirement |
|---|---|
| `dont_inline off` | Allows the explicitly inline helper to expand despite the unit's `-inline off`. |
| `inline_depth(1)` | Restores the depth needed for that one expansion. Either inline pragma alone leaves an out-of-line helper. |
| `global_optimizer off` | Bypasses frontend transformations that otherwise change the loop addresses and register allocation around the assembly branch. |

`register void (*const entry)() = image->entry` lets MWCC select `r0` for the
assembly operand. The compiler emits the load, prologue, loops and trailing
20-byte restore; none is copied, sliced from an object or written in assembly.
The assembly branch leaves the loader frame in place, exactly as the original
instructions do. The subsequent compiler-generated restore is not a normal
fallthrough successor of that branch. Its possible independent entry and
original ownership are not established by byte equality.

This profile needs neither the control's `nocse,nostrength,noprop` switches
nor a production compiler override. With the new pragma, both loops can share
the offset temporary and use loop-local const source pointers. The retained
shared index/destination/length/zero locals and separate `raw_size` expression
matter to allocation. Moving those declarations into the loops, folding the
size expression, or replacing `zero` with a literal loses the exact match.
These are reproduction constraints, not recovered original source spelling.

## Comparison and isolated linkage

| Candidate | Emitted bytes | Comparison with current 312-byte symbol | Complete 332-byte native span |
|---|---:|---:|---|
| `LaunchDol.cpp`, historical probe flags | 332 | 93.39744% | Three different words |
| `LaunchDolHandoff.cpp`, normal game flags | 332 | 93.589745% | Exact, including all ten relocations |

The 93.589745% score includes the extent discrepancy. It must not be relabeled
100% against the current 312-byte symbol. `verify.py` independently resolves
the candidate's ten relative calls using the symbol manifest and compares the
entire span directly with the SHA-1-pinned original DOL. The C++-only control
fails at `0x8042E9EC`, `0x8042E9F4`, and `0x8042E9F8`, as expected.

A fresh isolated checkout of `94f7968bbe11c159e63806cece73b13c9bdac488`
tested replacing the production provider with this body, changing the
`LaunchDol` extent from `0x138` to `0x14C`, and moving the next split's start
to the existing initializer entry at `0x8042EA10`. No code bytes were patched
after compilation. The build linked the candidate and reproduced original DOL
SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Linked-unit and retention
checks passed without overrides.

**That isolated trial fails the full PR check:** the old generated
`pad_03_8042E9FC_text` function address disappears from function coverage and
the total function count falls by one. Matched and source-linked code each
increase by 20 bytes; total code/data and matched-function count are unchanged.
The existing checker was not weakened. The trial's split/symbol changes are
not part of this PR. This is evidence for a concrete boundary proposal, not
an accepted ownership change. The newly separable initializer was not added
to that trial's linkset; #285 handles its linkage separately.

## Reproduce locally

First build normally with the pinned tools and original inputs. Use the shared
native-build capacity protocol in
[`tools/local_build_capacity/PROTOCOL.md`](../../tools/local_build_capacity/PROTOCOL.md)
for compiler probes. The following compile belongs inside that gate. Set the
`PSO_` variables to your existing tools; GC/2.6 compiler SHA-1 must be
`1110a7a9924a09a608967efdf79ecf09900344e7`.

```sh
mkdir -p build/launch-dol-experiment
"$PSO_WIBO" "$PSO_COMPILERS/GC/2.6/mwcceppc.exe" \
  -nodefaults -proc gekko -align powerpc -enum int -fp hardware \
  -Cpp_exceptions off -RTTI off -str reuse -maxerrors 1 -nosyspath \
  -i build/GPOE8P/include -i include -i src -i libs/dolphin/include \
  -i libs/dolphin/include/dolphin -char signed -use_lmw_stmw on \
  -O4,s -inline off -sdata2 4 -lang=c++ \
  -DPSO_LAUNCH_DOL_EXPERIMENT=1 \
  -c experiments/launch_dol/LaunchDolHandoff.cpp \
  -o build/launch-dol-experiment/LaunchDolHandoff.o
python3 experiments/launch_dol/verify.py \
  build/launch-dol-experiment/LaunchDolHandoff.o
"$PSO_OBJDIFF" diff \
  -1 build/GPOE8P/obj/pso/unk/text_8042E8C4.o \
  -2 build/launch-dol-experiment/LaunchDolHandoff.o LaunchDol \
  -o build/launch-dol-experiment/handoff-diff.json
```

For the historical control, compile `LaunchDol.cpp` separately, replacing
`-O4,s -inline off -sdata2 4` with
`-O4,p -inline auto -opt nocse,nostrength,noprop`. Its verifier exit status is
1 because three words differ. Invalid inputs produce status 2. The verifier
prints only metadata, never original instructions or assets. Keep objects,
disassemblies, split originals and private inputs local.

## Scope and provenance

The user authorized the Melee-style handoff experiment and subsequent pragma,
compiler-option and C++ iteration. The earlier no-new-assembly research scope
is superseded for this opt-in experiment. That authorization is not recorded
as approval of a portable fallback, the #285 ownership change or an accounting
exception. See the [exception register](../../docs/porting-exceptions.md).

The inline assembly uses a transfer mechanism analogous to
[Melee's OSReboot](https://github.com/doldecomp/melee/blob/2f8eab8ebd7a2d25541e125abfa246defe1bacec/libs/dolphin/src/dolphin/os/OSReboot.c#L30-L43).
That is not authenticated PSO source. The original compiler remains unknown;
exact output from the pinned stock compiler establishes reproducibility, not
historical authorship or original translation-unit boundaries. See the
[follow-up evidence](../../docs/evidence/launch-dol-cpp-recovery.md) and
[header/provenance record](../../docs/evidence/dol-header-view.md).
