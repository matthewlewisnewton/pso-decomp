# Recover native save, quest, and asset-loading interfaces

The current 218-path candidate is `06f05041eba0f87c018fd20e2e4d947b96d4f6ba` directly on upstream `31bb8ea5f01b0e02b609fb59411f4805308106bf`. It includes #375 and upstream’s UI, weapon and quest naming passes through #381. The retail DOL, coverage, original data ranges and focused save, quest and asset probes pass. [Exact-head validation](2026-11-23-upstream-381-rebase-and-cutover-validation.json)

The 218-path review preview `9589a617bea819ad462ad592073a80ffb4785526` builds on the already validated #377 merge preview `97711798d9`. It adds native player creation and saved inventory access to the save, quest and asset batch. The matching build and coverage pass, and the benchmark removes 1,067 findings and adds 26 with zero flagged labels. Three added mangled-name occurrences share one typed constructor declaration across two saved-player callers because the direct C++ member form changes retail instruction order. [Validation](2026-11-23-native-player-construction-validation.json)

The current standalone review is `d9537252e154ef0055cfe0d2d51ecb85f6c71086` on upstream master `63ba63fe8b`. Inventory preview `d8ae552bd4` and the actor and AVE-TCP preview `5a98123bb6` also match retail. [Current validation](2026-11-23-native-character-records-validation.json)

The earlier standalone review is `cad627125653e8bb70c3b7ebe3b3a74e7eb21b76` on upstream master `63ba63fe8b`. Inventory preview `45c84c3028` and the actor and AVE-TCP preview `857b515781` also match retail. [Current validation](2026-11-23-native-bank-window-validation.json)

The preceding standalone review is `991ae618f9a8ec08e906a809280386438f6946b1` on upstream master `63ba63fe8b`. The same code matches in the inventory preview `fbd1e87d5b` and with AVE-TCP #378 in `259ed12ee1`. [Exact-head validation](2026-11-23-saves-quest-asset-review-preflight.json)

The 179-path independent review `e2d6876245` is based directly on upstream master `e39eb9e138`. It retains the existing nullable release interface where the shared memory work is still queued. The recovered length methods and text builders share the native QuestDownloadRequest type, and BML entry traversal uses the archive header. The retail build, coverage gate and nine runtime suites pass. The benchmark removes 729 findings and adds 24, with zero flagged labels and zero newly stale retention entries. The separate review `02d6f9de87` on the validated #375/#377 preview keeps the existing texlist member, typed NPC records and relocated particle owner. It matches retail and passes coverage with 706 fewer findings and zero flagged labels. [Validation](2026-11-22-independent-save-quest-asset-validation.json)

The current local review is `e0d6a26efd` on `14951bf3bf`. The 179-path batch matches retail, retains coverage, and passes nine runtime suites. It preserves the existing typed BML callback parameters and uses the recovered name and symbol lookup fields. The two remaining label advisories follow the decoded length methods onto the existing address-named request record. [Current validation](2026-11-22-upstream-371-saves-quests-and-assets-validation.json)

The local review `great-merge/review/after-367/saves-quests-and-asset-loading` is at `6077e29d1cedfbbba0565de112f08aa67bbe6270` above the inventory review `61a66013a179485ff5923b6248c8b2b2d4b6de60`. Its two commits touch 174 paths and reproduce the validated cumulative source tree. [Validation and component records](2026-11-22-upstream-367-saves-quests-and-assets-validation.json)

## Proposed PR description

Recover the types used to load save data, quest entries, and assets, and carry those declarations through their existing callers.

- Memory-card selection and preflight use the original slot, load-result, and file records.
- Character selection, save validation and lobby entry share the native character record. Preview and status callers read its typed appearance and stats.
- The Hunter Guild uses typed quest callbacks and download windows. The cache passes the signed handle and native ARAM request through reads and completion, using the original records and buffers.
- Shared file requests keep their callback, completion pointer, and list links through cancellation and release. Texture and model callers pass the native GVM and BML records.
- The bank uses the native deposit window and the item selection callbacks on their actual window classes.
- The footprint effect uses a typed texture pointer from load through drawing and release, and reads yaw from the player's rotation record.

The 40 changed linker labels follow the recovered owners and argument types. The retail DOL matches byte for byte with all 27,572 functions exact, 2,368 linked units and all 1,147 original data bytes accounted for. The targeted checks cover card metadata, quest ARAM completion and timeouts, compressed and uncompressed BML headers, archive callbacks and texture handling.

The source-quality benchmark removes 1,053 findings and adds 26, with zero flagged symbol labels or newly stale retention entries.

- Six file-local types describe storage used only by the owning translation unit, including the ARAM DMA buffer and request extent, the adjacent card-save records, and the on-disc BML header and entry.
- The existing ARAM DMA storage has C linkage. The offsetof and ATTRIBUTE_ALIGN results are macro tokens reported as declarations.
- The two online quest callers now use the existing TShopWindowBase virtual slot also used by the offline and Challenge lists.
- lbl_805D4AE0 retains the existing BML header pointer label. Its declaration now uses the actual archive header type.
- Three typed BML callers use the existing BmlModelEntry::m_0 field for texture completion, failure and initialization.
- The bank delete and get windows use their four existing callback fields in place of byte-offset overlays. The deposit window uses the existing number-entry class for its horizontal position. The three shop item allocators keep explicit constructor calls to preserve CodeWarrior’s retail callback address loads.
- Two references use the existing file-local slot type to locate the character within the secondary-card record.
- Three references share the typed saved-player constructor declaration and preserve the retail instruction order across its two callers.
