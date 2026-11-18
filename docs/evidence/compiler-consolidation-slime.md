# Slime compiler consolidation blocker

Investigation date: 2026-11-13. Baseline source revision:
`08c178922f` (the Slime source remains unchanged). The proposed compiler set
retains GC/2.6 and GC/1.3.2 while retiring GC/2.0.

`pso/enemy/TObjEneSlimeTailAttack.cpp` still needs its GC/2.0 exception.
Fresh compilation of the current source and existing flags gives:

| Compiler | Exact original functions | Remaining discrepancy |
|---|---:|---|
| GC/2.0 | 90/90 | None |
| GC/2.6 | 89/90 | `TObjEneSlimeOne::receive_direct_attack`, 89.189186% |
| GC/1.3.2 | 80/90 | Ten other functions; direct-attack handler matches |

The original handler is at `0x800EAC34`, size `0x94`. GC/2.6 preserves its
length and instruction operations but moves `lwz r0,0(r5)` and
`cmpwi r0,2` earlier. The original saves r28–r31, moves the incoming
arguments into those registers, then reads `payload.kind` and compares it
with 2. GC/2.6 places the load before `stmw` and the comparison before
three of the argument moves. The remainder of the function matches.
The unit's `.text` score is 99.90606%; its `.ctors`, `.rodata`, `.data`,
`.bss` and `.sdata2` remain 100% in objdiff. These scores alone do not
authorize changing a source-linked unit.

## Tested alternatives

Natural source probes included a const by-value payload, a named kind or
boolean, local pointer/reference views, nested conditions, an inline typed
predicate, and explicit payload-copy/forwarding forms. None recovered the
complete function. A subtraction-based comparison reached 92.432434% but
introduced a different subtraction instruction and register assignment.
It was not adopted. `memcpy` forms emitted extra calls and larger frames.

Supported whole-unit comparisons included debug information, individual
optimizer controls, optimization levels, and processor scheduling choices.
GC/2.6 `-sym on`, `-opt noloop`, `-opt nostrength`, and 750/740 scheduling
retain the same blocker. `-opt nopeephole` changes 70 functions. Lower
optimization levels and speed optimization cause broader losses.
With `-opt nopeephole`, the handler itself is only 93.64865%: the saved
argument moves change order, the payload read uses r30 instead of the
original r5, and the return-zero load moves before the register restores.
An immediate-codegen island with peephole disabled therefore would not by
itself solve the handler, even if its emission order could be preserved.

Narrow pragma probes also failed. `scheduling off` and `scheduling once`
move the first load later but change argument moves, outgoing payload-copy
scheduling and the epilogue, reducing the handler to 76.89189%.
Pointer analysis on/off and its accepted `addr`, `ansi` and `type` modes
do not solve it. Register-save-helper, IBM-frame and vector-frame controls
also leave the blocker unchanged. Numeric pointer-analysis modes are
invalid syntax and are not evidence that an option took effect.
No source pragma, semantic qualifier, compiler setting or source rewrite
from these probes was landed.

## Backend interpretation and limits

The local reconstructed compiler source at
`/tmp/panarms-mwcc-tools/gc2/src/backend/CodeGen.c` shows a scheduling pass
before register coloring, followed by prologue/epilogue generation,
peephole merging and final scheduling. `scheduling once` suppresses the
first pass, not the final pass. This explains why it is not a control to
retain body scheduling while merely disabling prologue scheduling.
`CMachine.c` does not capture the `peephole` flag in deferred function
options, consistent with an ineffective scoped `peephole off` probe and
the broader effect of the command-line option.

The same reconstruction's `frontend/CFunc.c`, in
`CFunc_SetupNewFuncArgs`, lowers aggregate by-value parameters to pointers
qualified with `Q_REFERENCE | Q_RESTRICT`. `backend/CodeGen.c` attaches a
distinct virtual alias when moving such an argument to its saved register.
This is a frontend/argument-lowering rule, separate from the optional
pointer-analysis optimization. It explains why changing pointer-analysis
settings is not a direct control for the alias attached to this argument.

