# Recover actor positions, population and encounter setup

The local review `great-merge/review/after-367/actor-positions-and-population` is at `93772a11ffb81be3ee592432feac3a4fe70c2c66` above the Olga Flow replay. Its two commits cover 56 paths. [Validation](2026-11-22-upstream-367-actor-positions-and-population-validation.json)

## Proposed PR description

Use the shared character layout to copy actor centers across bosses, enemies, NPCs, and the player. Pass filenames and resource pointers through the typed REL loader and preserve the native NPC model and texture lifetimes.

Recover the Flower bomb's typed movement, floor contact, attack state and particle effect. Its owner keeps the current action handlers and reads the technique level from the battle movement record. The Shark action, movement and collision tables each use their own range in the linker map.

The retail build matches byte for byte with 27,572 exact functions, 2,417 linked source units, and all 1,147 starting data bytes accounted for. Runtime probes cover 56 NPC archive lifecycle cases, actor position copies, Shark subtype and resource setup, Flower melee and bomb setup, Recobox parameters, and movement and flight factories.
