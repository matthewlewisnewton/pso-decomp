# PR #308: typed file handles and quest filenames

Provenance: `gpt-6.1-sol full-perm r5 on ecc94601a PR#308`.

## Integration

Merged `origin/main` at `6c871bfd3` with a non-fast-forward merge, resolving
the tunnel consolidation, filename declarations, and exception inventory by
content. The merge is `9086a3c61`. Its build and `check_pr.py --no-build` passed
before it was pushed.

## Narrow API recovery

`TLobby::get_file_size(const void *)` uses an opaque `AdxfHandle *` and the
typed C middleware functions `ADXF_Open`, `ADXF_GetFsizeByte`, and `ADXF_Close`.
The handle is no longer a `TLobby` receiver. The other handle operations and
their necessary callers use the same type. The implementation owns the
0x138-byte pool records, with size and byte-size-offset assertions.

The item archive reader has explicit buffer, handle, partition, sector-count,
and mode fields at offsets 0, 4, 8, 0xC, and 0x10. Its open, close, read, and
status operations belong to `ItemArchiveReader`. The archive-loading operations
belong to the existing `TUnk_8049F42C` reader-derived class rather than the
unrelated `TItemLoad : TObject` task. This removes the handle/sector accesses
through `TObject` fields. The dependent symbol and force-active names were
updated together.

`TScene::update_lobby_scene(const void *)` retains its static filename API.
Its consolidated tunnel caller passes the filename directly.

## Quest string path

`QuestVmArgument` is a per-slot union. Argument opcodes determine the active
alternative: `arg_pushs(const char *)` writes `string`, numeric push opcodes
write `integer`, and the GBA disk opcode reads `string`. The integer conversion
accessor reads only the numeric alternative; it performs no pointer conversion.
`QuestVmContext::args` has the same union element type as the running globals,
so the existing context copies preserve the argument representation.

The filename now travels from the string getter through `arg_pushs`, the saved
argument slots, the GBA disk opcode, `TLobby::send_data`, and the static scene
size query without an integer-to-filename cast.

The first union experiment used an assignment operator for numeric pushes and
implicit scalar reads everywhere. It produced eight exact-function regressions.
Direct writes to `integer` fixed the four push regressions. Explicit numeric
member reads in `get_item_info`, `give_s_rank_weapon`, `set_mainwarp`, and
`npc_param` fixed the remaining four. No register-coloring local or pragma was
needed. The string-push symbol and opcode-table relocation were renamed too.

## Validation

With the integrated main and these API changes, objdiff reports:

| Function / section | Bytes | Match |
|---|---:|---:|
| `TLobby::get_file_size(const void *)` | 84 | 100% |
| `TScene::update_lobby_scene(const void *)` | 32 | 100% |
| `ADXF_GetStat` | 64 | 100% |
| `ADXF_GetFsizeByte` | 60 | 100% |
| `ADXF_GetFsizeSct` | 60 | 100% |
| `ADXF_Stop` | 476 | 100% |
| `ADXF_Close` | 720 | 100% |
| `ADXF_OpenAfs` | 572 | 100% |
| `ADXF_Open` | 540 | 100% |
| `qst_op_arg_pushs(const char *)` | 32 | 100% |
| `qst_op_prepare_gba_rom_from_disk` | 72 | 100% |
| Quest handlers `.text` | 51,176 | 100% |
| Quest handlers `.data` | 88 | 100% |
| Quest handlers `.bss` | 1,392 | 100% |

The post-merge and API-recovered builds have the same 4,163,792 exact code
bytes and 3,549 linked units. The existing pre-PR baseline is preserved.
Against that baseline, `check_pr` reports zero exact-function regressions and
all 3,549 linked units exact. The lower unit count versus that older baseline
comes from main's consolidations; no unit was unlinked for this recovery.
The DOL SHA-1 check passes. Both targets and the GBA runtime remain linked.

`init_from_id_lists` walks each id list with a pointer and a caller-born
index. That body scores 100% (780 bytes, 195/195 instruction words) and
`TLobby_8001EF5C` links. The reference-counter shape is not part of this work.

