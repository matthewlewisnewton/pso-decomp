# w3-enemy notes

## MaterialOpacityFade rename (TUnk_80494938)
- Whole class renamed, header moved to include/pso/render/MaterialOpacityFade.h. Members renamed to the
  fork's names where naming-three-way.tsv lists them: sub_800D741C -> update_alpha, advance_timer ->
  advance_to, set_field_10 -> set_rate, init_death_params -> start_fade_out (these three were declared on
  TObjEneMe3SinowZoa here; they are now MaterialOpacityFade members, callers cast accordingly).
- Not renamed: 800D7478 copy_position_vector__18TObjEneMe3SinowZoaFPv (fork: set_color__19MaterialOpacityFadeFPC8NJS_ARGB).
  Written as a MaterialOpacityFade member it compiles to 70% (the four channel loads are hoisted); the
  original reloads q->a for the second store. Tried NJS_ARGB member stores, struct copy (calls copy_argb, 0%),
  raw offset casts through void *, a local struct of pointer/u16 slots. Kept as a TObjEneMe3SinowZoa member.
- Not renamed: 800D72A4 TObjEneMe3SinowZoa__sub_800D72A4 (fork: has_partial_opacity__19MaterialOpacityFadeFv);
  it is a free function with extern declarations in four files, so left alone.
- ninja did not recompile units that reach the renamed header only through another header until their sources
  were touched; a rename of a header needs `touch` on the dependents.

## pso/enemy/panarms/TObjEnePanarms.cpp
- 800E252C (the constructor) matched by writing `(void *)&objectState` instead of `(void *)(s32)&objectState`.
- Not linked. The scan wants (a) the function-local statics panarms_sound_effect_pair, TObjEnePanarms__sound_ids,
  panarms_particle_frame_window and their init flags named as the compiler's `name$NNN`/`init$NNN` locals, and
  (b) function order to match the split object. (b) is the real blocker: in the split, __sinit_TObjEnePanarms_cpp
  (800E2964) is followed by ten small functions (clear_motion_flags .. ModelNodePositionCapture::clear, in
  reverse of this source's order), i.e. they come from separate source files merged into this split. One TU always
  emits __sinit last. Marking them `inline` makes the compiler drop them (regression). Needs the split cut at
  0x800E2DE4 into separate units, which this task does not allow.

## pso/enemy/gibbles/TObjEneGibbles.cpp
- Blocked on cw_align: .sdata2 starts at 0x805DE87C (not a multiple of 8). Also missing
  TObjEneGibbles__data_80472790 (rodata double) that would need scope:local.

## pso/enemy/gyaranzo (800D2A68 spawn_hit_debris)
- With the fork's `#pragma pool_data off` and constant initialisers for the three TObjChipParams (models via
  gyaranzo_bml_resource inline, not a local), the function reaches 99.73%; the only remaining diffs are the
  relocation names (@218-@220 against lbl_8043C278/C2C4/C310). It cannot reach 100% nor link: the target's
  .rodata holds the three spawn_hit_debris templates (C278..C35C) then shed_armor's (C35C) then volley data
  (C3A8..), i.e. reverse of function order, while the compiler pools them in function order
  (volley, shed_armor, spawn_hit_debris). The split would also need .rodata to start at 0x8043C278.
  Restored to upstream's version (82.8%).
