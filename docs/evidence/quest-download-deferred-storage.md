# Quest download slot storage

`quest_download_slot_chain_table` (`QuestDownloadSlot[80]`, 2,240 bytes at
`0x80595998..0x80596258`) is defined in `QuestDownloadBuffers.cpp`, in the BSS
run `0x8058DE08..0x80596668`. There is no `QuestDownloadSlots` unit.

## Why this is not its own translation unit

`symbols.txt` places four objects back to back:

| Object | Address | Bytes | Ends at |
| --- | --- | ---: | --- |
| `lbl_80595008` | `0x80595008` | `0x990` | `0x80595998` |
| `quest_download_slot_chain_table` | `0x80595998` | `0x8C0` | `0x80596258` |
| `lbl_80596258` | `0x80596258` | `0xC` | `0x80596264` |
| `quest_download_text_buffer` | `0x80596264` | `0x404` | `0x80596668` |

Nothing is left between them. Each address is 8 modulo 16, the same alignment
as `quest_download_block_pool` at `0x80596668`. That is the provider BSS
section alignment (8). It is not padding that would show a new file starting
at `0x80595998` or `0x80596258`.

Both `TQuestVmDownLoadServer_803E5668` and `TQuestVmDownLoadServer_803E6970`
reference the slot array, the prefix, and the text buffer with
`R_PPC_ADDR16_HA` / `R_PPC_ADDR16_LO`. Under the current splits neither object
defines those symbols. Reference locality does not put the array in a third
file by itself.

## Why the provider unit does not own these bytes

`TQuestVmDownLoadServer_803E6970` already defines `quest_download_block_pool`
at the start of its `.bss` (`0x80596668`). The matching
`init_block_free_list` (208 bytes, exact) takes that pool's address from the
section symbol `...bss.0` (`R_PPC_ADDR16_HA` / `R_PPC_ADDR16_LO` at the
function's `lis` / `addi`). CodeWarrior emits that form when the object is the
first object in the translation unit's BSS.

Compiling the same function with `lbl_80595008`, the slot array, `lbl_80596258`,
and `quest_download_text_buffer` defined ahead of the pool (GC/1.2.5, the
unit's real compiler and flags) keeps every other function the same size and
grows `init_block_free_list` from 208 to 212 bytes. The new instruction is
`addi r0, r3, 5728`, the distance from `...bss.0` to the pool. That is no
longer the original function. Those four objects are therefore not members of
this provider BSS. The pool stays offset 0.

## Where the bytes go

They continue the data-only BSS that `QuestDownloadBuffers.cpp` already
starts at `0x8058DE08`. The six cache objects end at `0x80595008`, which is
`lbl_80595008`. GC/1.2.5 lays the four following objects out at the symbol
addresses above and makes the section `0x8860` bytes, 8-aligned, with no
padding. The provider's text is unchanged because those symbols stay extern
there.

The workspace, prefix, and text buffer are the existing byte extents. This
does not assign them a query struct. The slot array is the canonical
`QuestDownloadSlot[80]` already required by `init_entries` (`sizeof` `0x1C`,
eighty records, `0x8C0` bytes). C linkage keeps `quest_download_slot_chain_table`
unmangled, matching the declaration the callers already use. The name is the
one stored in `symbols.txt` since `fa62488f775f2ed7bb32a8b391ae967120e94922`;
it is not a string from the executable.
