# Quest download slot storage

This selects one data object from source: the existing
`quest_download_slot_chain_table` symbol, `QuestDownloadSlot[80]`, at
`0x80595998..0x80596258` (2,240 bytes). It targets current `main`. The
six-object cache unit `QuestDownloadBuffers.cpp` (`0x8058DE08..0x80595008`,
29,184 bytes) is already selected there. Consumer function bodies are
unchanged.

The English identifier is the name already stored in `symbols.txt`. It
replaced `lbl_80595998` in the bulk data-symbol rename
`fa62488f775f2ed7bb32a8b391ae967120e94922`. It is not a string recovered from
the executable. Callers that already match, including `init_entries`, use this
symbol, so the definition keeps it.

## What the executable shows

`symbols.txt` gives the object `0x80595998`, size `0x8C0`, between
`lbl_80595008` (`0x990` bytes) and `lbl_80596258` (`0xC` bytes). The address
is a multiple of eight. The record header already requires
`sizeof(QuestDownloadSlot) == 0x1C`, with `entryHead` at offset 8 and
`textHead` at offset `0xC`. Eighty records are `0x8C0` bytes.
`TQuestVmDownLoadServer::init_entries` walks eighty slots and writes those
fields before normal use.

The compiled unit is one zero-initialized `.bss` object: size `0x8C0`,
alignment 8, global symbol `quest_download_slot_chain_table`. C linkage
matches the header declaration and that unmangled name. There is no second
definition, no extra capacity, and no aggregate that includes the neighbors.

## Ownership

`QuestDownloadSlots.cpp` owns only `0x80595998..0x80596258`. The slot records
hold pointers. The nodes those pointers refer to are not stored here, and
this definition does not start their lifetimes.

On current main the whole `0x80595008..0x80596668` span is one automatic BSS
unit, `auto_08_80595008_bss` (5,728 bytes), and none of it is matched or
source-linked. Carving out the slot array leaves that automatic unit at
2,448 bytes and creates `auto_08_80596258_bss` for the remaining 1,040 bytes
(the 12-byte prefix at `lbl_80596258` plus the 1,028-byte
`quest_download_text_buffer`). Those bytes stay original. They are not
claimed as padding, and they are not part of this C++ object. Report unit
count therefore rises by two, while source-selected units rise by one.

Direct references and the `lbl_80595008 + 0x990` index path both land on this
array. Defining the storage does not prove every caller's index domain.
The unresolved workspace, prefix, and scratch contracts stay with those
automatic bytes. Recovering the missing provider functions is required for
linking the mixed provider unit, not for this data object.

## Current-main validation

Baseline is current main `8ed16c860c8ac3130e767cdefc545de18e2f3105`.
`tools/check_pr.py` passed after `ninja -j6`. The DOL matches SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

`tools/report_delta.py` against that baseline:

| Measure | Before | After | Change |
| --- | ---: | ---: | ---: |
| Matched data bytes | 1,434,531 | 1,436,771 | +2,240 |
| Source-linked data bytes | 1,040,383 | 1,042,623 | +2,240 |
| Source-selected units | 3,561 | 3,562 | +1 |
| Source-bearing units | 3,696 | 3,697 | +1 |
| Matched functions | 27,293 | 27,293 | 0 |
| Exact functions gained or lost | 0 | 0 | 0 |

`QuestDownloadSlots` scores 2,240/2,240 data bytes at 100%, with no functions,
and the unit is complete. `link_units.py check` reports 3,562 linked units,
all exact. `link_units.py force-active --check` reports 16,698 retention
entries, with no unreferenced additions and no stale removals. Matched code
bytes stay 4,137,272.

The scan's one exact-but-unlinked candidate is `pso/unk/text_8020B47C.cpp`,
which is already on main and is not part of this change.
