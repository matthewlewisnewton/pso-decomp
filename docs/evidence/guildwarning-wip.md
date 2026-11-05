# GuildWarning recovery — source linked, still draft

`THunterGuildWarning` has a warning mode, a timer and four message-window pointers.
Construction, destruction, task dispatch and the renderer at 0x80211718–0x802119F0
are byte-exact.

Base: main `665186958`, merged normally.

## Measured state

Every function this branch touches is 100% under objdiff. `THunterGuildWarning_80211718`
(`close_windows`, `sub_80211774__19THunterGuildWarningFl` at 600 bytes, and
`sub_802119CC__19THunterGuildWarningFv`) is linked. On main, `sub_80211774` was
unmatched and the unit was 17.58%.

`ninja -j8 && python3 tools/check_pr.py --no-build` against main
`665186958` reports one new exact function, zero regressions, and linked
units 3545 → 3546, with complete code +728 and matched code +600. Eight
functions are renamed, including `set_window_mode_4__6TLobbyFPCvPCvl` and
`create_titled_window_menu__FPCvlll`. Address `0x80269CC0` is renamed from
`create_message_window__6TLobbyFllUls` to
`create_message_window__6TLobbyFPCvPCvUll` and stays 100% (100 bytes). The
renderer references the split-owned `lbl_8044BC7C` / `lbl_8044BC84` symbols.
`force_active` is unchanged.

`TUnk_804CE018` derives from `TLobby`, which adds no fields past `TObject`
(`sizeof` 0x1C), so `send_and_handle` and `set_position_xy` are called on a
`TWindowMessage *` with no receiver cast. `TWindow__close` is the unmangled
symbol at `0x80244A14`. It closes any window, so its one header declaration
takes `void *`.

`sub_80211774` and `sub_802119CC` are ordinary non-static members. Their
symbol names are project-assigned (the DOL holds only class-name strings).
The constructor's second parameter is the mode integer (`s32`,
`__ct__19THunterGuildWarningFP7TObjectl`).

`get_window_layout_position` returns `WindowLayoutPosition *` in
`TWindowOptionCtrl_8026CBA4.h`. `create_yes_no_window`,
`init_shop_judgment_window` and `create_window_menu` take that type in
`TWindowSubComCard_80265410.h`. The guild-warning, quest-list, quest-thread
and main-menu callers include those headers instead of declaring the
functions locally. So do `TWindow`, `TShopDeleteItemWindow` and
`TShopKeepItemWindow`, which no longer cast the layout.

`TWindow__close` is declared once, in `TWindowSubComCard_80244774.h`.
57 files used to declare it locally (`u8 *`, `void *` or `TWin_8020F070 *`);
53 now include the header.

The character-select save's memory-card window is a `TCheckMemoryCard *`.
Its ctor stores the three trailing arguments as integers, so it takes
`(TObject *, u32, u32, u32)`. `TAdSinglePlyChrSelectGC::create_check_memory_card`
and `fn_8033C5E4` return `TCheckMemoryCard *`, and both callers use the
static member instead of a mangled prototype.
`TAdSinglePlyChrSelectGC__sub_8033B9F8` returns `s32`: the original caller
tests it with `cmpwi r3, 0`.

## Register notes

`TLobby::create_message_window` takes the slot as `s32`. The factory `mr`s it
into `TWindowMessage__ct`, and the ctor's `extsh` is the narrowing into
`construct_with_parent`, whose third parameter is `s16`.

`update_selection__19TQuestListChallengeFv` passes `get_entity_id(...)`
inline as the factory's last argument, as `TQuestListOffline` does. MWCC
evaluates arguments right to left, so the call still comes first, and `sel`
and the slot get r29/r30 as in the original. A named `id` local shared with
the yes/no call is what swapped them (99.72%).

In `sub_80211774` case 2 the selected text is an `int` passed to a `long`
parameter inside the loop. MWCC hoists that conversion as the original's
`mr r28, r27`. An `s32` variable or a literal at each call does not.

## Still open

These need cross-file retypes beyond this branch:

