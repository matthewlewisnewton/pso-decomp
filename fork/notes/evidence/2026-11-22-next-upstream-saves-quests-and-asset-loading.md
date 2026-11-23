# Recover native save, quest, and asset-loading interfaces

The current standalone review is `991ae618f9a8ec08e906a809280386438f6946b1` on upstream master `63ba63fe8b`. The same code matches in the inventory preview `fbd1e87d5b` and with AVE-TCP #378 in `259ed12ee1`. [Exact-head validation](2026-11-23-saves-quest-asset-review-preflight.json)

The 179-path independent review `e2d6876245` is based directly on upstream master `e39eb9e138`. It retains the existing nullable release interface where the shared memory work is still queued. The recovered length methods and text builders share the native QuestDownloadRequest type, and BML entry traversal uses the archive header. The retail build, coverage gate and nine runtime suites pass. The benchmark removes 729 findings and adds 24, with zero flagged labels and zero newly stale retention entries. The separate review `02d6f9de87` on the validated #375/#377 preview keeps the existing texlist member, typed NPC records and relocated particle owner. It matches retail and passes coverage with 706 fewer findings and zero flagged labels. [Validation](2026-11-22-independent-save-quest-asset-validation.json)

The current local review is `e0d6a26efd` on `14951bf3bf`. The 179-path batch matches retail, retains coverage, and passes nine runtime suites. It preserves the existing typed BML callback parameters and uses the recovered name and symbol lookup fields. The two remaining label advisories follow the decoded length methods onto the existing address-named request record. [Current validation](2026-11-22-upstream-371-saves-quests-and-assets-validation.json)

The local review `great-merge/review/after-367/saves-quests-and-asset-loading` is at `6077e29d1cedfbbba0565de112f08aa67bbe6270` above the inventory review `61a66013a179485ff5923b6248c8b2b2d4b6de60`. Its two commits touch 174 paths and reproduce the validated cumulative source tree. [Validation and component records](2026-11-22-upstream-367-saves-quests-and-assets-validation.json)

## Proposed PR description

Recover the types used to load save data, quest entries, and assets, and carry those declarations through their existing callers.

- Memory-card selection and preflight use the original slot, load-result, and file records.
- The Hunter Guild uses typed quest callbacks and download windows. The cache passes the signed handle and native ARAM request through reads and completion, using the original records and buffers.
- Shared file requests keep their callback, completion pointer, and list links through cancellation and release. Texture and model callers pass the native GVM and BML records.
- The footprint effect uses a typed texture pointer from load through drawing and release, and reads yaw from the player's rotation record.

The 35 changed linker labels follow the recovered owners and argument types. The retail DOL matches byte for byte with all 27,572 functions exact, 2,368 linked units and all 1,147 original data bytes accounted for. The targeted checks cover card metadata, quest ARAM completion and timeouts, compressed and uncompressed BML headers, archive callbacks and texture handling.

The source-quality benchmark removes 798 findings and adds 15, with zero flagged symbol labels or newly stale retention entries.

- Six file-local types describe storage used only by the owning translation unit, including the ARAM DMA buffer and request extent, the adjacent card-save records, and the on-disc BML header and entry.
- The existing ARAM DMA storage has C linkage. The offsetof and ATTRIBUTE_ALIGN results are macro tokens reported as declarations.
- The two online quest callers now use the existing TShopWindowBase virtual slot also used by the offline and Challenge lists.
- lbl_805D4AE0 retains the existing BML header pointer label. Its declaration now uses the actual archive header type.
- Three typed BML callers use the existing BmlModelEntry::m_0 field for texture completion, failure and initialization.
