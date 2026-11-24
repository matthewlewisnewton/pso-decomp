# PR #295: entry-merge inline boundaries

## Measurement

Starting source: `2c34d2b9bc58eba852c24dd80f9544f00c0354b3`.
Compiler: the unchanged GC/1.2.5 unit profile, `-O4,p -inline off`.
Scores below use the pinned objdiff-cli 3.6.1 and freshly generated split
objects from the original DOL.

| Function | Starting report | Retained report | Compiled/original size |
|---|---:|---:|---:|
| `sub_803F03B4` | 87.69879% | 99.75903% | 332/332 bytes |
| `sub_803EC284` | 100% | 100% | 476/476 bytes |
| `sub_803E9A74` | undefined | undefined | original 876 bytes |

The earlier PR comment's 89.458% entry-merge score is not the starting
report's fuzzy score. This comparison uses the same tool and scoring path
for both versions. Exact unit coverage remains 31,512/41,696 code bytes
(75.57560%), 158/173 functions. There is no new exact function from this edit.

## Entry-merge evidence

The duplicate scan at `0x803F0434` copies the saved output base with `mr`,
walks six-byte entries, and materializes its result separately at each exit:
one for a duplicate, zero for an exhausted range. The subsequent text scan
at `0x803F04BC` has another input-cursor handoff and returns the advanced
cursor with `mr`. The existing `skip_entry_text` implements that exact
two-byte traversal and delimiter test.

Expressing the duplicate scan as `merge_duplicate_download_entry` and
reusing `skip_entry_text` reproduces both handoffs. This also puts the
`n * 6` multiply before the length mask, recovering the original persistent
registers: output base `r0`, record end `r7`, encoded-input cursor `r10`.
Writing both loops directly had lost these assignments.

The definition is beside its helper inside the existing depth-one region
for `sub_803EF958`; no directive, option, or region boundary changes.
This deliberately differs from address order. Returning the definition to
address order leaves both helpers out of line under the unit's unchanged
`-inline off` profile: 36.831326%, 248 bytes, with real calls and a frame.
The owning translation unit remains unchanged and unlinked. Source order
changes emitted function order; this is not a claim that the whole object
can yet replace its original linker input.

Every instruction from the first entry load through the final return now
agrees with the original, including the duplicate-loop counter setup and
the text-scan counter setup. Four header words remain different:

| Relative offset | Original | Retained |
|---|---|---|
| `+0x18` | length mask into `r10` | length mask into `r9` |
| `+0x1C` | name displacement into `r9` | name displacement into `r10` |
| `+0x24` | end pointer uses `r10` | end pointer uses `r9` |
| `+0x28` | input pointer uses `r9` | input pointer uses `r10` |

Header evaluation orders, decoded-field temporaries, output-array/reference
views, predicate result types, and direct versus inline traversals were
measured. The minimal two-helper form is retained. Separating the existing
text helper's parameter from its cursor regressed exact `sub_803EF538`, so
that experiment was rejected and the shared helper restored verbatim.

## Search ABI probe

Standalone ordinary-C++ GC/1.2.5 probes confirmed the union-return blocker
without editing the production search. A four-byte union of integer status
and segment pointer can return in `r3`, but assigning its integer arm and
returning either the pointer arm or the complete local union still emits a
stack store/load. Aggregate initialization, including a const local,
additionally reads an emitted constant. Extracting either arm from a union
call result also stores and reloads the returned word.

This supplies no spill-free implementation for the original search's
immediate failure return. Its production definition remains absent. No
pointer sentinel, pointer/integer cast, union conversion helper, compiler
override, or new exception is introduced by this edit.

## Checks

Pagination was rebuilt and verified at 100%, 476/476, after every production
source experiment, including rejected variants and their restoration.
`tools/check_pr.py` passed against the freshly built starting-head baseline
with zero exact, data, or linked regressions; the exception inventory check
also passed. The attempt-by-attempt log stays in ignored `.pilot-attempts.md`.

### Current-main integration

The retained source is committed as `347bb2b4a`. Main
`0b6342088f1d62ccf43a770600c98d33ecd1bac7` was separately built from its
checked-in splits, symbols and source, and its own `check_pr.py` passed.
It was integrated with an ordinary merge, `0f70e4d9b`, without changing the
quest source or its types.

The full build and `tools/check_pr.py --baseline` against that fresh main
report passed: zero matched-function, matched-data, linked-function, linked-data
or coverage regressions. All 3,562 linked units remain exact; retention has
zero missing or stale entries. The DOL SHA-1 check passes. The exception
inventory check passes without a generated-inventory change from this work.

Project totals after integration are 4,178,212 matched code bytes, 27,357
matched functions, and 1,463,239 matched data bytes. Relative to current main,
the extra 476 exact code bytes and one function are the pagination match
already present at this worker's starting commit. This round's entry-merge
improvement is fuzzy only. Unit fuzzy coverage is 76.36992%; exact coverage
remains 75.57560%.
