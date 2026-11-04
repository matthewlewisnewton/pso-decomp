# Upstream split realignment

Fork `main` split boundaries compared with upstream `zeroz41/pso-decomp` `master`.
Upstream's unit list has not changed since the squash of #190 (`5695627bd`).
Batches are the consolidations introduced by:

- **180** — Matchpassd, `9575dbb7c`
- **189** — Matchpass lane8, `f4200fcb0`
- **190** — Matchpass lane9, `5695627bd` (TAdMultiPlyChrSelectGC_802C50EC folded into TAdChrSelPlyPlateGC, plus the other lane9 removals)

A row is a fork translation unit that upstream removed. It maps to the upstream unit that now owns its anchor address (first `.text` byte, otherwise the first section).
`upstream-has-extra` means upstream's unit also owns bytes no fork member currently claims (usually a vtable or literal pool in a gap). `fork-overhang` means a fork member also owns bytes outside that upstream unit.

## What this branch folds

`upstream-split-realign-180` folds two #180 pairs whose absorbed half was a hand-written deleting destructor. Both classes already had a real virtual destructor; sharing one TU lets the compiler emit both deleting destructors and both vtables. Deferred generation (`-inline off,deferred` on the unit, not a pragma) is what puts them in address order. Both units stay linked and byte-exact. Upstream's `#pragma defer_codegen` was not imported.

| Fork units | Upstream unit |
|---|---|
| `TObjQuestColApcINW_80196EDC`, `TObjQuestColApcIN_80196F34` | `pso/object/TObjQuestColApcINW_80196EDC.cpp` |
| `TObjQuestColA_80196FE4`, `TObjQuestCol_8019703C` | `pso/object/TObjQuestColA_80196FE4.cpp` |

## Why the rest is deferred

- Units touched by an open fork PR stay out. Those PRs adopt the upstream boundary themselves.
- Almost every other consolidated source on the fork still contains mangled `extern "C"` declarations, offset casts, or steering pragmas. Moving that text into the surviving file would put the banned patterns in the diff. Cleaning them while keeping the current 100% link is per-function work, and unlinking them to clean them up would drop linked bytes.
- Where upstream's unit is larger than the union of the fork pieces, the extra range is data the split sources do not emit yet. Claiming it without a matching object would unlink a unit that links today.

## Open PRs consulted

Listed from `gh pr list -R matthewlewisnewton/pso-decomp --state open` at the time of this map. Source and header paths are the units left alone.

Mapping rows: 372. Folded here: 4. Deferred because an open PR touches the unit: 40. Deferred otherwise: 328.

