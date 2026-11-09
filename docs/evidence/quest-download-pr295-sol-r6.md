# PR #295: Sol full-permission round six

PROVENANCE: gpt-6.1-sol full-perm r6.

Starting head: `f9264353b`. The first command was `git status`; the tree was
clean. Both origin fetches found main at `7026cbad6`, already an ancestor of
HEAD, so no additional merge was needed. PR #295 was draft and mergeable.

Read the latest PR comments, the round-five evidence, the sibling local
round-four results and slot-representation evidence, and the shared Grok
attempt log. The slot-representation note and attempt log were absent at the
requested worktree-relative paths; their existing copies were read at
`wave16-gpt-pr295/docs/evidence/quest-download-slot-representation.md` and
`../pilot-logs/attempts/pr295-grok-attempts.md`. Sibling files were read-only.

## Retained pagination change

The active page count is now initialized after the first measurement. One
ordinary `fitting` scalar holds the measurement result at both scan sites;
each nonempty scan still has its own actual node, accumulated bytes and
immutable byte limit. The result is assigned on every path before use. The
unnecessary outer measurement blocks are removed.

The mode input and page count remain separate. The unchanged traversal accepts
at most nine groups, reserves nine bytes, charges three bytes per measured
group, and accepts at least one group for a nonempty page. Exhaustion still
uses the original fallback call and the common display-rebuild tail.

| Measurement | Starting head | Retained |
|---|---:|---:|
| Pagination objdiff/report match | 97.22689% | 97.31092% |
| Pagination compiled size | 476 bytes | 476 bytes |
| Pagination frame | 0x30 | 0x30 |
| Unit exact code | 31,036 / 41,696 | 31,036 / 41,696 |
| Unit exact functions | 157 / 173 | 157 / 173 |
| Unit fuzzy match | 76.23456% | 76.23551% |

Only pagination's compiled function body and function report change against
the saved starting-head object/report. The other bodies and `.bss`, `.data`
and `.rodata` reports are unchanged. A raw ELF section comparison changes only
`.text` and `.strtab`; the latter's only string change is the compiler-local
name `@1997` to `@1998`. Relocation-section bytes, symbol-table bytes, section
sizes and section alignments are unchanged. This is not a complete-object
identity claim, and the unit remains unlinked.

## Fresh diagnostic batches

There were 66 full-unit diagnostic compilations across five batches, including
controls, followed by one cleaned-scope confirmation. Diagnostics used the
configured GC/1.2.5 compiler, real include paths and `-O4,p -inline off
-use_lmw_stmw on`, with no more than eight simultaneous compiler jobs. No unit
flag or new pragma was tried or retained. Every successfully compiled
diagnostic preserved all other compiled function bodies against the control.

The generated complete sources, objects, per-candidate objdiff JSON and batch
results are under `/tmp/opencode/pr295-r6/`; the generation/build driver is
`/tmp/opencode/pr295-r6.py`. Its `first`, `second`, `third`, `fourth`, `fifth`
and `cleanup` arguments select the six batches. The verification driver is
`/tmp/opencode/pr295-r6-verify.py`.

