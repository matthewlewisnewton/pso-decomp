# Upstream matchpasses

Group related source recovery into fewer, larger reviews with independent matching builds. Keep upstream names where the entities have equivalent behavior, types and linkage. Include source changes that recover types, ownership, native code, or linking coverage. Keep documentation and tooling changes on the fork layer.

## Bulk replay on upstream master `6b080e67ab`

The new upstream build reproduces the retail SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3` and passes the project checker. The [90-range data ledger](2026-11-18-fork-data-ranges.tsv) records 980 source-linked bytes and 167 bytes of alignment padding. Upstream links the final 24-byte keyboard table at `0x804D0004`. The address comparison with the historical retail-matched fork build reports zero exact or source-linked losses.

Three-way replay applied 13 existing review groups directly to the new upstream master. The network review needed four overlapping files reconciled around the upstream native socket classes and the fork's shared datagram layout. All 14 local heads are single commits on `6b080e67ab`, reproduce retail, pass `tools/check_pr.py`, and retain comparable exact and linked coverage from the historical fork. Each review contains source changes only. The overlapping component reviews are available for integration and grouping.

| Local review | Head | Changed files |
| --- | --- | ---: |
| `stage-traps-and-resources` | `000cc1dbe8` | 66 |
| `enemy-archives-and-appearance` | `660fa19579` | 83 |
| `quest-inventory-and-resource-lists` | `951537b5fe` | 44 |
| `player-techniques-and-item-effects` | `c780db3055` | 71 |
| `camera-and-radar-views` | `7d296c4b1a` | 25 |
| `window-menus-and-controller-flags` | `2ffe296480` | 25 |
| `photon-blast-sequence-and-effects` | `a1d5cdd5be` | 15 |
| `title-compass-and-ending-scenes` | `e7879a64c5` | 40 |
| `dragon-attacks-and-material-fades` | `4a54365dba` | 59 |
| `resource-lifetimes` | `6132f74a35` | 224 |
| `encounter-drawing` | `77961d8d48` | 153 |
| `world-object-resources` | `b9a70258fa` | 95 |
| `stage-objects-and-weather` | `52b5c14a44` | 37 |
| `network-startup-and-packet-lifetime` | `d892292ba8` | 60 |

The cumulative merge reconciles all 85 overlapping paths. The socket replay keeps the shared datagram layout on upstream's native socket class. Keyboard text and key state use upstream's new classes, with the fork's typed positions, allocation, and query returns. Window drawing uses `WindowDrawContext` with the fork's fade expression and layout checks. The main menu and status rows retain the fork's typed fields. The flower retains its typed rendering calls in upstream's source order, which emits the newly linked float pool.

The complete source branch at `e235bf7e3b` and review stack at `ce9748d350` share the same source tree, with each earlier tip preserved as a merge parent. The combined and working fork builds reproduce retail and pass `tools/check_pr.py`. They preserve exact and source-linked code and data from upstream, the previous source tree, and the historical fork. The parent comparison has a four-byte alignment accounting change at `0x804C2304`. The separate 90-range inventory retains all 980 source-linked bytes and 167 alignment bytes. Source consolidation replaces nine prior units with seven under the same address coverage.

The working fork's regenerated retention list covers 26,957 symbols. All 133 tooling overlay paths round-trip, all 11 layer tests pass, and the layered fork differs from the source tree only under `fork/` and the fork workflow. The branch updates are local. The remaining original fork source edits are tracked in the [source review index](2026-11-18-fork-review-index.tsv).

## Player inventory and Photon Blast result interfaces

The 14-file combined replay at `31eaa1755f` carries the fork's saved-inventory and item-deletion interfaces into their current player, trade, and quest owners. It also makes the Photon Blast result setter take the original unsigned halfword and removes the indirect call cast. The compiler preserves the original equipment address arithmetic when the inventory slot is computed after the cast to `s32`.

The standalone quest, inventory and resource-list review at `333c4490b3` spans 51 files. The Photon Blast sequence, results and summoned-effects review at `4cd09cf8af` spans 17 files. Each is one commit on upstream master `6b080e67ab`. Both standalone reviews, the combined source, and the working fork reproduce retail and pass the checker. The exact and linked coverage checks report zero loss against the historical fork. All 133 tooling overlay paths round-trip and all 11 fork-layer tests pass.

The player-render comparison verifies six original function bodies, three GX binding tables, the texture object and the reload diagnostic in the consolidated source. The current owner retains 20 exact functions and 248 exact bytes of data, including the ranges previously emitted by three fork fragments. The consolidated source retains those definitions and their compiler placement.

The rename-aware preview compared 206 unambiguous paths. It found 16 clean replays, three already applied, 77 with non-overlapping edits, and 110 with overlaps requiring source review. The [source review index](2026-11-18-fork-review-index.tsv) now has 1,046 entries awaiting owner comparison and 918 with partial evidence.

## Subsystem batches and media contracts

The 10-file source replay at `65ea0db603` restores native Dolphin SDK file and command-block members to the 40 DVD request records. The combined unit keeps all 15 exact functions, including open, close, polling, asynchronous reads and file-size lookup. Six ADX stream consumers now share a single declaration for the 0x64-byte retail chunk splitter. The combined and working-fork builds reproduce retail, the project checker passes, and the 133 tooling paths round-trip. All 11 fork-layer tests pass.

Subsequent review builds use batches of related file changes. Resolve shared interfaces together and compare each batch against upstream and the historical fork. Keep a larger batch together when a reviewer can follow the dependency chain and split at an interface boundary when the file group needs different context.

| Local review | Head | Changed files |
| --- | --- | ---: |
| Player, quest and item state | `30050798e0` | 132 |
| Stage objects and world resources | `c088b7f407` | 133 |
| Windows, camera and scene rendering | `5307cf26ef` | 87 |
| Audio streaming, CVFS and disc archives | `5b4652af21` | 90 |
| Enemy, boss and encounter combat | `c46c0e1730` | 247 |

Each recorded head is one source-only commit on `6b080e67ab`. Each reproduces the retail executable and passes the project checker with zero matched or linked code and data loss. The larger heads include already validated standalone changes and are local review candidates. The audio review includes the existing shared CVFS callback prerequisite.

The first four batches have single-file integration overlaps around the signboard, lobby archive resource handling and character preview load. Apply those shared paths once in review order. The historical source audit remains open. The [source review index](2026-11-18-fork-review-index.tsv) now has 1,042 records awaiting owner comparison and 922 with partial evidence.

## Parallel historical source replay

The 89-file source replay at `c0e4c936a1` combines four independently validated changes on upstream `6b080e67ab`. The combined tree and working fork reproduce retail and pass the project checker. They retain matched and source-linked code and data from upstream and the historical fork. The 133 tooling overlay paths round-trip and all 11 layer tests pass.

- Weapon and item effects add a checked shared descriptor and native collider model and scale in 17 files. The 13 changed compilation units retain 189 exact functions. The seven weapon factory tables already share the linked consolidated owner.
- Enemy collision moves `update_collisions` to `TObjCollidable` and carries 95 calls across 39 files. The method keeps its retail address at `0x80156698`. The target replay types the shared `TObjChara` actor pointer and updates enemy, trap and NPC callers. The two enemy replays touch 49 unique files.
- Rendering and character creation restore the lens flare, critical hit, indirect effect and character-info constructors and factories in 14 files. The six directly affected units retain 58 exact functions and 1,000 exact bytes of data.
- World and quests carry typed GBA download filenames, full-width warp results and native tombstone data and fields in 11 files. The hair movement edits and quest-list storage already survive in their native owners.

The standalone player, quest and item review at `ce787c3349` now spans 146 files and passes the retail and coverage checks. The standalone window, camera and rendering review at `230bf773d9` now spans 98 files. The stage and world review at `021cdb2f6d` spans 139 files. Both pass the retail and coverage checks. The quest GBA filename change stays in the combined branch with its typed quest argument union. The enemy and boss review has eight overlapping files to reconcile against the collision and target replays. The [historical source review index](2026-11-18-fork-review-index.tsv) records 88 additional findings. It has 1,020 entries awaiting owner comparison and 939 with partial evidence.

## Bulk subsystem replay and enemy review

The 25-file replay at `7d34ce6cc5` combines independently validated changes on `6b080e67ab`. It restores the De Rol Le and Barba Ray tunnel curves, snapshot and segment calls, equipment list ownership and typed shop inventory, quest download text conversion, and typed player collision face indexing. The combined source and working fork reproduce the retail executable and preserve matched and source-linked code and data from upstream and the historical fork. The 133 tool overlay paths round-trip and all 11 layer tests pass.

The 279-file enemy, boss and encounter review at `ac47423607` groups the 49-file collision and targeting replay and the eight-file tunnel replay with the existing combat changes. The eight collision and targeting overlaps took the review's native class names and layouts. The tunnel pass retained the standalone breakup allocator. Its earlier standalone head was `c46c0e1730`. The enemy audit also verified 5,572 exact source-linked bytes across 55 historical ranges. The two uncovered words are alignment padding.

The 147-file player, quest and item review at `4321d51c98` includes the seven-file quest download text replay. Both reviews are single source commits on upstream `6b080e67ab`, reproduce retail, and retain upstream and historical matched and linked coverage.

The five current review candidates cover 665 of 1,756 source diff paths by path. The remaining 1,091 include paths for shared interfaces and files already reconciled in Great Merge, which need review assignment. A path can have edits from several review groups. The next largest grouping is the window framework and its drawing callers. The stage object preflight found shared archive, texture, player/demo, particle and sound dependencies across the selected door, lobby, ambient, fence and cave files.

The [source review index](2026-11-18-fork-review-index.tsv) records 24 additional findings. It has 1,013 records awaiting owner comparison and 946 with partial evidence.

## Whole-subsystem review candidates

Refreshing the older subsystem reviews in bulk puts all ten candidates below on upstream `6b080e67ab`. Each is one source commit with the source-linked build metadata it requires. Each reproduces the retail executable. Documentation and tooling live on the fork branches.

| Candidate | Local head | Changed files |
| --- | --- | ---: |
| Shared allocation, copying and release | `7cf8dfc61c` | 257 |
| Positional sound and particle factories | `fbe0109d70` | 342 |
| BML, model and GVM texture resources | `d7f1fb19b2` | 488 |
| Window framework and drawing | `1cc4a9b534` | 376 |
| Enemy, boss and encounter combat | `ac47423607` | 279 |
| Player, quest and item state | `4321d51c98` | 147 |
| Stage objects and world resources | `021cdb2f6d` | 139 |
| Window, camera and scene presentation | `230bf773d9` | 98 |
| Audio streaming and disc archives | `5b4652af21` | 90 |
| Network startup and packet lifetime | `d892292ba8` | 60 |

Memory and spatial effects also build together as a two-review stack at `befc3255ba`. The 536-file stack resolves 19 overlapping files, mostly independent header additions. It retains the separate memory and spatial review commits and passes the retail and coverage checks. The BML/GVM and window reviews also have substantial overlaps with those providers. Their independent source reviews are available for sequencing and rebuilding on the selected base.

The window review keeps upstream's native window and keyboard owners, including the original 24-byte keyboard table. It preserves all 67 audited drawing calls. Both the window and latest combined builds account for all 1,147 original inventory bytes in 90 ranges, with 980 source-linked bytes and 167 alignment bytes. The network candidate already contains the earlier DNS, DHCP, PPP and callback work under upstream's native UDP classes.

The candidates touch 1,490 of 1,756 Great Merge diff paths. The remaining 266 unassigned paths are concentrated in player and enemy interfaces. This is a path count. Shared-file edits still need coverage and merge checks when sequencing the reviews. The door, fence and cave trial compiled all 44 changed object translation units and identified 19 ambient and lobby callers that depend on the same provider changes. The stage expansion needs those callers and matching linked symbol providers together.

The 330-file legacy combat refresh at `9b9d8a9670` is an exact source donor for the remaining combat work. The full union with the current enemy review introduced 34 conflicting files and required separate player, actor, rendering and resource contracts. Keep the validated 279-file review as the current candidate and take the remaining combat changes by owning class, preserving the required declarations and their callers together.

## Player, actor and stage ownership replay

The 19-file source replay at `ec924a7a85` restores the native player action checks and inventory dispatch, the Rico ring constructors, and the multiplayer character-selection plate layout. It also synchronizes 13 linker registrations for already-recovered Gee and swarm functions. The combined source and working fork reproduce retail and preserve matched and source-linked coverage. The 133 fork tooling paths round-trip and all 11 layer tests pass. All 1,147 original data bytes are accounted for in 90 ranges, with 980 source-linked bytes and 167 alignment bytes.

| Review | Local head | Review base | Changed files |
| --- | --- | --- | ---: |
| Player, quest and item state | `995e372456` | `6b080e67ab` | 173 |
| Enemy and boss combat | `06305ec659` | `6b080e67ab` | 293 |
| Actor motion, animation and presentation | `2485f3ffe2` | `6b080e67ab` | 383 |
| Camera, scenes and frontend presentation | `81da6ab6e5` | `6b080e67ab` | 145 |
| Shared renderer and native chunk callbacks | `cff677a2aa` | `6b080e67ab` | 261 |
| Stage and world objects | `4f59b9f427` | `d7f1fb19b2` | 153 |

The player review includes typed state, scale and shrink packets, collision indexing and the action dispatch. Its standalone inventory helper uses the original ABI declaration to preserve the compiler's retail register assignments. The combined source uses the typed inventory owner. The enemy review adds native Canadin and Gee behavior plus six shared enemy interfaces for registration, groups, state exchange, experience and drops. The cumulative branch already had all 58 named enemy functions, so its additional enemy changes are the linker registrations.

The 400-file rendering stack at `6bc3dec076` validates shared renderer callbacks, frontend presentation and character creation, and then native starlight objects and their item-effect callers. The starlight patch uses the shared color-list interface from the presentation layer. Each stage reproduces the retail executable.

The stage review uses the BML/GVM provider as its parent and validates the shared trail API and its seven callers alongside fence debris, ambient particles, fish placement and lobby dolphin resource access. The independent 139-file stage review remains useful for reviewing the earlier stage scope against upstream. The complete actor prerequisite also validates independently. Keep overlap checks by owning class when sequencing these groups.

The prepared reviews and prerequisites touch 1,660 of 1,761 combined diff paths. The remaining 101 paths still need review assignment, and edits to paths shared between reviews still need merge validation. The [source review index](2026-11-18-fork-review-index.tsv) records 14 additional findings. It has 1,007 records awaiting owner comparison and 952 with partial evidence.

## Native matrix, encounter, and window source recovery

The latest exact source is `024d7add1f` and the local landing checkpoint is `a00468dc9b`. The 51-file replay combines four independently verified batches. The common matrix-array provider now has the full SDK call signature and 24 typed callers. Item and mag visibility use vector positions. Barba Ray's Tentacle and Needle use native construction and action methods. The enemy batch restores nine owners across Epsilon, Morfos, Recon and Slime. The window batch restores the selection-bar context and the 0x2C effect-light layout.

| Source batch | Component head | Files |
| --- | --- | ---: |
| Spatial transforms and item visibility | `ce062a88ab` | 25 |
| Barba Ray Tentacle and Needle | `66e7d32969` | 6 |
| Enemy state, targeting and effects | `94928d7d8f` | 12 |
| Selection bars and window effect lights | `8e27c3a0e8` | 13 |

The complete source and working fork reproduce retail and retain matched and source-linked coverage from upstream, the historical fork, and both review checkpoints. All 1,147 initial bytes remain accounted for, the 133 tooling paths round-trip, and all 11 layer tests pass.

The overlap audit classifies 791 hunks from the 334 paths in the recorded checkpoint preview. It verifies both include sets in 211 hunks. Historical source replay identifies 11 complete retained deltas, and anchored comparison finds 2,839 retained code hunks across 586 source entries. Eleven of those entries retain every changed code hunk and still need include ownership checks. The remaining variants are recorded for owner review. [Source retention evidence](2026-11-19-source-retention-audit.json)

## Disc streams, encounter owners and Challenge records

The 24-file source wave at `5c2f0eb778` is in landing `3fbbcc50dc`. The disc patch applies the ADXF handle type to the deferred read queue and sound-bank slots. TGStream and its BML callers use the original byte-buffer API. The Challenge patch recovers the typed record rows and the original dispatch tables. The enemy patch brings back typed Fly Nest slots and the Gee child-removal virtual method. The boss patch restores Olga Flow Type 1 construction, spawn records and PlotFalz ownership.

The Challenge records are part of the local display review at `28c2e9303e`. The world review at `1ebb463633` keeps disc streams, Fly Nest and Gee ownership, and Olga Flow Type 1 in three commits spanning 22 paths on the existing world history. Both review builds, the combined source and the working fork reproduce retail. The combined build has all 27,572 functions exact and preserves exact and source-linked coverage from upstream, the historical fork and both subsystem checkpoints. All 1,147 initial bytes are accounted for, all 133 local tooling paths round-trip, and all 11 fork layer tests pass.

Function-body comparison found 6,060 retained bodies across 810 historical paths awaiting source review. Of those, 980 differ from a comparable branch-point implementation, which establishes retention of a fork change. These comparisons cover function bodies and leave signatures, includes and header ownership for separate review. [Function-source evidence](2026-11-19-function-source-evidence.json)

## Player collision, Pan Arms, keyboard and quest download replay

The 21-file replay at `ff9f043765` is in the local landing checkpoint `02c7592bb3`. The player routines use typed vectors and the original collision hit result. They share the original combat constant declarations. Pan Arms restores captured model positions and typed split-half state, including the movement method and its five callers. Soft keyboard frame and reveal drawing use the shared window context and quad. Quest downloads use the original workspace, slot and scratch layouts.

The three existing subsystem reviews carry the new changes. Keyboard is in display at `ad2a91dacd`, and Pan Arms is in world at `2715532ccc`. Player and quest add 13 paths at `67fca574b8` in two commits. That review retains its current collision provider and return contract. The fully typed collision result is in the combined source.

The source, working fork and review builds reproduce retail. The source retains exact and source-linked coverage from the five queued upstream reviews. The original 90 ranges still account for 980 linked bytes and 167 padding bytes. All 133 local paths round-trip. Eleven fork-layer tests and five host smoke programs pass. Both changed quest workspace files compile in 32-bit host mode. The extended 32-bit smoke programs need a 32-bit C/C++ link runtime.

The audit closes 8 historical rows and records partial evidence for the other changed owners. The current ledger has 971 entries awaiting complete owner comparison and 957 with partial evidence. [Owner replay evidence](2026-11-19-owner-replay-evidence.json)

## Great Merge on upstream Matchpassz

Upstream `49b48c32e6` is the base of the local source at `4e6278824e` and landing checkpoint `4cd2081700`. The eight overlapping paths retain the fork's typed resource and drawing calls on upstream's native cursor and player owners. Dubchik keeps the three original filename definitions in its owning translation unit, and the action palette uses the original `gc_tag` resource array and lifetime.

Four retired source files contribute 171 exact functions to their replacement owners. All retain their original addresses and sizes. The complete game and working fork match retail and retain all 27,572 exact functions and 1,758,510 matched and linked data bytes. The refresh adds 400 matched data bytes and 180 linked data bytes over the prior checkpoint. The 30 apparent historical data gaps are the same 164 zero-valued alignment bytes omitted by upstream's split layout.

All four subsystem review branches, the five ordered reviews below, and the standalone Challenge review are validated on the same upstream base. The five queued patches keep their previous diffs. The original 90 ranges still account for all 1,147 bytes. All 133 fork-only tooling paths round-trip and all 11 fork-layer tests pass. [Upstream replay evidence](2026-11-19-upstream-332-replay.json)

## Stage ownership, Morfos, title scene and ADX replay

The 56-file combined source `75b5a6951a` is in the local landing checkpoint `eca56dcb7d`. The stage changes restore the native floor-area getter and Olga Flow player checks, together with 21 map-collision factory table entries and the laboratory caller. Morfos uses its native constructor, destructor, factory, virtual table and typed combat layout. The title scene owns its four mode handlers and transition lifetime. ADX encoding uses the shared SJ ring-buffer and decoder types.

Stage and Morfos add 39 paths to the world review at `b5ff4bf24a`. The title scene adds 13 paths to the display review at `d1c26559e5`. The audio changes are in the existing queued audio review at `702c76a225`. Its following results review keeps its 51-file diff at `b65ecabf8a`.

The combined source, working fork and refreshed reviews match retail without losing matched or linked coverage. All original 1,147 bytes are accounted for. Auditing 23 older data files verifies 78,944 source-linked bytes and 12 alignment bytes. Five active headers and two recovered interface entries are now fully reconciled. All 133 local paths round-trip, 11 fork-layer tests and five host smoke tests pass, and the ADX encoder compiles in 32-bit host mode. [Subsystem and historical source evidence](2026-11-19-subsystem-replay-evidence.json)

## Battle standings, Slime effects and fish-school replay

The 18-file source replay `5d585c5540` is in the local landing checkpoint `fff0d3a1e3`. The battle standings patch shares the original client, rank and score record between lobby and split-screen providers, duel windows and the quest score and place checks. The world patch restores the native Slime tail and water bomb classes, along with shared fish-school rendering and archive ownership.

The standings changes add 10 changed paths to the existing display review at `f8fee4e3c9`. The Slime and fish-school changes add eight changed paths to the existing world review at `df959f6a2f`.

The combined source, working fork and both review branches reproduce retail. All 90 original ranges retain their 980 source-linked bytes and 167 alignment bytes. The audit fully reconciled 11 historical records, including the two Slime headers, and added evidence for nine related records that still have wider changes to compare. The working fork retains all 133 overlay paths. Its link retention check and all 11 fork-layer tests pass.

The player class trial from this checkpoint is resolved in the following replay. [Source and validation evidence](2026-11-19-declaration-replay-evidence.json)

## Camera position, color-line rendering and native owner replay

The 102-file source replay `9f5ed76768` is in the local landing checkpoint `e418f8a73c`. Camera storage uses the original Vec across 33 environment and gameplay paths. Color-line rendering uses one shared descriptor across 25 paths. SlimeOne uses both native constructors, the 0x3F8 layout and original animation and effect ownership. The native TObject function compares class-name pointers through 22 translation units. Player and NPC initialization uses the original signed class byte while preserving the original loads, including the starting-inventory and level-stat functions.

The local display review at `3b8fd12a2f` carries the 25 rendering paths. The world review at `4f1237edb0` carries the combined 39 camera and Slime paths. The player review at `80437bd0a1` carries the 18-path class replay. The 26-path native object lookup also has a standalone review on current upstream at `6155c67873` under `great-merge/current/standalone-object-class-name`.

The combined source, working fork and all four review branches reproduce retail. All 90 historical ranges retain their 980 source-linked bytes and 167 alignment bytes. The source audit closed 15 historical records and updated evidence for 88 records in total. 1,895 remain open. The 133 fork-only overlay paths round-trip and all 11 layer tests pass. [Source and validation evidence](2026-11-19-native-subsystems-evidence.json)

## Menu sizing, Gryphon lightning and indirect scene effects

The 79-file source replay `7368e6ed1c` is in the local landing checkpoint `cee9e7eff5`. The display review at `8d7fc86f08` assigns menu sizing to TWindowMenu, retains all 41 original calls and uses typed choice-menu storage. The world review at `b144f74c5c` joins the native Gal Gryphon lightning constructors and typed indirect scene effects across 18 changed paths.

The separate compiler cleanup recovers 723 historical directive removals across 28 files. The exact build still needs the existing floating-point contraction scope in player collision and the two scheduling directives in protocol list assignment. The Gal Gryphon patch also removes 268 historical directives from its behavior owner.

The combined source, working fork and both review branches reproduce retail. All 90 original ranges retain 980 source-linked bytes and 167 alignment bytes. The historical audit updated 112 records and closed 29. 1,866 remain open. All 133 fork-only paths round-trip and all 11 layer tests pass. [Source and validation evidence](2026-11-19-owner-closure-evidence.json)

## Word Select, tunnel effects and native packet and model types

The 75-file source replay `5816ff8534` is in the local landing checkpoint `cfee239994`. The 40-file display update `fddb20c8c4` moves default drawing context to TWindowBase and restores Word Select page allocation, selection and lifetime. The display port retains its existing allocation and release pair.

The 36-file world update `9f6bc23b9e` joins native tunnel dust and splash layouts, the Dark Falz Zako and appearance factories, the typed 6xB2 sound packet and its dispatcher, and the shared NJS_OBJECT traversal used by Gol Dragon and Dark Falz rock rendering. Each subsystem reproduces the original executable. The world port retains tunnel normalization, the existing rock allocator and the Tenchu capture callback.

All 90 original ranges retain their 980 source-linked bytes and 167 alignment bytes. The historical audit updated 109 records and closed 23. 1,843 remain open. All 133 fork-only paths round-trip and all 11 layer tests pass. [Source and validation evidence](2026-11-19-structure-replay-evidence.json)

## Action palette, particle definitions and boss encounter types

The combined replay `f759412dff` carries 46 source paths into local landing checkpoint `53b78dd12e`. The action palette uses one four-byte tag for cursor, window and player reads and writes, including the two player attack wrappers. The particle renderers and emitters share the historical 0x28 definition. Dark Gunner has typed formation state, callbacks and constructor operands. Olga Flow rock breakup uses an explicit point, typed debris fields and a local pool for the four physics constants.

The 18-file display update `cf8d847e24` uses a small palette state header with its current player providers. The 30-file world update `e80e5badf2` joins the particle, Dark Gunner, and Olga Flow patches. Its existing renderer, sound and allocation calls retain their exact instruction sequences. Dark Gunner keeps the explicit virtual table and destructor because the current compiler orders the native virtual table and switch table differently from retail.

The combined source, working fork and both groups reproduce the retail executable. All 90 original ranges retain 980 source-linked bytes and 167 alignment bytes. The audit updated 27 records and closed 12. 1,831 remain open. All 133 fork-only paths round-trip. The 11 layer tests and all 294 fork tool tests pass. The fork-only viewport assertion now follows the current typed Dark Falz caller. [Source and validation evidence](2026-11-19-coherent-subsystems-evidence.json)

## Direct upstream review branches

These local review branches each start at upstream `49b48c32e6`. Each branch and the combined 99-file preview reproduce retail and pass strict upstream comparisons across all 2,449 linked units.

| Scope | Local branch | Files |
| --- | --- | ---: |
| Stage particles, scene refraction and Olga Flow debris | `great-merge/current/standalone-stage-particles-refraction-and-debris` | 34 |
| Enemy registration, state, group dispatch and Dark Gunner formation | `great-merge/current/standalone-enemy-registration-and-formations` | 44 |
| Action palette, cursor input and customization windows | `great-merge/current/standalone-action-palette-and-customization` | 24 |

The review branches use the interfaces available on upstream. The verified canonical ports carry the corresponding native providers forward in the working fork. [Source and validation evidence](2026-11-19-coherent-subsystems-evidence.json)

## Gameplay random state, enemy movement, trap motion, and small-font drawing

The 61-file source replay `f89d3c063a` updates canonical Great Merge and landing checkpoint `d2cc747122`. It restores the actor and embedded random-state interfaces, the shared collision and movement returns, stage trap targeting and motion ownership, and the shared speech-balloon and small-font render calls.

The historical audit added evidence for 42 records and closed five. The open ledger has 1,826 records. All 90 original ranges still account for 980 source-linked bytes and 167 alignment bytes. The working fork preserves all 133 fork-only paths and passes 294 tool tests and 11 layer tests.

These source-only reviews start at upstream `49b48c32e6`. Each branch and the combined 129-file preview reproduce retail across all 2,449 upstream-linked units.

| Scope | Local branch | Files |
| --- | --- | ---: |
| Enemy registration, formation and collision movement | `great-merge/current/standalone-enemy-registration-and-formations` | 53 |
| Trap targeting, player eligibility, and motion and resource ownership | `great-merge/current/standalone-stage-traps-and-motion` | 38 |
| Action palette, customization, speech balloons and small-font drawing | `great-merge/current/standalone-action-palette-and-customization` | 38 |
| Gameplay random state and native actor receivers | `great-merge/current/standalone-gameplay-random` | 29 |

The enemy and trap branches both edit the enemy class declaration. The combined build retains the typed state exchange from the enemy branch and removes the obsolete motion declaration from the trap branch. [Source and validation evidence](2026-11-19-native-provider-wave-evidence.json)

## Inventory, stage population, Gol Dragon and native message windows

The 59-file source replay `afcee17ce6` updates canonical Great Merge and landing checkpoint `6cac429aab`. It restores native inventory walks and placement records, shared live and archived floor layouts, Gol Dragon resource and clone ownership, and the Guild Warning and native message-window interfaces. Independent review identified a meseta caller that accepts non-player characters. The corrected declaration uses the shared character type.

The historical audit added evidence for 35 records and closed 14. Five closures came from comparing the complete authored source changes against the live compiler owners. The open ledger has 1,812 records. All 90 original ranges still account for 980 source-linked bytes and 167 alignment bytes. The working fork preserves 133 fork-only paths and passes 294 tool tests and 11 layer tests.

The source-only reviews start at upstream `49b48c32e6`. Each branch and their combined 124-file preview reproduce retail across all 2,449 upstream-linked units.

| Scope | Local branch | Files |
| --- | --- | ---: |
| Guild Warning, native modal messages, palette and small-font drawing | `great-merge/current/standalone-action-palette-and-customization` | 61 |
| Stage population, trap targeting, motion and resource ownership | `great-merge/current/standalone-stage-traps-and-motion` | 47 |
| Gol Dragon archive resources, model cloning and clone formation | `great-merge/current/standalone-gol-dragon-resources-and-formation` | 22 |

The direct inventory preview identifies the older native item-list methods and typed inventory owners as prerequisites. The exact recovered item code is already present in the working fork. [Source and validation evidence](2026-11-19-inventory-stage-window-replay.json)

## Inventory review, radar, Recon and character selection

Source checkpoint `65c060f3e8` and landing checkpoint `2ad537e9a5` carry 53 source files. Great Merge now has the native radar viewport and marker interfaces, Recobox and Recon ownership, the shared character selection plate and cursor constructors, and typed inventory placement, shop, and export storage. The source audit records 38 historical files and closes 15. The ledger has 1,797 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves 133 fork-only paths and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/challenge-and-duel-results` | Challenge and duel results, battle standings and quest score lookups | 57 |
| `great-merge/current/standalone-camera-and-radar` | Camera views, radar rendering and map markers | 33 |
| `great-merge/current/standalone-native-array-runtime` | Global C++ array allocation and release, with native call sites | 156 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy registration and formations, movement, and native Recon and Recobox ownership | 65 |
| `great-merge/current/character-selection-plates` | Character-selection plates, native cursor and multiplayer slot layout | 26 |
| `great-merge/current/standalone-inventory-and-item-placement` | Inventory trees, native records, item placement, sorting, shop and export interfaces | 39 |

The inventory review stacks on the global C++ array operators. That separate review replaces upstream's placeholder allocation and release names across their shared callers. The inventory diff is measured from the prerequisite. The results review and the array-runtime stack overlap in two translation units. The detailed evidence records those paths. [Source and validation evidence](2026-11-19-inventory-radar-recon-review.json)

## Weapon factories, enemy targeting, quest transfers and Symbol Chat

Source checkpoint `d1cccf4e5e` and landing checkpoint `698faaffce` carry 86 source files. Great Merge now has a typed weapon factory registry, shared enemy visibility and transition interfaces, and native online quest transfer records. The Symbol Chat Parts calls use their own window type. The source audit records 74 historical files and closes 33. The ledger has 1,764 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves 133 fork-only paths and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-weapon-factory-registry` | Weapon factory table, original slot targets and typed item records | 38 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy registration, formations, Recon and Recobox, targeting and transition hooks | 83 |
| `great-merge/current/standalone-online-quest-transfers` | Online BIN and DAT quest transfers and shared scratch-buffer callers | 22 |
| `great-merge/current/standalone-symbol-chat-and-shortcut-preview` | Symbol Chat Parts and shortcut preview, selection and activation | 20 |

The weapon audit compares every compiled registry slot with the prior retail target. The review keeps direct callback addresses on GameCube and uses exact-type adapters in hosted builds. The direct quest review uses the upstream allocator and transfer APIs. All four direct reviews combine into a retail-exact 159-file build. [Source and validation evidence](2026-11-19-weapon-targeting-quest-replay.json)

## ADX streaming, boss arenas, stage transfers and menus

Source checkpoint `01d56a4e4d` and landing checkpoint `660d7c4f5b` carry 66 source files. The source replay restores native ADX callbacks and playback handles, shared light slots for De Rol Le and Barba Ray, typed player callbacks for stage transfers, and bank deposit and Mag Photon Blast window lifetimes. The source audit records 47 historical files and closes 30. The ledger has 1,734 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves 133 fork-only paths and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-adx-streaming` | ADX playback, decoder and disc streaming interfaces | 35 |
| `great-merge/current/standalone-derolle-arena-lighting` | De Rol Le and Barba Ray arena lights and ceiling debris | 17 |
| `great-merge/current/standalone-stage-transfer-and-seasonal-assets` | Stage transfer callbacks and seasonal and forest resource ownership | 22 |
| `great-merge/current/standalone-main-menu-and-child-windows` | Main menu, bank deposit and Mag Photon Blast window lifetimes | 15 |

Each candidate builds from current upstream with the source for its subsystem. The combined 85-file review build also matches retail. A separate audio source review verified the callback signatures, playback arguments and cache ranges. [Source and validation evidence](2026-11-19-audio-arena-stage-window-replay.json)

## Olga Flow hazards, stage gates, saved inventory and list windows

Source checkpoint `1d38f7e396` and landing checkpoint `343d27547f` carry 123 source files. The source replay restores Olga Flow hazard constructors and rock queries, typed door and fence resources and wall contact packets, saved inventory loading and rebuild, and the shared equipment and item list constructors and layout. The source audit records 95 historical files and closes 67. The ledger has 1,667 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves 133 fork-only paths and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-saved-inventory-and-equipment` | Saved character inventory, equipment records and player initialization | 23 |
| `great-merge/current/standalone-olga-flow-arena-hazards` | Olga Flow rock radius queries, pursuit rocks, mines and sword waves | 14 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage doors, fences, resource lifetimes and Seabed wall contact packets | 51 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment and item list factories, icon rows and shared window extents | 36 |

Each candidate builds from current upstream with the source for its subsystem. The combined 120-file review build also matches retail. Independent source reviewers checked constructor and callback contracts, resource lifetimes and native layout. [Source and validation evidence](2026-11-19-hazards-gates-inventory-list-replay.json)

## Inventory ownership, Dark Falz cinematics, ambient archives and frontend input

Source checkpoint `496f0e0e02` and landing checkpoint `5483048ad0` carry 47 source files. The source replay restores native inventory construction and exports, typed Dark Falz cinematic owners, ambient model and texture storage, and front-end controller and input contracts. The source audit records 65 historical files and closes 42. The ledger has 1,625 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves 133 fork-only paths and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-saved-inventory-and-equipment` | Native item lists, storage and placement, saved inventory and equipment, and the inventory rebuild lifecycle | 59 |
| `great-merge/current/standalone-dark-falz-cinematic-actors` | Dark Falz cinematic factories, camera and part layouts, emitter state and controller positions | 22 |
| `great-merge/current/standalone-ambient-stage-archives-and-rendering` | Cave and jungle archives and sign rendering, ambient fish and grass resource lifetimes | 14 |
| `great-merge/current/standalone-online-setup-scenes` | Serial, password, PPP and dialing callbacks and native input/display records | 13 |

Each candidate builds from current upstream with the source for its subsystem. The combined 104-file review build also matches retail. The inventory review combines the saved-equipment candidate and the earlier item-placement provider into one direct review on current upstream. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-19-inventory-and-scene-replay.json)

## Camera controllers, mine traps, Gal Gryphon and character creation

Source checkpoint `fdc722c709` and landing checkpoint `b8856a45c9` carry 71 source files. The source replay restores camera resources and letterbox state, native mine trap dispatch and archive owners, Gal Gryphon cinematic and collision owners, and character creation actors. The source audit records 68 historical files and closes 55. The ledger has 1,570 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves 133 fork-only paths and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-camera-and-radar` | Camera views, radar, letterbox state and the shared color renderer | 58 |
| `great-merge/current/standalone-stage-traps-and-motion` | Floor population, trap motion, mine packets and chainsaw resources | 61 |
| `great-merge/current/standalone-gal-gryphon-arena-actors` | Gal Gryphon camera, attack collider, effects and pillar actors | 20 |
| `great-merge/current/standalone-character-creation-actors` | Character creation tags, occupation information and scene effects | 35 |

Each candidate builds from current upstream with the source for its subsystem. The combined 166-file review build also matches retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. The camera candidate overlaps the earlier action palette, ambient archives, and online setup review branches in one file each. Recheck the remaining candidate against the new base as each of those branches lands. [Source and validation evidence](2026-11-19-camera-creation-traps-gryphon-replay.json)

## Memory-card and shop windows, Olga Flow and Seabed objects

Source checkpoint `b97e35686e` and landing checkpoint `5e070f04a0` carry 115 source files. The source replay restores memory-card task and window owners, Olga Flow cinematic actors, shop and bank windows, and Seabed and lab objects. The source audit records 70 historical files and closes 42. The ledger has 1,528 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves 133 fork-only paths and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-memory-card-and-save-windows` | Memory-card checks, character saves, progress messages and backdrop lifetimes | 49 |
| `great-merge/current/standalone-olga-flow-cinematics` | Olga Flow Type 1 and Type 2 appearance and death actors | 35 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment lists, selling, purchase, appraisal and check-room windows | 64 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage doors, fences and contacts, lab geometry and Seabed archives | 65 |

Each candidate builds from current upstream with the source for its subsystem. The combined 205-file review build also matches retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-19-olga-card-shop-seabed-replay.json)

## Model-node capture, worm bosses, Pioneer 2 and Challenge results

Source checkpoint `ac698bf3fa` and landing checkpoint `cab9f349ac` carry 70 source files. The source replay restores model-node capture and output arrays, De Rol Le and Barba Ray body and mine ownership, Pioneer 2 and lobby archives, and Challenge rewards and results windows. The source audit records 86 historical files and closes 41. The ledger has 1,487 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves 133 fork-only paths and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-olga-flow-cinematics` | Olga Flow cinematics and shared model-node capture used by Dark Falz and Pan Arms | 82 |
| `great-merge/current/standalone-derolle-arena-lighting` | De Rol Le and Barba Ray arena lights, body joints, mines and laser handling | 34 |
| `great-merge/current/standalone-stage-transfer-and-seasonal-assets` | Pioneer 2 and lobby archives, seasonal rendering, aircars and ambient objects | 34 |
| `great-merge/current/challenge-and-duel-results` | Challenge and Battle results, reward ownership and player input lifetime | 71 |

Each candidate builds from current upstream with the source for its subsystem. The combined 210-file review build also matches retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-19-node-worm-city-results-replay.json)

## Stage gates, Vol Opt, Guild Card and item resources

Source checkpoint `96b757bd02` and landing checkpoint `18dc561954` carry 116 source files. The source replay restores stage gate and sensor resources, Vol Opt component effects, Guild Card confirmation ownership, and item model and texture archives. The source audit records 52 historical files and closes 31. The ledger has 1,456 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves 133 fork-only paths and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-weapon-factory-registry` | Weapon factory registry, item model and texture archives, projectile render resources and shared Ninja chunk reader | 68 |
| `great-merge/current/standalone-vol-opt-components` | Vol Opt component models, cage and pillars, breakup effects and positional sound | 35 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage door, fence, switch, barrier and sensor resources and collision contacts | 87 |
| `great-merge/current/standalone-main-menu-and-child-windows` | Main menu and child windows, Guild Card receipt and saved-card queue, and shared confirmation lifecycle | 49 |

Each candidate builds from current upstream with the source for its subsystem. The combined 235-file review build also matches retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-20-gate-volopt-guild-item-replay.json)

## Shop stock, Mericarol, quest dialogue and character selection

Source checkpoint `fc413ad485` and landing checkpoint `4d9227e2a7` carry 66 source files. The source replay restores typed shop stock and random pools, Jungle enemy resource and ground-effect ownership, quest dialogue and NPC callers, and character selection and preview requests. The source audit records 50 historical files and closes 26. The ledger has 1,430 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves 133 fork-only paths and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Shop tool and weapon stock, draw pools and sort operations, and related equipment and item list windows | 76 |
| `great-merge/current/standalone-mericarol-and-gibbles-effects` | Mericarol variants, Gibbles ground effects, oriented projectile shadows and shared terrain sounds | 20 |
| `great-merge/current/standalone-online-quest-transfers` | Online quest transfers, quest messages and scroll windows, and NPC dialogue dispatch | 44 |
| `great-merge/current/character-selection-plates` | Character selection plates, scene and preview player ownership, AFS and model preview requests | 49 |

Each candidate builds from current upstream with the source for its subsystem. The combined 182-file review build also matches retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-20-stock-mericarol-quest-selection-replay.json)

## Technique effects, Sinow ground contacts, animated scenery and item help

Source checkpoint `81300401f1` and landing checkpoint `8c5b201858` carry 100 source files. The source replay restores technique effect resources and shared sound pitch calls, Sinow terrain contacts and their ground query, animated stage scenery and debris, and item-help panel ownership. The source audit records 53 historical files and closes 22. The ledger has 1,408 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves 133 fork-only paths and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-technique-effects-and-sounds` | Technique BML and GVM ownership, ring-wave and lightning textures, and all sound-effect pitch callers | 43 |
| `great-merge/current/standalone-ground-effects-and-scenery` | Cached terrain and Sinow contacts, Mericarol and Gibbles ground effects, Cave and Mine resources, and animated stage scenery | 68 |
| `great-merge/current/standalone-action-palette-and-customization` | Action palette and customization, window lifecycle, native item status and help paging | 88 |

Each candidate builds from current upstream with the source for its subsystem. The combined 195-file review build also matches retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-20-tech-sinow-scenery-item-help-replay.json)

## Gol Dragon collision and attacks, Dark Falz phases, stage warps and combat HUD

Source checkpoint `d7da794835` and landing checkpoint `93b2721592` carry 87 source files. The source replay restores Gol Dragon collision and shared attack history, Dark Falz phase dispatch, stage warp resources and the combat HUD target list and its producers. The source audit records 45 historical files and closes 24. The ledger has 1,384 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves 133 fork-only paths and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-gol-dragon-resources-and-formation` | Gol Dragon resources, clone formation, collision and attack effects, with all shared attack-history callers | 50 |
| `great-merge/current/standalone-dark-falz-cinematic-actors` | Dark Falz cinematic actors, controller callbacks, first-form phase dispatch and shared Tenchu effects | 29 |
| `great-merge/current/standalone-stage-transfer-and-seasonal-assets` | Stage transfers and seasonal assets, plus the Forest, Ancient, Jungle, lobby and boss warp resources | 50 |
| `great-merge/current/standalone-camera-and-radar` | Camera and radar, combat target list creation and publishing, lock-on display and technique target copy | 91 |

Each candidate builds from current upstream with the source for its subsystem. The combined 212-file review build also matches retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-20-dragon-falz-warps-hud-replay.json)

## Olga Flow, Recon, stage containers and Short Mail

Source checkpoint `667b23c5e8` and landing checkpoint `57aa0c6e81` carry 78 source files. The source replay restores Olga Flow encounter and battle-effect owners, Recon and Recobox actors, the stage container and event transport owners, and native Short Mail selection and composition. The source audit records 39 historical files and closes 25. The ledger has 1,359 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves 133 fork-only paths and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-olga-flow-arena-hazards` | Olga Flow arena hazards, Form 2 attack dispatch, possession effect and native gravity-ball lifecycle | 36 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy formation and registration, Recon and Recobox effects and actor ownership, and ReconBomb hit and lifetime handling | 84 |
| `great-merge/current/standalone-stage-containers-and-floor-events` | Jungle, Ancient, Forest, Seabed and Ido container resources, drops and floor break events across eight callers | 25 |
| `great-merge/current/standalone-main-menu-and-child-windows` | Main menu and child windows, native Short Mail composition, queue and shared word movement | 80 |

Each candidate builds from current upstream with the source for its subsystem. The combined 213-file review build also matches retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-20-olga-recon-containers-mail-replay.json)

## weapon projectiles, worm arenas, quests and multiplayer selection

Source checkpoint `79a30b1172` and landing checkpoint `beaa4efaa7` carry 109 source files. The source replay restores the shared weapon projectile record and its collision path, De Rol Le and Barba Ray arena resources, quest task ownership, and multiplayer selection. The source audit records 51 historical files and closes 34. The ledger has 1,325 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves the fork-only layer and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-weapon-factory-registry` | Weapon factories and resources, the native full projectile descriptor, actor hit history and card effect targets | 86 |
| `great-merge/current/standalone-derolle-arena-lighting` | De Rol Le and Barba Ray arena lighting, tunnel movement and projection, model and dust resources, and collision | 54 |
| `great-merge/current/standalone-online-quest-transfers` | Quest script and VM ownership, dialogue, native NPC and collision triggers, and shared task lifecycle | 88 |
| `great-merge/current/character-selection-plates` | Character selection plates and preview loads, multiplayer scene lifecycle and guide requests | 56 |

Each candidate builds from current upstream with the source for its subsystem. The combined 268-file review build also matches retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-20-weapon-worm-quest-selection-replay.json)

## audio streaming, Gal Gryphon, stage wrecks and selection requests

Source checkpoint `f4f102ed96` and landing checkpoint `a2d89da7fa` carry 63 source files. The source replay recovers native audio streaming and WAVE decoding, Gal Gryphon arena and lightning resources, Seabed wreck and collision owners, and stored selection requests and preview callers. The source audit records 35 historical files and closes 17. The ledger has 1,308 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves the fork-only layer and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-adx-streaming` | ADX stream files, WAVE decoding, and native file, device and error callback interfaces shared by MFS and DVD | 48 |
| `great-merge/current/standalone-gal-gryphon-arena-actors` | Gal Gryphon actor and arena resources, captured-joint positions, body and particle archives, and native lightning constructors and hit callback | 32 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage doors and fences, placement and actual wall fade, shared contact work and Seabed wreck factories and collision models | 95 |
| `great-merge/current/character-selection-plates` | Character selection and preview, native saved-character requests and split-screen camera consumers, and the serialized appearance display index | 67 |

Each candidate builds from current upstream with the source for its subsystem. The combined 235-file review build also matches retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-20-audio-gryphon-wreck-selection-replay.json)

## Combined stage doors, weather and resource review

The 128-file local stage review at `0d7017a5cf` combines the 95-file doors, fences and Seabed patch with the earlier stage weather and resource patch. The only source conflict was the Seabed wall. It keeps the native constructor, model bounds and render fields along with the named debris template and typed archive lifetime. Rain ownership consolidates two existing source units. The stage branch and the 268-file combined review build reproduce retail and pass strict linkage with all 27,572 functions and 1,758,510 data bytes accounted for. [Stage consolidation evidence](2026-11-20-stage-weather-consolidation.json)

## trade windows, linked enemy actors and downloadable quest cache

Source checkpoint `c6908ed402` and landing checkpoint `13400d6a38` carry 41 source files. The source replay recovers native trade menus and request objects, linked Bal Claw and Pan Arms actors, and downloadable quest cache records. The source audit records 31 historical files and closes 8. The ledger has 1,300 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves the fork-only layer and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-main-menu-and-child-windows` | Main menu and Short Mail, Trade request lifecycle, three Trade child factories, confirmation dialogs and shared log teardown | 91 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy registration and Recon formations, Bal Claw split and join state, Pan Arms child placement and native attack collider | 95 |
| `great-merge/current/standalone-online-quest-transfers` | Online quest transfers and dialogue, quest scripts and native cache slot, text and item records | 96 |
| `great-merge/current/standalone-adx-streaming` | ADX and WAVE decoding, CVFS disc and memory devices, ADXF disc archives and movie module lifetime | 116 |

Each candidate builds from current upstream with the source for its subsystem. The combined 582-file review build also matches retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-20-trade-actors-quest-cache-replay.json)

## Terrain geometry, equipment windows, Morfos and audio streams

Source checkpoint `8e7c46d463` and landing checkpoint `14cb2d035f` carry 46 source files. The source replay recovers native terrain collision, equipment and item detail windows, Morfos actors, and ADX stream file and encoder contracts. The source audit records 29 historical files and closes 16. The ledger has 1,284 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves the fork-only layer and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-adx-streaming` | ADX, WAVE, disc archives and movies, native stream files across playback, archive and LSC consumers, and encoder layout | 117 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy registration and formations, Bal Claw and Pan Arms, Morfos body and projectile, and the common camera capture provider | 111 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage doors, weather, fences and Seabed wrecks, and native terrain registration, collision models and ground and wall candidate queries | 199 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Main-menu and Trade lifetimes, equipment and item lists, native help snapshots, Short Mail and related child windows | 167 |

The menu candidate combines the previously separate Trade and equipment reviews. Each candidate builds from current upstream with the source for its subsystem. The combined 722-file review build also matches retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-20-geometry-equipment-morfos-audio-replay.json)

## Inventory, status displays, enemy battle stats and floor placement

Source checkpoint `67c732c9bc` and landing checkpoint `0054cb35e0` carry 89 source files. The replay restores native inventory lookup and removal, screen and gauge records, enemy stat providers, and floor selection and decoration placement. The source audit records 31 historical files and closes 18. The ledger has 1,266 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves the fork-only layer and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-saved-inventory-and-equipment` | Saved inventory, stack lookup, item ownership and removal | 60 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Trade, equipment, status and item list windows | 183 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy formations, capture, battle stats and collision bodies | 117 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage doors, traps, floor placements, scene assets and geometry | 263 |

Status display is part of the equipment and Trade review. Floor placement and decoration are part of the stage review. The saved inventory review covers its separate game-state and persistence owners. The eight review groups build together across 834 files and also match retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-20-inventory-status-enemy-floor-placement-replay.json)

## Technique parameters, message history, Dragon behavior and Challenge floors

Source checkpoint `9689df28ef` and landing checkpoint `fdeba51c26` carry 94 source files. The replay recovers typed technique and power tables, native message history and window ownership, shared Dragon render and motion state, and Challenge floor flags and event storage. The source audit records 40 historical files and closes 25. The ledger has 1,241 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves the fork-only layer and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-technique-effects-and-sounds` | Technique casts, parameters, effects and sounds | 55 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Trade, equipment, status and message-log windows | 200 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy formations, combat stats, and Dragon and Gol Dragon behavior | 132 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stages, traps, geometry, decoration and Challenge floor sync | 274 |

Message history is part of the equipment and Trade review. Challenge floor sync is part of the stage review. Dragon and Gol Dragon share the enemy review. Technique calculation, positioning, effects and sound are reviewed together. The nine review groups build together across 890 files and also match retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-20-techniques-message-log-dragon-challenge-replay.json)

## Camera views, Hunter’s Guild menus, Flower actors and Online Ending

Source checkpoint `b7f13fbe55` and landing checkpoint `4a94501005` carry 91 source files. The replay recovers camera position and target banks, shared confirmation menus and offline quest callbacks, the Flower family’s projectile and render owners, and the Online Ending scene. The source audit records 26 historical files and closes 19. The ledger has 1,222 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves the fork-only layer and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-camera-and-radar` | Camera views, radar and combat target ownership | 104 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage objects, doors, warp, seasonal assets, Challenge floors and Online Ending | 306 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy formations, battles, Dragon and the Flower family | 151 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment, Trade, chat history, Guild menus and shared confirmations | 223 |

Guild and shared confirmation ownership join the window review. Flower actors join the enemy review. The ending scene, doors, warps and seasonal assets share the stage review. Camera views, radar and their targeting and draw interfaces form a separate review. The ten groups build together across 1007 files and also match retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-20-camera-guild-flower-ending-replay.json)

## Symbol shortcuts, Vol Opt and stage particle emitters

Source checkpoint `061de36612` and landing checkpoint `707ba291bc` carry 60 source files. The replay recovers saved symbol shortcut and keyboard lifetimes, Vol Opt model breakup parameters and their encounter callers, and the particle parameter banks and timed factories. The source audit records 23 historical files and closes 8. The ledger has 1,214 records awaiting full source comparison.

All 90 original data ranges remain accounted for. The working fork preserves the fork-only layer and passes 294 tooling tests and 11 layer tests. Source and working builds reproduce the retail DOL and retain the recorded code and data coverage.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage objects, doors, floor events, seasonal assets and particle emitters | 355 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy and boss encounters, Flower behavior and Vol Opt model breakup | 167 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment and Trade menus, chat history, Symbol Chat and shortcuts | 245 |

Symbol Chat and shortcuts join the equipment and menu review. Vol Opt joins the enemy encounter review. Timed emitters and particle banks join the stage review. The ten groups build together across 1085 files and also match retail. Independent source reviewers checked callable signatures, real receivers, resource lifetimes and native layout. [Source and validation evidence](2026-11-20-shortcut-volopt-particle-replay.json)

## Weapon motion, action palette, Olga Flow and stage lifetimes

Source checkpoint `a1b6b22247` and landing checkpoint `72a9716d9c` carry 84 changed source files. The replay recovers native weapon muzzle positions and motion, palette drawing and equipment slot ownership, Olga Flow phase and plot lifetimes, and stage container and trap receivers. The audit covers 41 historical records and closes 24. The ledger has 1,190 records awaiting full source comparison.

All 90 original data ranges remain accounted for. Source and working builds reproduce the retail DOL and retain recorded code and data coverage. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage containers, traps, floor events, seasonal assets and particle emitters | 374 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment, inventory, action palette, chat and shortcuts | 317 |
| `great-merge/current/standalone-olga-flow-cinematics` | Olga Flow arena hazards, cinematics and phase actor lifetimes | 107 |
| `great-merge/current/standalone-weapon-factory-registry` | Weapon factories, muzzle vectors and signed clamped motion in weapons and effects | 120 |

Stage and UI changes enlarge their existing reviews. Olga Flow groups arena hazards and cinematics with the phase actors. Weapon muzzle, motion and effect changes join the weapon factory review. The twelve groups build together across 1,309 files and reproduce the retail DOL. Independent source reviewers checked the changed layouts, call signatures and lifetime ordering. [Source and validation evidence](2026-11-20-weapon-palette-olga-stage-lifetimes-replay.json)

## Photon Blast resources, menu rows, quest matching and enemy registration

Source checkpoint `bbd69fb8de` and landing checkpoint `029e79b51f` carry 114 changed source files. The replay recovers the shared Photon Blast archive and camera, menu row and text rendering, downloadable quest matching, and typed collision registration and actor lookup. The audit covers 98 historical records and closes 0. The ledger has 1,190 records awaiting full source comparison.

All 90 original data ranges remain accounted for. Source and working builds reproduce the retail DOL and retain recorded code and data coverage. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-technique-effects-and-sounds` | Technique effects, Photon Blast sequences, archive slots and camera | 77 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy formations, collisions, registration and actor lookup | 184 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment, palette, shared menu row alignment and text measurement | 337 |
| `great-merge/current/standalone-online-quest-transfers` | Online quest transfers, download matching, scored text records and node ownership | 96 |

The technique, equipment window, online quest, and enemy formation reviews include these changes. The twelve groups build together across 1,352 files and reproduce the retail DOL. Independent source reviewers checked the changed layouts, call signatures and lifetime ordering. [Source and validation evidence](2026-11-20-photon-menu-quest-enemy-replay.json)

## Saved-character lookup, quest scoring, terminals, choice rows and Olga Flow

Source checkpoint `68b899d7b1` and landing checkpoint `752581cd62` carry 89 changed source files. The replay recovers saved-character lookup and its callers, typed quest scores, stage terminal owners, shared choice rows, and Olga Flow action state. The audit covers 38 historical records and closes 4. The ledger has 1,186 records awaiting full source comparison. The code-owner index also maps 46 historical rows to their current translation units by retail address.

All 90 original data ranges remain accounted for. Source and working builds reproduce the retail DOL and retain recorded code and data coverage. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/character-selection-plates` | Character selection and previews, memory-card windows, and its shared saved-record lookup | 127 |
| `great-merge/current/standalone-online-quest-transfers` | Online quest transfers, native scoring, and text node ownership | 96 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage objects, terminals, contact and trap behavior, archives and UV scrolling | 387 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment windows, palette, shared menu layout and label-value choice rows | 350 |
| `great-merge/current/standalone-olga-flow-cinematics` | Olga Flow arena, cinematics and typed Plot and form action messages | 110 |

The character selection, online quest, stage, equipment window, and Olga Flow reviews include these changes. The twelve groups build together across 1,410 files and reproduce the retail DOL. Independent source reviewers checked the changed layouts, call signatures and lifetime ordering. [Source and validation evidence](2026-11-20-character-save-quest-stage-menu-olga-replay.json)

## Item parameters, warp materials, window drawing and Dragon arena state

Source checkpoint `5dc1c07425` and landing checkpoint `e4b6544f8b` carry 94 changed source files. The replay recovers shared item parameter lookups, warp material selection, window part drawing, and the Dragon arena and crater owners. The audit covers 58 historical records and closes 5. The ledger has 1,181 records awaiting full source comparison.

All 90 original data ranges remain accounted for. Source and working builds reproduce the retail DOL and retain recorded code and data coverage. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-saved-inventory-and-equipment` | Saved inventory and equipment, typed item parameters and their archive owner | 72 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment, dialogue, menu layout and typed shared window-part rendering | 359 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage objects, terminals, warps, and shared Ginja material selection | 392 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy formations, actor registration, Dragon arena resources, crater and floor lifetimes | 190 |

The inventory, stage, equipment window and enemy encounter reviews include these changes. The twelve groups build together across 1,433 files and reproduce the retail DOL. Independent source reviewers checked the changed layouts, call signatures and lifetime ordering. [Source and validation evidence](2026-11-20-item-warp-window-dragon-replay.json)

## Equipment checks, window lifecycle, Challenge graves and enemy archives

Source checkpoint `b45ac1bec4` and landing checkpoint `c5256a3040` carry 59 changed source files. The replay recovers the original equipment check, window part updates and teardown, Challenge graves, and Mericarol and Gibbles resources. The audit covers 39 historical records and closes 4. The ledger has 1,177 records awaiting full source comparison.

All 90 original data ranges remain accounted for. Source and working builds reproduce the retail DOL and retain recorded code and data coverage. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-saved-inventory-and-equipment` | Saved inventory and original weapon, armor, unit, mag and Meseta equipment requirements | 81 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment and item windows with the shared part update and teardown lifecycle | 367 |
| `great-merge/current/standalone-mericarol-and-gibbles-effects` | Shared resource and action tables, normal and low-detail models, and collision data for Mericarol and Gibbles | 23 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage doors, fences, contacts and the Challenge tombstone placement and save lifecycle | 396 |

The inventory, stage, equipment window and enemy encounter reviews include these changes. All 13 groups build together across 1,447 files and reproduce the retail DOL. Independent source reviewers checked the changed layouts, call signatures and lifetime ordering. [Source and validation evidence](2026-11-20-equipment-layout-tombstone-enemy-replay.json)

## Window construction, Dark Falz, stage archives and card loading

Source checkpoint `33ae8206e0` and landing checkpoint `48370cd352` carry 57 changed source files. The replay restores shared window layout construction, Dark Falz form and fade ownership, stage scenery archives and memory-card loading interfaces. The audit covers 29 historical records and closes 8. The ledger has 1,169 records awaiting full source comparison.

All 90 original data ranges remain accounted for. Source and working builds reproduce the retail DOL and retain recorded code and data coverage. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/character-selection-plates` | Character selection plates and the full memory-card load, filename, capacity, result and SDK contract | 137 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment and item windows, shared variable-length layout initialization and symbol-chat callers | 370 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage scenery archives, Bind motion, sky scene and full Ginja object registry | 404 |
| `great-merge/current/standalone-dark-falz-cinematic-actors` | Dark Falz scene, fade and phase handoff, including the shared Olga Flow fade | 42 |

The character selection, stage, equipment window and Dark Falz reviews include these changes. All 14 groups build together across 1,491 files and reproduce the retail DOL. Independent source reviewers checked the changed layouts, call signatures and lifetime ordering. [Source and validation evidence](2026-11-20-window-falz-stage-card-replay.json)

## Float copies, network threads, Sinow textures and Ancient scenery

Source checkpoint `64f113bad3` and landing checkpoint `c9bebf2d29` carry 85 changed source files. The replay restores the shared two-float routine, native network thread pool, Sinow appearance lifetimes and Ancient animated model registry. The audit covers 49 historical records and closes 4. The ledger has 1,165 records awaiting full source comparison.

All 90 original data ranges remain accounted for. Source and working builds reproduce the retail DOL and retain recorded code and data coverage. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-network-thread-dispatch` | Native network thread pool, SDK callback lifetime and all five dispatcher and transport workers | 11 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment and item windows plus the shared two-float copy provider and callers | 406 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Ancient container archives and the complete animated stage model registry | 408 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Sinow and Stelth shared texture lifetime and appearance archives | 195 |

The network, stage, equipment window and enemy formation reviews include these changes. All 15 groups build together across 1,532 files and reproduce the retail DOL. Independent source reviewers checked the changed layouts, call signatures and lifetime ordering. [Source and validation evidence](2026-11-20-float-thread-sinow-ancient-replay.json)

## Reverse Technique textures, window text entries, Gyaranzo and animated NPC models

Source checkpoint `59c4b59f78` and landing checkpoint `fcd39b68df` carry 58 changed source files. The replay restores the Reverse Technique texture and picture owners, native window text-entry lifecycle, Gyaranzo missile hit routing and shared kind-1 NPC animation bindings. The audit covers 25 historical records and closes 9. The ledger has 1,156 records awaiting full source comparison.

All 90 original data ranges remain accounted for. Source and working builds reproduce the retail DOL and retain recorded code and data coverage. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-technique-effects-and-sounds` | Technique effects and sound dispatch plus the Reverse Technique scene texture, child task and picture lifetime | 84 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment and item windows plus the type-3 text entry, shared setter, rendering and callback lifetime | 409 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy formation and appearance resources plus Gyaranzo archive, missile volley and hit routing | 199 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage interactions and resource owners plus all kind-1 and kind-3 animated model registrations | 435 |

The technique, stage, equipment window and enemy formation reviews include these changes. All 15 groups build together across 1,554 files and reproduce the retail DOL. Independent source reviewers checked the changed layouts, call signatures and lifetime ordering. [Source and validation evidence](2026-11-20-text-gyaranzo-npc-reverse-tech-replay.json)

## Challenge state, frontend cursor, Dubchik and map warp destinations

Source checkpoint `2e756b074f` and landing checkpoint `7ddd591097` carry 58 changed source files. The replay restores common Challenge window/state ownership, the frontend cursor contracts, Dubchik archive and lightning lifetimes, and the shared warp destination and collision records. The audit covers 18 historical records and closes 8. The ledger has 1,148 records awaiting full source comparison.

All 90 original data ranges remain accounted for. Source and working builds reproduce the retail DOL and retain recorded code and data coverage. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Window and item handling plus real Challenge window, state and player record ownership | 422 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy formations and appearance plus Dubchik resource, attack and lightning lifetime | 205 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage interactions and animations plus map warp destinations, collision bodies and shared contact callers | 438 |
| `great-merge/current/character-selection-plates` | Character selection, card screens and the shared frontend cursor and controller lifetimes | 152 |

The equipment window, character selection, enemy formation and stage reviews include these changes. All 15 groups build together across 1,580 files and reproduce the retail DOL. Independent source reviewers checked the changed layouts, call signatures and lifetime ordering. [Source and validation evidence](2026-11-20-challenge-cursor-dubchik-warp-replay.json)

## Challenge4P, keyboard composition, Moja and map warp commands

Source checkpoint `8263d90f97` and landing checkpoint `fb03d4417b` carry 26 changed source files. The replay restores native Challenge4P state, keyboard text and conversion state, the Moja archive and sampled punch, and the original intra-map warp command interfaces. The audit covers 18 historical records and closes 5. The ledger has 1,143 records awaiting full source comparison.

All 90 original data ranges remain accounted for. Source and working builds reproduce the retail DOL and retain recorded code and data coverage. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Windows, item handling and Challenge state plus four-player Challenge and keyboard input/composition | 432 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy formations, appearance and encounters plus Moja combat, resources and placement | 211 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage interactions, animated models and warp collision plus the shared intra-map warp command and callers | 441 |

The equipment window review combines Challenge4P and keyboard changes. The enemy formation and stage reviews carry their additional scopes. All 15 groups build together across 1,594 files and reproduce the retail DOL. Independent source reviewers checked the changed layouts, call signatures and lifetime ordering. [Source and validation evidence](2026-11-20-challenge4p-keyboard-moja-warp-replay.json)

## Texture binding, spatial sound and NPC companion control

Source checkpoint `d77a1ec95f` and landing checkpoint `e6cf1dcaec` carry 45 changed source files. The replay types the guarded renderer texture setter, the spatial voice and sound-bank interfaces, and the player-owned NPC companion record. The audit covers 213 historical records and closes 10. The ledger has 1,133 records awaiting full source comparison.

All 90 original data ranges remain accounted for. Source and working builds reproduce the retail DOL and retain recorded code and data coverage. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Changed files |
| --- | --- | ---: |
| `great-merge/current/texture-binding` | Shared Ginja texture-list binding and the null-guarded caller interface | 375 |
| `great-merge/current/standalone-adx-streaming` | ADX streaming, sound-bank readiness and spatial voice requests | 122 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage interactions and warp commands, with player-owned NPC companion control | 446 |

The texture-binding review applies the shared renderer interface across systems. The existing ADX and stage reviews include the additional sound and companion-control work. All 16 groups build together across 1,691 files and reproduce the retail DOL. Independent source reviewers checked the changed layouts, call signatures and lifetime ordering. [Source and validation evidence](2026-11-20-texture-binding-sound-npc-replay.json)

## BML archives, window ownership, enemy models and floor transitions

Source checkpoint `42a5d1f9f6` and landing checkpoint `3473e00075` carry 57 changed source files. The replay uses native BML chunk and storage types, one active window controller, typed Bringer and Canadin resource records, and one floor-transition state. The audit covers 18 historical records and closes 4. The ledger has 1,129 records awaiting full source comparison.

All 90 original data ranges remain accounted for. Source and working builds reproduce the retail DOL and retain recorded code and data coverage. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Files from review base |
| --- | --- | ---: |
| `great-merge/current/standalone-bml-model-and-texture-accessors` | Shared BML model and texture accessors and the archive chunk allocator | 161 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage and warp interactions, with shared floor-transition state and commands | 455 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment and frontend windows, with active controller lifetime and child slots | 452 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy registration and formations, including Bringer and Canadin archive and render records | 214 |

The BML review uses the existing texture-binding review as its prerequisite. The existing window, enemy and stage reviews carry the associated ownership changes. All 17 groups build together across 1,731 files and reproduce the retail DOL. Independent source reviewers checked the changed layouts, call signatures and lifetime ordering. [Source and validation evidence](2026-11-20-archive-window-enemy-floor-replay.json)

## Native array allocation and character creation

Source checkpoint `a9ac4896da` and landing checkpoint `af250600bf` carry 1 changed source files. The source removes the last retired array allocation declarations. The local review queue now uses the native storage operators across the existing callers. The audit covers 44 historical records and closes 40. The ledger has 1,089 records awaiting full source comparison.

All 90 original data ranges remain accounted for. Source and working builds reproduce the retail DOL and retain recorded code and data coverage. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Files from review base |
| --- | --- | ---: |
| `great-merge/current/standalone-native-array-runtime` | Native array allocation, release, callers and runtime destruction | 156 |
| `great-merge/current/character-selection-plates` | Character selection previews and character creation selector, tag and backdrop actors | 182 |

The character review combines selection previews with the selector, tag and backdrop actors. The array review covers both storage operators, their callers and the runtime array destructor. All 18 groups build together across 1,790 files and reproduce the retail DOL. The character reviews retain both current constructor signatures in the shared metadata. [Source and validation evidence](2026-11-20-array-character-completeness-replay.json)

## Olga Flow plot state dispatch

Source checkpoint `34ed7bfb29` and landing checkpoint `a91036891c` carry 3 changed source files. The producer and dispatcher now share one nine-state table with the original member-function callbacks and record layout. The audit covers 3 historical records and closes 1. The ledger has 1,088 records awaiting full source comparison.

All 90 original data ranges remain accounted for. Source and working builds reproduce the retail DOL and retain recorded code and data coverage. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Files from review base |
| --- | --- | ---: |
| `great-merge/current/standalone-olga-flow-cinematics` | Olga Flow cinematic actors and shared plot state dispatch | 111 |

The change extends the existing Olga Flow cinematic review. All 18 groups build together across 1,791 files and reproduce the retail DOL. The producer and consumer retain the original callback slots, transition order and linked table address. [Source and validation evidence](2026-11-20-olga-plot-dispatch-replay.json)

## Arena resources and frontend ownership

Source checkpoint `a34560829c` and landing checkpoint `3c36d1e4db` carry 9 changed source files. Barba Ray owns its model, texture and motion accessors. Gol Dragon uses its inherited scale in the fade path, and the frontend uses the actual load controller and its signed field. The audit covers 11 historical records and closes 7. The ledger has 1,081 records awaiting full source comparison.

All 90 original data ranges remain accounted for. Source and working builds reproduce the retail DOL and retain recorded code and data coverage. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Files from review base |
| --- | --- | ---: |
| `great-merge/current/standalone-derolle-arena-lighting` | De Rol Le and Barba Ray arena lighting, tunnel movement, collision and native archive ownership | 55 |
| `great-merge/current/standalone-gol-dragon-resources-and-formation` | Gol Dragon arena resources, formation, targeting and inherited draw scale | 50 |
| `great-merge/current/character-selection-plates` | Character selection, previews, creation actors and the related online setup scenes | 190 |

Two arena reviews enter the combined queue. The existing character review now also covers the related online setup scenes. All 20 groups build together across 1,848 files and reproduce the retail DOL. The shared tunnel methods and the typed pointer reset survive the arena overlap, together with the existing array, BML and renderer interfaces. [Source and validation evidence](2026-11-20-arena-frontend-ownership-replay.json)

## Memory runtime, gameplay random and window ownership

Source checkpoint `08d141b527` and landing checkpoint `c4320e06bd` carry 13 changed source files. The main phase dispatcher and all 66 callback slots now use the shared table types. The shop review uses the real delete, withdrawal and judgment window constructors and their typed sequence owners. The source audit covers 11 historical records and closes 9. The ledger has 1,072 records awaiting full comparison.

The full source, working fork and combined review each reproduce the retail DOL. All 90 original data ranges remain accounted for. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Files from review base |
| --- | --- | ---: |
| `great-merge/current/standalone-native-array-runtime` | Native array allocation, overlapping byte and word copies, and nullable heap release | 257 |
| `great-merge/current/standalone-gameplay-random` | Gameplay random ratios and their real actor receivers | 29 |
| `great-merge/current/character-selection-plates` | Character creation, character selection, online setup and the shared frontend phase table | 192 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment and item windows, including the three shop constructors and two sequence owners | 455 |

The memory review extends the native array group with overlapping byte and word copies and nullable release. The gameplay random group joins the review queue. The frontend phase and typed shop updates extend existing groups, taking the combined review to 1,880 files across 21 groups. [Source and validation evidence](2026-11-20-memory-gameplay-review-replay.json)

## Challenge and duel results, shop icons, enemy appearance and stage proximity

Source checkpoint `f12da87ad3` and landing checkpoint `d0634238de` carry 24 changed source files. The result window retains the fork’s exact inline controls. The shop uses the native item-icon lifecycle, and its keep and deposit windows use the signed message interface. Berura and Dolm/Olm retain their real punch, fade, archive and animation fields. Room and proximity triggers use the original vectors and player calls. The audit covers 22 historical records and closes 13. The ledger has 1,059 records awaiting full comparison.

The full source, working fork and combined review reproduce the retail DOL. All 90 original data ranges remain accounted for. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Files from review base |
| --- | --- | ---: |
| `great-merge/current/challenge-and-duel-results` | Challenge and duel results, standings, action locks and shared page lifetime | 71 |
| `great-merge/current/standalone-enemy-registration-and-formations` | Enemy registration, formation and Berura and Dolm/Olm appearance | 217 |
| `great-merge/current/standalone-stage-doors-fences-and-contacts` | Stage doors, fences, room assignment, and area trigger checks | 462 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment and item windows, shop messaging, icon ownership and inventory | 489 |

The standalone Challenge and duel results branch joins the queue. The enemy, stage and item-window reviews grow in place, taking the combined review to 1,916 files across 22 groups. The standalone city door calls the area getter with its actual player. The queue retains its existing typed text, inventory, allocation and animated model registry interfaces. [Source and validation evidence](2026-11-20-results-appearance-stage-replay.json)

## Network datagrams, player slots and native subsystem ownership

Source checkpoint `296144636a` and landing checkpoint `df41bdffe2` carry 144 changed source files. Network transport uses typed packet descriptors and the original signed socket event signatures. The player lookup shares the original twelve-slot table and rejects the sentinel and out-of-range inputs. Vol Opt uses its original model nodes, arena placement and owning actor. Challenge status pages pass the active record set and retain their native page indicators. The audit covers 18 historical records and closes 13. The ledger has 1,046 records awaiting full comparison.

The full source, working fork and combined review reproduce the retail DOL. All 90 original data ranges remain accounted for. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Files from review base |
| --- | --- | ---: |
| `great-merge/current/standalone-network-datagrams-and-packet-pool` | Network datagrams, packet pool and socket callback types | 64 |
| `great-merge/current/standalone-player-slot-registry` | Player registry storage, lookup and compatible game callers | 110 |
| `great-merge/current/standalone-vol-opt-components` | Vol Opt components, arena placement and model-node ownership | 39 |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Item windows, status pages, indicators and Challenge record readers | 494 |

The packet and registry reviews enter the queue. The widened Vol Opt and equipment review branches use their exact native owner interfaces. The combined queue now covers 1,994 files across 25 groups. The joint status record owner uses the shared player lookup, and the working fork retains its host TCP declarations and guards in the fork layer. [Source and validation evidence](2026-11-20-datagram-registry-subsystem-replay.json)

## Consolidated network runtime review

The datagram and packet pool branch also carries the verified native thread dispatch. The grouped standalone review `23bb9724a5` covers 66 paths and reproduces the retail DOL. Every changed source and header blob, all 23 edited symbol locations and the force-active rename agree with the existing queue. Queue `f5a3161449` has the same source tree and covers 1,994 files across 24 review groups. [Validation evidence](2026-11-20-network-runtime-review-bundle.json)

## Native startup, player lookup, Dark Falz and window layouts

Source checkpoint `20565490cd` and landing checkpoint `1b4a9a34b4` carry 82 changed source files. Startup now calls the actual argumentless dispatcher and consistently consumes the signed result. The player registry uses the original narrowed IDs and passes the selected player to the Slime and revive state checks. Dark Falz actors share their native archive and the controller owns the Uso Tower pointer. The equipment and status review also carries the window base and derived layouts through their active owners. The audit covers 22 historical records and closes 10, leaving 1,036 awaiting full comparison.

The full source, working fork and combined review reproduce the retail DOL. All 90 original data ranges remain accounted for. The working fork passes 294 tooling tests and 11 layer tests.

| Local review branch | Scope | Files from review base |
| --- | --- | ---: |
| `great-merge/current/standalone-equipment-and-item-list-windows` | Equipment, item windows, status pages and native window layouts | 522 |
| `great-merge/current/standalone-network-datagrams-and-packet-pool` | Network datagrams, packet pooling, thread dispatch and signed startup | 70 |
| `great-merge/current/standalone-player-slot-registry` | Player slot registry and explicit legacy lookup callers | 167 |
| `great-merge/current/standalone-dark-falz-cinematic-actors` | Dark Falz actors, shared archive, and Uso Tower lifetime | 51 |

The four updated reviews are part of the 2,039-file queue across 24 groups. The 70-file network runtime and 462-file stage reviews also reproduce retail in a separate joint build on the current upstream base. [Source and validation evidence](2026-11-20-startup-registry-and-falz-replay.json)

## Network and stage reviews open upstream

The 61-file network runtime is open at `7301eadf78`. PR #334 is ready for review at `9f03861d41` across 487 files. Its attribution update preserves the source tree tested at `aa70392a37`. Use `9f03861d41` for published ancestry. The earlier joint build at `98cf31c3df` reproduces retail using the network head and the stage accessor head `ec0fac8435`. [#333](https://github.com/zeroz41/pso-decomp/pull/333) [#334](https://github.com/zeroz41/pso-decomp/pull/334) [Source-equivalent matching CI](https://github.com/zeroz41/pso-decomp/actions/runs/44813613964)

The stage cleanup puts the area accessor on TObjPlayer, uses shared typed live floor-row getters and the shared player lookup declaration, and uses the Dubchik class layout for its attachment helper. The review handoff verifies the standalone against the previous PR head and upstream with 2,448 source objects linked. Its historical-fork comparison accounts for a net 2,386-byte change in the total-data diagnostic through 2,549 omitted alignment bytes and 163 bytes of added coverage. It records zero exact-function, linked-function, non-padding-data, or linked-data losses. [Validation record](2026-11-20-stage-334-review.json)

The stage cleanup is replayed on canonical `195c6e16c2` and queue `6f12bb5fe8`. The 20 canonical and 10 queue overlaps were reconciled by source owner. Both trees reproduce retail and pass strict coverage. The stage receipt records the current player and floor contracts and the exact Dubchik owner.

Keep upstream’s existing names for functions, types, and fields wherever the fork uses the same entity. Remove name-only changes during review preparation. Use the established upstream type when consolidating duplicate views and describe any resulting signature or linkage change in the PR.

The player registry review follows the stage series because they share active source files. The equipment and window review follows the registry.

The published #334 cleanup at `aa70392a37` restores four upstream function names and 15 field names across 32 files. It reproduces retail with 2,448 linked source objects. The comparison with master reports 158 function label changes, including corrected types and owners. [Naming audit](2026-11-20-stage-334-review.json)

## Quest loading, companion saves and enemy fades

Source `b12c724cb3` and landing checkpoint `099f1fd992` carry 74 changed files. The quest review adds the native loader interface, particle actors, and shop callers. The saved inventory review adds the companion template and item export owners. The enemy review restores typed opacity and camera fade calls. The audit closes 29 historical comparisons and leaves 1,007 open.

The 2,044-file review queue covers 24 groups. The canonical source and working fork reproduce retail. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-quest-npc-fade-replay.json)

## Native platform and game source

Source `dbb9801fa6` and landing checkpoint `d07c474a46` carry 51 changed files. This batch covers FlyNest placement and factory, native PPP frame and wire-header contracts, memory-card file and lobby picture contracts, multilingual Word Select and native DD widgets. The audit closes 16 historical comparisons and leaves 991 open.

The PPP frame review starts from the validated #333 head and retains the existing buffer helper symbol. The standalone Word Select review covers message formatting, archive records and shared geometry. The combined queue also carries the DD widgets that depend on the equipment review’s window layout.

The 2,074-file review queue covers 26 groups. The canonical source and working fork reproduce retail. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-native-boundary-replay.json)

## Stage cleanup replay and owner corrections

Source `195c6e16c2` and landing checkpoint `6664106132` carry 51 changed files. This batch covers the reviewed stage accessors and Dubchik attachment owner, equipment and Symbol Chat name restoration, GoGo Ball counter and prompt receiver. The audit closes 1 historical comparisons and leaves 990 open.

The 2,085-file review queue covers 26 groups. The canonical source and working fork reproduce retail. The equipment review restores seven upstream names or linkage spellings. Compiler relocations confirm both Symbol Chat overloads. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-stage-owner-replay.json)

## Native source recovery across subsystems

Source `89b1ccecd7` and landing checkpoint `40d3c9ff83` carry 33 changed files. This batch covers ADXF command history, Gi Gue flight and attack effects, Ginja texture loading and resource callers, main-menu controllers and single-player backdrop. The audit closes 14 historical comparisons and leaves 976 open.

The 2,106-file review queue covers 27 groups. The canonical source and working fork reproduce retail. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-native-history-replay.json)

## Resources, entity groups and window ownership

Source `9a27677f86` and landing checkpoint `3986c9a808` carry 33 changed files. This batch covers Ginja texture uploads and native font state, Dark Gunner group control, the downloadable quest dictionary, speech balloons and Word Select dispatch. The audit closes 15 historical comparisons and leaves 961 open.

The 2,112-file review queue covers 27 groups. The canonical source and working fork reproduce retail. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-scoped-resource-replay.json)

The standalone Ginja upload review covers 18 files. The direct patch retains upstream spellings and can be rebuilt with the stage changes after resolving 2 overlapping files. The wider archive and model changes remain in the combined queue.

## Native archive and gameplay dispatch recovery

Source `6bb217d874` and landing checkpoint `a2789f20c5` carry 51 changed files. This batch covers BML resource access and archive loading, Dark Gunner dispatch and lightning, wall collision and ground transforms, main menus, speech balloons and Word Select. The audit closes 8 historical comparisons and leaves 953 open.

The 2,114-file review queue covers 28 groups. The canonical source and working fork reproduce retail. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-archive-and-dispatch-replay.json)

The local BML review covers 161 files from upstream master and retains the upstream renderer spellings. BML and Ginja uploads also form a validated 179-file loading review on upstream master. The 150-file main-menu review carries the speech-balloon and native Word Select formatter changes on the existing main-menu branch. The review restores 20 upstream spellings across the enemy, collision and menu branches.

## Stage-compatible loading and native subsystem recovery

Source `081bc64d52` and landing checkpoint `d08a56367d` carry 23 changed files. This batch covers Chaos Bringer rush and effects, Ancient container spawn and effects, HUD warnings, timer and radar map. The audit closes 17 historical comparisons and leaves 936 open.

The 2,128-file review queue covers 29 groups. The canonical source and working fork reproduce retail. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-stage-load-and-native-replay.json)

The 178-file loading review at `69ee8013f8` builds on the exact stage review tip. It resolves 59 overlapping paths and reproduces retail with the same linked coverage as both prior independent reviews.

## Compiler directives and native subsystem recovery

Source `fbb99312db` and landing checkpoint `858ca99494` carry 24 changed files. This batch covers redundant compiler directives, Party Status, HUD providers and player lock-on, Barba Ray actor and action packets, stage Symbol Chat presets and packet ownership. The audit closes 11 historical comparisons and leaves 925 open.

The 2,141-file review queue covers 30 groups. The canonical source and working fork reproduce retail. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-pragma-and-native-replay.json)

The compiler cleanup from fork PR #622 removes 108 directives across 12 files in the review queue. Canonical source needed 23 removals across six files after earlier cleanup. Both builds reproduce retail with unchanged coverage and linkage. The wider fork cleanup is tracked by compilation unit in the validation record.

## Projectile parameters and native subsystem recovery

Source `bd91f0b4b6` and landing checkpoint `2cfacdae70` carry 31 changed files. This batch covers original projectile technique parameters, Barba Ray laser and tentacle ownership, native Lock-On provider and player HUD ownership, mine, placement and trap effect ownership. The audit closes 13 historical comparisons and leaves 912 open.

The 2,146-file review queue covers 31 groups. The canonical source and working fork reproduce retail. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-technique-projectile-and-native-replay.json)

## Calendar, protocol and native subsystem recovery

Source `58ee62fc9a` and landing checkpoint `1c715e994f` carry 34 changed files. This batch covers native calendar conversion and month records, lobby and game menu wire entry assignment, Barba Ray constructor, motion data and particle ownership, stage model-node callbacks and motion transform owners, player HUD child and information window ownership. The audit closes 17 historical comparisons and leaves 895 open.

The 2,164-file review queue covers 32 groups. The canonical source and working fork reproduce retail. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-calendar-protocol-and-native-replay.json)

The protocol uses native assignment operators for both menu entry types. Their seven- and 21-instruction bodies match the retail code. Both still need their existing scheduling directives under the current compiler. The remaining inline directives for these operators were removed. The calendar conversions now share DateStamp and copy both calendar month tables through their native record.

## Character creation, item effects and native subsystem recovery

Source `f13a4f3809` and landing checkpoint `ea0a460686` carry 35 changed files. This batch covers character creation actions, pad reads and archive ownership, Epsilon body, guards and battle record ownership, native status and equipment item rows, item and boss fire-effect origins and storage. The audit closes 41 historical comparisons and leaves 854 open.

The 2,174-file review queue covers 33 groups. The canonical source and working fork reproduce retail. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-creation-item-and-native-replay.json)

Character creation uses the six argumentless menu callbacks at their original addresses, a typed physical pad slot and its unsigned trigger fields, and one creation archive pointer through loading, motion and cleanup. The standalone retains the existing archive loader boundary while the combined source uses the BmlResource constructor.

## Technique casting, ground projection, status windows and photon field tasks

Source `5b16fd51a8` and landing checkpoint `d6f93ee940` carry 56 changed files. This batch covers player technique-cast state, target counts and cast packet handling, ground projection and optional surface normals, status list, shop and shortcut heading and scrollbar lifecycles, photon field weapon and visual task lifecycles. The audit closes 28 historical comparisons and leaves 826 open.

The 2,197-file review queue covers 33 groups. The canonical source and working fork reproduce retail. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-technique-state-and-native-replay.json)

## Item factories, Barba Ray, communication cards and quest companions

Source `5991ac7b12` and landing checkpoint `d4f2793c65` carry 178 changed files. This batch covers tool, meseta and native weapon factory dispatch, Barba Ray crawfish, dust and encounter joints, quest companion actor ownership and previous-position readers, Guild Card display, list selection and confirmation. The audit closes 42 historical comparisons and leaves 784 open.

The factory review directly types 64 weapon factories used by 91 table slots and the full tool and item-class tables. All 203 retail dispatch entries were checked byte for byte.

The 2,312-file review queue covers 33 groups. The canonical source and working fork reproduce retail. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-item-factories-and-native-replay.json)

## Actor stats, tunnel encounters, snapshot archives and stage resource lifecycles

Source `cbff37c9f9` and landing checkpoint `5dc354c2d4` carry 60 changed files. This batch covers native actor HP, TP and recovery callers, tunnel phase inputs, effects and checksum contract, snapshot render and RLC motion archive ownership, stage floor manager and ARAM archive pool lifecycles. The audit closes 19 historical comparisons and leaves 765 open.

The actor stat pass verifies the three signed halfword getters at their original addresses. Three legacy caller units retain the original full-register return contract.

The 2,322-file review queue covers 33 groups. The canonical source and working fork reproduce retail. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-actor-stats-and-native-replay.json)

## Weapon factories, Berura, character selection, quest transfers and published stage names

Source `d25fcf8fab` and landing checkpoint `bd190e5fc1` carry 125 changed files. This batch covers remaining native weapon factory returns and dispatch, Berura battle records, attack inputs and detached-arm owners, native selector scene, slot plates and card state, native online quest selection and download records, published stage naming cleanup with current typed callers. The audit closes 16 historical comparisons and leaves 749 open.

The factory review now dispatches directly to all 129 weapon factories. The combined item tables retain all 203 original entries byte for byte. The working fork now uses the same direct callback for meseta. The two prior adapter paths are shared with the source tree, and all 131 remaining fork tooling overlay paths round-trip.

The 2,365-file review queue covers 33 groups. The canonical source and working fork reproduce retail. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-factory-closure-and-native-replay.json)

## Challenge selection, memory cards and combat records

Source `a0ab810dd1` and landing checkpoint `7434799df2` carry 49 changed files. This batch covers BalClaw body, claw attacks and formation ownership, Photon Blast participant admission, actor queries and hold dispatch, native memory-card selection, cursor and player-load state, native Challenge quest selector, catalog and VM windows. The audit closes 14 historical comparisons and leaves 735 open.

The 2,381-file review queue covers 33 groups. The canonical source and working fork reproduce retail. All 90 original data ranges are accounted for, and the fork passes 294 tooling and 11 layer tests. [Validation evidence](2026-11-20-native-selection-and-combat-replay.json)

## Bulk review packaging for existing source recovery

The combined review queue at `9e9fa4dda9` carries 146 changed paths for this batch. The source already reproduces retail at `a0ab810dd1`. The queue reproduces retail with 2,451 exact linked units and zero lost matched or linked coverage.

| Review | Local head | Review base | Changed files |
| --- | --- | --- | ---: |
| NPC population constructors, models and texture lifetimes | `5caa76608e` | `49b48c32e6` | 75 |
| Native character level tables, NPC templates and archive reads | `93e344aaab` | `49b48c32e6` | 93 |
| Ending scene, picture transitions and Rico ring lifetimes | `91eed3bfdc` | `49b48c32e6` | 62 |
| Native choice, message, callback and child menu windows | `55469cc402` | `e9a0de33c6` | 46 |

The queue now spans 2,433 files across 35 groups. A path comparison leaves 308 canonical changed paths outside the queue diff. Those paths still need review assignment or evidence of equivalent source in another owner. The child-window review uses the existing native equipment-window prerequisite. The source audit closes 6 historical comparisons, leaving 729 open. [Validation evidence](2026-11-20-bulk-owner-review-packaging.json)

## Player scale, input, materials and ambient scenery

The combined review queue at `a023237dca` carries 148 changed paths for this batch. The source already reproduces retail at `a0ab810dd1`. The queue reproduces retail with 2,451 exact linked units and zero lost matched or linked coverage.

| Review | Local head | Review base | Changed files |
| --- | --- | --- | ---: |
| Native player scale, shrink packets and state declarations | `c5493f319d` | `49b48c32e6` | 30 |
| Shared material, texture and sprite rendering | `f3d6a88dd8` | `49b48c32e6` | 78 |
| Ambient fish, rain and stage props | `6cb53ca77a` | `49b48c32e6` | 26 |
| Keyboard input, soft keyboard feedback and Symbol Chat | `fed9cf8b71` | `55469cc402` | 31 |

The queue now spans 2,470 files across 38 groups. A path comparison leaves 270 canonical changed paths outside the queue diff. Those paths still need review assignment or evidence of equivalent source in another owner. The keyboard and chat review uses the existing native equipment-window prerequisite. The source audit closes 5 historical comparisons, leaving 724 open. [Validation evidence](2026-11-20-input-render-and-stage-packaging.json)

## Persistent sound, technique effects, strip rendering and title scenes

The combined review queue at `cd5eb6b631` carries 147 changed paths for this batch. The source already reproduces retail at `a0ab810dd1`. The queue reproduces retail with 2,451 exact linked units and zero lost matched or linked coverage.

| Review | Local head | Review base | Changed files |
| --- | --- | --- | ---: |
| Model texture strips, UV scrolling and trail rendering | `ede02613cc` | `49b48c32e6` | 50 |
| Persistent positional sound requests | `bbd9564425` | `49b48c32e6` | 86 |
| Native title and attract scenes | `86686aa676` | `f43e9408f5` | 14 |
| Typed technique effects and shared band pitch | `1b0d09f9e0` | `b01ddac5d2` | 22 |

The queue now spans 2,505 files across 41 groups. A path comparison leaves 236 canonical changed paths outside the queue diff. Those paths still need review assignment or evidence of equivalent source in another owner. Technique effects and title scenes use the listed prerequisite branches. The source audit closes 2 historical comparisons, leaving 722 open. [Validation evidence](2026-11-20-technique-sound-strip-and-frontend-packaging.json)

## Quest downloads, gameplay packets and subsystem reviews

The combined review queue at `23b1198d5a` carries 144 changed paths for this batch. The source already reproduces retail at `a0ab810dd1`. The queue reproduces retail with 2,451 exact linked units and zero lost matched or linked coverage.

| Review | Local head | Review base | Changed files |
| --- | --- | --- | ---: |
| Native quest download text and cache workspace | `96e12501e1` | `47ee1bbdfe` | 12 |
| Gameplay sound and item drop packets | `d053035570` | `49b48c32e6` | 19 |
| Native menu windows, city shops and item stock | `540e1a91ba` | `fed9cf8b71` | 46 |
| Boss projectiles, attack geometry and raft splashes | `03eb2c367e` | `49b48c32e6` | 43 |
| Enemy target acquisition and registered actor lookup | `a9c6341c40` | `b26cf3e04a` | 42 |

The queue now spans 2,535 files across 44 groups. A path comparison leaves 209 canonical changed paths outside the queue diff. Those paths still need review assignment or evidence of equivalent source in another owner. The listed review bases identify prerequisite branches. The source audit closes 7 historical comparisons, leaving 715 open. [Validation evidence](2026-11-20-quest-packets-encounter-and-menu-packaging.json)

## Particle factories, native attachments and presentation reviews

The combined review queue at `3f8e3a05c0` carries 438 changed paths for this batch. The source already reproduces retail at `a0ab810dd1`. The queue reproduces retail with 2,451 exact linked units and zero lost matched or linked coverage.

| Review | Local head | Review base | Changed files |
| --- | --- | --- | ---: |
| World-position particle factories and callers | `1dfa045120` | `49b48c32e6` | 182 |
| Rope, bone rotation and fin attachments | `c2936d95ef` | `49b48c32e6` | 17 |
| Scripted camera playback and scene callers | `0394e28c27` | `a0ae8422d0` | 26 |
| Window draw contexts, selection bars and clipped text | `57a10b0f98` | `540e1a91ba` | 76 |
| Native BML lifetimes, resource descriptors and load callbacks | `fd2120f67c` | `8b4edc76eb` | 237 |

The queue now spans 2,585 files across 48 groups. A path comparison leaves 159 canonical changed paths outside the queue diff. Those paths still need review assignment or evidence of equivalent source in another owner. The listed review bases identify prerequisite branches. The source audit closes 2 historical comparisons, leaving 713 open. [Validation evidence](2026-11-20-particles-attachments-bml-and-display-packaging.json)

## Save images, actor layout and scene ownership

The combined review queue at `52fb47e450` carries 343 changed paths for this batch. The native source reproduces retail at `83decd2d24`. Its 37-path enemy acquisition update also passed on the working fork with all 294 tooling tests. The queue reproduces retail with 2,451 exact linked units and zero lost matched or linked coverage.

| Review | Local head | Review base | Changed files |
| --- | --- | --- | ---: |
| Native memory-card save images | `3a7ed59b8b` | `49b48c32e6` | 10 |
| Actor body center, movement and rotation layout | `015dd577a9` | `49b48c32e6` | 275 |
| Character creation presentation and packed-color drawing | `64ad571ed4` | `e03302a703` | 50 |
| Slime child actors and Canadin formation ownership | `4d38fbac42` | `a9c6341c40` | 14 |

The queue now spans 2,610 files across 50 groups. A path comparison leaves 135 canonical changed paths outside the queue diff. Those paths still need review assignment or evidence of equivalent source in another owner. The listed review bases identify prerequisite branches. The source audit closes 0 historical comparisons, leaving 713 open. [Validation evidence](2026-11-20-saves-actor-layout-and-family-packaging.json)

## Prospective merge of the open upstream reviews

PR #335 brings native classes, constructors and member calls across 1,334 paths after its original #334 dependency. `great-merge/incoming/pr-335` at `e546dc7bff` includes both current published heads. The three overlapping stage cleanup files retain the stage member and helper names while taking the recovered constructors and member calls. The network review merges cleanly on top at `e08d32c5f4` on `great-merge/incoming/prs-333-334-335`. Both trees reproduce retail and pass `tools/check_pr.py` with 2,448 exact linked units. The three-review tree preserves every exact function and source-linked code and data range from the current canonical source and queue. The original 90 ranges retain 980 linked bytes and 167 bytes of classified alignment padding. [PR #335](https://github.com/zeroz41/pso-decomp/pull/335) [Build and overlap evidence](2026-11-20-incoming-pr-335-reconciliation.json)

A trial of #335 plus stage finds 732 conflicting paths with the previous review queue (`52fb47e450`). The three-review baseline has 735 conflicts with that queue and 776 with canonical source (`83decd2d24`). UI has 287 of the three-review queue conflicts, followed by bosses (104), miscellaneous source owners (67), and enemies (64). Of the 135 previously recorded canonical paths outside the queue diff, the incoming tree edits 24 and still differs on each. The other 111 have their upstream content. Resolve source behavior and types by owner, keeping upstream names and the related callers in the same build. Recheck linker registrations after each group.

The first replay on the three-review tree is the 10-file memory-card save descriptor and callers at `0266e85f9b` on `great-merge/incoming/native-card-save-images`. It takes the published snapshot loader call and shares the typed save descriptor. The branch reproduces retail and passes the strict checker.

The verified review queue advances to `47ade105c7` with a 161-file combined replay of Ginja and Ninja rendering contracts, Dark Falz and Olga Flow drawing ownership, and Pan Arms split-body ownership with Canadin's signed formation tables. Its full build has 2,451 exact linked units and zero losses of checked coverage. It adds 26 of the 135 previously absent canonical paths to the queue diff, leaving 109. The three subsystem branches are available under `great-merge/prepared/`, and the trial against the prospective baseline records 735 remaining queue conflicts. The broader compiler directive cleanup from fork PR #622 remains a per-unit validation task. The 12-file subset already has a queue validation record. Keep keyboard fade and grass exceptions tied to their matching object evidence. The previous source audit still has 713 historical owner comparisons open.

Use the prospective baseline to reconcile related residuals, then repeat parity checks against actual upstream master after the open reviews land. Finish recovering and upstreaming the source changes before switching the fork default branch. Compare the final layered tree with upstream and prove exact retail, coverage, and fork-layer round trips before the switch. Keep the fork documentation and tooling under `fork/`.

### PPP wire records and native actor layout

`great-merge/incoming/replayed-source` at `9786fed299` adds 293 changed files after the validated card save replay. The 12-file PPP review at `71f9ce8177` uses native frame and wire-header records. The 281-file actor review uses typed body center and velocity vectors and the native three-angle rotation record. It keeps recovered constructors and member calls and carries the layout through callers that were added in the incoming reviews. The source declares the original actor offsets and retains the local rotation fields of the Dark Gunner's separate layout record.

Both builds reproduce retail and pass `tools/check_pr.py` with 2,448 exact linked units. The combined build preserves all checked exact and linked coverage against the prior review queue, canonical source and historical fork. It verifies the original 90 ranges with 980 linked bytes and 167 bytes of alignment padding. The typed actor layout changes many shared lines, so a whole-tree merge from the older stage base still conflicts across 801 queue paths and 881 canonical paths. Use the validated replay groups when combining later work. The next particle factory group has 48 paths requiring reconciliation.

The fork tooling patch preflight on this source reports 11 paths to refresh. Ten have overlapping changes and one is supplied by the pending Ginja provider review. Refresh the workspace patch after those providers land in the replay and check the resulting fork layer against the final source tree. [Build, overlap and fork tooling evidence](2026-11-20-prospective-actor-and-network-replay.json)

### Shared particle factories, rendering callbacks and the fork layer

The particle review at `227e14cd1f` uses one typed world-position factory across 182 files. It keeps the incoming member calls and the byte-offset expression required by the original switch attack. The 140-file renderer review at `a022239edb` adds typed Ginja material handlers and Ninja chunk callbacks. The combined source changes 291 paths from the actor review. Both reviews reproduce retail and pass `tools/check_pr.py` with 2,448 exact linked units. The final build preserves matched and source-linked coverage against the older queue, canonical source and historical fork. It accounts for the original 1,147 bytes across all 90 ranges.

The renderer supplies the Ginja provider needed by the fork tooling patch. The rest of the tooling patch replays with the portable collision, quest, shortcut and vector fallbacks adapted to the current source. The local retention block is regenerated with 27,029 current names. The materialized tooling workspace reproduces retail and passes the strict checker. A fresh materialization reproduces all 131 workspace changes, and all 11 layer tests pass. The layer adds `fork/` and the fork-specific CI workflow.

The full tool suite on the fresh workspace reports 265 failures and five errors across 285 tests. The failures are concentrated in typed BML accessors and also flag Dark Falz Zako resource and viewport contracts. Bring those source reviews into the replay and rerun the suite before fork cutover. [Build and cutover rehearsal](2026-11-20-particle-renderer-and-fork-layer.json)

### Typed BML access and Dark Falz resources

The BML accessor replay at `a73ba07e10` consolidates model and texture access in one typed declaration and carries it through 238 paths. The Dark Falz replay at `8b9cd6b587` restores the typed archive handle, child model setup, Zako cache, clear wrapper and shared viewport call across 17 paths. The renderer texture-list replay at `059fb5502f` carries the typed cache into the shared scene-state setter across 352 paths. The three reviews change 424 unique paths, reproduce retail and pass strict source-link checks. The combined build retains the original data inventory and all checked coverage against the older review queue, canonical source and historical fork.

The fork-only workspace patch still applies across its 131 paths and reproduces retail. All 11 layer tests pass. The 290 executed tool tests report zero assertion failures and one setup error in the Dark Falz cleanup fixture, which needs the native BML destructor. The archive-lifetime review at `daa3a3af77` carries that destructor and its consumers across 230 related paths. [Build and fork layer evidence](2026-11-20-bml-zako-and-texture-replay.json)

### Native BML archive lifetime and load completion

The 230-file lifetime replay at `c1c25b0a46` recovers the native constructor, destructor and arena fields. It migrates the archive owners and their callers, including the consolidated lock-on source and Dark Falz cleanup. The 39-file descriptor and load completion review at `696d108dad` adds the typed descriptor copy, filename override, chunk allocator and three completion request layouts. The reviews change 237 unique paths. Each reproduces retail and passes the strict source-link check. The combined tree retains all checked code and data coverage, including the original 90 data ranges.

Regenerating the fork linker retention block resolves the workspace patch's only conflict. The retained fork layer still adds only `fork/` and the fork-specific CI workflow. The workspace round trip preserves every tested file identity. All 294 fork tooling tests and 11 layer tests pass, including the four Dark Falz cleanup tests. UI has the largest concentration of canonical paths outside the prospective source diff, with equipment windows, keyboard ownership, city menus and the shared window drawing context already grouped for replay. [Build, layer and source audit](2026-11-20-bml-archive-lifetime-replay.json)

### PR #335 history update and remaining source

Published head `98923bc837` has the same tree as the previous head `1157670533`. The local three-review baseline at `69d2b0ad0e` and replay source at `510be1d79a` now contain the published heads of #333, #334 and #335. Both preserve their previously validated trees byte for byte. The fork layer retains its tested tooling patch. [PR #335](https://github.com/zeroz41/pso-decomp/pull/335) [History and path audit](2026-11-20-pr-335-history-refresh.json)

The canonical source changes 2,742 paths from the pinned master. Of these, 260 have identical content in the replay, 1,334 differ where both trees changed the path, and 1,148 lie outside the replay's diff against master. These counts guide subsystem review and include moves and alternate implementations. The largest groups outside the replay diff are UI (321), uncategorized `pso/unk` (167), weapons (142), bosses (107), enemies (76), player (66), and items (49). Reconcile the UI drawing and layout contracts with their callers, then use the existing review groups to separate equivalent source from changes that still need replay. Keep coverage as a separate check alongside the source comparison.

### Typed window draw setup

The 43-file replay at `f60f17d429` shares the original draw context return type and recovers `draw_default_entry` as a `TWindowBase` member with the real receiver. The source keeps the existing name. Its only linker label change from the previous replay follows the recovered receiver. The build reproduces retail and passes the strict source-link check with 2,448 exact linked units, 27,572 exact functions, and zero losses of exact or source-linked code and data coverage.

The path inventory now has 1,145 canonical changes outside the prospective replay diff. Of these, 86 also lie outside the earlier verified review queue. The largest groups in that intersection include shared and equipment effects, player code, and enemy code. The ledger records the paths for assignment to their owners. For the wider UI replay, 180 of the 318 UI paths outside the diff are under `ui/window`. The existing work on content frames, selection bars, clipped text, and menu layouts supplies the next related changes. [Build, fork layer and residual inventory](2026-11-20-native-window-draw-replay.json)

### Window content drawing and layout entries

The three commits through `8cb5f82169` update 78 paths. They share the selection bar and text clipping context, recover `get_draw_context` on `TWindowAddition`, and use one `WindowLayoutEntries` declaration for initialization, updates, drawing and destruction. Entry dispatch now uses the native part class. The four linker label changes from the preceding replay reflect the recovered receiver, parameter types or owner. The cumulative window draw review spans 86 files from `510be1d79a`.

The source and fork tooling workspace reproduce retail with 2,448 exact linked units, 27,572 exact functions and every previously checked code and data address retained. The workspace patch covers 131 paths and passes the 294 tooling tests and 11 layer tests. The remaining path comparison puts 1,136 canonical changes outside the replay diff, including 310 UI files. The 111-file native frame and scroll layout review has 54 overlapping paths against this checkpoint. [Build, fork layer and layout overlap evidence](2026-11-20-window-entries-replay.json)

### Native window frame and scroll layout

Published PR #335 head `b05988e1af` has the same tree as the previous validated local #335 merge at `b916cd59fb`. The refreshed prospective stack keeps that source and now contains the published head. [PR #335](https://github.com/zeroz41/pso-decomp/pull/335)

The 115-file replay at `04e3c21a71` puts the frame and scroll fields on `TWindowBase` and `TWindowAddition`, with assertions for the original sizes and offsets. Derived windows use those fields, and specialized item rows, gauges and sprites use their own records. The only changed linker label follows `request_close` to its shared base-class owner. The cumulative window review covers 147 files from `510be1d79a`.

The source and materialized tooling workspace reproduce retail and retain the checked code and data addresses. The strict check reports 2,448 exact linked units and 27,572 exact functions. The path inventory now has 1,097 canonical changes outside the prospective replay diff, including 271 UI paths. The remaining descriptor, keyboard, and city-menu batches have 17, 14, and 34 overlapping paths against this frame checkpoint. [Validation and overlap evidence](2026-11-20-native-window-frame-replay.json)

### Window descriptors, keyboard input and Symbol Chat

The 32-file descriptor replay at `9cdd31b823` uses the shared clipping context for inner bounds and returns entry pointers from the window accessor. The clean rebuild included six conversions at callers that still use integer addresses. The 52-file keyboard and Symbol Chat replay at `c5a12df954` recovers typed keyboard receivers, dismissal and input flags, child drawing and scroll construction. Both clean source builds reproduce retail, pass the strict link check and retain all checked code and data addresses. Linker label changes follow the recovered receivers, constructor or parameter types.

The combined replay changes 80 files, bringing the cumulative UI review to 189 paths from `510be1d79a`. The path inventory now has 1,079 canonical changes outside the prospective replay diff, including 255 UI paths. The next city shops, menu windows and item stock review has 34 overlapping paths on the new source. [Build, fork layer and overlap evidence](2026-11-20-window-interface-and-keyboard-replay.json)

### Landed upstream baseline

Upstream master `0fa391a887` includes the squash merges of #335 and #333. Its tree is identical to the validated prospective three-review tree at `28bfbe9f17`. The #335 squash at `7f4e8cd295` also has the same tree as the previously validated #335 merge. The local Great Merge replay at `74c19e2002` now descends from actual master and preserves the previous replay tree. A clean build of upstream master reproduces retail with 2,448 exact linked units. [PR #335](https://github.com/zeroz41/pso-decomp/pull/335) [PR #333](https://github.com/zeroz41/pso-decomp/pull/333)

### City menus and shop stock

The 71-file replay at `4d72d5f097` recovers typed menu factories, native shop and window ownership, and typed item stock and prices. Five linker labels change as the menu methods move to their owning class. The clean source build reproduces retail and passes the strict linkage check against master.

`great-merge/prepared/window-drawing-keyboard-and-city` at `0157762a98` groups window layout, drawing, keyboard input, Symbol Chat, and city menus into a 247-file review directly on `0fa391a887`. It preserves the renderer and resource calls from master. The independent clean build also reproduces retail, links all 2,448 exact units, and retains all checked code and data addresses.

The 131-path tooling patch round-trips over the new replay, reproduces retail, and passes 305 tooling and layer tests. The historical path inventory has 1,073 canonical paths outside the active replay diff. [Build and review evidence](2026-11-20-city-menu-and-upstream-replay.json)

### Native title scenes and compiler directives

The title-scene replay at `39e8ea07de` assigns scene state, child ownership, and callback dispatch to the title task and types the sprite tables. Its six changed linker labels follow those methods to the owning class. The 12-file cleanup from fork PR #622 removes 108 compiler directives and four adjacent blank lines. It keeps the live NPC and renderer signatures and changes zero linker labels. The combined source at `67daa1efc4` reproduces retail with 2,448 exact linked units and retains all checked code and data coverage. The 131-path fork tooling patch reproduces the tested workspace and passes 305 tests.

A replay preview checked 59 previous review tips. The leaf changes for particle factory callers, network datagrams and PPP frames are already present on the city baseline. The historical path inventory still has 1,058 canonical paths outside the active replay diff, including 86 also outside the earlier review queue. The preview identifies the stage archives and scenery, stage containers, and stage transfer and ending-scene groups for the next related batches. [Replay and validation evidence](2026-11-20-title-scenes-and-compiler-cleanup.json)

### Stage objects, map collision and ending scenes

The 40-file replay at `57b732df94` recovers the native fish constructor and destructor, reads ambient camera fields through the controller, and gives each Ancient container class its own typed effect positions. The ending scenes own their picture and wall rectangles. Rico rings use native constructors and retain their shared renderer and fades. City fireworks keep a typed particle handle, and the native map collision factory supplies the Jungle door, wrecks, lab props, boss actors and object factory tables.

The standalone review `great-merge/prepared/stage-objects-and-ending-scenes` at `ec81bd9ce7` applies the same recovery directly to master `0fa391a887` using its renderer and archive signatures. The replay keeps the upstream warp identifiers, floor-event senders and container archive implementations. All 15 changed linker labels follow corrected receivers, constructors or parameter types. Both builds reproduce retail with 2,448 exact linked units and zero lost code or data coverage. The 90 starting ranges account for 980 source-linked bytes and 167 alignment bytes on master and on both builds. All 305 tooling and layer tests pass on the 131-path fork workspace. [Source, inventory and fork layer evidence](2026-11-20-stage-collision-and-ending-scenes.json)

The historical inventory has 1,048 canonical paths outside the active replay diff, including 84 also outside the older queue. Challenge results, retry state and item-help and status windows are ready for reconciliation on this head. The results preview has 26 overlapping paths across 49 changed files.

### Challenge and duel results, retry windows, and page indicators

The 37-file replay at `4da1fa300a` gives the result windows native constructors and virtual methods. Both Challenge retry variants own their menu handles and countdown. The duel, card, shortcut, item-help, and status windows share one typed page indicator. The status records use typed text entries, and the item-help window uses its native descriptor and summary fields. The replay keeps the existing text-width helper and equivalent method names. Thirteen linker labels change with the recovered receivers, constructors, virtual methods, or parameter types.

The expanded local review `great-merge/prepared/window-layout-keyboard-and-results` at `8464cb68fb` adds this recovery to the existing window, keyboard, Symbol Chat, and city group. Its two commits cover 263 files directly on master `0fa391a887`. Both clean builds reproduce retail, link all 2,448 exact units, and preserve every checked code and data address. Both account for the full original 1,147-byte inventory. The 131-path fork tooling patch reproduces its tested workspace and passes 305 tests.

The historical inventory has 1,039 canonical paths outside the active replay diff, including 82 also outside the older queue. The next weapon registry and projectile interface preview spans 278 paths with 27 overlaps. The three-commit factory tail alone produces more overlap because it assumes the earlier projectile and item contracts. [Build, inventory and review evidence](2026-11-20-challenge-duel-and-page-indicators.json)

### Item factories and weapon projectile interfaces

The 272-file replay at `dca722cfd2` gives the item registry one native factory signature and has weapon factories call their constructors directly. Item archives return typed models, textures and motions. Projectile and effect callers use their actual owners, descriptors and collision records, and weapon models use typed muzzle vectors and motion fields.

The standalone review `great-merge/prepared/weapon-registry-and-projectiles` at `297a969781` starts directly from master `0fa391a887`. Both versions keep the upstream clamp helpers, Ninja reader name, texture entry field and shot-model helpers. Their 45 changed linker labels follow recovered receivers, constructors or parameter types. Clean builds reproduce retail with all 2,448 source objects linked and zero lost code or data addresses. Both builds account for all 1,147 original bytes. The fork-only tooling patch round-trips across 131 paths and passes 305 tests.

The historical inventory falls from 1,039 to 842 paths outside the active replay diff. A one-shot replay of the older review queue has 1,062 overlapping paths. The narrower previews identify online quest transfer and ADX streaming as separate 134- and 122-path groups, with 40 and 41 overlaps respectively. [Build, naming and overlap evidence](2026-11-20-weapon-factories-and-projectile-interfaces.json)

### ADX streaming, disc reads and callback contracts

The 89-file replay at `bb96c19268` carries typed ADX stream requests through playback, decoding and completion. Disc archive callers use the opaque ADXF file handle. CVFS and the movie memory device share a callback table, and ADXF owns the command history and sequence counters. The replay keeps the existing sound-pitch calls, cache-invalidation helper and stream-range method. The relocated-module accessor now belongs to the translation unit that loads and destroys the module buffers.

The standalone review `great-merge/prepared/adx-streaming-and-disc-reads` at `2572238636` starts directly from master `0fa391a887`. Both clean builds reproduce retail and retain every checked code and data address with 2,448 source objects linked. The 131-path fork tooling patch round-trips over the replay and passes all 305 tests. The historical inventory falls from 842 to 790 paths outside the active replay diff. [Build and replay evidence](2026-11-20-adx-streaming-and-disc-reads.json)

### Online quest transfers, cache and selection windows

The 133-file replay at `74b91cd5c7` carries typed download headers from the packet receiver to file assembly and gives quest cache records, text nodes and workspace slots shared layouts. Quest threads use their actual script managers. Challenge and guild selection use native window callbacks, and quest dialogue uses the existing native constructors. The replay reuses the shared object-set layout and preserves the original initializer and warp helper symbols.

The standalone review `great-merge/prepared/online-quest-transfers` at `5e0a443edd` starts directly from master `0fa391a887` and keeps its archive and menu interfaces. Both clean builds reproduce retail and retain every checked code and data address. The 131-path tooling patch uses the shared quest slot type for its host test and updates the private cache probe's symbol references. All 305 tests pass. The cache probe also verifies all 128 slots, ten pages, 80 buckets and 512 free-list nodes, plus file reads and page eviction, on retail and all three rebuilds.

The historical inventory falls from 790 to 739 paths outside the active replay diff. [Build and replay evidence](2026-11-20-online-quest-transfers-and-cache.json)

### Character selection, card saves and creation actors

The 191-file replay at `fef0ba0180` gives single- and multiplayer selection their native scene, cursor and plate owners. The preview loader uses typed appearance requests, model records and archive buffers. Card callers share the full-width character save lookup and the SDK card state. Creation-menu callbacks use their actual receiver and argument types. The replay keeps the existing controller-query, card-delete, serial-input and renderer interfaces where their behavior already matches.

The standalone review `great-merge/prepared/character-frontend-and-card-saves` at `d6e66ef2a8` starts from master `0fa391a887`. Its first commit carries the native card-save descriptor and its second adds the frontend replay. Together they change 194 paths. Both clean builds reproduce retail, link all 2,448 source objects and retain every checked code and data address.

The 131-path fork tooling patch round-trips over the replay and passes 305 tests. The repaired private save-image probe checks artwork, 15 save images and 30 header reads on retail and the three rebuilt images. The historical inventory falls from 739 to 656 paths outside the active replay diff. [Build, scope and replay evidence](2026-11-20-character-frontend-and-card-saves.json)

### Dark Falz scenes, Zako drawing and Olga Flow trails

The 69-file replay at `417985bccc` recovers the real Dark Falz form actors for phase and cutscene handoff. It gives the cinematic objects native C++ factories, shared archive and fade records, and typed direct-attack calls. The Zako renderer uses a shared draw buffer. Olga Flow afterimages use typed frames and the same triangle-fan interface as their other callers.

The 76-file review `great-merge/prepared/dark-falz-scenes-and-boss-trails` at `117e4f7411` starts directly from master `0fa391a887` and uses its existing archive, texture, and REL entry points. The source audit retained the existing story-flag setter, tower setter, 2D polygon draw, trail draw and vector copy labels. The remaining symbol differences reflect class ownership and callable types.

The replay, standalone review and fork build reproduce retail with all 2,448 source objects linked. Address-based checks found zero function or data coverage losses, and all 90 historical ranges still account for 980 linked bytes and 167 alignment bytes. The 131-path fork tooling patch round-trips and passes all 305 tests. The Olga Flow probe passed on retail and all three rebuilds.

The historical inventory falls from 656 to 633 paths outside the replay diff. Olga Flow phase scenes and hazards are the next related group. The projectiles, arena geometry and splashes form a separate group around shared collision and draw calls. [Build, scope and replay evidence](2026-11-20-dark-falz-scenes-and-boss-trails.json)

### Olga Flow phases, arena hazards and model-node capture

The 83-file replay at `72e8ab2910` recovers the nine-entry Plot Falz phase table, the native battle-action records and the appearance and death actors. It brings back typed rock, mine, sword-wave and gravity-ball lifetimes. The shared model-node capture now serves Olga Flow, Dark Falz and Pan Arms. The replay keeps the existing camera helpers, Pan Arms factory and Type 2 field names.

The two-commit review at `0266af6bf4` combines this change with Dark Falz and boss trail rendering across 136 files. It starts from upstream master `0fa391a887` and uses the archive, texture and scene interfaces available there. The replay, complete review and 131-path fork tooling layer reproduce retail with 2,448 source objects linked and zero lost code or data coverage. All 1,147 historical bytes remain accounted for. All 305 tests pass, and the trail and model-node capture probes pass on retail and each rebuilt image.

The historical inventory falls from 633 to 610 paths outside the replay diff. The next boss projectile and raft effect previews overlap on the De Rol Le tunnel and linker metadata. [Build, scope and replay evidence](2026-11-20-olga-flow-phases-and-hazards.json)

### Published source reviews

Seven reviews are open against master `0fa391a887`. GitHub shows the seven validated heads and attributes all ten commits to `matthewlewisnewton`. The published histories contain zero Codex authors, committers or co-author trailers.

| PR | Scope | Published head |
| --- | --- | --- |
| [#336](https://github.com/zeroz41/pso-decomp/pull/336) | Stage objects, map collision and ending scenes | `ec81bd9ce7` |
| [#337](https://github.com/zeroz41/pso-decomp/pull/337) | Item factories and shared projectile interfaces | `297a969781` |
| [#338](https://github.com/zeroz41/pso-decomp/pull/338) | ADX streaming, disc reads and callback contracts | `2572238636` |
| [#339](https://github.com/zeroz41/pso-decomp/pull/339) | Online quest transfers, cache records and selection windows | `5e0a443edd` |
| [#340](https://github.com/zeroz41/pso-decomp/pull/340) | Character selection, card saves and creation actors | `d6e66ef2a8` |
| [#341](https://github.com/zeroz41/pso-decomp/pull/341) | Dark Falz and Olga Flow phases, hazards and drawing | `0266af6bf4` |
| [#342](https://github.com/zeroz41/pso-decomp/pull/342) | Window layout, keyboard input and Challenge results | `17d35ad696` |

The final window head keeps its compiler directive in `TWindowChallengeResult.cpp`, which reproduces retail and passes the same linkage checks. The record includes the published commits and GitHub matching jobs. [Publication and commit audit](2026-11-20-upstream-publication-336-342.json)

### Boss projectiles, raft splashes and dust trails

The 58-file replay at `7eb2bdf853` recovers the typed lifetimes of Dragon and Gol Dragon fireballs, Barba Ray photon shots, and Olga Flow sword shots. Dragon, Gol Dragon, and Gal Gryphon share the attack descriptor. De Rol Le and Barba Ray restore native dust and raft-splash fields and use the trail renderer's actual arguments. The replay keeps the existing `get_boss7_motion` name and dust constant owners.

The standalone branch `great-merge/prepared/boss-projectiles-and-raft-effects` at `98b8dc9b74` uses the archive, particle and player interfaces on master `0fa391a887`. Matt is the author and committer of its single review commit. The unpublished review overlaps PR #341 in two Olga Flow callers. The cumulative replay already carries those changes together. Merge previews with the six other published reviews are clean.

The replay, standalone review and 131-path fork tooling layer reproduce the retail DOL, with all 2,448 source objects linked and zero function or data coverage losses. All 1,147 historical bytes are accounted for. The 305 tooling tests pass. The raft dust and strip animation probes pass on retail and each rebuilt image. The historical path count outside the replay diff falls from 610 to 591. [Build, scope and replay evidence](2026-11-20-boss-projectiles-and-raft-effects.json)

### Action-palette controls and Word Select

The 35-file replay at `d8d3d927b7` shares the action-palette tag across cursor, player, and customization code, and restores the Custom Select constructor and Custom Equip rendering. The Word Select formatters share a 12-byte message record, and the rendering callers use the original 24-byte vertex layout. The Word Select replay preserves every existing function label. The palette changes correct helper receivers, constructor and argument types, and ownership.

The unpublished standalone review at `9081bb020c` starts on master `0fa391a887`. Matt authored and committed its single commit. It overlaps PR #342 in four window files, already resolved on the cumulative replay. Merge previews with the other six published reviews and with the boss-projectile review are clean.

The cumulative replay, standalone review, and 131-path private tooling layer all reproduce the retail DOL, with 2,448 linked source objects and zero function or data coverage losses. All 305 tooling tests pass, and all 1,147 historical bytes remain accounted for. The historical path count outside the replay diff falls from 591 to 580. [Build, scope and replay evidence](2026-11-20-action-palette-and-word-select.json)

### Enemy targeting, formations and Slime attack actors

The 56-file replay at `9a864ea5d0` shares the typed enemy targeting and collision-actor lookup across callers. Canadin recovers its formation and action methods. Bal Claw uses its native body state handlers and child constructor. Slime uses typed child slots, animation state, tail poses, and water-bomb tasks. The existing Slime archive lifecycle and tail-hit member name are preserved.

The unpublished standalone review at `72ca918dcb` starts on master `0fa391a887`. Matt authored and committed its single commit. It overlaps PR #341 in three Pan Arms sources. The cumulative replay already builds with both sets of changes. The other six published review previews and both prepared reviews are conflict-free.

The replay, standalone review, and 131-path fork tooling layer reproduce the retail DOL. All 2,448 source objects link and the checks show zero function or data coverage losses. All 1,147 historical bytes remain accounted for. The 305 tooling tests pass, along with 34 enemy-state and 19 player-targeting cases on each of the four images. Four stale symbol names were corrected in the private probes at their original addresses. The historical count outside the replay diff falls from 580 to 568 paths. [Build, scope and replay evidence](2026-11-20-enemy-targeting-formations-and-slime.json)

### Main menu controller and trade windows

The 69-file replay at `7016e40009` recovers the main menu controller fields, single-player camera backdrop and player-window callbacks. The trade request owns its dialog, and the main menu constructs its three trade subwindows directly. The Yes/No and menu flag setters use their actual receiver types. The resize and slide methods use the child menu's height at `0x3C` and tween state at `0x50`.

The unpublished standalone review at `8e9e9ffd42` starts from master `0fa391a887`. Matt authored and committed its single commit. Its merge preview with PR #342 overlaps in 17 files. The prepared enemy-formation review overlaps on the linker retention list. The cumulative replay builds with all three sets of changes.

The replay, standalone review and 131-path private tooling layer each reproduce the retail DOL with all 2,448 source objects linked, zero coverage losses, and all 1,147 historical data bytes accounted for. The 305 tooling tests pass. Twelve resize and nine trade lifecycle cases pass on retail and all three rebuilt images. The historical path count outside the replay diff falls from 568 to 542. [Build, scope and replay evidence](2026-11-20-main-menu-and-trade.json)

### Four follow-up reviews and the upstream portability merge

Four more source reviews are open and mergeable against master. Each branch was fast-forwarded to its tested reconciliation after the upstream portability merge. GitHub attributes the eight PR commits to Matt as author and committer, with zero Codex author, committer, or co-author entries.

| PR | Scope | Published head | Files reconciled after #343 |
| --- | --- | --- | ---: |
| [#344](https://github.com/zeroz41/pso-decomp/pull/344) | Boss projectiles and raft effects | `45a7ef21ae` | 28 |
| [#345](https://github.com/zeroz41/pso-decomp/pull/345) | Action-palette controls and Word Select | `95334b8d75` | 10 |
| [#346](https://github.com/zeroz41/pso-decomp/pull/346) | Enemy targeting, formations and Slime attacks | `8c6e2163ee` | 22 |
| [#347](https://github.com/zeroz41/pso-decomp/pull/347) | Main menu controls and trade windows | `63636bea0a` | 34 |

The upstream portability merge advanced master from `0fa391a887` to `1fd561eae2` during publication and changed 2,960 paths. Master and all four tested review trees reproduce the retail DOL, with 2,448 source units linked and zero function or data coverage loss. The boss projectile patch now types the existing model field on the Barba Ray tentacle. The action palette patch uses upstream's address-width field type for the action table. The new master introduces 773 conflicts against cumulative source `7016e40009`. The older open review previews #336–342 also need reconciliation against this base. [Upstream #343](https://github.com/zeroz41/pso-decomp/pull/343) [Publication, validation and conflict inventory](2026-11-20-upstream-publication-344-347.json)

### Combined reviews on the portability baseline

The seven older reviews have local refresh branches under `great-merge/upstream-refresh/` on master `1fd561eae2`. The reconciliation covers 485 conflicting paths counted per review. Each branch preserves the published commits and has a fast-forward update ready with Matt as author and committer. Each tested tree reproduces the retail DOL and passes the strict linker and address-coverage checks independently.

| PR | Local refresh | Changed files |
| --- | --- | ---: |
| [#336](https://github.com/zeroz41/pso-decomp/pull/336) | `01ec31c94f` | 40 |
| [#337](https://github.com/zeroz41/pso-decomp/pull/337) | `46a0677d7f` | 271 |
| [#338](https://github.com/zeroz41/pso-decomp/pull/338) | `cc3fe0caf0` | 89 |
| [#339](https://github.com/zeroz41/pso-decomp/pull/339) | `10799b0e23` | 133 |
| [#340](https://github.com/zeroz41/pso-decomp/pull/340) | `19d635c87e` | 194 |
| [#341](https://github.com/zeroz41/pso-decomp/pull/341) | `dbe8717a52` | 134 |
| [#342](https://github.com/zeroz41/pso-decomp/pull/342) | `35fb9e4386` | 262 |

`great-merge/incoming/osp-reviewed-source` at `8854019965` combines these seven refreshes with the four published heads #344–347 across 1,171 files. The overlap fixes share the typed ADX and texture archive calls, the recovered boss receiver and trail layouts, the menu geometry and callbacks, and the character save and preview providers. The combined build matches 27,572 functions and links all 2,448 exact source objects. Coverage is preserved against master and the previous cumulative source. The original 90 ranges still account for 980 linked bytes and 167 alignment bytes.

The full cumulative replay still needs to carry the other source changes and the private tooling workspace. Comparing the earlier cumulative source `7016e40009` directly with the new checkpoint yields 740 conflicting paths. For the 773 paths that originally conflicted against master, the review transitions supply a single candidate for 345 paths. Of those, 294 already match the built checkpoint and the other 51 need a combined build. Another 428 paths still need resolution or a choice between different candidate contents. [Validation and replay evidence](2026-11-20-osp-combined-source-reviews.json)

## Expanded source replay after upstream portability

`great-merge/incoming/osp-replayed-source` at `ed48d6fc3a` carries 724 changed paths past the eleven-review checkpoint. It combines actor movement, world-position particles, Vol Opt and shared breakup effects, BML archive ownership, Ginja materials and texture lists, Short Mail and Guild Cards, and later cumulative changes to title scenes and PPP. The shared Ginja setter is used at all 599 audited call sites. The Zako cleanup and archive lookup use their shared declarations, and the PPP length comparison preserves the retail code's 16-bit width.

This tree and the materialized fork tooling both reproduce the retail DOL. The source retains all 27,572 exact functions and 2,448 exact linked source units. There are zero code or non-padding data coverage losses against the prior cumulative source. The 90 original ranges still account for all 1,147 bytes. An attribution audit over the 61 commits ahead of current master found zero Codex author, committer, or co-author entries.

`great-merge/incoming/osp-layered-replay` uses that source with the fork documentation and tooling overlay. The overlay reproduces the validated tree on reapplication, adds only fork-layer paths to the repository, and passes 294 tooling tests, 11 layer tests, and all five host port checks. The port callback fixture follows the shared byte-buffer signature now used by the native meseta factory. The layer records 27,031 retained symbols with zero missing or stale entries.

The latest historical comparison resolves 626 paths to the checkpoint. Of the 16 proposed edits, 15 repeat declarations or includes and one restores a superseded renderer cast. Another 110 paths need owner comparison and 12 have different candidate versions. The disc-error compiler cleanup passed separately at `252ba20838`, with no address or linkage changes. Against current master, every expanded review-sized batch still has conflicts. Open PRs #336–342 had separately tested updates, now published in the batch below. [Validation and remaining paths](2026-11-20-osp-expanded-source-and-fork-layer.json)

## Historical cumulative source replay complete

`great-merge/incoming/osp-replayed-source` at `27a9916d9e` accounts for the 122 remaining paths from the earlier cumulative snapshot. The replay reconciles 32 of those paths in source and retains the current owner for the other 90. The saved Guild Card slots, Short Mail recipient lookup, shop quantity factory, title sprite accessor, BML consumers and chunk callback now use their actual types. The title accessor keeps its original `int` argument and linker symbol. The shops narrow the client ID at their call sites, and the Dark Falz Zako initializer keeps both original archive lookups.

The source and fork workspace reproduce retail and pass the strict checker with 27,572 exact functions and 2,448 linked source units. The comparison with fork main keeps every exact and linked function and every non-padding and linked data range. The aggregate extent diagnostic is 2,549 alignment bytes omitted and 163 bytes newly covered. The 90 original ranges still account for all 1,147 bytes. There are zero Codex attribution entries in the 68 commits ahead of upstream. The fork workspace passes all 294 tooling tests, 11 layer tests and five host checks. Its overlay is byte-identical to the preceding snapshot. [Path decisions and validation](2026-11-20-osp-historical-source-closure.json)

The older fork review index covers additional work beyond the cumulative snapshot. Its 713 partially reviewed or unreviewed entries still need disposition. The initial rescan on the current source found 682 changed bodies, 26 entries whose previously recorded owner path moved, and five build or other non-source entries. The upstream refreshes for #336–342 are recorded with the publication below. The newer batches still need independent upstream bases before review.

## Relocated owners in the original fork index

`great-merge/incoming/osp-replayed-source` at `1a035e7521` restores the modem launch layout assertions and gives the equipment and shop windows shared typed declarations. Experience distribution, drop requests, group lookup, last-child transfer and actor registration now belong to `TObjEnemy`. Five linker labels follow those receiver changes at their original addresses. The four commits span 64 paths.

The source and materialized fork workspace reproduce retail with 27,572 exact functions and all 2,448 source objects linked. The strict checks show zero code or non-padding data coverage losses, and all 1,147 original data bytes are accounted for. There are zero Codex attribution entries in the 72 commits ahead of upstream. The fork tooling overlay round-trips byte for byte and passes 294 tooling tests, 11 layer tests and five host checks. [Owner decisions and validation](2026-11-20-osp-moved-source-owners.json)

The [original fork index](2026-11-18-fork-review-index.tsv) now points all 26 stale comparison paths to current owners. This pass resolves 32 entries, including declarations reviewed in place. The remaining 681 entries include six reviewed here that still need a field or call-site comparison.

## Ginja materials and Ninja model callbacks on upstream master

The standalone review at `7af1ccc64f` starts directly on master `1fd561eae2`. It recovers the Ginja material parameter and handler layouts, passes actual Ninja nodes through chunk draw callbacks, and caches colored vertices using the original 0x10-byte input and 0x20-byte output records. The two commits cover 141 files. All 45 changed linker labels follow corrected receivers or signatures. Both commits use Matt's Git identity with zero Codex attribution.

The review reproduces retail and links all 2,448 source units. The matching check shows no address or coverage losses and verifies all 1,147 original data bytes. Against the current-base review heads, eight merge previews are clean. The remaining overlaps are one path with #337, five with #341 and two with #346. The standalone review is open as [#348](https://github.com/zeroz41/pso-decomp/pull/348). [Review scope and overlap paths](2026-11-20-osp-renderer-review-and-layouts.json)

The cumulative branch at `9739c1febe` now has the same typed color cache. It shares the const-vector transform declaration with the footprint callers and restores five layout checks on the particle classes. The source and fork workspace reproduce retail, the fork layer passes all 310 checks, and the [fork index](2026-11-18-fork-review-index.tsv) has 675 remaining decisions. The weapon-hit interface stays open because the typed version changed the original compiler's instruction schedule.

## BML archive lifetimes and load requests on upstream master

The standalone archive review at `abb5022ed6` starts directly on master `1fd561eae2` and spans 317 files. It recovers the `BmlResource` constructor and destructor, the arena allocator, descriptor copies and the native load callback records. The callers share the model and texture pointer declarations. The 12 changed linker labels follow the restored receivers and signatures. The single review commit uses Matt's Git identity with zero Codex attribution.

The archive review and renderer review reproduce retail together at `c7a5af7abf` across 382 paths. The combination uses both shared interfaces in the live monitor. The archive still overlaps with the refreshed #341 in 31 files, primarily boss resource and draw code. The other current-base review overlaps are listed by path. The standalone review is open as [#349](https://github.com/zeroz41/pso-decomp/pull/349). [Builds and overlap paths](2026-11-20-osp-archive-review-and-layouts.json)

The cumulative branch at `45f6c97c98` restores the Vol Opt rock model and texture arrays, checks the archive request layouts and removes the obsolete lobby declarations. Both source and fork workspace reproduce retail with all 2,448 source objects linked and preserve all 1,147 historical data bytes. All 310 fork workspace checks pass, and 672 entries remain in the [fork source index](2026-11-18-fork-review-index.tsv).

## Particle factories and native sprite definitions on upstream master

The standalone review at `6d9f7bffe5` starts directly on upstream master `1fd561eae2`. Both particle factories use the shared world-position vector and return the native particle pointer. The atlas passes its task parent and sprite definition through the base and five quad constructors. The 191-file review matches the retail DOL with all 2,448 source units linked. The only six changed linker labels follow the constructor signatures, and the commit has zero Codex attribution.

The three local reviews reproduce retail together at `aa3fa4b709` across 480 paths. The particle change merges cleanly with the renderer alone. Combining it with the archive and renderer work resolved 39 shared paths, including one Gryphon shockwave that uses both recovered interfaces. The standalone review is open as [#350](https://github.com/zeroz41/pso-decomp/pull/350). [Build and overlap evidence](2026-11-20-osp-particle-review-and-actor-layouts.json)

Great Merge at `26fdc8afcf` also restores the native actor position initializer and word-sized action mask. The initializer retains the upstream name, uses `TObjChara` as its receiver and keeps the originally linked address. Twelve actor layout checks and the 66 updated callers pass the exact build. The fork workspace reproduces retail and passes all 310 checks. The [fork index](2026-11-18-fork-review-index.tsv) still has 670 open entries.

## Renderer, archive and particle publication

All three source reviews are open against upstream master at `1fd561eae2`. The branches keep their independently validated trees.

| PR | Scope | Published head | Changed files |
| --- | --- | --- | ---: |
| [#348](https://github.com/zeroz41/pso-decomp/pull/348) | Ginja materials and Ninja model callbacks | `7af1ccc64f` | 141 |
| [#349](https://github.com/zeroz41/pso-decomp/pull/349) | BML archive lifetimes and load requests | `abb5022ed6` | 317 |
| [#350](https://github.com/zeroz41/pso-decomp/pull/350) | Particle factories and sprite definitions | `6d9f7bffe5` | 191 |

The seven refreshed heads for #336–342 fast-forwarded to the locally tested commits listed above. All 14 open reviews were ready for review and mergeable against master at publication. The GitHub-visible commit audit checked 29 author and committer identities and all commit messages. It found zero Codex attribution and zero co-author trailers. The ten updated or newly opened reviews queued GitHub matching checks for their published heads. [Publication and commit audit](2026-11-20-upstream-publication-348-350.json)

## Consolidated source reviews

The 14 open reviews fit into three locally validated source batches on master `1fd561eae2`. Each batch contains the published source commits for its group and passes the retail DOL, linker and coverage checks independently.

| Group | Open reviews included | Local head | Files |
| --- | --- | --- | ---: |
| Resource loading, streaming and rendering | #338, #348–350 | `6109209848` | 562 |
| Frontend windows, character saves and quest transfers | #339, #340, #342, #345, #347 | `1de8691e80` | 588 |
| Combat, boss encounters and stage objects | #336, #337, #341, #344, #346 | `0bf3d567f9` | 531 |

The combined frontend and combat build at `ceedccb08a` matches retail after reconciling five overlapping files. The resource batch has nine conflicting files with the frontend and 87 with combat, concentrated in shared model, effect and archive callers. The first two groups together have 94 overlapping files with the resource batch. The actor movement component `45da070185` independently matches retail across 329 files. It restores the actor position and velocity vectors and shared rotation storage and is available for a related batch.

Great Merge at `54128af4ad` keeps the existing BML allocator and release names, ADX status and sector-size names, and the three player movement helper names. The implementations still use recovered receivers and typed arguments. The fork workspace matches retail, keeps all 27,031 required symbols, and passes 294 tooling tests, 11 layer tests and five host checks. The candidate source histories had zero Codex author, committer or co-author entries. The existing public reviews remain open. [Validation, attribution and overlap evidence](2026-11-20-consolidated-source-reviews.json)

## Integrated review stack with actor movement

The resource, frontend and combat groups reproduce retail together at `4421f385ee` across 1,504 files. The resource merge reconciles 94 files using the shared BML, ADX, particle and model-capture interfaces.

The expanded combat and stage group at `e57489ffb9` includes the actor position, velocity and rotation layouts across 779 files. It passes independently. The three groups with that expanded combat branch reproduce retail together at `909e18e6a4` across 1,556 files. The stack includes all 14 public review heads, keeps all 27,572 exact functions and 2,448 linked source units, and accounts for all 1,147 original data bytes. It loses no linked or exact coverage against cumulative Great Merge. The older fish callback fragment keeps upstream's source because the linker uses the recovered `ModelNodePositionCapture` owner.

The source-scope comparison with `54128af4ad` leaves 124 changed paths outside the three groups and 399 differing shared paths. The remaining work includes title and Guild Card windows, resource and particle layouts, and the PPP and network runtime. The exact file lists are recorded for grouping by owning interface. Publication is still local. [Integrated build and residual source inventory](2026-11-20-consolidated-integration-with-actor-layouts.json)

## Frontend titles, Guild Cards and Short Mail

The expanded frontend review at `fdfc8b3f1c` covers 622 files on current upstream master. It restores the Short Mail and Guild Card record layouts, native confirmation and composer windows, and typed title sprites and scene transitions. The shared word-copy routine has explicit source and destination arguments. The Guild Card accessor keeps `get_card_id` and the typed Short Mail table keeps `lbl_80513F70`.

The 84-file frontend replay on the three-review stack reproduces retail. The joined review stack at `289daa58dd` has the same tested tree and covers 1,588 files. The standalone review, joined stack and cumulative source `2ed1cfc781` each retain all 27,572 exact functions, 2,448 linked units and 1,147 historical data bytes. The cumulative and fork-layer builds retain the existing Challenge result compiler directive. The fork workspace passed all 310 checks and kept all 27,031 required symbols.

The source comparison leaves 91 paths outside the reviewed changes and 350 differing shared paths. The current texture-list receiver accounts for 247 of those paths by itself. The scope and exact file lists are recorded locally. [Frontend and remaining source evidence](2026-11-20-frontend-title-and-mail-reviews.json)

## Typed renderer texture lists and network frames

The resource review at `e6aca7b1bf` covers 674 files on current master and matches retail independently. The renderer's `set_global_param` now takes `GinjaTextureList *` and writes the typed scene-state member at its original address, `0x803DA798`. The source keeps upstream's function name. The receiver change updates 599 calls across the build. The combined texture-list replay at `74655b1000` matches retail and incorporates the standalone resource branch. Its 247 texture-only paths now match the cumulative source.

The 12-file PPP component at `925fa3bbd9` uses shared frame declarations and typed IPv4 and TCP records with the original entry-point names. It matches retail independently. The integrated source at `1b4a1c5af3` matches retail across 1,655 changed files, preserves all 27,572 exact functions and 2,448 linked source units, and accounts for all 1,147 original data bytes. The reviewed histories have zero Codex attribution. The component is staged locally with the larger reviews.

Cumulative Great Merge at `404d82cfd2` and its private tooling workspace match retail. The fork-only Zako texture-slot test uses the restored setter name. The workspace retains all 27,031 symbols and passes all 310 checks. The remaining source comparison has 180 paths, including 24 outside the integrated reviews and 156 shared paths with further differences. [Build and remaining source evidence](2026-11-20-texture-lists-and-network-frames.json)

## Audited boss effects, enemy ownership and ground effects

The remaining 180 paths from the prior cumulative source have a recorded decision. The replay at `31d3096942` carries native model breakup, enemy group and drop ownership, typed archive calls, and stage-object layouts in 146 files. It keeps the existing version on 34 paths with incidental casts, include order, compiler directives or obsolete retention entries. The model-breakup and group transfer helpers keep the upstream names `create_breakup_mdl`, `copy` and `link_chain_nodes` with their recovered types and owners.

The ground-effect recovery at `1b85ee8047` gives the two emitters actual position vectors and gives the Challenge dead-spot wrapper its explicit radius. All 15 ground-effect calls use the typed position interface. The full source and private tooling workspace match retail, preserve all 27,572 exact functions and 2,448 linked source units, and account for all 1,147 original data bytes. The combined source has zero Codex attribution. Cumulative Great Merge at `8140509c22` uses the exact tested source tree. The fork workspace passes all 310 checks and retains all 27,031 required symbols.

Applying the 146-file follow-up directly to the earlier standalone combat branch produces 98 conflicts, mostly where the branch lacks the resource and frontend interfaces already present in the combined build. The current frontend and resource branches have 22 overlapping paths when merged first. The older historical ledger still needs owner comparisons. [Scope, build and fork-layer evidence](2026-11-20-audited-combat-and-ground-effects.json)

## Consolidated reviews in landing order

All 14 current review heads are in three source batches. Each row measures the diff against the preceding row, starting at upstream master `1fd561eae2`. Each batch reproduces the retail executable and passes the strict coverage check. All 27,572 functions, 2,448 source units and 1,147 historical data bytes are preserved.

| Order | Review scope | Covered PRs | Local head | Files |
| ---: | --- | --- | --- | ---: |
| 1 | Frontend windows, character saves and quest transfers | #347, #339, #340, #342, #345 | `eb7cb1a1ea` | 649 |
| 2 | Resource loading, streaming and rendering | #349, #338, #348, #350 | `139544d996` | 679 |
| 3 | Combat, actor layouts and stage objects | #341, #336, #337, #344, #346 | `626f831042` | 929 |

The resource review reconciles 39 overlapping hunks in 22 files with the frontend batch. The combat batch uses the already validated actor, stage and effect implementations on the combined frontend and resource base. It also restores the typed position, ground contact and normal vectors in De Rol Le, Barba Ray, Vol Opt and Challenge. Both upstream method names are preserved. The separate 12-file PPP change on top produces `9a3b2715c5`, identical to the verified Great Merge source at `7286601fc8` across 1,713 changed files. All 67 candidate commits passed the attribution audit.

The upstream maintainer asked for one consolidated PR. The full source is available as a single candidate, and the three tested increments are available for sequential review. Publication and supersession are pending. [Maintainer feedback](https://github.com/zeroz41/pso-decomp/pull/341#issuecomment-7056770875) · [Matching build and review audit](2026-11-20-ordered-upstream-review-consolidation.json)

## Historical build ranges and character-selection slots

The historical fork's 3,637 selected units describe 7,332 address ranges. The current 2,448 source units cover all of their code and non-padding data. The 167 omitted bytes are alignment padding. The linker and source reports also account for the historical force-active entries. Five cave archive entries now come from the exact shared resource table. The fork workspace preserves the active MusyX build integration and archives the original GC/2.0 configure script.

The frontend at `c7dfef378c` uses one typed player label record for both slot screens and for the linked item label setter. Slot positions and icons use the existing classes. The setter keeps its upstream name and linked address. Each stage and the fork workspace reproduce the retail DOL. The fork workspace passes 294 tooling tests, 11 layer tests and five host checks.

The historical audit resolves eight rows, leaving 662. The record includes the original split, symbol-retention and modem restore evidence. [Historical and slot audit](2026-11-20-source-split-and-slot-audit.json)

## ADX players, mixer volume and gameplay sound

Great Merge at `bc3d32eb3f` restores the ADX player receiver for creation, playback, state and queue access. The GCRNA volume call uses the signed argument and the actual stream receiver at offset 0xC. The resource batch and the combat batch match in landing order. The gameplay sender and receiver share the 12-byte sound command, and the voice binding uses the native position member at offset 0x88.

The historical audio audit closes three entries, leaving 659. The materialized fork matches retail and passes 294 tooling tests, 11 layer tests, and five host checks. [Audio ownership and build evidence](2026-11-21-adx-player-and-gameplay-sound.json)

## Restored card, Photon Blast and Bal Claw interfaces

Comparing the earlier verified source at `a0ab810dd1` with the replay on current upstream identified three recoveries that needed to be carried forward. The card selector now constructs its real cursor, icon, title and warning tasks. Photon Blast uses typed participant records and the existing virtual direct-attack interface. Bal Claw uses the shared task parent, target cursor and minimap interfaces.

The revised review stages and the combined source reproduce retail at `7b3da3891a`. The fork workspace passes all 310 checks with its generated retention list refreshed. The audit updates 11 supporting records. 659 historical comparisons remain open. [Recovery and validation evidence](2026-11-21-card-cursor-photon-and-balclaw.json)

## Typed Challenge and Hunter Guild menu interfaces

Great Merge at `86578b66cc` gives the existing yes/no factory a shared declaration for its layout point, text and menu result. The offline and online Hunter Guild sequences use typed menu and quest-thread owners at their existing offsets. Offline result handling indexes the callback table directly, and the server confirmation callback uses the native server fields. The replay preserves the upstream symbols and field names.

All three stages, the combined candidate and the materialized fork reproduce retail. The 20-file update changes zero linked function labels and keeps all 1,147 historical data bytes accounted for. The fork workspace passes all 310 checks. Five historical entries gained source evidence and 659 comparisons remain open. [Challenge and Guild evidence](2026-11-21-challenge-and-guild-types.json)

## Native player HUD and warning windows

Great Merge at `7286601fc8` restores typed ownership of the six player HUD children and the original menu virtual dispatch. The status and information providers return their native window types. The lock-on path uses the 16-bit target ID and the existing create and bind calls. The four-player item warning now has a native constructor and checked fields. The dead list uses a typed message-window pointer.

The 17-file recovery changes one linker label, from the handwritten four-player warning constructor to the native constructor taking its parent. The three review stages, consolidated source and fork workspace reproduce retail with all 27,572 functions, 2,448 linked units and 1,147 historical bytes accounted for. The fork retains all 27,031 required symbols and passes all 310 checks.

The owner comparison closes four historical entries for mag oscillation, the character preview loader, the Seabed wreck collision object, and actor lights. The open ledger now has 655 rows. The broader token comparison found 215 partial matches to guide the remaining source-owner checks. [HUD and historical audit evidence](2026-11-21-native-hud-and-warning-windows.json)

## Ordered upstream review candidates

The local review sequence under `great-merge/queued/` starts on upstream `49b48c32e6`. Each row is the diff from the previous row. The existing source landing and working-fork builds remain separate from this submission sequence.

| Scope | Local head | Files |
| --- | --- | ---: |
| UDP datagrams, requests and packet lifetime | `fbfa587ae9` | 60 |
| Stage objects and weather | `de6be2385a` | 37 |
| Quest, player inventory and resource lists | `4624395d33` | 51 |
| Audio streaming, disc archives and movie REL lifetime | `702c76a225` | 102 |
| Challenge and duel result windows, page indicators and record types | `b65ecabf8a` | 51 |

All five stages reproduce retail and pass the strict check against the preceding stage. The final stage preserves matched and source-linked coverage against upstream, the historical fork, and the standalone results review. The only manual overlap in the sequence is the BML archive caller, which uses the quest file-extension provider and the audio ADXF handle together. Challenge and duel results also build independently on upstream at `32719bf02d`. These are local branches pending upstream approval.

## Local landing checkpoint with all four subsystem histories

`great-merge/current/landing-checkpoint` at `c685c00b1e` contains the four exact review branches and uses the verified Great Merge source tree at `3f3792f434`. The actor/player checkpoint `208df9435e` joins the actor fields with typed sound, particle and player calls. The display/world checkpoint `84e3194968` adds 22 ownership fixes from the remaining audit. That work restores native Berura methods, typed boss and stage resources, and shared display declarations. The shop and quest changes also pass on their narrower player review at `74e7cb1163`.

The complete source tree covers 1,797 files against the pinned upstream and includes a 36-file refresh. It restores the shop and quest message arguments from `d7143585fb`, five native team-window accessors, the typed city firework position and particle handle, and native Merill Lia encounter ownership. Merill Lia keeps the exact asset bank, state dispatch and hurt behavior. The complete tree and working fork match retail and retain all 27,572 functions and the matched and source-linked coverage of both checkpoints. All 1,147 original inventory bytes are accounted for. The 133-path tooling overlay round-trips, and all 11 fork-layer tests pass.

The standard Git preview of the two checkpoints found 334 overlapping paths. The assembled checkpoint uses the already validated Great Merge implementation for shared source. The dry replays found the typed firework fields as a substantive clean edit, which the refreshed source now contains. Remaining clean deltas are mostly redundant includes, an obsolete declaration, and provider comments. A retail match verifies executable behavior. The overlapping source variants and historical source mappings still need review before landing upstream. [Source audit](2026-11-19-landing-source-audit.json)

## Historical item drops, window drawing, and Barba Ray photon ownership

Great Merge source `ef8b7f3c2c` combines 39 changed files. The source, review and working trees reproduce the retail executable and retain matched and source-linked coverage against upstream, the historical fork and the previous combined source. All 90 original byte ranges still account for 980 linked bytes and 167 alignment bytes. The working layer materializes 133 local paths, and all 11 fork-layer tests pass.

| Work | Exact combined-source component | Review increment |
| --- | --- | --- |
| Native 6x5F packet construction, 6x60 request fields, and the drop generator's `TItemData` payload | `b99dc3cd47` | `acfcd51610`, 11 files |
| The shared draw context for text clipping and UV sprites, with native numeric glyph declarations | `a3dd561841` | `9bc06303e4`, 17 files |
| Native Barba Ray photon pad and bullet constructors, virtual hit dispatch and the boss-owned hit-effect receiver | `993a01c2ba` | `e5280c4a65`, 13 files |

The three review increments were validated independently. The player replay merged without conflicts. The display replay keeps its existing allocation and texture declarations. The world replay keeps its sound-call ABI while using the native pad constructor.

## Earlier Great Merge investigation notes

The older local branch `great-merge/main` at `bc3df70d93` adds 24 investigation notes that were missing from the fork layer. They are preserved byte for byte under their original paths in `fork/notes/`. They describe earlier experiments and refer to the source layout at the time.

The legacy source comparison against `6cfb23a4b3` covers 1,197 changed source, header, and config paths. It finds 22 already identical and 49 whose changes are already present by three-way replay. The remaining cases include moved owners and overlapping implementations. The typed Challenge event and main-menu entry layouts already exist in their current source owners. Use the older changes as evidence when checking other shared layouts and source ownership.

## Validated dependency order within four subsystem stacks

These source-only stacks are based on upstream master `6b080e67ab`. The file counts describe the complete stack versus upstream. The commits within each stack retain the dependency order for review.

| Review order | Local branch under `great-merge/current/` | Head | Changed files |
| --- | --- | --- | ---: |
| Network startup, packet lifetime, audio streaming, disc archives and movie lifetime | `network-audio-stack` | `fb53599452` | 157 |
| Rendering and camera presentation, then native windows and keyboard | `render-window-stack` | `98131699ee` | 772 |
| Allocation and memory, then player systems, then spatial sound and effects | `player-memory-spatial-stack` | `1a5ba8e2e8` | 723 |
| BML/GVM assets, then stage objects and Challenge, then enemy and boss combat | `world-enemy-stack` | `010a80a015` | 798 |

Networking adds 99 audio, disc and movie files on the existing 60-file network review. Renderer and window reconciliation resolves nine shared files while keeping the native keyboard and window owners. Memory precedes both player and spatial work so they share allocation, position and sound ownership. BML/GVM archives precede Stage and Enemy so that those callers share the native resource API. Every stack reproduces the retail executable and retains upstream, historical and component matched and source-linked coverage.

The four stacks and the actor prerequisite touch 1,765 of 1,777 comparison entries, counting both names for two renamed files. This measure counts path coverage. The 12 other paths belong to the new historical source replay. The larger stacks still overlap on shared code. A cross-stack merge preview found five conflicts between networking/audio and rendering/windows and 123 between rendering/windows and world/enemy.

The exact network startup commit `d892292ba8` is the shared parent for four local delivery branches. Their file counts are relative to upstream. Review each subsystem in the order shown.

| Scope | Local branch under `great-merge/current/` | Head | Changed files |
| --- | --- | --- | ---: |
| Network and audio, renderer, windows, selection, and the draw context | `delivery-network-render-window` | `cf8d847e24` | 949 |
| BML/GVM archives, stage, enemies, then native boss and photon ownership | `delivery-network-world` | `e80e5badf2` | 930 |
| Allocation, player and inventory, spatial effects, item drops, and quest/shop messages | `delivery-network-player-spatial` | `80437bd0a1` | 802 |
| Shared actor motion, animation and presentation | `delivery-network-actor` | `570ad35a4c` | 441 |

Rendering follows audio and disc streaming. The renderer resolves four overlapping include groups. The window layer keeps the typed audio slot in the native status window. The selection and lobby commit adds 12 files. The window context pass adds a further 17. The other three stacks replayed cleanly directly from the network commit. The world stack closes with the boss ownership and photon commits. All four branches reproduce retail and preserve matched and source-linked coverage.

The preview between the display and world stacks found 134 shared-file conflicts before the historical boss patch. Great Merge's exact source matches one complete input file in four cases. The preview contains 37 include-only conflicts. Among the files with shared archive or texture interfaces, resolve the typed providers and their callers together. The actor and player branches also share code with display. Each branch remains reviewable from the common network base while those overlaps are reconciled for landing.

The combined display/world checkpoint `db40e8a83a` covers 1,436 files against upstream and contains both current review branches as ancestors. The original interface-owner resolution at `428da61122` is independently reproducible. The refresh adds the latest 30 window and Barba Ray files and passes the retail and strict coverage checks against both review parents. Among 34 initially provisional paths, two now have identical source blobs and four differ only in their include lists or order. Twenty-eight still need source review before using the checkpoint as a landing branch. [Conflict decisions](2026-11-19-display-world-resolutions.json)

The combined source at `6cfb23a4b3` restores the full-width character-selection and lobby predicates, typed word-selection calls, Olga Flow's Tube, phase and scene ownership, and native Dark Falz and Gol Dragon model nodes. The source and working fork reproduce retail with all 27,572 functions and retain exact and linked coverage. The original 90-range ledger again yields 980 source-linked bytes and 167 alignment bytes. The separate fork layer still applies all 133 local paths and passes all 11 tests.

## Historical fade and debris replay and review assignments

The 21-file replay at `99d8d2c898` restores the native negative fade method at `0x800A0554` with all six enemy callers, and uses the fork's typed debris position and spread vectors with all known consumers. The retail executable and matched and source-linked code and data are preserved. All 90 original ranges still account for 980 source-linked bytes and 167 alignment bytes. The working fork reproduces retail, its 133 overlay paths round-trip and all eleven layer tests pass.

| Review | Local head | Changed files |
| --- | --- | ---: |
| Enemy, boss and battle parameters | `ad99e7980f` | 344 |
| Player, techniques, inventory, holds and quest runtime | `7148a593c1` | 275 |
| Stage objects, collision, debris and Challenge encounters | `cdc0344e09` | 206 |
| Rendering, presentation, preview and scratch-vector stack | `8c368b4a6c` | 428 |
| Window framework, keyboard and drawing | `ca78f691aa` | 380 |
| Camera, scenes and character preview | `fc59b9c0a4` | 168 |
| Audio, disc archives, REL and movie lifetime | `5e789c86fb` | 99 |

The stage review is measured against the BML/GVM provider at `d7f1fb19b2`. The rendering stack branches from upstream and validates its shared renderer, presentation, starlight, preview and scratch-vector layers together. All listed builds reproduce retail and pass the project gate. The inventory sorting and record helper probe reaches the linker and needs the project’s native array allocation and release operators from the shared memory review. Its staged source checkpoint is `11fc7dae6d`.

The 277-file player review at `aa306b9e62` uses the native memory parent `7cf8dfc61c`. It includes the typed inventory header, record and sorting helpers and equipment callers. The native array operators resolve the standalone inventory link. The original 275-file player review remains available. Both variants reproduce retail.

All 1,763 combined diff paths now have validated review assignments. The ordered file audit counts 1,765 entries when it includes both sides of the two renames. Of these, 1,095 already match a complete file in a review and 216 match after the proposed order is applied. The audit found 407 overlapping entries without an exact standalone file and 47 other entries whose clean union differs from the combined source. These entries need ownership decisions and full stack builds before publication.

A raw three-way replay confirmed 12 historical source deltas already present in their mapped owners. Four historical technique resource ranges also retain all 1,596 exact source-linked bytes in the consolidated technique controller. The historical source index has 1,003 records awaiting owner comparison and 944 with partial evidence. The remaining replay candidates need source review.

## Combined great-merge on upstream master `af11a99125`

The combined source at `5439b74826` and the complete source snapshot at `2a2a454320` incorporate the new upstream master. The combined merge retains the prior 40 source commits in its history. It reconciles all 42 overlapping paths and updates the related declarations, constructors and callers. The replay keeps the compiler-emitted breakup and window virtual tables on upstream's new owners. The consolidated balloon unit retains 27 replayed functions, and the split status unit uses the typed draw context with the native list row.

Both source builds reproduce the retail executable, SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`, and pass the project checker. The address-level comparisons preserve every exact and linked function and data range from the prior combined build and the new upstream base. The historical fork report still counts 2,382 more total data bytes because its report uses the older split layout. Its comparable exact and linked coverage has no losses, and the same accounting difference was present before this replay.

The [original data ledger](2026-11-18-fork-data-ranges.tsv) accounts for all 1,147 bytes again on the new base. It verifies 980 source-linked bytes, including the 24-byte keyboard virtual table at 0x804D0004, plus 167 bytes of alignment padding.

The working fork reproduces retail and passes its regenerated linked-symbol check. Its documentation and tools are under the fork-only layer. All 133 overlay paths round-trip and all eleven layer tests pass. The network, resource, encounter drawing and world-object standalone branches also point to their already validated replays on `af11a99125`. The standalone review updates are listed below. The historical source audit continues in the fork review index.

## Character-selection plates and slots

The 15-file replay at `09e54f5530` restores both selection plate layouts, move-plate construction, the shared serial and password plate drawing interface, and the numeric slot singleton factory used in the single-player and multiplayer menus. It replays the fork changes from `b12e7f4cc2`, `20662930dc`, and the related rendering changes from `264695a61f` onto the current source owners. The coordinate and draw parameters are mutable because the target compiler otherwise changes the instruction order. The geometry and drawing helpers read the input coordinates.

The standalone review at `e78bca5864` is based directly on upstream master `af11a99125` and uses its texture binding. The combined source and standalone review reproduce the retail DOL and pass the project checker. Six renamed exports keep their original sizes and addresses, and 36 direct calls reach them within the eight affected units. All 239 source-linked functions in those units match. Seven plate tables and two virtual tables retain 216 original source-linked bytes. The standalone branch has the same 24-byte keyboard-table coverage gap as upstream master. The combined branch retains those bytes through the window review.

The working fork passes its symbol inventory check, all eleven fork layer tests pass, and all 133 overlay paths round-trip. The [fork source index](2026-11-18-fork-review-index.tsv) reconciles 4 records and adds evidence to 14 others. It has 1,200 records awaiting owner comparison and 853 with partial evidence.

## Character preview requests and buffers

The 16-file replay at `be20c53a56` completes the shared numeric slot and unsigned cursor contracts from `a84a5d3f17`. The model and texture factories share their original argument records with callers. The preview request owns its model, texture and archive dispatch. AFS requests own the full-width completion check and loaded-buffer lookup. The model and texture constructors accept mutable pointers to retain the original instruction order. Both constructors read those records.

The local review at `90d87fc82b` adds one commit on top of the archive prerequisite `86d1a7faec`, which is based on upstream master `af11a99125`. It uses the archive branch's heap interface. All four source builds reproduce the retail DOL and pass the project checker. Fourteen renamed exports retain their addresses and sizes. The seven related units retain all 68 exact source-linked functions, 23 original calls to the renamed interfaces, and 48 bytes of exact slot cursors. The archive-dependent review keeps the historical fork coverage already present in its prerequisite. The combined stack covers the original 24-byte keyboard table through the window review.

Upstream already contains the fork's draw-line fold and the typed copy of the vertices. All 17 original functions remain exact and source-linked. The working fork passes symbol retention, all 133 fork-only overlay paths round-trip, and all eleven layer tests pass. The [fork source index](2026-11-18-fork-review-index.tsv) reconciles 6 records and adds evidence to 8 others. It has 1,190 entries awaiting owner comparison and 857 with partial evidence.

## Character creation effects and color rendering

The 44-file replay at `a62c10cd43` carries the fork's typed creation menu icons, heading labels, wall and fade renderer. The indexed icon animation and its callers use the full-width result of the original glyph extent query. The grid and fade strip retain the original positions and opacity behavior. The geometry interfaces at `0x801E352C` and `0x801E35C4` belong to the shared 16-byte vertex-and-color list. The letterbox, fade and split-screen dividers use that list directly. Other callers retain their existing descriptor storage and use the shared receiver type.

The standalone review at `5430552ee1` is one commit directly on upstream master `af11a99125`. Both source branches and the working fork reproduce the retail DOL and pass the project checker. Six renamed exports retain their addresses and sizes. The 30 source-linked units retain all 583 exact functions, 50 original calls to the recovered interfaces, and 352 original bytes in the nine checked icon, heading and fade data ranges. The standalone review preserves upstream's coverage. The combined stack retains the keyboard table through the window review.

All 133 overlay paths round-trip and all eleven fork layer tests pass. The [fork source index](2026-11-18-fork-review-index.tsv) reconciles 10 records and adds evidence to 7 others. It has 1,173 records awaiting comparison and 864 with partial evidence.

## Texture inputs and compass sprites

The 19-file source replay at `313c0f88bc` draws from `1539d9b78d`, `d1a35e4a99`, `fc3ec799fb` and `e52b2c722a`. The shared 0x24-byte Ginja input types configuration and entry registration for the menu font, image buffers, archive requests, captures, signboard, and effects. The radar and lobby share the 0x20-byte sprite descriptor and 0x14-byte frame layout. The radar loader, release path, binder and descriptor all use the same typed texture-list slot at `0x805D5F4C`.

The 24-file standalone review at `3c9cccdd7a` is one source commit directly on upstream master `af11a99125`. It carries the typed texture-entry layout and the corresponding field references onto that base. It keeps upstream's allocation and release calls. All four source builds reproduce the retail DOL and pass the project checker. The combined branches retain all 215 exact functions in 13 affected units. The standalone retains 243 exact functions in 16 units. All four retain the same 24 direct retail calls to the four checked entry points and 316 exact bytes in seven original data ranges. Address coverage has no losses relative to each parent. The standalone inherits the upstream keyboard-table baseline, and the combined stack retains the 24 bytes through the window review.

All 133 overlay paths round-trip and all eleven fork-layer tests pass. The [fork source index](2026-11-18-fork-review-index.tsv) reconciles 4 records and adds evidence to 15 others. It has 1,162 records awaiting comparison and 871 with partial evidence.

The bulk replay preview used the fork's first-parent branch point `1f2ecc1887` and current source ownership. Of 218 unambiguous whole-file mappings, 21 have a clean candidate, two already reproduce the current file, and 91 have changes outside overlapping sections. The remaining 104 need a closer comparison. The preview is a routing aid. Each candidate still needs source review and a build.

## Shared scratch-vector storage

The 17-file replay at `c8fe70331a` carries `e8128ff09d` onto the current source owners. Both scratch records use the same 32-byte type and expose their original vector at offset zero. The render unit owns both records. Camera cursor, player lighting, enemy movement, collision, traps, and world-object callers use the shared declaration.

The standalone review at `940dabd110` is one source commit directly on upstream master `af11a99125`. The four source builds reproduce the retail DOL and pass the project checker. The 15 affected units retain 1570 exact functions in the combined builds and 1577 in the standalone. Each build retains the two source-linked ranges at `0x8050BEE0` and `0x8050BF00` for 64 exact bytes. All four preserve the address coverage in their parents. The working fork keeps its existing host compiler guard in the collision query.

All 133 overlay paths round-trip and all eleven fork-layer tests pass. The [fork source index](2026-11-18-fork-review-index.tsv) reconciles 2 declarations and adds evidence to 15 source records. It has 1,159 records awaiting comparison and 872 with partial evidence.

## Camera views and controllers

The replay at `14f9743af7` carries the camera members and registry accesses from `dbc976eb97` and the split-screen vector and orbit controls from `3717ee6db2`. It keeps the original low-byte selector, 48-byte view copy, 0x70-byte orbit-controller layout, and the second controller input context. The conversation controller owns its position and target vectors. The main camera task retains the original field reads that match with the current compiler profile.

The six-file standalone review at `4efd7c3fe9` is one source commit on upstream master `af11a99125`. All four builds reproduce retail and pass the project checker. The 3 affected source units preserve 97 exact functions in the combined stack and 97 in the standalone patch, including both split-screen accessors and the orbit update. The address audit verifies 700 source-linked bytes covering the NPC destinations, camera vtables, look-at up vector, camera-mode float pool and motion sampler tables. Each branch preserves the address coverage of its parent.

All 133 overlay paths round-trip and all eleven fork-layer tests pass. The [fork source index](2026-11-18-fork-review-index.tsv) reconciles 2 declarations and adds evidence to 5 source records. It has 1,152 records awaiting comparison and 877 with partial evidence.

## Dragon material fade and grouped rendering reviews

The replay at `69a8e24daa` carries `e3a3822f2f` onto the Dragon and Gol Dragon source owners. The floating-point setter belongs to `MaterialColorFade` and writes the rate at offset 0x10. All 6 original calls use the actual fade state. The Gol Dragon's integer operation keeps its original address and its X position field remains a 32-bit float at 0x688.

The five-file standalone component at `cc3bff1e8b` is directly based on upstream master `af11a99125`. The four component builds reproduce retail and pass the project checker. Both affected source units retain all 345 exact functions, and the two material vtables retain 88 original bytes. Address coverage is preserved relative to each parent. All 133 overlay paths round-trip and all eleven fork-layer tests pass. The [fork source index](2026-11-18-fork-review-index.tsv) reconciles 1 declaration and adds evidence to 3 records. It has 1,151 records awaiting comparison and 877 with partial evidence.

Two grouped commits consolidate the related changes for local review. `great-merge/current/camera-and-radar-views` at `e89ec01968` combines the camera controller replay with radar views and markers in 25 files, covering 623 exact functions in 19 affected source units. `great-merge/current/material-opacity-and-dragon-fade` at `1c20f1a945` combines the Dragon fade with the shared opacity class and its callers in 51 files, covering 1516 exact functions in 26 affected source units. Both grouped commits are based on upstream master. They each reproduce retail and pass the project checker. The combined validation tree at `73cd80f7ff` also passes both checks.

## Title rendering and world resource tables

The title replay at `41a07248bc` carries the shared resource layout from `296081bae4`. The 46 title sprites and 46 frame entries use the same descriptor types as the lobby and radar. The original accessors return the texture list and sprite directly. The texture list declaration explicitly retains its original .data placement. The English and Japanese mode-change tables have names that follow the two language cases.

All four source builds reproduce retail and pass the project checker. The three affected units retain 67 exact functions and 2,874 exact source-linked bytes across twelve title and mode-change ranges. All 133 overlay paths round-trip and all eleven fork-layer tests pass.

The address audit confirms that six fork data files for mines, Seabed walls, ancient wrecks and forest warps already emit every original range from their current native owners. All 180 named objects retain 3,768 exact source-linked bytes. Eleven placeholder labels have descriptive native class-name symbols. The two warp confirmation methods keep current pointer arguments because their callers pass the confirming player. The [fork source index](2026-11-18-fork-review-index.tsv) closes 7 records and adds evidence to 7 others. It has 1,137 records awaiting comparison and 884 with partial evidence.

Two local review branches are based directly on upstream master `af11a99125`. `great-merge/current/title-and-compass-rendering` at `fb95d7b4a9` groups the title changes with texture inputs and the radar and lobby compass in 33 files. Its 19 affected units retain 310 exact functions. `great-merge/current/world-resource-tables` at `2c74919ee9` groups the world-object names, resource ownership and typed table users from `97f1a285af`, `cd2697d2dc`, and `6b7e2c53f3` in 20 files. Its 10 affected units retain 360 exact functions. Both branches reproduce retail and pass the checker independently and in the combined validation at `df36afcd13`.

## ADX stream files and grouped audio review

The twelve-file replay at `e254c361e1` carries the 0x40-byte ADX stream file layout and seven file operations from `b11af52845` into the current audio and archive owners. ADX, LSC, ADXF and the stream driver use that layout for size, offsets, seek, initialization and the ring buffer. The seven exports keep their original names, addresses and lengths. The standalone review at `0e967ac715` starts directly at upstream master `af11a99125`.

The grouped audio and archive review at `8d955ba78e` combines this replay with the sector reader, signed ADXB channels and sound pitch and duration from `f59cf4090d`. The overlapping file keeps the archive reader's named fields and uses the typed file calls. The 73-file review preserves all 899 exact, source-linked functions in its 55 changed compilation units.

All five source builds reproduce the retail DOL and pass the project checker. The nine stream-file units preserve all 100 exact functions and the 2,560-byte source-linked request pool at `0x80575140`. Each build preserves its parent's address-level coverage. The upstream-shaped reviews share upstream's historical 24-byte keyboard table deficit. The combined stack preserves those bytes through the window review. The 133 overlay paths round-trip and all eleven layer tests pass.

The [fork source index](2026-11-18-fork-review-index.tsv) reconciles five equivalent sources and records the scope covered in ten other source files. It has 1,127 entries awaiting comparison and 889 with partial evidence.

## Window drawing and textured-quad clipping

The 26-file replay at `4640c99919` carries the typed drawing and fade work from `1ea275a10d` and `ac66ceeead` into the current window owners. The shared draw context transforms the quad bounds, and the clip-and-transform call accepts the original 0x20-byte textured quad. Both keep their existing linker names. The keyboard fade uses the fork expression without the local common-subexpression override and keeps its signed tick and unsigned alpha conversion.

The review at `26e763735b` has one follow-up commit above the window-frame prerequisite `4618815064`, which supplies the draw-context layout. The two source interfaces are used by keyboard, chat, action palette, menu and status renderers. All four builds reproduce the retail executable and pass the project checker. The 24 edited source units preserve 417 exact functions in the combined review and 417 in the local window review. Both keep 67 original direct branches to the two shared calls inside those units.

The address audit covers 144 source-linked bytes in the draw context float pool, viewport offset tables and the soft keyboard table. All 133 overlay paths round-trip and all eleven fork-layer tests pass. The [fork source index](2026-11-18-fork-review-index.tsv) reconciles one declaration and records the checked scope in 23 other files. It has 1,121 entries awaiting comparison and 894 with partial evidence.

## Player state, scaling and shrink packets

The 26-file replay at `6fd023cca6` carries the player-state fold from `3a4e3f6a3b`. One header replaces ten fragment headers with 40 shared declarations. Upstream already builds their implementations in the native player unit. The audit verifies 82 exact functions spanning 2,656 original bytes in the former fragments. The one-instruction accessor at `0x801BF914` returns its incoming pointer, which is used by 3 original call sites. Entity ID stores consume the original full-width arguments and write the low halfword.

The 30-file review at `62ac4dd661` combines this state work with typed scale, camera offsets and shrink and restore packets in two commits on upstream master `af11a99125`. It preserves all 1918 exact source-linked functions in the 14 changed compilation units. The original flag storage is at offset 4. The build with a constructed flag member inserted calls in two player constructors, so the final source keeps the original explicit initialization. The 25-file state-only review is at `ba9932dbb1`.

All five builds reproduce the retail executable and pass the project checker. The address audit retains the two source-linked scale constants. Each variant preserves its parent's address coverage. All 133 overlay paths round-trip and all eleven fork-layer tests pass.

The [fork source index](2026-11-18-fork-review-index.tsv) records ten reconciled header removals, two fully reconciled declarations and partial evidence for 7 source files. It has 1,119 entries awaiting comparison and 894 with partial evidence.

## Quest download text, cache and save images

The eight-file replay at `bc1a0d94db` carries the fork's quest request and input records into the current frontend, parser, cache writer and text converter. Both request consumers read the same 0x10-byte layout. The 39 input entries use their original eight-byte stride, with the character at offset zero and the signed length at offset four. The eight text exports retain the names from `5a7a047c3e` and their original addresses and sizes. The request keeps the type tag used in the original append_message_text linker name. The standalone replay at `629294b6a4` is based directly on upstream master.

The 28-file review at `1d0631030f` combines the text replay with the quest file cache and memory-card save-image review from `819c685f00`. The combined review starts directly on upstream master `af11a99125` and preserves 1,276 exact source-linked functions across 19 changed units. The five text units preserve all 198 exact functions and 352 source-linked bytes in the input table and scratch storage. All five builds reproduce retail and pass the project checker.

The linked decoder passes empty input, ASCII, mixed Shift-JIS, a full 36-entry input and overflow. The cache probe passes all 128 slots, ten linked pages, 80 buckets, 512 free-list nodes, file reads and page eviction. The fork overlay round-trips 133 paths and passes all eleven layer tests. The [fork source index](2026-11-18-fork-review-index.tsv) adds partial evidence to seven source and header entries.

## Enemy appearance resources, movement and targeting

The nine-file replay at `fde739ef91` carries Moja's typed appearance clamp and resource declarations into the current enemy, NPC and model-binding owners. The clamp uses the fork name and retains address `0x800ACA60` and its 72 original instruction bytes. The local component at `c5767c0784` is directly on upstream master. Mericarol's data owner exposes distinct three-entry tables for base stats, attack, resistance and movement. The names follow the four consuming calls. The 48 original bytes of those tables and the 24 original bytes of the Moja resource state stay source-linked.

The 80-file review at `952a177bf3` combines this replay with the enemy movement and target selection batch at `938245496d`. It starts directly on upstream master `af11a99125` and preserves all 2,379 exact functions across 35 changed source units. All five builds reproduce the retail executable and pass the project checker. The appearance component retains 121 exact functions across its five compilation units.

Linked execution passed eight appearance inputs, four phase tables, 34 guarded enemy-state cases and 19 player-targeting cases. The 133 fork overlay paths round-trip and all eleven tests pass. The [fork source index](2026-11-18-fork-review-index.tsv) reconciles the Moja resource header and records partial evidence for 5 other entries.

## Bulk replay of player techniques and item effects

Use the old review base, the donor tip and the current target for each three-way comparison. Start with an existing subsystem delta. The whole-fork trial surfaced 2,747 conflicting paths and the archived source queue surfaced 491. The old technique batch applied to current master with zero text conflicts. Replaying it on the Great Merge source would touch seven paths. The current tree already retains the technique changes there with the current rotation and scratch-vector fields, array allocation, particle declarations and three separate data owners.

The 57-file technique replay at `ff77410f60` retains the three upstream data splits and refreshes the matching declarations. A second commit adds the typed Bringer and equipment constructors and the shared reverse-tech callback pair. The resulting 71-file review at `94af1568a6` starts on `af11a99125`. The 17-path item-effects delta is also on the cumulative source at `8230aed0c4`. The weapon hit callback retains its full-register call sequence. The other equipment callers use the 16-bit owner ID declared by their factory.

The technique, grouped, combined and working-fork builds reproduce the retail executable and pass the project checker. The grouped review inherits the 24-byte keyboard table gap from master. The cumulative source and working fork retain that range and lose no matched or linked addresses against fork main. The checked tables retain 28 Bringer virtual-table bytes, 80 equipment virtual-table bytes, the 44-byte equipment collision template and the 56-byte reverse-tech callback table at their retail addresses. The three added retention names are regenerated only on the working fork. All 133 overlay paths round-trip and all eleven fork layer tests pass.

## Shared enemy registration, state and group links

The 40-file replay at `c794af0ca9` carries the source portions of `784ab5b061`, `32902e97ea` and `ecf2bfb910` together. The 24 caller branches to `0x8003F0E8` register their receiver in the object table. The fork's `TObjEnemy::register_by_id` expresses the underlying call. The 36 saved-state caller branches pass a pointer to the existing 12-byte lobby object record. Beast and Merill Lia use `TObjEnemy::has_group` and `TObjEnemy::link_last_group_child` at the original group call sites.

The local review at `6a5bf7aead` starts directly on `af11a99125`. It and the combined stack each retain all 2,260 exact functions across the 36 affected source units. The four corrected exports have the original addresses and sizes, and all 66 original direct branches reach those addresses. The standalone, cumulative source, review stack and working fork reproduce the retail executable and pass the project checker. The standalone retains the existing upstream 24-byte keyboard table coverage gap. The cumulative source and working fork retain that table and all matching and linked address coverage from fork main.

Linked execution passed 184 group queries, all 16 combinations of source and destination chain lengths, 32 saved-state cases and eight registrations. The fork-only overlay restores 133 paths and passes all eleven tests. The [fork source index](2026-11-18-fork-review-index.tsv) records the replayed interface in 34 original paths.

## Network startup, packet release and saved configuration

The 33-file replay at `0ddee16b36` carries the fork's startup APIs, packet-pool release, typed address helpers and saved configuration requests onto the existing C and C++ source owners. Three startup names follow the actual IPv4 routing, IPv6 routing and IPv6 neighbor-discovery records. The card load request applies the compiler frame alignment to its local parameter declaration, with a plain C-linkage prototype for callers. The named 19-byte file header remains source-linked at `0x804FD338`.

The local review at `2f060fcbb8` extends the existing buffers, DNS, timer and PPP review at `ebe7edd892`. The full review starts on `af11a99125` and covers 60 files with 670 exact source-linked functions in 33 affected units. The new component at `1b609ebabb` and the cumulative replay each preserve 393 exact functions across 20 affected units. All 12 updated exports preserve their addresses and sizes. Their 60 original direct branches retain their targets. All five builds reproduce retail and pass the project checker. The two upstream-shaped reviews inherit the upstream 24-byte keyboard table coverage gap. The cumulative source and working fork retain that table and all matched and linked address coverage from fork main.

Linked checks covered 140 packet-pool operations, 42 card load requests, 36 polls, five file-header inputs and eight startup records. The TCP queue probe passed 786 reassembly comparisons, 12 out-of-order receives, 2,528 gathers and 1,600 acknowledgments. All 133 fork-only overlay paths round-trip and all eleven layer tests pass. The [fork source index](2026-11-18-fork-review-index.tsv) accounts for the complete network codec and request units and adds evidence for three other paths.

## Quest stage records, localized filenames and downloads

The 15-file replay at `a2948b5308` uses one typed stage record for the challenge and battle lists and passes the actual filename field to the shared offline quest loader. The two filename helpers share one declaration across their quest, scene, map and archive callers. A null destination keeps the original in-place behavior. The stage-title call keeps the original third-register argument at its existing call site. The fork's eight-byte floor-name format is now a named constant at `0x80438660` in the consolidated floor window.

The local review at `8c7134e424` extends the quest download text and cache review at `1d0631030f`. It starts on `af11a99125` and covers 42 files with 1,604 exact source-linked functions in 32 affected units. The new component at `26190ba914` and cumulative replay each preserve 328 exact functions across 13 affected units. All 47 direct branches to the two filename helpers keep their original targets. The five builds reproduce retail and pass the project checker. The two upstream-shaped builds inherit the existing 24-byte keyboard-table gap. The cumulative source and working fork retain that table and all matched and linked address coverage from fork main.

Linked checks passed 20 filename transformations, 24 stage-list queries, and 132 localized filename combinations across all 22 stage records. The download cache passed its slot, page, bucket, free-list, read and eviction probe. All 133 overlay paths round-trip and all eleven layer tests pass. The [fork source index](2026-11-18-fork-review-index.tsv) reconciles three former quest or floor-window source paths and updates evidence for two others.

## Scene particles, radar-hide objects and cave signs

The 10-file replay at `ce18186367` carries the native source from `0550bf24c1`, `3462b8d7ad` and `690e4f79ae` onto the current object owners. The particle uses the original placement record and stores the emitter and ID in typed fields. The radar-hide constructor is emitted inside the consolidated radar unit. Both cave signs inline the same model traversal and maintain the original rendering order. The upstream-based versions use the camera rotation fields and texture-list call already on their base. The prior door and switch work already supplies its child model table, scene state, key counter and archive pointer from the current owners.

The local review at `7cb3ebf845` extends the existing world-resource review `2c74919ee9` on `af11a99125`. The full review covers 29 files and retains 401 exact functions across 15 affected source units. The new component `5d9be6d4ed` and cumulative replay each retain 41 exact functions across five affected units. The constructors remain at `0x80195400` and `0x80197490`. Both 52-byte virtual tables and their original relocations remain in the same locations. The five builds reproduce the retail executable and pass the project checker. The two upstream-shaped builds inherit the existing 24-byte keyboard-table gap. The cumulative source and working fork retain that table and all matched and linked address coverage from fork main.

Linked checks passed 32 particle constructions with their flag words and emitter pointers, 96 radar transitions and both visible and hidden states for the two cave signs. Each visible sign drew all nine models in the original order and balanced nine matrix pushes and three effect pairs. All 133 overlay paths round-trip and all eleven fork-layer tests pass. The [fork source index](2026-11-18-fork-review-index.tsv) reconciles five source or declaration paths and adds evidence for five other paths.

## Native ending walls, pictures and scene startup

The seven-file component at `3a5297fa66` carries the ending wall and picture controllers from `11d8ab092c` and `8dd092872c` into their current scene owners. Their native constructors keep the 0xF0-byte allocation and six textured quads. The scene startup constructs both children with the original parents. The wall controller uses the shared Ginja texture layout to bind four 14-entry texture lists at 0x8048E840. The existing camera startup already emits the two constants recovered in `2259468d9c` at their original locations.

The local review `901b8c33ff` adds the ending replay to the title and compass work at `fb95d7b4a9` for a 40-file review based on `af11a99125`. The component is also available at `e0889a9809`. All five builds reproduce the original executable and pass the project checker. All 35 functions in the four affected scene units still match and link. The cumulative source and working fork retain the historical fork's matched and linked addresses. The upstream-shaped builds inherit the existing 24-byte keyboard virtual table gap at 0x804D0004.

Linked execution checked both controllers at 30 and 25 ticks per second, covering four constructions, 104 transition cases, ten archive selections and 56 texture entries. The fork-only layer round-trips all 133 overlay paths and passes all eleven tests. Nine rows of the [fork source index](2026-11-18-fork-review-index.tsv) carry the corresponding evidence.

## Stage objects and weather

The rain replay `e931dd4156` carries the consolidated rain unit from `f38e6ec6c7` into the current ambient-object source. The 16-drop layout, streak points and colors, and native constructor are retained. The spawning task now names its countdown and constructs both its controller and drops through their native types. Its original 0x20-byte allocation and split-screen condition are preserved. The jungle warp already carries the typed animation motion and six source-linked constants from `8762a22f23` in its current owner.

The combined local review `caddbc33aa` extends the world-resource and scene-object review `7cb3ebf845` into a 37-file review on `af11a99125`. All four builds reproduce the original executable and pass the project checker. All eleven functions in the three rain units remain exact and source-linked. The cumulative branches retain the historical fork's matched and linked addresses. The upstream-shaped review inherits the 24-byte keyboard virtual table gap at 0x804D0004.

The linked weather tests cover eight constructor inputs, twelve floor and activity combinations and sixteen scheduling and allocation cases. The harness substitutes the console vector addition helper and retains the ordinary register saves around the rain initializer. The fork-only layer round-trips all 133 overlay paths and passes all eleven tests. Seven entries in the [fork source index](2026-11-18-fork-review-index.tsv) carry the source evidence.

## Creation effects, starlight and item-effect callers

The twelve-file replay at `9489a33655` carries native starlight construction and task updates from `2b6fc8bb52` and the typed factory and menu setter from `f0ab98c0b1`. Starlight parameters own their field copy. The effect creates children through their native constructor, retains the shared color renderer, and keeps the 0x4C-byte and 0x30-byte object layouts. The follower, attack collision and gun callers use the same factory. The attack collision keeps its existing constant initialization for the exact compiler output.

The combined local review `0701b795c1` extends creation effects and their color renderer `5430552ee1` to 53 files on `af11a99125`. All four builds reproduce the original executable and pass the project checker. The six affected source units retain all 88 original exact, source-linked functions. The cumulative branches retain the historical fork's matched and linked addresses. The upstream-shaped review inherits the existing 24-byte keyboard virtual table gap at 0x804D0004.

Linked checks covered fifteen child constructions, four factory allocation and split-screen cases, thirty-six task visibility and movement cases and sixteen flag updates. The tests substitute the projection, vector math and allocation helpers and retain the scalar register saves around the child constructor. The fork-only layer round-trips all 133 overlay paths and passes all eleven tests. Ten entries in the [fork source index](2026-11-18-fork-review-index.tsv) carry the source evidence.

## Window controller flags and menu creation

The 25-file replay `92f3bda8d4` carries the typed window-controller flag accessors from `9bd754054e` and the menu pointer stores from `cf65d957cd` into the current owners. The flags use the controller's 16-bit word at 0x1C and the child field at 0x3C. Shop lists and challenge item selection store the factory's TWindowMenu pointer directly. Character selection, the short list, room sequences and area warps all use the same factory declaration. Room and equipment-sell callers retain the original 16-bit client ID conversion.

The local review `a19c782cfa` is based directly on `af11a99125`. All four builds reproduce the original executable and pass the project checker. All 570 functions in the nineteen changed source units stay exact and source-linked. The cumulative branches retain the historical fork's matched and linked addresses. The upstream-shaped review inherits the existing 24-byte keyboard virtual table gap at 0x804D0004.

Linked execution covered 200 flag changes, 320 read-only queries, and 48 menu factory cases. The factory cases check the original allocation size, forwarded position, item count, client ID, and allocation-failure return through simulated allocation and construction. The fork-only layer round-trips all 133 overlay paths and passes all eleven tests. Twelve entries in the [fork source index](2026-11-18-fork-review-index.tsv) record the corresponding evidence.

## Dragon attacks and material fades

The eleven-file component `7d38c6c657` carries the Dragon and Gol Dragon fireball and breath changes from `0b0f090a42`, `4f68b08348`, `90e5ebb1cf`, and `ebeb4b1d6b`. Both fireball types use native constructors at their four original call sites. Their states, emitter pointers and particle tables stay at their original locations. Both breath effects use typed position and velocity fields and keep their original attack-history allocation and cleanup.

The combined local review `e00e1ec6c4` extends material opacity and Dragon fades `1c20f1a945` to 59 files on `af11a99125`. Its vector-normalization call uses the existing declaration on that base at 0x8007E9EC. Great Merge uses the typed declaration for the same original function. All four builds reproduce the retail executable and pass the project checker. The six changed source units retain all 362 original exact, source-linked functions. The cumulative branches retain the historical fork's matched and linked addresses. The upstream-shaped review inherits the existing 24-byte keyboard virtual table gap at 0x804D0004.

Linked execution covered eight constructions, twenty-four breath-height cases and twelve fireball lifecycles. The harness supplies vector, particle, sound and attack callbacks and verifies the original motion, particle selections, impact and destruction boundaries. The fork-only layer round-trips all 133 overlay paths and passes all eleven tests. Ten entries in the [fork source index](2026-11-18-fork-review-index.tsv) record the corresponding evidence.

## Photon Blast sequence, Estlla line and Leilla summon

The eight-file cumulative replay `f4edb367ce` carries the native Photon Line from `bf9fb51dfa`, its Estlla caller, and the typed Leilla setup and summon packet. The line keeps its original collision record and hit limit. Leilla uses its native object and a shared 0x24-byte parameter record in the existing in-place setup. A C++ constructor variant changed the compiler's register allocation, so the verified review keeps the in-place call at the original address. The fork's native shower behavior from `3b07dfd01b` was already present in the consolidated Olga Flow effects owner.

The 15-file local review `640bb6049b` combines this component with the typed sequence, result owner and attachment work already integrated at `6db60a1081`. The complete review reproduces the retail executable on `af11a99125` and retains all 79 exact, source-linked functions in the six affected units. All cumulative builds reproduce retail and retain the historical fork's matched and linked addresses. The upstream-based branch inherits the existing 24-byte keyboard virtual table gap at 0x804D0004.

Linked execution covered eight line constructions, sixteen path and hit-limit cases, and twenty Leilla setup cases with simulated allocation and engine callbacks. The fork-only overlay round-trips all 133 paths and passes all eleven tests. Ten entries in the [fork source index](2026-11-18-fork-review-index.tsv) carry the corresponding evidence.

## Quest item operations and player inventory

The three-file component `1e2fe01fbd` carries the typed inventory access and item data from `4430049671` and `ba1838d281`. Four quest opcodes use the native item record, slot and owner types. The player keeps its typed inventory pointer at 0xD00. Revival pickup and mag feeding keep the original item checks and now use typed item owners. The story quest traversal from `ce647f0670` was already present in full, apart from the current TLobby include path.

The combined local review `59f1eaacb9` extends the quest lists, filenames and downloads review `8c7134e424` to 44 files on `af11a99125`. Its inventory calls retain the existing upstream-base entry points. The cumulative build uses the corresponding typed inventory methods already integrated there. All four builds reproduce the retail executable and pass the project checker. All 929 functions in the two changed source units remain exact and source-linked. The cumulative builds retain the historical fork's matched and linked addresses. The upstream-shaped review inherits the existing 24-byte keyboard virtual table gap at 0x804D0004.

Linked checks covered 24 inventory searches, 40 deletion cases and eight revival-item pickup cases with simulated item and inventory providers. They cover missing owners, byte sign extension, the upper destination limit, and the original behavior when the source and destination registers overlap. The fork-only overlay round-trips all 133 paths and passes all eleven tests. Four entries in the [fork source index](2026-11-18-fork-review-index.tsv) carry the corresponding evidence.

## Enemy model archives and appearance

The five-file replay at `056498255a` carries the Gibbles resource contracts from the fork's native lifecycle, the Morfos archive and model traversal from `5d373037ea` and its follow-ups, and the byte buffer and typed model and texture records from `93c5d139d2` and `b92fac49d3`. Gibbles and Morfos and its arm now keep their archive pointers and read model, texture and motion entries directly. Both Gibbles descriptors retain one model, ten motions and their original filenames. The loader shares the model record with its callers.

The archived 73-file batch at `9f5506ed2c` provided the dependency map. The typed enemy archive factories and model-node capture already use the current owners. All 133 names in the fork's enemy filename batch `3ec6bd3db1` are present at the same addresses and sizes. The capture and Monest callback units retain 48 exact source-linked functions.

The local review at `86f0163316` extends enemy appearance, movement and targeting to 83 files on `af11a99125`. It uses the upstream archive entry points and preserves the unsigned texture-slot comparison in its loader. The cumulative version uses its existing native archive constructors and callbacks. All four builds reproduce the retail executable and pass the project checker. All 136 functions in the four changed source units remain exact and source-linked. The cumulative builds retain the historical fork's exact and linked function and data coverage. The standalone review shares the upstream 24-byte keyboard virtual table gap at 0x804D0004.

The fork-only layer round-trips all 133 overlay paths and all eleven layer tests pass. The [fork source index](2026-11-18-fork-review-index.tsv) records six source comparisons.

## Stage traps, debris and player state

The 31-file replay at `2a2a454320` carries the trap archive array from `92e4892cdc`, typed chip copy and model draw queue from `9ac34042fb`, and the player flag method and its callers from `9a4fe1fccc` and `68aa010f97`. The three Ancient02 records share one array of 0x18-byte entries. Ancient and Seabed traps, warps, and other callers read the flag on the player class. The battle result path keeps the original linkage form because the receiver is already in the incoming register. The chip copy keeps the original mutable pointer signature and reads its input. The Seabed template stays in read-only storage. The chip unit and its consumers share the two parameter layouts.

The local review at `2e2a94a0f5` adds this work to stage objects, weather, and resources for 66 files on upstream `af11a99125`. Every build reproduces retail and passes the project checker. All 1,554 functions in the 24 affected units remain exact and source-linked. The linked audit verifies all 72 bytes of the archive array, including each filename, model-list pointer and count. The 36 flag calls, three draw-queue calls and one chip-copy call retain their original targets. The cumulative builds preserve the historical fork's covered addresses. The upstream-shaped review shares the existing upstream 24-byte keyboard table gap at 0x804D0004.

The fork-only layer round-trips all 133 paths and passes all eleven tests. The [fork source index](2026-11-18-fork-review-index.tsv) records ten source comparisons.

## Standalone reviews on upstream master `af11a99125`

The seven remaining review families and the alternate combat build with the allocation dependency now have verified local heads. Each head contains one subsystem review commit based directly on the new upstream master. The previous grouped commits remain available under `great-merge/snapshots/6e09dda9c5/`. The fork tooling, documentation and workflows stay in the fork layer.

| Review | Head | Paths requiring conflict resolution |
| --- | --- | --- |
| memory | `88f754be9e` | 8 |
| spatial-effects | `a2c7411173` | 1 |
| combat | `6802a8b2ce` | 6 |
| window-frames | `4618815064` | 23 |
| bml-resource-lifetime | `343fbe8d17` | 15 |
| render-interfaces | `e8a06c9c0e` | 3 |
| actor-presentation | `dffec79c24` | 1 |
| combat-with-runtime-array-allocation | `87675984b6` | 14 |

All eight builds reproduce the original executable and pass the upstream project checker. Address-level comparisons preserve the exact and linked functions and data from each previous review and the new master. Comparison against the historical fork finds no losses beyond the current upstream baseline. The branches with extra files route calls through upstream's relocated status classes. Memory and combat keep the same allocation behavior in the new owners, and the resource and rendering reviews retain the typed consumers of upstream's native breakup classes.

The window branch uses its existing placement calls in upstream's consolidated balloon file. Its original 90 data ranges cover 980 source-linked bytes and 167 alignment bytes, including all 24 keyboard virtual table bytes. It can be reviewed separately from the existing chat placement follow-up.

## Previous review queue on upstream master `6e09dda9c5`

The eleven standalone reviews and the combined source stack have been replayed on `6e09dda9c5`. The upstream-shaped stack at `a409bd5c82` includes the chat balloon, typed bone rotation, native rope simulation, NPC resources, typed quest records, challenge retry objects, player technique casts, dragon attack ownership and the shared boss action packets and typed enemy archive loading, the BML model and motion callbacks, and the Photon Blast sequence and attachments, typed character initialization, typed technique effects, the named technique resource data, native needle contact dispatch, and the Canadin and Sinow interfaces, including native Canadin formation and action handling, Gi Gue attacks, Morfos behavior, shared encounter callbacks, Pan Arms coordination, and Gibbles and Gyaranzo combat ownership, Gibbles construction and teardown, the Ginja draw and material interfaces, the Bal Claw and Berura combat states, the shared enemy experience and item-drop methods, the typed inventory methods, record export and sorting, the player scale and size packet interfaces, the typed equipment and packet callers, and the typed movement hold, release and animation interfaces. The all-source snapshot is `0a610fd618`. The preceding heads are preserved under `great-merge/snapshots/3f35d99bb1/`.

| Review branch | Tip |
| --- | --- |
| `great-merge/current/network-contracts` | `5e90284b9a` |
| `great-merge/current/memory` | `e8c95dbad0` |
| `great-merge/current/resource-lifetimes` | `5b3de69908` |
| `great-merge/current/spatial-effects` | `e1e487e5d3` |
| `great-merge/current/combat` | `ffa3cf9604` |
| `great-merge/current/encounter-drawing` | `764b12bea2` |
| `great-merge/current/window-frames` | `cb1ebc1100` |
| `great-merge/current/bml-resource-lifetime` | `ae880a661a` |
| `great-merge/current/render-interfaces` | `60bd735c2e` |
| `great-merge/current/actor-presentation` | `ba1790084a` |
| `great-merge/current/world-object-resources` | `bbbb69ff1b` |

The window review reconciles 57 overlapping paths. It retains upstream's native menu and word-select construction and its item-help constant pool, along with the fork's typed callers and field layouts. Sixteen overlapping signatures retain the fork types and original linked addresses. The rebased window review supplies the original chat balloon, item-help and software-keyboard virtual tables. All 90 entries in the [data range ledger](2026-11-18-fork-data-ranges.tsv) now resolve to 980 source-linked bytes and 167 bytes of alignment padding.

The full stack and all-source snapshot retain all exact functions and linked data from both the prior review stack and the historical fork. The window review, full stack, all-source snapshot and working fork passed their project checks and reproduced the original GameCube executable, SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. The full stack has 2,456 exact source-linked units. The working fork passed the generated retention check after recalculating its local linker inventory. The layer check and eleven unit tests passed, and the materialized fork reproduces all 133 tooling paths.

The source audit reconciles the snapshot and main-menu headers. The target compiler confirms all six historical menu field offsets against their current names. The snapshot and item-help builds source-link all 46 original routines at the same addresses and sizes. Five source or interface records now have partial evidence in the [fork review index](2026-11-18-fork-review-index.tsv).

### World objects, NPCs and quests

Comparing complete source-linked functions by original address and size aligned 316 open world, NPC and quest source records with current owners. Forty of those records span multiple owners. This gives the source audit a starting point for naming, type and declaration changes.

The replay at `81fc986ad1` restores the fork's typed bone-rotation constructors, player factory and recursive angle math, along with the player action mask and both hair-effect call sites. The native code preserves the fork's object sizes and all four changed exports at their original addresses and sizes. The standalone world review at `bbe6cf744d`, the combined stack, all-source snapshot and working fork passed the full build, original executable hash and project checks. The overlay round-trips all 133 paths, and its eleven tests passed.

The rope replay at `3f001efd86` restores the native player and base constructors, typed collision and segment records, and the De Rol Le fin constructor and segment table. Six changed functions retain their original addresses and sizes. Nine linked data records include the two native virtual tables and the 72-byte fin segment table. One source-specific compiler setting reproduces the original function and table order. The standalone world review at `cc7b595095`, the combined stack, the all-source snapshot and the working fork all reproduce the original executable. The fork overlay retains its 133 paths and all eleven tests pass.

The [fork source index](2026-11-18-fork-review-index.tsv) accounts for ten rope and fin records.

The NPC resource replay at `a07ec1a39a` reconciles thirteen classes. Their current owners already source-link the twenty-six original loader and cleanup methods and have the typed BML descriptor paths. The replay gives thirty-nine existing strings explicit definitions, types the eight GVM model and texture pointers and preserves their original addresses. The standalone world review at `0fe5806ad0`, combined stack, all-source snapshot and working fork pass the original executable and linkage checks. One hundred thirty-three overlay paths round-trip and all eleven fork layer tests pass.

The first NPC replay accounts for twenty-four historical source and declaration records.

The follow-up at `6b6b24813d` carries the HFW01 and NFW01 model and texture pointers, their archive filenames and the NPC character-data filename. The four original resource methods, four pointer slots and seven strings retain their original addresses. The standalone world review at `a370ce1bd3`, combined stack, all-source snapshot and working fork reproduce the original executable and pass the project checker. The 133-path overlay round-trips and all eleven layer tests pass.

Twenty neighboring source files already carry their fork changes. The preceding follow-up closes twenty-four entries in the [fork source index](2026-11-18-fork-review-index.tsv).

The interface replay at `b1d4ca3d91` completes the three open NPC source differences. Both asynchronous callers use the shared typed filename. Moja uses the shared archive’s motion list, and Soutokufu and the two Gryphon switch callers use the original XZ tests. The dragon and Gryphon effect templates and copy sites share the original twenty-byte record. The standalone world review at `436bcf4fc1`, all-source snapshot and working fork all pass the original executable and linkage checks. The fork overlay round-trips 133 paths and passes eleven tests.

The NPC interface replay closes nine additional entries in the [fork source index](2026-11-18-fork-review-index.tsv).

### Quest data and arguments

The replay at `28385477f6` restores the fork’s typed quest VM arguments, complete match and item data, and story flag traversal. The string push and dictionary matcher retain their original addresses and sizes. The review verifies 189 historical quest download functions, twenty data and state symbols and the original executable. The standalone resource review at `5b3de69908`, combined stack, all-source snapshot and working fork passed the full project checks. The 133-path fork overlay round-trips and all eleven tests pass.

The [fork source index](2026-11-18-fork-review-index.tsv) closes six entries and adds evidence for eight more.

### Challenge retry objects

The replay at `e5c8760ae8` carries the original state, countdown, menu and message fields into both challenge retry classes and their current owners. It preserves all 62 function names, addresses and sizes in those owners on the combined stack. The standalone world review at `bbbb69ff1b`, combined stack, all-source snapshot and working fork pass the project checker and reproduce the original executable. The fork overlay round-trips 133 paths and passes all eleven layer tests.

The [fork source index](2026-11-18-fork-review-index.tsv) closes the two header entries and records the field replay against both source owners.

### Player technique casts

The 25-file replay at `bdc5b56af7` restores the original 6x47 packet, player cast state, NPC sender and target handling from `ca6e72d5e7` and its companion predicate change `d6b6ecb087`. Mapped three-way replay handled 16 paths automatically and identified 44 overlaps across eight paths. The remaining historical source unit now lives in the combined technique controller. The 364-byte handler and 15 renamed functions retain their original instructions, addresses and source linkage.

The standalone combat review at `c780ad28de`, combined stack, all-source snapshot and working fork reproduce the original executable and pass the project checker. The fork-only linker inventory replaces two stale retained names with their recovered exports. The fork overlay round-trips 133 paths and passes all eleven layer tests.

The [fork source index](2026-11-18-fork-review-index.tsv) records the coverage at 25 paths.

### Dragon attack and camera ownership

The 20-file replay at `320749ae74` types the Gol Dragon leader, attack-slot and spawn calls, the Dragon burrow trail, the live camera target and the render position. The source replay follows functions at their original addresses through upstream's combined owners. All ten renamed functions retain their original addresses and sizes. Twelve linked units contain 435 exact functions. The two class vtables match at `0x804E4BF0` and `0x804F1A78`.

The standalone encounter review at `21f28742f9`, combined stack, all-source snapshot and working fork pass the project checker and reproduce the original executable. The fork-only linker inventory updates four retained names. The 133-path overlay round-trips and all eleven layer tests pass.

The [fork source index](2026-11-18-fork-review-index.tsv) records 24 source and declaration entries.

### Shared Dragon, Gol Dragon and Barba Ray action packets

The 10-file replay at `8a0619369b` recovers the common 8-, 12-, 20- and 24-byte action layouts from `40da694279`. The original send and byte-swap functions operate on packet storage. Their call sites use the shared layouts for Dragon, Gol Dragon and Barba Ray. All twelve renamed functions remain exact and source-linked at their original addresses and sizes.

The standalone encounter review at `c7db801ce9`, combined stack, all-source snapshot and working fork reproduce the original executable and pass the project checker. The fork-only inventory updates seven retained exports. The 133-path overlay round-trips and all eleven layer tests pass.

The [fork source index](2026-11-18-fork-review-index.tsv) records 11 source and declaration entries.

### Gal Gryphon action packet

The seven-file replay at `9f1e618729` restores the original 0xA0 packet and action state from `cdfb1d660b`. The typed sender, receive handler, action copy and byte swaps live in the current Gal Gryphon unit. The run-time action readers use the same parameter record. All eight renamed functions retain their original exact instructions, addresses and sizes. The two affected source units contain 180 exact functions.

The standalone encounter review at `764b12bea2`, combined stack, all-source snapshot and working fork pass the project checker, including the original executable hash. The fork linker inventory updates seven retained exports. The 133-path fork overlay round-trips and all eleven layer tests pass.

The [fork source index](2026-11-18-fork-review-index.tsv) records 7 source and declaration entries.

### Enemy archive loaders and Gal Gryphon resources

The 41-file replay at `3e3744f3fa` restores the shared enemy archive declaration and the original typed descriptor copy. It covers the default and alternate-filename loaders and their boss, enemy and object callers. Gal Gryphon's loader, cleanup, model rendering and three effects share the typed archive and texture handles. The battle and movement callers use their original parameter types. The replay verifies 17 Gryphon data and pointer records and 1,999 exact functions across the 35 affected source units.

The standalone review at `ece92dc455` uses the combat group's existing battle parameter declarations. The combined stack, all-source snapshot, standalone review and working fork reproduce the original executable and pass the project checker. The fork tooling overlay round-trips 133 paths and passes all eleven layer tests.

The [fork source index](2026-11-18-fork-review-index.tsv) records 38 source and declaration entries.

### Bulk replay and BML resource lifetime

A mapped three-way replay from fork main `3342e42983` onto the source stack at `3e3744f3fa` found 844 paths with one current owner. It prepares 94 complete file edits and can extract nonoverlapping changes in another 657 files. The other 93 mapped files only yielded overlapping changes. These are replay candidates. Each subsystem still needs declaration and symbol reconciliation, a full build and coverage comparisons.

The original executable contains 506 branches to the BML resource constructor and destructor in 441 functions. Comparing the old and current source owners at the original function addresses verified 483 allocations and releases as typed C++ calls. The other 23 have exact binary evidence. All original call sites in 222 indexed source files have source and binary evidence. This gives 194 open entries specific evidence about allocation and cleanup. Each entry records the current owner and original function addresses.

The replay at `0ed3cc93c7` carries the original model and motion callback signatures into the current archive owner. The texture completion callback and the resource completion check use the native request and resource fields. The callbacks match at 0x8001F998 and 0x8001FA1C under their typed signatures. The standalone BML review at `ae880a661a`, combined stack, all-source snapshot and working fork reproduce the original executable and pass the project checker. The 133-path overlay round-trips and passes all eleven layer tests.

### Photon Blast sequence and attachments

The nine-file replay at `1c90d6df9b` restores the fork's native Photon Blast sequence receiver, typed admission slots and original action-hold call. Both result paths use the sequence to calculate damage. The summon uses the original camera vectors and a shared attachment record from joint traversal through particle creation, updates and release. Golla reads the joint position through the same record.

The original calculation, hold and constructor link at 0x801A826C, 0x801A86E0 and 0x801A9E10. All 55 functions in the three affected source units remain exact at their original addresses and sizes. The standalone combat review at `5ef27baa2d`, combined and all-source stacks and working fork reproduce the original executable and pass the project checker. The fork overlay round-trips 133 paths and passes all eleven layer tests.

The [fork source index](2026-11-18-fork-review-index.tsv) records 11 source and declaration entries.

### Character initialization, starting inventory and level growth

The 22-file replay at `2cb50b645a` types the shared level rows and the saved character stat block. Character creation, selection reset, NPC setup and the two challenge rebuild paths use the common inventory and stat interfaces. Level advancement and battle-level resets read the original stat increments and experience fields. The class index retains the original full-register argument at the shared calls, and the table consumers apply the original signed byte conversion.

All 954 functions in the fifteen affected source files remain exact at the original addresses and sizes. The twelve starting inventories and their pointer table account for 1,728 exact source-linked bytes. The standalone combat review at `6e52270263`, combined and all-source stacks and working fork reproduce the original executable and pass the project checker. The 133-path fork overlay round-trips and passes all eleven layer tests.

The [fork source index](2026-11-18-fork-review-index.tsv) records 20 source and declaration entries.

### Technique factories, lightning effects and band sound

The 22-file replay at `fec32dd03b` restores both static Gi-Barta factories and places bolt construction on the native lightning effect class. The original executable has nine direct calls to the ice factories and 36 to the bolt constructor. All 45 calls use the corrected types in the current source owners, including the player dispatcher, bosses, enemies, a trap and a weapon. Barta, Gi-Barta and Megid share the band sound schedule and its original pitch changes.

All 435 functions in the sixteen affected source units remain exact and source-linked. The audit also traces 1,572 existing bytes of technique resource and tuning data into the current controller. The standalone combat review at `f7fb6e725e`, combined and all-source stacks and working fork reproduce the original executable and pass the project checker. The 133-path fork overlay round-trips and passes its eleven tests.

The [fork source index](2026-11-18-fork-review-index.tsv) records 22 source and declaration entries.

### Named technique archive and charge-light data

The replay at `34970abfe3` defines the original nineteen technique archive and class strings and eighteen charge-light color and direction records in the current controller. All 37 compiled definitions match their original addresses, sizes and contents across 612 bytes. The model and motion tables use the named strings, and the controller’s nine charge-light cases copy the paired records. The 0x6B0-byte charge-light routine and all 21 controller functions remain exact.

The standalone combat review at `9b263c85e3`, combined and all-source stacks and working fork reproduce the original executable and pass the project checker. The fork overlay round-trips 133 paths and passes all eleven tests. GitHub’s branch comparison confirms that the local upstream base `6e09dda9c5` and fork snapshot `3342e42983` match their remote branches.

The [fork source index](2026-11-18-fork-review-index.tsv) closes the historical resource unit.

### Needle projectile contacts and collision geometry

The seven-file replay at `568010cb36` recovers all six native needle contact methods, covering 2,008 original instruction bytes. The Gee needle and Gi Gue missile use the shared dispatcher at both original call sites. The contact queries use the projectile’s native positions and the original actor flags. All 30 functions in the three affected source units remain exact and linked.

The current box, sphere and line projection units match the fork’s collision routines after translating its local types and names. The box face tables, bounds checks, edge tests, square-root refinement and line projection body all agree. The current source keeps the upstream implementations.

The standalone combat review at `151b8668c5`, combined and all-source stacks and working fork reproduce the original executable and pass the project checker. The working fork updates the retained dispatch name. The 133-path tooling overlay round-trips and passes all eleven tests.

The [fork source index](2026-11-18-fork-review-index.tsv) records 8 entries. It has 1,296 entries awaiting owner comparison and 770 with partial evidence.

### Canadin formation and Sinow motion interfaces

The nine-file replay at `7a8afe9254` restores the native Canadin formation slots, hover methods and color argument. Shinowa uses the fork's state and effect names with the current typed effect pointers. Sinow Zoa uses a native movement collision method and the shared Ninja model types for all three material lookups.

All eight recovered method symbols retain their original addresses and 1,044 instruction bytes. The three affected source units retain all 263 exact linked functions. The form of the Sinow Zoa collision call preserves the original signed comparison.

The standalone combat review at `0184305183`, combined stack, all-source snapshot and working fork reproduce the original executable and pass the project checker. The fork tooling overlay round-trips all 133 paths and passes eleven tests.

The [fork source index](2026-11-18-fork-review-index.tsv) records evidence against 8 fork records. It has 1,293 entries awaiting owner comparison and 773 with partial evidence.

### Canadin formation, actions and discharge

The six-file replay at `36e551a432` restores the fork's native Canadin formation, movement, fade and action interfaces. The typed follower factory takes the original leader, spawn vector and two indices. Both Canadin classes share the native fade and movement methods. Eight action handlers dispatch through the Canadin class, and the discharge effect invokes its original receiver.

All 34 method symbols match the fork names, addresses and sizes across 8,284 original instruction bytes. The two affected units retain all 115 exact linked functions. The leader header and the original float ceiling helper are accounted for in the fork source index.

The standalone combat review at `1aeceb4919`, combined stack, all-source snapshot and working fork reproduce the original executable and pass the project checker. The fork tooling overlay round-trips all 133 paths and passes eleven tests.

The [fork source index](2026-11-18-fork-review-index.tsv) records evidence against 5 fork records. It has 1,292 entries awaiting owner comparison and 773 with partial evidence.

### Native enemy actions and encounter callbacks

The 17-file replay at `1b721d5692` restores Gi Gue target collection, search, landing, needle, missile and technique behavior as native methods. Morfos uses native state dispatch targets, an original virtual status test, and typed heading and arm position accessors. The arm reads both from its parent when created and on each update. Sinow Zoa uses the original native action handlers and its real-enemy factory. The three Shinowa Mirage resource callbacks and one Morfos resource callback now use the class declarations.

All 28 method symbols match the fork by name, original address and size across 11,696 instruction bytes. The seven affected source units preserve all 284 exact linked functions and all of their data sections. The five factory and resource callback pointers are unchanged at their original table addresses.

The standalone combat review at `98c3031b75`, combined stack, all-source snapshot and working fork reproduce the original executable and pass the project checker. The fork tooling overlay round-trips all 133 paths and passes eleven tests.

The [fork source index](2026-11-18-fork-review-index.tsv) records evidence against 13 fork records, including the complete Morfos Arm and Sinow Zoa Real declarations. It has 1,287 entries awaiting owner comparison and 776 with partial evidence.

### Pan Arms body and half coordination

The nine-file replay at `e5105e2cae` restores the Pan Arms body and both halves as typed links. The halves use their native state predicates, target acquisition, split transitions and position methods. The body uses the original ground probes, combine path and warp. The GameCube instructions for the warp and the byte-sized half-health result remain exact.

All 27 method symbols match the fork by name, original address and size across 3,280 instruction bytes. All 132 exact linked functions and every data section in the four affected units remain intact.

The standalone combat review at `4443638522`, combined stack, all-source snapshot and working fork reproduce the original executable and pass the project checker. The fork tooling overlay round-trips all 133 paths and passes eleven tests.

The [fork source index](2026-11-18-fork-review-index.tsv) records evidence against 7 fork records. It accounts for both small state units and the remaining C declaration. It has 1,282 entries awaiting owner comparison and 778 with partial evidence.

### Gibbles and Gyaranzo combat methods

The six-file replay at `a7c3cdfdc1` restores Gibbles' native joint tracking, both joint attacks, landing damage, ground contact effects, and action methods. Gyaranzo owns its original action dispatch, chase and return, knockback, missile aiming and volley, fade, visibility and death breakup. The restored Gyaranzo class matches the fork declaration set, field order, and virtual order.

All 24 method symbols match the fork by name, original address and size across 8,764 instruction bytes. The two affected source units retain all 83 exact linked functions and each data section.

The standalone combat review at `03ca305e1d`, combined stack, all-source snapshot and working fork reproduce the original executable and pass the project checker. The fork tooling overlay round-trips all 133 paths and passes eleven tests.

The [fork source index](2026-11-18-fork-review-index.tsv) records evidence against 5 fork records. It has 1,281 entries awaiting owner comparison and 778 with partial evidence.

### Gibbles construction, teardown and targeting

The replay at `ec8de0a5ed` uses the fork's native Gibbles factory, constructor, destructor and targeting override. The constructor creates the two original collision objects and initializes the opacity and camera fades. The destructor frees both collision objects and the compiler handles the fade member teardown. The factory still creates the original controller before its enemy.

The three compiled method symbols retain 1,808 original instruction bytes. The movement parameters, three collision templates and compiler-generated 83-entry virtual table retain 492 bytes at their original addresses. The table keeps the destructor and targeting override in their original slots. Deferred generation places the table before the two switch tables and keeps all 54 exact linked functions in address order.

The standalone combat review at `03cda7414b`, combined stack, all-source snapshot and working fork reproduce the original executable and pass the project checker. The fork tooling overlay round-trips all 133 paths and passes eleven tests.

The [fork source index](2026-11-18-fork-review-index.tsv) records the recovered lifecycle against the two original fork records. It has 1,281 entries awaiting owner comparison and 778 with partial evidence.

### Ginja draw, material and texture interfaces

The 74-file replay at `7620a6ee98` restores the fork's model pointer through the shared renderer, draw callbacks and direct callers. Material drawing accepts a const draw record with typed parameters. Model drawing shares the original zero-argument preparation call, and texture slot selection and release use the public texture declarations.

The four exports retain their original addresses and sizes. The retail executable has 206 direct model draw branches, six preparation branches, two material decoder branches and fourteen texture slot branches. Item model traversal also uses the pointer-typed indirect callback. All 1,305 functions in the 68 affected gameplay source units match exactly on the combined stack.

The standalone renderer review at `60bd735c2e`, combined stack, all-source snapshot and working fork reproduce the original executable and pass the project checker. The three 24-byte virtual tables for the chat balloon, item help and software keyboard are verified on the combined stack and working fork. The standalone renderer base carries those tables through the original link inputs. The 133-path tooling overlay round-trips and all eleven overlay tests pass.

The [fork source index](2026-11-18-fork-review-index.tsv) records evidence for 60 entries. It has 1,267 entries awaiting owner comparison and 790 with partial evidence.

### Bal Claw body and Berura combat states

The eight-file replay at `5c49304572` gives Bal Claw its native form selection, state reset, targeting movement and death sequence. The body constructor reads the typed 0x40-byte placement record. Berura owns its original patrol, action, turn-limit and punch state methods, and the factory tables use its native placement entry point.

All 30 method symbols match the fork by name, address and size across 12,120 instruction bytes. The three gameplay source units retain 96 exact functions. The factory unit keeps the three original 0xA5 pointers. The detached punch retains its original branch to each of the two Berura owner methods.

The standalone combat review at `9c9de5d77c`, combined stack, all-source snapshot and working fork reproduce the original executable and pass the project checker. The combined stack and working fork source-link the chat balloon, item help and software-keyboard virtual tables. The standalone combat branch uses the original link inputs for those three 24-byte tables. The 133-path tooling overlay round-trips and all eleven overlay tests pass.

The [fork source index](2026-11-18-fork-review-index.tsv) records evidence against 12 fork records. It has 1,261 entries awaiting owner comparison and 796 with partial evidence.

### Shared enemy experience and item drops

The 29-file replay at `556783a12a` restores the shared `TObjEnemy` methods for awarding experience and requesting standard item drops. All 24 retail branches to the experience-and-drop method and both branches to the request method keep their original targets. The request method retains the original branch to the 6x60 drop request. Source callers now pass the native enemy receiver, including five callers that previously omitted it in source.

The affected 26 gameplay units retain all 1,367 exact functions. Both new exports match fork names at the original addresses and sizes. The standalone combat review at `10ea2b04c3`, combined stack, all-source snapshot and working fork reproduce the retail executable and pass the project checker. The standalone combat branch uses the existing original link inputs for the three window virtual tables. The fork overlay round-trips all 133 paths and passes eleven tests.

The [fork source index](2026-11-18-fork-review-index.tsv) carries call-site evidence against 28 fork records. It has 1,256 entries awaiting owner comparison and 801 with partial evidence.

### Player inventory and item-list ownership

The 22-file replay at `4e41d94861` carries the inventory walk, item lookup, update, quantity and equipped-item operations onto `TPlyItem` and `TItemList`. Shop, quest, player item and death-drop calls use the typed receivers and pass the node explicitly. The replay preserves the current native placement classes and their list layout. At this revision, the item-owner accessor used the existing 32-bit return representation.

The 29 exports match the fork by name, original address and size for 3,184 instruction bytes. The 15 affected gameplay units retain all 1,153 functions and 145 original direct calls to the recovered methods. The standalone combat review at `ffa3cf9604`, combined stack, all-source snapshot and working fork reproduce the retail executable and pass the project checker. The standalone combat branch uses the original link inputs for the three window virtual tables that are source-linked on the combined stack. All 133 fork overlay paths round-trip and the eleven layer tests pass.

The [fork source index](2026-11-18-fork-review-index.tsv) carries evidence against 25 fork records. It has 1,238 entries awaiting owner comparison and 819 with partial evidence.

### Typed inventory record export and sorting

The 13-file replay at `4c56068484` restores the native inventory sort list and the constructor, destructor and copy assignment for its records. The item-list owner is a `TItem *`, and the list lookup, NPC export, trade removal and quest callers pass the original types. The normal and death-drop exports use typed record pointers, and copy and removal use the shared 0x1C-byte inventory entry.

The nine exports match the fork by name, address and size across 888 instruction bytes. The replay preserves 34 original direct calls to those exports and all 1,111 functions in the 7 affected source units. The combined stack, all-source snapshot and working fork reproduce the retail executable and pass the project checker. The dependent combat review at `c556067784` also passes with the array-allocation runtime on its base. All 133 overlay paths round-trip and all eleven fork layer tests pass.

The [fork source index](2026-11-18-fork-review-index.tsv) records evidence against 11 fork records. It has 1,233 entries awaiting owner comparison and 824 with partial evidence.

### Player scale, camera offsets and size packets

The 13-file replay at `9ede604f8a` gives the player scale state and camera vectors their six original methods and moves ten state and packet routines onto typed receivers. The 0x30-byte scale state, camera offset at 0x18, and 8-byte shrink and 4-byte restore packets are checked at compile time. The scale flag uses 32-bit storage to preserve the existing explicit construction order. Compiling the existing constructors with a constructed FlagWord member changed both function bodies. Three player routines use scoped compiler settings to retain the original repeated scale-state address calculations.

All 16 exports occupy the original addresses and sizes. The 6 affected source units retain all 1,191 exact functions, including 27 original direct calls to these exports. The dependent combat branch at `91bebad92c`, the combined stack, the all-source snapshot and working fork reproduce the retail executable and pass the project checker. All 133 overlay paths round-trip, and the eleven fork layer tests pass.

The [fork source index](2026-11-18-fork-review-index.tsv) records evidence against 7 fork records. It has 1,229 entries awaiting owner comparison and 828 with partial evidence.

### Player equipment and equip packets

The 16-file replay at `79eea9a7e4` restores the fork's player equipment eligibility and unequip methods and its saved battle equipment constructor. Equip and unequip use typed item pointers and the original item virtual methods. Shop, shortcut, inventory, enemy and MAG callers pass the player and item ID explicitly. The outgoing equip and unequip structures retain their 12-byte and 8-byte wire formats. The unit attachment calls retain the original signed-byte conversion and integer temporary so the compiler emits the original virtual dispatch sequence.

All five renamed exports retain their addresses and sizes across 840 instruction bytes. The 13 affected source units retain all 917 exact functions, including 26 original direct calls and the saved equipment array constructor reference. The dependent combat branch at `37b78ac803`, the combined stack, the all-source snapshot and working fork reproduce the retail executable and pass the project checker. All 133 overlay paths round-trip, and the eleven fork layer tests pass.

The [fork source index](2026-11-18-fork-review-index.tsv) records evidence against 15 fork records. It has 1,227 entries awaiting owner comparison and 830 with partial evidence.

### Player movement holds, effects and animation dispatch

The 34-file replay at `a409bd5c82` brings the fork's movement-hold, release and effect interfaces onto the current source owners. Trap, enemy, NPC, quest, battle and Photon Blast callers pass the affected player explicitly. The 0x2C hold packet takes full-width duration and mode arguments and stores their low halfwords. It uses the fork's mutable position-pointer signature, which retains the original PowerPC load and store order. The equipment animation query returns the original signed result, and menu and inventory gates use native action-state queries.

Three renamed exports and seven other recovered or verified interfaces retain their original addresses and sizes across 792 instruction bytes. The 31 affected source units retain all 1,769 exact functions. The audit checks 99 original direct calls to these interfaces in those units. The dependent combat branch at `262f46f1a1`, the combined stack, the all-source snapshot and working fork reproduce the retail executable and pass the project checker. All 133 overlay paths round-trip, and the eleven fork layer tests pass.

The [fork source index](2026-11-18-fork-review-index.tsv) records evidence against 37 fork records. It has 1,216 entries awaiting owner comparison and 841 with partial evidence.

## Incoming upstream master `af11a99125`

A clean build of `af11a99125` reproduced the original executable and passed the project checker. Four review groups replay cleanly onto it. Their builds reproduce retail and retain the new upstream source coverage. Comparisons with the original fork build found no additional source or linked coverage losses.

| Review group | Local branch | Head | Replayed commits |
| --- | --- | --- | --- |
| network-contracts | `great-merge/incoming/af11a99125/network-contracts` | `ebe7edd892` | 3 |
| resource-lifetimes | `great-merge/incoming/af11a99125/resource-lifetimes` | `a53303e898` | 9 |
| encounter-drawing | `great-merge/incoming/af11a99125/encounter-drawing` | `94363b6618` | 10 |
| world-object-resources | `great-merge/incoming/af11a99125/world-object-resources` | `6dd9ff3049` | 11 |

Across the original 90 fork data ranges, the new master links 956 bytes and retains 167 bytes of alignment padding. The remaining 24 bytes are the software keyboard virtual table at 0x804D0004. The existing verified window replay emits that table. The new master now emits the other two window tables, recovering 48 bytes from the preceding master. The [data range ledger](2026-11-18-fork-data-ranges.tsv) records every range.

The combined and all-source branches initially stayed on `6e09dda9c5` while their replay was reconciled. A three-way comparison found 42 conflicts, including 23 window and menu paths, 14 encounter and effect paths, and 3 build metadata files. Several conflicts follow upstream's native class and virtual table changes. The replay needs those definitions and the fork's typed consumers together.

## Replay on upstream master `6e09dda9c5`

Upstream advanced 65 commits from `3f35d99bb1`. A fresh build of `6e09dda9c5` reproduces the original GameCube executable, SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Four local candidates have passed that same executable check and the full project checker against the new master.

| Local candidate | Tip |
| --- | --- |
| Network contracts | `great-merge/incoming/6e09dda9c5/network-contracts` at `5e90284b9a` |
| Actor presentation | `great-merge/incoming/6e09dda9c5/actor-presentation` at `ba1790084a` |
| World-object resources | `great-merge/incoming/6e09dda9c5/world-object-resources` at `31557ce897` |
| Chat balloon overlap | `great-merge/incoming/6e09dda9c5/balloon-overlap` at `14bf7316fd` |

The three review groups preserve all 15 original commits. The chat balloon candidate restores the typed rectangle test and the three placement queries at their original addresses, covering 524 instruction bytes. Placement now uses the viewport root's first child and returns the overlapping balloon through the actual member interface. The combined stack at `467564e30b` remains the latest fully verified combined build. Its replay has 63 paths requiring reconciliation, including upstream's window constructor changes.

The [data range ledger](2026-11-18-fork-data-ranges.tsv) verifies 908 source-linked bytes and 167 padding bytes on the new upstream base. The three remaining ranges each account for a 24-byte compiler-generated virtual table.

### Seven more review groups and the combined replay through encounters

| Local review branch | Tip |
| --- | --- |
| Array allocation, memory copies and release | `great-merge/incoming/6e09dda9c5/memory` at `e8c95dbad0` |
| Archive, streaming and quest-cache lifetimes | `great-merge/incoming/6e09dda9c5/resource-lifetimes` at `9a269ca0e4` |
| Positional sound and particle effects | `great-merge/incoming/6e09dda9c5/spatial-effects` at `e1e487e5d3` |
| Combat and player techniques | `great-merge/incoming/6e09dda9c5/combat` at `91438961d3` |
| Encounter and boss-effect rendering | `great-merge/incoming/6e09dda9c5/encounter-drawing` at `629568f631` |
| Texture and BML resource lifetimes | `great-merge/incoming/6e09dda9c5/bml-resource-lifetime` at `daa3a3af77` |
| Renderer and model interfaces | `great-merge/incoming/6e09dda9c5/render-interfaces` at `6c43c3a146` |

All seven branches were replayed on `6e09dda9c5`, retaining their 39 original commits. The resolved allocation calls use paired array allocation and release in upstream's reordered fog, keyboard, area-map and word-select sources. The charge emitter retains the shared particle and sound declarations in upstream's consolidated unit. Dead Spot retains the typed ground and texture calls in their respective review branches. The encounter and combat groups use upstream's new owners for the overlapping float and string data.

Each review branch passed the full project checker against the new upstream baseline and reproduced the original executable. The resource, effects, combat and encounter branches also preserve all exact functions and linked data ranges from their preceding review branches.

The cumulative replay through the first six groups is `great-merge/incoming/6e09dda9c5/combined-through-encounters` at `dd85301db0`. It resolves all ten conflicts from that portion of the old stack, passes the full checker, and reproduces the original executable. Ten of the eleven standalone review groups now have validated heads on the new base. The window review awaits reconciliation with upstream's constructor changes before the remaining groups can join the cumulative replay.

## Previous review queue on upstream master `3f35d99bb1`

The eleven local review groups were replayed on `3f35d99bb1`. The current cumulative stack at `467564e30b` changes 1,471 paths counting both sides of renames. The all-source snapshot is `5e1dc83969`. The previous upstream snapshots remain under `great-merge/snapshots/c572111ed6/`.

| Review branch | Standalone tip | Cumulative commit |
| --- | --- | --- |
| `great-merge/current/network-contracts` | `f68c619ed6` | `756d4a874b` |
| `great-merge/current/memory` | `f69270a9e6` | `96b4cca0db` |
| `great-merge/current/resource-lifetimes` | `b4b46375d2` | `16772fda0f` |
| `great-merge/current/spatial-effects` | `f781f52b51` | `1b33f02f81` |
| `great-merge/current/combat` | `a42b08d6eb` | `de49f74be1` |
| `great-merge/current/encounter-drawing` | `8f5eb4303f` | `9445c1e728` |
| `great-merge/current/window-frames` | `c50d4c1908` | `942a0c050f` |
| `great-merge/current/bml-resource-lifetime` | `3ed5b08f94` | `beded0d4d9` |
| `great-merge/current/render-interfaces` | `5a4673df7e` | `5af38c6b3d` |
| `great-merge/current/actor-presentation` | `5a2a778de3` | `fa2a1e5837` |
| `great-merge/current/world-object-resources` | `90d72bb2bd` | `5996f01f11` |
| Challenge enemy-set records | Included in its review branch | `4fa38ff78e` |
| Audio file-system callbacks | Included in its review branch | `50bc7543d7` |
| Barba Ray and Olga Flow encounter records | Included in its review branch | `3b34b9def9` |
| Enemy action, targeting and resource names | Included in its combat review | `0cce15ee15` |
| Stream entries, AFS tag and CVFS diagnostics | Included in its resource review | `132daf866a` |
| Dark Falz scene parts and Gol Dragon model override | Included in its encounter review | `bfbb029994` |
| Shortcut preview and symbol-chat construction | Included in its window review | `76d4f68f70` |
| Typed word-select formatters and callers | Included in its window review | `5439d728d5` |
| Time-setting scene and shared display constants | Included in its window review | `1c761f22be` |
| Boss effect constants and model handles | Included in the encounter review | `44bfc6c84b` |
| Actor animation binding, rest-angle capture and weapon preview | Included in its actor presentation review | `7b44dc747f` |
| Equipment effect collision template | Included in its spatial effects review | `d927dd90c2` |
| Sinow Zoa melee dispatch | Included in its combat review | `b82940c3d7` |
| Technique texture archive and list names | Included in its resource lifetimes review | `315bce551c` |
| Enemy projectile, nest, claw and color sequences | Included in its combat review | `63e8a18e15` |
| Rain and fish lifetime and resource records | Included in the world-object review | `28582fc056` |
| Native Com Card follower | Included in the window review | `011823a1c6` |
| Native word selection lifetime and scrolling | Included in the window review | `f6648c7664` |
| Native word-select menu, scrollbar and string window | Included in the window review | `a39c9a4d2b` |
| Native status gauge constructors and drawing | Included in the window review | `531ec09862` |
| Shared bag-warning window lifecycle | Included in the window review | `73745157f7` |
| Typed player-window commands and queries | Included in the window review | `b55c8aabcf` |
| Native window callbacks and borrowed draw arguments | Included in the window review | `6d9c527699` |
| Keyboard queries, composer modes and chat availability | Included in the window review | `fcaf0573ae` |
| Native chat and keyboard child ownership | Included in the window review | `96d3b95da5` |
| Shared window layout and vertex records | Included in the window review | `0dd3f7aebc` |
| Native message constructors and shared scrollbar storage | Included in the window review | `65b75fdd24` |
| Native numeric readout windows | Included in the window review | `df5b75721a` |
| Native status, timer and guild-card displays | Included in the window review | `39b136da5f` |
| Native menu and guild-card list lifetimes | Included in the window review | `9808118b7b` |
| Native lobby, area map and quest-board windows | Included in the window review | `f5fda12041` |
| Native action palette and customization windows | Included in the window review | `70717f69b9` |
| Native symbol-chat editor windows | Included in the window review | `11129323ca` |
| Native shortcut preview and list | Included in the window review | `fd001b831c` |
| Native item preview and lock-on windows | Included in the window review | `22f7ebeb5b` |
| Native choice and sound option windows | Included in the window review | `467564e30b` |

The updated master splits out six data blocks that the prior fork stack recovered inside code files. The replay uses upstream's six data units and moves 48 typed definitions into them. The first eight bytes of the player's later small-data pool still belong to its code unit. Each moved block matches the upstream source object and the extracted bytes at its original range, allowing the original four bytes of trailing alignment padding in three blocks. The preceding code owners have identical instructions and relocations. The render group also carries eight Canadin and Morfos table names into the new upstream data units with declarations that match their callers. Every renamed table has one provider and no reference to a placeholder name.

The cumulative validation compiled 2,450 selected source objects. Of the 2,415 objects present in the preceding stack, 2,403 are identical in allocated sections, symbol locations and relocations after same-address aliases are normalized. Twelve differ only in the data sections moved or adopted from upstream. The configured link set has 2,484 inputs and no new unresolved strong reference. The combat, encounter and window reviews compiled 47 affected objects each, and the renderer review compiled 48. The stock checker passed in object-report mode against a fresh upstream object report, with 27,572 exact functions, all 2,450 linked units exact and no loss of non-padding coverage. That replay was checked at the object level. The current stack also passed the executable hash check recorded below.

The fork-only branch `great-merge/current/layered-fork` at `a3aab5454f` leaves the cumulative source tree identical outside the fork layer. Its materialized checkout reproduces all 133 overlay paths from `500467cd41`. The layer check and eleven unit tests passed on the rebased head. The [original range ledger](2026-11-18-fork-data-ranges.tsv) still accounts for all 1,147 bytes. Upstream now supplies 872 exact source-linked bytes, the combined stack supplies the remaining 108, and 167 bytes are verified alignment padding.

### Enemy action, targeting and resource names

The combat review at `e566cc2ccd` and cumulative stack at `0cce15ee15` carry 30 fork method names across nine enemy source owners. The changes cover Gee swarm phases, target commitment and activation, Gi Gue barrier and action state, Gyaranzo armor and debris, and the other enemy targeting and resource accessors. Gee uses the fork's unsigned flag field, activation delay, and four named fighter and appearance masks. The source index records the names and addresses against 15 original fork paths. It has 1,747 entries awaiting owner comparison and 510 with partial evidence.

All 2,451 combat and 2,450 cumulative compiled source objects preserve the preceding allocated sections, symbol locations and relocations after the 30 aliases are mapped by original address and size. The working fork compiles the same 2,450 source objects. Every renamed method has one definition per build, matches its extracted instruction bytes, and has no stale reference. The upstream checker passed in object-report mode for both the combat review and cumulative stack. The executable hash remains unverified on this base.

The address comparison against fork main found zero lost matched or linked functions and zero lost non-padding data ranges. The stock report flags a net decrease of 2,358 bytes of aggregate data coverage. Its address rows account for 2,521 bytes of removed alignment padding and 163 bytes of added coverage. The previous range ledger remains valid because every allocated section and relocation is preserved.

### Streaming diagnostics and encounter models

The resource-lifetimes review at `665123cc84` carries 21 names from the fork. The stream table names its four entries, the two creation diagnostics keep their call sites, and the AFS tag and fourteen live CVFS diagnostics keep the same addresses. The encounter review at `1001dd7640` carries two Dark Falz draw methods, seven scoped strip and frame constants, and the Gol Dragon model override. The two Dark Falz scene classes use model and texture pointers in their shared part layout. Gol Dragon uses the native Ninja model structure for its cloned node override.

The standalone resource review compiled 2,450 source objects and the encounter review compiled 2,449. The cumulative stack and working fork each compiled 2,450. Every selected input has the same allocated contents and relocation destinations as its reference after resolving the new names to their original addresses. The three renamed exports have one provider each. Each named private record has the original bytes and offset. The stock checker passed in object-report mode against current upstream for both reviews and the cumulative stack. The address comparison against fork main still has no lost matched or linked code or non-padding data. The executable hash on this base remains unverified.

The source index gives partial evidence for eight historical paths and closes the Nano Drago and main-menu header records. Their complete declarations and comments survive in order and linkage at the current owners, including the ancestor-side removals. The index has 1,741 entries awaiting owner comparison and 514 with partial evidence. The layer check and eleven unit tests passed, and the disposable workspace still reproduces all 133 tooling paths.

### Shortcut preview and native symbol-chat construction

The window review at `51ded1241f` and cumulative stack at `76d4f68f70` now carry the complete 52-byte shortcut preview pool at 0x805DD348 through 0x805DD37B. It has the separator, icon choices, dimensions and depth under the fork names. The preview, preset list and chat list construct `TWindowChatSymbol` directly. The editor calls the same native constructor for its base subobject and uses the base selection and visibility methods. The fork tooling overlay retains the empty-kind host behavior.

The preview retains its 1,044 original instruction bytes. The five earlier functions and their table remain in the current shop window owner. The implementation keeps the name `show_shortcut` because it fills the whole window, including the entry labels and icons. The typed word-select formatter and its callers are covered in the follow-up below. The fork index records the preview and symbol-chat changes across seven historical paths. It has 1,734 entries awaiting owner comparison and 521 with partial evidence.

Each of the three builds compiled 2,450 source objects. The standalone review compared 2,485 selected inputs. The combined stack and working fork compared 2,484 each. Allocated sections, symbol locations and relocation destinations match the preceding objects after resolving the new names to their original addresses. The thirteen data entries and three symbol-chat method definitions have one provider each, the same original bytes and no unresolved references to the old names. Both review heads passed the stock checker in object-report mode. The comparison with fork main found no lost matched or linked code or non-padding data. The executable hash remains unverified on this base.

### Typed word-select formatters and callers

The window review at `9bc5490c5e` and cumulative stack at `5439d728d5` carry the fork's 12-byte word-select record through Japanese, English, German, French and Spanish formatting. The dispatcher, speaker lookup and message display share the original 16-bit speaker contract. The incoming message, shortcut preview and list, editor and existing window display pass the typed record. The Spanish archive loader and formatter share the word-prefix category pointer.

All eight entry points retain their original bytes and addresses under the fork names. Each has one provider and no caller refers to an old label. Each build compiled 2,450 source objects. The comparison covers 2,485 selected inputs on the window branch and 2,484 each on the combined stack and working fork. Their allocated sections, symbol locations and relocations match the preceding builds after mapping the eight names. Both reviews passed the upstream checker in object-report mode. The comparison with fork main found no lost matched or linked code or non-padding data. The executable hash remains unverified on this base.

The source index closes three complete fork paths and records partial recoveries on seven more. The new shared header, the message display source and the incoming message source match the fork after include relocation and whitespace normalization. The index now has 1,726 entries awaiting owner comparison and 526 with partial evidence. All 133 tooling paths still reproduce in the fork-only workspace.

### Time-setting scene and shared display constants

The window review at `70f73ffcbb` and its cumulative counterpart `1c761f22be` carry the fork names for the startup actions, message timer and text buffer, two display formats, sprite unit scale and nameplate height. The handler at 0x802E2AD4 is called `show_load_message` because the native `create_backgrounds` at 0x802E1C6C allocates the two backgrounds. The load-message handler calls it and opens the dialog. Seven scene field offsets and the 24-byte state record are checked in source. The 25-state table and its callback references match the original.

The four method addresses and four pooled-data addresses retain their original bytes and references. Each renamed method has a single provider. Each of the three builds compiled 2,450 source objects. The standalone review compared 2,485 selected inputs and the combined stack and working fork each compared 2,484. The allocated sections, symbol locations and relocation destinations agree with their preceding builds. Both review heads passed the upstream checker in object-report mode. The fork-main comparison continues to account for all matched and linked source ranges separately from the historical padding difference. The executable hash remains unverified on this base.

The fork source index closes the complete default-sprite wrapper and records partial evidence for three more source paths. It has 1,724 entries awaiting owner comparison and 527 with partial evidence. The fork-layer check and eleven unit tests passed. The fork-only workspace still reproduces all 133 tooling paths.

### Boss effect constants and model handles

The encounter review at `8f5eb4303f` and the cumulative stack at `44bfc6c84b` carry the fork's named Dark Falz projectile and fade coefficients, the Dragon tail and crater scales, the De Rol Le tunnel effect tail, the Vol Opt pillar template, and the Olga Flow death sequence limit. The Dark Falz tower uses its typed fade state and inherited position. The Olga Flow motion parts store model and texture-list pointers. The two tunnel guard labels use descriptive source names for the existing word and byte allocations.

Twenty named ranges match the original data or uninitialized storage sizes at their exact addresses. The check found one provider for each of the three renamed exports. All allocated sections, symbol locations and relocation destinations agree with their preceding builds after the three names are accounted for. The standalone review compiled 2,449 source objects and compared 2,487 selected inputs. The combined stack and working fork each compiled 2,450 source objects and compared 2,484 selected inputs. Both review heads passed the upstream checker in object-report mode. The fork comparison retains all non-padding source coverage. The executable hash remains unverified on this base.

The fork source index accounts for the two complete constant units and their headers and records additional evidence for eleven original source paths. It has 1,715 entries awaiting owner comparison and 532 with partial evidence. The fork layer passed all eleven tests and its materialized workspace reproduces all 133 tooling paths.

### Actor animation, equipment effects and technique resources

Four existing review groups carry the latest fork changes. The actor-presentation review at `5a2a778de3` adds the typed bone-angle capture and its original Ninja node walk, names the Nano Drago animation binding and names the weapon preview offset. The spatial-effects review at `f781f52b51` names the equipment effect collision template. The combat review at `1e45071f32` carries the Sinow Zoa melee callback as `vfunc_105`. Both Sinow Zoa dispatch tables point to that callback at word index 105. The resource-lifetimes review at `b4b46375d2` names both texture strings in the technique loader. Local constant pointers preserve their position in the compiler's read-only pool.

The original layout and bytes agree for eight named ranges, including three functions and five data records. Each of the four renamed exports has one provider. The four standalone reviews, cumulative stack and materialized working source agree with their corresponding earlier object layouts and relocation targets after the alias changes. The stock checker passed in object-report mode on the standalone reviews and cumulative stack. The executable hash remains unverified on this base. The fork layer passed eleven tests and reproduces all 133 tooling paths.

The source audit closes the complete technique texture-name file and adds evidence for eight other fork paths. It has 1,708 entries awaiting owner comparison and 538 with partial evidence.

### Enemy projectile, nest, claw and color sequences

The combat review at `a42b08d6eb` and cumulative stack at `63e8a18e15` carry the fork's typed Dark Gunner projectile constructor and hit dispatch, including the 16-bit owner ID and the shared collision query and attack interfaces. The Fly nest uses its const pending-spawn check and named replenish fields. The Bal Claw body and claw share the base model selector. The claw's setup is named `initialize_claw` because it is called from both native constructors after construction of the base. Gee's color sequences use the base Gee receiver, named color fields and an unsigned flag test. Moja's name string has its fork label in the symbol registry and its pointer initializer keeps the original storage.

Nine renamed ranges match the original bytes, including eight routines and one string. The standalone combat review compares 2,488 selected inputs and the combined stack and materialized fork each compare 2,484. Each renamed export has one provider, and the allocated sections and relocation targets match the preceding builds after mapping the renamed symbols. The standalone and combined heads passed the project checker in object-report mode. The executable hash remains unverified on this base. The fork layer passed eleven tests and reproduces all 133 tooling paths.

The source audit accounts for the complete projectile implementation and header and adds evidence for ten other fork paths. It has 1,702 entries awaiting owner comparison and 542 with partial evidence.

### Rain, fish and the Com Card follower

The world-object review at `90d72bb2bd` uses the native rain and fish constructors. Rain uses the fork's typed drop array in initialization, movement and drawing. Fish uses the typed placement fields, destructor and five area resource descriptors. The ancient rare enemy container uses its original class-name pointer. The window review at `0a446167fd` gives both status-window callers the native Com Card follower constructor and binds its selected-index setter to that class. The Com Card unit uses the fork's deferred compilation setting and emits its dispatch table before the icon switch table.

The combined stack at `011823a1c6` preserves the bytes and locations of nine renamed ranges, including the three class-name pointers and the follower dispatch table. The fish's 52-byte dispatch table and 240-byte area resource table retain their original layouts. Both standalone reviews and the combined stack passed the upstream checker in object-report mode. The compiled sections and relocation targets agree with their preceding builds after mapping the renamed symbols. The executable hash remains unverified on this base. The fork layer passed all eleven tests and reproduced all 133 tooling paths.

The source audit closes three complete headers and records additional evidence for seven original paths. It has 1,693 entries awaiting owner comparison and 548 with partial evidence.

### Native word selection lifetime and scrolling

The window review at `6bb8433bb1` and combined stack at `f6648c7664` use the native word-selection constructor, destructor, scroll update and offset method. The constructor lays out the visible rows, list ID and scroll position through named fields. The class uses the shared entry list in `TWindowBase`. The standalone review uses its existing array-release name and the combined stack uses the array operator carried by the memory review. Both target the original routine at 0x80147A80.

The word-window source uses the fork's deferred compiler setting and lists the functions in reverse so their compiled order stays the same. The compiler emits the six-word dispatch table at 0x804EFC90 with its original four method targets. A build with the entry-table definition in the same file put the 168-byte table ahead of that dispatch table and changed the constructor instructions. The adjacent entries now have a source-linked unit at their original range of 0x804EFCA8 through 0x804EFD4F. Joining the two data ranges reproduces the previous allocation, content and references. The five renamed exports each have one provider and match their original ranges.

The standalone review and combined stack passed the project checker in object-report mode. They compiled 2,451 source objects each, with 2,486 selected inputs for the standalone and 2,485 for the combined stack. The working fork uses the same selected inputs and object layouts as the combined stack. The executable hash remains unverified. The fork layer passed eleven tests and reproduced all 133 tooling paths. The source audit closes the complete word-window header and records evidence for four other paths. It has 1,689 entries awaiting owner comparison and 551 with partial evidence.

### Native word-select menu, scrollbar and string window

The window review at `2b52cfe3cb` and combined stack at `a39c9a4d2b` restore the native three-row menu, scrollbar and string-window constructors and their callers. The menu selection fields and scrollbar geometry fields have named layouts. The string window takes a typed draw context and reserves all 192 bytes for eight vertices. Its renderer preserves the original instructions, including the stack frame.

The menu and scrollbar use translation-unit-specific deferred compilation. The scrollbar keeps its span helpers inline to preserve the original draw instructions. The generated six-word dispatch tables start at 0x804EFBAC and 0x804EFBE4 with their original four targets. Each table ends before four zero bytes restored by the following unit's eight-byte data alignment. All twelve renamed ranges have one provider with the original bytes and addresses. The standalone review builds with 2,486 selected inputs. The combined source and the working fork use 2,485, with identical allocated sections, symbols and relocations.

Upstream master, the standalone window review, the combined source, the all-source snapshot and the working fork all reproduced the original GPOE8P executable, SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. The project checker passed with a full build for the window review, combined source and all-source snapshot. The comparison with fork main found zero regressions or missing linked code or non-padding data. Its aggregate data count is 2,358 bytes lower, from 2,521 bytes of historical alignment padding leaving coverage and 163 bytes entering coverage. The fork layer passed eleven tests and materialized all 133 tooling paths. The audit closes three complete headers and adds evidence for six other paths. It has 1,681 entries awaiting owner comparison and 556 with partial evidence.

### Native status gauge constructors and drawing

The window review at `ef53963eb2` and combined stack at `531ec09862` restore the gauge base constructor at 0x80256BDC and the derived constructor at 0x802572F0. The derived class reads a 36-byte layout record through named fields. The width and update routines also use the class fields. The extended gauge calls the inherited bar renderer with a typed draw context. Six source units agree on the constructor and drawing entry points, including both item-help constructors.

The two 24-byte dispatch tables at 0x804CF918 and 0x804CF930 have their original layout, with a zero in the pure base class slot. The three renamed ranges have one provider each. The allocated bytes, symbols and relocation targets match the preceding window pass across all 2,486 standalone inputs and 2,485 combined inputs. The standalone window review, combined source, all-source snapshot and working fork reproduced GPOE8P SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. The standalone, combined and all-source project checks passed with full builds. The original fork comparison has no regressions or loss of linked code or non-padding data, with the same reconciled aggregate padding difference as the preceding pass. The fork layer passed eleven tests and materialized all 133 tooling paths.

The source audit closes two complete gauge headers and adds evidence for seven other paths. It has 1,675 entries awaiting owner comparison and 560 with partial evidence.

### Shared bag-warning window lifecycle

The window review at `79d3848fdf` and combined stack at `73745157f7` use a common update routine for the single-player and four-player bag warnings. Both classes share the window pointer, 128-byte message buffer and countdown at the original offsets. Each keeps its own eligibility check and message creation. The current single-player native constructor and folded source owner are preserved.

The original compiler inlines the shared lifecycle into both 176-byte update methods. The window-root test uses the full-register return convention already used by these callers. The bool declaration produces a low-byte mask in those two methods. Six affected constructor, open and update ranges and every selected link input have the same bytes and relocations as the previous window pass. The standalone window review, combined source, all-source snapshot and working fork reproduced GPOE8P SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All three upstream-shaped project checks passed with full builds. The fork layer passed eleven tests and reproduced all 133 tooling paths.

The source audit closes four warning headers and the relocated page-indicator header. It records partial evidence for three warning source paths. It has 1,667 entries awaiting owner comparison and 563 with partial evidence.

### Typed player-window commands and queries

The window review at `bb6b24551c` and combined stack at `b55c8aabcf` carry the fork's typed player-window command and query dispatch. They cover menu enable and disable, window suppression, active-menu checks and visibility checks. Lobby, shop, quest, trade, warning and battle callers use the shared per-client declarations. The pass changes 42 paths. It keeps the split that owns the original callback tables and uses the existing controller callback header.

The eight name changes keep their addresses, instruction bytes and single definitions. The 216-byte callback table preserves all 18 three-word records and their relocation targets. The lobby give-up loop uses a scoped client index and player value to retain the original register allocation with the corrected command declaration. The selected link inputs have matching sections, symbols and relocations after the names are mapped. The standalone review, combined source, all-source snapshot and working fork reproduced the original executable SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. The project checker passed with full builds for the three upstream-shaped branches. The fork layer passed eleven tests and materialized all 133 tooling paths.

The audit reconciles 13 complete fork paths and records partial evidence against 33 other paths. It has 1,635 entries awaiting owner comparison and 582 with partial evidence.

### Native window callbacks and borrowed draw arguments

The window review at `85ece01de8` and combined stack at `6d9c527699` construct the callback window through its native class and use the shared two-argument callback type. The producers cover serial entry, password, agreement, Episode III, player status, symbol chat and character selection. The character-select callback stays on the native transition class that constructs and owns the callback window. The current window descriptor and inherited size fields retain their layouts.

Eight functions retain their original addresses, instructions and single definitions. The compiler-generated 24-byte callback window table keeps the original four method targets at 0x804DE374. Every selected link input retains its allocated bytes, symbol positions and relocations after mapping the function names. The standalone review, combined source, all-source snapshot and working fork reproduced SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. The project checker passed with full builds for the three upstream-shaped branches. The fork layer passed eleven tests and materialized all 133 tooling paths.

The audit reconciles 4 complete fork paths and records partial evidence for 16 others. It has 1,618 entries awaiting owner comparison and 595 with partial evidence.

### Keyboard queries, composer modes and chat availability

The window review at `904154a252` and combined stack at `fcaf0573ae` use a shared declaration for the three keyboard input queries, with a signed full-register result. The composer owns its input-mode byte and setter. The hard and soft keyboards take the draw context in their status and frame routines. The chat availability test uses the real chat receiver, its composer state and the signed hard-keyboard timer. The controller, log and trade callers share that declaration. This pass changes 24 paths.

Three renamed functions and six query or gate functions retain their original addresses, instruction bytes and individual providers. Every selected link input agrees with the previous pass after normalizing the three names in symbols and relocations. The standalone review, combined source, all-source snapshot and working fork reproduced the original executable SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. The three upstream-shaped project checks passed with full builds. The comparison against fork main found no lost compiled or linked functions or non-padding data. The fork layer passed eleven tests and materialized all 133 tooling paths.

The audit reconciles 5 complete fork paths and records partial evidence for 18 others. It has 1,605 entries awaiting owner comparison and 603 with partial evidence.

### Native chat and keyboard child ownership

The window review at `f5e4fa6389` and combined stack at `96d3b95da5` carry the fork's named chat input state through the three input modes and child teardown. The composer owns its flag, mode-byte accessors, reset and conditional flush. The hard keyboard owns its input reset and key-hold state. Short mail, trade, controller, card and shortcut callers use the corresponding native interfaces. The input methods keep the original allocation, reset and child retirement order. This pass changes 19 paths.

Nine renamed ranges and five retained chat transition functions reproduce the original instructions at their original addresses. The compiler renumbers two private hard-keyboard labels. The 312-byte key-handler table and one-byte initialization flag keep their original storage and relocation targets. The selected link inputs match after normalizing both private labels and the nine renamed exports. The standalone review, combined source, all-source snapshot and working fork reproduce SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. The three upstream-shaped branches passed the full project check. The fork layer passed eleven tests and reproduced all 133 tooling paths.

The audit adds evidence to 16 fork paths and has 1,601 entries awaiting owner comparison and 607 with partial evidence.

### Shared window layout and vertex records

The window review at `8b5b17c95c` and combined stack at `0dd3f7aebc` name and check the 20-byte window descriptor in the existing layout header. The base window setup reads the named extent, order, flags and entry pointer. Three callers set the extent through the same fields. All 21 descriptors defined through the fork schema have a source provider at the original address and preserve all 420 bytes.

The word-select menu, scrollbar, string and word windows use the shared 24-byte vertex record. The storage initializer and UV copy use the fork's declarations at their original addresses. Their callers preserve the eight-vertex buffers and relocation targets. The combined comparison matches all selected inputs after mapping the two function names. The standalone review, combined stack, all-source snapshot and working fork reproduce SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All three upstream-shaped project checks passed with full builds. The fork layer passed eleven tests and reproduced all 133 tooling paths.

The audit reconciles 2 complete fork headers and records partial evidence for 29 paths. It has 1,581 entries awaiting owner comparison and 625 with partial evidence.

### Native message constructors and shared scrollbar storage

The window review at `ba6d8f0d4a` and cumulative stack at `65b75fdd24` use native constructors for Message, Infomation, Log, Page, Quest and Scroll. Their factories pass the original extent, row counts, client words and flags. Log, SubComCardList, MenuIconLine, CustomSelect and SymbolChatParts use the 12-byte scrollbar storage. ChoiceSetting shares the frame counter and release helpers through the original storage-level interface.

The six message constructors and four scrollbar routines match 844 original instruction bytes. All 24 scrollbar call sites reach their original addresses in the linked executable. Each build compiled 2,451 source objects. The object comparison preserves every selected section and relocation after mapping the ten names. The standalone review, combined stack, all-source snapshot and working fork reproduce SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All three upstream-shaped project checks passed with full builds. The fork layer passed eleven tests and reproduced all 133 tooling paths.

The audit reconciles 5 complete fork paths and records partial evidence for 25 paths. It has 1,555 entries awaiting owner comparison and 646 with partial evidence.

### Native numeric readout windows

The window review at `09874ab4f6` and cumulative stack at `df5b75721a` use native construction for Meseta, Quantity and Cost. The Meseta and Quantity scales are floats at their original offsets. Shared factory declarations preserve the word-valued client inputs and the narrowing at the short-client call sites. The shop callers use the Cost value bridge with its actual receiver.

The three constructors and value bridge match 700 original instruction bytes. The twelve factory calls, ten value-update calls and four direct constructor calls retain their original targets in the linked executable. The three virtual tables and Quantity descriptor preserve their 92 bytes at the original addresses. Each build compiled 2,451 source objects. The object comparison preserves all selected inputs after mapping the four names. The window review, combined stack, all-source snapshot and working fork reproduce SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All three project checks passed with full builds, and the fork layer passed eleven tests and reproduced all 133 tooling paths.

The audit reconciles 4 complete fork headers and records partial evidence for 16 paths. It has 1,539 entries awaiting owner comparison and 658 with partial evidence.

### Native status, timer and guild-card displays

The window review at `e77499a9ec` and cumulative stack at `39b136da5f` use native construction for SimpleStatus, Status, PartyStatus, Timer and UserSort. The two status factories preserve their original clients, descriptors and slot calculation. SimpleStatus refresh manages all five icon pointers, and the destructor follows the original four-slot cleanup. Timer keeps both original layout initializer calls. The guild-card task passes the selected record to UserSort and stores the resulting window handle.

The seven changed entry points retain 668 original instruction bytes and all ten direct call targets. Five descriptors and five compiler tables retain their 220 original bytes and addresses. Each build compiled 2,451 source objects. All selected inputs preserve their allocated sections and relocations after mapping the seven names. The window review, combined stack, all-source snapshot and working fork reproduce SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All three project checks passed with full builds. The fork layer passed eleven tests and reproduced all 133 tooling paths.

The audit reconciles 4 complete fork headers and records partial evidence for 11 paths. It has 1,530 entries awaiting owner comparison and 663 with partial evidence.

### Native menu and guild-card list lifetimes

The window review at `5ebb66f7d8` and cumulative stack at `9808118b7b` use native constructors for Menu and both forms of SubComCardList. The list retains its page indicator, word-valued mode input and original setup order. Rendering and base task dispatch use the native class interfaces. Four callers set the loss flag through Menu.

The three constructors and loss-flag method retain 768 original instruction bytes and all nine direct call targets. The original menu descriptor and two compiler tables retain their 68 bytes and addresses. Each build compiled 2,451 source objects, and the object comparison preserves every selected section and relocation after mapping the four names. The window review, combined stack, all-source snapshot and working fork reproduce SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All three project checks passed with full builds. The fork layer passed eleven tests and reproduced all 133 tooling paths.

The audit reconciles 4 complete fork paths and records partial evidence for 9 paths. It has 1,525 entries awaiting owner comparison and 664 with partial evidence.

### Native lobby, area map and quest-board windows

The window review at `2d0138bdc2` and cumulative stack at `f5fda12041` use native constructors for BreakIn, ComCard, AreaMapDisp and QuestBoardSelect. The six allocation sites preserve the original arguments and allocation paths. The ComCard, follower and LockOn entry-help calls pass entry storage directly. ComCard retains its original table and deleting entry, including the trailing word. AreaMap preserves text, radar and heading cleanup order. QuestBoardSelect forwards the actual text to width measurement and retains its signed selection sentinel.

The four constructor bodies retain 720 original instruction bytes. The six constructor calls and three entry-help calls retain their original targets in the linked executable. Four descriptors and four tables retain their 180 bytes and original locations. The object comparison preserves all selected inputs after mapping the four constructor names. The window review, combined stack, all-source snapshot and working fork reproduce SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All three project checks passed with full builds. The fork layer passed eleven tests and reproduced all 133 tooling paths.

The audit reconciles 5 complete fork declarations and records partial evidence for 9 paths. It has 1,516 entries awaiting owner comparison and 668 with partial evidence.

### Native action palette and customization windows

The window review at `d1766607d8` and cumulative stack at `70717f69b9` use native constructors for ActionPalette, CustomEquip and CustomSelect. The selected-action lookup belongs to CustomSelect and returns the record pointer used by both controller calls. The ActionPalette constructor keeps the original tag initialization and reset order. CustomSelect's early returns precede initialization of its two child fields, so exact recovery leaves that original initialization boundary in place.

The three constructors and action lookup retain 896 original instruction bytes and all five direct call targets. The three descriptors and three compiler tables retain 132 bytes at the original addresses. The object comparison preserves all selected input sections and relocations after mapping the four names. The window review, combined stack, all-source snapshot and working fork reproduce SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All three project checks passed with full builds. The fork layer passed eleven tests and reproduced all 133 tooling paths.

The audit reconciles 2 complete fork headers and records partial evidence for 7 paths. It has 1,512 entries awaiting owner comparison and 670 with partial evidence.

### Native symbol-chat editor windows

The window review at `f872aebd46` and cumulative stack at `11129323ca` use native constructors for FaceType, Help, Parts and PartsSet. The seven allocation sites borrow the original editor values and retain the original heading and scrollbar cleanup order. Six help-state operations use the actual Help receiver, with all twelve original calls retained.

The four constructors and six help operations retain 844 instruction bytes at their original addresses and all nineteen direct call targets. Three layout descriptors and four compiler tables retain their 156 bytes. Every selected input preserves its allocated sections and relocations after mapping the ten names. The window review, combined stack, all-source snapshot and working fork reproduce SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All three project checks passed with full builds. The fork layer passed eleven tests and reproduced all 133 tooling paths.

The audit reconciles 5 complete fork declarations or owners and records partial evidence for 11 paths. It has 1,503 entries awaiting owner comparison and 674 with partial evidence.

### Native shortcut preview and list

The window review at `38e995abae` and cumulative stack at `fd001b831c` use the native ShortCut preview constructor and static ShortCutList factory. The preview retains the heading and the text and symbol child close order. The constructor calls the existing source-owned shortcut renderer using the original index and record. The list preserves the signed page calculation and typed page indicator.

The preview and list constructors and the list factory retain 480 original instruction bytes and all four direct call targets, including the preview renderer call. The descriptor and two compiler tables retain 72 bytes at the original addresses. All selected sections and relocations compare identically after mapping the three names. The window review, combined stack, all-source snapshot and working fork reproduce SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All three project checks passed with full builds. The fork layer passed eleven tests and reproduced all 133 tooling paths.

The audit reconciles 1 complete fork header and records partial evidence for 5 paths. It has 1,501 entries awaiting owner comparison and 675 with partial evidence.

### Front-end callback header audit

The complete fork headers for `TAdEp3Exist` and `TAdAgreementBaseGC` match the current owners at `fd001b831c` after adjusting their path-based include guards and the relocated `TObject` include. The [fork source index](2026-11-18-fork-review-index.tsv) records both matching blobs. The audit has 1,501 entries awaiting owner comparison and 673 with partial evidence.

### Native item preview and lock-on windows

The window review at `61d3d45839` and cumulative stack at `22f7ebeb5b` use native construction for the item texture preview and the lock-on window. The preview owns the icon-loading operation and queues destruction of its loader. The Mag and shop callers pass the original item records to the preview. Lock-on retains its typed refresh callback, validates the target before allocation, and runs the original binding during construction.

The four renamed exports retain 700 instruction bytes. Fourteen direct calls retain their original destinations, including the two factories, all three item icon requests and both lock-on binding calls. Two descriptors, two virtual tables and four layout tables retain 624 bytes at the original addresses. All selected sections and relocations match after mapping the four names. The window review, combined stack, all-source snapshot and working fork reproduce SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All three project checks passed with full builds. The fork layer passed eleven tests and reproduced all 133 tooling paths.

The audit reconciles 3 complete fork declarations and records partial evidence for 8 paths. It has 1,493 entries awaiting owner comparison and 678 with partial evidence.

### Native choice and sound option windows

The window review at `c50d4c1908` and cumulative stack at `467564e30b` use the native sound balance constructor and the two unsigned-count choice constructors. Sound balance measures both labels from their text pointers and restores both gains from the original settings call. The choice factory forwards the original extent pointer and count, and the information popup owns its entry initializer. The cursor still interprets the stored 16-bit count as signed.

The four renamed exports match 676 instruction bytes. Twenty direct calls retain their original linked destinations. Two descriptors, two layout tables and three virtual tables retain their 260 bytes at the original addresses. The linked addresses and sizes confirm the choice exports even where the compiler's intermediate object contains extra space. All selected sections and relocations match the previous build after mapping the four names. The window review, combined stack, all-source snapshot and working fork reproduce SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All three project checks passed with full builds. The fork layer passed eleven tests and reproduced all 133 tooling paths.

The audit reconciles 10 complete fork paths, including the two options factories, the complete option state machine, and the option header's declarations on the save task that owns them. It records partial evidence for 5 more paths. It has 1,484 entries awaiting owner comparison and 677 with partial evidence.

### Option layout and save-task source audit

The current source at `467564e30b` carries both complete fork units for window positions and the memory-card save dialog. The layout uses the shared two-float position records and preserves the existing split-screen table choice and window ordering. The save dialog uses the original save-task receiver, format and result calls, and the compiler-generated deleting entry. All 13 original functions are source-linked and reproduce their instruction bytes at the same addresses in both builds. The audit has 1,482 entries awaiting owner comparison and 677 with partial evidence.

## Consolidated review queue on `c572111ed6`

The local branches below group related changes for review. The component branches retain their individual validation records. Together the eleven groups cover the 1,339 added, changed and removed source paths in the difference from upstream master to `a5540e955c`. Separate path entries count both endpoints of renames. Shared files can appear in multiple groups.

| Review | Local branch | Tip | Paths from pinned master |
| --- | --- | --- | ---: |
| Archive loading, audio streaming and quest-cache lifetimes | `great-merge/current/resource-lifetimes` | `ba96b4a344` | 219 |
| Array allocation, memory copies and nullable release | `great-merge/current/memory` | `381e372339` | 257 |
| Enemy targeting, battle parameters, collision and player techniques | `great-merge/current/combat` | `ac997883bf` | 209 |
| Radar, raft effects, scrolling strips and boss trail rendering | `great-merge/current/encounter-drawing` | `8ccc7adee4` | 117 |
| Positional sound, area effects and particle spawning | `great-merge/current/spatial-effects` | `748755c261` | 342 |
| Model hierarchy, renderer callbacks and matrix interfaces | `great-merge/current/render-interfaces` | `ad8e27cbe6` | 189 |
| Texture binding, BML accessors and archive lifetime | `great-merge/current/bml-resource-lifetime` | `39e6385750` | 453 |
| Actor orientation, demo playback and animation bindings | `great-merge/current/actor-presentation` | `9c1e8b2c3f` | 381 |
| Network buffer, timer, DNS and PPP contracts | `great-merge/current/network-contracts` | `202831ff52` | 47 |
| World-object resources and map-collision setup | `great-merge/current/world-object-resources` | `118f154267` | 33 |
| Window entry, input and rendering interfaces | `great-merge/current/window-frames` | `37e0caf80a` | 268 |

The memory review applies the array allocation component `63c3f4ea45` first, then the memory-copy and nullable release changes from `6194d462e1`. The two components overlap in the menu font cleanup. Its resolved form uses matching array allocation and deletion for the glyph table and palette, and uses the nullable release helper for the glyph data. The compiler output confirms both array delete calls and the nullable release call.

The standalone memory branch compiled 857 selected objects, including 247 edited sources and 610 callers of changed headers. All allocated sections, symbol locations and relocation targets match prior compiled objects once the five aliases are mapped to their original addresses. In 856 cases the objects match upstream and both standalone components. The lobby-join object matches the validated array-allocation component. The check compares object files on the pinned master `c572111ed6`.

The resource-lifetimes review keeps five commits in order. The archive and quest components establish the loader, cache and save-image contracts. The three audio commits then adopt typed sector reads, signed ADXB channels and pitch forwarding. Eight overlapping files combine the two sets of declarations and calls. The sky loader keeps its typed BML lists and uses the shared ADXF close operation. The asynchronous texture loader checks completion through ADXF and passes the texture to the typed GVM loader.

The grouped resource branch compiled 1,007 selected objects, including 168 edited sources. After mapping 52 symbol names by section, address and size, all rebuilt objects match previously compiled versions. Of these, 992 match upstream and every standalone component. Fourteen match the archive component and one matches the quest component. A separate check across all 2,487 selected linker inputs found a single provider for each renamed export and no unresolved or stale references to those names. Validation ran at the object-file level.

The encounter-drawing review brings together radar map and marker state, De Rol Le and Barba Ray raft effects, scrolling strips and the Dark Falz and Olga Flow effects. City seasonal rendering keeps both shared declarations. The two Olga Flow constructors call the typed strip initializers and create their typed afterimage receivers. The comment-only configure.py edit stays on the fork.

The grouped drawing branch compiled 1,571 selected objects, including 74 edited sources. Of these, 1,564 match upstream and each standalone component, and seven match their validated individual components. The comparison maps 40 names at their original addresses. Across 2,484 selected linker inputs, each of the 37 renamed exports has one provider with no stale references. The three private records match their compiled local offsets and sizes. Validation ran at the object-file level.

The combat review keeps six commits covering enemy movement and targeting, battle parameters, Gyaranzo resource records, ground contacts, player techniques and the special-event item. In the overlapping callers, typed ground queries receive the shared target vectors. The Gyaranzo constructor keeps the native lifecycle and reads the typed movement, collision and model records. The special-event item inherits the existing compiler profile under its renamed source path.

The grouped combat branch compiled 1,283 selected objects, including 145 edited sources. Of these, 1,272 match upstream and every standalone component. Ten match their validated individual components. The Gyaranzo object matches the cumulative source when 13 differently named calls are compared by function address and size. The objects agree on allocated bytes and symbol locations. The selected 2,486 linker inputs contain one provider for each of the 65 renamed exports and no unresolved or stale references to those names. The private missile attack record stays at 0x8043C464. Validation ran at the object-file level.

The spatial-effects review brings the world-position particle factories together with one-shot, persistent and area-dependent sound requests. The two commits touch many of the same callers. The combined form retains both typed interfaces across 58 overlapping files. The Dolmolm caller now takes its declarations from the shared headers.

The grouped effects branch compiled 559 selected objects, including 331 edited sources. All match upstream and both standalone components after mapping six renamed symbols to their original addresses. The 2,487 selected linker inputs contain one provider for each renamed export and no unresolved or stale references to those names. Validation ran at the object-file level.

The texture and BML review keeps the existing four-commit dependency chain. The first commit carries the current texture-list type through renderer callers. The next recovers typed BML model and texture accessors. The third applies the interfaces to the Dark Falz Zako model and texture lifetime, followed by the shared archive constructor and destructor. Those boundaries provide a review order across the 453 paths.

A fresh build of the grouped BML tip reproduced all 984 affected objects from the validated snapshot, including 437 edited sources. Allocated sections, exact symbol locations and relocations match. Each of the ten renamed exports retains its address and has one provider across the 2,487 selected linker inputs, with no stale references. Validation ran at the object-file level.

The render-interfaces review combines the model hierarchy, node position capture, material fades, native callback types and shared matrix and vector operations into six commits. The Berura, Canadin and draw traversal callers keep their typed node and matrix state and call the recovered matrix or view helpers. The small SDK declaration fixes travel with their native callers.

The grouped branch rebuilt 1,350 selected objects, including 116 edited sources. Allocated sections, symbol locations and relocation targets match validated baselines after mapping names by address and size. Of those objects, 1,348 match upstream and both components. The other two match the model-rendering component. The 2,487 selected linker inputs have one provider for each of the 154 renamed exports and no stale or unresolved references to those names. The other 78 names are private. Validation ran at the object-file level.

The actor-presentation review keeps six commits covering the shared demo predicate, actor positions and rotations, action and motion lists, NPC bindings, named actor parameters and the Seabed dolphin registration. At shared call sites, the NPC bound check uses the typed rotation with the binding’s debug action limit, and the Gee breakup calls use the typed position and yaw with the named model records.

The grouped actor branch rebuilt 1,486 selected objects, including 353 edited sources. Of those objects, 1,448 match upstream and every component after name normalization. Thirty-eight match the validated actor-camera component. The 2,487 selected linker inputs contain one provider for each of the 35 renamed exports and no unresolved or stale references to those names. The other 14 names are private. Validation ran at the object-file level.

The network and world-object rows use their existing review branches. Each branch matches the tracked files in its verified build snapshot. Their per-commit comparisons and tests are recorded in the sections below.

### Cumulative review stack

The local branch `great-merge/current/review-stack` puts all eleven review groups on upstream `c572111ed6`. The world-object group has two commits and changes 38 paths in total. The audio callback and typed encounter follow-ups extend their standalone reviews and appear at the end of the cumulative stack. The tip at `070583514d` changes 1,356 paths, counting both sides of renames. The standalone review branches remain available.

| Stage | Group | Stack commit | Paths in stage | Object-file checks |
| --- | --- | --- | ---: | --- |
| 1 | network-contracts | `0368c735e9` | 47 | Tree equals the validated network review |
| 2 | memory | `a4009abcdc` | 257 | 906 objects, 16 renamed exports |
| 3 | resource-lifetimes | `f484c8671a` | 206 | 1,090 objects, 68 renamed exports |
| 4 | spatial-effects | `e3a6e2fe36` | 341 | 1,258 objects, 74 renamed exports |
| 5 | combat | `7dd3f44c70` | 211 | 1,558 objects, 139 renamed exports |
| 6 | encounter-drawing | `8a3dc02c93` | 110 | 1,715 objects, 176 renamed exports |
| 7 | window-frames | `141a9f9105` | 268 | 1,874 objects, 308 renamed exports |
| 8 | bml-resource-lifetime | `90ce759593` | 451 | 1,875 objects, 312 renamed exports |
| 9 | render-interfaces | `46f198c984` | 190 | 1,985 objects, 466 renamed exports |
| 10 | actor-presentation | `15b085f571` | 381 | 1,986 objects, 501 renamed exports |
| 11 | world-object-resources | `bad4f7f29a` | 33 | 1,987 objects, 505 renamed exports |
| 11 | Challenge enemy-set records and buffers | `e24c516c41` | 6 | 644 affected objects, 11 renamed exports |
| 3 | Audio file-system callbacks and stream buffers | `94eb357b12` | 18 | 644 affected objects, 5 renamed exports |
| 6 | Barba Ray encounter and Olga Flow death records | `070583514d` | 8 | 893 affected objects, 8 renamed exports, 2 local records |

The stack combines the array allocator and nullable release with typed archive loaders, carries the positional effects interfaces through combat and encounter drawing, and updates Gyaranzo’s fade field alongside the renderer header rename. The stage checks compare allocated sections, symbol locations and relocations with validated objects. They normalize same-address symbol aliases and check the raw references for stale names, missing providers and duplicate exports. The encounter through renderer stages match one Gryphon object's compiler-generated local names by section, offset, size and linkage. All 1,987 affected objects through `bad4f7f29a` match the cumulative source baseline. That check covers 505 renamed exports across 2,481 selected linker inputs. Validation ran at the object-file level.

The only source differences from `afe1ce8cb5` are the compiler-profile comment in `configure.py`, whose fork wording stays on the working fork, and removal of an empty C-linkage block in `src/pso/unk/text_800FA464.cpp`. The working fork descends from the review stack and carries the local documentation and tooling. The review stack is local pending publication approval.

The stack covers the cumulative source already prepared for upstream. The [fork source index](2026-11-18-fork-review-index.tsv) still has 1,761 entries awaiting owner comparison and 496 with some matching edit blocks. These entries track the older fork history through upstream's split realignment. Each needs a disposition before the historical source audit is complete.

### Challenge map set and action records

`e24c516c41` carries the typed enemy-set builder from fork commits `1f4e2d4a22` and `6dd3ce20d4` into the consolidated map-loading owner. It keeps the existing source boundary, uses the 0x10 header, 0x18 random event, 0x14 fixed event and 0x48 placement records, and keeps the neighboring array allocator and nullable release calls. The placement room and wave fields stay at offsets 0x0C and 0x0E. The builder preserves the unwritten header word during the original 16-byte copy. The fork's declaration order, mutable copy source and separate tail-address increment remain in the code and preserve the compiler's instruction order.

The builder remains at 0x80209D34 with size 0x454. All 644 affected objects compiled fresh and match the preceding stack after mapping the four function names and seven buffer names. The raw symbol check finds one provider for every renamed export across 2,481 selected inputs and no stale references. The working fork updates all eleven retention entries and compiles the same owner object. The map-collision factory header also has a complete fork-side comparison against the existing stack.

### Audio file-system callbacks and stream buffers

`ba96b4a344` groups the CVFS, DVD, memory-file and ADX callers with the existing resource-lifetimes review. The cumulative counterpart is `94eb357b12`. The shared registration forwards the callback context, diagnostic message and handle word. The file backends have the same signed size and opaque open types. ADX supplies the path and mode explicitly to its size queries. The public queries accept a const path and use the existing private path parser. The DVD completion callback has the two arguments used by the SDK.

Both stream buffers retain their addresses at 0x805D62D8 and 0x805D62DC and use the fork's pointer types. The three snapshots each recompiled 644 affected objects. Their allocated sections, symbol locations and relocations match their preceding objects after mapping five symbol names. Each renamed export has exactly one provider and no references to its old name. The fork retention list includes the three affected names that it carried before the change. Validation ran at the object-file level.

### Barba Ray encounter and Olga Flow death records

`8ccc7adee4` extends the encounter-drawing review. The stack includes the same changes at `070583514d`. Barba Ray selects crawfish action, position and yaw through the named pattern tables. Both spawn routines use class members and the shared angle type. The model and motion accessors return their actual types, and the tentacle node bank uses the Ninja layout for child and sibling links, position and roll. The Olga Flow death demo uses the fork's names for the origin and motion indices.

The standalone review recompiled 897 affected objects. The cumulative stack and working fork each recompiled 893. The allocated sections, symbol locations and relocation targets match their preceding objects after alias normalization. Eight renamed exports and two local records each have one definition and no stale references. The four renamed routines have the same bytes as the extracted function ranges and preserve the preceding object's section offsets. Their unlinked offsets are eight bytes past the extracted offsets. The fork's six affected retention entries follow the new names. Validation ran at the object-file level.

Three additional fork edits are already present under their current owners. The native container destructor, mine-trap physical attack member and reverse-tech cleanup walk match the extracted code and relocation targets at 0x8015C8D8, 0x8016F5B4 and 0x8011A3D8 respectively. The source index records those checks alongside the encounter changes.

### Fork-only tooling workspace

The local `great-merge/current/layered-fork` candidate at `7c4288c43c` adds 448 files to the cumulative source at `070583514d`. All its changes are additions under `fork/` or `.github/workflows/fork-*.yml`. The existing review files, stock build tools, and native configuration have the same Git tree entries as the stack.

The tooling workspace restores the active tools, host sources and build settings in a disposable checkout. Applying its compressed patch reproduces all 133 non-layer working-fork changes from `b6d4a527ad`, including file modes and binary fixtures. Both the source checkout and materialized checkout are clean. The fork check workflow uses this workspace for its host checks.

The layer check, 11 layer tests, all 294 existing tooling tests, the polygon and sphere probes, and the portable behavior and sanitizer checks passed locally. The 18 native translation units whose source differs in the tooling workspace have the same allocated sections, addressable symbols and relocations in the previously verified working-fork and stack object snapshots. The native source audit continues independently of the layer candidate.



Upstream master `c572111ed6` reorganized 715 files. The branches below start directly from that revision. Each was compiled from fresh objects, reproduced the original GPOE8P executable (SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`) and passed the upstream checker against a fresh master build. These first twenty branches combine at `734e53187f`. The four resource commits below extend `great-merge/current/all-source` to `59ab60ae41` across 1082 paths. The combined build passed the same checks. These are local review components. The previous matchpass grouping remains the guide for bundling related components for submission.

| Subject | Local branch | Commit | Paths from current master |
| --- | --- | --- | ---: |
| Recover radar map views and actor markers | `great-merge/current/radar-camera` | `a87a5d8123` | 20 |
| Recover encounter strip selection and texture scrolling | `great-merge/current/texture-strips` | `6ceb6c20b8` | 33 |
| Recover the shared demo playback check and its callers | `great-merge/current/demo-playback` | `32cf63b74b` | 112 |
| Recover enemy movement and player target selection | `great-merge/current/enemy-motion` | `938245496d` | 74 |
| Recover native callback signatures and SDK math declarations | `great-merge/current/native-callbacks-sdk` | `777ad3e8aa` | 11 |
| Recover battle parameter tables and their consumers | `great-merge/current/battle-parameters` | `de0774585f` | 79 |
| Recover actor positions, movement vectors and scripted camera playback | `great-merge/current/actor-camera-angles` | `5d0802c2e5` | 340 |
| Recover quest download caching and memory-card save images | `great-merge/current/quest-cache` | `819c685f00` | 25 |
| Recover archive loaders, movie lifetime and GVM textures | `great-merge/current/archive-lifecycle` | `4443f0c85f` | 130 |
| Recover Dark Falz effects and Olga Flow trail frames | `great-merge/current/boss-effects` | `cb172b2134` | 51 |
| Recover the De Rol Le and Barba Ray raft effects | `great-merge/current/raft-encounters` | `2032c512f9` | 20 |
| Recover player combat constants, weapon animation and technique effects | `great-merge/current/player-techniques` | `474dab4b5c` | 48 |
| Recover guild-card records, chat windows and keyboard input | `great-merge/current/guild-card-chat` | `df16b13beb` | 82 |
| Recover item-help dispatch and status window display data | `great-merge/current/item-help-status` | `372fd86847` | 10 |
| Recover ground contact results and radial collision queries | `great-merge/current/collision-results` | `121062c25f` | 60 |
| Recover byte and word copies and nullable heap release | `great-merge/current/memory-moves` | `6194d462e1` | 116 |
| Recover array allocation and storage release across game systems | `great-merge/current/runtime-array-allocation` | `63c3f4ea45` | 156 |
| Recover world-position particle factories and callers | `great-merge/current/particle-factories` | `a70dd5edd0` | 188 |
| Recover positional sound requests and area-dependent effects | `great-merge/current/positional-sound` | `25b8532604` | 252 |
| Recover result windows, page indicators and text measurement | `great-merge/current/result-windows` | `94f4d035fe` | 51 |

The combined branch recovers all 296 source bytes still missing on master in the original inventory. Guild-card and keyboard work supplies the last 48 bytes of speech-balloon and keyboard dispatch tables. The item-help and status window component supplies the final 64 bytes from the broader window-list group. Other window-list source changes still require comparison. The 90-row [address ledger](2026-11-18-fork-data-ranges.tsv) accounts for 980 exact source-linked bytes and 167 bytes of verified alignment padding. Comparison with fork main finds zero lost exact or linked functions and zero lost non-padding data ranges. The executable checks also covered all eight guild cards, all 256 item-help window flag combinations, and the ground-contact and radial queries.

Retail execution covered 40 overlapping, nonoverlapping and zero-length byte and word copies, 13 array allocation and release cases, and the nullable scalar release and file wrapper. The particle factories passed 30 cases. One-shot sound passed eight admission and position tests. Persistent sound passed its slot checks and four dispatch routines across all 36 floors. The allocation and copy changes belong together for review. The particle factories and positional sound share the spatial effect callers.

The result-window branch uses the upstream window constructors and restores the 12-byte page indicator with its client and arrow offset. The timed battle-music task owns the four-byte pointer at 0x805D5D90. The standalone and combined executions each passed 180 page-input cases. The combined item-help renderer also passed all 256 window flag combinations.

The new upstream owners include the item archive loader, the small help font, Gifoie, the Dark Falz player fade, the character-creation ruler and the two weapon-effect files. The review patches retain those upstream owners. Executable probes covered radar gates, both encounter strip rings, battle tables, targeting, demo playback, character vectors, quest caching, save artwork, GVM archives, Olga Flow trail frames and weapon animation. The port retains the upstream identity matrix table and the named tunnel scroll speed at their verified addresses.

`great-merge/fork-docs` carries the fork documentation on this upstream master. The complete earlier integration snapshot remains on `great-merge/integration` while its remaining source groups and fork tooling are carried forward.

### Shared matrix and vector calls

Commit `6294e0d34a` extends the native callbacks and SDK review with four shared functions from the fork. Matrix copy and concatenation use SDK matrix pointers and preserve their null-argument convention. Checked vector normalization now exposes its XYZ input and floating-point length. The two-argument view transform uses the existing camera declaration. The four symbol names stay at their verified addresses. The effect caller at `TeneFakeTecThunderEff.cpp` carries the fork's original declaration for the ignored result because changing its return type moved two independent pointer increments in the compiler output.

The patch changes 61 paths, including 53 source files. The review compiled and compared 950 affected objects. The cumulative source at `ae12ac4f52` and the working fork each compiled and compared 945. Their allocated sections, addressable symbols and relocation targets match their prior objects after mapping the four symbol names. The working fork passed 294 tests and its linker retention check.

### Network buffer and packet layouts

Commit `22e91f2417` starts the network contracts review on upstream master. It brings the fork's typed DHCP buffers to the upstream C implementation. Outgoing, reply and receive storage retain their existing 1500-byte regions. The DNS resolver and packed buffer pool keep their upstream records and gain compile-time checks for the field offsets covered by the fork. The changes leave the network state machine and its callback behavior intact.

The review, the cumulative source at `4a30242839` and the working fork each compiled and compared 39 affected objects. Their allocated sections, symbol locations and relocations match their baselines. The working fork passed all 294 tests and its linker retention check.

Commit `4ef7fa0aca` extends the review across the timer dispatcher, DHCP configuration, UDP callback registration and the Ethernet adapter. The three buffer descriptor constructors use the fork's typed interfaces across the IPv4, IPv6 and TCP callers. Timer registration and removal share the same callback type. The DHCP getters share their typed outputs with the connection setup. UDP registration passes the existing datagram layout to the three concrete callbacks. The EXI send completion uses the same named callback at registration and invocation. The network configuration lifecycle declarations now live with their source owner.

The patch changes 36 paths. The review, cumulative source at `06ac07ae27` and working fork each compiled and compared 48 affected objects. The allocated code and data, symbol positions and relocations match after mapping five renamed symbols. All 294 fork tests passed and the linker retention check found no missing or stale entries.

Commit `202831ff52` continues the network review with the typed DNS request, message and callback records. Fragment reset and checksum helpers use the records their callers pass. The connection callbacks use the current C connection type and the shared PPP control header. IPCP and IPv6CP reuse a common option mapper where the instructions match. The inline mappings that produce different instructions remain in their native callers. The TCP receive queue declarations and slot and modem layout checks are shared.

The review, cumulative source at `03a9b49eb9` and working fork each compiled and compared 49 affected objects. Allocated code and data, symbol locations and relocations match after mapping the six renamed symbols. All 294 fork tests and the linker retention check passed.

## Renderer and BML resource reviews

The first branch starts from upstream master `c572111ed6`. Each later branch builds on the one immediately above it. The last column counts paths changed by that step. Review the two accessor and Dark Falz commits together to follow the archive entry into the game code that uses it. The resource lifecycle commit then carries the constructor and destructor through the callers. All four review trees and their four counterparts on the combined local source branch passed the retail executable and upstream checks.

| Subject | Local branch | Commit | Paths in step |
| --- | --- | --- | ---: |
| Pass the current texture list to the renderer and its callers | `great-merge/current/texture-binding` | `1c3fb51ca6` | 353 |
| Recover the typed BML model and texture accessors | `great-merge/current/bml-accessors` | `4ed5af2ee8` | 257 |
| Recover the Dark Falz Zako model and texture lifetime | `great-merge/current/bml-zako` | `3fe1598ae8` | 17 |
| Recover the BML resource constructor, destructor and archive layout | `great-merge/current/bml-resource-lifetime` | `39e6385750` | 230 |

## Model hierarchy, enemy resources and renderer callbacks

`great-merge/current/model-rendering` starts directly from upstream master `c572111ed6`. Its three commits change 120 distinct paths. Review them as a single group. The first identifies the position-capture class used by Pan Arms, Dark Falz and Olga Flow. The second recovers the enemy resources that supply model and animation data, including Berura’s two banks of 17 node matrices. The third follows the model node through callback registration, renderer traversal, and the animation cache. Barba Ray passes the current motion and frame through that cache.

| Commit | Change | Paths in commit |
| --- | --- | ---: |
| `227b920bce` | Recover shared model-node position capture and its render callers | 38 |
| `444549edc9` | Recover enemy model resources, animation tables and detached-part matrices | 20 |
| `c08b78456f` | Pass typed model nodes through renderer callbacks and the animation cache | 78 |

All three standalone commits, their counterparts on the combined source branch, and the fork build passed upstream checks and reproduced retail GPOE8P. Direct execution covered the 64-entry capture limit and repeated node indices, 16 endpoint visibility combinations, 16 recursive matrix-traversal cases, three renderer traversals with callbacks installed and cleared, 24 capture-forwarding cases, six animation samples and four cached draws. The original fork and current sources register the same 37 distinct targets. Their 99 compiled setter branches have the same addresses and enclosing function sizes across 36 original and 36 current source owners.

The [original fork index](2026-11-18-fork-review-index.tsv) records ten complete original file edits and the setter sites on mixed files. The current combined source is `01e8aa6ff7`. The 90 original byte ranges still account for 980 linked source bytes and 167 verified padding bytes.

### Shared material opacity

Commit `6d4d503ab5` extends model rendering with the fork's original `MaterialOpacityFade` class and implementation. Its 47 changed paths include the rename from the Sinow Zoa unit to the rendering owner. The low-level opacity check, rate, color and fade operations have the same class across the Sinow Zoa, Stelth, Epsilon, Morfos and related callers. The symbol table maps the same 17 function and data entries to their original fork names.

The review compiled and compared 60 affected objects. The cumulative branch `825665ae67` and the working fork each compared 62 objects. Allocated code and data, symbol locations and relocation targets match each tree's preceding objects after the renames. All 294 fork tests passed and the linker retention list remains current.

## Audio streaming and item archives

`great-merge/current/audio-streaming` starts directly from upstream master `c572111ed6`. Its three commits change 65 distinct paths. Review the archive and sound work together. ADXF opens, seeks, reads and closes sector-based files for the item, scene, character and sound loaders. The ADXB decoder supplies the signed channel count to its buffer and ring operations. The sound slot passes pitch and slide duration from the technique and weapon callers to the voice pool.

| Commit | Change | Paths in commit |
| --- | --- | ---: |
| `bffabbeb7b` | Recover ADXF sector reads and their archive callers | 31 |
| `7cce238123` | Recover the signed ADXB channel count and streaming callers | 5 |
| `35f924abcd` | Pass pitch and duration through the sound slot and its effect callers | 32 |

Each step reproduced the retail executable and passed the upstream checker independently and on the cumulative source. The working fork reproduced the same executable. Linked execution covered 75 seeks, pending reads, cancellation, 12 archive opens, eight item loader lifecycles, 32 buffer alignments, 70 resource loading cases, every signed channel byte, and 18 pitch-forwarding and nine full voice-pool cases. Two fork-only probes now recognize the upstream names.

The [original fork index](2026-11-18-fork-review-index.tsv) maps all 198 linked branches to these 17 entry points from 54 original source owners to 43 current owners. Their destinations and enclosing function boundaries agree. Eight original source or header edits were reconciled in full. Other edits in mixed files remain open in the index.

## Menu frames, item lists and text clipping

`great-merge/current/window-foundations` groups the existing result-window, guild-card and item-help changes on upstream master `c572111ed6`. Its 128 paths include the page indicator and draw context needed by the next review. `great-merge/current/window-frames` adds 169 paths against that base. It follows the window from its frame and scrolling state through menu closure, item rows and text clipping.

| Commit | Review scope | Paths in commit |
| --- | --- | ---: |
| `593e0b3399` | Recover the shared window frame, layout entries and scroll offsets | 160 |
| `977f5f052e` | Use the shared window close and clipping operations for menus, item rows and text | 18 |

The UI base, both review steps, their cumulative counterparts and the working fork reproduce the retail GPOE8P image and pass the project checks. The 0x60-byte window base owns the entry list, flags, target and displayed geometry. Its 0x70-byte extension adds two content-scale and two scroll coordinates. The item-row renderer reads the same 0x4C-byte context as the menu frame and glyph clipper. Its original vtable slot at 0x804CF9C0 points to 0x80259510. The original code and the current build have the same 154 direct branches to the other fourteen frame and lifecycle entry points, across 87 original and 84 current source owners.

Direct execution covered 63 sparse lists and their destruction order, all 256 low-byte close-flag states, 64 clipping rectangles, 80 frame dispatch cases and 640 item rows. The item-row emulator omits the paired-single spill and reload of FPR31. The adjacent scalar save and restore still execute. Host checks exercised 20,000 rectangles with frame interpolation, scrolling and clipping under address and undefined-behavior sanitizers. The [original fork index](2026-11-18-fork-review-index.tsv) records seven complete file comparisons and the linked branches in mixed files. The following commit recovers the shared entry accessor and its callers.

### Window entry lookup and callers

Commit `625979515a` extends the same window review with 53 paths. The shared layout returns its stored entry pointer. Item lists pass their signed counts explicitly. Guild-card selection, menu rows, status displays and the four symbol-chat entry banks consume the pointer. The source no longer declares the same lookup separately in 28 translation units.

Original fork and combined source `3e348a15d4` have 446 branches to the same lookup address and identical enclosing function boundaries. These branches connect 64 original source files to 59 current files. The original, review, combined and working-fork executables passed 56 sparse lookups, 100 symbol-chat lookups, 36 bounds cases, 16 selected IDs, 64 card updates and 72 insertions each. The three local builds passed the upstream checks, reproduced the retail image and passed 640 item-row rendering cases each. The working fork also passed all 294 fork tests.

### Main-menu entries and navigation

Commit `37e0caf80a` extends the existing window review with the fork's typed row and slot arrays, lifecycle and navigation methods. The outer menu controller uses its typed child window for population, selection and submenu updates. Frame drawing and texture binding use the current native window helpers. The two arrays begin at 0x64 and 0x124. The controller's factory has the same implementation as fork main after translating its include paths.

The review, the cumulative source at `3661bc5e1b` and the working fork each compiled and compared 17 affected objects. Their allocated code and data sections, symbol locations and relocation targets match the preceding objects after accounting for 29 renamed symbols. The working fork passed all 294 tests and the retention check.

## Actor animation tables and motion resources

`great-merge/current/actor-animation` starts directly from upstream master `c572111ed6`. Commit `238612cb27` connects the shared action and motion setters to the enemy, boss, player, object and Photon Blast callers in 71 files. The actor stores a TObjMotionAction pointer at 0xD8 and a BmlMotionEntry pointer at 0xDC. Archive callers use the motion list at 0x430.

The original and the combined source at `d33f5a172d` have 69 branches to the action-table setter and 47 to the motion-list setter. All 116 retain the same call addresses, destinations and enclosing function bounds across 69 original and 69 current source files. On the original, review, combined and fork builds, eight isolated setter cases verified both pointers and adjacent memory. In 64 animation setup cases per build, both pointers were in place when the requested action reached the animation selector. The three local trees passed the upstream checker and reproduced retail GPOE8P. All 294 fork tests passed.

### NPC model registration and animation records

Commit `8e9c7309f9` adds 62 paths to the same actor animation review. The fork's NPC slot, binding and registry headers are retained verbatim. Upstream's consolidated NPC translation unit keeps ownership of registration. The slot reset and binding assignment use their original typed methods. Callers that share the animation record layout use the common type with named default, conversation and debug fields.

The branch, the cumulative source at `292b7e793c` and the working fork each compiled 667 affected translation units. Allocated sections, symbols and relocation targets agree with their prior objects after mapping the three renamed symbols. This check includes NPC data records and uses each tree's prior objects as its baseline. All 294 fork tests passed.

### Actor motion and parameter data names

Commit `b363e57965` carries 38 names from fork commit `ff61f623a6` for the Gee, Gi Gue, Morfos, Shark, Berura, Stelth, Gryphon and Olga Flow data. The names still identify the same records on fork main. The corresponding addresses, section, linkage metadata, storage and references stay consistent across the review and combined source. Ten affected translation units per build preserve their allocated code and data sections and relocation targets after resolving the renamed symbols. The fork retention check and 294 fork tests passed. The cumulative source commit is `34b52ae04b`.

### Special-event items and snapshot-window lifetime

The existing player-techniques review now includes commit `c950b4cfd0`, which carries the fork's inferred `TItemSpecialEvent` class name into upstream's consolidated use-effect unit, factory table and build entries. The item owner remains at 0xF0. The established use-effect methods and compiler profile stay with the consolidated unit.

Commit `fb6e85d03f` extends the existing window review. The options menu creates a `TWindowSnapShot`, the class implements its virtual renderer, and both use the current window entry and draw-context fields. Player-motion RLC loading remains in its current owner.

All affected translation units compiled on both review bases and on the cumulative and working branches. Comparing the combined objects found identical allocated sections and relocation targets after mapping the renamed symbols. All 294 fork tests passed on the combined overlay. Cumulative source is `81349deed2`.

## World-object and seasonal resource names

Commit `6f03218555` names 109 model, archive, texture and diagnostic references already present in the current source. Three nearby debris parameter records take their fork names in the same patch. The six source owners cover the Ancient, Jungle, Forest and Seabed containers, Ancient wreck resources, the Forest warp and the seasonal lobby.

The comparison pinned each of the 112 names to its original read-only offset and size. Allocated code and data, the other symbol entries and relocation targets match in the six objects on each of the review, cumulative source at `457411adb3` and working fork. The fork passed all 294 tests and its linker retention check.

Commit `c72bbfbf33` extends the world-object review with the shared wreck resource handles, collision entries and debris tables. The wreck spawner uses the existing `TObjChipParams` type. Forest warp models and textures use pointers through the resource getters and the four warp classes. The native warp table owner shares the read-only destination and screen positions and the quest flags with their callers.

The review, cumulative source at `5f25ff5c5b` and working fork compiled and compared 14 affected objects each. Allocated bytes and relocation targets match. The two debris tables gain the external binding used by the fork at the same offsets and sizes. All 294 fork tests and its linker retention check passed. The fork's generated retention list records the two shared tables.

Commit `bd65f0d44b` adds the shared Seabed wall and wreck declarations to the same review. The spawner uses the fork's typed 76-byte debris record, and the wall accesses the typed resource pointer and fade member. The review, cumulative source at `db9345607c` and working fork each compiled three affected objects. The previously anonymous data now has the fork's external name at 0x8044311C. Allocated bytes, the other symbols and relocation targets match. All 294 fork tests and the retention check passed.

Commit `118f154267` carries the shared map-collision factory from fork commit `30ed6f3ed6` into the same review. The factory accepts a set-data pointer and returns a `TObjMapCsn` pointer. Jungle doors and rocks, Seabed wrecks, arena objects and the factory tables use the shared interface. The factory and native constructor stay at 0x80194934 and 0x801949FC. All 21 factory table records still target the same entry point. The lab constructor's compatibility call keeps its existing floating-point arguments.

The review rebuilt 22 affected objects. The cumulative source at `64af88f68e` and working fork each rebuilt 23. Allocated sections, addressable symbols and relocations match after mapping the two renamed symbols. The 294 fork tests and the linker retention check passed.

### Lobby-animal resources and animation binding

Upstream `c572111ed6` already source-links the lobby-animal resources and native virtual tables from fork commits `b0c58784d5` and `703fed303b` in its consolidated `src/pso/object/lobby/LobbyPigeonPath.cpp`. The original linker split and fresh compiled objects agree across 1,612 bytes of resource, profile and virtual-table ranges, including their 114 relocations. The comparison includes 40 bytes of zero-filled resource state and one trailing alignment byte. All six virtual tables are at their original offsets. Each of the four builds uses this source owner, and its 10,460 text bytes and text relocations also agree with the original.

Commit `aae96ffd62` adds the remaining typed Seabed dolphin animation binding to the actor-animation review. The combined source at `a64b19131b` uses the named motions field on the native BML resource. The standalone review uses the archive layout and compatibility call available on that branch. Both build the same code and data as their prior objects. The working fork also matches its prior object, and all 294 fork tests and the retention check passed.

## World and camera constant ownership

Fork commit `c7470b0f0e` placed 146 floating-point constants in source. All 608 bytes are already exact at their original addresses in the source objects selected by upstream master `c572111ed6`. The actor and camera review at `5d0802c2e5`, cumulative source at `5f25ff5c5b` and working fork at `433a38f909` select the same 47 owners. The source ownership was checked from the generated linker inputs. Each affected object was rebuilt on all four snapshots. The comparison checked the original split data and the compiled sections, symbol locations and relocation targets. It accounts for every source definition in that fork commit.

The [fork source index](2026-11-18-fork-review-index.tsv) records the addresses and owners for the original 48 source files, including one fragment since folded into its current owner. The [original data inventory](2026-11-18-fork-data-ranges.tsv) tracks its own 90 address ranges.

## Interface, combat, actor and menu constant ownership

The [numeric constant audit](2026-11-19-numeric-constant-audit.tsv) checks 729 definitions from 11 fork commits across 194 historical source files. These cover the original interface, combat, actor and menu pool batches and later camera, angle, Dragon, shop and De Rol Le changes. Fresh builds compared 3,036 bytes with the original split objects at each address. The generated linker inputs identify the selected owner for every value.

Upstream `c572111ed6` emits 712 definitions from 184 compiled objects. The other 17 values are already present at their original addresses in selected upstream objects. The cumulative source at `a5540e955c` and working fork at `073b2523e4` emit all 729 from 188 compiled objects. The 68 bytes below are part of the original [1,147-byte inventory](2026-11-18-fork-data-ranges.tsv). All three standalone review branches were rebuilt for their affected owners.

| Range | Bytes | Standalone review | Selected source owner |
| --- | ---: | --- | --- |
| 0x805D85B8–0x805D85CC | 20 | `raft-encounters 2032c512f9` | TObjBoss2DustCtrl.cpp |
| 0x805D8AE0–0x805D8AE8 | 8 | `boss-effects cb172b2134` | TBoss4Type3_800524E8.cpp |
| 0x805DCE00–0x805DCE10 | 16 | `item-help-status 372fd86847` | TWindowHelpItem_802540AC.cpp |
| 0x805DCF18–0x805DCF30 | 24 | `item-help-status 372fd86847` | TWindowSubStatusDisp_80257BC0.cpp |

## Gyaranzo resources, parameters and missile state

Upstream `c572111ed6` already source-links the Gyaranzo catalog, tuning pool, resource state, parameter records and missile virtual table. The selected source objects match the original 836-byte ranges and all 15 data relocations on upstream, the local review, cumulative source and working fork. The data comparison includes the shared volley timer and the original alignment at the end of the alternate archive string.

Commit `ba84021c8a` adds the fork's typed resource handles, movement and collision records, model index arrays and breakup parameters to the battle-parameters review. The movement and collision records now have their own symbol entries at 0x804941DC and 0x804941F8. The preceding animation action table covers its 128 bytes. The flagged index table retains its trailing zero halfword to cover the original 28-byte extent. The standalone review retains the existing texture-list cast required by its archive declaration. The combined source is `a5540e955c`.

Three affected translation units in each local tree match their prior objects after normalizing the renamed symbols. Allocated sections, addressable symbols and relocation targets all agree. All 294 fork tests and the retention check passed. The fork retention list adds the two newly named records and updates the name of the missile class pointer.

## Working fork on upstream PR 326

`great-merge/current/working-fork` combines the native source through `a5540e955c` with the documentation under `fork/` and runnable fork tooling. The 94 tool paths, 14 host-port paths and one workflow carried by the earlier working fork remain available. The original tool archive is under `fork/tooling/original/`.

All 294 fork tests pass after the window frame and item-list changes, including the shared BML accessor checks and the three Dark Falz Zako fixtures. The rebuilt retail executable passed all 2,415 linked units, the 26,872-entry retention check, eight BML filename-list cases, and 64 model and texture retrieval cases. The [fork source index](2026-11-18-fork-review-index.tsv) records the original edits for nineteen files with 36 matching calls and the separate header and Zako initialization comparisons. The earlier host portability and sanitizer results remain recorded at `b66fafd6e9`. The source-wide audit continues beyond this resource family.

## Whole-tree merge trial

A three-way merge of the full fork at the latest shared ancestor produced 2,571 conflicts, with upstream's native file layout accounting for much of the path churn. Using the fork's original branch point produced 2,371 conflicts. The earlier native integration tree yielded 358 conflicts and 23 clean changes. Clean paths still need ownership validation. For example, some historical window sources add methods the current tree already defines in consolidated units.

## Current source comparison

The current source at `34b52ae04b` retains six additional complete fork edits. One complete file matches after translating the include moves. Five whole patches can be merged in either direction against the original fork point while reproducing the current owners exactly. The six current blobs match those tested by the audit. The [fork source index](2026-11-18-fork-review-index.tsv) records those owners and their blobs. 2,291 rows still require full or partial owner comparison.

## Review queue on the previous master


The maintainer requested that specialized tools stay on the fork. Upstream candidates contain game and library source, headers and the configuration needed to build those sources. Run the upstream repository's own checks on a clean source branch. The working fork supplies its own probes, CI, host harnesses, and build helpers on a separate branch.

| Local branch | Purpose | Verified relationship |
| --- | --- | --- |
| `great-merge/upstream/combined` · `d86ae41c4d` | Combined source matchpasses, including the shared item archive reader, sound-slot pitch and weapon animation | Retail hash and upstream PR checks pass |
| `great-merge/upstream/all-source` · `f69deb8c97` | Complete native source currently recovered on integration | Retail hash and upstream PR checks pass |
| `great-merge/upstream/pending-reviews` · `2ce569b3b1` | Thirteen subsystem drafts and twenty-one follow-up native recoveries on the combined source | Its complete Git tree equals `great-merge/upstream/all-source` |
| `great-merge/pending-reviews` | Alias for the current source-only queue | Same commit as `great-merge/upstream/pending-reviews` |
| `great-merge/fork-tooling` | Runnable fork tools, hosted workflow changes, test harnesses and the fork's build helpers | The active tool files retain their original working paths |
| `great-merge/fork-docs` | Documentation kept for the fork | Its project files outside `fork/` equal upstream |

The [source matchpass register](2026-11-18-source-only-matchpasses.tsv) lists twenty independently tested local branches based on upstream `f76fdd7ff1`. Each reproduced retail and passed the stock upstream checker. The former link-verification proposal is now entirely fork-local. The source portion of the host-portability proposal contains native item and rendering callbacks and SDK declarations. The register preserves the verified components on that previous master. Earlier validation branches below also contain fork tools and serve as historical evidence.

The [pending source index](2026-11-18-upstream-source-groups.tsv) records the original 4,357 edit blocks across 665 path names in thirteen local drafts and the later changes to collision, matrix math, the ADX decoder, positional sound requests, particle factories, enemy targeting, demo playback, ground contacts, memory-card operations, save images, actor orientation, encounter camera calls, Olga Flow afterimages, movie modules, GVM texture archives, heap release and character movement vectors. Each draft contains one subsystem group. The combined result builds. On the merged upstream base, the thirteenth cumulative build passes. The first twelve original intermediate builds exposed dependencies across groups. Their current source index describes the original split.

The fork's enhanced linker checker had produced thousands of retention-list changes. The source-only cumulative build starts from the stock list and updates the affected symbol names. The stock compiler also reproduces the adjacent Dark Falz weighted-selection and material routines in one source unit. Together they emit the two floats at 0x805D8AD8 and 0x805D8ADC naturally. This removes the fork's object-alignment helper from the upstream build. The comparison with fork main found zero lost matched or source-linked function or data ranges. Its total extent decreases by 2,045 bytes, with 2,200 bytes of verified padding leaving coverage and 155 bytes entering coverage.

The four authorized submissions are [#321](https://github.com/zeroz41/pso-decomp/pull/321), [#322](https://github.com/zeroz41/pso-decomp/pull/322), [#323](https://github.com/zeroz41/pso-decomp/pull/323) and [#324](https://github.com/zeroz41/pso-decomp/pull/324). All four merged. The maintainer asked to keep specialized tooling on the fork. The network, renderer and resource-loading reviews were updated in place, passed upstream CI and merged as `800d66a50b`, `1cd8f309f7` and `f76fdd7ff1`. The network update also resolved the PPP linker conflict.

## Review groups on the merged master

Seventeen checked components form the first six larger local branches on upstream `f76fdd7ff1`. Each branch below builds independently, passes the stock PR checks and reproduces the retail executable. The first five cover game subsystems. The sixth holds the smaller native callback and SDK changes. Positional sound, particle factories and demo playback are the seventh, eighth and ninth local review groups. Actor orientation and scripted camera playback form the tenth.

| Review branch | Commit | Paths | Components |
| --- | --- | ---: | --- |
| `great-merge/reviews/resource-lifetimes` | `092d6ab361` | 221 | archive-lifecycle, quest-cache, audio-streams |
| `great-merge/reviews/window-interaction` | `4c814cd01f` | 166 | window-lists, result-windows, guild-card-chat |
| `great-merge/reviews/combat` | `89df16b535` | 205 | battle-parameters, enemy-motion, collision-results, player-techniques |
| `great-merge/reviews/encounter-drawing` | `0c07764c1a` | 115 | radar-camera, raft-encounters, texture-strips, boss-effects |
| `great-merge/reviews/memory` | `04be4b7fc9` | 259 | runtime-array-allocation, memory-moves |
| `great-merge/reviews/native-callbacks` | `d8c3791ade` | 11 | native-callbacks-sdk |
| `great-merge/upstream/positional-sound` | `cc23e836c9` | 259 | one-shot, persistent and area sound with particles |
| `great-merge/upstream/particle-factories` | `4137dcb168` | 188 | particle factories and controller initialization |
| `great-merge/upstream/demo-playback` | `a4bc4be6f8` | 112 | shared demo playback state and game-wide callers |
| `great-merge/upstream/actor-camera-angles` | `23f4e183f5` | 338 | actor orientation and scripted camera playback |

The resource group also names the stream buffer and cue work area at 0x805D62D8 and 0x805D62DC. After moving their associated declarations, callers and linker entries together, the recovered source immediately before these two names and the complete source both passed independently. The former checkpoint is `great-merge/fork-validation/archive-and-memory-callers` at `e6646c0fc3`. The three-file remainder belongs to the resource group.

The resource group passed the ADXF, archive, sound-slot, disc-read and quest-cache checks. The window group passed the guild-card and results-page checks. The combat and encounter groups passed the battle, collision, weapon, camera, trail and strip-animation checks. The memory group passed 96 guarded copy cases. The native callback C++ host checks passed on the fork.

The combat group now reads character flags through MSL's 256-byte table and the
shared letter mask. The SDK group names the angle conversion and declares the two
floats the identity kernel uses. Both groups and both follow-up cumulative builds
passed the stock checker and matched retail. The portable implementations and
their tests are on the fork tooling branch.

## Fork branch point

The last commit on the fork's first-parent history already reachable from upstream is `1f2ecc1887`. The later common ancestor `fba9382235` entered through a side branch. It works for describing Git's comparison view. The earlier commit identifies the source files the fork actually started with.

The original fork tip `3342e42983` has 798 subsequent first-parent commits. Comparing the complete file mode and blob at both ends, and inspecting each first-parent diff including merge results, identifies 1,101 previously unresolved paths that the fork never edited. Their individual blob IDs are in the [review index](2026-11-18-fork-review-index.tsv). Reproduce the history check with `git log --first-parent --diff-merges=first-parent --no-renames --name-only 1f2ecc1887..3342e42983`. Files touched and later reverted were excluded.

Sixteen more complete fork-point patches reproduce their current owner when merged in both directions. Three contain only include-directory or header-guard moves after mapping Git renames. Another sixteen have every fork edit block present with unique surrounding source context. The comparison preserves comments and directives. The block check skips multiline literals and comments and requires the old contextual form to be absent. The index records the current owner in each case.

The audio branch also recovers the signed ADXB channel count and its three stream callers. All 256 possible channel bytes returned their sign-extended values. The query and output-drain loops selected the expected rings for negative, zero, mono and stereo counts. These checks ran on integration, the audio and resource branches and the cumulative native queue. All four builds passed the stock checker and reproduced the retail SHA-1. The review index currently lists 1,842 paths requiring an owner comparison and 502 with partially matched edit blocks.

## One-shot positional sound requests

The original fork recovered a signed request handle and a read-only world position in `35e4af0df0`. The standalone branch `great-merge/upstream/one-shot-sound` at `fcd789803e` applies that interface to current upstream master in 207 files. The cumulative source change at `54bd96bdc6` touches 206. The game uses one shared declaration in every caller. Four callers passed an unused fifth register or temporary on the cumulative branch. Their recovered four-argument calls match the original instructions. The standalone group also handles the former five-argument character-select call and passes its signed handle directly to the pitch routine.

Both original and integrated source-linked images contain 1,198 direct PowerPC branches to `play_sound_effect` at 0x8022675C. Each branch's enclosing function has the same address and size and is an exact source match in both reports. Across 294 current caller files, the source expression count equals the compiled branch count for each file. Eighteen original fork paths contain only the historical sound edit. The ledger records 35 call-site addresses for those paths and partial evidence for 1,111 calls across 272 other paths.

The standalone, cumulative and fork builds passed the upstream checker and reproduced retail. The fork-only probe `tools/probes/check_one_shot_sound.py` executes eight cases covering admission, duplicate suppression, allocation failure, position copying and returned handles. It observes the packed request arguments and checks neighboring slots and the caller's vector for writes. It passed on the original fork binary and all three rebuilds. The results-page and weapon-animation probes also passed on all four images.

## Persistent and area sound with particles

The positional sound group at `cc23e836c9` has three commits on upstream `f76fdd7ff1`. Its first commit remains available at `great-merge/upstream/one-shot-sound`. The second recovers persistent requests with separate owner and position pointers, the six floor-specific request IDs and the one-shot floor dispatcher's return value. The third restores the two area sound-and-particle routines and the shared particle spawn that takes a position. Enemy callers now pass the position directly to the correct routine.

All 195 direct persistent-sound branches in the original and integrated images have the same source-linked address and enclosing function. Each of the 82 caller files has the expected number of typed calls. Both area sound-and-particle entries have the same nine and ten callers by instruction address. The two calls to the common particle routine are present. The fork-only check `tools/probes/check_persistent_sound.py` exercises slot creation, reuse with a new position, admission failure, allocation failure, owner retention and all four area dispatch routines across 36 floors. The sound ID, returned handle, particle IDs and 30-unit vertical offset are checked on the emitted code.

An independent pass on the current texture list verified 600 original source-linked calls across 348 current caller files. Twenty-seven fork paths contain only those interface changes. Five wreck object files contain only native destructor conversions and removal of raw declarations. Each class has its destructor declared and defined at the current owner and both builds reproduce its address, symbol and size. The review index records partial evidence separately where a path has additional fork changes.

## Particle factories and their callers

The independently buildable branch `great-merge/upstream/particle-factories` at `4137dcb168` recovers the world position and returned controller for both particle factories. The unflagged initializer accepts the same read-only position and returns the initialized controller. Its eight global and area calls and its symbol at 0x800883DC build against the current class. The source index records all 188 review paths.

The original and integrated executables have 369 direct calls to the basic factory across 144 current caller files and 187 to the flagged factory across 46. Every instruction maps to the same original function, and each current source file has the expected number of typed calls. Thirty test cases execute the factories and initializers on the original image and the three rebuilt images. They cover the first and last global and area IDs, the first invalid ID, allocation failures, flag truncation, task selection, position copying and bounds of controller writes. All three builds reproduce the retail executable and pass the upstream checks.

A separate history comparison found 31 source paths whose entire sequence of fork edits had already landed on upstream master. The source index records the corresponding fork and upstream commits for each path. Every pair has identical before and after contents and file modes at that path.

## Enemy player target selection

The enemy-motion component at `13468aa162` and the larger combat group at `6516431b23` recover the collector and its five source owners. The shared player record has a 16-bit ID, two padding bytes and a horizontal squared distance. Canadin now forwards its range argument explicitly, including the observed 22,500 limit. Shinowa receives the number of filled records from the member function before indexing the shared table. All six compiled calls to the collector occur at the same original instruction addresses.

The component, combat, cumulative source and integration builds passed the upstream checks and reproduced retail. Nineteen cases on each build and the original image check live players, strict range boundaries, ties, horizontal distances, out-of-range and inactive players, the returned count, table bounds, padding and Canadin's forwarded floating-point argument. The fork-only test skips four Gekko paired-single register spill instructions unsupported by the emulator. The scalar save and restore instructions still execute.

## Shared enemy movement and target state

The two local changes in the combat group at `18e3816c9c` restore six movement fields on TObjEneDD and nine target fields on TObjEneDD_ST. The original fork and the new headers compile to the same offsets and storage widths for all fifteen fields. The base classes occupy 0x38C and 0x3C0 bytes. Across 28 concrete classes the sizes and the offsets and widths of 836 identified subclass members following the shared state agree with the preceding integration build.

The target policy at 0x800B9578 belongs to TObjEneDD_ST. The compiled game has 30 direct calls to this method and 28 to the retained-target validator at 0x800B95E0. All call addresses and enclosing function sizes match the original fork. The enemy-motion component, combat group, cumulative native source and integration each passed the stock checker and reproduced retail after both changes. On all four final builds and the original image, 34 guarded cases exercised movement counters, target lookup, validation and neighboring object memory. The nineteen existing player-candidate cases also passed on each image.

## Demo playback

The game-wide check at 0x80080750 reads the enabled byte and the signed camera controller index. It accepts an enabled demo unless the index is 2 or 4. Players, enemies, bosses, particle effects and map objects use the same no-argument declaration. All 171 calls appear at their original instruction addresses. The 114 fork source files containing those calls now correspond to 108 files after upstream consolidation.

The source-only review, the cumulative game source and integration passed the stock checker and reproduced retail. The private demo-mode probe exercised 90 combinations on each build and the original fork, including signed index boundaries, high flag bits, two incoming register values and guards around the camera state.

## Ground contacts and grounded effects

The collision component `f71b7189b4` and combat group `89df16b535` recover the shared downward query, the two position projection helpers and the two grounded particle effects. The query returns the existing contact pool. The helpers take vectors, and both grounded effects pass a full local position to the particle emitter. The original instruction addresses and enclosing function sizes agree for all 36 downward queries, eight projection calls and 15 effect calls. Delbiter reads its two secondary points at contact indices 2 and 3.

All four native builds reproduced retail and passed upstream's checks. The fork probe ran 39 cases on each and on the original game. It covered misses before and after triangle testing, unsigned mask forwarding, source and output aliasing, the optional normal output and the two particle IDs and their lifetimes. The original startup, contact-pool and radial-wall cases passed on the same images.

## Memory-card and save windows already upstream

Upstream commit `ddca6f4122` contains the exact final fork files for the main lobby frame, multiplayer save screen and memory-card format sequence. Later upstream changes moved or folded these files. Comparing the recovered call sites in the fork, upstream master and integration confirms both lobby slot probes, 14 multiplayer save calls and ten format-sequence calls. These include message text, window closing, menu choice, confirmation, cancellation and the integer card slot. The review index records their original instruction addresses.

## Memory-card operations

The quest-cache component `bec454312f` and resource group `6aeb7aec0c` recover the card channel, deletion filename, eight-byte serial number and detach callback arguments. The game uses the SDK declarations for its card file and status structures. Character selection, quest checks and boss snapshot calls now pass the explicit arguments.

The component, review group, cumulative source and integration each reproduce the retail executable and pass the upstream checks. Runtime checks on those four images and retail exercised both channels, invalid channels, ten SDK status codes, free-space conversion, filename forwarding and guarded serial-number output.

## Memory-card save images

The quest component `f438bf695d` and resource group `0dbe815f53` share the 0x60-byte descriptor used to write character, guild-card, system, quest and snapshot saves and parse quest, snapshot and signboard files. The 0x2048-byte on-card header carries the game title, comment, banner, icon, payload length and header CRC. All eight writer calls, six reader calls and eight artwork selections retain their original branch locations and enclosing function sizes. The quest download state machine uses the writer's returned block count.

Four builds passed the upstream checks and reproduced retail. The fork-only probe and the retail game agree on all six artwork slots, 15 generated images at five payload sizes and 30 successful or corrupt header reads per build. The probe computes CRC independently, compares the full header and payload, verifies buffer guards and checks that failure preserves the caller's descriptor. A separate 72-case check verified open/create behavior per build.

## Actor orientation and scripted camera playback

The independent review begins with the scripted camera class and its motion banks at `90543935ed`. Its second commit, `a1776fbb96`, recovers the actor's pitch, yaw and roll at 0x5C and the two shared actor methods previously attributed to Dark Falz. The compiler identified uses of the removed actor members in player, enemy, boss, NPC, effect and stage code. Independent fields on weapon models, map collision records and other objects retain their own owners.

Both review commits, the cumulative source and integration passed the upstream checks and reproduced the original game. The fork probe checked the previous-position copy, angle address, guarded camera pose writes, projection caching, selection by floor, bank and motion index, and frame stepping, looping and stopping. It passed on retail and the three complete builds. The third review commit `edea475228` applies the shared declarations to all 20 camera pose calls and all ten playback queries. It recovers named camera positions for the Dark Falz and Olga Flow encounters and stores fixed camera poses as vectors and angles. The 29 calls forwarding playback and the four angle and nine previous-position calls retain every original branch target and enclosing function size. The three updated builds passed and reproduced retail. Comparison with the original fork found zero function, data-match or non-padding coverage regressions; 2,200 bytes of alignment padding left coverage and 155 bytes entered, for the previously recorded change of 2,045 bytes.

The fork review index records the lines for 231 additional orientation edits across 101 partially reviewed files. Each full edit was located in its original fork source, in the actual before-and-after patch at the native owner, and in integration at `37b468f137`. These files still have other fork changes to compare.

## Olga Flow afterimages

The boss-effects component `b85422c3e0` and encounter review `0c07764c1a` now use the afterimage owner for both Olga Flow forms and the death sequence. A frame records activity and an array of colored 3D points. Each consecutive pair of active frames emits a quad per segment. The first and last edges of each uninterrupted run fade to transparent. Character selection, the status window, the ruler, Rico's ring and the signboard share the recovered color and triangle-fan calls.

All four builds reproduced retail and passed the upstream checks. The original and compiled objects agree on the four factory calls, three point-update calls, 20 color-copy calls and four fan calls. The fork executable check covered minimum dimensions, the seven-point fifteen-frame history, demo pause, disconnected runs, corner order and alpha, release order and each textured and untextured fan setup. The original fork comparison lost zero matched functions, data matches or non-padding coverage.

## Movie REL loading

The archive component `744904740b` and resource review `49fadc5d24` follow the movie module from the filename read to the image and optional BSS allocations, SDK linking, prolog, epilog and release. TMovie owns the descriptor at offset 0x1C. The image accessor's eight bytes at 0x803204B0 now compile with the resource functions immediately before it.

The four builds reproduced retail and passed the project checks. Runtime comparisons on those images and retail exercised missing files, failed allocations, modules with and without BSS, startup and cleanup callback order, null handles, and all three signs of the descriptor deletion flag. Across the component, review and cumulative builds, the input and compiled object retain both calls to the accessor and the original movie load and destruction calls.

## GVM texture archives

The archive component `5cc35436e8` and resource review `092d6ab361` follow the filename into the temporary disc buffer, directory parser and Ginja texture list. The same entries carry the name, attributes and archive global index or live texture pointer. The lookup accepts a nullable list, which preserves the original missing-list return. The tank, jungle grass, seabed trap and localized alphabet use the pointer directly.

The 153 file loads, 13 archive loads, ten name lookups and three header or byte-reader calls have their original branch addresses and enclosing function sizes. All four local builds passed the project checks and reproduced retail. Executable checks covered both sides of the 256 KiB buffer threshold, empty directories, all sixteen low directory flag combinations, alternate global indices, reversed image ordering, name lookup and invalid archive headers. The fork-to-integration comparison lost zero matched functions, matched data or non-padding coverage.

## Heap release and archive pointers

The memory component `4b7aba01b4` and review `04be4b7fc9` recover the pointer passed to the common heap release. Scalar operator new now forwards its size to the allocator, and the item data-file wrapper has the same void release contract. The 192 original calls to the null-checking release and both calls to the file wrapper retain their branch addresses and enclosing function sizes.

All four builds passed the project checks and matched retail. The executable checks verified null and non-null cleanup, pointer identity, guard bytes and scalar allocation. The fork's 70 resource-read cases and GVM directory and release checks passed on the integration build. The source comparison also traced 393 BML model lookups and 209 texture-list lookups back to the original fork. The four verified pointer interfaces account for 331 cast changes across 167 original source paths, including every fork-point edit in five of them.

## Character positions and movement velocity

The actor review `23f4e183f5` restores the character base class's position initialization and body-center copy. The two shared vectors start at offsets 0x2FC and 0x308. The 66 initialization calls and 33 center-copy calls retain the same branch addresses and enclosing function sizes. The original executable and each of the three native builds passed a guarded check of the order, sources and destinations of all four transfers. Each build matched the retail executable and passed the project checker.

The fork comparison verified 106 additional original edit blocks across 74 paths, completing seven of those paths. A separate whole-file comparison verified the shared position initializer after mapping its upstream include path.

## Buildable boundaries in the remaining drafts

The original thirteen-way split crosses changes to shared interfaces. The local branch `great-merge/fork-validation/before-window-layouts` at `13f3dd6b54` groups the archive, texture and memory interfaces with the code that calls them. It defers the window layout fields until their corresponding classes and consumers change. On its verified base, `great-merge/fork-validation/window-layouts` at `c703356789` reaches the complete native snapshot at `eae28ce0b6`. The later native recoveries are recorded in the current queue above. The remaining difference at this boundary covers 196 paths, including 169 UI sources and headers. Both stages reproduce retail and pass the upstream PR checks. The comparisons from combined source to the first stage and from there to the complete source lose zero exact or source-linked function and data ranges.

The 514-path archive and caller stage is a local build checkpoint. It still needs smaller related review groups. The two commits preserve a working base while that split is refined.

Five changes within the checkpoint now build on the combined source and
memory changes (`5c12a4b1cf`). These are stacked local review candidates.

| Local branch | Commit | Paths changed from parent | Review scope |
| --- | --- | ---: | --- |
| `great-merge/fork-validation/current-texture-list` | `90e77d43ef` | 353 | Pass the current texture list to the renderer from each game caller. |
| `great-merge/fork-validation/bml-accessors` | `2085b37b6b` | 258 | Use one typed BML model and texture accessor declaration across archive loads and their game callers. |
| `great-merge/fork-validation/bml-lifecycle` | `ae0c1877fc` | 228 | Construct and destroy each model archive through its native C++ owner, including every loader and teardown caller. |
| `great-merge/fork-validation/model-node-capture` | `c9c246ddfd` | 38 | Install and clear model-node capture during rendering and write captured positions for boss and enemy effects. |
| `great-merge/fork-validation/enemy-model-resources` | `5028bc4339` | 44 | Recover enemy model and animation resources, detached-part state, and the shared floor-area sound calls. Includes the eight Canadin and Morfos parameter tables their loaders use. |

All five pass upstream's build and regression checks and reproduce the retail DOL.
The BML accessor stage also passes the fork tests for declarations, consumers, and
table layout. Executing the built renderer setter verified its return value and
the single context slot it writes for both null and non-null lists. Five archive
entries returned their own model and texture pointers. The model-node code passed
empty, null and 63–65-entry table cases, registered the correct callback, and wrote
two distinct outputs for a repeated node index.

Path counts overlap because many game objects load, render, and destroy the same
model. Comparing the fifth stage with the earlier pre-window checkpoint leaves
154 changed paths. The window-layout group follows that checkpoint.


The source ledger reconciles 25 original fork headers that declared a constructor
or destructor through a raw C entry point. Each native class header declares the
corresponding lifetime operation. Its implementation matches the original address
and size in both source-linked builds. The small-lobby font header accounts for
28 further C declarations with matching return types, argument types, linkage
and native definitions. These headers add no files to the upstream review groups.

## Item model and texture archive reads

The model and texture loaders share a five-word reader. Their concrete objects span 0x40 and 0x28 bytes respectively. The native constructors pass the AFS filename, partition, and file count to the common initializer. Reads forward the handle, sector count, and destination to the alignment-checked ADXF function. The interface now serves the GSL, scene and sound-bank callers too. The local audio and archive group at `50a99fbc96` contains 82 changed paths against the merged master.

All seventeen individual source groups, the combined source, complete native source and integration reproduced the retail SHA-1. The stock PR checks passed. The fork-only probes exercised 12 AFS open cases, eight model and texture lifecycles, every destination alignment modulo 32, the existing 70 resource-reader cases and the existing ADXF suite. All 294 fork tests passed. The local memory group at `c73a05326b` covers byte and word copying across 32 files. Both overlapping copy directions, zero lengths, disjoint buffers and identical pointers were tested on retail and two builds (96 cases per image).

The fork source ledger reconciles twelve more full-file edits that rename verified storage or spell a retail float as a literal. The comparison checked the complete ancestor and fork tokens, original storage addresses, current names, and source-linked function sizes. One further file changed only its location or whitespace.

## Player combat and weapon animation

The 48-path player-combat review at `136c85e73d` includes the existing distance and Gifoie changes and the shared animation used by Madam's Parasol and Madam's Umbrella. Both canopy models have three scale components at 0x1F8. The idle transition plays the opening sound once when x reaches one. Both weapons apply the scale in draw mode 2. The floating-point and integer helpers at 0x80115B80 and 0x80115BC0 also control other weapon and effect animations. The trail setter at 0x801210B0 updates a pair of signed joint indices on the weapon.

The combined combat review, isolated weapon changes, cumulative reviews, full source and fork integration each passed their native build and PR checks with retail SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Across retail and every rebuilt image the private check in `tools/probes/check_weapon_animation.py` verified 18 clamping cases, 96 animation frames, eight draw modes, 16 construction, destruction and regeneration cases, and five guarded writes to the trail arrays. The existing distance and Gifoie checks passed on the same images.

The [source ledger](2026-11-18-fork-review-index.tsv) also records 35 original weapon factories, 23 destructors and 28 of their headers. Each factory preserved its null-item and allocation-failure paths, original allocation size, parent and item arguments, and constructor address. Each destructor preserved its table write, base destruction and conditional release. Original descriptive table names are recorded at their linked addresses. The review column in the source ledger was refreshed against the actual four submissions and the sixteen current local review branches. It records overlap by path. The source-comparison column gives the evidence for individual fork edits. The same audit found 27 entire single-function source files matching at their current owners and 69 headers consisting entirely of declarations verified against native definitions. It compared return and parameter types, linkage, compiled address and function size. The ledger retains the original prototype spellings.

## Sound pitch and voice slots

The existing audio review at `22ecb2bd0d` now covers 106 paths. The wrapper at 0x80226258 takes a sound slot, pitch and slide duration. It accepts slots 0 through 39 when sound is enabled. The lower-level voice setter at 0x8023F8F4 accepts slots 0 through 31. The merge branch previously called the setter without arguments and relied on the compiler leaving registers untouched. Player, enemy, weapon, technique and UI callers now use a common declaration. The warning sound caller uses the four-argument playback declaration and passes its returned slot to the wrapper.

The audio branch, combined reviews, full native source and fork integration each passed a clean build and their PR checks. Each produced retail SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All 294 fork tests passed. The fork-main comparison found zero lost exact or source-linked function and data ranges. Its net decrease in total data extent remains 2,045 bytes from the reconciled padding and coverage changes. The private check at `tools/probes/check_sound_slot_pitch.py` exercised 18 gate and argument cases and nine guarded full-pool comparisons on retail and all four rebuilt images. It checks positive and negative pitches, wraparound, slot boundaries, disabled sound, and both explicit and default durations.

The original fork header and two complete caller changes are credited in the [source ledger](2026-11-18-fork-review-index.tsv). The same ledger identifies 62 further original headers whose complete declarations, linkage, comments and includes are present at their current owners. For three modified headers the comparison also checked the common ancestor for removals. Other changes in the consolidated sound and technique source files retain their own review entries.

## Collision results

The [source matchpass register](2026-11-18-source-only-matchpasses.tsv) includes `great-merge/upstream/collision-results` at `0385e4c583`. The 32 contacts at 0x804FF9C0 have a 28-byte stride. The line and ground queries share the eight-byte result at 0x80500140. The radial query extends it with the index and penetration depth of the deepest contact. Three native constructors generate the original startup routine at 0x8007A6C8. The player reads the selected contact through the same record type.

The standalone and cumulative native builds pass the upstream checks. The private check in `tools/probes/check_collision_results.py` runs the actual initialization and selection instructions on the original and rebuilt images. It checks the contact pool and both adjacent records, the untouched 0x400-byte group buffer, guards around each constructor's destination, empty and missed rays, ties, signed depths and the last contact slot.

## Fork-only tooling and archival copies

The runnable overlay differs from the full native source in 105 project paths, including 80 tool files. This includes the private collision, sound pitch and weapon animation checks. The [original tooling inventory](2026-11-18-original-fork-tools.tsv) separately accounts for all 96 original fork tool, test and workflow changes outside the documentation. Of those originals, 42 are active byte-for-byte. The archive under `fork/tooling/original/` holds 32 originals whose active versions have changed and 22 originals absent from the active tools. Their Git blob IDs and file modes are recorded independently of the current branch names. Historical utilities use the source layout of fork main `3342e42983`.

## Runtime array allocation and the twenty-group build

The standalone review `great-merge/runtime-array-allocation` at `aa4fb55c76` builds directly on upstream `2ad5dece70`. Start at `TOBoss4Rock.cpp` with array allocation at 0x80147AA8 and conditional release at 0x80147A80. The shared declaration replaces local prototypes across game callers and the runtime's array destructor. Two callers now pass the snapshot size and the keyboard text size explicitly. All 157 files belong to the same two-function interface change. Native code and linked data match the upstream baseline by address. On retail and rebuilt images, 16 allocation cases cover forwarded sizes and returned pointers, and four release cases cover null and non-null storage.

The combined `great-merge/verify-twenty` at `c0550da29f` includes the nineteen earlier groups and this matchpass. It reproduces retail with 27,572 exact functions and 2,529 exact linked units. The upstream PR checks passed. All twelve earlier subsystem checks passed after adapting the battle-table and strip checks to the new operator names. The comparison with fork main found zero lost exact or linked function or data ranges. Its data extent differs by the verified padding and coverage amounts below. Integration at `5604c903e1` uses the reviewed include order in twenty files, eliminating twenty follow-up diffs, and also reproduces retail.

## Rebuilt on upstream master after PR 325

Upstream [PR 325](https://github.com/zeroz41/pso-decomp/pull/325) consolidated game source files and recovered additional data. Both the combined nineteen-review branch `great-merge/verify-nineteen` at `4aaee804a2` and full integration at `2ea980a848` build on that master (`2ad5dece70`). The builds reproduce GPOE8P SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All 27,572 functions and 2,529 source-linked units are exact. Both pass the upstream PR checks with 26,322 required linker entries. Matched data increases by 764 bytes over this master, to 1,747,103. The integration test suite passed all 294 tests.

The native comparison against fork main found zero lost matched or source-linked functions or data ranges on either build. The report flags a 2,045-byte decrease in total data extent. Its address records account for 2,200 bytes of original alignment padding leaving coverage and 155 bytes entering coverage. The [range ledger](2026-11-18-fork-data-ranges.md) tracks the smaller, original 1,147-byte inventory separately.

| Local review rebuilt directly on this master | Files | Commit |
| --- | ---: | --- |
| Radar and shared camera records | 22 | `e26535409b` |
| Quest download cache and name pages | 9 | `169252cbc2` |
| Guild cards and chat windows | 84 | `e2b6da332f` |
| BML archive lifecycle and filename lists | 16 | `cbd518de3f` |

Each of these four local branches independently passed the upstream checks. The guild-card branch includes the earlier chat-window review. The nineteen-group build passed the retail and rebuilt checks for radar, quest downloads, guild cards, archive lists, battle tables, CRI streaming, scene reads, texture strips, encounter trails, result pages and combat techniques. The socket queue checks also passed. Older baseline-specific measurements follow below.

## Review groups closing the data inventory

Four upstream submissions and ten local reviews reproduce retail when combined at `great-merge/verify-fourteen` (`5d66c65409`). The last 72 inventory bytes fit into the following three reviews. The [ledger](2026-11-18-fork-data-ranges.md) records each range.

| Local branch | Review scope | Validation |
| --- | --- | --- |
| `great-merge/window-lists` · `f205cde58d` | 55 files from current master. The area-selection menu extends the existing window-list group. Follow its list entries, construction and dispatch together. | The area selector contributes 24 more inventory bytes. The full branch contributes 344 inventory bytes and 380 linked bytes. |
| `great-merge/boss-effects` · `081015bbac` | 32 files. Follow effect creation and controller lifetime from the Photon Blast shower, Gal Gryphon and Olga Flow sword shot to the Dark Falz material, wave offsets and player mirror. | Independently reproduced retail and linked 40 additional bytes. Four more inventory bytes are original Dark Falz alignment padding. |
| `great-merge/audio-streams` · `0ea1105986` | 38 files beyond the combined master and PR 324 base `e713338046`. Review the CRI file handles and their stream lifecycle, then the area sequencer and fade. Submit after the disc reader lands. | Independently reproduced retail. The CRI pool, AFS directory, 75 seeks, reads, cancellation, error paths and all 70 resource-read cases passed on retail and rebuilt images. The branch adds 12 linked bytes beyond the reader, including the final four music inventory bytes. |

The combined fourteen-group build has 26,228 required linker entries, with zero missing or stale. Socket, battle, stream, resource, texture-strip, result-page, combat and raft-encounter checks passed on the combined build. The full-tree comparison recovered all fork-matched and source-linked address ranges. The fork-wide source review continues below.

## Enemy motion and collision

The local branch `great-merge/enemy-motion` at `b9c637ebce` contains four commits across 16 files on master `b2cac76477`. Read the slime child slots and spawning first, then its six animation methods, Gyaranzo's lifecycle and fade states, and the Merill Lia and Morfos movement and collision tables. The branch preserves the upstream model accessors and allocator. The standalone build reproduced retail with 27,572 functions and 2,538 selected source units exact. These changes recover source structure after the byte inventory is closed.

## Host portability and the sixteen-group build

The local `great-merge/host-portability` branch at `879339cca0` adds the host math, loader transfer, EXI Ethernet, material and item callback checks together with their SDK and game declarations. The 25-file review built independently from master. All five host executables passed normally and under the address and undefined-behavior sanitizers. The console build reproduced retail.

The combined branch `great-merge/verify-sixteen` at `67ce4e8e78` contains the four submissions and twelve local reviews. It reproduces retail, retains 26,233 linker entries with zero stale or missing entries and passes the console behavior and host checks. All 5,542 tracked files in the tested export matched the branch. The sixteen groups gain 792 matched and linked bytes over master, with 27,572 exact functions and 2,539 exact source-linked units. The comparison against fork main found zero lost matched or linked address ranges.

## Camera, quest downloads and guild cards

Three local review branches build directly on upstream revision `b2cac76477`. The chat branch expands the existing chat-window matchpass. The camera and quest branches add two reviews to the sixteen-group series. All three passed a clean GPOE8P build and the project checks. The files used in each build matched the corresponding Git tree.

| Local review | Review scope | Behavior checked on retail and rebuilt images |
| --- | --- | --- |
| `great-merge/radar-camera` · `58917b28bb` | 22 files. Follow the shared 40-byte camera record through the three radar views, the loading screens, enemies, both raft bosses and the map-icon gate. | All ten fields and the adjacent bounds on each view. The gate accepts a marker at distance 300, rejects 301 unless overridden and respects the 128-marker capacity. The emulator omits the paired-single register spill and reload in the gate. The native scalar register save, distance calculation and marker writes run on both images. |
| `great-merge/quest-cache` · `cffec53c5c` | Nine files. Review the slot table, file-page chain and encoded-name index together with the routines that load and rotate the eight name pages. The quest initializer at 0x803E97B0 previously carried the video retrace handler's name. | All 128 slots, ten file pages, 80 bucket heads and 512 free nodes. Failed seek, short read, sorted insertion, page eviction, free-list reuse and selective slot invalidation. |
| `great-merge/guild-card-chat` · `43a2bceb9e` | 84 files on current master. Review the keyboard and composer first, then the eight guild-card records, the selected card and its mail and status-window callers. Supersedes `great-merge/chat-windows` for submission. | Six accessors per card and bounded copies of all 188 bytes in each record. |

`great-merge/verify-eighteen` at `9f57147ed3` combines all eighteen reviews. All 27,572 functions and all 2,539 source-linked units are exact. All 26,233 required linker entries are accounted for. Relative to current master this is a gain of 792 matched and linked data bytes. The comparison with fork main found zero lost matched or linked address ranges. The same checks pass on the complete integration source at `43d3b9a4c3`.

## BML archive layout and filename-list loading

`great-merge/archive-lifecycle` at `69b50d48eb` is a 16-file review directly on upstream revision `b2cac76477`. It recovers the archive's 0x440-byte layout and six loader methods, then follows filename lists through the sky scene and character-creation requests. The existing scalar model and texture accessors remain available to current callers. Eight runtime cases cover empty lists, model-only and motion-only lists, combined lists, synchronous dispatch, all 256 handle slots and allocation extents. The original and rebuilt games passed. The 5,508 tracked files in the build matched the branch.

`great-merge/verify-nineteen` at `3f1999b4d9` includes that review alongside the previous eighteen. The retail checksum, all 27,572 functions, all 2,539 linked units and the linker retention check passed. The complete integration source and BML behavior fixture are at `ccfeb84258`.

## Historical integration groups before the tooling split

The archived `great-merge/fork-validation/pending-with-tooling` starts on the twenty-group build at `c0550da29f`. The [group index](2026-11-18-remaining-integration-groups.tsv) assigns 4,609 remaining edit blocks across 714 path names to 17 local commits. The final source at `70fe7f549f` equals integration `5604c903e1` outside `fork/`. Every review commit excludes the fork documentation.

| Group | Local commit | Paths |
| --- | --- | ---: |
| Archive and renderer interfaces | `10504dd69b` | 40 |
| Enemy model archives and attachments | `9f5506ed2c` | 73 |
| Dark Falz models, textures and effect lifetimes | `89cb376d3d` | 30 |
| Boss models and effect resources | `4a32f93428` | 64 |
| Lobby, NPC and ambient models | `a23cf3b8ee` | 63 |
| Stage scenery and map models | `989d530723` | 44 |
| Doors, switches and trap models | `159a0bce6c` | 67 |
| Player equipment, techniques and effects | `44fa993d9e` | 66 |
| Character creation and menu models | `8fb27c819d` | 46 |
| Window frame and layout | `d945fff3fe` | 70 |
| Chat, lists and option windows | `a13aaab0f0` | 53 |
| Shop, status and battle windows | `a97037d195` | 64 |
| Resource buffers and player motion archives | `48fc44a9ea` | 24 |
| Area sound and disc streaming | `387433f527` | 10 |
| Collision, rendering and compiler checks | `b2296290b0` | 8 |
| Fork build reports and contributor handoffs | `317281de76` | 14 |
| Fork batch integration and validation | `70fe7f549f` | 19 |

This historical grouping included tooling in the proposed rows. The current source-only index above supersedes it. Contributor and batch tools stay on the fork. The earlier review sequence through `great-merge/review-slices` at `55a4d83f3d` also reproduces the integrated source outside `fork/`.

The initial archive-interface partition exposes a return-type conflict in the fish model header when built alone. Package each public signature with its declaration, definition and affected callers. Stage the model loader's internal layout and filename-list lifecycle separately from the return-type migration. For the window reviews, land the frame before the list, shop and battle callers. The individual draft rows still need their own compatible bases and retail checks.

## Local reviews based on the landed front-end matchpass

Upstream master `b2cac76477` is a parent of integration merge `6f2212d865`. That merge keeps the landed window destructors, status gauge, PPP control and quest downloads. At integration `fc96ba681f`, the retail GPOE8P executable matches. All 27,572 functions and all 2,539 selected source units are exact. The merge gained 928 matched and source-linked data bytes over the previous integration build and 792 over upstream. The [data ledger](2026-11-18-fork-data-ranges.md) reconciles the total extent against fork main.

| Local review | Review order | Independent validation |
| --- | --- | --- |
| `great-merge/texture-strips` at `ea1d01d79a` | 35 files. Follow the shared strip collector from Olga Flow and its appearance scene to enemy models, Photon Blasts and city objects. The first commit recovers the constructor and its callers. The second exercises the buffer lifetime. | Tested texture selection through child and sibling nodes, both winding signs, UV scrolling, failed allocation and release on the retail and rebuilt games. |
| `great-merge/result-windows` at `0256acb840` | 53 files. Review text measurement, the challenge result window, its shared page indicator, the battle results music task and finally the duel result window. | Both games passed 180 page and arrow cases, including wraparound, simultaneous directions and a one-page list. |
| `great-merge/player-techniques` at `2db5656989` | 11 files. Trace the player action and enemy thunder data into the combat distance, hit-display and targeting helpers. Then follow the Gifoie orbit task through creation and release. | All 168 newly linked bytes are in the original inventory. Both games passed 10 distance inputs and 36 particle cleanup cases covering all six level bands. |
| `great-merge/raft-encounters` at `f4dd13cbc3` | 26 files. Start with De Rol Le's tunnel state and the dust helix parameters used by both raft fights. Follow the position, strip slot and frame counter through the two dust tasks, the weapon and enemy trail callers, and the GX renderer. | All 64 newly linked bytes are in the inventory. Both slot rings wrapped through 22 selections. The probes checked the positions and colors written for all 20 strips and ten lifetime cases on both games. |

Each local branch was built against master independently. Each reproduced retail with all 27,572 functions and 2,538 linked units exact. All tracked files in the four tested build directories matched their respective Git trees. The four local reviews in the earlier queue below remain prepared on `77a34b3d72`.

## Validation across all twelve groups

The local branch `great-merge/verify-twelve` at `ee4e1655cb` combines the four submitted and eight prepared reviews. For the result windows, preserve the native help and status constructors from the list-window branch while typing their page indicators. For the battle loader, retain the resource reader's return type and the battle bank's size and offset checks. Regenerating linker retention from the combined objects yields 26,217 names, with zero stale or missing entries. This branch is a validation build for the series.

The combined build matches retail. Against `b2cac76477` it adds 716 matched and source-linked data bytes, including 676 in the starting inventory. The standalone texture, results, combat and raft probes all passed on this build. The resource and battle probes also passed 70 file-read cases, 384 table lookups and 32 difficulty-bank loads. The remaining 72 inventory bytes have owners in the [range ledger](2026-11-18-fork-data-ranges.md).

## How to split the remaining integration edits

The [integration path index](2026-11-18-integration-review-paths.tsv) covers all 1,048 changed path names outside `fork/` between master `b2cac76477` and integration `fc96ba681f`. It counts the old and new sides of a move separately. For 249 paths a standalone review contains the same final file or deletion. Another 214 paths overlap a review but carry additional or differently adapted changes. The index routes 581 paths by their integration commits. Four shared linker and symbol files need to travel in pieces with the owning changes. Reviewers can look up each source path, its existing review branches and the integration commits that touched it.

The model-resource family alone touches hundreds of callers. Stage the shared archive loader and renderer declarations first, then group the callers by use. The index distinguishes boss encounters, enemy attachments, menus and character selection, equipment and effects, lobby and NPC objects, doors and traps, and stage scenery. Keep the allocation-operator migration separate because it also reaches code that never opens a model archive. The window frame and area selection group follows the native base layout through its consumers. Batch automation and contributor handoffs have a separate review decision. The fork-wide index below also includes source paths not yet reconciled on integration.

## Submissions against upstream master `77a34b3d72`

| Review | Head | Files | Additional linked bytes |
| --- | --- | ---: | ---: |
| [Front-end scenes, PR 321](https://github.com/zeroz41/pso-decomp/pull/321) | `56f32a94b8` | 43 | 64 |
| [Network runtime, PR 322](https://github.com/zeroz41/pso-decomp/pull/322) | `717c8c2b1e` | 22 | 8 |
| [Chunk rendering, PR 323](https://github.com/zeroz41/pso-decomp/pull/323) | `35d9fbae56` | 19 | 32 |
| [Scene resources, PR 324](https://github.com/zeroz41/pso-decomp/pull/324) | `ad4b9e3229` | 56 | 32 |

All four passed the upstream CI match gate. Upstream merged PR 321 as `b2cac76477`, with the same Git tree as the tested review head. PRs 322–324 were still open at that checkpoint.

Each PR independently reproduces retail and passes the upstream checks after compiling all source objects. All four merge cleanly together and the combined build gains 136 exact and linked data bytes. Two resource-loading call sites preserve the destructor from [PR 320](https://github.com/zeroz41/pso-decomp/pull/320) alongside the typed filename and read interfaces.

## Local review queue on that master

| Branch | Review sequence | Validation |
| --- | --- | --- |
| `great-merge/window-lists` at `f4aa4b40f9` | Seven commits across 51 files. Follow equipment and item icon lists into the status list, then shop and team lists, settings choices, item help and the status popup. | 356 exact and linked bytes, including 320 inventory bytes, 2,541 exact linked units. |
| `great-merge/chat-windows` at `3d209a850d` | Six commits across 77 files. Follow the speaker to a balloon, the composer through its hardware and software keyboards, and the shared draw context into the current upstream status gauge. | 56 exact and linked bytes, including 52 inventory bytes, 2,541 exact linked units. |
| `great-merge/link-verification` at `760ce5a864` | Check data extents, weak symbols and linker retention against the active objects. Review nine tooling and test files in `718d8ee549`, then the generated configuration. | The standalone branch passed 54 tests and the full game check. The generated list has 26,096 names, with zero stale or missing entries on regeneration. |
| `great-merge/battle-parameters` at `d622bfd399` | Trace the four lookups across 76 enemy, boss and other source units, the 0xF600 file into its 0x3D80 difficulty bank, and the probe that exercises both. Three commits touch 81 files. | Both retail and the standalone branch passed 384 table lookups and 32 full-file loads each. All 2,541 linked units are exact. The branch uses the allocator and disc interface already on master. |

The four submitted reviews and the two local UI branches also passed a combined clean GPOE8P build and upstream checks, recovering 548 exact and linked bytes. The item-help icon coordinates and status-text constants belong with the list windows. The word-select threshold and scale belong with the chat window. Of the 548 bytes, 504 appear in the original inventory. The list windows apply cleanly to the four submitted reviews. The chat branch needs two small adjustments if those branches land first. Combine the adjacent linker entries, and remove the obsolete keyboard constructor and file-loader declarations in `TWindowKeyBoardBase.cpp`. The tested combined tree includes those adjustments. Regenerate the linker-verification branch’s generated list when its landing base changes.

## Fork-wide review index

The [fork change index](2026-11-18-fork-review-index.tsv) routes every one of the **7,495 fork change records** between common ancestor `fba9382235` and fork main `3342e42983`. There are 2,912 renames at Git’s 50% similarity threshold, 2,630 additions, 978 modifications and 975 deletions. Each row records both paths where available, its comparison path, changes made on the fork side, routing evidence and any existing review touching those paths.

The original pass left 805 rows without an owner. The audit used direct callers, declaring headers, common-ancestor file contents, fork commits, modified or deleted declarations and linked address owners. All 805 now have a review destination. For example, the two unlabelled weapon headers lead to the Yasminkov controller, the deleted Gogo-ball marker header leads to the two constructors called by the lobby game, and the dial-prefix validator leads to the dialing screen. The index explicitly calls out the mixed `TLobby.h` declarations for review with their callers.

The source-comparison columns distinguish exact blob matches, whole-source matches after quoted include directories and leading header guards are normalized, and individual edit blocks found at their mapped owners. The whole-source test preserves comments, statements, declarations and macro line boundaries. Header bindings still need checking after path changes. For a changed block the audit requires unique matching new text with neighboring lines in the integration owner and absence of the corresponding old text. Eleven records matched every tested block. Another 319 matched 653 blocks in part. These text checks describe the files at `6e1fdce05d`.

The radar, quest-cache and guild-card header decisions are recorded at their current game owners. The weapon review compared fork definitions, native class declarations, function addresses and exact linked sizes. It identified 53 explicit destructor wrappers, 22 manual factories, 12 constructor bodies and 59 corresponding declaration records whose behavior upstream already expresses through C++ weapon classes. For example, at 0x80121278 the fork writes the vtable, calls the base destructor and conditionally frees the object. The matching upstream implementation is `TUnk_804A07C0::~TUnk_804A07C0()`. At 0x80121318 upstream also constructs that class directly from the same parent and item. The per-path evidence names the class and address for each decision.

The deletion pass covers all 975 original fork deletions. Retain 403 headers that compiler dependencies show are used by live units on both builds, 360 source files with identical exact function addresses and sizes across upstream, integration and fork main, five live data-only owners and two native owners whose functions were regrouped. Another 119 paths are absent from all three trees. Integration already contains 14 further removals. For 71 files the original contents moved elsewhere on the fork. One historical deletion names the path now used for the recovered window base constructor and destructor. The [file ledger](2026-11-18-fork-review-index.tsv) records the evidence on each row. A decision to retain a live upstream file resolves the deletion of that path. Any fork additions that replaced it retain their own review records.

There are still 3,415 source records marked for owner comparison and 318 with partial text matches. These records can carry source-level information even when the full linked game matches.

All 374 changed documentation and evidence paths have a local destination under `fork/`. Three executable evidence models are preserved there as Markdown examples. The repository license and third-party license text have separate provenance entries. Shared source and build changes still require semantic comparison before deciding which fork implementation to retain.

At the symbol level, 6,309 postimage address, section and kind combinations have fork names that changed since the common ancestor. On integration `3cb6af949d`, 4,884 still carry their ancestor names, 961 carry the fork names, 299 carry another name and 165 object starts have no symbol of that kind at that precise address. Differences in aliases and object boundaries need source review.

## Disc streaming and battle parameters on integration

Commit `1ca2b401ad` unifies nine CRI file operations through a 16-entry handle pool used by archive, sound-bank, character and texture callers. The executable checks cover pool exhaustion and reuse, AFS directory access, 75 seeks, reads, cancellation and errors. The resource reader also passed 70 cases. Commit `8619e5caf3` recovers the shared byte and word copy interfaces. Both binaries passed 90 copy and cache-flush cases covering overlapping buffers.

Commits `aa2b4b3bd2` and `510782e359` recover the four enemy battle tables, their 96 records, the four difficulty banks and their enemy and boss callers. The probe at `3cb6af949d` exercised 384 lookups and compared the entire 0x3D80-byte active bank and its guards across 32 mode and difficulty combinations on both executables. All 294 repository tests passed on the integration source export.

## Front-end scenes at the original baseline

`great-merge/frontend-scenes` starts at upstream master `92a266f5eb`. Head `6a32eddbc2` contains five commits across 43 files (+449/−482). Most callers change only how they create the menu line controller. The eight-byte ending checkpoint is included in this branch.

| Commit | Review focus |
| --- | --- |
| `544c351c4f` | The ending fade and wall texture list have shared declarations across their writers and consumers. |
| `3db59f8252` | The ending scene constructor uses the class name from the scene setup unit. |
| `34e3191db7` | The drawing controller owns the relocated resource. Its tasks animate lines, start the next line by key and serve the title and selection screens. Four previously separate source-linked units become one. |
| `69d60d75a2` | The title sprites share their frame table. The menu font loader and upload task agree on the palette pointer type. |
| `6a32eddbc2` | Character selection owns its memory-card callbacks and load state. The adjacent four-byte keyboard channel mask belongs to the input polling unit. |

Against a fresh upstream build, the full GPOE8P check passed. The original DOL SHA-1 is `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All 27,572 functions and 2,538 source-linked units are exact. Matched and linked data both increase by 64 bytes with zero address regressions. Six original inventory ranges contribute 60 bytes. The keyboard mask at 0x805D793C contributes the other four. Applying the exported patch to the pinned upstream tree reproduces the branch tree exactly.

## Network runtime

`great-merge/network-runtime` starts independently at `92a266f5eb`. The seven commits through `440c87295d` cover 22 files (+1,676/−579). Read the TCP queue and callback commits first, then the modem initializer, PPP buffers and broadband adapter helpers. Fork PR 457 is included. Upstream's matching check passes with the original DOL, all 27,572 functions exact, all 2,541 linked units exact and eight newly linked inventory bytes. The exported patch reproduces the review branch exactly. Git merged this branch and the front-end scenes branch cleanly in a tree-only check.

The [socket integration evidence](../../docs/evidence/socket-protocol-runtime.md) records both the exact and bounded builds. The host fixtures check interrupt dispatch over all 65,536 modem status and mask pairs, receive completion and initialization order, and Ethernet frame forwarding. The adapter helpers passed the full 16-bit input sweep normally and under address and undefined-behavior sanitizers.

## Chunk rendering

`great-merge/chunk-rendering` starts independently at `92a266f5eb`. The five commits through `59f81c77c3` cover 19 files (+955/−70). Review the camera scissor interface, the ordinary and weighted vertex transforms, and the polygon dispatcher in that order. The GX default lighting and rotation scale add 32 exact and linked inventory bytes. The branch reproduces the retail executable with all 27,572 functions and 2,541 source-linked units exact.

The scalar transforms passed 800 comparisons against the original instructions. Seven scissor tests passed, including 10,000 bounded states. The polygon dispatch checks passed. Of the six stock compiler profiles tested on the geometry unit, GC/2.0, 2.0p1 and 2.6 reproduced all 27 functions. The three 1.3-series profiles reproduced 26.

The exported patch reproduces the standalone branch tree. The front-end, network and renderer branches also merged cleanly together. A full build and upstream check of the combined tree `dc40c3fc84` passed with all 27,572 functions and 2,538 linked units exact. Matched and linked data each increased by 104 bytes, comprising 100 inventory bytes and the four-byte keyboard polling mask.

## Scene resources

The independent branch `great-merge/scene-resources` starts at upstream master `92a266f5eb`. Its three commits through `15b7a4f233` touch 56 files (+424/−242). Start with the two event names in the area loader at `e7ba26d7e5`. Follow the archive lookup, disc fallback, exact-byte and whole-sector readers into their callers at `4af9a88c8e`. Commit `15b7a4f233` adds a reproducible 70-case test of the linked game code with a simulated device and decoder. The case at 2,049 bytes distinguishes an exact-byte read from a two-sector transfer.

The standalone build gains 32 matched and linked bytes in the event loader. All 27,572 functions and 2,541 linked units are exact. Both the retail executable and the review branch passed all 70 cases. Applying the exported patch to the base recreates the review branch tree. The integration counterparts are `385404c113`, `34cdd1526e` and `3cfb401fdb`. The separate BML ownership and player-motion RLC class changes remain on integration.

All four prepared review branches merge cleanly together. The combined tree `1e8efd9e1d35` reproduces the retail executable and passes upstream's full check with 27,572 exact functions and 2,538 exact linked units. It gains 136 exact and linked data bytes, of which 132 appear in the initial inventory. The other four are the adjacent keyboard polling mask. The combined binary also passed all 70 resource-read cases.

## Shared window frame and item rows

Start the window lifecycle review with the window and menu opening the same draw context at `7f2104b445`. Then review sorting depth, client index and the closing tick on the window base at `9693628876`. Commit `42687a6baf` gives that base the list of layout entries and the window flags. Its status-row callers use the existing item-row type for icons, colors and the two owned strings. Most of the header changes remove copies of fields inherited from the base.

Those three commits recover the shared layout through offset 0x2F and preserve the range ledger. The original GPOE8P executable, all 27,572 functions and all 2,539 linked units matched after each commit. A host check of the production method bodies exercised 321 fade ticks, 21 closing-stretch values, and reverse-order entry destruction with empty slots and a repeated clear. Address, leak and undefined-behavior checks passed. Upstream PR 320 was still open at `f72cca569d` when these changes were checked.

The next two commits finish both inherited layouts. Commit `11799c9505` places the target and displayed rectangles, interpolation counter, draw depth and opening tick on the 0x60-byte window base. Commit `4c42018c19` places the content scale and scrolling offsets on the 0x70-byte extension. Follow the settings window, message window, quest message and speech balloon into the same draw context. The choice list and item menus also use the shared scroll offsets. The two changes passed the retail build and upstream checks. A host check of 20,000 rectangles verified clipping, pivots, scale assignment, scrolling and interpolation at zero through 15 remaining ticks.

Commit `5bd1ce23b0` recovers the 0x64-byte snapshot window constructor, options-menu allocation and virtual renderer. Commit `ae2c172468` moves file loading and directory decoding onto the distinct 0x40-byte RLC reader used for player motion. The latter belongs with scene resources. Its two big-endian readers matched 65,536 test words. A host fixture covered missing names, file-size and read failures, 31-character name truncation, successful loads and repeated cleanup. The final build reproduced the original executable with all 27,572 functions and 2,539 linked units exact. A clean export passed all 294 repository tests.

## Mapping fork sources to current owners

At fork `3342e42983` and integration `ae2c172468`, 6,024 changed or newly present fork paths under `src/` and `include/` survived from the fork-side comparison with the common ancestor. There are 3,303 paths under `src/` and 2,721 under `include/`. A local review export, `build/review/fork-source-paths.tsv`, cross-references each path against the common ancestor, upstream and integration. Name and content comparisons alone leave 1,898 paths without a candidate in the integration tree.

Matching the module, virtual address and size of exact linked functions identifies the integration owners for 26,097 functions across 3,241 of the changed source files. That recovers ownership for 1,309 source files that the filename comparison missed. For 147 fork sources, the functions span multiple integration files. Of the remaining 62 paths under `src/`, 50 own data sections, nine are headers, and three are older indirect-rendering source files. For the 50 data units, 231,052 of 231,068 section bytes overlap exact linked integration sections. The four four-byte gaps fall in the existing padding reconciliation. Both builds assign the starting functions of the three older files, at 0x802A8140, 0x802A9284 and 0x802A9568, to `pso/effect/TEffIndirectCtrl.cpp`. Shared addresses establish compiled behavior. Source-level recovery still needs comparison of types, interfaces and implementations. The original 1,147-byte ledger continues to track data separately.

## Enemy motion, collision and rendering

Two local integration commits recover additional source detail for the player, enemy and effect review family. They preserve the byte inventory.

| Integration commit | What to review |
| --- | --- |
| `b3f0cfce63` | Merill Lia has 14 motion actions at 0x80494570, three movement records at 0x80494650 and three collision bodies at 0x804946A4. The constructor indexes each variant and the model loader updates the collision radii. Morfos assigns its movement record at 0x804EE0C0 and passes its collision body at 0x804EE0DC to model initialization. The linked object sizes are 0xE0, 0x54, 0x84, 0x1C and 0x2C respectively. |
| `3a73dc46ea` | Canadin takes the color from the polygon list of each leader and follower model node. Gi Gue's missile renderer uses the pointer at 0x805D6858 to select a model and motion from the BML archive. The fork called this a barrier count. Olga Flow's attack selector uses two signed-byte pitch pairs at 0x805DE2C8 and 0x805DE2CC. |

The integration build reproduces the original executable after these changes. All 27,572 functions and 2,539 linked units pass the project check. Comparing to the build of fork main `3342e42983` found zero lost matched or linked function or data ranges. These commits still need packaging with the related enemy work.

## Original range allocation at `92a266f5eb`

Use the subsystem and the question a reviewer can answer to set the boundary. Include the owning types, their callers, linker changes and relevant checks in the same PR. Keep independent steps visible as commits. Recent upstream examples covered 33 files and 57 files respectively. [Matchpass 22](https://github.com/zeroz41/pso-decomp/pull/301) and [Matchpass 21](https://github.com/zeroz41/pso-decomp/pull/300).

| Review family | Starting inventory bytes | Scope and dependency |
| --- | ---: | --- |
| Front-end scenes | 60 | Prepared and validated above. |
| Window lifecycles and results | 396 | Group the list, help, choice, keyboard and status windows with their shared window helpers and callers. Include the challenge and duel result screens and their page indicator. Refresh the base after PR 320 lands. |
| Already proposed in PR 320 | 176 | Six window recoveries have an existing upstream review. The constructor prerequisite also belongs there. Check the landed tree before cutting the windows branch. [Upstream PR 320](https://github.com/zeroz41/pso-decomp/pull/320) |
| Player, enemy and effect behavior | 272 | Group player combat pools and enemy or boss lifecycle and effect changes by shared behavior. The Gifoie and Photon Blast recoveries include their task lifetimes. The Photon Blast class-name recovery depends on a compiler alignment change. |
| Chunk rendering | 32 | Prepared and validated above. The default lighting range contributes 24 bytes and the matrix angle scale contributes eight. |
| Scene resources | 32 | Prepared and validated above. The event names and disc/GSL interfaces travel with their callers. The broader BML lifecycle and RLC recovery remain on integration. |
| Network runtime | 8 | Prepared and validated above. The PPP scratch buffers occupy 0x805D7A70–0x805D7A78. |
| Audio | 4 | Carry the area-music fade settings with the music sequencer work. |
| Original alignment padding | 4 | The Dark Falz range includes four verified padding bytes at 0x805D8A2C. |
| Already covered at the upstream baseline or outside its measured deficit | 163 | The ledger records the disposition by address. |
| **Total** | **1,147** | |

The rows account for the inventory. They also identify dependencies for packaging the broader integration branch. Resource interfaces and their game callers can travel together. Standalone build and progress tooling can travel with its fixtures and portability checks. The later review branches still require a current upstream base and independent validation. Refresh the queue as upstream accepts work. Keep the range ledger and LLM notes under `fork/` on the fork.