| Batch | Fork unit | Upstream unit | Ranges | Status |
|---|---|---|---|---|
| 180 | `pso/effect/TEffIndirectCtrl_802A88AC.cpp` | `pso/effect/TEffIndirectCtrl.cpp` | upstream-has-extra | deferred: open PR #161, #187, #215, #222, #291 |
| 180 | `pso/effect/TEffIndirectCtrl_802A9284.cpp` | `pso/effect/TEffIndirectCtrl.cpp` | upstream-has-extra | deferred: open PR #161, #187, #215, #222, #291 |
| 180 | `pso/misc/TScene_802A8140.cpp` | `pso/effect/TEffIndirectCtrl.cpp` | upstream-has-extra | deferred: open PR #161, #187, #215, #222, #291 |
| 180 | `pso/player/TObjPlayer_802A8368.cpp` | `pso/effect/TEffIndirectCtrl.cpp` | upstream-has-extra | deferred: open PR #161, #187, #215, #222, #291 |
| 180 | `pso/unk/text_802A8210.cpp` | `pso/effect/TEffIndirectCtrl.cpp` | upstream-has-extra | deferred: open PR #161, #187, #215, #222, #291 |
| 180 | `pso/unk/text_802A9568.cpp` | `pso/effect/TEffIndirectCtrl.cpp` | upstream-has-extra | deferred: open PR #161, #187, #215, #222, #291 |
| 180 | `pso/effect/TEffIndirectCtrl.cpp (survivor, kept)` | `pso/effect/TEffIndirectCtrl.cpp` | upstream-has-extra | deferred: open PR #161, #187, #215, #222, #291 |
| 180 | `pso/effect/TEffStarLight2D.cpp` | `pso/effect/TEffStarLight2D_Base.cpp` | overlap | deferred |
| 180 | `pso/effect/TEffStarLight2D_Base.cpp (survivor, kept)` | `pso/effect/TEffStarLight2D_Base.cpp` | overlap | deferred |
| 180 | `pso/boss/TBoss8Dragon_800BB650.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD_800B99B4.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD_800B99D8.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD_800B9A34.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD_800B9AF8.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD_800B9B84.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD_800B9D20.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD_800B9F64.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD_800B9F98.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD_800BA138.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD_800BA754.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD_800BA934.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD_800BABA4.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD_800BB158.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD_800BB364.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD_800BB804.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneEpsilon_800B92AC.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_800B9194.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_800B9254.cpp` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/enemy/TObjEneDD.cpp (survivor, kept)` | `pso/enemy/TObjEneDD.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012AB74.cpp` | `pso/item/TUnk_804A4A88.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012AA0C.cpp` | `pso/item/TUnk_804A4A88.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012AB1C.cpp` | `pso/item/TUnk_804A4A88.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012AEA8.cpp` | `pso/item/TUnk_804A4B80.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012AE00.cpp` | `pso/item/TUnk_804A4B80.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012AF50.cpp` | `pso/item/TUnk_804A4B80.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012ABCC.cpp` | `pso/item/TUnk_804A4B80.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012AE50.cpp` | `pso/item/TUnk_804A4B80.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012AF00.cpp` | `pso/item/TUnk_804A4B80.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012AF80.cpp` | `pso/item/TUnk_804A4B80.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012B198.cpp` | `pso/item/TUnk_804A4C78.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012AF98.cpp` | `pso/item/TUnk_804A4C78.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012B0F8.cpp` | `pso/item/TUnk_804A4C78.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012B1F0.cpp` | `pso/item/TUnk_804A4C78.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012AFF8.cpp` | `pso/item/TUnk_804A4C78.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012B140.cpp` | `pso/item/TUnk_804A4C78.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012B7FC.cpp` | `pso/item/TUnk_804A4E68.cpp` | overlap | deferred |
| 180 | `pso/player/TObjPlayer_8012B618.cpp` | `pso/item/TUnk_804A4E68.cpp` | overlap | deferred |
| 180 | `pso/player/TObjPlayer_8012B854.cpp` | `pso/item/TUnk_804A4E68.cpp` | overlap | deferred |
| 180 | `pso/unk/text_8012B664.cpp` | `pso/item/TUnk_804A4E68.cpp` | overlap | deferred |
| 180 | `pso/unk/text_8012B898.cpp` | `pso/item/TUnk_804A4E68.cpp` | overlap | deferred |
| 180 | `pso/item/TItemEquipVariant_8012BDC0.cpp` | `pso/item/TUnk_804A4F60.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012BDA8.cpp` | `pso/item/TUnk_804A4F60.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/TUnk_804A4F60.cpp` | `pso/item/TUnk_804A4F60.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012BE68.cpp` | `pso/item/TUnk_804A5058.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012BE18.cpp` | `pso/item/TUnk_804A5058.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012BEC0.cpp` | `pso/item/TUnk_804A5058.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012BEFC.cpp` | `pso/item/TUnk_804A5058.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012C128.cpp` | `pso/item/TUnk_804A5150.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012BF54.cpp` | `pso/item/TUnk_804A5150.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012C0D0.cpp` | `pso/item/TUnk_804A5150.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012C810.cpp` | `pso/item/TUnk_804A535C.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012C3F4.cpp` | `pso/item/TUnk_804A535C.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012C458.cpp` | `pso/item/TUnk_804A535C.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012C4E0.cpp` | `pso/item/TUnk_804A535C.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012C548.cpp` | `pso/item/TUnk_804A535C.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012C78C.cpp` | `pso/item/TUnk_804A535C.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012C868.cpp` | `pso/item/TUnk_804A535C.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012C950.cpp` | `pso/item/TUnk_804A535C.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012C4E4.cpp` | `pso/item/TUnk_804A535C.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012C5F8.cpp` | `pso/item/TUnk_804A535C.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012C8F8.cpp` | `pso/item/TUnk_804A535C.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012CA20.cpp` | `pso/item/TUnk_804A5458.cpp` | exact | deferred |
| 180 | `pso/player/TObjPlayer_8012CA78.cpp` | `pso/item/TUnk_804A5458.cpp` | exact | deferred |
| 180 | `pso/unk/text_8012CB2C.cpp` | `pso/item/TUnk_804A5458.cpp` | exact | deferred |
| 180 | `pso/item/TItemEquipVariant_8012CBC4.cpp` | `pso/item/TUnk_804A5550.cpp` | overlap | deferred |
| 180 | `pso/player/TObjPlayer_8012CB84.cpp` | `pso/item/TUnk_804A5550.cpp` | overlap | deferred |
| 180 | `pso/player/TObjPlayer_8012CC1C.cpp` | `pso/item/TUnk_804A5550.cpp` | overlap | deferred |
| 180 | `pso/unk/text_8012CC74.cpp` | `pso/item/TUnk_804A5550.cpp` | overlap | deferred |
| 180 | `pso/item/TItemEquipVariant_8012CD90.cpp` | `pso/item/TUnk_804A5648.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012CDE8.cpp` | `pso/item/TUnk_804A5648.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012CE44.cpp` | `pso/item/TUnk_804A5648.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012CFDC.cpp` | `pso/item/TUnk_804A5740.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012CE9C.cpp` | `pso/item/TUnk_804A5740.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012CF84.cpp` | `pso/item/TUnk_804A5740.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012D410.cpp` | `pso/item/TUnk_804A5838.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012D034.cpp` | `pso/item/TUnk_804A5838.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012D218.cpp` | `pso/item/TUnk_804A5838.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012D080.cpp` | `pso/item/TUnk_804A5838.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012D354.cpp` | `pso/item/TUnk_804A5838.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012D5C8.cpp` | `pso/item/TUnk_804A5930.cpp` | overlap | deferred |
| 180 | `pso/player/TObjPlayer_8012D4C0.cpp` | `pso/item/TUnk_804A5930.cpp` | overlap | deferred |
| 180 | `pso/player/TObjPlayer_8012D620.cpp` | `pso/item/TUnk_804A5930.cpp` | overlap | deferred |
| 180 | `pso/player/TObjPlayer_8012D6B4.cpp` | `pso/item/TUnk_804A5930.cpp` | overlap | deferred |
| 180 | `pso/unk/text_8012D468.cpp` | `pso/item/TUnk_804A5930.cpp` | overlap | deferred |
| 180 | `pso/unk/text_8012D65C.cpp` | `pso/item/TUnk_804A5930.cpp` | overlap | deferred |
| 180 | `pso/unk/text_8012D6BC.cpp` | `pso/item/TUnk_804A5930.cpp` | overlap | deferred |
| 180 | `pso/item/TItemEquipVariant_8012D7EC.cpp` | `pso/item/TUnk_804A5A28.cpp` | overlap | deferred |
| 180 | `pso/player/TObjPlayer_8012D844.cpp` | `pso/item/TUnk_804A5A28.cpp` | overlap | deferred |
| 180 | `pso/player/TObjPlayer_8012D8E4.cpp` | `pso/item/TUnk_804A5A28.cpp` | overlap | deferred |
| 180 | `pso/unk/text_8012D88C.cpp` | `pso/item/TUnk_804A5A28.cpp` | overlap | deferred |
| 180 | `pso/item/TItemEquipVariant_8012DCEC.cpp` | `pso/item/TUnk_804A5B20.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012D9C8.cpp` | `pso/item/TUnk_804A5B20.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012EA50.cpp` | `pso/item/TUnk_804A5E20.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012E98C.cpp` | `pso/item/TUnk_804A5E20.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012E83C.cpp` | `pso/item/TUnk_804A5E20.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012E9F8.cpp` | `pso/item/TUnk_804A5E20.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012ECA4.cpp` | `pso/item/TUnk_804A5F18.cpp` | exact | deferred |
| 180 | `pso/player/TObjPlayer_8012EAA8.cpp` | `pso/item/TUnk_804A5F18.cpp` | exact | deferred |
| 180 | `pso/unk/text_8012EC4C.cpp` | `pso/item/TUnk_804A5F18.cpp` | exact | deferred |
| 180 | `pso/item/TItemEquipVariant_8012EDCC.cpp` | `pso/item/TUnk_804A6010.cpp` | exact | deferred |
| 180 | `pso/player/TObjPlayer_8012ECFC.cpp` | `pso/item/TUnk_804A6010.cpp` | exact | deferred |
| 180 | `pso/player/TObjPlayer_8012EE24.cpp` | `pso/item/TUnk_804A6010.cpp` | exact | deferred |
| 180 | `pso/unk/text_8012EE68.cpp` | `pso/item/TUnk_804A6010.cpp` | exact | deferred |
| 180 | `pso/item/TItemEquipVariant_8012F004.cpp` | `pso/item/TUnk_804A6108.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012EEC0.cpp` | `pso/item/TUnk_804A6108.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012EFAC.cpp` | `pso/item/TUnk_804A6108.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012F05C.cpp` | `pso/item/TUnk_804A6200.cpp` | exact | deferred |
| 180 | `pso/unk/text_8012F298.cpp` | `pso/item/TUnk_804A6200.cpp` | exact | deferred |
| 180 | `pso/item/TUnk_804A6200.cpp (survivor, kept)` | `pso/item/TUnk_804A6200.cpp` | exact | deferred |
| 180 | `pso/item/TItemEquipVariant_8012F384.cpp` | `pso/item/TUnk_804A62F8.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012F2F0.cpp` | `pso/item/TUnk_804A62F8.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012F3DC.cpp` | `pso/item/TUnk_804A62F8.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012F478.cpp` | `pso/item/TUnk_804A62F8.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012F5F8.cpp` | `pso/item/TUnk_804A63F0.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012F4D0.cpp` | `pso/item/TUnk_804A63F0.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012F558.cpp` | `pso/item/TUnk_804A63F0.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012F5A0.cpp` | `pso/item/TUnk_804A63F0.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012F650.cpp` | `pso/item/TUnk_804A64E8.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012F890.cpp` | `pso/item/TUnk_804A64E8.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TUnk_804A64E8.cpp (survivor, kept)` | `pso/item/TUnk_804A64E8.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012F9F0.cpp` | `pso/item/TUnk_804A65E0.cpp` | overlap | deferred |
| 180 | `pso/player/TObjPlayer_8012F8E8.cpp` | `pso/item/TUnk_804A65E0.cpp` | overlap | deferred |
| 180 | `pso/player/TObjPlayer_8012F9BC.cpp` | `pso/item/TUnk_804A65E0.cpp` | overlap | deferred |
| 180 | `pso/player/TObjPlayer_8012FA48.cpp` | `pso/item/TUnk_804A65E0.cpp` | overlap | deferred |
| 180 | `pso/unk/text_8012FAB0.cpp` | `pso/item/TUnk_804A65E0.cpp` | overlap | deferred |
| 180 | `pso/item/TItemEquipVariant_8012FC58.cpp` | `pso/item/TUnk_804A66D8.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012FCB0.cpp` | `pso/item/TUnk_804A66D8.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8012FCF8.cpp` | `pso/item/TUnk_804A66D8.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8012FD50.cpp` | `pso/item/TUnk_804A67D0.cpp` | exact | deferred |
| 180 | `pso/unk/text_8012FF8C.cpp` | `pso/item/TUnk_804A67D0.cpp` | exact | deferred |
| 180 | `pso/item/TUnk_804A67D0.cpp (survivor, kept)` | `pso/item/TUnk_804A67D0.cpp` | exact | deferred |
| 180 | `pso/player/TObjPlayer_8012FFE4.cpp` | `pso/item/TUnk_804A68C8.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_80130040.cpp` | `pso/item/TUnk_804A68C8.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TUnk_804A68C8.cpp (survivor, kept)` | `pso/item/TUnk_804A68C8.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_802A3138.cpp` | `pso/misc/TChCrTagPlGraphic.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TChCrTagPlGraphic.cpp (survivor, kept)` | `pso/misc/TChCrTagPlGraphic.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_803367F4.cpp` | `pso/misc/TLobby_803360CC.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TLobby_803360CC.cpp (survivor, kept)` | `pso/misc/TLobby_803360CC.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOGrassJungle_8029CD90.cpp` | `pso/misc/TOGrassJungle.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOGrassJungle.cpp (survivor, kept)` | `pso/misc/TOGrassJungle.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOMineDisp.cpp` | `pso/misc/TOMineTrapDisp.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOMineDisp_8016EF68.cpp` | `pso/misc/TOMineTrapDisp.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOMineTrapDisp.cpp (survivor, kept)` | `pso/misc/TOMineTrapDisp.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveBL01.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveBL02.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveBL03.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveBrakable.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveL01.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveL02.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveL03.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveM01.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveM02.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveM03.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveS01.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveS02.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveS03.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveSL02.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveSM02.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveSS02.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCaveSimple.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_80173874.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_801739F8.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_80173B7C.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_80173D00.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_80173E60.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_80173FC0.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8017411C.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8017427C.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_801743DC.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_80174538.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_80174698.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_801747F8.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_80174954.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_80174AB4.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_80174C14.cpp` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TORockCave.cpp (survivor, kept)` | `pso/misc/TORockCave.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOVS2Wall01_8017C7A4.cpp` | `pso/misc/TOVS2Wall01_8017BE08.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOVS2Wreck01.cpp` | `pso/misc/TOVS2Wall01_8017BE08.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOVS2Wreck02.cpp` | `pso/misc/TOVS2Wall01_8017BE08.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOVS2Wreck03.cpp` | `pso/misc/TOVS2Wall01_8017BE08.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOVS2Wreck04.cpp` | `pso/misc/TOVS2Wall01_8017BE08.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOVS2Wreck05.cpp` | `pso/misc/TOVS2Wall01_8017BE08.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOVS2Wreck06.cpp` | `pso/misc/TOVS2Wall01_8017BE08.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOVS2Wall01_8017BE08.cpp (survivor, kept)` | `pso/misc/TOVS2Wall01_8017BE08.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOWreckAncientBrakable_8017D444.cpp` | `pso/misc/TOWreckAncientBrakable.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOWreckAncientBrakable_8017D5A4.cpp` | `pso/misc/TOWreckAncientBrakable.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TOWreckAncientBrakable.cpp (survivor, kept)` | `pso/misc/TOWreckAncientBrakable.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_803281B8.cpp` | `pso/misc/TParticleCtrl_80327D30.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TParticleCtrl_80327D30.cpp (survivor, kept)` | `pso/misc/TParticleCtrl_80327D30.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TPlyPtclObjectLeftHand.cpp` | `pso/misc/TPlyFollowParticleCtrl.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TPlyPtclObjectLeftHand_8030A4C8.cpp` | `pso/misc/TPlyFollowParticleCtrl.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TPlyPtclObjectRightHand.cpp` | `pso/misc/TPlyFollowParticleCtrl.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_80309D80.cpp` | `pso/misc/TPlyFollowParticleCtrl.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TPlyFollowParticleCtrl.cpp (survivor, kept)` | `pso/misc/TPlyFollowParticleCtrl.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TSaveChCr_80339B64.cpp` | `pso/misc/TSaveChCr.cpp` | exact | deferred |
| 180 | `pso/misc/TSaveChCr_8033A088.cpp` | `pso/misc/TSaveChCr.cpp` | exact | deferred |
| 180 | `pso/misc/TSaveChCr.cpp (survivor, kept)` | `pso/misc/TSaveChCr.cpp` | exact | deferred |
| 180 | `pso/unk/text_8030C340.cpp` | `pso/misc/TWindowPartyStatus.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TWindowPartyStatus.cpp (survivor, kept)` | `pso/misc/TWindowPartyStatus.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_80271400.cpp` | `pso/misc/TWindowStatus.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TWindowStatus.cpp (survivor, kept)` | `pso/misc/TWindowStatus.cpp` | upstream-has-extra | deferred |
| 180 | `pso/misc/TNpcPlayer_80149374.cpp` | `pso/npc/TObjNpcBase.cpp` | upstream-has-extra | deferred |
| 180 | `pso/npc/TObjNpcBase_801490F4.cpp` | `pso/npc/TObjNpcBase.cpp` | upstream-has-extra | deferred |
| 180 | `pso/npc/TObjNpcBase_80149128.cpp` | `pso/npc/TObjNpcBase.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_80148DCC.cpp` | `pso/npc/TObjNpcBase.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_80148274.cpp` | `pso/npc/TObjNpcBase.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_801482F8.cpp` | `pso/npc/TObjNpcBase.cpp` | upstream-has-extra | deferred |
| 180 | `pso/npc/TObjNpcBase.cpp (survivor, kept)` | `pso/npc/TObjNpcBase.cpp` | upstream-has-extra | deferred |
| 180 | `pso/object/TObjBgmCol.cpp` | `pso/object/TObjBgmColCtrl.cpp` | upstream-has-extra | deferred |
| 180 | `pso/object/TObjBgmColCtrl_8017E2EC.cpp` | `pso/object/TObjBgmColCtrl.cpp` | upstream-has-extra | deferred |
| 180 | `pso/object/TObjBgmColCtrl_8017E498.cpp` | `pso/object/TObjBgmColCtrl.cpp` | upstream-has-extra | deferred |
| 180 | `pso/object/TObjBgmColCtrl_8017E8E4.cpp` | `pso/object/TObjBgmColCtrl.cpp` | upstream-has-extra | deferred |
| 180 | `pso/object/TObjBgmCol_8017E664.cpp` | `pso/object/TObjBgmColCtrl.cpp` | upstream-has-extra | deferred |
| 180 | `pso/object/TObjBgmCol_8017E7F0.cpp` | `pso/object/TObjBgmColCtrl.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8017E4EC.cpp` | `pso/object/TObjBgmColCtrl.cpp` | upstream-has-extra | deferred |
| 180 | `pso/object/TObjBgmColCtrl.cpp (survivor, kept)` | `pso/object/TObjBgmColCtrl.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_803516F8.cpp` | `pso/object/TObjButterflyLobby_80350958.cpp` | upstream-has-extra | deferred |
| 180 | `pso/object/TObjButterflyLobby_80350958.cpp (survivor, kept)` | `pso/object/TObjButterflyLobby_80350958.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8004E6D0.cpp` | `pso/object/TObjDFDemo1.cpp` | upstream-has-extra | deferred |
| 180 | `pso/player/TObjPlayer_8004FA98.cpp` | `pso/object/TObjDFDemo5.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8004F904.cpp` | `pso/object/TObjDFDemo5.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8004FE20.cpp` | `pso/object/TObjDFDemo5.cpp` | upstream-has-extra | deferred |
| 180 | `pso/object/TObjDFDemo5.cpp (survivor, kept)` | `pso/object/TObjDFDemo5.cpp` | upstream-has-extra | deferred |
| 180 | `pso/object/TObjQuestCol_8019703C.cpp` | `pso/object/TObjQuestColA_80196FE4.cpp` | upstream-has-extra | folded on upstream-split-realign-180 |
| 180 | `pso/object/TObjQuestColA_80196FE4.cpp (survivor, kept)` | `pso/object/TObjQuestColA_80196FE4.cpp` | upstream-has-extra | folded on upstream-split-realign-180 |
| 180 | `pso/object/TObjQuestColApcIN_80196F34.cpp` | `pso/object/TObjQuestColApcINW_80196EDC.cpp` | upstream-has-extra | folded on upstream-split-realign-180 |
| 180 | `pso/object/TObjQuestColApcINW_80196EDC.cpp (survivor, kept)` | `pso/object/TObjQuestColApcINW_80196EDC.cpp` | upstream-has-extra | folded on upstream-split-realign-180 |
| 180 | `pso/object/TObjRaderHideCol.cpp` | `pso/object/TObjRaderIcon.cpp` | upstream-has-extra | deferred |
| 180 | `pso/object/TObjRaderIcon.cpp (survivor, kept)` | `pso/object/TObjRaderIcon.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012E7D8.cpp` | `pso/player/TUnk_804A5D28.cpp` | exact | deferred |
| 180 | `pso/player/TObjPlayer_8012E760.cpp` | `pso/player/TUnk_804A5D28.cpp` | exact | deferred |
| 180 | `pso/player/TObjPlayer_8012E830.cpp` | `pso/player/TUnk_804A5D28.cpp` | exact | deferred |
| 180 | `pso/unk/text_8012E708.cpp` | `pso/player/TUnk_804A5D28.cpp` | exact | deferred |
| 180 | `pso/player/TUnk_804A5D28.cpp (survivor, kept)` | `pso/player/TUnk_804A5D28.cpp` | exact | deferred |
| 180,189 | `pso/unk/text_801811FC.cpp` | `pso/system/CityTraffic.cpp` | upstream-has-extra | deferred |
| 180,189 | `pso/unk/text_80181278.cpp` | `pso/system/CityTraffic.cpp` | upstream-has-extra | deferred |
| 180,189 | `pso/unk/text_8018130C.cpp` | `pso/system/CityTraffic.cpp` | upstream-has-extra | deferred |
| 180,189 | `pso/unk/text_80181310.cpp` | `pso/system/CityTraffic.cpp` | upstream-has-extra | deferred |
| 180,189 | `pso/unk/text_801815A0.cpp` | `pso/system/CityTraffic.cpp` | upstream-has-extra | deferred |
| 180,189 | `pso/unk/text_80180D18.cpp` | `pso/system/CityTraffic.cpp` | upstream-has-extra | deferred |
| 180,189 | `pso/system/CityTraffic.cpp (survivor, kept)` | `pso/system/CityTraffic.cpp` | upstream-has-extra | deferred |
| 180 | `pso/ui/TAdMcSelectCursorGC_8032A610.cpp` | `pso/ui/TAdMcSelectCursorGC.cpp` | upstream-has-extra | deferred |
| 180 | `pso/ui/TAdMcSelectCursorGC.cpp (survivor, kept)` | `pso/ui/TAdMcSelectCursorGC.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_8036EBEC.cpp` | `pso/ui/TAdMultiChgGameModeGC_8036DE10.cpp` | upstream-has-extra | deferred |
| 180 | `pso/ui/TAdMultiChgGameModeGC_8036DE10.cpp (survivor, kept)` | `pso/ui/TAdMultiChgGameModeGC_8036DE10.cpp` | upstream-has-extra | deferred |
| 180 | `pso/item/TItemEquipVariant_8012C32C.cpp` | `pso/unk/TUnk_804A5248.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/TUnk_804A5248.cpp (survivor, kept)` | `pso/unk/TUnk_804A5248.cpp` | upstream-has-extra | deferred |
| 180 | `pso/object/TObjDFDemo0.cpp` | `pso/unk/text_8004D9A8.cpp` | fork-overhang | deferred |
| 180 | `pso/unk/text_8004D9A8.cpp (survivor, kept)` | `pso/unk/text_8004D9A8.cpp` | fork-overhang | deferred |
| 180 | `pso/misc/TKeyBoardControl_802A1180.cpp` | `pso/unk/text_802A1020.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_802A1144.cpp` | `pso/unk/text_802A1020.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_802A1154.cpp` | `pso/unk/text_802A1020.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_802A1324.cpp` | `pso/unk/text_802A1020.cpp` | upstream-has-extra | deferred |
| 180 | `pso/unk/text_802A1020.cpp (survivor, kept)` | `pso/unk/text_802A1020.cpp` | upstream-has-extra | deferred |
| 180 | `pso/npc/TObjNpcEnemy_803D8090.cpp` | `pso/unk/text_803D853C.cpp` | upstream-has-extra | deferred: open PR #128, #296 |
| 180 | `pso/unk/text_803D8030.cpp` | `pso/unk/text_803D853C.cpp` | upstream-has-extra | deferred: open PR #128, #296 |
| 180 | `pso/unk/text_803D853C.cpp (survivor, kept)` | `pso/unk/text_803D853C.cpp` | upstream-has-extra | deferred: open PR #128, #296 |
| 189 | `pso/boss/TBoss5Gryphon.cpp` | `pso/boss/Boss5GryphonBehavior.cpp` | upstream-has-extra | deferred |
| 189 | `pso/boss/TBoss8Dragon_80065C90.cpp` | `pso/boss/Boss5GryphonBehavior.cpp` | upstream-has-extra | deferred |
| 189 | `pso/boss/Boss5GryphonBehavior.cpp (survivor, kept)` | `pso/boss/Boss5GryphonBehavior.cpp` | upstream-has-extra | deferred |
| 189 | `pso/boss/TBoss4ZakoDraw_8030A96C.cpp` | `pso/boss/TBoss4ZakoDraw.cpp` | exact | deferred |
| 189 | `pso/boss/TBoss4ZakoDraw.cpp (survivor, kept)` | `pso/boss/TBoss4ZakoDraw.cpp` | exact | deferred |
| 189 | `pso/boss/TBoss6Rock_8035477C.cpp` | `pso/boss/TBoss6Rock.cpp` | upstream-has-extra | deferred |
| 189 | `pso/boss/TBoss6Rock_80354A30.cpp` | `pso/boss/TBoss6Rock.cpp` | upstream-has-extra | deferred |
| 189 | `pso/boss/TBoss6Rock_80354A44.cpp` | `pso/boss/TBoss6Rock.cpp` | upstream-has-extra | deferred |
| 189 | `pso/boss/TBoss6Rock.cpp (survivor, kept)` | `pso/boss/TBoss6Rock.cpp` | upstream-has-extra | deferred |
| 189 | `pso/boss/TObjBoss1Crater_8002C6B4.cpp` | `pso/boss/TObjBoss1Crater.cpp` | upstream-has-extra | deferred |
| 189 | `pso/boss/TObjBoss1Crater.cpp (survivor, kept)` | `pso/boss/TObjBoss1Crater.cpp` | upstream-has-extra | deferred |
| 189 | `pso/boss/TObjBoss2Tunnel_8007C5C0.cpp` | `pso/boss/TObjBoss2Tunnel.cpp` | upstream-has-extra | deferred: open PR #240, #290 |
| 189 | `pso/boss/TObjBoss2Tunnel_8007CE14.cpp` | `pso/boss/TObjBoss2Tunnel.cpp` | upstream-has-extra | deferred: open PR #240, #290 |
| 189 | `pso/boss/TObjBoss2Tunnel_8007CF0C.cpp` | `pso/boss/TObjBoss2Tunnel.cpp` | upstream-has-extra | deferred: open PR #240, #290 |
| 189 | `pso/boss/TObjBoss2Tunnel_8007E0CC.cpp` | `pso/boss/TObjBoss2Tunnel.cpp` | upstream-has-extra | deferred: open PR #240, #290 |
| 189 | `pso/boss/TObjBoss2Tunnel_8007E100.cpp` | `pso/boss/TObjBoss2Tunnel.cpp` | upstream-has-extra | deferred: open PR #240, #290 |
| 189 | `pso/boss/TObjBoss2Tunnel_8007E380.cpp` | `pso/boss/TObjBoss2Tunnel.cpp` | upstream-has-extra | deferred: open PR #240, #290 |
| 189 | `pso/boss/TObjBoss2Tunnel_8007E3AC.cpp` | `pso/boss/TObjBoss2Tunnel.cpp` | upstream-has-extra | deferred: open PR #240, #290 |
| 189 | `pso/boss/TObjBoss2Tunnel_8007E418.cpp` | `pso/boss/TObjBoss2Tunnel.cpp` | upstream-has-extra | deferred: open PR #240, #290 |
| 189 | `pso/boss/TObjBoss2Tunnel_8007E8D8.cpp` | `pso/boss/TObjBoss2Tunnel.cpp` | upstream-has-extra | deferred: open PR #240, #290 |
| 189 | `pso/boss/TObjBoss2Tunnel_8007E918.cpp` | `pso/boss/TObjBoss2Tunnel.cpp` | upstream-has-extra | deferred: open PR #240, #290 |
| 189 | `pso/boss/TObjBoss2Tunnel_8007E9EC.cpp` | `pso/boss/TObjBoss2Tunnel.cpp` | upstream-has-extra | deferred: open PR #240, #290 |
| 189 | `pso/boss/TObjBoss2Tunnel_8007EA74.cpp` | `pso/boss/TObjBoss2Tunnel.cpp` | upstream-has-extra | deferred: open PR #240, #290 |
| 189 | `pso/boss/TObjBoss2Tunnel.cpp (survivor, kept)` | `pso/boss/TObjBoss2Tunnel.cpp` | upstream-has-extra | deferred: open PR #240, #290 |
| 189 | `pso/boss/TObjBoss2Tunnel_802F2070.cpp` | `pso/boss/TObjBoss2Tunnel_802F1A58.cpp` | upstream-has-extra | deferred: open PR #290 |
| 189 | `pso/boss/TObjBoss7TunnelCol.cpp` | `pso/boss/TObjBoss2Tunnel_802F1A58.cpp` | upstream-has-extra | deferred: open PR #290 |
| 189 | `pso/unk/text_802F1D1C.cpp` | `pso/boss/TObjBoss2Tunnel_802F1A58.cpp` | upstream-has-extra | deferred: open PR #290 |
| 189 | `pso/unk/text_802F1F58.cpp` | `pso/boss/TObjBoss2Tunnel_802F1A58.cpp` | upstream-has-extra | deferred: open PR #290 |
| 189 | `pso/unk/text_802F1FB0.cpp` | `pso/boss/TObjBoss2Tunnel_802F1A58.cpp` | upstream-has-extra | deferred: open PR #290 |
| 189 | `pso/boss/TObjBoss2Tunnel_802F1A58.cpp (survivor, kept)` | `pso/boss/TObjBoss2Tunnel_802F1A58.cpp` | upstream-has-extra | deferred: open PR #290 |
| 189 | `pso/enemy/TObjEneDf2Bringer_80097100.cpp` | `pso/enemy/TObjEneDf2Bringer.cpp` | upstream-has-extra | deferred |
| 189 | `pso/enemy/TObjEneDf2Bringer_800972B0.cpp` | `pso/enemy/TObjEneDf2Bringer.cpp` | upstream-has-extra | deferred |
| 189 | `pso/unk/text_80362638.cpp` | `pso/enemy/TObjEneEpsilonGuard_8035F5C8.cpp` | upstream-has-extra | deferred |
| 189 | `pso/enemy/TObjEneEpsilonGuard_8035F5C8.cpp (survivor, kept)` | `pso/enemy/TObjEneEpsilonGuard_8035F5C8.cpp` | upstream-has-extra | deferred |
| 189 | `pso/enemy/TObjEneRe7Berura_80092CCC.cpp` | `pso/enemy/TObjEneRe7Berura.cpp` | overlap | deferred |
| 189 | `pso/enemy/TObjEneRe7Berura_8009358C.cpp` | `pso/enemy/TObjEneRe7Berura.cpp` | overlap | deferred |
| 189 | `pso/unk/text_80092B10.cpp` | `pso/enemy/TObjEneRe7Berura.cpp` | overlap | deferred |
| 189 | `pso/enemy/TObjEneRe7Berura.cpp (survivor, kept)` | `pso/enemy/TObjEneRe7Berura.cpp` | overlap | deferred |
| 189 | `pso/unk/text_80223B98.cpp` | `pso/misc/ShopToolStock.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/ShopToolStock.cpp (survivor, kept)` | `pso/misc/ShopToolStock.cpp` | upstream-has-extra | deferred |
| 189 | `pso/player/TObjPlayer_801A5AEC.cpp` | `pso/misc/TKeyBoardControl_801A57C4.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TKeyBoardControl_801A57C4.cpp (survivor, kept)` | `pso/misc/TKeyBoardControl_801A57C4.cpp` | upstream-has-extra | deferred |
| 189 | `pso/object/TObjFish_8001ED90.cpp` | `pso/misc/TLobby_8001EF5C.cpp` | upstream-has-extra | deferred: open PR #240 |
| 189 | `pso/misc/TLobby_8001EF5C.cpp (survivor, kept)` | `pso/misc/TLobby_8001EF5C.cpp` | upstream-has-extra | deferred: open PR #240 |
| 189 | `pso/unk/text_801036CC.cpp` | `pso/misc/TLobby_80103F5C.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TLobby_80103F5C.cpp (survivor, kept)` | `pso/misc/TLobby_80103F5C.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TOTrapAncient01_80226534.cpp` | `pso/misc/TLobby_80226070.cpp` | upstream-has-extra | deferred |
| 189 | `pso/unk/text_802264B8.cpp` | `pso/misc/TLobby_80226070.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TLobby_80226070.cpp (survivor, kept)` | `pso/misc/TLobby_80226070.cpp` | upstream-has-extra | deferred |
| 189 | `pso/audio/SoundBankTables.cpp` | `pso/misc/TLobby_8023F734.cpp` | overlap | deferred |
| 189 | `pso/misc/TLobby_8023F734.cpp (survivor, kept)` | `pso/misc/TLobby_8023F734.cpp` | overlap | deferred |
| 189 | `pso/misc/TOBoss4Rock_801589E8.cpp` | `pso/misc/TOBoss4.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TOBoss4.cpp (survivor, kept)` | `pso/misc/TOBoss4.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TLobby_802A018C.cpp` | `pso/misc/TODoorLabo.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TODoorLabo.cpp (survivor, kept)` | `pso/misc/TODoorLabo.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TQuestListOnline_80217464.cpp` | `pso/misc/TQuestListOnline.cpp` | exact | deferred |
| 189 | `pso/misc/TQuestListOnline.cpp (survivor, kept)` | `pso/misc/TQuestListOnline.cpp` | exact | deferred |
| 189 | `pso/misc/TShopEquipmentGearSequence_8021B438.cpp` | `pso/misc/TShopEquipmentGearSequence.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TShopEquipmentGearSequence.cpp (survivor, kept)` | `pso/misc/TShopEquipmentGearSequence.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TWindowSubStatusDisp_802598E4.cpp` | `pso/misc/TWindowSubStatusDisp_80257784.cpp` | upstream-has-extra | deferred: open PR #187, #219 |
| 189 | `pso/misc/TWindowSubStatusDisp_80257784.cpp (survivor, kept)` | `pso/misc/TWindowSubStatusDisp_80257784.cpp` | upstream-has-extra | deferred: open PR #187, #219 |
| 189 | `pso/object/TObjGbAdvance.cpp` | `pso/object/TObjComputer.cpp` | upstream-has-extra | deferred |
| 189 | `pso/object/TObjGbAdvance_80187D90.cpp` | `pso/object/TObjComputer.cpp` | upstream-has-extra | deferred |
| 189 | `pso/object/TObjGbAdvance_80187E18.cpp` | `pso/object/TObjComputer.cpp` | upstream-has-extra | deferred |
| 189 | `pso/object/TObjComputer.cpp (survivor, kept)` | `pso/object/TObjComputer.cpp` | upstream-has-extra | deferred |
| 189 | `pso/object/TObjGoalWarpAncient.cpp` | `pso/object/TObjMapWarpAncient.cpp` | upstream-has-extra | deferred |
| 189 | `pso/object/TObjMapWarpAncient.cpp (survivor, kept)` | `pso/object/TObjMapWarpAncient.cpp` | upstream-has-extra | deferred |
| 189 | `pso/unk/text_802E62A4.cpp` | `pso/object/TObjOnlineEndingHexLine.cpp` | upstream-has-extra | deferred |
| 189 | `pso/object/TObjOnlineEndingHexLine.cpp (survivor, kept)` | `pso/object/TObjOnlineEndingHexLine.cpp` | upstream-has-extra | deferred |
| 189 | `pso/object/TObjWarpLobby_801A0760.cpp` | `pso/object/TObjWarpLobby.cpp` | upstream-has-extra | deferred |
| 189 | `pso/unk/text_801A069C.cpp` | `pso/object/TObjWarpLobby.cpp` | upstream-has-extra | deferred |
| 189 | `pso/object/TObjWarpLobby.cpp (survivor, kept)` | `pso/object/TObjWarpLobby.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TLobby_80215AE4.cpp` | `pso/player/THunterGuildSeqOnlineTask.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TQuestListOnline_802150E8.cpp` | `pso/player/THunterGuildSeqOnlineTask.cpp` | upstream-has-extra | deferred |
| 189 | `pso/player/THunterGuildSeqOnlineTask.cpp (survivor, kept)` | `pso/player/THunterGuildSeqOnlineTask.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TCameraCtrl_80082FCC.cpp` | `pso/player/TObjPlayer_80083594.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TLobby_8008350C.cpp` | `pso/player/TObjPlayer_80083594.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TParticleCtrl_80083550.cpp` | `pso/player/TObjPlayer_80083594.cpp` | upstream-has-extra | deferred |
| 189 | `pso/misc/TScene_800838C4.cpp` | `pso/player/TObjPlayer_80083594.cpp` | upstream-has-extra | deferred |
| 189 | `pso/player/TObjPlayer_80083360.cpp` | `pso/player/TObjPlayer_80083594.cpp` | upstream-has-extra | deferred |
| 189 | `pso/player/TObjPlayer_80083B38.cpp` | `pso/player/TObjPlayer_80083594.cpp` | upstream-has-extra | deferred |
| 189 | `pso/player/TObjPlayer_800847A8.cpp` | `pso/player/TObjPlayer_80083594.cpp` | upstream-has-extra | deferred |
| 189 | `pso/unk/text_80082C30.cpp` | `pso/player/TObjPlayer_80083594.cpp` | upstream-has-extra | deferred |
| 189 | `pso/unk/text_800832EC.cpp` | `pso/player/TObjPlayer_80083594.cpp` | upstream-has-extra | deferred |
| 189 | `pso/player/TObjPlayer_80083594.cpp (survivor, kept)` | `pso/player/TObjPlayer_80083594.cpp` | upstream-has-extra | deferred |
| 189 | `pso/unk/text_801258A0.cpp` | `pso/player/TObjPlayer_80125780.cpp` | upstream-has-extra | deferred |
| 189 | `pso/player/TObjPlayer_80125780.cpp (survivor, kept)` | `pso/player/TObjPlayer_80125780.cpp` | upstream-has-extra | deferred |
| 189 | `pso/menu/TAdRicoRing_8001BEE8.cpp` | `pso/system/FlagWord.cpp` | exact | deferred |
| 189 | `pso/player/TObjPlayer_8001BED8.cpp` | `pso/system/FlagWord.cpp` | exact | deferred |
| 189 | `pso/player/TObjPlayer_8001BF10.cpp` | `pso/system/FlagWord.cpp` | exact | deferred |
| 189 | `pso/menu/TAdRicoRing.cpp` | `pso/ui/TAdRicoRingCtrl.cpp` | exact | deferred: open PR #225 |
| 189 | `pso/ui/TAdRicoRingCtrl_8001B4A0.cpp` | `pso/ui/TAdRicoRingCtrl.cpp` | exact | deferred: open PR #225 |
| 189 | `pso/unk/text_8001B424.cpp` | `pso/ui/TAdRicoRingCtrl.cpp` | exact | deferred: open PR #225 |
| 189 | `pso/ui/TAdRicoRingCtrl.cpp (survivor, kept)` | `pso/ui/TAdRicoRingCtrl.cpp` | exact | deferred: open PR #225 |
| 189 | `pso/misc/TLobby_8028D714.cpp` | `pso/ui/TAdSinglePlyChrSelectGC_8028D5D4.cpp` | exact | deferred |
| 189 | `pso/ui/TAdSinglePlyChrSelectGC_8028D5D4.cpp (survivor, kept)` | `pso/ui/TAdSinglePlyChrSelectGC_8028D5D4.cpp` | exact | deferred |
| 190 | `pso/player/TObjPlayer_800A894C.cpp` | `pso/enemy/TObjEneDubchik.cpp` | upstream-has-extra | deferred |
| 190 | `pso/unk/text_800A887C.cpp` | `pso/enemy/TObjEneDubchik.cpp` | upstream-has-extra | deferred |
| 190 | `pso/unk/text_800AAC5C.cpp` | `pso/enemy/TObjEneDubchik.cpp` | upstream-has-extra | deferred |
| 190 | `pso/unk/text_800AAD28.cpp` | `pso/enemy/TObjEneDubchik.cpp` | upstream-has-extra | deferred |
| 190 | `pso/unk/text_800AAF78.cpp` | `pso/enemy/TObjEneDubchik.cpp` | upstream-has-extra | deferred |
| 190 | `pso/enemy/TObjEneDubchik.cpp (survivor, kept)` | `pso/enemy/TObjEneDubchik.cpp` | upstream-has-extra | deferred |
| 190 | `pso/ui/TAdMultiPlyChrSelectGC_802C50EC.cpp` | `pso/ui/TAdChrSelPlyPlateGC.cpp` | upstream-has-extra | deferred: open PR #214, #215, #250, #294 |
| 190 | `pso/unk/text_802C6DD4.cpp` | `pso/ui/TAdChrSelPlyPlateGC.cpp` | upstream-has-extra | deferred: open PR #214, #215, #250, #294 |
| 190 | `pso/ui/TAdChrSelPlyPlateGC.cpp (survivor, kept)` | `pso/ui/TAdChrSelPlyPlateGC.cpp` | upstream-has-extra | deferred: open PR #214, #215, #250, #294 |

