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
