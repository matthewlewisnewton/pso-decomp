# Fork data coverage at the November 18 sync point

## After the four upstream reviews merged

As of upstream `f76fdd7ff1`, 644 of the original 1,147 bytes remain across 29 ranges. The three latest merges recovered 72 bytes across four rows compared with `2ad5dece70`. The last column of the [range ledger](2026-11-18-fork-data-ranges.tsv) compares source-linked data from a clean build of the merged master with fork main and excludes verified padding. Full local integration accounts for every row.

## After upstream PR 325 landed

Upstream master `2ad5dece70` has 716 bytes still missing across 33 of the 90 original inventory rows. PR 325 closed 32 bytes since the previous upstream build. The [per-range column](2026-11-18-fork-data-ranges.tsv) gives the residual at each original address. Both the combined nineteen-group build `4aaee804a2` and the full integration build `2ea980a848` preserve all fork-matched and source-linked data ranges. Both reproduce the retail GPOE8P executable. In the newly consolidated De Rol Le dust unit, aligning the origin constant to eight bytes reproduces the four original padding bytes at 0x805D85B4 and places the five controller constants at 0x805D85B8–0x805D85CB.


Original fork inventory at `8937534387e0ee55dc2bdce311b90642d922ea4a`. Upstream master `92a266f5ebb72b0fce6f1ca70b690d0464779d7a`. The initial eight-byte checkpoint is `ef2ca77a86` on `great-merge/fork-data-ranges`. Its changes now open the front-end scenes matchpass.

## Fourteen review groups close the inventory

Local branch `great-merge/verify-fourteen` at `5d66c65409` accounts for all 1,147 bytes across the [90 ledger rows](2026-11-18-fork-data-ranges.tsv). From the last 72 bytes, the area selector links 24, the boss effects link 40, and the area music sequencer links four. Four original linker-padding bytes at `0x805D8A2C` belong to the Dark Falz review. The two final columns record these contributions and the zero residual in each row.

Against upstream master `b2cac76477`, the combined build gains 792 matched and source-linked data bytes and one exact linked unit. It reproduces the retail executable with all 27,572 functions and 2,539 selected units exact. Against fork main `3342e42983`, there are zero lost exact or linked functions or data ranges. The overall reported data extent still requires the alignment reconciliation recorded below.

## Landed upstream and the twelve-group build

On upstream master `b2cac76477`, 748 of the original inventory bytes still need coverage. The twelve published and local review groups build together at `ee4e1655cb`. Their combined tree recovers 676 of those 748 bytes. Comparing the game built from that tree to fork main leaves **72 bytes across eight original ledger rows**. The report coalesces the last two adjacent Dark Falz rows. The [range ledger](2026-11-18-fork-data-ranges.tsv) records the contribution of each additional review and the measured residual by address.

| Remaining owner | Inventory bytes | Intended group |
| --- | ---: | --- |
| Area selection window | 24 | Window layout and area selection |
| Photon Blast shower class name and pointer | 16 | Particle creation and lifetime |
| Gal Gryphon controller pointer | 4 | Boss encounter state |
| Area music fade | 4 | Music sequencing and streaming |
| Dark Falz effect and demo constants | 24 | Boss effects. Four bytes at 0x805D8A2C are original linker padding. |

The integration tree at `fc96ba681f` contains the recoveries for all of these rows. Comparing its build against fork main finds zero lost exact or source-linked functions or data ranges. The report flags the total data extent for manual reconciliation. Removing 2,196 bytes of verified alignment padding and gaining 151 bytes of covered addresses accounts for the 2,045-byte decrease. This comparison is separate from the original 1,147-byte inventory.

## After upstream PR 320 landed

Upstream master `77a34b3d72` contains all 176 inventory bytes previously credited to PR 320. Comparing the original inventory with a fresh build of master leaves 808 bytes across its 90 rows. The four submitted matchpasses recover 132 inventory bytes. The two local UI matchpasses recover 372 more. The combined six-group build leaves 304 inventory bytes in 18 ranges, including the four verified padding bytes at 0x805D8A2C. Its exact and linked data totals increase by 548 bytes, including 44 outside the initial inventory. Of the 304 still outside these six reviews, 272 belong to player, enemy and effect work, 24 to the area window, four to music and four to padding.

The added columns of the [range ledger](2026-11-18-fork-data-ranges.tsv) record the remaining byte count on this master, the contributing PR or local branch, and the deficit after applying all six groups. The original baseline and integration columns retain the earlier comparison.

Upstream merged PR 321 as `b2cac76477`. Its complete Git tree equals the tested front-end branch. The current upstream deficit fell from 808 to 748 original inventory bytes. The remaining three submitted PRs cover 72 of those and the two queued UI branches cover 372. The upstream-b2cac76477 column reports the deficit on the landed tree by address.

## Integration against the original baseline

**All 1,147 bytes are accounted for** at `66eec9e27e`. The integration build links 980 previously missing inventory bytes from source. Four bytes at 0x805D8A2C are verified original linker padding. The other 163 bytes were already outside the checker's original 984-byte deficit. The ledger records the original and current missing-byte counts and the commit that closed each row.