## Open PR file notes

PRs with an empty file list were open with no diff at query time.

- #125 `codex/fork-function-wave1-07-cast-packet` — WIP: reconstruct cast technique packet handler
  - units: `src/pso/player/TObjPlayer_801C7430.cpp`
- #128 `decomp/vec3-dot` — WIP: Recover typed scalar vector dot product
  - units: `src/pso/unk/text_803D853C.cpp`
- #144 `codex/fukidasi-name-plate` — WIP: reconstruct speech balloon name plate
  - units: `include/pso/misc/TUnk_804CF0B8.h`, `src/pso/misc/TWindowFukidasi.cpp`
  - also edits: `config/GPOE8P/psov3/symbols.txt`, `configure.py`
- #158 `codex/ui-draw-context` — WIP: establish draw context singleton ownership
  - units: `include/pso/misc/TUnk_804CE018.h`, `include/pso/misc/TWindowDrawContext.h`, `include/pso/misc/TWindowKeyBoardSoft.h`, `include/pso/misc/TWindowKeyBoardSoft_8024E68C.h`, `src/pso/misc/TWindowActionPalette.cpp`, `src/pso/misc/TWindowChoiceSetting.cpp`, `src/pso/misc/TWindowChoiceSetting_80249240.cpp`, `src/pso/misc/TWindowCtrlMain.cpp`, `src/pso/misc/TWindowCtrlMain_8024EEF8.cpp`, `src/pso/misc/TWindowDeposit.cpp`, `src/pso/misc/TWindowDuelResult.cpp`, `src/pso/misc/TWindowFukidasi.cpp`, `src/pso/misc/TWindowHelpItem_80255AB4.cpp`, `src/pso/misc/TWindowInputNumber_80256170.cpp`, `src/pso/misc/TWindowKeyBoardSoft_8024E68C.cpp`, `src/pso/misc/TWindowLoadItemTexture.cpp`, `src/pso/misc/TWindowMeseta_802690B4.cpp`, `src/pso/misc/TWindowMessage.cpp`, `src/pso/misc/TWindowMessageInfomation.cpp`, `src/pso/misc/TWindowMessageLog_8026AA38.cpp`, `src/pso/misc/TWindowMessageQuest_8026B118.cpp`, `src/pso/misc/TWindowQuantity.cpp`, `src/pso/misc/TWindowSubComCardList.cpp`, `src/pso/misc/TWindowSubComCard_80244774.cpp`, `src/pso/misc/TWindowSubComCard_80265410.cpp`, `src/pso/misc/TWindowSubCustomSelect.cpp`, `src/pso/misc/TWindowSubEquipKind.cpp`, `src/pso/misc/TWindowSubEquipList.cpp`, `src/pso/misc/TWindowSubItemList.cpp`, `src/pso/misc/TWindowSubShortCutList.cpp`, `src/pso/misc/TWindowSubStatusDisp_80248BE8.cpp`, `src/pso/misc/TWindowSubStatusDisp_8025B050.cpp`, `src/pso/misc/TWindowSubStatusDisp_802671F0.cpp`, `src/pso/misc/TWindowSubStatusDisp_8026DFE8.cpp`, `src/pso/misc/TWindowSubStatusDisp_80281198.cpp`, `src/pso/misc/TWindowSubSymbolChatParts.cpp`, `src/pso/unk/text_80244238.cpp`, `src/pso/unk/text_80246CE8.cpp`, `src/pso/unk/text_80262C3C.cpp`
