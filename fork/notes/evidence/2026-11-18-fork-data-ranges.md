# Fork data coverage at the November 18 sync point

Fork main `8937534387e0ee55dc2bdce311b90642d922ea4a`. Upstream master `92a266f5ebb72b0fce6f1ca70b690d0464779d7a`. First patch `ef2ca77a865197057945e9bf39e30a15a7a83ac4` on `great-merge/fork-data-ranges`.

## Current integration status

At integration commit `75a68a350c`, 148 of the 1,147 inventoried bytes have been recovered across nine ledger rows. The address checker finds another 836 bytes missing from both exact and source-linked data, across 38 normalized ranges. The other 163 bytes were outside the checker's baseline deficit. The ledger gives the missing byte count at baseline and at this integration commit for every row, along with the commit responsible for each recovery.

This comparison also covers fork main through `23aa26cec0`. The newer Gyaranzo change extends the fork's constant pool to 0x805DA258–0x805DA2A0. Upstream already links that entire range from `pso/enemy/gyaranzo/TObjEneGyaranzo.cpp`. The other two changes since the inventory update the fork's documentation.

The integration build matches the original DOL. All 27,572 functions are exact and all 2,541 source-linked units pass. The checker identifies eight bytes of alignment outside the new reported total, four after the Gal Gryphon pointer and four after the thunder-effect constants. The first-patch branch remains independently reviewable from the upstream base.

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

## First patch and acceptance

The ending-scene owner defines the two globals at 0x805D4F10 and 0x805D4F14. Independent review found a handwritten int declaration for the fade state in the TEndingC writer. The amended patch uses the shared s32 declaration, and independent re-review accepted the exact head. The fresh baseline and final complete build used the local GPOE8P disc inputs. check_pr.py passed against the upstream baseline. All 27,572 functions remain exact and all 2,541 linked units pass. The linked ELF inputs select the compiled TEndingAB object. The compiled object defines the two four-byte symbols in .sbss. Both DOLs match the original SHA-1, 0d85744b51d7379efb025a943d0cd5aaae2191a3.

| Metric | Upstream baseline | First patch |
|---|---:|---:|
| Matched code bytes | 4,353,092 | 4,353,092 |
| Linked code bytes | 4,353,092 | 4,353,092 |
| Matched data bytes | 1,743,987 | 1,743,995 |
| Linked data bytes | 1,744,207 | 1,744,215 |

Against the pinned fork build, the upstream address comparator reports 984 bytes missing from exact and linked data at baseline and 976 after the patch (47 to 46 normalized ranges). Each set describes the same bytes under two measures. Both comparisons preserve every fork exact and linked function. The tool also flags the existing difference of 1,961 total data bytes. Its address details report 2,156 bytes of lost alignment coverage and 195 bytes gained. These are unchanged by this patch. The checker applies its own padding rule and normalizes adjacent intervals, while the 1,147-byte inventory uses declared splits. The combined fork-parity gate is still open.

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
