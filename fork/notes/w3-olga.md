# great-merge/w3-olga notes

## Match notes (kept out of source)

- TBoss6Zanzo draw_trail: statement order in the opening assignments decides the register
  assignment: `step = 1.0f / m_28; alpha = 1.0f; frame = ...; end = ...;`, with the quad
  locals (`next_alpha`, colours, positions, quad) declared inside the `else` block and the
  loop counter and per-point pointers declared in the loops/blocks that use them.
- TBoss6Demo11_TYPE1_DEAD constructor: the model/motion/camera tables must be referenced
  by their own symbols, not through the shared `...data.0`/`...rodata.0` base. That needs
  the weak extern declarations (`__declspec(weak) extern const ...`) ahead of the
  definitions for the three rodata tables. The model index is `const s32 index` declared
  inside the `for (s32 i...)` loop; a variable declared outside the loop, or none, loads
  differently.
- TBoss6Type1: the nine small constants (two s8 pairs and seven s32) match only as
  `static const` definitions at the end of the file. Defined `extern` they were emitted
  ahead of the compiler's float constants and the sdata2 order was wrong. The data and
  sbss "missing" symbols were then localised with `tools/localize_split_globals.py`.
- text_8031EF14 spawn_death_debris: needs `mw_version GC/2.0` and `-pooldata=off` in
  `GAME_EXCEPTIONS` (three separate debris templates, `@68`..`@70`, claimed as
  `.rodata 0x804762F0-0x804763D4` in splits.txt). Same switches as the fork.
- TTecGiFoie TUnk_804CC800::run_task: `fp_contract on` and `opt_propagation off` around the
  function, and the zero for `direction.y` bound to a named local before the loop.
  `direction_to_rotation_xz` has to be called by its C++-mangled name from inside the
  extern "C" block. The vtable stays `lbl_804CC800` (naming-three-way: upstream wins).
- PhotonBlastSummon spawn_photon_blast_attachment_effects: effect id/arg1/arg2 are fields
  of a local struct, declared with the rotation array before the loop; `flags` and the
  output angle array are declared inside the loop.

## Skipped

### pso/unk/text_802EDE90.cpp (TBoss7DeRolLeC constructor, 97.4%)
The original constructor addresses the .data tables (movement params at +0x9C, action table
at +0x13C) and the vtable (+0x264) from one base register (`lbl_804E3BF0`). The fork
reproduced that with a hand-written overlay struct and an explicit vtable pointer
store, which CONTRIBUTING.md forbids. Here those objects live outside the unit (no `.data`
in its split), so the compiled constructor addresses each by its own symbol. Other diffs:
float constants `@102`/`@103` vs `lbl_805DEA30`/`lbl_805DEA10` (sdata2 not claimed),
frame size, `TBoss7Joint__ct` vs `__ct__11TBoss7JointFP7TObjectUssP3Vec`, `fn_8035A860`
vs `__ct__13TUnk_804F1C58FP7TObjectPv`. Not attempted further; needs the data split
reshaped and a vtable-owning unit decision.

### pso/object/TObjDFDemo4.cpp (constructor 8004F6AC, unit TObjDFDemo4_8004F6AC.cpp)
Same obstacle: the original constructor uses one `.data` base (`lbl_80485720`) for the
motion tables and `__vt__11TObjDFDemo4` (+0x44), plus `dfdemo4_strip_nodes` and the two
camera initialisers in .rodata and float constants in .sdata2. None of it is in this
unit's split, and the vtable is only emitted by the compiler where the class's virtual
functions are defined together; the destructor is in a different unit here
(TObjDFDemo4_8004F5F8.cpp, which stores the vtable pointer by hand). The fork matched it
only as one combined unit written last-defined-first. Not attempted: no way to get the
shared base without either moving split boundaries or hand-writing the vtable.