Of the 980 bytes now linked, 176 come from six recoveries already proposed in upstream PR 320. The integration branch uses those commits locally with their original authorship. At that baseline PR 320 was open at `f72cca569d`. It subsequently landed in `77a34b3d72`. The other 804 bytes come from the fork integration work. The front-end scenes matchpass builds directly on upstream master and is independent of PR 320.

| Integration commit | Inventory gap closed (includes identified padding) | Additional matched bytes outside the inventory | Missing inventory bytes after commit |
|---|---:|---:|---:|
| `75a68a350c` and predecessors | 148 | 0 | 836 |
| `7202f5fbd6` — event filenames, card, boss and network state | 84 | 4 | 752 |
| `7aea3ba036` — player combat, boss dust and lighting | 112 | 0 | 640 |
| `a427c24c40` — rotation, window and boss constants | 28 | 4 | 612 |
| `6baca82926` — line-drawing resources and constants | 20 | 0 | 592 |
| `8c4f54cf1d` — music, status window and Dark Falz | 40 (36 source, 4 padding) | 44 | 552 |
| `e6e6079ea6` — Gifoie orbit-task dispatch table | 24 | 0 | 528 |
| Selected PR 320 window commits, validated at `4dd0e29fe5` | 176 | 32 | 352 |
| `c83050f684` — area-window dispatch table | 24 | 0 | 328 |
| `d9898049b2` — equipment-kind, equipment-list and item-list dispatch tables | 84 | 0 | 244 |
| `3719b26d9a` — status-list window dispatch table | 28 | 0 | 216 |
| `6be15b784e` — shop and team-status list dispatch tables | 56 | 0 | 160 |
| `f20aaf813a` — choice popup and settings dispatch tables | 48 | 0 | 112 |
| `e4d3db27d0` — speech-balloon dispatch table | 24 | 0 | 88 |
| `af37412365` — item-help dispatch table | 24 | 0 | 64 |
| `8804f7af44` — status rank prefixes and display dispatch table | 40 | 0 | 24 |
| `66eec9e27e` — soft keyboard dispatch table | 24 | 0 | 0 |

The starting comparison covers fork main through `23aa26cec0`. The newer Gyaranzo change extends the fork's constant pool to 0x805DA258–0x805DA2A0. Upstream already links that entire range from `pso/enemy/gyaranzo/TObjEneGyaranzo.cpp`. The other two changes since the inventory update the fork's documentation.

The integration build matches the original DOL. All 27,572 functions are exact and all 2,539 source-linked units pass. Compared with pinned upstream master, the integration branch gains 1,064 matched and source-linked data bytes, including 84 outside the original inventory. The 64-byte decrease in total reported data coverage comes from alignment gaps. Each of the six latest recovery commits passed the full check against its parent. All 266 tooling tests passed.

The address comparison against fork main `23aa26cec0` finds zero missing exact or source-linked functions and zero missing exact or source-linked data ranges. The aggregate comparison still flags a 2,025-byte difference in total reported coverage. All 2,176 bytes leaving coverage satisfy the per-address original alignment-padding check. The other direction adds 151 zero bytes, including 147 meeting that same check and four bytes of .bss at 0x8050104C. The two directions reconcile exactly. These are differences in section coverage, separate from the 1,147-byte inventory.

The [matchpass queue](2026-11-18-upstream-matchpasses.md) groups the recovered bytes with their subsystem changes. The first upstream candidate, `great-merge/frontend-scenes`, includes the ending globals, line drawing, title and menu assets, and character-select input state. Its standalone build recovers 60 inventory bytes and four adjacent bytes.

Fork main subsequently advanced to `3342e42983` with the TCP runtime recovery. Its executable build inputs match the checked fork checkout. Comparing that build to integration still gives zero missing exact or source-linked functions and zero missing exact or source-linked data ranges. The 2,025-byte aggregate coverage difference has the same address-level reconciliation. The network matchpass includes eight bytes of the existing inventory. Together the first two review branches cover 68 inventory bytes.

Four prepared matchpasses now cover 132 inventory bytes. Front-end scenes cover 60, network runtime eight, chunk rendering 32 and scene resources 32. Their combined build gains another four linked bytes outside the inventory.

## Starting inventory

The [range ledger](2026-11-18-fork-data-ranges.tsv) breaks the 1,147 bytes into 90 nonoverlapping intervals, divided at fork owner boundaries. The addresses are absolute and the end is exclusive. Each fork owner is in the fork executable's Ninja link inputs as a compiled source object. Each row names the upstream baseline report unit covering it (or records absence). The source mentions are lexical references to overlapping upstream symbols, including declarations. They are leads for porting and do not establish ownership by themselves.

| Section | Fork-only bytes |
|---|---:|
| .data | 556 |
| .rodata | 100 |
| .sdata | 24 |
| .sdata2 | 388 |
| .sbss | 79 |
| Total | 1,147 |

