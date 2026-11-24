# Texture reader cursor storage

Baseline: fork main `1a18b4bd7577af4ee367317064e020d1f91ce5a8`.
The initial source investigation used `f0f05f3afe`; current-base validation
also includes the subsequent rope and ADX recoveries.
Reference: upstream `8c507b2dacae5428291a823c3868ca486419660c`,
`src/pso/system/TLanguage_801E4874.cpp` and its split/symbol metadata.
Upstream #196 and #198 are already ancestors of this fork baseline; this is
an independently bounded data recovery, not another merge of either PR.

The existing source uses `TLanguage__read_cursor` as a byte pointer. The
original word at `0x805D5E58` is the read cursor: the header reader stores the
input buffer, the byte readers load/advance it, and `read_into_buffer` uses
and advances it. Across all original split objects listed in the baseline's
fresh `build/GPOE8P/config.json`, its 20 relocations occur only in
`pso/misc/TLanguage_801E4874.cpp`. All have zero addends and are on `lwz` or
`stw` word accesses. The definition preserves the source's existing pointer
type, linkage and name; no function body or declaration boundary changes.

The old eight-byte symbol extent includes the next word. Only the first four
bytes are supported as this pointer. This change corrects that symbol extent
and claims `[0x805D5E58, 0x805D5E5C)` for the current source unit. This is
supported ownership for the current recovery; the original translation-unit
boundary and original variable name are not authenticated.

The adjacent `[0x805D5E5C, 0x805D5E60)` word remains an explicit original-only
split, `original_unclaimed_805D5E5C`. It has no source definition, is not added
to the linkset and is not counted as matched or source-linked. A bare
four-byte claim, as upstream uses, leaves that alignment-sized gap out of its
report. Keeping it explicit prevents an apparent gain that erases original
address coverage. Its purpose and ownership remain unknown; this change
does not label it as padding or invent a second field.

Expected incremental result: four newly matched and source-linked data bytes;
no newly matched function or code byte, no newly linked code byte, and no
change to total code/data/function address coverage. The already linked
reader unit stays linked, and the adjacent original word stays original.

## Progress-category distinction

Global raw coverage retains all 1,761,223 data bytes. The explicit
`original_unclaimed_805D5E5C` hold remains unclassified in the current
reporting tool: it assigns source-less automatic data pools to `game`, but
has no per-unit category override for explicit source-less holds. Therefore
the game-category data denominator changes from 1,720,430 to 1,720,426 bytes,
while its matched data rises from 1,431,806 to 1,431,810 and linked data from
1,149,958 to 1,149,962. The game percentage change includes this four-byte
reclassification and must not be presented as additional recovery.

The four unclassified bytes remain unmatched, original-provided and included
in the global total and strict raw-address coverage checks. Preserving their
old category would require a reporting-tool change or an artificial source
configuration entry; neither is introduced in this narrowly scoped recovery.
The measured source gain remains exactly four bytes.

## Validation

- Unchanged baseline and candidate full native builds used the pinned installed
  toolchain and `/tmp/pso-decomp-full-build.lock`, with Ninja limited to two
  jobs. Both reproduce DOL SHA-1
  `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- `tools/check_pr.py --no-build` passes against the fresh unchanged-main
  report. Matched data rises from 1,472,575 to 1,472,579 bytes; source-linked
  data rises from 1,190,727 to 1,190,731. Code, function and total data
  counts are unchanged, as are source-bearing and linked-unit counts. The
  explicit original-only hold adds one raw report unit. The retention list adds only
  `TLanguage__read_cursor`; the linked-unit list does not change.
- A strict raw-report comparison, without the ordinary padding-loss allowance,
  retains all code/data/function address coverage, exactness and source-linked
  extents. The original-only neighboring word appears in the final report
  with no exact-data score and no source-link flag.
- The reader's complete 856-byte `.text` and all 54 normalized text
  relocations are identical to both current main's source object and the
  freshly split original target. Original and compiled `.sbss` are both
  four bytes, aligned to eight. No function becomes newly matched.
- Linked-unit, retention, porting-exception inventory and whitespace checks
  pass. No exception, compiler profile, handwritten table or assembly is
  added.
