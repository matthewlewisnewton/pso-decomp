# Recover typed texture binding and BML render interfaces

The standalone review is `great-merge/review/renderer-and-bml` at `927d57da604a6be2583457cac6363ae99556c91b`, one commit directly on upstream `b2d2912058829d0f0c9260f6272dc2a303c90110`. Its stable patch ID matches the original rendering replay at `ffc356db09`. The source diff spans 360 paths with 647 insertions and 651 deletions. The review history uses the configured fork author and committer and has no co-author trailers.

Published as upstream PR #366 at the validated head. GitHub shows one commit with the configured fork attribution. [Upstream PR #366](https://github.com/zeroz41/pso-decomp/pull/366)

The standalone build accounts for all 1,147 historical data bytes across 90 ranges. Linked data accounts for 980 bytes and original alignment accounts for 167. The sole linker label change at `0x803DA798` follows the pointer argument to the existing setter.

| Evidence | SHA-256 |
| --- | --- |
| Build report | `a199ca96d421a51ed2a30457fa1616d1d7bb8c933c4212d056cddb24bf96fecf` |
| Coverage check | `c9642cc379caec2d7507c5576f0a974ceaaf5a8fd1844c9564a4df5f3abf39ab` |
| Runtime results | `e1279349b310de5d6ba8e5f3761929a25aa0bff2b1596cf7204b9d8b7b2d5c38` |
| Linked texture call sites | `99a144c2fbd5808c0a963acd6f2511fde0d01e2e40fe0bbcc96b4c71d4158108` |

## Proposed PR description

### Summary

`TObjFish::set_global_param` takes a `GinjaTextureList *` and writes the native render context’s texture field. Render callers pass the list they already hold, including lists borrowed from BML archives and the shared capture target. Code that still stores an address as an integer converts it at the call boundary.

Start the review at `include/pso/object/ambient/TObjFish.h` and `src/pso/unk/text_803DA798.cpp`. The breadth of the diff comes from updating the existing callers together. The Dark Falz changes give the archive getters concrete return types and route the Zako reset through the existing Dark Falz link-state clearer.

### Validation

- GPOE8P builds byte-for-byte against retail DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- `tools/check_pr.py` passes against upstream master with all 27,572 functions exact and all 2,446 source units linked. Function and data coverage are unchanged.
- Runtime checks cover texture rebinding in both render contexts, null lists, the capture-list getter, and the Dark Falz clear call. All 600 original branches to the texture setter are inside exact linked functions.