| Source/data-flow hypothesis | Result / disposition |
|---|---|
| Reuse actual node scratch, measurement result, or complete scalar scan state | 95.78992–97.05882%; no improvement |
| Explicit scan exits, accepted-group branch, empty-scan exit | 85.29412–97.22689%; no improvement |
| Initial slot pointer/reference or borrowed text-head member | 96.890755%, frame 0x38; no improvement |
| Branch-local head acquisition after optional preparation | 89.28571%, 504 bytes |
| One measurement site inside a page-selection loop | 70.2521%, 348 bytes |
| Walk real list-link addresses during measurement/advance | 85–89.54622%, 492–508 bytes |
| Advance through a consumed head reference | 91.05042%, 496 bytes |
| Unsigned/short bounded fit count | 95.37815% / 93.78151% |
| Node-led, count-led or equality-bound scans | 90.2521–97.14286%; no improvement |
| Mode switch or post-preparation boolean rebuild policy | 96.21849% / 93.193275% |
| Explicit page-loop exit or fallback return with rebuild | 94.2437% / 90.5042% |
| Immutable requested index with a separate working offset | 96.13445–97.22689% |
| Active count created only after first measurement | 97.22689% |
| Late active count with a shared actual measurement result | **97.31092%; retained** |
| Late count plus a shared scan node | 97.05882% |
| Post-tested selection, direct active-count measurement, width conditional expression | 95.46218% / 96.344536% / 92.89916% |
| Named measured-group size | 97.31092%; no benefit over simpler expression |
| Separate overhead accumulation or reassociated size addition | 97.22689% / 94.033615% |
| Scan owns null-node state, node-first short circuit, final-link exit | 88.90756–92.22689% |
| Explicit local copies of immutable request inputs, independent of count | Up to 97.52101%; extra input copies not retained |
| Entry-scoped head and/or complete real scalar scan state | 96.12605–96.97479% |
| Remove unneeded scopes from the retained late-count form | **97.31092%; confirmed** |

The retained body still has mode/index/head in `r31/r30/r29`, against the
target's `r30/r29/r31`. None of these concrete source/control/ownership
hypotheses recovered the target's 0x40 frame and allocation together. This is
a finite investigation, not a proof that exact pagination is impossible.

## Slot producer/consumer investigation

Rather than retrying sentinel spellings or null-only reset stores, this round
followed the dictionary routine's result and length output into the native
slot generator and search caller. The generated original assembly is
`build/GPOE8P/asm/pso/misc/TQuestVmDownLoadServer_803E6970.s`.

| Original addresses | Observed contract |
|---|---|
| `803E9E00..803E9E08` | For a non-dictionary byte, write length 1 and return null |
| `803E9EA0..803E9EA8` | Write completed length and return the actual dictionary-record pointer in r30 |
| `803E9EAC..803E9EC0` | On exhausted input with mode at least 3, return all ones without writing the length output |
| `803E9F04..803E9F08` | Completed no-match writes the best length and returns null |
| `803EAA34..803EAA40` | Slot generator tests slot+0 itself to decide whether generation is needed |
| `803EAA54..803EAA6C` | On all ones, leave the slot unchanged; otherwise copy the length into slot+0x18 and store the returned pointer directly in slot+0 |
| `803E9ACC..803E9AE8` | Search tests all ones separately from null before token access |
| `803E9AA0..803E9AB8` | Even the terminal search path distinguishes null from all ones using the global input mode |
| `803EA030..803EA044` | Search caller tests the returned segment pointer for all ones before traversing its list |

The length byte is real state that a portable coordinated recovery could use
to describe readiness; it is not evidence that slot+0 is an integer. In the
native generator, that byte is updated only after the distinct result check.
Likewise, returning null for both search outcomes would route incomplete-input
failure into the caller's ordinary empty-list path. Recovering that result as
an explicit status requires changing the producer/search/caller contract and
does not recover the native immediate pointer store/return.

No new search body or reset representation is retained. Search remains
undefined here. The inherited main pointer-sentinel sites remain unresolved
blockers, not approved constructs or an exception granted by a passing gate.

## Validation and outcome

Both required commands passed on the retained production source:

```sh
ninja -j8 && python3 tools/check_pr.py --no-build
python3 tools/list_port_exceptions.py --check
```

The original DOL hash, linked-unit and force-active checks passed. A separate
`report_delta.py --check` against the starting-head snapshot also reports
**zero regressions and zero new exact functions**. Project totals remain
4,164,972 matched code bytes, 27,339 matched functions, 1,454,863 matched data
bytes and 3,550 linked units. The standard baseline's +11 functions / +6,196
code bytes are existing main integration, not round-six gains.

Strict source review finds no added sentinel, pointer/integer conversion,
union/byte pun, cursor wrapper, padding, mode/count reuse, assembly, pragma or
exception. Only the small honest pagination improvement is publishable. Exact
pagination and sentinel-free exact reset/search remain stuck after these
additional batches. PR #295 stays draft.
