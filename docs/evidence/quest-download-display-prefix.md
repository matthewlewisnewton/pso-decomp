# Quest display prefix

`lbl_80596258` is defined in `QuestDownloadBuffers.cpp`, not in its own unit.
It sits between `quest_download_slot_chain_table` and
`quest_download_text_buffer`. Those three addresses are consecutive, and the
same 8-byte section alignment continues into `quest_download_block_pool`.
That is not a new file. See
[quest-download-deferred-storage.md](quest-download-deferred-storage.md).

The object is twelve encoded characters.

- `803E5B94` copies `lbl_8047E68C` with `strcpy`. That constant is
  `20 20 8E 63 20 20 20 20 20 20 00 00`: NUL at offset 10, and a zero at
  offset 11.
- `803EB4D4` starts at offset 5 and writes three ASCII count digits (or
  spaces), then passes offset 0 to `803EC95C`, which reads until NUL.
- `803EBEFC` and `803EC460` add 12 and use that address as
  `quest_download_text_buffer`. They do not widen this object.

The linker name stays `lbl_80596258`, the name already stored in
`symbols.txt`. Callers in the provider units still declare `u8[]`; this
definition does not change those function bodies.