## Final main refresh

Main advanced during the session when #322 landed. A second non-fast-forward
merge integrates `7026cbad6`, preserving its recovered quest-list implementation
and typed temporary-buffer APIs alongside the opaque ADXF handles and filename
variants. The combined synchronous stream reader accepts `AdxfHandle *` and a
byte-buffer destination. Regenerated force-active metadata removed one stale
entry; the exception inventory was regenerated again.

Final required checks pass: `ninja -j8`, `check_pr.py --no-build` (zero
regressions, all 3,549 linked units exact, force-active current), and
`list_port_exceptions.py --check`. The refreshed main brings the total to
4,164,192 exact code bytes and 1,454,863 exact data bytes. The original baseline
and DOL SHA-1 are preserved.


## Current-main refresh and buffer-copy boundary (2026-11-09)

PR head `d77cdec95ecf64de21723acdf1aec09c809a0322` already contained
main `ab62e8cf7`. Normal merge `8b57f8b163c5f18d450ca43b083f84e4e5d5d602`
adds current main `6daa19a11db97b1b8222fd2665eba485ed3a74a4` without conflicts.
The slice remains useful for the typed APIs above, even though main already
has the exact linked bytes of `TLobby_8001EF5C`. The combined upstream-history
merge is still PR #353; this source slice does not clear its separate review hold.

The wrapper at `0x803DE7BC` is a buffer operation: it passes r3/r4 to `memmove`
and scales the r5 word count by four. Its callers supply download parameter
storage, mail/card arrays, chat-log entries, and an asynchronous read buffer.
None supplies a `TLobby` object. It is now the free function
`move_words(void *dst, const void *src, s32 n)`, with the corresponding symbol-map
entry. All nine source callers use that declaration. The existing scheduling
and peephole pragmas are unchanged. The halfword wrapper is unchanged.

Both download constructors pass destination `entry + 0x44` and count 8, so the
copy spans 0x20 bytes. Their local entry descriptions now represent that whole
span instead of an 8-byte array followed by unnamed storage. The total entry
size is still 0x68 and the callback is still at 0x40. Callback-specific structures
may describe only the used prefix; this change preserves the original copy
length and does not infer fields for the unused bytes or change caller payloads.

Fresh candidate build results with the pinned project tool versions (DTK 1.8.4,
objdiff 3.6.1, CodeWarrior GC/2.6 for these units):

| Unit / function | Code bytes | Exact |
|---|---:|---:|
| `TLobby_8001EF5C` | 6,460 | 19/19 functions |
| `init_from_id_lists` | 780 | 100% |
| `create_file_load_entry` | 252 | 100% |
| `create_named_entry` | 232 | 100% |
| `move_words` | 36 | 100% |
| `TLobby_803DE778` | 104 | 3/3 functions |

The target unit's 48 data bytes remain exact. The full candidate DOL matches
SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Link checking passes for all
3,570 units, force-active is +0/-0, and the porting-exception inventory check
passes. A fresh build of main `6daa19a11` also matches the original DOL.
`tools/check_pr.py --no-build` against that report passes with zero address-based
regressions: matched functions 27,364 -> 27,364, matched code 4,180,388 ->
4,180,388 bytes, matched data 1,468,463 -> 1,468,463 bytes, linked code
3,636,556 -> 3,636,556 bytes, linked data 1,165,731 -> 1,165,731 bytes, and
linked units 3,570 -> 3,570. There are zero newly exact functions. The main
baseline's own link/retention and exception checks also pass. The generated
Ninja link inputs name the compiled source objects for the target unit, both
entry constructors, and `TLobby_803DE778`. Build outputs and original inputs
stay local in isolated checkouts.

Remaining boundaries are explicit: the legacy `safe_free(u32)` API and pointer
alignment mask remain; `create_named_object(long)` keeps an unrecompiled caller's
ABI. The screenshot size representation follows current main. No new assembly,
steering pragma, or compiler override was added.
