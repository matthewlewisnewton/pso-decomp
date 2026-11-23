# Recover player combat, technique effects, and shared actor state

The 463-path review `3101817acc4c8b0e430a78822de084988283c924` is based on the validated world objects and resource-lifetime review `c3b0000bea8218676b3e1667eeb19bbda8174f19`. Upstream PR #375 is already in its history.

- Share the native cast packet and target records across player, NPC and enemy techniques. Carry the typed records through collision, particle emitters and effects.
- Use the original player hold, shrink, damage, and Photon Blast state. The two scale messages share the native client-ID header and retain their tested wire layout and byte order.
- Use the native model and matrix parameters in weapon animation, object breakup, and actor drawing. Preserve the typed sound and shared memory functions from earlier reviews.

The build matches retail DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3` with all 27,572 functions exact, 2,368 linked units and zero coverage loss. Focused checks cover technique distances and cleanup, collision, weapon animation, Photon Blasts and the scale messages. [Validation](2026-11-23-post-world-combat-review-validation.json)

Upstream’s benchmark removes 1,802 findings and adds 65, with zero newly stale retention entries. Seven label advisories follow corrected receivers or parameters on classes with existing address-based names.

- `0x8002E62C` The breakup piece takes a read-only 3-by-4 matrix in its existing constructor.
- `0x800D80E4` The ground spot constructor takes a read-only position and the native Ginja texture list.
- `0x803375F0` Ground snapping belongs to the Morfos appendage object and accepts its Vec.
- `0x80337824` The appendage constructor takes a read-only Vec and its base character owner.
- `0x8035A69C` The node recording task owns the draw callback and receives a native Ninja object.
- `0x8035A740` The node task owns the visibility-checked draw callback.
- `0x8035A860` The node task constructor receives a native Ninja object.

The review retains scoped CodeWarrior settings for the following routines. The retail match covers these settings.

- Dragon hierarchy cloning, CSN wall query preparation, debris construction and player ground adjustment retain scoped scheduling settings.
- The Gibbles attack loops retain their loop-invariant settings.
- Photon Blast registration retains floating-point contraction.
- Barta, Gi-Barta and Megid dispatch, and two weapon idle callbacks retain the scoped inline settings.