- #161 `codex/fork-indirect-dispatch-continuation` — WIP: continue native indirect dispatcher and source-link closure
  - units: `include/pso/effect/TEffIndirectCtrl.h`, `src/pso/effect/TEffIndirectCtrl_802A88AC.cpp`
- #167 `codex/fork-movie-80143988-continuation` — WIP: Recover movie frame packing
  - units: `src/pso/misc/TMovie_80143988.cpp`
- #187 `codex/ui-context-provider-contract` — WIP: define typed context and quad provider contract
  - units: `include/pso/effect/TEffIndirectCtrl.h`, `include/pso/misc/TWindowDrawContext.h`, `include/pso/misc/TWindowKeyBoardSoft_8024E68C.h`, `include/pso/misc/TWindowMenuMainMenu.h`, `include/pso/player/TObjPlayer_802A8368.h`, `include/pso/unk/text_8026CB5C.h`, `src/pso/misc/TShopItemListWindow.cpp`, `src/pso/misc/TWindowHelpItem_8025A60C.cpp`, `src/pso/misc/TWindowKeyBoardSoft_8024E68C.cpp`, `src/pso/misc/TWindowMainMenu_802AD538.cpp`, `src/pso/misc/TWindowSubComCard_80244774.cpp`, `src/pso/misc/TWindowSubCustomEquip_80275D9C.cpp`, `src/pso/misc/TWindowSubStatusDisp_8024FBA8.cpp`, `src/pso/misc/TWindowSubStatusDisp_80256B94.cpp`, `src/pso/misc/TWindowSubStatusDisp_80257784.cpp`, `src/pso/misc/TWindowSubStatusDisp_8025995C.cpp`, `src/pso/misc/TWindowSubStatusDisp_8025B050.cpp`, `src/pso/player/TObjPlayer_802A8368.cpp`, `src/pso/unk/text_8026CB5C.cpp`
  - also edits: `config/GPOE8P/psov3/symbols.txt`
