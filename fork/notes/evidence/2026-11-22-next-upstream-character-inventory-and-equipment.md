# Recover native character growth, inventory, and equipment interfaces

The local review `great-merge/review/after-366/character-inventory-and-equipment` is at `50664446c4e459629362ea6aaedee37b460c4d8b` above the validated network stack `8b22ee1626c71f6eb8a72648aa40fd3eb577cb43`. Its ten commits touch 117 paths and use the configured fork author and committer. [Validation and component records](2026-11-22-upstream-366-inventory-review-validation.json)

## Proposed PR description

The character and inventory code now carries its own types from character initialization through equipment selection, loadout recovery, shop lists, and saved inventory.

- Character growth and companion initialization use the original level tables, motion inputs, and companion templates.
- Inventory sorting, export, placement and traversal keep the original allocation, stable order, and saved record layout.
- Equip and unequip share the original 12-byte packet layouts. Live actor stats and saved equipment use their actual records through combat, shops, and quests.
- The weapon, armor, Mag, and judgment lists use the selected player's inventory object and preserve the equipped-item and empty-list behavior.

The 43 linker labels follow the recovered native owners and signatures. The review build reproduces retail with 27,572 exact functions, 2,447 linked units, and all 1,147 original data bytes accounted for. The coverage check and runtime probes pass for growth, companion templates, inventory sort and export, item placement, equipment packets and effects, combat stats, and all four shop list paths.
