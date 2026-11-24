# great-merge/w5-n8: fork names that needed source changes

- TObjEneMorfos: update_demo and render_demo are the new virtual slots 105 and 106 (the hand-written vtable in
  TObjEneMorfos.cpp already listed them there). The old `vfunc_83` override declaration was removed, so run_task's
  call to slot 83 goes through `TObjEneDD_ST::vfunc_83`.
- TObjEneMorfos::crosses_heading takes s32 parameters and masks with 0xFFFF; a u16 parameter version compiles
  differently.
- TBoss7DeRolLeC_802ED928.cpp keeps a local declaration, `apply_with_callback__13TUnk_804F1C58FP10NJS_MOTIONf(int, int)`,
  because its only call passes no float and relies on the value already in f1.
- TUnk_804F0C08 and TUnk_804F1A78 constructors/destructors are hand-mangled extern "C" functions, like the other
  item-effect and dragon ones in those files.
- TUnk_804F112C was renamed to TItemSpecialEvent (class, vtable symbol and all member symbols follow from that).