The fork source objects' ELF symbol tables place 982 bytes inside sized objects. The other 165 are zero in the original DOL and fall outside those symbols. Of these, 139 occupy 35 entire ranges and 26 share ranges with objects. Zero-fill bytes do not justify new source variables. Range sizes include internal padding when the compiler includes it in an object's symbol size.

The largest group is 552 bytes in 20 intervals containing virtual tables. Some intervals also contain neighboring data. Open upstream PR 320 at `f72cca569da650fee0f015d7bf2aa77e232800ba` proposes linked splits over 176 bytes in six intervals. Its parent base is the pinned upstream master. The two PR 320 columns measure intersection with its declared linked intervals. Check its landed result before duplicating that work.

The class name for TDPBShower has a proven consumer and pointer relocation. The isolated 16-byte recovery using the ordinary upstream compiler configuration failed the DOL hash. Both sections need four-byte placement and MWCC emits them with eight-byte alignment. The fork has a per-unit alignment override. Commit `707b399ca6` recovers both rows on the integration branch. The compiler emits the class vtable and the constructor sets the inherited name field. The per-unit alignment adjustment places the 12-byte string range at 0x80479C3C and its four-byte pointer at 0x805D4454. At this commit the address comparison showed 40 remaining fork-only exact and linked ranges totaling 848 bytes.

## Original eight-byte checkpoint

The ending-scene owner defines the two globals at 0x805D4F10 and 0x805D4F14. Independent review found a handwritten int declaration for the fade state in the TEndingC writer. The amended patch uses the shared s32 declaration, and independent re-review accepted the exact head. The fresh baseline and final complete build used the local GPOE8P disc inputs. check_pr.py passed against the upstream baseline. All 27,572 functions remain exact and all 2,541 linked units pass. The linked ELF inputs select the compiled TEndingAB object. The compiled object defines the two four-byte symbols in .sbss. Both DOLs match the original SHA-1, 0d85744b51d7379efb025a943d0cd5aaae2191a3.

| Metric | Upstream baseline | First patch |
|---|---:|---:|
| Matched code bytes | 4,353,092 | 4,353,092 |
| Linked code bytes | 4,353,092 | 4,353,092 |
| Matched data bytes | 1,743,987 | 1,743,995 |
| Linked data bytes | 1,744,207 | 1,744,215 |

Against the pinned fork build, the upstream address comparator reports 984 bytes missing from exact and linked data at baseline and 976 after the patch (47 to 46 normalized ranges). Each set describes the same bytes under two measures. Both comparisons preserve every fork exact and linked function. The tool also flags the existing difference of 1,961 total data bytes. Its address details report 2,156 bytes of lost alignment coverage and 195 bytes gained. These are unchanged by this patch. The checker applies its own padding rule and normalizes adjacent intervals, while the 1,147-byte inventory uses declared splits. At that first-patch checkpoint, the combined fork-parity gate was still open.

The intended end state is shared source, configuration, and tooling with upstream, with fork-only LLM documentation. Keep this inventory and review evidence out of the upstream patch. Publication requires separate confirmation.

## Four constant pools on the integration branch

Commit `66f583cdfaf5beb64fede187d813847af45ff808` recovers the original split ranges below. The ledger above records the starting inventory.

| Owner | Start | End (exclusive) | Bytes |
|---|---|---|---:|
| TObjPlayer_801AF2F0 | 0x805DC278 | 0x805DC2B0 | 56 |
| TObjPlayer_801C7430 | 0x805DC374 | 0x805DC380 | 12 |
| TWindowHelpItem_802540AC | 0x805DCE00 | 0x805DCE10 | 16 |
| TeneFakeTecThunderEff | 0x805D99F0 | 0x805D9A0C | 28 |

The upstream compiler emits the help-window coordinates and three action-state literals in the original order. The larger player pool exports constants referenced across units. The thunder effect needs its named loads to preserve two functions' floating-point instructions. With upstream's existing options, ordinary named definitions were emitted in .sdata. Specifying .sdata2 produced the original object layout and DOL. The final float occupies four bytes. The following four zero bytes are alignment padding.

The full upstream check passed. Against the preceding integration commit, matched and source-linked data each increased by 112 bytes. Against the pinned fork, 42 intervals totaling 864 bytes remain missing under each measure. All fork exact and source-linked functions remain covered.

## Ending class name and Gal Gryphon controller

Commit `781e7e3ef7` recovers the eight bytes at 0x80439568–0x80439570. The ending-scene setup unit defines the read-only class name. The constructor assigns the pointer to the task's name field.

Commit `75a68a350c` recovers the four-byte controller pointer at 0x805D4DE0–0x805D4DE4. The factory stores the new controller and its destructor clears the pointer. The boss and lobby callers share its declaration. The original build report included the following four bytes in the symbol extent. The compiled object defines one four-byte pointer and the next object starts at 0x805D4DE8.

`tools/check_pr.py` passed on each code commit against upstream `92a266f5eb`. The integration build covers every exact and source-linked function in the current fork.
