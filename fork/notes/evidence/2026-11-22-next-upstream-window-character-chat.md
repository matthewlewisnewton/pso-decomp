# Recover native window, character selection, and chat interfaces

Upstream PR #371 is in draft at `5cd8d9c8e9` from `matthewlewisnewton:recover-native-window-character-chat` to `master` while the typed polygon fields are audited. The local ref `great-merge/review/after-370/window-character-chat` points to the same commit. Its single commit on upstream `d8c0a969d2` covers 377 paths. It reproduces retail with all 27,572 functions exact, 2,417 linked units and all 1,147 original data bytes accounted for. Title, status, and lifetime probes pass. [Upstream PR #371](https://github.com/zeroz41/pso-decomp/pull/371) · [Validation at the published head](2026-11-22-upstream-370-window-symbol-validation.json)

Upstream’s `tools/source_quality.py` at `d8c0a969d2` finds **2,497 fewer findings** across 373 source files, with 3,082 removed and 585 added. Separate ownership diagnostics fall by 101. The first review on this base, `0f8ed70741`, had 39 flagged symbol labels and 41 newly stale retention entries. The revised review has zero in both categories. It changes 247 labels overall, including 79 additional mangled labels for members sharing the recovered class owners. [Upstream benchmark](https://github.com/zeroz41/pso-decomp/blob/d8c0a969d273c9e2cdb1c6c34a1e6aa2be4cc571/tools/source_quality.py) · [Upstream CI workflow](https://github.com/zeroz41/pso-decomp/blob/d8c0a969d273c9e2cdb1c6c34a1e6aa2be4cc571/.github/workflows/ci-comment.yml)

The game’s task-name strings establish `TAdChrSelPlayerGC`, `TWindowFukidasi` and the original spelling `TWindowMenuInfomation`. The other owner names describe roles shown by their construction, layout fields and callers. The review uses the inherited model transforms and window sibling pointers, keeps typed gauge arguments, and declares the transition animation callback as a standalone function. [Earlier build and replay](2026-11-22-upstream-370-replay-validation.json)

The independently validated review is `great-merge/review/after-369/window-character-chat` at `717dfedd37bbe9e207552eba8d4e9d21c90a3ba0` directly above upstream `1698caaa1941302ed6dfc60d886d041bae272e0e`. It changes 358 paths. The retail DOL matches and all 1,147 original data bytes are accounted for. The title, status and lifetime probes pass, and the single commit uses the configured fork identity. Its function-label changes alter receivers, signatures, linkage or the constructor and destructor forms. The upstream quality report flags existing address-derived names among those changes. [Current validation](2026-11-22-upstream-369-window-review-validation.json)

Upstream PR #367 advanced master to `6aee940eca`. The first local review is window, character selection and chat at `1484889e3b` on that revision. It covers 358 paths. The shared memory review will carry the 195 release-related edits removed from this candidate. Three remaining merge conflicts were resolved using the upstream controller and trade field names and the existing model loader’s writable pointer array. [Merged PR #367](https://github.com/zeroz41/pso-decomp/pull/367)

The stock upstream build and the new review reproduce retail. Each accounts for all 1,147 starting data bytes and all 27,572 functions. The 12-byte data coverage difference from the assembled queue before #367 is alignment padding. The first review links 2,417 units and passes the title, status and lifetime probes. [Window review validation](2026-11-22-upstream-367-window-review-validation.json)

The 439-path review `c55003f5b9` on `2ea1c02d4c` includes the native character selection, calendar and item-help layout checks. Its exact build and title and status-window probes pass. The next revision is being replayed onto upstream PR #367. [Assembled queue validation](2026-11-22-upstream-366-assembled-queue-validation.json)

The current review is `great-merge/review/after-366/window-character-chat-expanded` at `7e38bacd3a3be70b715037db837d5366763d4502` on upstream master `2ea1c02d4c0b7fa917ede02beac56fcaf3f4b87e`. It changes 435 paths (+5,208/−5,550). The added title sprite and status-window commit changes 24 paths from the original candidate. The two new linker labels follow the sprite pointer on the camera draw call and the native owner of the existing window-entry flag check. Both commits use the configured fork author and committer. [Title sprite validation](2026-11-22-upstream-366-title-sprites-validation.json) · [Status-window validation](2026-11-22-upstream-366-status-windows-validation.json)

The expanded review builds against the current upstream master, with all 27,572 functions exact, 2,447 units linked, and all 1,147 original data bytes accounted for. The title and status runtime checks pass on the review build. The same patch applies cleanly to the queued actor and enemy heads, yielding trees `0457264fa5` and `2258dff4ab`. Those are merge previews.

| Expanded review evidence | SHA-256 |
| --- | --- |
| Build report | `d370b71003ae765db7ca41fd6c53c6be9b408494eef44fa92686a0291fe63ef6` |
| Coverage check | `832ef098e8b3f702573db769337b29c3df96ff429219225b1fa522c1570eced2` |
| Runtime probes | `f2dd79a267ce6a51dc3e2dbeac238fee376c45569a685663935e2d72a77b5f09` |

The earlier 422-path review at `e5ec2c019bfa452cf0a4f85fc465b41a1176f013` remains the parent of the expanded review. [Earlier review validation](2026-11-22-upstream-366-reconciliation.json)

The local review is `great-merge/review/window-character-chat` at `ebd31cec2b8fcffad5dfb01f5fbdeb54cf6c23a2`, one commit on the published renderer head `927d57da604a6be2583457cac6363ae99556c91b`. It changes 422 source and build-metadata paths, with 5,081 insertions and 5,350 deletions. The branch combines these three checkpoints.

- `dc12657265` [Component validation](2026-11-21-upstream-365-window-and-lobby-choices-validation.json)
- `c958220a90` [Component validation](2026-11-21-upstream-365-frontend-validation.json)
- `54384a64aa` [Component validation](2026-11-21-upstream-365-window-widgets-and-chat-validation.json)

The three-way replay applies cleanly and puts the window changes on the renderer branch. The 19 paths from the separate wall and ground-contact patch account for the entire tree difference from the original stacked UI checkpoint. No fork documentation or tooling enters the review. Both review commits use the configured fork author and committer.

The earlier review's 163 linker-label changes are the exact address and name pairs already present in the three component checks. Of these, 129 keep the same leading function name or constructor/destructor marker. The other 34 include restoring constructors, moving member functions to their native record or window, and giving the old Short Mail lookup a typed record return. The build accounts for all 1,147 historical data bytes across 90 ranges, including 167 bytes of original alignment.

The renderer review landed with the same source tree as the original parent. [Merged renderer review](https://github.com/zeroz41/pso-decomp/pull/366)

| Evidence | SHA-256 |
| --- | --- |
| Build report | `a98c3e0c6643df2f8a2ed07e82da63d79633ea8477acb43cd61e7a23edd14b25` |
| Coverage check | `d246a3b40a763c52f049978135f6ed5dc8f73c0fb98bb22f9a8435cfb94aa2bf` |
| Runtime probes for chat | `f4f09241c4953eb17c72344e07a1adc2401118ff1a417add714c4d1d5b46c803` |
| Runtime probes for frontend | `69ec662465653cc90704b46b5707afc303e556cffb0a49f704d9f098aeabc7cc` |
| Runtime probes for choice-windows | `1e8dd6a82f54813ff0f4d19cf4cfa89c56d92adab7ab20ab152a81c4314aaa32` |
| Runtime probes for window-readouts | `214547f33a5a30b7583f3388283519e896f7b6d126179606d3ce5b287637de9b` |

## Proposed PR description

### Summary

Recover the C++ interfaces shared by front-end scenes, lobby windows, and chat. The patch follows the declarations through the existing callers so their window objects, records, and callbacks agree on types and ownership.

- Window and lobby callers share typed choice entries, yes/no factories, team-window callbacks, and status readouts.
- Character selection and title scenes use typed slot labels, scene transitions, and the shared sprite records and texture list.
- Item and status windows pass native context and position records through the shared icon renderer, and numeric rows use the glyph declarations directly.
- Word Select, Symbol Chat, Short Mail, and Guild Card windows use native constructors and records. The Word Select table keeps its 168-byte extent and original address in a dedicated data unit.

Start with the interfaces in `include/pso/ui/window/TWindowMakeTeam.h`, `include/pso/ui/frontend/TAdSinglePlyChrSelectGC.h`, and `include/pso/ui/chat/ShortMail.h`, then follow the callers. Linker label changes follow native C++ owners, constructors, or typed function declarations.

The live task-name strings establish `TAdChrSelPlayerGC`, `TWindowFukidasi` and `TWindowMenuInfomation`. The title scene, card follower, Word Select mode indicator, and gauge names describe roles established by their constructors and callers. Symbols for members of those classes use the recovered owner in their mangled names.

### Validation

- GPOE8P reproduces retail DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- `tools/check_pr.py` passes against upstream master `d8c0a969d2` with all 27,572 functions exact, 2,417 units linked, and zero code or data coverage losses.
- Upstream’s source-quality benchmark reports 2,497 fewer findings overall, zero flagged symbol names and zero newly stale retention entries.
- Component runtime probes agree with retail for choice selection, status rendering, character slot labels, controller repeat, Word Select, Guild Card accessors, radar data, title sprite and camera routing, and numeric glyph rendering.