- #214 `codex/fork-pr142-refresh-20261102` — WIP: refresh multiplayer helper recovery over main
  - units: `include/pso/ui/TAdMultiPlyChrSelectGC.h`, `include/pso/ui/TAdMultiPlyChrSelectGC_802C50EC.h`, `src/pso/ui/TAdMultiPlyChrSelectGC_802C50EC.cpp`
  - also edits: `configure.py`
- #215 `codex/fork-pr184-refresh-20261102` — WIP: refresh multiplayer slot contracts over helper recovery
  - units: `include/pso/effect/TEffIndirectCtrl.h`, `include/pso/player/TObjPlayer_802A8368.h`, `src/pso/misc/TShopItemListWindow.cpp`, `src/pso/player/TObjPlayer_802A8368.cpp`, `src/pso/ui/TAdMultiChgGameModeGC.cpp`, `src/pso/ui/TAdMultiConfirmGC.cpp`, `src/pso/ui/TAdMultiPlyChrSelectGC_802C50EC.cpp`, `src/pso/ui/TAdMultiPlyChrSelectGC_802DBCC4.cpp`, `src/pso/ui/TAdMultiPlyChrSelectGC_802DEC44.cpp`, `src/pso/ui/TAdMultiSelGameModeGC.cpp`
  - also edits: `config/GPOE8P/psov3/symbols.txt`
