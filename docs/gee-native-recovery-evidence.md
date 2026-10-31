# Gee native recovery checkpoint

This bounded reapplication preserves the Gee and private swarm recovery reviewed at
`9a3f61a766eddfcb20c60bab45810ec91045ec10`. It changes their two owning headers,
the main unit, the adjacent mechanical resource-getter call, and the Gee-only
compiler/split/symbol configuration. Shared headers and implementations are retained
from the fork base. The main and swarm shadow calls use the base's canonical
`draw_ground_shadow` declaration.

## Current base and remaining prerequisites

The certified foundation merged at fork
`a166aa963a4afefc9d94608aeb4411a2b26dbf33` has the exact tree reviewed and
validated at `6286c30af81e4bb81cae2c99d0c2c818219f28a8`. It supplies the canonical
MaterialOpacityFade class/unit, BML/NPC storage and view/ground/position interfaces.
The native fade member remains 0x1C bytes at Gee offset 0x3CC, with automatic
construction and destruction. The Gee source uses the foundation's free demo
predicate, float ceiling helper, positional effects, typed motion-table setters
and ground-shadow calls. Shared declarations and implementations are unchanged.

The candidate also merges the current-core-aligned immutable draft stack:

- `d769df7015d21166caf915a39f27499ca7a40f5f` (fork PR81): nonstatic
  actor receiver for `TObjEneDD::get_random_scaled`.
- `8b7d34d0a4cceb973ee9be63a1b29062d2b6309e` (fork PR82): full-register
  `s32` result for the static main-phase predicate.

This stack includes certified core `c183840fc681ebca7351734acefa2e177f14f1ed`
with typed node callbacks, capture, collision, groups and state/checker changes.
Gee accepts the callback's unused NJS_OBJECT pointer and registers its function
through the canonical callback type, preserving its native camera cursor storage.
The phase stack also includes prospective typed render/sound base
`8fa0e6ebb852d005a628b8bd276a3c40b50d8d37`. Gee uses its current texture-list
setter and typed persistent/one-shot sound declarations with actual actor and Vec
pointers. The adjacent unit retains the prerequisite's mechanical texture binding
change; no new Needle behavior or layout is recovered.
PR82 is the immediate fork-local base. Shared full certification and this Gee
head's full build/check/provenance and independent review remain pending. No
generic shared definitions or compatibility shims are introduced. Earlier SHAs
are retained through normal merges.

## Native storage and emission

The recovered source owns both compiler-generated 472-byte vtables, its actual
constructors/destructors and factories, typed combat-parameter pointer arrays,
a camera Vec, a class-name pointer and seven private small-data globals. The
small-data source holds 28 bytes; natural four-byte alignment completes its
32-byte owning range. No dummy padding object or manual table is introduced.

The requester-approved Gee source-order arrangement uses reversed definitions
and `-inline off,deferred`. A finite independently reviewed 29-case compiler
investigation found no tested supported ascending-source alternative preserving
function placement, vtables, switch tables and relocations. This does not prove
all possible source arrangements fail or establish original source order.
[CodeWarrior Build Tools Reference, page 282](https://www.nxp.jp/docs/en/reference-manual/PA_Build_RM.pdf#page=282)
explains whole-translation-unit deferred processing in a later compiler; the
specific ordering observations come from probes of the installed compiler.

## Incomplete recovery

The collector at 0x800BB484, record copy at 0x800BB650 and Gee helper at
0x800CBB34 still need reconciled receiver/output and explicit floating-limit
contracts. Their existing overlay and implicit f1 forwarding remain provisional.
The real 0x10 breakup-model constructor and effect-creation interfaces remain
integer boundaries; the unrelated 0x54 TBreakUpMdl is not that allocation type.
Const color copy, movement/effect/matrix/debug interfaces and additional private
read-only/scalar storage remain open. The adjacent Needle unit has no behavior
or layout recovery in this layer. Integrating a bounded checkpoint does not
complete Gee's semantic or cross-unit recovery gates.
