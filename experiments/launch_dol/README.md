# LaunchDol recovery experiments

`LaunchDolHandoff.cpp` reproduces all 332 bytes and ten call relocations at
`[0x8042E8C4, 0x8042EA10)`. The source uses typed C++, the CodeWarrior
`__isync()` intrinsic, and a two-instruction nonlinking transfer through LR.
The stock GC/2.0 compiler with the current ntUtl middleware flags and stock
GC/2.6 with the same flags emit identical objects.

`LaunchDol.cpp` preserves the direct C++ call as a comparison control. It
uses a linking CTR call, which changes control flow and the guest LR. Both
files require explicit opt-in through `PSO_LAUNCH_DOL_EXPERIMENT` and define
the same symbol, so compile them separately.

## What made the handoff match

The candidate uses the current ntUtl `-O4,p -inline off` profile.
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

## Production boundary

Retain the existing native split. The compiler appends a 20-byte restore to
the 312-byte function body and handoff. The production build tracks the restore
separately at `0x8042E9FC` and links it through the #285 retention fix. The
byte match supports interpreting the suffix as part of the loader's frame.
Possible indirect entries and original symbol ownership remain open.
The [ownership investigation](../../docs/evidence/launch-dol-stranded-epilogue.md)
describes the limits of the original-input evidence.

| Candidate | Emitted bytes | Objdiff against the 312-byte symbol | Complete native span |
|---|---:|---:|---|
| Direct C++ call, historical GC/2.6 probe flags | 332 | 93.39744% | Three different words |
| LR handoff, current ntUtl flags | 332 | 93.589745% | Exact after resolving ten relocations |

An [isolated linkage trial](../../docs/evidence/launch-dol-cpp-recovery.md#authorized-handoff-and-pragma-continuation)
reproduced the original DOL by widening the symbol to 332 bytes. The report
dropped the function start at `0x8042E9FC`, which the strict coverage check
rejected. The native provider retains that address and uses the shared typed
`LaunchDol` declaration. Ports can execute the existing guest-state handoff
and restore handlers. The [portable contract](../../docs/evidence/loader-restore-retention.md)
covers those nine instructions. The port backend also needs to supply the
earlier relocation, reset and cache operations.

## Reproduce locally

Build with the pinned tools and original inputs. Run the compiler probe under
the [native build capacity protocol](../../tools/local_build_capacity/PROTOCOL.md).
Set the `PSO_` paths to your installed tools. The GC/2.0 compiler SHA-1 is
`ef148743ee72be15f64926ac18c3aadc9cca2b47`. For the GC/2.6 comparison, use
`1110a7a9924a09a608967efdf79ecf09900344e7` with the same flags.

```sh
mkdir -p build/launch-dol-experiment
"$PSO_WIBO" "$PSO_COMPILERS/GC/2.0/mwcceppc.exe" \
  -nodefaults -proc gekko -align powerpc -enum int -fp hardware \
  -Cpp_exceptions off -RTTI off -str reuse -maxerrors 1 -nosyspath \
  -i build/GPOE8P/include -i include -i src -i libs/dolphin/include \
  -i libs/dolphin/include/dolphin -char signed -use_lmw_stmw on \
  -O4,p -inline off -lang=c++ \
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

For the direct-call control, compile `LaunchDol.cpp` with GC/2.6 and replace
`-O4,p -inline off` with `-O4,p -inline auto -opt nocse,nostrength,noprop`.
The verifier reports three different words at `0x8042E9EC`, `0x8042E9F4` and
`0x8042E9F8` and exits with status 1. Invalid inputs exit with status 2.
The verifier reports addresses and metadata. Keep original inputs and
generated artifacts local.

## Provenance

The opt-in assembly transfer follows the approach used by
[Melee's OSReboot](https://github.com/doldecomp/melee/blob/2f8eab8ebd7a2d25541e125abfa246defe1bacec/libs/dolphin/src/dolphin/os/OSReboot.c#L30-L43).
Matt authorized the handoff experiment and compiler iteration. The
[exception register](../../docs/porting-exceptions.md) records the scope.
Stock compiler reproduction establishes the native byte match. The
[header evidence](../../docs/evidence/dol-header-view.md) covers the limits of
historical compiler and source provenance.
