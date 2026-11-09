# DHCP and Falz folds after main integration

PR #303 was refreshed from head `1f98305a1069024acf087f83b906c3feab8a4964`
against fork main `6daa19a11db97b1b8222fd2665eba485ed3a74a4` on 2026-11-09.
The older local `sol61-pr303` continuation and dirty lane8 worktrees were left
untouched; validation used an independent clone and a detached main worktree,
each with its own freshly generated splits, compiled objects and report.

## Remaining contribution

Main already links `NetworkPacketRuntime` at 24/24, including the reset at
`0x80424E44`. This branch retains the descriptive DHCP globals and portable
volatile state declaration, but does not claim that reset as a new match.
The useful incremental matches are the lease callback `0x80423298` (424 bytes),
request step `0x80423E80` (940 bytes), and discover step `0x8042422C` (816 bytes).
`text_80421620` goes from 39/42 and unlinked to 42/42 with exact code/data and
links from its compiled source object.

The branch also folds the already-exact Falz shadow draw (9 functions) and
character-select load buffer (9 functions), and supplies source data for
`float.c`, `OSMemory`, and `GcrnaStream`. The folds remove two unit names and
the DHCP/float additions add two, so the linked-unit count stays 3,570.
The separate upstream #171 provenance merge is already on main through #305;
this branch does not introduce another upstream merge.

## Integration repairs

Main's typed `NetRegisterTimer` declaration replaces this branch's obsolete
local `void *` callback prototype. Its declaration of the lease callback as a
function is retained. The two reset helpers keep this branch's renamed DHCP
globals; their resulting unit stays 24/24 exact, including its data.

Newly landed `TOBoss4`, `TBoss6Rock`, and trap units include `BmlResource.h`,
whose model accessor now returns `NJS_OBJECT *`. `TOBoss4Rock::models` is an
array of model pointers: both assignments take the model accessor result and
the only indexed read feeds `draw_ginja_object`. Its field is therefore
`NJS_OBJECT **`; the allocation uses `sizeof(NJS_OBJECT *)` and the draw needs
no cast. The GameCube layout remains 0xB8 and its containing unit remains exact.

Explicit conversions remain at the existing integer interfaces: the model
argument to `TUnk_804F1280::set_target`, `TMotorcycle::add_entry`, and the
`TObjChipParams`/`TObjChipSpawnParams` model words. These conversions record
the boundary rather than changing those shared interfaces or their mangled
names. Existing `BmlModelEntry::model` and texture-list handle boundaries are
also unchanged. Removing every legacy model-handle conversion is separate
work; the current declarations are not a claim that those words are portable
host-sized pointers. Redundant conversions at pointer-consuming callers were
removed. No new assembly, pragma, intrinsic or per-unit override was added
by the integration repairs.

## Validation

Fresh main builds to DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`, passes `check_pr.py` against its
own fresh report, and passes retention with no additions or removals.
The integrated branch builds to the same DOL hash and passes
`tools/check_pr.py --no-build --baseline <fresh-main-report>`:

| Measure | Main | Integrated branch | Delta |
|---|---:|---:|---:|
| Exact functions | 27,364 | 27,367 | +3 |
| Matched code bytes | 4,180,388 | 4,182,568 | +2,180 |
| Matched data bytes | 1,468,463 | 1,468,551 | +88 |
| Complete code bytes | 3,636,556 | 3,648,776 | +12,220 |
| Complete data bytes | 1,165,731 | 1,170,619 | +4,888 |
| Linked units | 3,570 | 3,570 | 0 |

There are no address-level code/data regressions or coverage losses. All 3,570
linked units pass the source-linkage check. Retention was regenerated from
this branch's fresh split objects: 17,528 names become 17,549 (21 additions,
zero removals). The regenerated retention check and porting-exception inventory
check pass. `TOBoss4` (18/18), `TBoss6Rock` (37/37), `TOTrapAncient01` (18/18),
`TOTrapAncient02` (32/32), and `TOTrapSeabed01` (19/19) retain exact code/data
and source linkage after adapting the accessor callers.

Remaining review concerns are the bounded legacy model-handle interfaces and
the existing DHCP boundaries documented by the PR (UDP buffer address, lease
parser receiver and cookie store). Matching and linkage do not establish the
unrecovered original source types at those boundaries.
