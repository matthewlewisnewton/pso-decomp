# Upstream matchpasses

## Current review queue on upstream master `6e09dda9c5`

The eleven standalone reviews and the combined source stack have been replayed on `6e09dda9c5`. The upstream-shaped stack at `4c56068484` includes the chat balloon, typed bone rotation, native rope simulation, NPC resources, typed quest records, challenge retry objects, player technique casts, dragon attack ownership and the shared boss action packets and typed enemy archive loading, the BML model and motion callbacks, and the Photon Blast sequence and attachments, typed character initialization, typed technique effects, the named technique resource data, native needle contact dispatch, and the Canadin and Sinow interfaces, including native Canadin formation and action handling, Gi Gue attacks, Morfos behavior, shared encounter callbacks, Pan Arms coordination, and Gibbles and Gyaranzo combat ownership, Gibbles construction and teardown, the Ginja draw and material interfaces, the Bal Claw and Berura combat states, the shared enemy experience and item-drop methods, and the typed inventory methods, record export and sorting. The all-source snapshot is `18189e9459`. The preceding heads are preserved under `great-merge/snapshots/3f35d99bb1/`.

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
