# Camera unit at 8006BA68

Initially validated against fork main `4b40cbeb93`, then rebased and revalidated
against `9efb3e1574` on 2026-11-12 with the configured GC/2.6 compiler.
The existing text range is 8006BA68–8006BCD8 (eight functions, 624 bytes).
It was already matched and source-linked; this recovery preserves those matches and
adds the native 48-byte vtable at 80488B38–80488B68 to source-owned data.

The entry at 8006BA68 calls the TUnk_80488A28 constructor, installs the vtable
at 80488B08, sets the inherited field at +38 to 4, and clears the fixed-NPC-camera
flag. It is now the native TUnk_80488B08 constructor. Its allocation caller at
8006B91C uses `new TUnk_80488B08()`. The class names remain address placeholders;
this establishes constructor/vtable ownership, not a historical semantic class name.

The orbit controller at 8006BB1C reads controller-input offsets +70, +84 and +86:
these are `controllers[1].buttons`, `stick_x` and `stick_y` in the shared input
layout. The second context is intentional. It changes the float at object +6C
by 2.2, clamps it to 10–300, then uses it as the radius in the position calculation.
Object +30 is a signed angle accumulator, updated by three times stick X; the
existing +2C accumulator receives stick Y. Typed members replace the unrelated
whole-object overlay. Field offset and class-size assertions preserve the layout.
The existing floating-point contraction setting is retained.

The accessors at 8006BAB4 and 8006BAC8 return vectors at +104 and +D4 with a
12-byte index stride. Their shared declaration now uses a signed integer index
and a vector pointer result, replacing the caller's pointer-typed index and
integer-typed result. CameraViewVectors is a bounded provisional view of these
banks; it does not establish the surrounding TCameraCtrl layout or validate indices.

The initial native destructor compiled to identical instructions but emitted an
additional `.data` section. Following the complete-object checks in
[compiler emission evidence](compiler-emission-evidence.md) and the extra-section
rules in `tools/link_units.py`, the split now owns the compiler-generated vtable.
Its ten function-pointer relocations and all 48 bytes match the original table;
no table is written by hand. Definition order remains ascending and no compiler
override is added. Regenerating retention from fresh splits adds only the vtable,
its destructor and its run_task entry, with no removals.

Final unit coverage is 8/8 functions, 624/624 code bytes and 60/60 data bytes
(48 vtable plus 12 constants), all source-linked. `tools/check_pr.py` passes
against the unchanged-main baseline: +48 matched and linked data bytes, zero
function/code/link regressions, and all 3,625 linked units remain exact. The full
DOL reproduces SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
