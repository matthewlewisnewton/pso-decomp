# w3-audio notes

## pso/unk/text_803CC294.cpp: ADXF_ReadNw32 (803CCB98), not matched (96.2%)
- Target keeps `lis r9, lbl_8047C818@ha` hoisted to the prologue and uses r4 = base + 0x244/0x26C/0x298/0x2C0 for the four
  error messages (fork: `const char *messages = lbl_8047C818;` as extern char[]), and holds &lbl_8057B7B0 in r31.
- Tried: fork-style open-coded history blocks, a `messages` local from the first message literal, a defined
  `const char lbl_8047C818[]`, a struct view of lbl_8057B7B0, inlining the read-start code (as the fork does) instead of
  read_sj32_803CCB98, declaring `sj` mid-function. Each stayed short of a match (string base still sinks to first use, frame 0x30
  instead of 0x20, saved regs r25..r31 instead of r26..r31). Reverted.
