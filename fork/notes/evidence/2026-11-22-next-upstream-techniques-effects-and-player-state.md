# Recover native techniques, effects, and player state

The local review `great-merge/review/after-367/techniques-effects-and-player-state` is at `a27e2abd333929138af541047de7983200e679ac` above the validated saves, quests and assets review `6077e29d1cedfbbba0565de112f08aa67bbe6270`. Its commit touches 109 paths and reproduces the validated cumulative source tree. [Validation and component records](2026-11-22-upstream-367-techniques-and-player-state-validation.json)

## Proposed PR description

Recover the C++ types shared by player technique casting, NPC and enemy casts, particle and resource handling, and the player state packets that carry the corresponding changes.

- Player and NPC techniques share the original 6x47 cast packet and target records. Gi-Barta, Zonde and Rafoie use their actual effect and emitter receivers.
- Critical-hit and ring-wave drawing share the native texture frame and Ginja lists. The critical-hit factory takes a position directly and keeps the particle and fade timing.
- Hold, release, shrink and scale callers use the native player state and packet records. Enemy, trap, NPC and quest callers share those declarations.
- Technique charge lights use the native light constructor and the original color and direction records.

The 38 changed linker labels follow native owners or signatures. The build matches retail with all 27,572 functions exact, 2,417 units linked and all 1,147 original data bytes accounted for. Runtime probes cover casts, effects, hold and scale packets, and critical-hit allocation, particles and drawing.
