# Recover native save, quest, and asset-loading interfaces

The local review `great-merge/review/after-366/saves-quests-and-asset-loading` is at `773c658eccd69066f6592db2bc4cfc6add2fbb02` above the technique review `a5d9b6d32225e338cfe71cdcff5184520c9667cd`. Its five commits touch 172 paths. [Validation and component records](2026-11-22-upstream-366-saves-quests-and-assets-validation.json)

## Proposed PR description

Recover the types used to load save data, quest entries, and assets, and carry those declarations through their existing callers.

- Memory-card selection and preflight use the original slot, load-result, and file records.
- The Hunter Guild uses typed quest callbacks and download windows. The cache passes the signed handle and native ARAM request through reads and completion, using the original records and buffers.
- Shared file requests keep their callback, completion pointer, and list links through cancellation and release. Texture and model callers pass the native GVM and BML records.
- The footprint effect uses a typed texture pointer from load through drawing and release, and reads yaw from the player's rotation record.

The 22 changed linker labels follow the typed owners and signatures. The build matches retail with all 27,572 functions exact, 2,447 units linked and all 1,147 original data bytes accounted for. The runtime probes cover memory-card polling and metadata, quest menus and cache eviction, ARAM read boundaries, file requests, texture binding, archive callbacks, and footprint rendering and release.
