# units-a notes

## pso/unk/TLobby_803BFE50.cpp
- Fork comment on publish_decode (now drain in 803C0238): the local declaration order
  (written, used, unused, then source/decoder) gives CodeWarrior the original saved
  registers and chunk slots.
- 803C0238 matched by taking the fork's prepare/publish/advance inlines (counter field
  mapping: fork decoded_samples/decoded_bytes/decode_position = upstream
  output_samples/consumed_bytes/decoded_samples). `int minimum`/`room` locals in the feed step and
  the `decoded_samples < remaining ? ... : ...` ternary in the skip step matter.

## pso/unk/TLobby_803C1A58.cpp
- 803C2388 (AIFF header walk): needs `#pragma opt_propagation off` and
  `#pragma opt_common_subs off`, `s32 form_size` and a local `chunk_bytes`-free form
  (`end = p + (form_size - 4)`), plus READ_LE32/SWAP32 with the high byte shifted as unsigned
  (`(int)((u32)(b)[3] << 24)`, `(u32)(x) << 8`) keeping the native int result.
- 803C3570: needs `opt_common_subs off`, `opt_lifetimes off`, `opt_propagation off`; the
  fork's local declaration order and its `AdxBlockTransferView` layout view (replaces
  Strm_803C1A8C for this function only; Strm_803C1A8C still serves 803C2A00 and others).
  Fork comment: "Keep the high-byte shift unsigned while retaining the native int result."

## pso/render/GinjaMaterial.cpp
- apply_ginja_material_params (803DBE1C): the only change needed was holding the surface
  format as a reference (`const u32 &format = ...->surface->format;`) across the
  GXSetZCompLoc call in the 0x8000 branch, so the surface address stays in a register and
  the format is read after the GX call. Fork comment pointed at
  docs/evidence/ginja-material-recovery.md (fork-only).
- Link: lbl_805E0F68 ({0,0,0,127}, C_803DB9A0) is defined in this unit, in .sdata2, after the
  other uses ("late definition keeps the named load in set_ginja_material_color" in the fork).
  Split changed to .sdata2 0x805E0F68-0x805E0F7C (0x805E0F7C..0F80 unowned padding);
  lbl_805E0F6C/70/74/78 made scope:local, lbl_805E0F78 size 8 -> 4.

## pso/unk/text_80104FCC.cpp
- Upstream could not link it: the .data split started at the jumptable (0x8049EEFC, not
  8-byte aligned). The fork's split starts at 0x8049EED8 and the unit defines the two
  factory tables there (item_pro_create_fn_table[4], item_create_fn_table[5], 0x24 bytes),
  which puts the jumptable at 0x8049EEFC. No cw_align needed.
- The tables must be defined before check_equip_requirements in the source; defined after
  it, the compiler emits the jumptable first and the link differs (table references in
  construct_item / 801054E0 then point at the wrong offsets and the DOL hash fails).
- Fork comments: "These two factory tables precede this unit's generated restriction table."
  and "The original callback table erases this factory's TItemData* argument to the record's
  byte buffer" (TItemMoney::create takes TItemData*, so it is cast to ItemCreateFunction).
- Ported with a local `typedef TItem *(*ItemCreateFunction)(u8 *)` (the fork has it in
  include/pso/item/ItemCreateFunction.h, upstream does not) and a local declaration of
  create_weapon_for_item(u8 *) returning TItem *, because upstream's header declares it as
  s32(s32). TLobby__sub_801054E0 now returns TItem * and takes u8 *.
- Only the check_equip_requirements rewrite from the fork was not taken: upstream's version
  already matches.