- #216 `codex/mainmenu-refresh-143-20261102` — Match main menu frame renderer with its constant pool
  - units: `include/pso/misc/TWindowDrawContext.h`, `include/pso/misc/TWindowKeyBoardSoft.h`, `include/pso/misc/TWindowKeyBoardSoft_8024E68C.h`, `include/pso/misc/TWindowMainMenu.h`, `include/pso/misc/TWindowMainMenu_802AD538.h`, `include/pso/misc/TWindowMenuMainMenu.h`, `src/pso/misc/TWindowKeyBoardSoft_8024E68C.cpp`, `src/pso/misc/TWindowMainMenu.cpp`, `src/pso/misc/TWindowMainMenu_802AD538.cpp`, `src/pso/misc/TWindowMenuMainMenu.cpp`, `src/pso/misc/TWindowSubComCard_80244774.cpp`
  - also edits: `config/GPOE8P/psov3/splits.txt`, `config/GPOE8P/psov3/symbols.txt`, `configure.py`
- #218 `codex/mainmenu-refresh-183-20261102` — Use array-backed main menu frame quads
  - units: `src/pso/misc/TWindowMainMenu_802AD538.cpp`
- #219 `codex/mainmenu-refresh-188-20261102` — Refresh typed main menu context and label quad
  - units: `include/pso/misc/TWindowDrawContext.h`, `include/pso/misc/TWindowKeyBoardSoft.h`, `include/pso/misc/TWindowKeyBoardSoft_8024E68C.h`, `src/pso/misc/TWindowHelpItem_8025A60C.cpp`, `src/pso/misc/TWindowKeyBoardSoft_8024E68C.cpp`, `src/pso/misc/TWindowMainMenu_802AD538.cpp`, `src/pso/misc/TWindowSubComCard_80244774.cpp`, `src/pso/misc/TWindowSubCustomEquip_80275D9C.cpp`, `src/pso/misc/TWindowSubStatusDisp_80256B94.cpp`, `src/pso/misc/TWindowSubStatusDisp_80257784.cpp`, `src/pso/misc/TWindowSubStatusDisp_8025995C.cpp`, `src/pso/misc/TWindowSubStatusDisp_8025B050.cpp`
  - also edits: `config/GPOE8P/psov3/config.yml`, `config/GPOE8P/psov3/linked_units.txt`, `config/GPOE8P/psov3/symbols.txt`
- #221 `codex/fork-ancient-base-e8a` — Restore Ancient trap base and data ownership
  - units: `include/pso/misc/TOTrap.h`, `include/pso/misc/TOTrapAncient01.h`, `include/pso/misc/TOTrap_801792AC.h`, `src/pso/misc/TOTrap.cpp`, `src/pso/misc/TOTrapAncient01.cpp`, `src/pso/misc/TOTrapAncient02.cpp`, `src/pso/misc/TOTrapSeabed01.cpp`
  - also edits: `config/GPOE8P/psov3/splits.txt`, `config/GPOE8P/psov3/symbols.txt`, `configure.py`
