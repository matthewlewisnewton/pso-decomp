# PR #403 matching scope and review checkpoint

This checkpoint follows native Word recovery `e16871d0bf` and integration
`fb6e24bb42` of independently rebuilt main
`c193225262c59b584d182605d53cf4c6918c57b5`. The requested completion criterion is
100% matching code and data in this PR's window scope, with no regressions
elsewhere. It is readiness for code review, without a claim that every historical
ownership, lifetime, original-source or portable-interface question is solved.

## Scope and exactness

The source delta against that main contains 206 active compiled units. Of these,
205 complete units, including 135 with window names, are entirely original-exact
and source-linked:

| Measurement | Exact / total |
| --- | ---: |
| Functions | 3,065 / 3,065 |
| Code bytes | 455,952 / 455,952 |
| Data bytes, including startup records and BSS | 48,717 / 48,717 |
| Complete source-linked units | 205 / 205 |

The remaining touched unit is `TObjPlayer_801AF2F0`. Its only source change is
the 88-byte `get_battle_ctrl_id` helper, which is original-exact. Three unrelated
pre-existing nonmatches (`apply_battle_level_reset`, `apply_class_level_growth`
and `apply_wall_response`) and its remaining unmatched data are outside this
window scope and are unchanged. This is not a whole-game 100% claim.

The native Word constructor/destructor/table now pass the whole-owner placement
and actual-relocation gates, superseding that historical blocker. See
[the complete emission evidence](window-word-native-emission.md). The Word change
itself adds no matching coverage: its former raw implementation was already exact.

## Baseline and no-loss evidence

Both the independently built main and combined PR build reproduce original DOL
SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Main's unchanged source-linked
and generated-retention checks pass before comparison.

| Aggregate measurement | Main | Combined PR | Delta |
| --- | ---: | ---: | ---: |
| Exact functions | 27,508 | 27,508 | 0 |
| Matched code bytes | 4,302,440 | 4,302,440 | 0 |
| Matched data bytes | 1,496,516 | 1,498,144 | +1,628 |
| Source-linked code bytes | 4,153,448 | 4,153,448 | 0 |
| Source-linked data bytes | 1,494,296 | 1,495,924 | +1,628 |
| Exact linked units | 3,619 | 3,619 | 0 |

`tools/check_pr.py` passes against both this fresh main and published prior
continuation `7874908788`. There are no lost exact functions, exact-data ranges,
source-linked functions or source-linked data ranges. The fourteen previously
qualified four-byte tail intervals remain outside report coverage against main;
the existing gate classifies them as alignment padding. This checkpoint adds no
tail, ownership claim or new regression waiver. Historical tail qualifications
remain in [the review index](window-continuation-review-index.md).

All 3,619 linked units are exact, generated retention contains 19,971 names
without drift, and the scanner reports no pending exact candidates or regressed
linked units. All 347 synthetic tool tests and the portable behavior and
ASan/UBSan targets pass after integration. Python syntax, changed-line whitespace
and generated exception-inventory checks pass.

## Remaining review qualifications

The earlier [readiness assessment](window-continuation-readiness.md) assessed
completion of the broader native-lifetime investigation. It remains historical
evidence of real uncertainty, rather than a requirement to invent source or
change original behavior to meet a binary-matching request. The current checkpoint
supersedes its blanket draft recommendation for the explicitly requested matching
scope. The Word order/table/startup failure is resolved; the other qualifications
remain available for review.

In particular, retain CustomSelect's nonzeroing-allocation/early-return and valid
session ordering preconditions; ComCard and Hard table/trailing-word ownership;
borrowed callbacks and deferred-generation ordering; raw storage, helper and
buffer interfaces; ChoiceSetting's auxiliary producer; Palette reset/index/tag
contracts; and original compiler-profile provenance. No speculative null guard,
zeroing, synthetic data, manual table or behavior-changing safety repair is added.
The new Word compiler override is recorded with its reason and port guidance.

Original #268 history and the 153-entry attribution archive are preserved. No
merge to main or formal approval is part of this checkpoint.
