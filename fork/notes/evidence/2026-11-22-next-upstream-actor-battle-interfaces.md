# Recover native actors, boss encounters, and battle interfaces

The current 103-path model and battle review is `great-merge/review/after-376/actor-model-and-battle-parameters` at `323ae890a8`. Its inventory-and-saves preview is `419733d89a`. The model and NPC component now travels with the native battle parameter file and active bank, typed enemy and boss variants, stat reload and reset, and quest endian handoffs. The two existing offset-named resistance fields replace byte-pointer access in the standalone build. Their specific effects still need source evidence before naming them. The inventory preview already uses those fields. Both heads preserve #375’s resource selections and action bindings, match retail, and have zero flagged labels. [Current battle and contact validation](2026-11-23-native-battle-and-area-contact-validation.json)

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

The combined review stays local behind the window and chat candidate in the review queue.

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

## Proposed PR description

### Summary

Recover native C++ ownership and types across shared actor movement and boss and enemy motion. The patch brings the actor classes and the callers of their shared interfaces together.

- Wall and ground movement pass native contacts and destination records through the enemy, boss, and player paths.
- Enemy and boss actors use their native fields and lifecycle methods, including Pan Arms parts, Canadin membership, and the De Rol Le and Barba Ray tentacles.
- The lobby loads typed battle tables. Enemy stats, shared actor animation, and Photon Blast summons use their actual parameter and motion records.
- Matrix copy, concatenation, and camera projection take pointers to the data they read. Both tentacles borrow the matrices allocated by their enclosing boss, and Barba Ray passes a typed attack position.

- Gibbles and Gyaranzo use native lifecycle and battle methods. Pan Arms uses its native ground, movement, and contact methods. Morfos, Epsilon, the Sinow variants and Ill Gill use typed asset, factory, and state interfaces.

The commit sequence starts with actor owners and movement, then follows the resource, battle data, camera, and encounter callers. The linker label changes follow recovered native methods, constructors, or argument types.

### Validation

- GPOE8P reproduces retail DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- `tools/check_pr.py` passes against the window and chat base with 27,572 exact functions, 2,447 linked units, and zero code or data coverage losses.
- Runtime probes cover wall and ground contacts, Pan Arms and Canadin ownership, Photon Blast summons, battle-file loading and table access, matrix and camera arguments, and both tentacle layouts and attack requests.
