# Dragon ground grid unit

The unit `pso/boss/TBoss8Dragon_8002CC48.cpp` owns text at
`0x8002CC48–0x8002DF7C`: 23 functions, 4,916 bytes. The recovered
`TBoss8Dragon__sub_8002D5F8` is 1,268 bytes. Its existing address name remains
provisional; the globals and callers establish the ground-grid initialization
role, but do not establish a new class member signature.

The initializer takes material words from resource model 4, creates 11-by-11
and 5-by-5 position/normal grids, fills their UV coordinates, and creates an
11-wide single-strip grid. It then edits model 3's chunk polygon stream,
allocates its UV pairs, and collects vertices above height 15 into 16-byte
deformation records. The last record field is a signed state/countdown,
initialized from `rand()` and read by the existing update routine. Source model
vertices are six-float records following an eight-byte header. The private grid
allocation is 0x68 bytes; its embedded object has an unwritten four-byte tail.
These private overlays describe this unit's accesses rather than a newly
asserted public model ABI. The shared accessors now return pointers, and the
initialization caller shares the recovered void declaration.

## Compiler constraints

An ordinary indexed UV loop produced all the correct operations and register
operands but reordered three setup instructions (98.99054%). A compiler trace
using [mwcc-debugger](https://github.com/cadmic/mwcc-debugger), following the
[existing tracing workflow](moja-compiler-tracing.md), showed two initial
induction values. One became unused when the loop became a CTR loop. Its late
deletion cleared the block's scheduled flag and caused another scheduling pass.

A named width of 11 for the first grid constructor, with scoped
`opt_propagation off`, leaves constant propagation to the backend. The matched
trace runs constant propagation and dead-load cleanup before scheduling; only
the used UV induction value remains in the preheader. Register allocation then
preserves the original setup order. The production GC/2.6 compiler independently
produces all 1,268 bytes exactly. Removing either the width binding or pragma
restores the scheduling mismatch. Other loop forms, inline helpers, scheduling
models, and installed compiler versions did not preserve the complete object.
The pragma is an implementation choice, not evidence of the historical source.

The first twelve functions are defined in reverse order with deferred code
generation. A UV-record size check after `defer_codegen off` flushes them before
the named default-scale constant. This preserves their text order, the scalar
pool, and both compiler-generated vtables: Solo at `0x80482048`, SoloM at
`0x80482060`. Immediate emission reverses those vtables even though objdiff
reports the data as matching. This follows the repository's
[emission-order evidence](compiler-emission-evidence.md); the link checker also
verifies the named objects' offsets.

## Data and validation

The unit owns the two native vtables (48 bytes), the signed conversion pool
(8 bytes), and `.sdata2` at `0x805D8178–0x805D8200` (136 bytes including
alignment). The final object contains 132 scalar bytes; the last four bytes
are zero alignment, not an eight-byte float object. The symbol at `0x805D81F8`
is therefore four bytes. The named 16.0 default scale keeps its original pool
position with a guarded section attribute; the other constants are ordinary
float expressions. The localization tool checked all active original and
compiled consumers before marking the 32 anonymous scalar labels local.

The duplicate rock render definition belongs to the following unit and is
removed here. No asset bytes, hand-written vtables, assembly, padding objects,
or compiler/tool changes are needed. Completion requires the whole-object
report, source-link checks, retention/no-loss checks, and original DOL SHA-1
check described in [CONTRIBUTING](../../CONTRIBUTING.md).
