# units-b notes

## 0x803F3BF8 and TAdPlayerLoadGC_803F339C
- Upstream's unit 339C ended at 0x803F3CF4, but the ntInf library starts at 0x803F3BF8
  (the fork's NetworkConfigLifecycle begins there). In the mcfs library (GC/1.2.5) the
  function came out with an unaligned frame (85.9%); with GC/2.6 it is 100%.
  Fix: moved the boundary in splits.txt (339C ends 0x803F3BF8; the 803F3CF4 unit now
  starts at 0x803F3BF8, name kept) and moved the ntinf MIDDLEWARE start in configure.py.
- Match notes from the fork: the original aligns the frame to 32 bytes although the body
  has no stack locals; `ATTRIBUTE_ALIGN(32)` on the first parameter reproduces it (same
  as request_network_info_load), with `#pragma scheduling off`. The original retains the
  `backup_mode == 1` check after rejecting nonzero modes.
- Linking 339C needed nothing else once the boundary was fixed.

## TAdTrialModemChkGC_8042E9FC (DOL SHA-1 failure)
- Cause: the unit's first 0x14 bytes are the local `pad_03_8042E9FC_text` (frame-restore
  tail of the previous function's computed-jump exit). Nothing references it, so the
  linker dropped it and the DOL lost 20 bytes. The compiled object was identical to the
  split original (same symbols and sizes); the loss was at link time only.
- Fix: `#pragma force_active on` around it, as the fork did. The two-unit split was not
  the cause; upstream's single unit is kept.
- Fork comment on the function, moved here: the epilogue has no prologue, and no C
  construct produces it (an empty function gives `blr`, a register-hungry one gives
  prologue+stmw+epilogue, statement-level asm gets its own frame; 0/20 MWCC versions
  emit the 20 bytes). The function-level asm from orig_asm is exact on 20/20.
  `static` keeps the symbol local, as in the original object.
