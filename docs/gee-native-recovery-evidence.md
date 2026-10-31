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

The candidate also merges the immutable draft random/phase stack:

- `d8c77c6597a216329a7922f28e0f38d919f57d38` (fork PR81): nonstatic
  actor receiver for `TObjEneDD::get_random_scaled`.
- `ad9f594f4bb350d1548850df1d8b17c63f05e2ac` (fork PR82): full-register
  `s32` result for the static main-phase predicate.

PR82 is the immediate fork-local base. These shared heads have targeted owner
object checks but their full certification is pending. This layer introduces no
generic declarations or shims. The combined Gee draft must pass its own exact
checks and independent review after the parent gates; prior matching results do
not certify this reapplication.

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
