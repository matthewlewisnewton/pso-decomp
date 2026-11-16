# Creation-menu icon animation interfaces

Base: fork main `8d032356158714045be28c034286f4c6e846a843`.
Unit `pso/object/TObjCMIcon_80299488.cpp` already matched and linked: eight
functions, 1,268 code bytes and 108 data bytes. This change recovers typed
interfaces throughout that unit and preserves its coverage; it claims no new
matched functions or linked bytes.

## State, groups and callbacks

The reset loop at `80299488` and initializer at `8029951C` walk seven 12-byte
`CreationIconState` records. The copy at `8029957C` transfers a word at +0 and
floats at +4/+8, matching `hidden`, `fade` and `x`. Shared size and offset
assertions describe those accesses.

Render (`802995A0`) and task update (`802997DC`) both pass their incoming
receiver to `80299598`. They are now native `TObjCMIcon` members. The small
identity helper retains its existing C entry label and a typed icon receiver;
its unused receiver alone does not establish its original member declaration.
The visibility and copy helpers likewise retain their existing entry labels.

The render loop indexes the group table with a 20-byte stride. Update advances
the same table by 20 bytes. Both read the count at +0 and sprite IDs at +4.
`CreationIconGroup[7]` now describes the table in its provider and consumers,
replacing a flat 35-word definition and two distinct local structure views.
The provider uses the shared class declaration instead of a duplicate class.

Rendering sorts squared fades in ascending order, preserving equal-key order,
and passes each squared fade as sprite alpha. Its depth calculation retains
the original integer division by seven. Task update preserves the existing
fade clamps, hidden-icon movement, fused interpolation and scroll easing.

## Compile, compare and research

The initial typed experiment used whole-record assignment. With the existing
GC/2.6 `-inline off` configuration this emitted an extra assignment operator
and a call instead of the original seven-instruction copy. Explicit field
assignments removed that call, but a `const` source still hoisted loads and
changed float registers. The mutable typed source preserves all three
load/store pairs. This is the same constraint documented for `copy_tech_params`
in [cast-technique register allocation](cast-technique-6x47-register-allocation.md).
No new compiler control is needed.

Calling the shared `s16 get_creation_sprite_id` declaration initially added
`extsh` to both callbacks. The provider at `80290DEC` already returns a signed
halfword through `lhax r3`; all known callers consume a full signed register.
Its shared declaration and definition now return `s32`, still loading signed
16-bit storage. The other two source callers use this same declaration.
The [status-gauge investigation](status-gauge-native-evidence.md) records the
same caller-side extension problem. The inherited function name is retained;
this change does not establish its original name.

Including the new icon helper header before `TObjCMName`'s existing
`TOBJECT_OUT_OF_LINE_HELPERS` definition emitted an extra weak helper. The full
link check caught the repeated-text size discrepancy despite exact function
scores. The include now follows that definition, preserving its established
helper-emission behavior.

## Validation

All eight functions and all five allocated sections in the chosen unit are
exact. Its allocated section bytes, sizes, alignments and 55 normalized
relocation records equal both the baseline source object and fresh original
split. The group provider's allocated bytes and 12 relocation targets equal
the baseline; its original split includes the same four trailing zero padding
bytes that the linker recreates after its 172-byte compiled data section.

All twelve rebuilt consumer/provider units retain 100% code and data matching.
The generated link inputs continue to select compiled source. A full rebuild
retains DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
Address-based regression checks, all 3,619 linked-unit checks and the unchanged
19,818-entry retention check pass. The 347 synthetic tool tests and existing
portable behavior and ASan/UBSan suites pass. No split, symbol, link-selection,
retention or compiler-profile metadata changes are required.
