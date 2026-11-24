# Recover native enemy lifecycle, assets, and combat interfaces

This component is included in the 339-file actor and boss review at `6fef559bb1`. [Combined review](2026-11-22-next-upstream-actor-battle-interfaces.md) · [Current validation](2026-11-22-upstream-366-actor-and-network-review-validation.json)

The earlier component review is `great-merge/review/after-366/enemy-lifecycle-and-resources` at `5db0dc93ed1e80eda57825a1852dbce705f0c648` on the queued actor branch `688f231369208dfde04906467b470ea4606ea5ac`. It changes 66 files with 2,419 insertions and 3,287 deletions. The source combines nine matched parts of the cumulative replay. [Validation and component records](2026-11-22-upstream-366-reconciliation.json)

## Proposed PR description

This recovers the C++ methods and types that own enemy lifecycle, resource loading, and combat. Start with the Gibbles and Gyaranzo construction and destruction paths, then follow the floor registration and state dispatch into the enemy-specific methods.

- Gibbles and Gyaranzo use native constructors, destructors, and battle methods. Gyaranzo emits the original 83-entry virtual table. Fly Nest reads its children through the original entity lookup.
- Morfos passes typed model-node positions to its arm and projectile factories. The Epsilon body creates and positions its guards, and the shared archive, breakup models, and polygon streams use their native types.
- Pan Arms owns its ground checks, warp and detour methods, and split-body contact handling. The attack collider takes the real direct-hit receiver and shares the knockback methods.
- Canadin, Gee, and Gi Gue use the native formation, sound, and effect records. The fade classes own their methods, and Flower dispatches its callback through the original receiver.
- Shinowa, Sinow Zoa, and Stelth load and restore native Ginja texture entries. Sinow Zoa owns its factory and movement handlers. Ill Gill's shadow receives the task parent and target through its native base types.

The 71 changed linker labels correspond to the owner and signature changes in the nine component validations. The review uses the queued actor branch's existing one-shot sound, player-effect, and position helper declarations where the cumulative replay already has newer shared types.

## Validation

- GPOE8P reproduces retail DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- All 27,572 functions match exactly and all 2,447 source units link. The coverage comparison reports zero code, data, or linkage losses and accounts for all 1,147 historical data bytes.
- Runtime probes cover Gyaranzo and Fly Nest construction and status, enemy lifecycle, actor fading, Pan Arms movement and contacts, Epsilon archive release, Sinow archive selection and texture copies, and Ill Gill shadow inputs.
