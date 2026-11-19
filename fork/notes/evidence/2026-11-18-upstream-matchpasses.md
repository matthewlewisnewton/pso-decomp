# Upstream matchpasses

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

## Remaining integration changes by review group

`great-merge/pending-reviews` starts on the nineteen-group build. The [group index](2026-11-18-remaining-integration-groups.tsv) assigns the remaining 5,122 edit blocks across 789 paths to 18 local commits. The final source at `59b5983cc4` equals integration `ccfeb84258` outside `fork/`. None of these review commits carries the fork documentation.

| Group | Local commit | Paths |
| --- | --- | ---: |
| Archive and renderer interfaces | `efc66f0927` | 40 |
| Array allocation and release | `5e5f02b6d7` | 29 |
| Enemy model archives and attachments | `e5dde3d4a0` | 76 |
| Dark Falz models, textures and effect lifetimes | `040a3220d7` | 33 |
| Boss models and effect resources | `1c0bad1e39` | 71 |
| Lobby, NPC and ambient models | `04c52d81e4` | 64 |
| Stage scenery and map models | `90ba13855b` | 43 |
| Doors, switches and trap models | `b01aadc7ae` | 68 |
| Player equipment, techniques and effects | `8534c513e5` | 85 |
| Character creation and menu models | `a18fcd19fe` | 53 |
| Window frame and layout | `7bafff01e5` | 74 |
| Chat, lists and option windows | `45b81b8ea5` | 58 |
| Shop, status and battle windows | `dc0b957a74` | 66 |
| Resource buffers and player motion archives | `a14ad50308` | 25 |
| Area sound and disc streaming | `b1334c2ebb` | 10 |
| Collision, rendering and compiler checks | `eb3c3c8156` | 9 |
| Fork build reports and contributor handoffs | `f42db5a44d` | 14 |
| Fork batch integration and validation | `59b5983cc4` | 19 |

The first sixteen rows are candidates for upstream review. The last two preserve the fork’s contributor and batch tools for a separate disposition. Their implementations remain recoverable in Git. Keep only the documentation as a lasting fork-specific difference when the source branches converge. The earlier review sequence through `great-merge/review-slices` at `55a4d83f3d` also reproduces the integrated source outside `fork/`.

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

There are still 3,737 records marked for owner comparison and 786 fork deletions requiring review, in addition to partially matched records. A split fork file can contain several native owners. Review its remaining functions individually before crediting the whole file.

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
