# Gee native recovery checkpoint

This bounded reapplication preserves the Gee and private swarm recovery reviewed at
`9a3f61a766eddfcb20c60bab45810ec91045ec10`. It changes their two owning headers,
the main unit, the adjacent mechanical resource-getter call, and the Gee-only
compiler/split/symbol configuration. Shared headers and implementations are retained
from the fork base. The main and swarm shadow calls use the base's canonical
`draw_ground_shadow` declaration.

## Required prerequisites

The initial fork base `623d9415a5edb3e27c686135385dcf98b5fa36bc` lacks these
reviewed contracts needed by this source:

- `c8556ebbba071e334b2d994c92fc5dcba4d07fdf`: canonical
  `MaterialOpacityFade` class and implementation. The native member is 0x1C
  bytes at Gee offset 0x3CC; its construction/destruction is automatic.
- `028902d2ca5bacfde2ec6cb4f37865f7ed53b57c`: nonstatic actor receiver
  for `TObjEneDD::get_random_scaled`.
- `e2267dabd4c903e79b5f7f13b98c8f987858590d`: full-register `s32`
  result for the static main-phase predicate.

The integration lead supplies coherent equivalents on a fork-local common base.
This layer introduces no generic declarations or shims to fill those gaps. The
initial draft is unvalidated on this base; prior matching results do not certify
this reapplication. Validate after the prerequisite base is available.

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