- **The `s32` layout convention, partly retyped.** `set_window_mode_4` is
  the real static member `set_window_mode_4__6TLobbyFPCvPCvl` (layout and
  size are `const void *`). `create_titled_window_menu` is
  `create_titled_window_menu__FPCvlll`. Callers that already hold the
  lookup pointer pass it with no cast, and those units are function-100%,
  including `TWindowSubMag`, `TWindowSubTechnique` and `TWindowSubItem`.
  `TWindowSubMagPhoton` is function-100% but still casts the layout pointer
  to `s32` for `TWindowSubStatusDisp__sub_80248BE8` (that free function and
  `refresh_with_default_list__20TWindowSubStatusDispFll` still take integers;
  `draw_with_layer__13TAdVIConfigGCFlll` forwards the same integers). The folded `TObjBoss2Tunnel` message functions
  pass their `f32` position arrays the same way and stay 100%.
  `update_window_mode_from_progress` now passes `this` with no cast.
  Two adapter casts remain because the callee's public symbol is still an
  integer: `TWindowSubComCard_80271E7C` casts its `s32` lookup into the three
  `set_window_mode_4` calls (widening that file's lookup renames
  `create_for_card__14TWindowComCardFlll`), and `open_yes_no_prompt` stays
  the unmangled `s32` symbol and casts into `create_titled_window_menu`.
  Both are function-100%. The other lookup files still declare
  `get_window_layout_position` as returning `s32`. That remainder still
  runs through `check_room_seq_4__16TAdChrSelASlotGCFl`,
  `draw_card_icon__17TWindowSubComCardFll`, and the mangled
  `TWindowHelpItem` / `TWindowInputNumber` ctors.
- **The window constructor chain.** `create_message_window` now returns
  the `TWindowMessage *` from `__nw__7TObjectFUl` and `TWindowMessage__ct`
  with no cast, and that function stays 100%. `update_window_mode_from_progress`
  passes `this` through with no cast and stays 100%. A real
  `TWindowMessage::TWindowMessage` does not: MWCC emits
  `bl __ct__13TUnk_804CDFE8Fv` and a vtable store at 0x18 *before*
  `construct_with_parent`, then the body stores the vtable again. The
  original has only the second store. Defining
  `TUnk_804CDFE8::TUnk_804CDFE8(void *, s32, const void *)` as that base
  constructor emits `bl __ct__13TUnk_804CE018Fv`, which emits
  `bl __ct__6TLobbyFv`, which calls `__ct__7TObjectFP7TObject` with a null
  parent, and stores the compiler vtable `__vt__13TUnk_804CDFE8`. The DOL
  slot at `lbl_804CDFE8` is `destroy_window__13TUnk_804CDFE8Fs`, not a C++
  destructor, so that vtable cannot be the one MWCC emits. The C-named
  `TWindowMessage__ct` stays. Its field stores now use `m_name`, `m_70`,
  `m_74`, `next_line`, `line_count`, `m_78`, `m_84`, `unk_80` and `lines`,
  and the function is still 100%. The vptr store at 0x18 has no declared
  field (it is the hidden `TObject` vptr) and is still a byte offset.
- **`TLobby::send_and_handle(int, int)`.** It has 127 call sites, so a text
  pointer is still passed as an integer.
- **`create_yes_no_window` locals now take `const void *`.** The eight
  `s32` prototypes in `THunterGuildSeqOffline`,
  `THunterGuildSeqOffline_80213788`, `TMedicalCenterSequence`,
  `TShopGetItemWindow`, `TShopJudgmentItemWindow`, `TShopArmorListWindow`,
  `TShopEquipmentListWindow` and `TWindowSubComCard_802A5748` pass the
  lookup pointer through. Those units stay function-100%.
  `TShopSequence::create_message_window(s32, s32)` still takes the layout
  as an integer, so the guild and medical callers still cast there.
  `new TWindowHelpItem` / `new TWindowInputNumber` would call
  `__nw__15TWindowHelpItemFUl` / `__nw__18TWindowInputNumberFUl`; the
  originals call `__nw__7TObjectFUl`, so those factories stay C calls.
- **Four local `TWindow__close` prototypes now take `void *`, matching the header.** The calls still cast `u32` window fields through `u8 *`. `TWindowChatSymbol_802486A8`,
  `TWindowSubComCard_80271E7C`, `TWindowSubStatusDisp_8026F6DC` and
  `TWindowSubTradeMain_80330A84` declare other functions from
  `TWindowSubComCard_80244774.h` with different signatures:
  - `fn_8024491C`, `fn_80244958` and `TWindowSubTradeMain__sub_802448E4`
    take `(window, pos)`, but their definitions forward `pos` to a mangled
    `copy_vec2` call by r4 pass-through.
  - `TWindowSubComCard__sub_80245558` returns a byte in its definition
    (`extrwi r3, r0, 8, 19`), while its four callers test a word
    (`cmpwi r3, 0`). With `bool` the callers gain a `clrlwi`, and with `s32`
    the definition drops to 97.93%, so one declaration can't be exact.
