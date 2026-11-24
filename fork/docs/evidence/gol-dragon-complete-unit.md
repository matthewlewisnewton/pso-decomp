# Complete Gol Dragon behavior unit

This change starts from fork main `554d21699c873ccf9be1b2268eba37cd3a32e48b`.
The unchanged baseline was configured, split, compiled and linked in a fresh
worktree using the pinned tools and the original disc inputs. Its DOL hash and
retention checks passed before source changes.

Final integration uses current fork main
`8c973b965d` (including the draw-line component). That exact base was also
configured, split, compiled and checked in a separate fresh worktree. Both its
unchanged checks and the integrated candidate's incremental `check_pr.py` checks
pass; linked units increase from 3,621 to 3,622.

## Recovered behavior and interfaces

`pso/boss/TBoss8Dragon.cpp` contains 141 functions at
`0x802F44D8`–`0x802FDDD4`. The three remaining functions were:

- `0x802F89F8`: an event/state handler with seven update phases, seeded projectile
  placement, rotation and vertical movement. It remains `fn_802F89F8`; the
  implementation does not claim an original action name.
- `0x802FA4E4`: the action dispatcher, with a 44-entry local static array of real
  C++ member pointers. Entries 20, 33 and 34 are null. The remaining 41 entries
  reproduce the native compiler-generated initializer records.
- `0x802FDA78`: resource loading, tree cloning, camera-vector initialization,
  combat-parameter lookup and shared-state reset.

The dispatch array establishes member ownership for its 38 distinct handlers.
Their old descriptive names are retained where already established; unresolved
handlers keep address placeholders. There are no free-function-to-member-pointer
casts or manually encoded member pointers.

The initializer's third clone argument is a model pointer, not the formerly
provisional integer/zero argument. It refers to the 24-byte `NJS_CNK_MODEL` at
`0x80541E18`. The preceding three camera vectors occupy `0x80541DF4`–`0x80541E18`.
The existing clone provider now uses `NJS_OBJECT` and replaces its `model` field;
the recursive count helper likewise traverses `child` and `sibling` as a free
model-hierarchy operation rather than casting model nodes to a boss class.
The original allocation remains 0x50 bytes per counted node; the clone advances
by `sizeof(NJS_OBJECT) == 0x38`. This change does not infer why the allocation
has that extra capacity.

The projectile constructor has shared pointer arguments and a 16-bit owner ID.
The random-ratio provider now explicitly accepts the generator-state pointer it
passes onward in r3, with its next result converted to unsigned before shifting.
The generator's full shared storage type and older unrelated receiver overlays
remain outside this recovery. Existing provisional C interfaces and overlays
are retained where the unit does not establish stronger ownership.

## Compiler experiments

The first initializer candidate compiled at 77.18%. Separating the camera-vector
and replacement-model ranges, retaining short address lifetimes, using ordered
stores and passing the actual model pointer brought its 420 bytes to an exact
match. The first state-handler candidate was 97.61%; the seed-packing spelling
already used by `TBoss1Dragon`, the verified virtual slot and explicit float
intermediates removed the differences.

`Boss5GryphonBehavior.cpp` supplied the member-pointer dispatcher precedent.
An immediate-compilation trial changed constructor and initializer instructions.
An outlined table helper did not reproduce the dispatcher. The final source uses
its existing deferred settings, descending function definitions, and the local
static array directly. Its three Bezier arrays are declared after that function
so the static initializer records, destination table and native vtable retain
their original data positions. This is an observed source arrangement, not proof
of historical source order. The general constraints are described in
[compiler emission evidence](compiler-emission-evidence.md).

Matching instruction bytes did not initially match switch relocations. Twelve
handlers' no-op events pointed to an earlier equivalent return block. Moving
only their `default` labels to the final switch exit preserved the instructions
and corrected all 58 differing table relocations. All 664 `.data` relocations
then agreed with the original. The final `.text` also has identical raw bytes
and all 1,760 symbolic relocations agree.

The final float work compared default optimization, propagation disabled,
common-subexpression elimination disabled, lifetime optimization disabled and
combined settings. Only scoped `opt_common_subs off` retained the native float
register operands in the three functions listed in the
[porting register](../porting-exceptions.md#complete-gol-dragon-behavior-unit).
Explicit acceleration and velocity intermediates also retain the final helper's
two fused multiply-add operand orders without an intrinsic or assembly.

## Owned data and validation

The explicit tables, camera vectors and 84 named float constants reproduce the
unit's `.data` (4,720 bytes), `.bss` (128), `.rodata` (8) and `.sdata2` (336).
The shared small globals own `0x805D6988`–`0x805D69C8`: 60 emitted `.sbss` bytes
and four bytes of zero alignment before the next eight-aligned unit. The final
float at `0x805D69C0` is four bytes; its previous eight-byte symbol included that
padding. The existing link checker validates the following alignment and padding.
The total source-linked data coverage is 5,256 bytes.

Provisional aggregate symbol ranges are partitioned at actual emitted object
boundaries. Initializer records, the member-pointer array and its guard are local.
The compiler-generated signed conversion bias at `0x80474B10` is localized only
after `localize_split_globals.py` checks the fresh consumer inventory.

All 141 functions and every owned section compare at 100%. The source-linked
DOL reproduces SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
The address-based report gains three exact functions, 3,328 matched code bytes,
5,120 matched data bytes, 39,164 source-linked code bytes and 5,256 source-linked
data bytes, with no losses. The generated retention block adds the unit's
previously unreferenced exported symbols without removing existing entries.
