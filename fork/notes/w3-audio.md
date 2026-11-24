# w3-audio notes

## pso/unk/text_803CC294.cpp: ADXF_ReadNw32 (803CCB98), not matched (96.2%)
- Target keeps `lis r9, lbl_8047C818@ha` hoisted to the prologue and uses r4 = base + 0x244/0x26C/0x298/0x2C0 for the four
  error messages (fork: `const char *messages = lbl_8047C818;` as extern char[]), and holds &lbl_8057B7B0 in r31.
- Tried: fork-style open-coded history blocks, a `messages` local from the first message literal, a defined
  `const char lbl_8047C818[]`, a struct view of lbl_8057B7B0, inlining the read-start code (as the fork does) instead of
  read_sj32_803CCB98, declaring `sj` mid-function. Each stayed short of a match (string base still sinks to first use, frame 0x30
  instead of 0x20, saved regs r25..r31 instead of r26..r31). Reverted.

## pso/network/TLobby_80429598.c: TLobby__sub_80429648 (80429648), not matched (95.0%)
- Porting the fork's body to C (fork declaration list with its padding slots, `#pragma opt_propagation off`, locals
  scoped inside the loop body, struct view `ExiPacketDescriptor` of lbl_805D7C5C, volatile header/flags copy) reaches 96.7%:
  frame 0x50 and all stack offsets match. Remaining difference: the descriptor length halfword. Target does
  `extrwi r3,r5,4,24` then `rlwimi r3,r4,4,20,27` (desc[2] inserted into the high nibble); the compiler here emits
  `clrlslwi r5,r5,24,4` then `rlwimi r5,r6,28,28,31`. Swapping the operand order, `+` instead of `|`, u8/u32/s32 `high`,
  an `(s8)` cast on desc[2], and `#pragma cplusplus on` around the function did not change it. The fork matches this
  function as C++; the unit here is C.
- Remaining renames (12 symbols) were not applied: the unit cannot link yet, and no name is needed for matching.

## Matches and link decisions (for the record)
- 803CA8B4 (AdxStreamRuntime): needed `#pragma opt_common_subs off` before the prep/dec/end inlines (the fork had it).
- AdxStreamRuntime link: upstream folded five original objects into one unit. AdxManager's first reference into .bss is
  anchored at `...bss.0`, which has to be adxm_worker_thread (offset 0), so the stream read-request table and decoder
  channel pool (0x80575140..0x80575E80, from the original AdxStream/AdxExpand objects) were moved by .bss range to
  AdxEncoder.cpp (splits.txt: AdxEncoder .bss end 0x80575E80, AdxStreamRuntime .bss start 0x80575E80) and are defined
  there as raw arrays (u8[0xA00], u8[0x340]); AdxStreamRuntime.cpp keeps `extern` declarations. Text boundaries unchanged.
  Two compiler double constants became `@358`/`@705` (symbols.txt, scope:local). Fourteen unreferenced functions of the
  unit were added to config.yml force_active by hand (mwld dead-strips them otherwise: 803C8594, 803C9104, 803C9284,
  803C92B4, 803C9350, 803C9358, 803C94D8, 803C96A8, 803C96B0, 803C96E0, 803C96F0, 803C977C, 803C9C84, 803CBA18).
- 803CE544 stays `TLobby__sub_803CE544` (naming table: upstream wins); cvFsEntryErrFunc not applied.
- AdxEncoder 803C7978: fork's local declaration order in encode_channels and the ternary for `n`.
- text_803CE568: lbl_8047CF30 (0x87C) is now `@stringBase0` data:string_table (precedent at 0x8047BAB0); split claims
  .sdata2 0x805E0DA0-0DA4 (lbl_805E0DA0, made `extern`) and .rodata ends at 0x8047DAB4 (the 4 trailing zero bytes are
  alignment padding; lbl_8047DA48 shrunk 0x70 -> 0x6C). The fork also claimed 0x805E0DA4..DAC; not needed here.
- ModemRuntime: the two setup command strings are a `static char [][12]` table (24 bytes in .data); `dolphin/os.h`
  replaced by OSInterrupt/OSThread/OSCache/OSUtil (os.h pulls in sqrt weak statics in .sdata2); 17 unreferenced split
  globals localized with tools/localize_split_globals.py.
- TAdPlayerLoadGC_803F18B8 803F1908: fork's loop-invariant locals (slot_name, stat_game_name, stat_company,
  ticks_per_second) in this order. Link: PSO_SDK_COMPACT_MATH defined around the headers (as AdxEncoder does) so sqrt
  statics stay out of .sdata2; lbl_805E10E8 placed with `__declspec(section ".sdata2") extern`, split claims
  .sdata2 0x805E10E8-10EC. 803F282C untouched (keeps this tree's name).
- TQuestVmDownLoadServer 803EA1A8: opt_propagation/opt_common_subs/opt_lifetimes off, slot addressed by byte offset,
  second borrow of the head pointer, text/pos loop pair, function-level local order as in the fork, plus an unused
  `volatile s32 frame_pad[2]` that gives the original's 0x30 frame (the fork reaches the frame another way).
  803EC284: `saved_mode` copy with `mode` reused as the group count, and a depth-2 inline region (next group / count /
  advance) as in the fork.

## Overseer: 803EA1A8 match withdrawn

The 803EA1A8 match used an unused `volatile s32 frame_pad[2]` plus three optimisation
pragmas to reproduce the 0x30 frame. The fork matches the same function with no padding
(`git show origin/main:src/pso/misc/TQuestVmDownLoadServer_803E6970.cpp`, the insertion loop is
written out instead of calling `merge_sorted_nodes`). The function is back to its earlier
form (99.45%) and is queued for a port of the fork's body. 803EC284 stays matched.
