# Upstream matchpasses

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

The [fork change index](2026-11-18-fork-review-index.tsv) assigns all 7,495 changed entries between common ancestor `fba9382235` and fork main `3342e42983` to review families. Git pairs 2,912 renames at its 50% similarity threshold. There are also 2,630 additions, 978 modifications and 975 deletions. Each row records the original and fork paths, a comparison path, file-level evidence and reviews touching any of those paths. A path shared with a review may still contain unrelated changes. The index uses source ownership and filenames to route further review. It leaves 805 entries with an unresolved owner.

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
