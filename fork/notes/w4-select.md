# w4-select notes

## pso/ui/frontend/TAdSinglePlyChrSelectGC_8028EF14.cpp (linked)
- Functions already matched. Link needed: .sbss split start 0x805D6558 (fork's value) with
  `creation_resource_ready_state` defined in the unit (was extern, so the 8-aligned start
  was missing); the fork's function order inside the deferred_codegen region (map_button_code
  before blend_shape_chunk_vertices; load/bind/reset_model_parts after init_entry_tables);
  218 string literals / pooled constants marked scope:local with tools/localize_split_globals.py.
- 8007EBB4 safe_free name left as this tree has it (not needed).

## pso/unk/text_801A9CB8.cpp (not linked: blocked on unit boundaries)
- __vt__13TUnk_804C349C (0x804C349C, no split owns it) belongs with the ctor/dtor in
  text_801A9CB8 (.text 801A9CB8-801AA220), but claiming .data 0x804C349C-0x804C34B4 for it
  fails in dtk: "Cyclic dependency encountered while resolving link order" because the
  neighbouring units text_801AA220 / text_801AA3B4 own .data below it (0x804C32C0-0x804C344C)
  while their .text follows 801A9CB8. Also the symbol size 0x1C must become 0x18 (fork value).
  Needs the fork's merged unit; not done.

## pso/object/trap/TOTrapAncient01.cpp (play_sounds matched, not linked)
- play_sounds (801794CC) 100% with: mw_version GC/2.0, -pooldata=off, the fork's const
  TObjChipParams locals with brace initialisers (const_cast on the new TObjChip calls), and
  split .rodata widened to 0x80442D80-0x80442E70 so the templates are owned by the unit.
- Float externs (lbl_805DBA48.. etc.) replaced by literals, .sdata2 split widened to
  0x805DBA48-0x805DBA78 (fork value). All 12 floats now compiled, but the order differs from
  the original: compiled has 1.25f first, original has 1.0f, 0.0f, 1.25f. 1.25f is first used by
  play_sounds, which sits before vfunc_82 (1.0f/0.0f) in text order. The fork's source is in
  reverse function order (deferred codegen) which gives the right pool order; here text order
  is source order. Link reason now: `data .sdata2:91.66667%` plus localizable `missing` symbols.
  Not tried: reordering via -inline deferred with reversed source.

## pso/npc/TObjNpcKenkyuW.cpp (802A445C unmatched, 96.5%)
- Remaining diff: `mr r3,r30` before `lwz r4,0(r31)` for the is_hit_receivable_target call
  (target has the mr first). Tried: fork's scheduling off + global_optimizer off pragmas
  (93.0%), scheduling off alone (93.0%), hoisting actors[0] into a local (89.8%), fork's comma
  expression for m_38/vfunc_9 (96.5%, no change). Reverted. No renames needed or applied.