- #222 `codex/fork-ancient-source-e8a` — Match Ancient01 .sdata2 floats
  - units: `include/pso/effect/TEffIndirectCtrl.h`, `include/pso/player/TObjPlayer_802A8368.h`, `src/pso/misc/TOTrapAncient01.cpp`, `src/pso/misc/TShopItemListWindow.cpp`, `src/pso/player/TObjPlayer_802A8368.cpp`
  - also edits: `config/GPOE8P/psov3/symbols.txt`
- #223 `codex/fork-ancient-link-e8a` — Hold Ancient trap source linkage
  - no files
- #225 `codex/fork-boss6-zanzo-recovery-20261102` — WIP: Recover native Boss 6 trail rendering
  - units: `include/pso/boss/TBoss6Demo21_TYPE2_DEAD.h`, `include/pso/boss/TBoss6Type1.h`, `include/pso/boss/TBoss6Type2.h`, `include/pso/boss/TBoss6Zanzo.h`, `include/pso/misc/TMovie.h`, `include/pso/player/TObjPlayer.h`, `include/pso/render/ColorCopy.h`, `include/pso/render/TriangleFan3D.h`, `include/pso/system/RelModuleBuffer.h`, `include/pso/unk/text_80320358.h`, `src/pso/boss/Boss6Type2Death.cpp`, `src/pso/boss/TBoss6Type1.cpp`, `src/pso/boss/TBoss6Type1_80320AE0.cpp`, `src/pso/boss/TBoss6Type2.cpp`, `src/pso/boss/TBoss6Zanzo.cpp`, `src/pso/menu/TAdPlyChrSelPlateGC.cpp`, `src/pso/misc/TLobby_801E2F94.cpp`, `src/pso/misc/TMovie_80143E90.cpp`, `src/pso/misc/TMovie_801443C0.cpp`, `src/pso/misc/TMovie_80144778.cpp`, `src/pso/misc/TWindowSubStatusDisp_8025737C.cpp`, `src/pso/object/TObjSinBoard.cpp`, `src/pso/ui/TAdChrMoveEffectGC.cpp`, `src/pso/ui/TAdRicoRingCtrl_8001B4A0.cpp`, `src/pso/unk/text_80290D1C.cpp`, `src/pso/unk/text_80320358.cpp`
  - also edits: `config/GPOE8P/psov3/config.yml`, `config/GPOE8P/psov3/splits.txt`, `config/GPOE8P/psov3/symbols.txt`
- #240 `codex/fork-quest-window-data-types` — Import Quest/window fold for ownership qualification
  - units: `include/pso/TAdPlayerLoadGC.h`, `include/pso/TShopWindowBase.h`, `include/pso/misc/TLobby.h`, `include/pso/misc/TQuestVmDownLoadServer.h`, `include/pso/misc/TShopArmorListWindow.h`, `include/pso/misc/TShopDeleteItemWindow.h`, `include/pso/misc/TShopEquipmentListWindow.h`, `include/pso/misc/TShopEquipmentSellWindow.h`, `include/pso/misc/TShopGetItemWindow.h`, `include/pso/misc/TShopItemListWindow.h`, `include/pso/misc/TShopJudgmentItemWindow.h`, `include/pso/misc/TShopKeepItemWindow.h`, `include/pso/misc/TShopSequence.h`, `include/pso/misc/TUnk_804CDFE8.h`, `include/pso/misc/TUnk_804CE7E8.h`, `include/pso/misc/TUnk_804CE964.h`, `include/pso/misc/TUnk_804CF0B8.h`, `include/pso/misc/TUnk_804D0618.h`, `include/pso/misc/TUnk_804D0658.h`, `include/pso/misc/TUnk_804D0948.h`, `include/pso/misc/TUnk_804EFBAC.h`, `include/pso/misc/TWindowAddition.h`, `include/pso/misc/TWindowBase.h`, `include/pso/misc/TWindowBreakIn.h`, `include/pso/misc/TWindowCallBack.h`, `include/pso/misc/TWindowChallengeResult.h`, `include/pso/misc/TWindowChatSymbol.h`, `include/pso/misc/TWindowComCard.h`, `include/pso/misc/TWindowDD_WS_ScrollBar.h`, `include/pso/misc/TWindowDD_WS_String.h`, `include/pso/misc/TWindowDD_WS_Word.h`, `include/pso/misc/TWindowDeposit.h`, `include/pso/misc/TWindowDuelResult.h`, `include/pso/misc/TWindowKeyBoardBase.h`, `include/pso/misc/TWindowKeyBoardHard.h`, `include/pso/misc/TWindowLoadItemTexture.h`, `include/pso/misc/TWindowLockOn.h`, `include/pso/misc/TWindowMenu.h`, `include/pso/misc/TWindowMenuIconLine.h`, `include/pso/misc/TWindowMenuMainMenu.h` …
  - also edits: `config/GPOE8P/psov3/config.yml`, `config/GPOE8P/psov3/linked_units.txt`, `config/GPOE8P/psov3/splits.txt`, `config/GPOE8P/psov3/symbols.txt`, `configure.py`
- #241 `codex/fork-rename-tunk-804F112C` — Name TItemSpecialEvent special-event units
  - units: `include/pso/item/TItemSpecialEvent.h`, `include/pso/item/TUnk_804F112C.h`, `src/pso/item/TItemSpecialEvent_803531FC.cpp`, `src/pso/item/TItemSpecialEvent_80353380.cpp`, `src/pso/item/TItemSpecialEvent_80353414.cpp`, `src/pso/misc/TEndingPic.cpp`, `src/pso/unk/text_803531FC.cpp`, `src/pso/unk/text_80353380.cpp`, `src/pso/unk/text_80353414.cpp`
  - also edits: `config/GPOE8P/psov3/config.yml`, `config/GPOE8P/psov3/linked_units.txt`, `config/GPOE8P/psov3/splits.txt`, `config/GPOE8P/psov3/symbols.txt`, `configure.py`
- #250 `codex/fork-multiplayer-chrselect-20261101` — Match multiplayer character-select slot routines
  - units: `include/pso/ui/TAdMultiPlyChrSelectGC_802C50EC.h`, `src/pso/ui/TAdMultiPlyChrSelectGC_802C50EC.cpp`
  - also edits: `config/GPOE8P/psov3/config.yml`, `config/GPOE8P/psov3/linked_units.txt`, `config/GPOE8P/psov3/splits.txt`, `config/GPOE8P/psov3/symbols.txt`
- #260 `codex/fork-information-str-source-hold` — Recover InformationStr source; hold activation on localization storage
  - units: `include/pso/TChCrTagInformationStr.h`, `include/pso/misc/TChCrTagInformationStr.h`, `include/pso/unk/text_80309890.h`, `src/pso/misc/TChCrTagInformation.cpp`, `src/pso/misc/TChCrTagInformationStr.cpp`, `src/pso/unk/text_80309890.cpp`
  - also edits: `config/GPOE8P/psov3/config.yml`, `config/GPOE8P/psov3/linked_units.txt`, `config/GPOE8P/psov3/splits.txt`, `config/GPOE8P/psov3/symbols.txt`
- #261 `codex/fork-floor-flags-current` — Link floor flag import with typed buffer interfaces
  - units: `include/pso/misc/TLobby.h`, `include/pso/unk/text_8020B47C.h`, `include/pso/unk/text_8020E08C.h`, `src/pso/misc/TLobby_8020B588.cpp`, `src/pso/misc/TLobby_8020BF68.cpp`, `src/pso/misc/TPlyJoinLobbyEntry.cpp`, `src/pso/unk/text_8020B47C.cpp`, `src/pso/unk/text_8020E08C.cpp`
  - also edits: `config/GPOE8P/psov3/linked_units.txt`, `config/GPOE8P/psov3/symbols.txt`
- #263 `codex/fork-quest-prefix-workspace-publish-r21` — Link Quest prefix and workspace storage (2,460 bytes)
  - units: `src/pso/misc/QuestDownloadBuffers.cpp`
- #267 `codex/fork-indirect-gc20-exact` — Match and link TEffIndirectCtrl
  - no files
- #268 `codex/fork-guildwarning-wip-20261102` — WIP: preserve GuildWarning recovery with activation holds
  - units: `include/pso/THunterGuildWarning.h`, `src/pso/misc/THunterGuildWarning.cpp`, `src/pso/misc/THunterGuildWarning_80211648.cpp`, `src/pso/misc/THunterGuildWarning_80211690.cpp`, `src/pso/misc/THunterGuildWarning_802116EC.cpp`, `src/pso/misc/THunterGuildWarning_80211700.cpp`, `src/pso/misc/THunterGuildWarning_8021170C.cpp`, `src/pso/misc/THunterGuildWarning_80211718.cpp`, `src/pso/player/THunterGuildWarning.cpp`
  - also edits: `config/GPOE8P/psov3/linked_units.txt`
- #272 `codex/fork-lens-flare-native-linked-20261102` — Match and link TEF_LensFlare
  - units: `include/pso/effect/TEF_LensFlare.h`, `src/pso/effect/TEF_LensFlare.cpp`, `src/pso/misc/TWindowKeyBoardBase_8008102C.cpp`
  - also edits: `config/GPOE8P/psov3/config.yml`, `config/GPOE8P/psov3/linked_units.txt`, `config/GPOE8P/psov3/splits.txt`, `config/GPOE8P/psov3/symbols.txt`, `configure.py`
