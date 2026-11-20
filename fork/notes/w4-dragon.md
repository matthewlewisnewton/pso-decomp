# w4-dragon: pso/boss/goldragon/TBoss8Dragon.cpp

## Stage 1 (done): members and names
- The 41 action functions (802F4B90..802FA478, listed in remaining-renames-per-unit.json) are now
  `TBoss8Dragon` members `void name(u32)`, named as in the fork (`fn_XXXXXXXX`, `action`, `action_17`,
  `update_wander_state`, `handle_*_state`, `state_*`). Bodies keep a local `arg0` alias of `this`.
- The hand-written vtable/record overlay in the .cpp still refers to them by mangled symbol through
  `extern "C"` declarations of the new names (no overlay change otherwise).
- Also renamed: vfunc_44..50 -> apply_poison_status ... clear_harmful_statuses (802FDE68..80, member
  functions also defined in TBoss8Dragon_802FDDD4.cpp), update_colliders -> vfunc_88 (member), 802F4360
  -> vfunc_105__12TBoss8DragonFv, 802F4380 -> render__12TBoss8DragonFv, TBoss8Dragon__ct ->
  __ct__12TBoss8DragonFP7TObjectPv (still a free function).
- Conversion regressed four functions until their local aliases matched the fork's: fn_802FA478 uses
  `this` directly; handle_leap_state and fn_802F8F88 declare `f32 *d;` before the `u8 *arg0` alias;
  fn_802F9A4C aliases as `TBoss8Dragon *`.
- Not renamed (fork wins in the tsv but out of this unit's reach or needs a signature change):
  802F3D18 (receive_direct_attack, signature differs), 802F45A0 (update_camera_script takes NJS_OBJECT*),
  8002AE5C/8002AE64 (MaterialColorFade / TObjMotion classes), 8007E1F8..8007E6C4 (TObjBoss2Tunnel and
  AccelerationCurve, other units), 800B9E84, 8007EBB4, 803D8960 (matrix_mult_vec_array; mult_vec_array
  is spelled in ~20 files), 80541E18. 802F4B90.. etc. where both names were placeholders: fork's mangled
  form used since it is what makes them members with the (u32) signature.
- Same-name members with a different signature (action, handle_walk_state, ...): fork's `FUl` form used.

## Stage 2: dispatch_action at 99.97%
- `TBoss8Dragon::dispatch_action(u32, s32)` is the fork's body. For the code to match, the function
  must sit in source between the head of the hand-written lbl_804E5014 blob and the bezier tables:
  the compiler emits 41 12-byte records (@16..@56) then the 0x210-byte `actions$15` storage in .data,
  and the original has them at .data 0x490 and 0x67c from the unit start. lbl_804E5014 is now only
  its first 33 words, and the bezier arrays and __vt__12TBoss8Dragon are defined after the function.
- symbols.txt: lbl_804E4D9C shrunk to 0x2FC, @16..@56 and actions$15 added as locals at
  0x804E5098.. and 0x804E5284.
- Remaining 2 instructions (lbz/stb of the init guard): our object names it `init$57`, the target's
  symbol is `init$57_805D69BE` because 0x805D69BE is not in this unit's split. Claiming sbss
  0x805D6988-0x805D69C8 (or 0x805D69B0-0x805D69C8) for the unit fails in dtk with
  "Cyclic dependency ... TBoss8Dragon.cpp -> TBoss8Dragon_802FDDD4.cpp": the next unit (802FDDD4)
  owns .sbss 0x805D6980-0x805D6988 (lbl_805D6980/84, written by its __sinit), which precedes ours in
  sbss order but follows ours in text order. In the original those floats and the guard belong to one
  object, so the unit boundary at 802FDDD4 is the blocker (the fork has one unit, which
  includes clone_node_tree and the __sinit). Blocked on unit boundaries.

## Stage 3: not attempted
- Not exact (dispatch_action 99.97%), so the link scan does not list it. Also .data (39.8%) and
  .sdata2 (23.7%) still differ; the .data vtable is the hand-written overlay.
