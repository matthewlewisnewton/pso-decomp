# Recover native actor models, battle parameters and camera interfaces

The 195-path standalone review is `1d9d60ce82b7307903fe4b0cdd72d2d7dd9d240e` on master `63ba63fe8b`. The combined inventory, saves and AVE-TCP preview is `d188731c39143af0e758673b68f8f760a96f4f67`. Saves, quests and assets still has the next review slot. [Actor motion validation](2026-11-23-native-actor-motion-validation.json)

The previous 177-path standalone review was `41db0911ec9636e49a8af652cd2b9221950c0cd8` on master `63ba63fe8b`. The inventory-and-saves preview is `77b449105051a32128d73765cafaee27719d38c6`. Saves, quests and assets still has the next review slot. [Camera reset and actor batch validation](2026-11-23-native-camera-reset-validation.json)

## Proposed PR description

### Summary

Recover the native records used by actor model lookup, battle parameter loading and shared boss and player interfaces. Keep the resources and action bindings already established by #375.

- Use typed model and texture entries in enemy archives and the NPC model registry. Pass native matrices through model capture, weapon drawing and player joints.
- Recover the active battle parameter bank and its actor stat bindings. Use typed rows in De Rol Le, Gal Gryphon and Saver.
- Share native arena, hit and curve records across the affected encounters and quest path opcodes.
- Recover the typed action- and motion-list setters and use the existing action record in 63 Gal Gryphon, Slime, Pan Arms and character-creation entries. Keep the #375 action selections and table addresses.
- Pass the native player to camera reset and the native optional vector to the fallback view. Preserve split-screen slot selection and camera pose updates.

### Validation

- GPOE8P matches retail DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3` in the standalone review and combined preview.
- The coverage check passes against master with 27,572 exact functions, 2,368 linked units and zero regressions.
- Targeted motion cases verify 63 action records, two Pan Arms table pointers, and both setters with pointer and null inputs.
- Targeted camera cases cover null and live follow targets, compact split-screen slots, boss and ordinary settings, and vertical and zero-direction fallback views.
- The source-quality benchmark removes 503 findings and adds five. All 39 changed function labels follow recovered owners or signatures, with zero flagged labels and zero newly stale retention entries.

### Remaining benchmark findings

- `vfunc_16` is the existing virtual contact slot used by the Mericarol bomb.
- `m_2f6` and `m_2fa` are established resistance fields. They replace byte offsets, and their effects still need evidence before renaming.
- `Hit_800C4A5C` is the local hit record shared by the Flower bomb factory and contact path.
- `node_matrix_array_base` is the existing callback-side declaration for the native model-capture buffer.

## Earlier candidates

The earlier 103-path model and battle review is `great-merge/review/after-376/actor-model-and-battle-parameters` at `323ae890a8`. Its inventory-and-saves preview is `419733d89a`. The model and NPC component now travels with the native battle parameter file and active bank, typed enemy and boss variants, stat reload and reset, and quest endian handoffs. The two existing offset-named resistance fields replace byte-pointer access in the standalone build. Their specific effects still need source evidence before naming them. The inventory preview already uses those fields. Both heads preserve #375’s resource selections and action bindings, match retail, and have zero flagged labels. [Current battle and contact validation](2026-11-23-native-battle-and-area-contact-validation.json)

The 61-path model-tree and NPC registry component started on master `63ba63fe8b` and the inventory-and-saves preview. Both candidates match retail and pass coverage. The same model, motion, texture and slot choices flow through the registry calls from #375. The source-quality benchmark removes 33 findings and adds zero, with zero flagged labels. The component is preserved at `great-merge/review/after-376/model-and-npc-resources` and forms the first commit of the model and battle review. [Model and NPC resource validation](2026-11-23-current-model-and-npc-resource-review-validation.json)

The earlier 339-path review is `great-merge/review/after-366/actors-bosses-and-enemies` at `6fef559bb1293e2d14ff158822b96779199a95d1` above the expanded window review `7e38bacd3a3be70b715037db837d5366763d4502`. It groups the five actor and battle commits with the enemy lifecycle, assets and combat commit. Its original actor build and combined network build match retail, with 217 linker labels from owner and signature fixes. Replaying it as a whole against the current queue reports 226 conflicts. [Earlier validation](2026-11-22-upstream-366-actor-and-network-review-validation.json) · [Enemy component details](2026-11-22-next-upstream-enemy-lifecycle-and-resources.md)

The original actor review is `great-merge/review/actor-battle-interfaces` at `5c9df48dbc73d4d930271b895172e983d42c1a70`. Its five commits follow the local window and chat candidate at `ebd31cec2b8fcffad5dfb01f5fbdeb54cf6c23a2`. The review changes 321 paths with 4,666 insertions and 4,445 deletions. Each commit has the configured fork attribution. [Window, character selection and chat candidate](2026-11-22-next-upstream-window-character-chat.md)

The motion API changes overlap seven Photon Blast actors. The candidate includes the typed Photon Blast resources so all seven callers use the native actions and motion entries. The only overlap after bringing in those actors was a header include. The candidate takes the matrix types and the already-present player declarations on the window base.

The 146 linker changes exactly equal the original address and label pairs in the component checks. The standalone build accounts for 980 linked bytes and 167 bytes of original alignment across 90 ranges.

- [Wall and ground contacts](2026-11-21-upstream-365-contact-validation.json)
- [Enemy and boss actors](2026-11-21-upstream-365-boss-and-enemy-validation.json)
- [Photon Blast](2026-11-21-upstream-365-photon-blast-validation.json)
- [Battle parameter loader](2026-11-22-upstream-365-battle-provider-validation.json)
- [Battle tables and actor motions](2026-11-22-upstream-365-battle-motion-validation.json)
- [Matrices and camera](2026-11-22-upstream-365-matrix-contracts-validation.json)
- [Tentacles](2026-11-22-upstream-365-encounter-contracts-validation.json)

| Evidence | SHA-256 |
| --- | --- |
| Build report | `deebd9038ae224b0aa0b77489e001d05759cc1fd21e5c863ad72b80ea1027506` |
| Coverage check | `08ad003eff3e6df0276b404f28031ba5adf9fd4e2cb6b5bbc4b46e477dc8d723` |
| Pan Arms and Canadin | `dcf2fa884db13431952535feef8783fc1d7c94a951c4e78151116cd8f9a1c2b5` |
| Battle data and actor motion | `d4b661b57234f37f08b21b5b06674ca8c0fe0d054e7b7848838eee052af66158` |
| Tunnel and arena | `7385f9bfd1602aa7250bc47f46e15b8b80f91d770be880a2231ed61d46c18c46` |
| Photon Blast | `d0fd64e03aef0d93b64597dd9ac7f49e43d8ac005efde3b75cb53564763dda3e` |
| Wall and ground contacts | `6be8cbdf2c03bbbcf1517cf8a27b63af287318ffc87cb515fac1d6aada307ca3` |
| Matrix and projection | `fd96296d833e998e23ef4b2c04bfd94318895afe2a604712b8d6fe7a5adb149c` |
| Tentacle constructors and attacks | `e3872e6e8e742290c0b4a720dfcdb86cbeebe85f22694e536956bd8327f990c7` |