- #278 `codex/fork-falz-plot-table-20261102` — Type the Falz plot script-state table consumed by TBoss6PlotFalz
  - units: `include/pso/boss/TBoss6PlotFalz.h`, `include/pso/boss/TBoss6PlotFalzState.h`, `src/pso/boss/TBoss6PlotFalz.cpp`, `src/pso/boss/TBoss6PlotFalz_802B0228.cpp`
- #281 `upstream-pr-178-transform-chunk-vertices-pos-normal` — [upstream #178] Recover transform_chunk_vertices_pos_normal as scalar C++
  - units: `src/pso/unk/text_803E2D70.cpp`
- #282 `upstream-pr-184-tlobby-sub-80402ce0` — [upstream #184] Match TLobby__sub_80402CE0 (308 B, twin-transcribe of matched sub_803FC318)
  - no files
- #284 `upstream-pr-172-fn-8042e8c4` — [upstream #172] Recover LaunchDol (0x8042E8C4) as C++
  - units: `include/pso/network/ModemLaunchContext.h`, `src/pso/unk/text_8042E8C4.cpp`, `src/pso/unk/text_8042EAD4.cpp`
  - also edits: `config/GPOE8P/psov3/symbols.txt`
- #285 `upstream-pr-174-pad-03-8042e9fc-text` — [upstream #174] Match pad_03_8042E9FC_text (5 words) — stranded epilogue of the #172 relocator; 20/20-version C-impossibility
  - units: `src/pso/unk/text_8042E9FC.cpp`
- #286 `upstream-pr-177-tboss7tentacleneedle-ct` — [upstream #177] Match TBoss7TentacleNeedle__ct (416B, 104/104) — unit completes 41/41; 144-perm wall fell to a rebased staging restage
  - no files
- #287 `codex/fork-minetrap-8016f6f8` — Link TOMineTrap_8016F6F8
  - units: `include/pso/misc/TOMine.h`, `include/pso/misc/TOMineTrap.h`, `src/pso/misc/TOMineTrap_8016F6F8.cpp`, `src/pso/unk/text_8016F1C0.cpp`
- #289 `upstream-matchpass-180-tboss6type1` — [upstream #180/#183 slice] TBoss6Type1 unit / TLobby__sub_801E38A0
  - units: `include/pso/boss/TBoss6Type1.h`, `include/pso/enemy/BattleParameters.h`, `src/pso/boss/TBoss6Type1.cpp`, `src/pso/misc/TLobby_801E2F94.cpp`
  - also edits: `config/GPOE8P/psov3/splits.txt`, `configure.py`
- #290 `upstream-matchpass-185-tobjboss2tunnel` — Port upstream TObjBoss2Tunnel consolidated unit (upstream #185)
  - units: `include/pso/TAdPlayerLoadGC.h`, `include/pso/boss/TObjBoss2Tunnel.h`, `include/pso/boss/TObjBoss2Tunnel_8007CF0C.h`, `include/pso/boss/TObjBoss2Tunnel_8007E418.h`, `include/pso/boss/TObjBoss2Tunnel_8007EA74.h`, `include/pso/boss/TUnk_804E4B3C.h`, `include/pso/misc/TKeyBoardControl_803DE9C4.h`, `include/pso/misc/TLobby.h`, `include/pso/misc/TWindowSubStatusDisp_803DEE6C.h`, `include/pso/system/ControllerInputState.h`, `include/pso/ui/TAdSinglePlyChrSelectGC.h`, `src/pso/boss/TObjBoss2Tunnel.cpp`, `src/pso/boss/TObjBoss2Tunnel_8003B138.cpp`, `src/pso/boss/TObjBoss2Tunnel_8007C5C0.cpp`, `src/pso/boss/TObjBoss2Tunnel_8007CE14.cpp`, `src/pso/boss/TObjBoss2Tunnel_8007CF0C.cpp`, `src/pso/boss/TObjBoss2Tunnel_8007E0CC.cpp`, `src/pso/boss/TObjBoss2Tunnel_8007E100.cpp`, `src/pso/boss/TObjBoss2Tunnel_8007E380.cpp`, `src/pso/boss/TObjBoss2Tunnel_8007E3AC.cpp`, `src/pso/boss/TObjBoss2Tunnel_8007E418.cpp`, `src/pso/boss/TObjBoss2Tunnel_8007E8D8.cpp`, `src/pso/boss/TObjBoss2Tunnel_8007E918.cpp`, `src/pso/boss/TObjBoss2Tunnel_8007E9EC.cpp`, `src/pso/boss/TObjBoss2Tunnel_8007EA74.cpp`, `src/pso/boss/TObjBoss2Tunnel_802F2070.cpp`, `src/pso/boss/TObjBoss2Tunnel_803E2BAC.cpp`, `src/pso/misc/TBreakUpMdl.cpp`, `src/pso/misc/TLobby_800F9D38.cpp`, `src/pso/misc/TLobby_803382E4.cpp`, `src/pso/misc/TWindowKeyBoardHard_801FBA48.cpp`, `src/pso/misc/TWindowSubStatusDisp_803DEE6C.cpp`, `src/pso/ui/TAdPlayerLoadGC_801E0C30.cpp`, `src/pso/ui/TAdSinglePlyChrSelectGC_80243218.cpp`, `src/pso/ui/TAdSinglePlyChrSelectGC_802E13C8.cpp`
  - also edits: `config/GPOE8P/psov3/config.yml`, `config/GPOE8P/psov3/linked_units.txt`, `config/GPOE8P/psov3/splits.txt`, `config/GPOE8P/psov3/symbols.txt`, `configure.py`
- #291 `upstream-matchpass-180-teffindirectctrl` — Port upstream TEffIndirectCtrl consolidated unit (upstream #180)
  - units: `include/pso/effect/TEffIndirectCtrl.h`, `include/pso/effect/TEffIndirectCtrl_802A88AC.h`, `include/pso/misc/TScene.h`, `include/pso/unk/text_802A8210.h`, `src/pso/effect/TEffIndirectCtrl.cpp`, `src/pso/effect/TEffIndirectCtrl_802A88AC.cpp`, `src/pso/effect/TEffIndirectCtrl_802A9284.cpp`, `src/pso/misc/TScene.cpp`, `src/pso/misc/TScene_802A8140.cpp`, `src/pso/misc/TTecRaFoie.cpp`, `src/pso/player/TObjPlayer_802A8368.cpp`, `src/pso/unk/text_802A8210.cpp`, `src/pso/unk/text_802A9568.cpp`
  - also edits: `config/GPOE8P/psov3/config.yml`, `config/GPOE8P/psov3/linked_units.txt`, `config/GPOE8P/psov3/splits.txt`, `config/GPOE8P/psov3/symbols.txt`, `configure.py`
- #294 `upstream-matchpass-180-tadmultiplychrselectgc` — Port upstream TAdMultiPlyChrSelectGC_802C50EC unit (upstream #180)
  - units: `src/pso/ui/TAdMultiPlyChrSelectGC_802C50EC.cpp`
  - also edits: `config/GPOE8P/psov3/splits.txt`, `config/GPOE8P/psov3/symbols.txt`
- #295 `cursor/quest-vm-803e9a74-803ec284` — Decompile quest-download segment search and page fitting
  - units: `include/pso/misc/QuestDownloadRecords.h`, `src/pso/misc/TQuestVmDownLoadServer_803E6970.cpp`
- #296 `upstream-matchpass-180-text-803d853c` — Port upstream render_debug_text (text_803D853C, upstream #180)
  - units: `include/pso/render/DebugFont.h`, `include/pso/unk/text_803D853C.h`, `src/pso/unk/text_803D853C.cpp`
  - also edits: `configure.py`
- #298 `upstream-matchpass-183-tlobby-803fc178` — Port upstream TLobby_803FC178 unit (upstream #183)
  - units: `src/pso/misc/TLobby_803FC178.cpp`
  - also edits: `config/GPOE8P/psov3/splits.txt`, `config/GPOE8P/psov3/symbols.txt`
- #299 `upstream-matchpass-183-tboss7tentacleneedle` — [Matchpass slice] TBoss7TentacleNeedle unit from upstream #183 (41/41, links; real ctor at 100)
  - units: `include/pso/TBoss7Tentacle.h`, `include/pso/boss/TBoss7TentacleNeedle.h`, `include/pso/player/TObjPlayer.h`, `src/pso/boss/Boss7DeRolLeCBehavior.cpp`, `src/pso/boss/Boss7TentacleBanks.cpp`, `src/pso/boss/TBoss7TentacleNeedle.cpp`
  - also edits: `config/GPOE8P/psov3/config.yml`, `config/GPOE8P/psov3/linked_units.txt`, `config/GPOE8P/psov3/splits.txt`, `config/GPOE8P/psov3/symbols.txt`, `configure.py`
- #300 `upstream-pr-187-tlobby-804061fc` — [Matchpass slice] TLobby__sub_804061FC from upstream #187 (1/1, unlinked)
  - units: `src/pso/misc/TLobby_804050DC.cpp`
- #301 `grok/issue-233-conversion-pool-constants` — Recognize conversion-pool constants and drop the Fish duplicate
  - units: `src/pso/object/TObjFish_8033CCC8.cpp`
  - also edits: `config/GPOE8P/psov3/symbols.txt`