## Read-only GC/2.6 trace

A subsequent trace ran the original GC/2.6 compiler under retrowin32/GDB
using the unchanged production source and flags, without `-sym on`.
The debugger only read compiler state; its usual call to
`CMangler_GetLinkName` was removed. Compilation continued after the selected
function so the complete output could be checked. A task-local emulator
build changes only its debugger listener from port 9001 to 19213.

| Original compiler address | Measured stage and effect |
|---|---|
| `0x433F8C` | After generating the prologue/epilogue: prologue and entry are separate blocks; the payload load uses saved r30. |
| `0x433FD4` | After merging the prologue: the load remains after the saves and still uses r30. |
| `0x434006` | After late peephole optimization: the payload load's base changes from r30 to incoming r5. |
| `0x434063` | After final scheduling: that load crosses `stmw`, and its comparison crosses three argument moves. |

At the final scheduling checkpoint the payload load's alias is an object
part for compiler-created virtual object `@1200`, alias index 10. The
prologue stores use a set alias whose membership word is `0x1e2`; bit 10
is clear. The function-call alias set instead has word `0xdfa`, where bit
10 is set. These are measured alias memberships: the payload read has no
memory-alias dependency on the prologue saves, while calls retain one.
Together with the late r5 substitution, this accounts for the newly
available load motion. The reconstructed `may_alias_alias` implementation
tests precisely that membership for an object-part/set pair.

Both complete traced outputs are byte-for-byte identical to a normal Wibo
compilation, not merely equivalent in their allocated sections. All three
object SHA-256 values are
`e712baa1202612963db73a4fe087b5545e46b7c66fcd0bc3f8da801ed5027826`.
The traced compiler SHA-256 is
`316e2a98236c23f3fc902243b157eaebf8ef2ad6edb88cfd632a15b6676fa9a8`.
The first debugger run reported a remote disconnect after the compiler
finished normally; its complete object has the same hash. The repeated
run handles that normal emulator disconnect explicitly.

GC/2.0's internal scheduler was not traced. Its exact output is the
comparison reference; the qualification/alias-creation explanation above
also uses reconstructed compiler source and should not be read as a trace
of GC/2.0. No supported preserving source candidate was found. This does
not exhaust every possible source form or setting, or establish Sega's
historical compiler choice.

## Reproduction

Local investigation artifacts are under `/tmp/gc20-slime-migration/`.
From the repository root, run:

```sh
python3 /tmp/gc20-slime-migration/reproduce.py
```

The script compiles the unchanged unit with GC/2.0, GC/2.6 and GC/1.3.2,
then compares each complete object to the original split using
`objdiff-cli diff -c functionRelocDiffs=data_value`. Exact argv, compiler
diagnostics and diff JSON are saved in its `reproduce/` directory. Wibo
needs the same execution permissions as a normal matching build.

Original split objects and compiler/tool hashes come from
`/tmp/pso-compiler-consolidation-20261113/`. That audit verified the DOL's
SHA-1 and split it with the current symbols and unit boundaries. Generated
includes and installed tools were read from the existing local build;
all probe outputs were isolated. These scratch objects are locally
derived game data and must not be committed. Full-build integration
validation belongs to the parent consolidation change; this investigation
does not claim a successful compiler migration for Slime.

The trace archive is `/tmp/gc20-slime-trace/`. `run.py` records the exact
argv in `argv.json`; `debugger.py` is the read-only adapted debugger.
`baseline/` and `membership/` contain stage dumps and complete compiler
objects; `membership/alias-membership.txt` records the measured sets.
Run `python3 /tmp/gc20-slime-trace/run.py` from the repository root to
repeat the GC/2.6 trace with its isolated listener. The emulator source and
build log are in the same scratch archive. No compiler executable or
production source was patched.
