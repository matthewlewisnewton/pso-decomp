# Recover native character growth, inventory, and equipment interfaces

Upstream PR #377 is open at `39848c3108` on master `e39eb9e138`. The 106-path review uses native inventory, placement, equipment and item-drop records. It preserves the shared unequip entry points and leaves equipment effects to PR #375. Eight runtime suites and the standalone and combined #375 retail and coverage checks pass. GitHub matching passed. The source-quality benchmark removes 1,123 findings and adds 102, with zero flagged labels or newly stale retention entries. [PR #377](https://github.com/zeroz41/pso-decomp/pull/377) · [Validation](2026-11-22-upstream-377-inventory-validation.json)

## Earlier fork replay

The local review `great-merge/review/after-367/character-inventory-and-equipment` is at `61a66013a179485ff5923b6248c8b2b2d4b6de60` above the validated enemy-spawn checkpoint `25d14badb4e43f13105492b4eec959ffa05e4349`. Its three commits touch 110 paths and use the configured fork author and committer. [Validation and component records](2026-11-22-upstream-367-inventory-actor-stats-validation.json)

## Proposed PR description

The character and inventory code now carries its own types from character initialization through equipment selection, loadout recovery, shop lists, and saved inventory.

- Character growth and companion initialization use the original level tables, motion inputs, and companion templates.
- Inventory sorting, export, placement and traversal keep the original allocation, stable order, and saved record layout.
- Equip and unequip share the original 12-byte packet layouts. Live actor stats and saved equipment use their actual records through combat, shops, and quests.
- The weapon, armor, Mag, and judgment lists use the selected player's inventory object and preserve the equipped-item and empty-list behavior.

The 43 linker labels follow the recovered native owners and signatures. The review build reproduces retail with 27,572 exact functions, 2,417 linked units, and all 1,147 original data bytes accounted for. The coverage check and runtime probes pass for growth, companion templates, inventory sort and export, item placement, equipment packets and effects, combat stats, and all four shop list paths.
