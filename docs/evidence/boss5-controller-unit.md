# Gal Gryphon controller unit

Against fork main `6d478092bf9791e1db79bb20a886173bb97e7021`, the three
adjacent `TObjBoss5Ctrl` fragments already match and link 748 code bytes and
32 data bytes. This change consolidates them, replaces the raw constructor
and allocation wrapper with native C++, and recovers 36 additional matched
and source-linked data bytes. It claims no new function or code matches.

## Layout and lifecycle

The five functions occupy `0x80067124..0x80067410`: pillar-sound forwarding,
update, destructor, constructor and factory, in that order. The factory
allocates `0x30` bytes and passes `tl_01` as the constructor's parent in `r4`.
The constructor forwards that parent to `TObject`, initializes the class name,
clears four child pointers, and initializes a signed 16-bit countdown at
`+0x2C`. Native construction supplies the vtable; no table is handwritten.

| Offset | Field | Evidence |
| --- | --- | --- |
| `+0x1C` | `floor_grass` | Result of the floor-grass factory |
| `+0x20` | `floor_stone` | Result of the floor-stone factory |
| `+0x24` | `pillar_controller` | Factory called with the controller as parent |
| `+0x28` | `pillar_demo` | Result of the pillar-demo factory |
| `+0x2C` | `sound_countdown` | Signed halfword load, decrement and store |

The destructor queues the children in reverse field order, clears each pointer,
then clears the singleton. The shared singleton declaration also replaces the
integer/byte-pointer views in the two neighboring consumer units; all six of
those consumers' functions remain exact. Child pointers retain the verified
`TObject` base interface rather than inventing more complete floor-object types.

The constructor checks the current floor's enemy-set state. An uncleared room
creates the grass, stone and pillar controller only outside split-screen mode;
the pillar demo is also created in split-screen mode. The child-null checks
remain even though the fields were initially cleared: intervening factory
calls are observable and may change the controller.

Update tests the countdown's old value before decrementing. When it is at most
zero it plays sound `0x40033215` and resets the countdown to
`(s16)(60.0f * ((1.0f / 32768.0f) * (f32)rand()) + 90.0f)`.
The original uses one multiply followed by a fused multiply-add. The existing
`fp_contract on` is retained; no new optimization setting is introduced.
The constructor's former floating arguments to `get_current_floor` were live
register artifacts: the callee takes no arguments, and the native call still
reproduces the original instructions and register allocation.

One external boundary remains provisional. The sound-forwarding function passes
its pillar-demo child to the entry currently named
`play_sound_once__19TObjBoss5PillarCtrlFv`. That entry tests and sets a word at
`+0x1C`. Its present class name does not prove a PillarCtrl/PillarDemo inheritance
relationship. The local ABI declaration retains a `TObject *` borrow and the
existing symbol rather than casting the child to an unrelated derived class.
Likewise the pillar-controller factory's legacy member spelling is retained at
an explicit parent-pointer ABI boundary. These helper ownership questions are
outside this controller unit.

## Data and compiler comparisons

The class-name string at `0x80438128` and its pointer at `0x805D2828`, singleton
at `0x805D4DE0`, and three countdown literals at `0x805D8F10..0x805D8F1C` now
belong to this unit. The string precedes the existing compiler-generated signed
conversion bias at `0x80438138`; the vtable remains at `0x80488778`.
These references, the contiguous code, and complete native emission support the
consolidation; they do not recover an original filename.

The first native C++ version matched all 748 code bytes. Defining the floats as
named constants in the same source then emitted duplicate pool entries:
`.sdata2` grew to 24 bytes, and the two countdown calculations' relocations
differed. Following [laser-light constants](laser-light-constant-pool.md) and
[conversion pools](conversion-pool-constants.md), ordinary literals emit the
original 12-byte pool in order (`90`, `60`, `1/32768`). A fresh census of all
configured original and compiled consumers permits the three float symbols to
be local. No post-processing or explicit conversion-bias definition is used.
A reduced C timer probe also matches all 156 bytes when given the same read-only
string/bias layout. The delivered lifecycle remains C++.

The name pointer, singleton and last float are four-byte objects. Their previous
eight-byte symbol extents included four zero padding bytes each. Only the actual
objects are assigned to the source unit; the three padding ranges remain in the
original fallback inventory. Overall data coverage does not decrease.

## Validation

Clean base and candidate builds use fresh split objects and generated configuration
with the pinned repository compiler/tool versions. Unchanged main passes retention
freshness. The candidate reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`; all five functions, six allocated
sections, and their relocation destinations match. The source-link checker
accepts the whole 748-code/68-data-byte object, including sizes and alignment.

`check_pr.py` passes with zero lost exact functions or linked address ranges:
matched and linked code remain 4,294,708 and 4,086,576 bytes; matched and linked
data increase from 1,489,000 / 1,477,844 to 1,489,036 / 1,477,880 bytes.
The two retired code fragments reduce linked source-unit count from 3,625 to
3,623 without losing any source-linked code. Retention adds only the native
constructor, name string and name pointer. Original-derived outputs and probe
files remain local.

All other active compiled objects are raw-identical to the clean baseline. The
346 source-tool tests, portable behavior suite, and AddressSanitizer/UBSan suite
pass. The generated port-exception inventory and changed-line whitespace checks
pass as well.
