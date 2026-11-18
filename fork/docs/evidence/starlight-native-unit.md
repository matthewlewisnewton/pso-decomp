# Native starlight effect unit

`TEffStarLight2D_Base.cpp` owns the complete `80084BC4..80085774` span:
18 functions, 2,992 code bytes and 220 data bytes. The baseline at
`45f9e45bd94f2beba952ca4f2cdfc3b03ec5623a` already matches and source-links
this allocation. This recovery preserves that coverage; it claims no new
matched bytes or linked unit.

The child constructor at `800855F8` calls `TObject(parent)`, installs the
`TEffStarLightChild` vtable, and writes the class-name pointer. Its two endpoint
arguments provide x/y coordinates; the task at `80085424` consumes the two
resulting edges at offsets `20` and `28`, and the shrink distance at `1C`.
These are the existing shared class's actual members. A genuine constructor
and native task replace the per-function layouts, manual base call/vptr write,
and C export wrappers. The parent task at `800851B0` now uses native `new` with
the previous/current screen points and width/speed parameters. All three bodies
match without a new compiler override.

The copier at `800852EC` addresses a twenty-byte parameter record, not a
`TObject`. Its callers pass `this + 38`; its loads/stores are two floats,
four individual color bytes, an integer and another float. Moving the method
to `StarLightParameters` removes the fictitious object-pointer arithmetic and
float writes through object-header members. The constructor keeps its existing
`void *` arguments as a compatibility boundary for callers outside this unit;
it immediately borrows the established `Vec` and parameter types. The existing
parameter-update entry keeps its `void *` ABI for the same reason.

## Compiler comparison

The first typed version matched 17 functions exactly, including both native
tasks and the child constructor. Its `const StarLightParameters *` copier
scored 71.23529%: it had the right size and operations, but GC/2.6 pipelined
loads ahead of stores and used extra registers. The complete text score was
99.34626%; all four allocated data sections matched.

Repository research found two relevant cases after that comparison:

- [Gryphon lightning construction](gryphon-lightning-construction.md) records
  coordinate-load scheduling differences from const versus mutable borrows.
- [Effect parameter storage and copy](effect-parameter-copy.md) uses scoped
  scheduling control for a different parameter copier.

Testing the mutable-source form first reproduces every alternating load/store
in the starlight copier, with no scheduling pragma. The method does not modify
its source. The existing reverse definitions and `defer_codegen` remain because
the emitted function, literal and three compiler-generated vtable sequences
must all match; [the emission investigation](compiler-emission-evidence.md)
explains why function scores alone are insufficient. No historical source-order
claim follows from this arrangement. The existing arithmetic and rendering
pragmas are retained, with no new exception.

Both changed symbol identities stay at their original addresses and extents;
retention metadata substitutes exactly those two names. Splits, compiler flags,
link selection and data ownership do not change. Layout assertions cover the
parameter fields, screen positions and child edges used by the recovered code.

Full `tools/check_pr.py` validation reproduces the original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`, with zero function/code/data/link
losses. All 18 functions and every allocated section match, and all 3,620
linked units remain exact. This is native ownership recovery, not a behavior
change or an audit of the existing rendering color union, numeric conversions,
or callers' initialization of the final parameter float.
