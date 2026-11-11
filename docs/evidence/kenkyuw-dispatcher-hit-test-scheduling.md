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

In this three-pcode call block, two loads tie and keep source order, while
the copy cannot tie with the load. A preceding store that may alias can
instead serialise the load (`serialize_load` / `serialize_store`), letting
the copy fill the freed slot. The earlier survey's broader claim that every
such pair requires a preceding store was incorrect; the corrected boundary
survey below records a real address-dependency example. Adding
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

## Ownership and ABI provenance (2026-11-10)

The helper labels are project history, not recovered original C++ symbols.
Commit [`72055d994148a1933beb4b99c1036f1665b4bcf3`](https://github.com/matthewlewisnewton/pso-decomp/commit/72055d994148a1933beb4b99c1036f1665b4bcf3)
renamed the placeholder `TObjPlayer__sub_802A3DAC` to
`is_hit_receivable_target__10TObjPlayerFiUi`. Later mechanical conversion
commit [`f93243677ad7ce6987336efa1528d4df575b3182`](https://github.com/matthewlewisnewton/pso-decomp/commit/f93243677ad7ce6987336efa1528d4df575b3182)
introduced the static `TObjPlayer` declaration. The collector at `0x802A41CC`
became a `TObjPlayer` member in mechanical conversion commit
[`236691930f476231ba118d9f84e8fff0250aa923`](https://github.com/matthewlewisnewton/pso-decomp/commit/236691930f476231ba118d9f84e8fff0250aa923).
These names and conversions cannot independently establish original class
ownership, parameter spelling or static/member ABI. In particular, the
project-assigned `FlUl` spelling is not a reason to reject an alternative
ownership model without inspecting its actual call contract.

A scan of direct relative `bl` instructions in the original PsoV3 DOL's
text sections produced the following call sites. Addresses are original;
function descriptions use current project labels. This audit used the
source/configuration of `fc32e17695475276fbb27f83593590ac9da8e433`.

| Target | Direct call sites |
| --- | --- |
| Clear contacts, `0x802A3D68` | `0x802A3E10`, `0x802A4004`, `0x802A41F4` (the three collectors) |
| Predicate, `0x802A3DAC` | `0x802A44F8` (the dispatcher) |
| Collector, `0x802A3DE8` | `0x802A44C8` (the dispatcher) |
| Collector, `0x802A3FDC` | `0x802A44B4` (the dispatcher) |
| Collector, `0x802A41CC` | `0x802A44A4` (the dispatcher) |
| Dispatcher, `0x802A445C` | `0x802A4CA0` (needle task), `0x802CE410` (GiGue missile task) |

Both dispatcher callers are modeled as `TNeedleShoot`-derived projectiles
and pass the projectile plus the existing second argument. The collectors
use the first input's collision-body pointer at `0x68`, position at `0x6C`,
and data at `0xA0`, and call the projectile motion-data helper. The adjacent
`TNeedleShoot` construction/destruction code allocates and releases a
collision body at `0x68` and initializes position at `0x6C`. This supports
a projectile-oriented operational contract; casting the projectile to
`TObjPlayer` in the current collector call does not establish player
ownership. The predicate ignores its first incoming register and checks
the actor supplied in the second, so those reads alone cannot distinguish
a member with one explicit argument from a static/free function with an
unused first argument.

This is a bounded direct-call audit, not a scan of all possible indirect
references. No original map was located in the extracted-originals and
Downloads trees inspected for this pass. Current generated split objects,
linker scripts and project labels are not independent original translation-
unit provenance. Adjacency across `0x802A3D68` through `0x802A4540` therefore
does not justify a new unit split or a compiler override.

The operational receiver evidence is useful for a future ownership repair,
but the original member/static choice, class interface and unit boundary
remain provisional. This audit changes no source declaration or argument,
does not repeat the one-argument-member scheduling probe, and does not
claim a matching dispatcher.

### Provisional reset-call boundary

The three collector calls at `0x802A3E10`, `0x802A4004` and `0x802A41F4`
pass their projectile in `r3` to the reset at `0x802A3D68`. The reset body
does not consume that incoming value: each caller restores `r3` from its
saved projectile after `VecCopy`, while the reset immediately overwrites
incoming `r3` with zero. The previous source declared a
zero-argument function, then cast it to a different function-pointer type
at each call to pass the extra argument. That represents an incompatible
source-level call even though it produced the desired register setup.

The reset now has the neutral free-function boundary
`void clear_technique_contacts(TNeedleShoot *)`, with the unused parameter
explicit in its definition and its declaration in `TechniqueContact.h`.
The project-assigned hand-mangled label is renamed at the same original
address; no address range or translation-unit split changes. All three
collectors make an ordinary call through that shared declaration instead
of casting the function type. The existing private receiver views remain
provisional, as does the unrelated player-class collector declaration.

This repairs the observed call contract without claiming the original
source used a free function, a static member or an instance member. It
does not change the dispatcher or either of its caller arguments. The
acceptance criteria remain unchanged: preserve every exact function and
the complete compiled unit text, pass the full build and address-based
incremental/main comparisons, and retain the unlinked dispatcher hold.

Validation of the repair passed. All loadable object sections were
byte-identical to the pre-repair object, including the complete 2,376-byte
`.text` section (SHA-256
`8ee6b7fff5cce454ab810a1823c1d976f34b2a8d3ed224b9f2c3069e78a517aa`).
All 120 relocations were identical after mapping only the old reset label
to the new one. The reset and the other eight exact functions remain 100%;
the dispatcher remains 96.49123%. The full build reproduced the original
DOL hash. `check_pr.py` against the pre-repair PR report and the address-
based comparison against main `387621104107ed1ff8c650bf2f50ef00c6859ba4`
both reported zero regressions and zero new exact functions. All 3,587
linked units remained exact, retention metadata had no drift, and the
porting-exception inventory check passed. No compiler setting or unit
boundary changed, and the dispatcher remains unlinked.

## Small same-flags late-branch witness (2026-11-10)

Active investigation found a small, source-defined witness for a genuine
late-deleted branch between an argument move and an independent argument
load. It does not depend on a long block, an aggregate copy, different
flags, assembly, a dummy condition or a changed calling convention.
The [standalone fixture](kenkyuw-late-branch-receiver-witness.cpp) delivers
an event to one of two receivers and returns the configured fallback for
subsequent work. Both destination choices and the returned pointer are
observable results of this deliberately small API; it is not proposed PSO
source or evidence of PSO's original ABI.

```cpp
Receiver *dispatch_and_get_fallback(
    Receiver *active, const Event *event, Receiver *fallback, int use_fallback) {
    Receiver *receiver = use_fallback ? fallback : active;
    deliver_event(receiver, event->code);
    return fallback;
}
```

The shipped GC/2.6 executable had SHA-256
`316e2a98236c23f3fc902243b157eaebf8ef2ad6edb88cfd632a15b6676fa9a8`.
The fixture used the same unit flags, including `-O4,s -inline off`:

```text
-nodefaults -proc gekko -align powerpc -enum int -fp hardware
-Cpp_exceptions off -RTTI off -str reuse -maxerrors 1 -nosyspath
-char signed -use_lmw_stmw on -O4,s -inline off -sdata2 4 -lang=c++
```

The compiler traces explain the boundary rather than inferring it from
the final instruction order. After the first scheduler, the true arm
contains a virtual-register copy and a branch to the join; the false arm
also contains a copy. The join contains `lwz`, argument copy, `bl`, in
the scheduler's usual load-first order. Register allocation must retain
the original fallback across the call because the function returns it.
It allocates that pointer to `r31`, while the selected receiver uses `r3`.
The false arm's copy from the incoming active receiver becomes a self-copy
and disappears. The join's argument copy also disappears. The nonempty
true arm and the now-empty false arm remain distinct blocks.

After the second scheduler, the relevant blocks are:

```text
B3:  mr   r3,r31
     b    B5
B4:  [empty]
B5:  lwz  r4,0(r4)
     bl   deliver_event
```

After `optimizefinalbranches`, the complete dump changes by exactly one
instruction: the `b B5` is deleted. No comparison, move, load or store is
removed at that stage. The emitted sequence is consequently:

```text
0x1c  mr   r3,r31
0x20  lwz  r4,0(r4)
0x24  bl   deliver_event
```

The move and load are independent: the move reads `r31` and writes `r3`,
while the load reads and writes `r4`. The second scheduler sees separate
blocks of two pcodes each and does not combine them. The early block merger
cannot remove `b B5`: its next logical block is the empty `B4`, while its
target is `B5`. Final assembly can see that both labels have the same
physical address. The debugger captures
were taken after scheduler one (`0x433E0C`), register allocation
(`0x433EAB`), scheduler two (`0x434063`), and final branch optimization
(`0x4EB166`), using the same local debugger extension described above.

Independent compilation through the normal `wibo` runner produced a
64-byte `.text`, SHA-256
`a3328a8f6f0ba15be3f0f4fd8ca46a03533761117ef47286e6138c10e549623e`,
with those three words at the stated offsets. The fixture's optional host
check verifies exactly one delivery, the selected destination, unchanged
inputs and the returned fallback over 20 cases (five code values and
four zero/nonzero selectors). It can be run with:

```sh
c++ -std=c++98 -Wall -Wextra -pedantic -DKENKYUW_WITNESS_HOST_CHECK \
    docs/evidence/kenkyuw-late-branch-receiver-witness.cpp -o /tmp/kenkyuw-witness
/tmp/kenkyuw-witness
```

The complete fixture file's SHA-256 is
`a6e71011925c9d6422eb84b98111401e551b70f03f7797ab66e0eb95a7209fb1`.

Two precursor fixtures help bound the mechanism. Selecting the receiver
and nullable event code independently left two comparisons. Selecting
between two receivers without retaining the fallback after the call let
allocation reuse the first arm's register; the other arm's copy remained,
so there was no late-deleted branch. Neither precursor was a dispatcher
candidate, and neither is retained as production source.

This reaches the same-compiler, same-flags witness threshold. It does not
yet provide a source-correct PSO adaptation. The fixture's empty false arm
depends on the active receiver still arriving in `r3`; PSO's collectors
instead return the contact list in `r3`, while its projectile survives in
`r30`. PSO's null-list arm calls `vfunc_6` and exits rather than delivering
to a second receiver. Introducing another receiver, a new return contract,
an extra comparison or a dummy lifetime use would not preserve that source
contract. The witness therefore reopens a concrete allocation/join lead,
but no dispatcher permutation was compiled from it without such a mapping.
The dispatcher, its 96.49123% result, unit split and unlinked hold remain
unchanged. No compiler override or technical exception is proposed.

### Receiver lifetime adaptation and collector controls

A bounded follow-up tested the receiver/list distinction rather than
assuming that the small witness transfers to PSO. The existing direct-call
audit identifies the two projectile callers. In the original dispatcher,
`r30` retains that projectile and `r31` retains the collector result. The
predicate may call an external actor routine, so the later actor/body reads
must remain after it. The projectile is then needed for the body store and
virtual hit callback. Neither pointer can simply be discarded at the
predicate boundary. The miss callback's result is ignored; no receiver
return value was assumed or introduced for it.

One full-unit candidate shortened only a meaningful nullable receiver's
lifetime. It selected the receiver before the null/miss decision, used it
only as the predicate's first argument, and retained the original `self`
for subsequent work:

```cpp
TNeedleShoot *receiver = list != 0 ? self : 0;
if (receiver == 0) {
    self->vfunc_6();
} else if (TObjPlayer::is_hit_receivable_target(
               (s32)receiver, (u32)list->actors[0]) != 0) {
    // Original post-call actor reload, null guard, body store and hit callback.
    // These still use the original self, not receiver.
}
```

For a valid projectile, a null list selects null and invokes exactly the
original miss path; a nonnull list selects the unchanged projectile and
passes the original predicate arguments. All later reads/calls remain in
their original order. A host model generated from the original and candidate
bodies compared 192 cases: zero/nonzero `m_68`, mode 1, mode 2, two default
selectors, null/non-null lists and actors, hit/no-hit results,
and mutations that clear or replace the actor during the predicate. It
also changed the contact body during that call, checking the required
post-call reloads. Host pointer transport was widened solely for the host
model; the compiled candidate kept the target headers and ABI unchanged.

The candidate was rejected: the dispatcher grew from 228 to 244 bytes and
matched only 89.29825%. Its source SHA-256 was
`cea83cd48227f0b946b1ffe08f041f8e91548c937320664d2449264a5a6b45ed`,
based on the production source at PR head `73b6a2c25`. The other nine
functions remained exact. Allocation did remove the predicate block's
argument copy, but the earlier selection remained:

```text
B16: mr    r3,r30
     b     B18
B17: li    r3,0
B18: cmpli cr0,r3,0
     bf    cr0,2,B21
     ... original miss callback and exit ...
B21: lwz   r4,0(r31)
     bl    is_hit_receivable_target
```

The zero-valued arm is nonempty, and the receiver comparison is real in
the emitted code. The second-scheduler and final-branch dumps are identical.
Thus this formulation gets the receiver setup out of the call block but
does not produce the empty arm needed by the successful witness. Removing
the extra zero/comparison by assertion, type punning or a new contract is
not an established solution.

Two separate, semantically defined controls isolated the collecting call
and post-check lifetimes. Adding collection/miss handling to the small API
while not retaining its event after delivery produced 112 bytes. Its event
stayed in `r3`, so loading the event argument before restoring `r3` was a
real data dependency. That differs from PSO's saved list. The refined
[collector/lifetime control](kenkyuw-collected-receiver-control.cpp)
re-reads the event after the check, updates the active receiver, and returns
the configured fallback. It therefore retains the active receiver, fallback
and collected event for their actual subsequent uses. It passes 144 host
cases, including null collection
and post-check event mutation, and produces a 144-byte function. Both
receiver-selection arms retain real copies (`mr r3,r29` / `mr r3,r28` in
this control), so its final branch pass also deletes nothing. Neither
control is proposed PSO source or a changed PSO interface.

The full-unit candidate and both controls were authenticated against the
ordinary compiler output: re-encoding their final trace instructions,
including physical branch displacements and record bits, reproduces every
function byte emitted by the normal GC/2.6 runner. This is stronger than
checking only the visible move/load pair. The refined control's `.text`
SHA-256 is
`1304756b5fa2ad3a8f1b4cd6424aed1bfbc1ca57c1df58261146edd839b697e8`;
its complete source file's SHA-256 is
`5e05963c8d30e7d2a19aa1fcdd4dc0316a4e2514a2a5a31dd0d73753a4eccd8b`.
The same host-check command above works with this control's filename.

The ordinary stock full-unit compile also reproduced the last validated
production object's complete text and relocations. The candidate's nine
sibling bodies matched the original provider byte for byte; all other
allocated sections were unchanged. All 120 relocation targets, types and
addends were retained. Only the dispatcher's predicate relocation moved,
from unit `.text` offset `0x900` to `0x910`. The stock compiled `.text` still
differed
from the original provider only at the known two instruction words.

No candidate was installed or activated. The generated link graph still
selects the original `obj/pso/npc/TObjNpcKenkyuW.o` provider. The small
same-flags witness remains valid evidence of a possible compiler mechanism,
but these measurements do not supply a truthful way to obtain its empty
arm with PSO's actual receiver/list lifetimes. This is a bounded negative
result, not a proof excluding every C++ formulation. The production
dispatcher remains at 96.49123%, with all scheduling and link holds intact.

### Expanded boundary survey and array-reference test

The next bounded investigation corrected two limitations in the earlier
machine-code survey. It now treats instructions following calls and all
direct/indirect branch forms as block starts, rather than looking backward
only to a branch target. It also surveys independent `mr` / `lwz` / direct
call triples across argument registers `r3` through `r10`. A load that reads
the move's source register is allowed (both read it); a load whose base is
overwritten by the move, or whose destination overwrites the move's source,
is excluded. Record-form moves are excluded. Relocated calls are not
mistaken for branches to their own placeholder displacement.

The [read-only scanner](kenkyuw-argument-boundary-scan.py) reproduces the
survey on an existing build:

```sh
python3 docs/evidence/kenkyuw-argument-boundary-scan.py --output /tmp/kenkyuw-survey.json
```

On the source build underlying PR head `5268a15bf` (validated main base
`fffd67d0c`), 3,096 units and 19,583 function symbols matched the dispatcher's
GC/2.6 version and complete command flags. The scanner found 147 independent
triples. None began at a direct branch target. Of the 93 without a preceding
store since the nearest decoded block boundary, 90 had an earlier load.
Of the remaining three, two had a real address add and one had a longer
address construction. Indirect jump-table destinations are not recovered.
Source pragmas and scheduling causes require separate validation; these counts are candidate
classification, not proof of matching settings inside every function.

A real exact source example was then compiled and traced under the same
flags: [`init_model_node_tables`](../../src/pso/unk/text_8004AA04.cpp).
Its indexed record lookup `r = &arg1[i]` produces this four-pcode block:

```text
add  r25,r31,r28
mr   r3,r27
lwz  r4,0(r25)
bl   get_bml_model
```

The order is present after the first scheduler and survives the second.
There is no late deletion or change to this block. This is consistent with
the compiler's two-instruction issue model: the address add is selected,
its dependent load cannot issue at the same scheduler clock, and the
independent move can fill that clock's other issue slot. The next clock
can issue the load. The real address operation remains in the output, so
this does not supply the dispatcher's isolated three-pcode shape.

The normal compilation reproduced the cached and original provider's whole
396-byte unit text, including this 272-byte function. Re-encoding the final
trace reproduced all 272 native bytes. Function SHA-256:
`11c4d4248582a905dbfa5221d5c86ff9a29f4d9223d684ad41685e222655c290`;
source file SHA-256:
`9cf0830e8a9f8504cb21fb727304db7dbe0c8a59559cc34252a3157b5acd3bfa`.
Only two early-return branch targets were threaded by final branch cleanup;
the argument block did not change. Thus a preceding store is not the only
real source mechanism, but the demonstrated alternative needs an address
calculation absent from the target dispatcher.

One truthful source test checked whether binding the actual first contact
array can retain such an address/boundary without adding arithmetic. Inside
the existing nonnull-list arm it bound:

```cpp
TechniqueContactActor *(&contact_actors)[16] = list->actors;
```

Both predicate input and post-call actor reload then used `contact_actors[0]`.
This references the original array; it does not cache an actor across the
predicate. The compiler rejected the initially const-qualified array
reference before code generation. The supported exact array-reference type
above passed all 192 original/candidate host cases, including mutations
during the predicate, and compiled successfully without any flag change.

This test was rejected as a matching lead: even the initial backend dump
already has only `mr`, `lwz`, `bl` in the hit-call block. No address operation
or extra block survives to scheduling. The first scheduler reverses the
pair as before; final branch cleanup changes nothing. The entire compiled
unit text and all 120 relocations are byte-identical to production, with
the same nine exact siblings and 228-byte dispatcher at 96.49123%. The
final trace independently re-encodes every native dispatcher byte. Candidate
source SHA-256:
`c141122fad1b554b459a11efd1e2b66289281da4d1a7495345d32e862eb08826`.
No further array-view permutations were run or retained.

Finally, an expanded direct-entry audit decoded `B`, `BL`, `BC` and `BCL`
targets in all seven original DOL text sections. It found only the two
known external entry calls, with no external direct branch into
`0x802A445C..0x802A4540`. The branch into the hit setup is internal. This
supplies no evidence for an alternate external entry or a different split
boundary; it does not exclude indirect entries. The original provider and
all source, ABI, compiler and activation holds remain unchanged.

### Call-lowering and nonnull receiver-contract controls

The address-dependency example suggested checking whether a known callback
could temporarily retain call/address setup and later become a direct call.
In the inspected compiler, [`call_function`](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/optimizer/FunctionCalls.c)
chooses `branch_subroutine` versus `branch_subroutine_indirect_ctr` during
initial code generation, before either scheduler. No later CTR-call to
direct-call rewrite was identified. This supplies no evidence for a late
callback boundary, so no function-pointer alias permutations were compiled.

The survey was also extended to byte and halfword GPR argument loads, whose
modeled load latency is the same. `--include-narrow-loads` on the published
scanner finds 154 triples: the original 147 word loads plus two `lhz` and
five `lha` cases, with no direct branch-entry triple. This is a bounded
extension of the existing-code search, not a new same-shape source witness.

A [nonnull receiver-reference control](kenkyuw-nonnull-receiver-control.cpp)
then tested the actual valid-object precondition separately from pointer
spelling. This independent API takes a valid receiver by reference, collects
a nullable event, selects either that receiver or null, handles a miss, and
otherwise checks the event before re-reading it and updating the receiver.
The nullable test is meaningful because collection can fail. No production
parameter type, ABI, helper declaration or source body was changed.

The control passed 36 host comparisons against the direct null-list form,
including post-check changes to event code/body and observable miss effects.
Under the same GC/2.6 flags it emitted 128 bytes. The nonnull reference
contract did not remove the zero-valued selection arm or the subsequent
receiver comparison. After allocation the relevant blocks still contain:

```text
B4: mr    r3,r30
    b     B6
B5: li    r3,0
B6: cmpli cr0,r3,0
    bf    cr0,2,B9
    ... miss call and exit ...
B9: lwz   r4,0(r31)
    bl    check_event
```

The second-scheduler and final-branch dumps are identical. Re-encoding the
final trace reproduces every byte from the normal compiler runner; the
documented fixture also independently emits that same `.text`, SHA-256
`2f13bc06d6ce7c26ebdef2a53b560896081a0d6eb1cf4f91c57f07c5f7efc163`.
Thus a source-valid nonnull receiver contract alone does not supply the
missing empty arm under these settings. No production reference-signature
variant was attempted on the strength of this negative control.

Finally, the pass chronology rules out a simple stale-scheduling explanation
for an address copy removed during allocation. The allocator's coalesced-move
removal in [`Coloring.c`](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/backend/Coloring.c)
calls `deletepcode`. That routine in [`PCode.c`](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/backend/PCode.c)
clears the containing block's `fScheduled` flag. An otherwise unchanged
three-pcode hit block is therefore eligible for the second scheduler again.
Merely deleting such a copy cannot be assumed to preserve the first pass's
order. A distinct surviving boundary or another demonstrated mechanism is
still needed; these checks do not assert that all source forms are excluded.

### Conditional lvalues and implicit null adjustments

Two bounded controls audited whether a language-generated boundary could
fit the real collection-failure path without adding artificial control flow.
Both used the same stock GC/2.6 compiler and flags recorded above. Every
final trace was independently re-encoded and matched the corresponding
normal compiler function byte for byte.

The [conditional-lvalue control](kenkyuw-conditional-lvalue-control.cpp)
collects a nullable event, reports a miss on failure, and otherwise binds a
pointer reference to one of two genuine receiver slots. Both slots are
observable choices. The callback can replace or clear the selected slot,
so the function must read that same slot again after the call. Its 144 host
cases check null collection, both slot choices, null/nonnull receivers,
accept/reject results, replacement/clearing, and the untouched other slot.
Build the host check with `-DKENKYUW_WITNESS_HOST_CHECK`.

The frontend does have a scalar conditional-lvalue path separate from the
aggregate conditional-expression path. In
[`CExpr_LValue`](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/frontend/CExpr2.c),
`ECOND` arms that are compatible indirect lvalues become a conditional of
their addresses, wrapped in an indirection. Binding the reference therefore
selects a slot address rather than selecting the pointer value in that slot.
The 124-byte control retains that distinction through allocation and both
schedulers:

```text
    cmpi cr0,r31,0
    bt   cr0,2,B8
B7: addi r31,r30,4
    b    B9
B8: mr   r31,r30
B9: lwz  r3,0(r31)
    lwz  r4,0(r4)
    bl   inspect_slot
    ... later reload r3 from 0(r31) on acceptance ...
```

Final branch optimization changes nothing. The real selection branch,
nonzero slot offset and receiver load remain. Function text SHA-256:
`b645a6b92f0e895bd648aaab8aebaeb6ddfe7f2b1be335f93148dda284d7133e`.
PSO's null-list arm calls the miss callback and exits; it supplies no second
receiver slot for the hit call. Its receiver argument is the projectile
value itself, not a pointer loaded from a selected slot. A reference cannot
use a null-list dereference as its other arm. This control therefore does
not justify a full-unit conditional-lvalue candidate.

The [base-conversion control](kenkyuw-null-adjustment-control.cpp) contrasts
an ordinary zero-offset primary base with a genuine nonzero secondary base.
Four host cases check null preservation and nonnull object addresses. The
primary conversion emits only `blr` (4 bytes). The secondary conversion
emits 16 bytes:

```text
    cmplwi r3,0
    beqlr
    addi   r3,r3,4
    blr
```

Before final branch optimization the conditional targets the return block;
the late pass rewrites it to a conditional return. The comparison and real
adjustment remain, as required to preserve null. Secondary function SHA-256:
`88385080181aa960359611757a5aa9ee1498e03d7651b4e0edaa9dba959eae4c`.

An additional header-backed compile used the actual declaration, with no
replacement layout:

```cpp
#include "pso/misc/TNeedleShoot.h"
extern "C" TObject *convert_projectile_base(TNeedleShoot *p) { return p; }
```

That function also emits only `blr`, SHA-256
`f332ea5b5437103cbb6f1508679da89eec9288ad775c96c439a17fccabe3de8e`.
In [`CClass_AccessPathCast`](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/frontend/CClass.c)
the nonvirtual adjustment is conditional on a nonzero base offset;
[`CExpr_SafeClassPointerCast`](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/frontend/CExpr.c)
does not create `ENULLCHECK` when the cast leaves the expression unchanged.
The actual `TNeedleShoot : TObject` conversion offers no such boundary.
The diagnostic secondary-base layout is not evidence for PSO ownership or
layout and was not transplanted into the unit.

Neither control supplies a source-faithful split for the target pair. No
full-unit candidate, production signature, compiler flag or link-provider
change followed from this audit. The exact two-instruction scheduling
blocker remains; the earlier genuine late-branch witness remains valid
within its demonstrated receiver-lifetime conditions.

### Original-object comparison and the remaining evidence threshold

A further survey on main `baa0b4e482921446c794fcbb2ccb798d2d05a7fa`
and PR source `b1bc33f98d47780831c17ee667af3cb020383977` closed a gap
in the earlier comparison corpus: compiled source objects omit instruction
patterns that remain unmatched. The scanner now accepts `--provider original`
to inspect corresponding original split objects while selecting the same
configured GC/2.6 command/flag cohort. This selection does not independently
prove which compiler or pragmas originally produced those objects.

```sh
python3 docs/evidence/kenkyuw-argument-boundary-scan.py \
  --include-narrow-loads --provider source --output source-boundaries.json
python3 docs/evidence/kenkyuw-argument-boundary-scan.py \
  --include-narrow-loads --provider original --output original-boundaries.json
```

Both surveys cover 3,093 objects. Source objects contain 19,495 eligible
function symbols and 154 triples; original objects contain 19,425 eligible
function symbols and 156 triples. These are symbol counts under the scanner's
defined, nonzero-sized function filter, not a claim of identical function
symbolization or recovered original translation units. All 154 source-site
keys (source, symbol, function-relative offset and registers/load kind) also
occur in the original survey. The only two original-only sites are:

| Function | Function offset | Relevant original sequence |
| --- | --- | --- |
| `TWindowSubStatusDisp__sub_8026E1D4` | `0x3E8` | `stw r0,0x68(r31); mr r4,r20; lwz r3,0x68(r31); bl set_selection...` |
| `TObjPlayer__sub_802A445C` | `0x94` | `mr r3,r30; lwz r4,0(r31); bl is_hit_receivable_target...` |

The window site has a real preceding store to exactly the loaded field;
it supplies no store-free scheduling witness. The dispatcher is the only
original triple at a decoded direct branch target, and the only one with
zero preceding instructions in its decoded block. Thus the original corpus
adds no second comparable unresolved site to pursue. As before, indirect
jump-table destinations are not reconstructed, source pragmas require a
separate audit, and this is a bounded cohort rather than a universal result.
The original input DOL still has the required SHA-1 recorded above.

The scanner binds each run to an ordered digest of object paths and complete
object hashes. For this snapshot the source corpus digest is
`ec2df550be0d02c9a1e04691d401df3e1cb96e29de66cbbad410605e49f770fb`,
and the original corpus digest is
`c0bd299c61a835fae6233b3719f7011c73c5153278b3d518c0fb9f677326184c`.
No compiler, binary, private object, or private report is published by the
scanner, and it neither builds nor changes the selected provider.

The alternative post-allocation load-to-copy route was also checked in
[`ValueNumbering.c`](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/optimizer/ValueNumbering.c).
`simpleload` and `pointerload` replace available loads by inserting a copy
and deleting the old load; both operations clear `fScheduled` through the
normal pcode mutation functions. This extends the earlier coalesced-copy
audit: neither route demonstrates a stale scheduled flag that would let a
new three-pcode move/load/call block evade the second scheduler. No source
permutations were compiled on the strength of that unsupported explanation.

The strongest demonstrated mechanism remains the genuine late-deleted
branch witness, but its receiver-in-`r3` empty arm has not survived the real
collector/lifetime conditions. Another generic conditional witness alone
would not reopen the target search. Useful new evidence would be either:

- A same-GC/2.6, same-flags truthful control whose preceding external
  collector returns a nullable list in `r3`, whose miss path exits, and
  whose receiver and list remain live for a post-predicate list reread and
  receiver callback, while a genuine boundary separates the independent
  move/load until after scheduler two. The stock-run authenticated trace
  must show how that boundary disappears without extra comparisons,
  argument calculations, loads, stores or copies remaining.
- Independent original source/build or layout/ABI evidence that changes
  those currently modeled lifetimes or the compiler provenance, together
  with a reproducible explanation of the complete target sequence. Another
  project-assigned helper name or an incompatible compiler's matching pair
  is insufficient.

Those are evidence requirements for a new experiment, not permission for a
compiler override or fabricated semantics. An activation candidate still
must preserve all 57 target instructions, nine siblings and relocations and
pass a real source link with the original DOL hash. This audit identifies no
further productive source compile under the current model; it does not
prove that every source-level solution is impossible.

### Cross-flag GC/2.6 cohort check

The exact-flags survey excluded some GC/2.6 units because of floating-point
contraction, debug symbols, small-data settings, string pooling or inlining
options. Those exclusions alone do not establish a different GPR argument
scheduler. A second read-only pass therefore included every configured
GC/2.6 source-object rule, classifying sites by the complete flags rather
than assuming that any option difference explains the instruction order:

```sh
python3 docs/evidence/kenkyuw-argument-boundary-scan.py \
  --flag-scope all-gc26 --include-narrow-loads --provider source \
  --output all-gc26-source.json
python3 docs/evidence/kenkyuw-argument-boundary-scan.py \
  --flag-scope all-gc26 --include-narrow-loads --provider original \
  --output all-gc26-original.json
```

On the same `baa0b4e4` main/`3f3b6b202` PR snapshot this covers 3,399 objects
in 43 full-flags groups, with no missing objects. The source survey contains
23,918 eligible function symbols and 190 triples; the original survey
contains 23,972 eligible function symbols and 195 triples. Relative to the
exact-flags cohort this adds 306 objects, 4,423/4,547 source/original function
symbols and 36/39 triples. The scanner records each site's compiler, full
flags, dispatcher-flags equality, and per-flags object/function/site counts.

Only the group configured with `-O3,p -inline off -opt nopeephole` contributes
new zero-prefix or direct-branch-entry sites:

| Function | Function offset | Calls | Present in |
| --- | --- | --- | --- |
| `load_nj_chunk_model_resource` | `0x218` | `move_data` | Source and original; direct branch target |
| `load_nj_chunk_model_resource` | `0x224` | `DCFlushRange` | Source and original; immediately after the preceding call |
| `dispatch_chunk_polygon_list` | `0xC0` | `apply_chunk_texture_command` | Original only; conditional fallthrough |

The polygon unit explicitly has global `#pragma scheduling off`, so that
site supplies no same-settings source witness. The resource-loader function
has no function-scoped scheduling override. Its unchanged complete unit was
compiled privately first with its configured flags: the entire `.text` and
all relocations reproduced the cached source object, and the 1,104-byte
loader is 100% exact in the existing report. One further diagnostic compile
used precisely the dispatcher flags, including `-O4,s -inline off -sdata2 4`,
with the real headers and unchanged source. Both new triples became
load-first. Around the cache flush:

```text
configured:       mr  r3,r30       dispatcher flags: lwz r4,12(r1)
                  lwz r4,12(r1)                      mr  r3,r30
                  bl  DCFlushRange                    bl  DCFlushRange
```

The loader becomes 1,056 bytes under dispatcher flags; function text SHA-256
`a2f7ffc482f4c63c88b3acb58b5e8d1786ab4697940ab0fedf35598020f1728c`.
The unchanged unit source SHA-256 is
`0ebc7062a433c4d90e958f2c7cc84674e406863c3373ecb3ea62d13882cce03f`.
No source edit, flag change or link-provider change was made in the project.
The additional cohort therefore supplies no source lead that survives the
required flags; no new dispatcher permutation or full-unit candidate follows.
Indirect jump-table destinations and original build provenance remain the
same bounded-survey limitations described above.

Finally, the verified delete/insert invalidation paths must not be generalized
to every pcode mutation. In the inspected compiler,
[`change_opcode` and `change_num_operands`](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/backend/PCodeInfo.c)
do not clear `fScheduled`; neither does `appendpcode`. The in-place
`EXTSB`/`EXTSH`/`RLWINM` to `MR` rewrites in
[`adjustforward`](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/backend/Peephole.c)
require preceding genuine narrow-value definitions, absent from the target's
pointer-valued argument setup. The post-color merger's append path follows
deletion of the predecessor's terminal branch when such a branch is present;
that deletion clears its scheduled flag. These facts narrow the hypothesis
without proving all possible stale-state cases impossible. If a real source
lead emerges, the discriminating trace should record the target block's
`pcodeCount`, `fScheduled`, instruction identities and predecessor links
immediately around `peepholemergeblocks(TRUE)` and `peepholeoptimizepcode`.
No such lead was established by this survey, so no artificial narrow cast,
dummy definition or new target source permutation was compiled.
