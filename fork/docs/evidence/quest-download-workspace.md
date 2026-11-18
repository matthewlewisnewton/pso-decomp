# Quest download workspace

`lbl_80595008` is defined in `QuestDownloadBuffers.cpp`, not in its own unit.
The four objects from `0x80595008` through `0x80596668` are packed against
each other and against the cache BSS that ends at `0x80595008`. Nothing in
the addresses is a file boundary. The provider BSS starts at
`quest_download_block_pool` (`0x80596668`), which `init_block_free_list`
addresses as `...bss.0`. See
[quest-download-deferred-storage.md](quest-download-deferred-storage.md).

The object is `QuestDownloadWorkspace` (2,448 bytes). Its only relocations
are in `TQuestVmDownLoadServer__sub_803EA428` and `__sub_803EA9E8`.

- `803EA428` adds `0x8C0` and reads a halfword at +0, a word at +4 and a
  halfword at +8. It passes that address to `build_item_list`,
  `803F06B8` and `803F0268`.
- `803F03B4` writes 6-byte entries and stops when the index reaches 32
  (`cmpwi r5, 0x20`). Thirty-two entries plus the 14-byte header are 206
  bytes; the `u32` member rounds the object to `0xD0`.
- Both functions also add `0x990`, which is `quest_download_slot_chain_table`,
  the next symbol. `803EA9E8` uses that form for `x15` (`+0x9A5`) and the
  slot words. It does not read the workspace bytes.

No instruction loads or stores `0x80595008..0x805958C7` through this symbol.
Those `0x8C0` bytes stay a leading array. They are not declared as a second
`QuestDownloadSlot[80]`. The linker name stays `lbl_80595008`.
