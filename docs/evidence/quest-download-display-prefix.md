# Quest display-prefix source linkage

This selects the existing `lbl_80596258` symbol, `u8[12]`, at
`0x80596258..0x80596264` (12 bytes). It is stacked on #262, which selects
`quest_download_slot_chain_table` at `0x80595998..0x80596258`. The cache unit
`QuestDownloadBuffers.cpp` (`0x8058DE08..0x80595008`) is already selected on
main. Consumer function bodies are unchanged.

`symbols.txt` already names this object `lbl_80596258`, size `0xC`. That is
the placeholder stored for the address, not a new English name, so the
definition keeps it. Existing source declarations use `u8[]`. C linkage
matches that unmangled name. The compiled unit is one zero-initialized `.bss`
object: size 12, alignment 8, global symbol `lbl_80596258`. There is no second
definition and no aggregate that includes the neighbors.

The next symbol is `quest_download_text_buffer` at `0x80596264`, size `0x404`
(1,028 bytes). This unit stops at that address. On current main the whole
`0x80595008..0x80596668` span is one automatic BSS unit. After #262 and this
change, that scratch object is the leftover automatic unit
`auto_08_80596264_bss`. It is not matched, not source-linked, and not claimed
as padding or as a tail of the prefix.

Defining the prefix does not recover provider functions. Callers that use the
prefix address plus 12 stay in the original provider. The 12-byte size is the
exported object. It is not a proof that every reader stops inside it for
arbitrary bytes. No original string or asset is copied into the source.

## Current-main validation

Baseline is current main `b305c93d6315a67533b81580eb8ea019269b31c6`.
This branch contains that main, #262 at
`144047665f23d39f4a4f52d7c7522ec6cae11ef9`, and these prefix and workspace
units. `tools/check_pr.py --no-build` passed after `ninja -j6`. The DOL matches
SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.

`tools/report_delta.py` against that baseline, for the combined stack:

| Measure | Before | After | Change |
| --- | ---: | ---: | ---: |
| Matched data bytes | 1,434,531 | 1,439,231 | +4,700 |
| Source-linked data bytes | 1,040,383 | 1,045,083 | +4,700 |
| Source-selected units | 3,561 | 3,564 | +3 |
| Source-bearing units | 3,696 | 3,699 | +3 |
| Matched functions | 27,294 | 27,294 | 0 |
| Exact functions gained or lost | 0 | 0 | 0 |

The +4,700 bytes are the three BSS objects: #262's slot array (2,240), this
workspace (2,448) and this prefix (12). Against #262 alone, the increment is
the workspace and the prefix: **+2,460** matched and source-linked bytes, **+2**
source-selected units, and **+1** report unit (the 1,040-byte automatic
remainder splits into this 12-byte object and the 1,028-byte scratch unit).
Matched code bytes stay 4,137,724.

`QuestDownloadDisplayPrefix` scores 12/12 data bytes at 100%, with no
functions, and the unit is complete. `link_units.py check` reports 3,564
linked units, all exact. `link_units.py force-active --check` reports 16,698
retention entries, with no unreferenced additions and no stale removals.
Total data bytes stay 1,761,331. The scratch unit remains unmatched.

See [the workspace note](quest-download-workspace.md) for that object's
boundary. Scratch representation and provider-function recovery stay out of
this change.
