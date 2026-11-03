# Gryphon lightning construction

This follows up on #213 without reverting it. On fork main
`0a3bc130601435d2108cca9afc5d6df69c4ee64a`, the constructor at
`80324F4C` scores 89.685715% and is not source-linked. Its compiled body
is 276 bytes versus the original 280. A passing DOL check on that baseline
uses the original object, so it establishes no constructor recovery gain.

The existing `TBoss5GryphonLightning` class now owns the recovered fields.
Its genuine constructor takes `TObject *parent`, a floating parameter, and
`const Vec *source`, and invokes `TObject(parent)`. The two positions and four
16-byte point records are actual subobjects. The derived Wing and Horn
constructors use the same shared interface and compiler-generated vtables;
the parallel layouts, manual vptr stores, and incompatible one-float base
declarations are removed. Size and offset assertions cover the native layouts.

Wing/Horn factories construct real objects. Each factory's local endpoint and
the Wing helper's local middle point are genuine `Vec` objects, synchronously
copied by the constructors; their addresses are not retained. The Wing middle
point and helper endpoint inputs remain mutable pointer borrows. With GC 2.6,
making them const changes coordinate load scheduling. In the Wing constructor,
the explicit, genuine base-subobject pointer also preserves the native loop's
per-coordinate loads and stores. These are compiler observations, not claims
about the historical source spelling. The factory's existing address-valued
`s32` result and Wing C export spelling remain compatibility boundaries; integer
casts no longer substitute for constructor arguments or object construction.

The constructor stays in `pso/unk/text_80324F4C.cpp`: its complete compiled
allocation is exactly 280 bytes of text, with 13 native relocations and no data.
The adjacent destructor unit continues to own its existing generated vtable
and data. Folding them is unnecessary to reproduce either allocation. Four
same-address symbol renames record the compiler-generated constructor and
typed static-factory identities; no alias or manual table is introduced.

Validation against a separately built clean baseline at the commit above:

- Constructor: all 280 instruction bytes and all 13 relocation destinations,
  types, offsets, and addends match the original.
- Existing destructor, Wing, Horn, and Gryphon caller objects: 159 function
  bodies, all allocated section bytes/layout, and all physical relocations are
  preserved, allowing only the four declared global renames and equivalent
  compiler-local label names at the same section/offset.
- `tools/check_pr.py`: PASS; matched functions +1, matched code +280 bytes,
  matched data +0, source-linked units 3547 to 3548, zero regressions.
- The actual linker response selects `src/pso/unk/text_80324F4C.o`, not its
  original fallback. The map places the generated constructor at `80324F4C`
  with size `0x118`. The DOL SHA-1 remains
  `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- The complete build and linked-unit/retention checks pass with isolated tool
  copies. No split boundaries, compiler profiles, or unrelated unit selection
  are changed. Remaining unrelated Gryphon geometry reconstruction is separate.
