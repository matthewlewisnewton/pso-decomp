# w7-replay-a notes

Units replayed from great-merge/main onto upstream 1542ec2fe0.

- TRaderMapCore: draw_compass takes great-merge/main's body (union-typed vertex colour, `scale`/`pos` locals),
  calling draw_compass_sprite through `TObjPlayer` (this tree's owner of that method; great-merge/main moved it
  to a SpriteDescriptor class, not brought across). The unit also needs the three sdata2 constants
  lbl_805DC548/54C/550 written as literals so the object emits the pool the split owns; the lbl_8044A7A0/A8 and
  lbl_805DC540..55C symbols became scope:local (localize_split_globals).
- TLobby_803BFE50: process_audio_stream_input splits into prepare/publish/advance inlines under
  `#pragma inline_depth(4)` / `dont_inline off`, as in great-merge/main. The matching inline decomposition,
  not the pragmas alone, is what the 98.1% version lacked.
- text_8007ECF0: needs `mw_version` GC/1.3.2 (GAME_EXCEPTIONS); under it sprintf and
  draw_outlined_string_right_aligned are plain calls, and the sdata2/rodata pool is defined in the file
  (lbl_805D9298..A4, 92AC, 92B8, "%3d%"). ColorLineVertex/ColorLineList are declared locally in the .cpp
  (this tree has them only in TLobby_801E2F94.h).
- TBoss6Zanzo::sub_803205C4 and TLobby__sub_8020B5CC: great-merge/main bodies (locals declared inside the loops
  for Zanzo; one-struct-per-pass layout for 8020B5CC) with this tree's call forms.
- TWindowShortCut::initialize_preview (8026E1D4): symbol renamed from the placeholder
  TWindowSubStatusDisp__sub_8026E1D4 (own commit); fields m_64/m_68 became text_preview/symbol_preview.
  It calls this tree's names for two functions whose fork names differ: update_state__9TWindowDDFv is the
  fork's format_word_select_message (0x8034861C) and refresh_status_display__9TWindowDDFv is measure_text_entry
  (0x80246F8C); lbl_805DD34C..378 are the data the fork called shortcut_*. set_selection is the existing
  TWindowSubSymbolChatPartsSet::set_selection at 0x80248534. Using the fork spellings left 99.54% (symbol
  names compared by objdiff).
- TMovie_80143988: great-merge/main's pack_movie_frame (explicit lane merges) with
  `-opt nolifetimes,nocse,noprop,noloop`, mapped onto this tree's MovieFramePlanes field names.
- NetworkInfoRequests: request_network_info_load matches only with the first parameter declared
  `ATTRIBUTE_ALIGN(32)` under `scheduling off`/`peephole off`, which reproduces the original's 32-byte stack
  realignment. Brought across as in great-merge/main; flag if that counts as a stack-size trick.
