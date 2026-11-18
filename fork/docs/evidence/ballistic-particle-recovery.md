# Ballistic particle update and complete unit linkage

Initial recovery base: fork main `f8a71fae8a52f0bde1b956af4519061fe306cb30`.
Final validation base: fork main `0a85a72c1c09598512363e6d375616ebd1d1b63e`.
The existing `pso/misc/ParticleBallistic.cpp` boundary is unchanged:
`.text` `0x8008877C..0x80089F7C`, `.rodata` `0x804394E8..0x80439530`,
and `.sdata2` `0x805D94F8..0x805D9528`. All eight functions, 6,144 code
bytes and 120 data bytes match. The missing update at `0x800888E8` accounts
for 2,060 newly matched code bytes.

## Recovered behavior and interfaces

`TUnk_8048E778::run_task` advances the particle's local step or returns it to
its origin after half its life, transforms the step in either XYZ or ZXY
order, applies a randomized ground bounce, horizontal damping and gravity,
then updates scale, age, colour, spin and sprite frames. Additive sprites
fade RGB; other sprites fade alpha. It optionally follows the target's
virtual center, optionally offsets that point toward the camera, advances
motion and calls the existing retirement method. The null-target path queues
destruction and returns before motion advancement. A null center only skips
the attachment update. The spin magnitude check replaces either sign with
positive 20 when its absolute value exceeds 20, as in the original.

The derived tail now declares a float motion-frame step at `+0xC0` and the
rotated movement vector at `+0xC4`, with size/offset guards preserving the
0xD0 allocation. The shared particle parameter, quad-sprite and definition
types are the ones already used by the radial recovery. The sprite table
keeps its owner's `void *[0x6C]` declaration; its entries use the existing
quad-sprite base's `void *m_28` definition boundary. Entity lookup and the
center virtual use the existing shared actor interface. Destruction uses
TObject's supported out-of-line declaration. Shared matrix, math and motion
render declarations replace conflicting local prototypes where touched.

The original class name remains unknown, so `TUnk_8048E778` is retained.
Existing constructor/destructor storage views, explicit legacy vptr writes
and other renderer interfaces remain bounded legacy recovery, as in the
radial unit. This change does not establish original C++ constructor spelling
or recover the entire particle API. No vtable or assembly is added.

## Compile, compare, research, revise

The first implementation was derived from the original update's assembly
and compiled with ordinary GC/2.6 unit settings. It scored 93.33787%, emitting
2,084 rather than 2,060 bytes. The movement, bounce, spin, attachment and
motion sequences already agreed; colour control flow and FPR allocation
accounted for the substantive differences.

The next investigation used [radial particle evidence](radial-particle-update.md)
and its merged implementation. Its additive helper returns zero directly for
a negative channel, and otherwise multiplies opacity by the upper-clamped
channel. Multiplying opacity by the result of a separate full clamp had
produced different branches. Grouping the meaningful age/opacity pair and
RGB triple in arrays reproduced the native floating-point allocation.
Together these changes produced 2,060 bytes at 99.64078%; the remaining
mismatches were constant relocations. Defining the owned constants and using
native literals made the update 100% exact. The grouping is a matching source
arrangement, not proof of the original local declarations.

Completing data required further object-level comparisons:

| Attempt | Observation |
|---|---|
| Define the four renderer initializers before functions with normal pooling | Correct 72-byte `.rodata`, but shared-base addressing changes the renderer to 1,412 bytes / 94.68715%. Both static and external const definitions show this. |
| Declare early, define after the functions | Restores the renderer's instructions, but the conversion pool precedes the initializers; `.rodata` order fails. |
| Define early and scope `pool_data off` to the renderer | All 1,432 renderer bytes and original independent addresses match; the other seven functions remain exact. Existing `TOKurage` and `TOKeyAncient01` unit profiles document the same independent-address pattern. |
| Use a scalar `360.0f` literal | Emits only 44 of the owned 48 small-data bytes. |
| Preserve `lbl_805D9520` as the original eight-byte object with small-data placement | All 48 bytes match, including the trailing zero. This follows the same object shape documented in the orbit recovery, without changing the split. |

The two integer-conversion biases arise naturally from casts; none is
hand-written. [Conversion-pool evidence](conversion-pool-constants.md)
explains why explicit duplicate bias definitions would be wrong.

## Compiler and port constraints

The update's scoped `fp_contract on` preserves the original fused bounce
impulse and twelve fused colour interpolations. Existing constructor scopes
are retained. Ports requiring the native single rounding should use `fmaf`
for those expressions. The renderer's scoped `pool_data off` only controls
address formation and can be removed in a port. The explicit `.sdata2`
annotation on the two-float angular-range object is guarded for MWCC.

Colour is assembled by writing the representation of a live `u32` through
`u8 *`, rather than reading an inactive union member. GameCube byte order
makes it `0xAARRGGBB`. A little-endian port must pack the converted channels
with shifts. These constraints are in the [porting register](../porting-exceptions.md).
Fifteen redundant copies of the existing inline-pragma trio and unused emitter
macros were removed without changing compilation behavior.

## Link admission and verification

The original unit does not own `TParticleCtrl::clear_active_flag` at
`0x80088000`; its redundant definition was removed here while preserving the
owning boss/particle-base unit. The localizer inspected the fresh active split
and compiled consumer inventory and found no external references to the
seventeen pool/initializer symbols made local. The angular-range object keeps
its global symbol. The scanner adds only this unit and four retention names:
its two constructors, retirement method and angular-range object.

The unchanged-main baseline passed the retention check before editing.
Native builds use the pinned project toolchain, original inputs and freshly
generated split metadata. The full linked build and `check_pr.py --no-build`
check original DOL identity, address-based no-loss, unit linkability and
retention consistency. No split, report accounting or validation gate changes.

The five other class-header consumers were separately recompiled using the
baseline header and compared with candidate objects. Complete ELFs are
byte-identical for `TParticleCtrl`, `ParticleRadial`, `ParticleOrbit`,
`TParticleCtrl_80085EE4` and `TBoss4Type2_800874F4`.

Final linked DOL SHA-1 is `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
`check_pr.py --no-build` passes with zero regressions, 3,602 exact linked
units and no retention drift. The final linker edge selects the compiled
`src/pso/misc/ParticleBallistic.o` exactly once and no original fallback for
this unit. All 306 source-tool tests, Python syntax, exception inventory and
changed-line whitespace checks pass. The current portable behavior and
ASan/UBSan suites also pass. This is binary/build validation, not a
runtime gameplay test or an independent source review.
