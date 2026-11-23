# Recover native techniques, effects, and player state

The local combined review `great-merge/review/after-376/techniques-effects-and-player-state` is at `ac527c58211903ee21810aac6b0a97f839554b1b`. It touches 521 paths above the validated window, inventory, saves, actor and AVE-TCP queue. Both the retail and coverage checks pass. [Validation](2026-11-23-combined-combat-and-actor-validation.json)

## Goals for the combined batch

- Carry the native cast packet, target records, and elemental effect parameters through the player, NPC and enemy technique callers.
- Give player actions native hold, grab, shrink, damage, Photon Blast and collision state. Share those declarations with traps, bosses, movement and network packet writers.
- Type weapon animation, borrowed BML motion, actor node state, and Ginja texture and matrix arguments at their callers. Preserve the common release and one-shot sound entry points for their own subsystem reviews.

The merged #375 tree is an ancestor. The 209 shared paths include the Photon Blast registry and Ginja model and texture callers. For example, the De Rol Le tentacle’s texture list now crosses the model boundary as its native pointer, without casting away its type.

## Source quality

The benchmark removes 1,873 findings and adds 65, with zero newly stale retention entries. Seven label advisories follow actual receivers or parameter types on classes whose existing names still encode addresses.

- `0x8002E62C` The breakup piece receives a read-only 3-by-4 matrix through its real constructor parameter.
- `0x800D80E4` The ground spot constructor takes a read-only position and the native Ginja texture list.
- `0x803375F0` Ground snapping belongs to the typed Morfos appendage object and accepts a Vec.
- `0x80337824` The same appendage constructor takes a read-only Vec and its base character owner.
- `0x8035A69C` The node recording task owns the draw callback and receives a native Ninja object.
- `0x8035A740` The node task owns the visibility-checked draw callback.
- `0x8035A860` The node task constructor receives a native Ninja object.

## Earlier technique review

The local review `great-merge/review/after-367/techniques-effects-and-player-state` is at `a27e2abd333929138af541047de7983200e679ac` above the validated saves, quests and assets review `6077e29d1cedfbbba0565de112f08aa67bbe6270`. Its commit touches 109 paths and reproduces the validated cumulative source tree. [Validation and component records](2026-11-22-upstream-367-techniques-and-player-state-validation.json)

## Proposed PR description

Recover the C++ types shared by player technique casting, NPC and enemy casts, particle and resource handling, and the player state packets that carry the corresponding changes.

- Player and NPC techniques share the original 6x47 cast packet and target records. Gi-Barta, Zonde and Rafoie use their actual effect and emitter receivers.
- Critical-hit and ring-wave drawing share the native texture frame and Ginja lists. The critical-hit factory takes a position directly and keeps the particle and fade timing.
- Hold, release, shrink and scale callers use the native player state and packet records. Enemy, trap, NPC and quest callers share those declarations.
- Technique charge lights use the native light constructor and the original color and direction records.

The 38 changed linker labels follow native owners or signatures. The build matches retail with all 27,572 functions exact, 2,417 units linked and all 1,147 original data bytes accounted for. Runtime probes cover casts, effects, hold and scale packets, and critical-hit allocation, particles and drawing.
