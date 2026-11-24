# great-merge/texlist: set_global_param -> set_current_texture_list

Pure rename of the function at 0x803DA798 (was `TObjFish::set_global_param(s32)`, symbol
`set_global_param__8TObjFishFl`). No compiled object changed; check_pr.py PASS, psov3.dol OK,
all counts equal to baseline.

## What was done
- Added `include/pso/system/CurrentTextureList.h` (fork's declaration, extern "C").
- symbols.txt renamed; TObjFish.h declaration removed. config.yml has no mention of the old name.
- The definition in `src/pso/unk/text_803DA798.cpp` is now `s32 set_current_texture_list(GinjaTextureList *list)`.
- 540 call sites `TObjFish::set_global_param(ARG)` became
  `set_current_texture_list((GinjaTextureList *)(ARG))` (script, parentheses matched properly,
  scratch only, not in repo). Include inserted alphabetically among `"pso/..."` includes
  (before the first greater path, else after the last one, else after the last `#include`).
  TObjFish.h includes were left alone.
- Dropping the cast on `...texlist` arguments was tried; every such file failed to compile
  (the fields are not GinjaTextureList *), so all calls keep the cast.

## Hand-mangled references (29 files)
Old files declared `set_global_param__8TObjFishFl` locally with varying signatures.
- 7 files where every use is a plain one-argument call: local decl/#define/#undef removed,
  call converted to the header form, header included.
- 18 files with zero-argument calls, function-pointer casts or macros: converted to a pure
  identifier rename. They keep their local `extern "C"` declaration under the new name and
  do NOT include the header (the header's prototype would conflict). Converting these to
  the header form changes codegen: a cast function-pointer call compiles to
  lis/addi/mtctr/bctrl instead of bl (TObjCamera::render and
  TObjContainerJungEx::vfunc_81 regressed).
  Files: Boss7DeRolLeCBehavior, TBoss4Type1, TObjCamera, TObjEneBm3FlyNest,
  TObjEneMe1Gee_NEEDLE_802A4BB8, TObjGyaranzoMissile, TObjBigTuitate, TObjDoaEx01, TButterfly,
  TObjFish, TODoorFourLightSpace, TObjLaboDesignBase, TObjLaboMapWarp, TObjPlayer_8023E480,
  TObjPlayer_8033E910, TSceneSora, TAdMultiConfirmGC_802E03D0, text_80081BB0.
- 4 files mix both kinds: TObjEneRe7Berura (two-argument call kept as a function-pointer
  cast call through the header), TObjEneSlimeTailAttack, TObjContainerJung (zero-arg call
  after `TObjFish__sub_8001EDB0` / `TObjContainerJungEx__sub_8018D900`, both of which return
  the texture list in r3, merged into `set_current_texture_list((GinjaTextureList *)(that call))`),
  TWindowSubStatusDisp_8036D774 (zero-arg call after load_gvm_texture_file kept as a cast call).
  Those four include the header.
- `TODoorJungleMain`: result used as an argument to push_matrix, so the call is wrapped in
  `(void *)` to keep the object identical.

Follow-ups: the zero-argument sites really pass through r3 from the previous call
(`TObjFish__sub_8001EDB0` returns the model's texture list); once that function is renamed
they can be converted to the nested form and the 18 files can use the header.
