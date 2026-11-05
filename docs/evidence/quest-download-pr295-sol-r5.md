# PR #295: Sol full-permission round five

PROVENANCE: gpt-6.1-sol full-perm r5 on 035985056 PR#295.

Starting head: `0359850563c97e01646ea1350f6e331e0cf34357`.
Fetched main: `6c871bfd3cae756fb1460c3404dc1af88578ab50`, already merged.
The first command was `git status`; the starting tree was clean. PR #295 was
draft and mergeable. The previous local round-four `gpt-task/results.md` and
the PR summary comments were read before the experiments.

## Retained cleanup

`sub_803EC284` now has an immutable mode input and a separate page count.
The two measurements and group advance are ordinary scalar loops. The
duplicated fit/recount helpers and their declaration-order explanation are
gone. The inherited `dont_inline off` / `inline_depth(1)` scope starts at
`Default_803EC460` again, at its main boundary. No compiler flag is changed.

The direct recovery keeps the original decisions: at most nine whole groups,
nine bytes reserved, three bytes of overhead per measured group, and at least
one group on a nonempty page. An exhausted page walk falls back to selection
`(0, 0)` before the optional display rebuild.

| Measurement | Starting PR | Retained |
|---|---:|---:|
| Pagination objdiff | 99.957985% | 97.22689% |
| Pagination compiled size | 476 bytes | 476 bytes |
| Unit exact code | 31,036 / 41,696 bytes | 31,036 / 41,696 bytes |
| Unit exact functions | 157 / 173 | 157 / 173 |
| Unit overall fuzzy score | 76.26573% | 76.23456% |

Only pagination's compiled function body and function report change against
the freshly built starting head. The other compiled function bodies and the
`.bss`, `.data`, and `.rodata` section reports are unchanged. This is not a
claim that the complete object, including relocation and symbol tables, is
identical. The unit remains unlinked.

## Slot+0 remains a pointer-ABI blocker

The original assembly generated in this worktree independently confirms the
round-four producer evidence:

| Address | Evidence |
|---|---|
| `0x803EAA50` | Call `find_longest_match_entry` |
| `0x803EAA54..0x803EAA5C` | Test the all-ones failure result |
| `0x803EAA6C` | Store the returned pointer directly into slot+0 |
| `0x803E9ACC..0x803E9AD8` | Load slot+0 and test all ones |
| `0x803E9AE4` | Separately test null |
| `0x803E9C08` | Dereference the loaded pointer with `lbz` |
| `0x803E9CE0..0x803E9CE8` | Subtract a signed four-byte-record displacement from that pointer |
| `0x803EADF0..0x803EADF4` | Load integer -1 and store it into slot+0 on reset |

The recovered dictionary producer also returns actual addresses in
`quest_download_lz_match_entry_table`. No base addition or handle resolution
exists between the slot load and the search's token accesses. There is no
evidence for changing this native word into an integer index or handle.
An integer field initialized to `~0` would merely move the conversion problem
to the successful pointer values.

A full-unit diagnostic replacing just the two inherited token sentinel stores
with null reproduced reset at **97.704544%** (180 versus 176 bytes) and
`init_entries` at **96.29508%**. It changes only those two compiled functions
relative to the retained source. Those are two new exact-function regressions,
664 original code bytes, and the distinct native uninitialized/null states
would be collapsed. This candidate was rejected.

The actual PR starting head is different from the local round-four trial:
search is already undefined, pagination is already partial, and reset and
initialization are exact through inherited main code containing pointer
sentinels. A passing gate on this PR therefore does **not** mean the local
round-four four-regression problem has been solved. No sentinel-free exact
reset/initialization or matching search was recovered in this round. The
inherited casts are unresolved blockers, not approved exceptions or newly
introduced sentinel spellings.

## Rejected diagnostic families

Full-unit candidate sources and objects were generated under
`/tmp/opencode/pr295-r5/`, using the configured GC/1.2.5 compiler with
`-O4,p -use_lmw_stmw on` and the real project include paths. Compilations ran
with at most eight concurrent jobs. Function bytes were compared against the
starting compiled unit, and target scores against the original split object.
These diagnostics do not alter the configured build or establish whole-unit
acceptance of a flag.

| Candidate family | Pagination score / result |
|---|---|
| Direct scalar control | 97.22689%; retained |
| `for` fit loop, increment in loop header | 94.033615% |
| Limit initialized before running total | 96.97479% |
| Const mode / preincrement / countdown advance | 97.22689%; no improvement |
| Explicit boolean rebuild policy | 92.89916%, 484 bytes |
| Read width within each fit iteration | 88.4874% |
| Remaining-byte budget instead of accumulated total | 92.85714%, 460 bytes |
| Post-tested fit scan | 92.35294%, 468 bytes |
| Advance the head directly instead of a local group cursor | 96.21849%, 472 bytes |
| Scalar fit/recount helpers, distinct count, unit `-inline on` or `noauto` | 99.663864%, but changes exact `sub_803EA1A8` |
| Same helpers, unit `-inline deferred` | 99.663864%, many other compiled bodies change |
| Same helpers, unit `-inline all` | 99.117645%, many other compiled bodies change |
| Helpers outside the pragma scope, `off` or `off,deferred` | 36.10084%, 232 bytes; deferred also changes other bodies |

For `on`/`noauto`, `sub_803EA1A8` retains its instructions but loses eight
bytes of frame (`0x30` to `0x28`), changing five save/restore/prologue words.
Typed slot access, typed head-member pointers/references, indexed command-byte
access, scoped command positions, and real inline command-scan helpers using
returned positions or consumed references did not restore the exact body.
Removing combinations of its inherited optimization pragmas also did not
restore it. No such edit or flag is retained.

The existing partial `sub_803F03B4` was also tested with wide versus truncated
length expressions, cursor/end construction order, byte versus halfword key
locals, key-member reads, and success/failure exits from duplicate lookup.
The best diagnostic reached 89.084335%, still 328 versus 332 bytes, with no
new exact function. Its production source is unchanged at 86.73494%.

These experiments exhaust the concrete alternatives investigated this round;
they are not a proof that every possible honest source arrangement is
impossible. Neither an artificial cursor nor reused mode/count storage is
restored to obtain a higher score.

## Validation

The normal regression baseline is left unchanged. A separate snapshot of the
freshly built starting-head report additionally checks the incremental change.
Both required final commands passed before the final main catch-up:

```sh
ninja -j8 && python3 tools/check_pr.py --no-build
python3 tools/list_port_exceptions.py --check
```

The retained result preserves 4,163,792 exact project code bytes, 27,337 exact
functions, 1,454,631 matched data bytes, and 3,549 linked units. The incremental
comparison against `035985056` has zero new exact functions and zero
regressions. The normal baseline includes earlier main integration, so its
reported +5,016 code bytes / +9 functions / +1,328 data bytes are inherited,
not gains from this round.

The sentinel-free exact slot/search recovery remains stuck. This round's
publishable progress is removal of pagination steering at a lower honest
fuzzy score with no exact-function loss. PR #295 stays draft.
