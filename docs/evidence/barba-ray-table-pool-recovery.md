# Barba Ray table-pool recovery

PR 456 completes `pso/boss/Boss7DeRolLeCBehavior.cpp`: all 90 functions,
24,736 instruction bytes and 7,792 data bytes match and link from C++.
The selector at `0x802E7BE8` now uses ordinary indexing for every lookup.
There is no assembly or pointer-to-integer conversion in that function.

## Compile, trace, research, revise

The review hold concerned hand-scaled byte offsets into the action and kind
arrays. Replacing those accesses while retaining the former external aggregate
view changed address folding, instruction scheduling and register allocation.
Changing only the kind lookup swapped r10/r11; many local spelling and optimizer
variations did not restore the complete match. Those failures did not establish
an assembly origin.

The next investigation followed the repository's
[Moja compiler traces](moja-compiler-tracing.md),
[Dragon grid recovery](dragon-ground-grid-recovery.md), and
[deferred-emission evidence](compiler-emission-evidence.md). Read-only traces
of the original GC/2.6 compiler through
[mwcc-debugger](https://github.com/cadmic/mwcc-debugger) distinguished frontend
index temporaries from backend table-base materialization. The debugger was a
diagnostic tool; acceptance builds use the normal unmodified compiler and wibo.
The debugger project's allocator notes and the compiler's `TOC.c` pool handling
explain why a manually reconstructed aggregate address is not equivalent to a
compiler-managed data-pool reference during optimization.

The decisive experiments were:

| Source representation | Result |
| --- | --- |
| External aggregate view, ordinary indices | Address folding and register differences remain. |
| Ordinary kind/yaw indices, retained native angle-base conversion | Correct registers, but two address/shift instructions exchange positions. |
| Separate real action, position and yaw tables defined in this unit | Native address and load instructions appear without scaled offsets or integer address casts. |
| Those definitions, function-scope positions pointer and branch-scope locations pointer | All 220 selector instruction bytes match. |
| Entire original leading data pool plus compiler-generated class vtable | All data can be owned by the behavior unit without artificial gaps. |
| Deferred generation, reverse definitions and preserved inline expansion | All 90 functions, data, alignment and resolved relocations match; full DOL checksum passes. |

The source arrangement is a reproducible matching implementation, not a claim
that these were the historical declaration names or exact source order.
Unlike the cross-version evidence discussed in Twilight Princess's
[J3DSkinDeform investigation](https://github.com/zeldaret/tp/pull/2896), this
case has an exact compiler-generated C++ result. There is no reason to infer
wrapped assembly here.

## Data ownership and emission

The unit now owns `.data` from `0x804E3BF0` through `0x804E45C4`, adding the
1,032-byte prefix formerly left in an automatic original-data object. Its real
objects are the scale and joint offsets, three four-entry pattern tables,
six load/unload callback pairs, the seven-word movement parameters, model and
motion name lists, the resource descriptor, 17 motion actions, particle indices
and widths, and the compiler-generated 420-byte `TBoss7DeRolLeC` vtable.
The existing compiler-generated switch tables follow at `0x804E3FF8`.

The original labels at `0x804E3C2C`, `0x804E3C5C` and `0x804E3D1C` each covered
multiple objects. Their extents are separated at the observed array and record
boundaries. No padding objects or hand-written vtable are introduced.
The actual resource and action types determine their layout. The neighboring
renderer and resource loader share the real scale, callback and descriptor
declarations instead of declaring the same symbols as opaque integer arrays.

Declaring the existing `render_shadows` override first gives this unit ownership
of vtable emission without changing virtual slot order. The previously free
state dispatcher becomes the actual `dispatch_action(u32, s32)` override;
using `this` directly preserves all 1,052 instruction bytes. Its symbol and the
vtable name are updated consistently. The spawn position argument is const,
matching its read-only use and avoiding a cast at the selector call.

Deferred generation emits the vtable before switch tables. Reversing function
definitions restores native text order. Explicit inline expansion remains
available during the deferred pass: otherwise the short-update helper and an
aggregate assignment become calls, changing two functions. Repeated identical
pragma scopes are consolidated, and all controls are registered in
`porting-exceptions.md`.

The neighboring legacy constructor still uses its established bounded native
address view. That declaration now explicitly refers to the objects owned here;
it does not define storage. Its 1,616 bytes remain exact. This change does not
claim a complete portable reconstruction of that constructor or every legacy
interface in the behavior unit.

The separately registered signed-short update in `spawn_pattern_crawfish`
remains. Scalar, reference-helper and named-base alternatives were compiled;
they did not preserve its native register operands. The review identified this
as nonblocking independently of the now-removed selector accesses. It remains
an explicit porting obligation, not evidence of original assembly.

## Validation

The baseline is fork main `8e27ed9a61756b650fde9788d356785e68929402`, freshly
built and checked before these changes. Original objects and configuration are
regenerated from the checked-in metadata and pinned original inputs.

- All allocated sections match: `.text` 24,736 bytes, `.rodata` 4,872 bytes,
  `.data` 2,516 bytes and `.sdata2` 404 bytes.
- Relocation-sensitive comparisons use `functionRelocDiffs=data_value`; linked
  unit checks additionally verify symbol offsets, sizes, alignment and resolved
  relocations.
- Full source-linked DOL SHA-1 is
  `0d85744b51d7379efb025a943d0cd5aaae2191a3`, identical to the original.
- Against main: +3 exact functions, +2,216 matched code bytes, +2,920 matched
  data bytes, +24,736 source-linked code bytes and +7,792 source-linked data
  bytes. Report denominators are unchanged and no address loses coverage.
- A 64-bit host harness extracts the actual selector and compares it with the
  previous native-addressing implementation across 5,760 difficulty, pattern,
  variant, column and slot combinations. AddressSanitizer and
  UndefinedBehaviorSanitizer pass. This is a focused selector check, not a
  claim that the entire game builds for the host.

Ignored `build/pr456/` artifacts retain the compiler traces, source experiments,
full-build receipts, comparisons and final gate report. No compiled objects,
original data dumps or diagnostic compiler modifications are committed.
