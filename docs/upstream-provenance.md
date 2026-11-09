# Upstream provenance

## 2026-11-09 carrier through #228

The [#207 carrier audit](evidence/upstream-catchup-207.md) records the ancestry fold
through `00cda35c8f04b9089a26b46a5cc2df017f669198`, the three units actually ported,
the inherited exceptions and the substantive upstream changes still deferred. The
fold keeps the fork tree before the selected code port; ancestry is not a claim that
all upstream source changes were applied. The entries below describe earlier work.

Which original upstream commits each fork mirror PR carries, and how they were brought in.
Checked against the live PR bodies on `matthewlewisnewton/pso-decomp` on 2026-11-04, plus `PROVENANCE:` lines workers left in the pilot logs.
A row is **pending** when that body does not yet name the original SHAs or the merge method.

Upstream is `zeroz41/pso-decomp` `master`. Upstream squash-merged #167–#191, so the commits on `master` are not the original PR commits. The shared merge-base of this fork with those PR heads is `c5e453d76`.

Methods:

- **direct merge** — `git merge` of `pull/N/head`, original SHAs kept
- **cherry-pick side branch** — only that PR's own commits, `git cherry-pick -x` onto `c5e453d76`, then a normal merge (often `-s ours` so the fork tree stays)
- **squash fallback** — the squash commit on upstream `master`, when the PR head is gone
- **not possible** — stated reason; nothing merged

## This branch

| Fork PR | Upstream | How | Commits |
|---|---|---|---|
| #309 | #180 | cherry-pick side branch | `d022ec60385499322e480eccfa96d5876aba0c42` cherry-picked as `2173f1076`, merged `-s ours` as `d7b825df3`. That commit is the QuestCol fold (and 13 other folds this tree does not take). PR head `4c46d4a9c` was not merged: 83 commits from `c5e453d76`, including #167–#179 and `orig_asm`. Squash `9575dbb7c` was not merged. |
| #310 | #189 | cherry-pick side branch | `943ce88c2c85a432c9bbae979b9aaa7f68b70892` cherry-picked as `86ddf4bf4`, merged `-s ours` as `e8e3ba21b`. Door, quest-list, and hunter-guild folds in that commit are history only. The other twelve lane-8 commits are on #303. Squash `f4200fcb0` was not merged. |

#190 was not opened from this branch. #311 and #250 carry that lane.

## Other fork PRs

| Fork PR | Upstream | How | Commits |
|---|---|---|---|
| #281 | #178 | cherry-pick side branch | `9048ffaba` cherry-picked as `b69da920c`, merged `7275b50e8`. Direct merge skipped: the head also contains #167–#171. |
| #284 | #172 | pending | Body cites the upstream squash `d5ab5a472`. No original-commit merge is stated. |
| #285 | #174 | pending | Body says the upstream commit was cherry-picked with `-x` onto the #172 mirror, and that an asm block was inserted. Squash `b9b9437b4`. Original SHA not restated. |
| #282 | #184 | pending | Body says cherry-picked with `-x` onto `main`. Squash `619a6ca98`. Original SHA not restated. Superseded by #298. |
| #286 | #177 | pending | Closed. Body says cherry-picked with `-x`. Squash `9ab78a2a9`. Original SHA not restated. Superseded by #299 (duplicate ctor). |
| #289 | #180, #183 | pending | Body cites squashes `9575dbb7c` and `61f965ad7`. |
| #290 | #185 | pending | Body cites `123215bfb`. |
| #291 | #180 | pending | Body cites squash `9575dbb7c`. |
| #294 | #180 | pending | Body cites squash `9575dbb7c`. |
| #296 | #180 | pending | Body cites squash `9575dbb7c`. |
| #298 | #183, #184 | pending | Body cites `61f965ad7` and `619a6ca98`. |
| #299 | #183 | pending | Body cites `61f965ad7` (also #177 and #165). #188's `TBoss7TentacleNeedle` rewrite is called out on #312 and is not confirmed here. |
| #240 | `ddca6f412`, #185 via #290 | not a git merge of the upstream commit | Adaptation of `ddca6f412205abd69aaf86d1378f95d23152d6f4` from checkpoint `ee0c46d61636f6dc313ebdb512484de3b79beccf`. #185 arrives by merging #290. |
| #250 | #190 | not a git merge | Manual fold of `0x802C50EC`–`0x802C6DD4` from `38884a337` and `675829442`. Cherry-pick of `38884a337` conflicts with the current sources; the #190 head is 40 unrelated commits. |
| #300 | #187 | cherry-pick side branch | `72fb1a6f9` cherry-picked as `202b4a358`, merged `e4ac3b14c`. Direct merge skipped (#167–#185). Squash `7008688d3` was not the method. |
| #302 | #191 | cherry-pick side branch | `fda7a764d`, `d4e9fa62d`, `7d291db74`. Direct merge of head `7d291db74` would also bring #167–#190. Squash `e175bcd9f` was not the method. |
| #303 | #189 | cherry-pick side branch | Thirteen commits not on upstream `master`, merged `450d762ae`: `935a6b824`, `c0ffd3c6e`, `52030419e`, `bdedf7396`, `d2af7c540`, `e83869f99`, `0874cd550`, `d7480346a`, `6aeeefead`, `c96b43cb1`, `778baf85f`, `d56f15fe6`, `943ce88c2`. Squash `f4200fcb0` was not merged. |
| #304 | #164 | direct merge of PR head | `78cea72b6`. Squash `467fd255c` was not the method. |
| #305 | #171 | cherry-pick side branch | `1bfb8886e`, `bfaac327c`, `150c7d05a`, `bd1e5fe80`, `7bb7210cf`, `ecdff56ff`, `df466322d`, `53934c6aa`, merged `ec832725c`. Direct merge of `53934c6aa` would also bring #167 and #168. |
| #306 | #180 | not possible | PR head `4c46d4a9c` is 83 commits from `c5e453d76` (12 master commits #167–#179 plus 71 Matchpassd commits, including `orig_asm`). Squash `9575dbb7c` was not merged. |
| #307 | #183 | cherry-pick side branch | `4fe521b6eff38927ae5d7791046072aa5ecbc8c9` cherry-picked as `3cf3c7defff7fa569104e863bf71cf1b3f4d7120` (head `9c56c80fc`). The other 18 commits of head `0fdea2fa9` were not merged. Squash `61f965ad7`. |
| #308 | #185 | cherry-pick side branch | `e6273d2020b57985aa0a273b251b34ea9f1dff1a` cherry-picked as `76a879bc7`, merged `03268ffd7`. The other six #185 commits were not merged. Squash `123215bfb`. |
| #311 | #190 | cherry-pick side branch | Sixteen commits, merged `-s ours` as `84554b0de7ffbcf4f8d1cd84013129e247e56904`: `fa756be8f9057e6aaacbfd8f8090a9ef471e6eed`, `12d385bb72427ac0b0715959a5e25db4599064a0`, `f2483e6b36ea8ef279081eb65100d6488cd590c4`, `b82d9c86efc6bbd893d425af0d90923e1782b5ec`, `38d35b81b9d31d11bcf985aa133c5aacf2bcb535`, `83c492b6e9889579e2e9c61d9be3f9f8ff1c04c4`, `0c37a09bec742c4b0cd408f3a59ba200d4c90dc6`, `a0ca4fc5d9b84557aa1e69c31f09e9de5008a881`, `38884a337398ed37e2b83296c8855356c1a5f03c`, `150e44a2617d0043357213e4c1c5f9d052c611e9`, `8f3a5a9ef1beff087233e02453cb2806853f2caa`, `67582944279d0985e57133c8deb6abaf76b0ea91`, `9c4e9ea1dacccbcf66d5c8316c2fc7bb4ecff771`, `6f0661815d1b00e7af49688c8f8fc30b351ee0da`, `1e84ca74d5a295b7528490de90aaa94eac752eb0`, `96031a78cdcf47180ea1d12dfb7d2d505bfe1832`. Direct merge of the head would also bring #167–#189. Squash `5695627bd` was not merged. |
| #312 | #188 | pending | Body cites squash `d82be2a8b`. No original-commit merge is stated. |

No open PR was found for an upstream #181 gap.

## Coordinator seed, resolved

| Seed | Fork PR |
|---|---|
| z/171 | #305 |
| z/188 | #312 |
| z/189 | #303 (FlagWord slice also #310) |
| z/190 | #311 |
| z/191 | #302 |
| #180 gap | #306 |
| #181 gap | none open |
| #183 gap | #307 |
| #185 gap | #308 |
| text_801D40D4 | #304 |
| split consolidations from this branch | #309 (#180 QuestCol), #310 (#189 FlagWord) |
