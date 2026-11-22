# Recover native techniques, effects, and player state

The local review `great-merge/review/after-366/techniques-effects-and-player-state` is at `a5d9b6d32225e338cfe71cdcff5184520c9667cd` above the inventory review `50664446c4e459629362ea6aaedee37b460c4d8b`. Its seven commits touch 118 paths. [Validation and component records](2026-11-22-upstream-366-technique-review-validation.json)

## Proposed PR description

Recover the C++ types shared by player technique casting, NPC and enemy casts, particle and resource handling, and the player state packets that carry the corresponding changes.

- Player and NPC techniques share the original 6x47 cast packet and target records. Gi-Barta, Zonde and Rafoie use their actual effect and emitter receivers.
- Critical-hit and ring-wave drawing share the native texture frame and Ginja lists. The critical-hit factory takes a position directly and keeps the particle and fade timing.
- Hold, release, shrink and scale callers use the native player state and packet records. Enemy, trap, NPC and quest callers share those declarations.
- Fog and related scene effects pass their actual resource and draw records.

The 40 changed linker labels follow native owners or signatures. The build matches retail with all 27,572 functions exact, 2,447 units linked and all 1,147 original data bytes accounted for. Runtime probes cover casts, effects, hold and scale packets, and critical-hit allocation, particles and drawing.
