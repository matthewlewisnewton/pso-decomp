# great-merge/w3-misc notes

## pso/item/TItemList.cpp
- The unit's original object has no .data; __vt__9TItemList sits in unclaimed data. A `.data` claim for it makes the
  link order cyclic (TPlyItem data follows it). The unit instead defines the deleting destructor by its C symbol
  `__dt__9TItemListFv` against the external vtable (as the fork did), and `~TItemList()` is only declared.

## pso/object/trap/TOMineTrap_8016F6F8.cpp
- Needs `-inline on` (run_task's mode-4 strike helpers expand inline) and `-fp_contract on` (three fmadds), and
  `TOBJECT_OUT_OF_LINE_HELPERS` so queue_destruction stays a call under -inline on.
- The constructor needs `#pragma opt_common_subs off` and the `type * 0x50 + (idx * 0x14 + id)` form for m_37e.
- The double constant at 0x804421F8 is claimed as .rodata in the split (symbol made scope:local).
- vfunc_86 has to precede run_task in source, otherwise the link scan reports a function order difference.
- The rename of TOMine__ct raised only __ct__10TOMineTrap (98.66 -> 98.68); run_task did not change at that point.
- The 0.0f at 0x805DB85C is not owned by this unit: text_8016F1C0's .sdata2 split starts after it, and claiming it here
  makes the link order cyclic. It is only referenced as an external, so no claim was needed.

## pso/effect/TEF_LensFlare.cpp
- render needs `#pragma opt_propagation off`, `-fp_contract on`, the LensFlareSprite/colour layout and the byte
  copies of the colour word (`__memcpy`), taken from the fork. Element table index is 9 + the first word.
- Data now defined in the unit: class-name string and pointer, the ten-record descriptor table, the 0,0,-1 vector in
  .rodata. The fifteen .sdata2 literals became compiler locals (@63..@77, scope:local).

## pso/unk/text_8020B5CC.cpp
- TLobby__sub_8020B5CC: the fork's loop structure. Header copy must be a different struct type from the buffer
  (AreaSetFlagsHeader base) or the compiler merges the two pointers. Names kept as in this tree (bswap_4_words,
  safe_free ...FUl); naming-three-way.tsv has no row for 8007EBB4.

## pso/unk/TLobby_802409AC.cpp (NOT linked)
- calc_sound_spatial_params now matches: `#pragma opt_propagation off`, `#pragma opt_lifetimes off`, the camera held
  in a `const TCameraCtrl *` for the pan computation, `(s32)yaw + 0x4000` form.
- Link scan reasons: eight sdata2 constants (0x805DC9E0..9FC) and the double at 0x8044E5C0 are not defined by the
  unit; `.ctors` is empty because the fork builds the guild-card record arrays as global objects with a constructor
  (LobbyGuildCardRecord, include/pso/misc/LobbyGuildCardRecord.h and TLobby_802409AC_tail.h in the fork) so the
  compiler emits the static initializer, whereas this tree has a hand-written construct_entry_arrays; and the
  function order differs. Needs the guild-card record class, namespace-scope const f32 constants and the
  construct_entry_arrays symbol renamed to the compiler's initializer name. Not attempted.

## pso/ui/charcreate/TObjCMName.cpp (NOT linked)
- TObjCMHairMenu::render matches with the fork's body (declaration order of the shared values, float temporaries).
- Link scan: about 130 sdata2 constants, several data tables (lbl_804DBC0C ... lbl_804DBD18), vtable layout
  (`.data+0x3E0 != .data+0x2EC`) and function order are all missing. This is a full data port. Not attempted.

## pso/object/TObjHMS_EZRope_Player_800FEFCC.cpp / pso/unk/text_800FF580.cpp (NOT matched)
- fn_800FF580 stays at 99.73%: the only difference is the two callee-saved float registers for `len` and `half`
  (target f30 = len, f28 = half; ours the reverse). Tried: moving the half/zero hoists into the loop, declaration
  and assignment order permutations of half/zero/reach/d/best, the fork's loop shape with clearance computed per
  sphere, literal-in-loop forms. None changed the allocation. Restored to the original source.

## pso/item/TItemAttackCol.cpp
- Constructor added; TItemAttackCol's fields are typed (header taken from the fork) and the TUnk_804E355C constructor
  is declared. The base class position/yaw are reached through casts of m_24/m_30 because a local reference to them
  costs a register. Linked with .data 0x804E3530-0x804E353C claimed for lbl_804E3530.

## pso/player/TObjPlayer_801C7430.cpp
- Five float literals that were `extern` data references (1.0, 0.04, 0.1, 0.0, 10.0) are written as literals so the
  compiler pools them in the original order; the symbols at 0x805DC360..370 and the double at 0x80447130 are now
  scope:local compiler names (@24, @48, @122, @379, @489, @566).
