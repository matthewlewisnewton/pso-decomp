# Native status-gauge interfaces

`pso/misc/TWindowSubStatusDisp_8026F6DC.cpp` contains fifteen already-matching
functions (3,640 code bytes) and sixteen bytes of compiler conversion constants.
This change replaces reconstructed call shells and register-residue calls with
native interfaces and explicit arguments, then selects the complete unit for
source linkage. It does not claim new matched functions or complete recovery
of the surrounding window hierarchy.

## Gauge and player interfaces

Entries 3 and 4 returned by the window's existing array accessor are gauge
entries. The shared `TUnk_804CF930` layout places `maximum` at 0x20 and `target`
at 0x24. Its native `calc_bar_width()` slot matches the original indirect call
through vtable 0x804CF930 at offset 0x14. The initialization and gauge updates
now use those fields and the existing native accessor.

The three player virtual-call shells are replaced by shared declarations.
The original player table selects `get_name()` at 0x30,
`get_actor_level_index()` at 0x40, and `has_flag_0x800()` at 0x84. Native calls
preserve those slots and all instructions. Player lookup and photon-blast
charge calls now receive their actual inputs explicitly. The chain lookup
receives both its output record and incoming client ID, matching its provider
at 0x801AA17C, which fills two four-element arrays.

The TP read remains signed as in the original `lha`. Its view through the
corresponding signed-short type is permitted for unsigned-short storage;
`static_cast<s16>(player->tp)` instead emits an extra load/sign-extension
sequence with the configured compiler. Existing HP maximum helper names are
retained as bounded C ABI entry labels: the original helper reads the player
prefix at 0x2B8, rather than an item receiver. No item-class receiver cast is
needed here.

## Marker and bounded legacy interfaces

`update_photon_blast_player_marker` takes an entry pointer and a full-register
client ID and returns void. Neither original caller consumes a result. The
old inferred integer return fell through without a value; the shared header
and caller now describe the observed contract. Forwarding the incoming client
argument directly to the chain lookup preserves the original allocation.

Some original window ownership remains provisional. In particular, the
32-bit word write at offset 0x60 is retained explicitly instead of assigning
it to guessed members in the shared window hierarchy. Other existing opaque
window/renderer boundaries remain bounded and unchanged.

The inherited `get_width__19TWindowSimpleStatusFv` label reads a signed
halfword at window offset 0x20. This unit consumes its canonical signed result
as a full-register client ID and passes its receiver explicitly. The local C
ABI declaration retains that full-register result; declaring it `s16` emits
extra caller-side `extsh` instructions in six functions under GC/2.6. This
observation does not establish that the inherited method name or receiver
ownership is the original source interface.

## Source linkage

The two conversion constants at 0x8044F608 and 0x8044F610 are emitted
anonymously by the compiler. `localize_split_globals.py` checks every original
and compiled unit for outside references before marking only these split
labels local. Their sixteen bytes, placement, alignment, and relocations stay
unchanged. No hand-written data tables, game assets, unit-boundary changes,
or compiler/profile changes are needed.

Validation compares all fifteen functions, allocated sections, and physical
relocation targets with the original and validated main-source objects. Both
header consumers are checked, including the caller whose entry argument
changes from integer transport to a pointer. Final validation must preserve
all original addresses and total code/data coverage, pass linked-unit checks,
confirm the actual ordered linker inputs select this compiled object, and
retain DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
