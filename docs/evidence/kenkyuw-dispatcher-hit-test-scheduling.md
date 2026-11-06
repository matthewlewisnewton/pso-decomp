# Technique dispatcher hit-test argument order (MWCC instruction scheduler)

Base: fork `main` `d27f62054`, branch `decomp-tobjnpc-kenkyuw` (PR
[#318](https://github.com/matthewlewisnewton/pso-decomp/pull/318)). Unit
`pso/npc/TObjNpcKenkyuW.cpp`, function `TObjPlayer__sub_802A445C`
(`0x802A445C`, 228 bytes). Unit flags are the defaults (`GC/2.6`, `-O4,s`,
`-inline off`). Nine of the ten functions in the unit are exact; this one is
96.49123% with two adjacent instructions transposed.

This note records *why* the remaining pair cannot be reordered from C++, so
that the shape is not re-searched. It does not propose an exception: the
   10|function stays unmatched.

## The mismatch

The hit-test call is the `bne` target of the `list == 0` test. The original
sets up its two arguments in source order; every compile of every modelled
shape hoists the load:

    original   mr   r3,r30          ours   lwz  r4,0(r31)
               lwz  r4,0(r31)              mr   r3,r30
               bl   is_hit_receivable_target__10TObjPlayerFlUl

    20|The 55 other instructions, both relocations, the `.text` size and every
other block match. The default switch case in the same function
(`lwz r4,28(r30)` / `mr r3,r30` / `bl TObjPlayer__sub_802A3DE8`) has the same
dependency structure and is load-first in *both* builds, so the original was
scheduled; only the hit-test block escaped scheduling.

## Why a three-instruction block is always load-first

Read from the GC/2.6 compiler decompilation
([doldecomp/mweppc](https://github.com/doldecomp/mweppc) `919828d`), which
agrees with the earlier debugger traces of the shipped `mwcceppc.exe`
    30|(block skip at VA `0x507c70`, second scheduling pass at `0x43405e`).

- `Scheduler.c scheduleinstructions` schedules a block iff
  `pcodeCount > 2`, `!(flags & (fIsProlog | fIsEpilogue))` in pass 1, and
  `!fScheduled`. A call ends its block, so the pair plus the `bl` is exactly
  three pcodes and qualifies.
- `MachineSimulation750.c instruction_timing` gives every `LSU1` load
  latency 2 and the `IU1`/`IU2` integer ops (`or`, i.e. `mr`) latency 1.
  `findsuccessors` makes both argument setups predecessors of the `bl`, with
  edge latency equal to the producer's own latency, so
    40|  `height(lwz) = height(mr) + 1` and the load alone sits on the critical
  path.
- `computedeadlines` sets `latest = criticalpath - height`, and
  `selectinstruction` prefers a candidate whose deadline has expired
  (`node->latest > counter && candidate->latest <= counter`) before it looks
  at anything else. At cycle 0 that test picks the load whatever order the
  two setups appear in. Source order only survives when the deadlines tie.

Measured on the real unit (`/tmp/pr318opus`, same flags), confirming the
tie rule rather than guessing at it:
    50|
| Both arguments | Emitted |
|---|---|
| `(self->m_1c, list->actors[0])` | `lwz r3,28(r30)` / `lwz r4,0(r31)` — source order |
| `(list->actors[0], self->m_1c)` | `lwz r3,0(r31)` / `lwz r4,28(r30)` — source order |
| `(self, list->actors[0])` (the real call) | load hoisted |
| `(self, self->m_1c)` (the default case) | load hoisted |

Two loads tie and keep source order; a copy can never tie with a load. This
also explains the survey finding that every `mr r3` / independent `lwz r4` /
    60|`bl` site elsewhere in this DOL has a store in front of the pair: a store
that may alias serialises the load behind it (`serialize_load` /
`serialize_store`), and the copy fills the freed slot. Adding
`self->m_38 = 1` before the call reproduces that exactly
(`mr r3,r30` / `stw r0,56(r30)` / `lwz r4,0(r31)` / `bl`), at the cost of a
store the original does not have.

## The only remaining mechanism, and why no source shape reaches it

Because the scheduler cannot be argued with, the original pair must have sat
in a block of at most two pcodes. `Peephole.c peepholemergeblocks(FALSE)`
    70|runs before pass 1 and produces exactly that: a non-empty, call-free
predecessor whose last instruction is a `b` to the next block has that branch
deleted and then absorbs the next block's instructions up to its first call,
provided the two blocks are each other's only successor and predecessor. A
stub block holding only `b H` therefore ends up as `[mr, lwz]` with `[bl]`
after it, both too small to schedule in either pass. A `switch` shaped to
produce that stub does emit the original order, which confirms the mechanism.

The stub has to come from codegen, and `branch_always` has only twelve call
sites in the whole backend:

    80|- `CodeGen.c gotostatement` — the frontend deletes a `goto` whose target is
  the next statement (`COptimizer.c optimizegoto`, whose scan skips only
  `ST_NOP`/`ST_LABEL`), and dead-code elimination removes anything placed
  after the `goto` to block that scan. Keeping the stub needs a reachable
  statement that emits no code wedged between the `goto` and its label, i.e.
  deliberate no-op steering.
- `CodeGen.c returnstatement` — always branches to the return label, never to
  the next block, and `peepholemergeblocks(FALSE)` refuses an epilogue
  successor.
- `InstrSelection.c` ECOND (six sites) — `b label3` jumps past the false arm,
    90|  so its target is the next block only when the false arm emits nothing, and
  then there is nothing to absorb. `label3` also has two predecessors.
- `Switch.c treecompare` (four sites) — the `b default` stub exists, but a
  32-bit selector compares with `cmpwi` (`cmplwi` only for an unsigned
  selector narrower than four bytes) and branches only `beq`/`bge`/`blt`,
  never `bne`, and the dispatch lays the default body first. Every variant
  leaves at least one extra compare and branch, and a dead case is steering.

Loops contribute nothing: the frontend lowers them to `ST_GOTO`/`ST_IFGOTO`,
and `newstatement` only splits a block that already holds more than 100
   100|pcodes (this function has 57 instructions).

So the transposition is reachable only through a construct that is banned
here — a pragma, a no-op or unreachable statement, or a dead switch case.
The function is left unmatched, which is what `CONTRIBUTING.md` asks for.

## Shapes already measured

Around seventy source shapes were compiled and rejected across waves 10-18:
copy locals and casts of `self`, real/static/implicit-`this` member
variants, `&&` and `?:` forms, `goto` and label forms, loops that run once,
   110|constant `switch`es, volatile and pointer-arithmetic forms for
`list->actors[0]`, and every unit flag allowed by the porting rules
(`-fp_contract on/off`, `-inline auto`/`deferred`/`auto,deferred`/`noauto`/
`on`/`off`/`all`; `-inline auto` and `all` inline the hit test and drop the
function to 84.38%). `-schedule off`, `-opt noschedule`, `-O2` and `-O3` give
this block the original order but un-schedule the default case and the
`vfunc_9` block, so the whole unit gets worse. The per-shape table lives in
`pilot-logs/attempts/pr318-grok-attempts.md` and
`pilot-logs/attempts/pr318-opus-attempts.md`.
