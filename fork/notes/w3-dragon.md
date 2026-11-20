# w3-dragon: Gol Dragon units

## pso/boss/goldragon/TBoss8Dragon_8002CC48.cpp: linked
- 8002E2D8: naming-three-way.tsv decision is upstream (`__ct__13TObjBoss1RockFP7TObjectPC3VecPC3Vecl`); nothing to do.
- The unit's whole body was replaced by the fork's current version (kept this tree's include
  list, the extern "C" declaration block, the s32 returns of sub_8002DAEC/sub_8002DB04, and
  `new TObjBoss1Rock(...)`). Reason: with the old `lbl_805D81xx` externs the new function
  matched in code but the constants were not the compiler's own, and the sdata2 pool order
  (2.0, 8.0, 3.05e-5 ... 16.0 at 0x805D81D4 as a defined global, then 1024.0) only comes out
  right with the fork's literal expressions and definition order (reversed definitions with
  `#pragma defer_codegen on`, then `lbl_805D81D4 = 16.0f`).
- Function 8002D5F8 needed `#pragma opt_propagation off` around it (from the fork).
- Grid_8002DB7C's object needs a 4-byte tail (allocation is 0x68); Ent_8002CE78 has `s32 state`.
- symbols.txt: sdata2 0x805D8178..0x805D81F8 renamed to the compiler's `@N` locals (0x805D81D4
  stays `lbl_805D81D4`, global, defined in the unit), rodata 0x804355D0 is `@150`.
- splits.txt: unit now claims `.data 0x80482048-0x80482078` (the two MokoHill vtables the
  unit defines) and `.sdata2 0x805D8178-0x805D81FC`. The original has a 4-byte zero pad at
  0x805D81FC before the next unit at 0x805D8200; ending the split at 0x81FC lets the link
  scan accept it, DOL hash is OK.

## pso/boss/goldragon/TBoss8Dragon.cpp: not done (802FA4E4)
- 802FA4E4 is the fork's `TBoss8Dragon::dispatch_action(u32, s32)`: a function-local
  `static DragonAction actions[44]` of pointers to member functions, initialised at run time
  (44 member-pointer records, 1,484 bytes). It takes `&TBoss8Dragon::fn_xxx` of about 40
  action functions.
- Here those actions are extern "C" free functions with other signatures, TBoss8Dragon.h has no
  declarations for them, and the vtable is a hand-written overlay in the .cpp. A member-pointer
  table cannot be written without making all of them real members (which needs the fork's
  renames, e.g. fn_802FA478__12TBoss8DragonFUl for TBoss8Dragon__sub_802FA478) and without
  hand-written pointer records, so I did not attempt it. Blocked on class members/renames.
- No fork-wins renames were applied. All 63 listed under "pso/boss/TBoss8Dragon.cpp" in
  remaining-renames-per-unit.json are left for a later rename batch.
- Fork source: `git show origin/main:src/pso/boss/TBoss8Dragon.cpp`, line 4216.
