# Technique dispatcher hit-test argument order (MWCC instruction scheduler)

Base: fork `main` `d27f62054`, branch `decomp-tobjnpc-kenkyuw` (PR
[#318](https://github.com/matthewlewisnewton/pso-decomp/pull/318)). Unit
`pso/npc/TObjNpcKenkyuW.cpp`, function `TObjPlayer__sub_802A445C`
(`0x802A445C`, 228 bytes). Unit flags are the defaults (`GC/2.6`, `-O4,s`,
`-inline off`). Nine of the ten functions in the unit are exact; this one is
96.49123% with two adjacent instructions transposed.

This note records the scheduling constraint and measured source shapes, so
that those shapes are not re-searched. It does not propose an
exception: the function stays unmatched.

## The mismatch

The hit-test call is the `bne` target of the `list == 0` test. The original
sets up its two arguments in source order; every compile of every modelled
shape hoists the load:

    original   mr   r3,r30          ours   lwz  r4,0(r31)
               lwz  r4,0(r31)              mr   r3,r30
               bl   is_hit_receivable_target__10TObjPlayerFlUl

The 55 other instructions, both relocations, the `.text` size and every
other block match. The default switch case in the same function
(`lwz r4,28(r30)` / `mr r3,r30` / `bl TObjPlayer__sub_802A3DE8`) has the same
dependency structure and is load-first in *both* builds, so the original was
scheduled; only the hit-test block escaped scheduling.

## Why a three-instruction block is always load-first

Read from the GC/2.6 compiler decompilation
([doldecomp/mweppc](https://github.com/doldecomp/mweppc) `919828d`), which
agrees with the earlier debugger traces of the shipped `mwcceppc.exe`
(block skip at VA `0x507c70`, second scheduling pass at `0x43405e`).

- `Scheduler.c scheduleinstructions` schedules a block iff
  `pcodeCount > 2`, `!(flags & (fIsProlog | fIsEpilogue))` in pass 1, and
  `!fScheduled`. A call ends its block, so the pair plus the `bl` is exactly
  three pcodes and qualifies.
- `MachineSimulation750.c instruction_timing` gives every `LSU1` load
  latency 2 and the `IU1`/`IU2` integer ops (`or`, i.e. `mr`) latency 1.
  `findsuccessors` makes both argument setups predecessors of the `bl`, with
  edge latency equal to the producer's own latency, so
  `height(lwz) = height(mr) + 1` and the load alone sits on the critical
  path.
- `computedeadlines` sets `latest = criticalpath - height`, and
  `selectinstruction` prefers a candidate whose deadline has expired
  (`node->latest > counter && candidate->latest <= counter`) before it looks
  at anything else. At cycle 0 that test picks the load whatever order the
  two setups appear in. Source order only survives when the deadlines tie.

Measured on the real unit (`/tmp/pr318opus`, same flags), confirming the
tie rule rather than guessing at it:

| Both arguments | Emitted |
|---|---|
| `(self->m_1c, list->actors[0])` | `lwz r3,28(r30)` / `lwz r4,0(r31)` — source order |
| `(list->actors[0], self->m_1c)` | `lwz r3,0(r31)` / `lwz r4,28(r30)` — source order |
| `(self, list->actors[0])` (the real call) | load hoisted |
| `(self, self->m_1c)` (the default case) | load hoisted |

Two loads tie and keep source order; a copy can never tie with a load. This
also explains the survey finding that every `mr r3` / independent `lwz r4` /
`bl` site elsewhere in this DOL has a store in front of the pair: a store
that may alias serialises the load behind it (`serialize_load` /
`serialize_store`), and the copy fills the freed slot. Adding
`self->m_38 = 1` before the call reproduces that exactly
(`mr r3,r30` / `stw r0,56(r30)` / `lwz r4,0(r31)` / `bl`), at the cost of a
store the original does not have.

## Investigated block-split mechanism

A demonstrated way to preserve the original pair is to keep it
in a block of at most two pcodes. `Peephole.c peepholemergeblocks(FALSE)`
runs before pass 1 and produces exactly that: a non-empty, call-free
predecessor whose last instruction is a `b` to the next block has that branch
deleted and then absorbs the next block's instructions up to its first call,
provided the two blocks are each other's only successor and predecessor. A
stub block holding only `b H` therefore ends up as `[mr, lwz]` with `[bl]`
after it, both too small to schedule in either pass. A `switch` shaped to
produce that stub does emit the original order, which confirms the mechanism.

The stub has to come from codegen, and `branch_always` has only twelve call
sites in the whole backend:

- `CodeGen.c gotostatement` — the frontend deletes a `goto` whose target is
  the next statement (`COptimizer.c optimizegoto`, whose scan skips only
  `ST_NOP`/`ST_LABEL`), and dead-code elimination removes anything placed
  after the `goto` to block that scan. Keeping the stub needs a reachable
  statement that emits no code wedged between the `goto` and its label, i.e.
  deliberate no-op steering.
- `CodeGen.c returnstatement` — always branches to the return label, never to
  the next block, and `peepholemergeblocks(FALSE)` refuses an epilogue
  successor.
- `InstrSelection.c` ECOND (six sites) — `b label3` jumps past the false arm,
  so its target is the next block only when the false arm emits nothing, and
  then there is nothing to absorb. `label3` also has two predecessors.
- `Switch.c treecompare` (four sites) — the `b default` stub exists, but a
  32-bit selector compares with `cmpwi` (`cmplwi` only for an unsigned
  selector narrower than four bytes) and branches only `beq`/`bge`/`blt`,
  never `bne`, and the dispatch lays the default body first. Every variant
  leaves at least one extra compare and branch, and a dead case is steering.

Loops contribute nothing: the frontend lowers them to `ST_GOTO`/`ST_IFGOTO`,
and `newstatement` only splits a block that already holds more than 100
pcodes (this function has 57 instructions).

The measured successful block-split shapes need a pragma, a no-op or
unreachable statement, or a dead switch case. None is a permitted solution.
These experiments have not established a source-correct way to preserve
the pair, and the function is left unmatched. They do not establish that
every possible C++ source shape is impossible; see the qualification below.

## Shapes already measured

Around seventy source shapes were compiled and rejected across waves 10-18:
copy locals and casts of `self`, real/static/implicit-`this` member
variants, `&&` and `?:` forms, `goto` and label forms, loops that run once,
constant `switch`es, volatile and pointer-arithmetic forms for
`list->actors[0]`, and every unit flag allowed by the porting rules
(`-fp_contract on/off`, `-inline auto`/`deferred`/`auto,deferred`/`noauto`/
`on`/`off`/`all`; `-inline auto` and `all` inline the hit test and drop the
function to 84.38%). `-schedule off`, `-opt noschedule`, `-O2` and `-O3` give
this block the original order but un-schedule the default case and the
`vfunc_9` block, so the whole unit gets worse. The per-shape table lives in
`pilot-logs/attempts/pr318-grok-attempts.md` and
`pilot-logs/attempts/pr318-opus-attempts.md`.

## Dispatcher call boundary

The callers in `TObjEneMe1Gee_NEEDLE::run_task` and
`TObjEneMe1GiGueMissile::run_task` both pass `(this, 1)` to
`TObjPlayer__sub_802A445C`. Both classes derive from `TNeedleShoot`, and
neither caller consumes a return value. The dispatcher reads no incoming
second argument and returns no result. Its shared declaration in
`TNeedleShoot.h` therefore keeps the second argument as an unnamed, unused
`s32` in the definition and declares a `void` result. This replaces the
inconsistent local `s32 (void *, s32)` / `s32 (void *, int)` declarations and
the one-argument definition without dropping the callers' original argument.
The role of the unused argument and the original function name remain unknown.

## 2026-11-09 refresh

Merged fork `main` `6daa19a11db97b1b8222fd2665eba485ed3a74a4` into
the PR without conflicts. Main still has no source implementation of the
dispatcher, so this work has not been superseded. The signature repair does
not solve the instruction-order mismatch.

Fresh, separate main and PR builds used GC/2.6, the default unit flags and
fresh splits from the original inputs. Both builds reproduced the original
PsoV3 DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
`check_pr.py --no-build` against the fresh main report passed with zero
regressions and zero new exact functions; 3,570 linked units remained exact,
with no force-active drift. `list_port_exceptions.py --check` also passed.

Both projectile `run_task` functions remain 100% exact. Their complete
compiled `.text` sections are byte-identical to the fresh main baseline
after sharing the declaration. The dispatcher remains 96.49123% (228
bytes), its nine siblings remain 100%, and the unit remains 99.6633% fuzzy
with 2,148 of 2,376 code bytes exact. This unit remains unlinked. These are
object-level results; the passing DOL hash does not score the dispatcher.

## Direct source-link diagnostic and proof limits

A separate scratch link on 2026-11-09 used the validated source/configuration
of PR head `b47c9e6ff7f55d16bb40ed0c260f2ea98d9e24b8`. Starting with the
generated main executable's 4,970-input link list, it replaced only
`build/GPOE8P/obj/pso/npc/TObjNpcKenkyuW.o` with
`build/GPOE8P/src/pso/npc/TObjNpcKenkyuW.o`. It used the same GC/2.6 linker,
`-fp hardware -nodefaults`, and generated `ldscript.lcf`, with a private ELF,
response file and DOL output. No source, linkset or canonical build output
was changed for this diagnostic.

The link succeeded. The resulting DOL had the same 5,233,088-byte size as
the original, with exactly eight changed bytes in two instruction words at
`0x802A44F0` and `0x802A44F4`. Every other byte was identical. Its SHA-1 was
`d61c4fd1d8e938620c55a2b30ebfc66f7c05db7c`, rather than the required
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. This rules out the hypothesis
that ordinary linking repairs this pair, and exposes no additional
symbol/data/layout blocker in this exact build. It is an intentional
failing-hash diagnostic, not authorization to link the unmatched unit.

Inputs binding this diagnostic (SHA-256):

- Compiled unit: `2fa267c3643deacd0477e1f6d1de91c558f0b24adbfc2466fdb3b0dbbb314f7a`.
- Original split unit: `29a9d8a030a78f44e85e96ea0798655d4a8520d3dd3ff1b9be8a097b00906a42`.
- Linker script: `cf83ca3d5e14c9c7af513d1b2b6d86919546f78c7172ceec59d871a17de01c00`.

One assertion in the earlier local attempt notes needs qualification:
"Nothing after the second schedule deletes a branch" is not generally true.
In the inspected compiler source, `assemblefunction` calls
[`optimizefinalbranches`](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/backend/PCodeAssembly.c#L1519)
after scheduling; the pass can delete unconditional and conditional branches
whose targets are the next instruction. Thus an intermediate branch in a
backend scheduling dump is not, by itself, proof that the branch will be
present in the emitted object. This observation does not produce a matching
source shape, and does not invalidate the measured failures above. It does
mean that the block-split investigation is a bounded search, not an
exhaustive proof about every C++ program.

The concrete remaining blocker is unchanged: no permitted source shape has
produced the original instruction order while preserving all other code.
A new candidate must be meaningful source, preserve the other nine exact
functions, and pass a real source link with the original DOL hash. Assembly,
synthetic split units, dead cases and no-op steering are not solutions.

## Further bounded probes on 2026-11-09

The following experiments used the source and headers of
`fe4628c545db1f7d35e8dee3583bf124921201b1`, the default GC/2.6 flags and
private outputs. The inline continuation probe alone used
`-inline on,noauto`. None was retained, and no compiler exception is proposed.

| Source organization | Dispatcher fuzzy | Emitted size |
| --- | ---: | ---: |
| Each real collection mode handles its own contacts | 22.666666% | 400 bytes |
| Same per-mode continuation through an inline helper | 22.666666% | 400 bytes |
| Null-list response joins a nullable receiver before hit testing | 94.38596% | 236 bytes |
| Materialize the selected nullable actor with statements | 91.29825% | 236 bytes |
| Materialize the selected nullable actor with a conditional expression | 89.12281% | 244 bytes |

All nine existing functions stayed 100% in each full-unit compile. The
per-mode forms did not merge their common tails. The receiver form retained
extra null state/testing. The actor forms preserved the null-list callback,
the post-hit reload of `actors[0]`, and the final null-actor guard. They
materialized an actual nullable actor, rather than a dummy hit-status value,
but neither improved the instruction order or whole-function match.

The debugger was extended to capture the shipped GC/2.6 compiler immediately
after `optimizefinalbranches` returns (x86 VA `0x4EB166`), instead of stopping
before `assemblefunction` (VA `0x4340B1`). The compiler executable's SHA-256
was `316e2a98236c23f3fc902243b157eaebf8ef2ad6edb88cfd632a15b6676fa9a8`.
Both the earlier `v_if_tern_cond.cpp` specimen and the new nullable-actor
statement form had one three-pcode hit-test block before scheduling:
`mr`, `lwz`, `bl`. The first scheduler changed it to `lwz`, `mr`, `bl`;
the second scheduler retained that order. The complete final-branch dump
was identical to the second-scheduler dump for both specimens. Neither
provides a late-deleted branch witness. These traces investigate the
unobserved final stage; they do not retry the old conditional shape as a fix.

A bounded scan of the fresh build's compiled `.text` sections found 112
adjacent `mr r3,...` / independent `lwz r4,...` / direct-call sequences.
Eight began at branch targets; all eight used GC/1.2.5n middleware units,
not GC/2.6 game units. This is not a universal compiler-pattern proof.
It supplies no GC/2.6 witness with the required branch-entry dependency shape.

### Header-free GC/1.2.5n diagnostic

The earlier full-unit GC/1.2.5n attempt failed while parsing
`TObjNpcBase.h`, before dispatcher code generation. It therefore did not
establish the dispatcher's behavior under that compiler.

One diagnostic compile used the existing header-free `/tmp/pr318x/base.cpp`
unchanged, with the normal game flags (`-O4,s -inline off`, `-proc gekko`,
`-fp hardware`, `-use_lmw_stmw on`, `-sdata2 4`, exceptions/RTTI off).
Fixture SHA-256:
`0397cc5aede431d00632d54613d0b8aa864cd8d19532c99be6dcbe54ca294cf0`.
GC/1.2.5n compiler SHA-256:
`ccf4b465cec73b5aae9c5c5543dcf8cda8a62aba246f89e2e0b200d742f2e55c`.
Only the fixture's dispatcher symbol label was mapped to the original
placeholder for object comparison; its instruction bytes were not changed.

The compile succeeded and emitted the desired `mr` before `lwz` at the
hit-test call. However, the complete function was 244 bytes and only
72.38596% fuzzy, with different stack-frame and virtual-call sequences.
Whole-unit and sibling compatibility were not established. This closes a
gap in the old measurements; it does not justify a compiler override or
a synthetic unit split, and it is not a matching implementation.

The next useful lead needs a genuine GC/2.6 source-generated boundary that
reuses the existing condition, survives both scheduling passes, and then
loses only a legitimate branch. Another local-variable permutation, extra
comparison, dead case or scheduling override is not evidence for that lead.
