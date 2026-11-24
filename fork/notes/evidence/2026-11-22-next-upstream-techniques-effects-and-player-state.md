# Recover player combat, technique effects, and shared actor state

The 464-path local review `cd29476f2f` follows the validated world and resource batch `a72efc88aa`.

- Share the native cast packet and target records across player, NPC and enemy techniques. Carry the typed records through collision, particle emitters and effects.
- Use the original player hold, shrink, damage, and Photon Blast state. The two scale messages share the native client-ID header and retain their tested wire layout and byte order.
- Share the 12-byte enemy state record across set-table initialization, spawn dispatch, and game-state synchronization. Its byte-order method swaps the flags, drop ID, and damage and preserves the four status bytes.
- Pass the native `EnemyPlacement` stored in each live `EnemySetRecord` directly to its factory. Live row reads and Pan Arms child construction share that layout. The five spawn paths use `TObjEnemy::apply_enemy_state` at the original virtual slot. The factory reads the live row type during each table comparison, preserving the retail instruction sequence.
- Use the native model and matrix parameters in weapon animation, object breakup, and actor drawing. Preserve the typed sound and shared memory functions from earlier reviews.

The build matches retail DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3` with all 27,572 functions exact, 2,295 linked units and zero coverage loss. Focused checks cover technique distances and cleanup, collision, weapon animation, Photon Blasts and the scale messages. [Validation](2026-11-23-followups-on-latest-pr385-and-pr386.json)

The upstream source-quality checker removes 2,074 findings and adds 125 across 462 source paths, with zero newly stale retention entries. The placement and declaration follow-up drops 26 unused player-state prototypes and three obsolete status-effect declarations. The remaining source advisories cover legacy linkage and class labels, unresolved layout fields, and matching constraints in the touched routines. It removes 218 source-local virtual findings and adds zero. Seven label advisories follow corrected receivers or parameters on classes with existing address-based names. The class names stay as upstream defines them.

- `0x8002E62C` The breakup piece takes a read-only 3-by-4 matrix in its existing constructor.
- `0x800D80E4` The ground spot constructor takes a read-only position and the native Ninja texture list.
- `0x803375F0` Ground snapping belongs to the projectile spawned by Morfos and accepts its `Vec`.
- `0x80337824` The projectile constructor takes a read-only `Vec` and accepts its owner as `TObjChara *`.
- `0x8035A69C` The node recording task owns the draw callback and receives a native Ninja object.
- `0x8035A740` The node task owns the visibility-checked draw callback.
- `0x8035A860` The node task constructor receives a native Ninja object.

The review retains scoped CodeWarrior settings for the following routines. The retail match covers these settings.

- Dragon hierarchy cloning, CSN wall query preparation, debris construction and player ground adjustment retain scoped scheduling settings.
- The Gibbles attack loops retain their loop-invariant settings.
- Photon Blast registration retains floating-point contraction.
- Barta, Gi-Barta and Megid dispatch, and two weapon idle callbacks retain the scoped inline settings.
