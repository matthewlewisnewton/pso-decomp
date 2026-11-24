# GC/1.3.2 feasibility for the remaining boss units

Investigation date: 2026-11-14. Sources are unchanged from revision
`08c178922f`. This is a bounded investigation of Gryphon and Dragon under
GC/1.3.2, not a production migration. Slime is covered separately in
[its GC/1.3.2 investigation](compiler-consolidation-gc132-slime.md).

## Result

The large initial regression counts do not represent dozens of independent
optimizer incompatibilities. Many come from function-pointer casts in the
reconstructed source: GC/2.0 folds a known casted function address into a
relative direct call, while GC/1.3.2 often emits an indirect call through
`ctr`. Removing those casts in favor of compatible direct calls recovers
real matches under the older compiler.

| Unit | Exact original functions with GC/2.0 | Unchanged source with GC/1.3.2 | Best bounded GC/1.3.2 source probe | Previously exact functions still lost |
|---|---:|---:|---:|---:|
| `Boss5GryphonBehavior.cpp` | 168/168 | 130/168 | 146/168 | 22 |
| `TBoss8Dragon.cpp` | 138/141 | 78/141 | 91/141 | 47 |

The probes restore 16 Gryphon and 13 Dragon functions without losing any
function already exact in the unchanged-source GC/1.3.2 build. Neither
complete object is equivalent to its GC/2.0 baseline, so neither compiler
assignment can be changed yet. Dragon's three pre-existing unmatched
functions remain unmatched. These counts measure exact original functions,
not just improvement in a similarity score.

All allocated non-code sections retain their GC/2.0 baseline contents,
sizes and ELF alignment in the best probes. Code remains different:
Gryphon `.text` is 35,152 bytes versus 34,984, and Dragon `.text` is 36,696
versus 35,836. Function layouts and code relocation positions therefore
still differ. This is not evidence that Dragon's baseline non-code sections
already fully match the original.

## Shared cause and source probes

All 60 initially changed Dragon functions and 32 of 38 initially changed
Gryphon functions lose at least one direct `bl` call relative to GC/2.0.
The comparison observes those call changes; it does not claim every other
instruction difference is caused by them.

For example, Dragon's `store_position` casts `VecCopy` to a function taking
two integers, then passes integerized addresses. GC/1.3.2 expands the known
function address with `lis`/`addi`, followed by `mtctr`/`bctrl`. A scratch
rewrite uses a byte pointer for the existing offset-based interface and
calls the existing two-pointer declaration directly. The complete function
then matches. Other probes remove return-type-only casts where the return
is ignored, call vector and matrix helpers directly, and use declared
argument types for the existing provisional interfaces.

Three stages were compiled for each unit:

1. Compatible direct calls and vector-copy address cleanup: three functions
   restored in each unit.
2. More direct calls, correct floating/integer argument ordering for
   `move_along_angle`, and the Gryphon external constant declaration below:
   11 Gryphon and eight Dragon functions restored cumulatively.
3. Additional direct calls to the already-declared random, flag, particle,
   state and sound helpers: 16 Gryphon and 13 Dragon functions restored
   cumulatively.

Gryphon's external eight-byte `lbl_80437EB0` constant needs its known
`.rodata` placement stated explicitly in this experiment. Without that
information, GC/1.3.2 emits an SDA-relative load where the original and
GC/2.0 use `lis` plus `lfd`. Adding
`__declspec(section ".rodata")` to the external declaration restores the
addressing mode. This declaration is a proposed compiler-specific source
exception, not an adopted production change.

These probes do not add assembly or change the compiler executable. They
also do not add guessed callee arguments to paper over missing signatures.
Pointer/integer conversions remain at several existing provisional
interfaces in the scratch code; the patch is research material, not a
reviewed API cleanup ready to land.

## Remaining work

There is more ordinary source-recovery work available, but it is not all a
mechanical cast-removal pass:

- Some callers pass arguments through a cast while the declared or defined
  function omits them, including implicit object arguments. Some declared
  return types also disagree with the cast used by callers. Those need
  callee and call-site evidence before changing shared signatures.
- With direct calls restored, some Gryphon functions still differ in
  argument preparation order. For example, `handle_descend_state` places
  the incoming object and angle preparation differently around the float
  argument load. Its score improves but is not exact.
- Some direct Dragon calls expose narrowing implied by the current
  declaration. The `get_entity_id` cleanup, for example, introduces a
  `clrlwi ...,16` where the reference has a register move. This needs an
  authoritative interface decision rather than another incompatible
  function-pointer cast.

The five aggregate-copy helpers that blocked GC/2.6 (three Gryphon, two
Dragon) already match under unchanged-source GC/1.3.2 and stay matched in
these probes. The older compiler is therefore a credible route if source
interface cleanup is desirable. However, retaining GC/2.0 currently
preserves all those exact functions without these repairs. This experiment
alone does not justify replacing it, or establish Sega's historical
compiler version. A decision should also use the independent reverse
GC/2.6-to-GC/2.0 sweep.

## Reproduction and limits

Local artifacts are in `/tmp/pso-gc132-game-blockers/`:

- `probe.py`: unchanged-source and first-stage compilation/comparison.
- `direct.py`, `more.py`: subsequent source transformations.
- `<unit>/<stage>/`: same-basename scratch source, compiler argv and log,
  output object, comparisons against both fresh original split objects and
  the GC/2.0 baseline, and result summary.
- `<unit>/direct-more.patch`: best bounded source probe for review.
- `manifest.json`: production-source and probe hashes, changed section list.

Run each script from the repository root. They use read-only installed
compilers, Wibo, objdiff and generated includes from
`/home/matt/workspace/pso-decomp/build`, and original objects from
`/tmp/pso-compiler-consolidation-20261113/original/obj`. The compiler needs a
host execution context in which Wibo is permitted. The scripts write only
their own scratch output. Compiler-only and source experiments keep the
original production flags. Failed exploratory compilations are not counted
as source matches.

No production configuration or source changed. Since no full preserving
candidate was found for these two units, no integrated link or
`check_pr.py` acceptance was claimed. Complete code, data, relocation and
link validation remains required before either proposed migration.
