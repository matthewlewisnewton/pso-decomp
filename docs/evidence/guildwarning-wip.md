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
  including `TWindowSubMag`, `TWindowSubTechnique`, `TWindowSubItem` and
  `TWindowSubMagPhoton`. The folded `TObjBoss2Tunnel` message functions
  pass their `f32` position arrays the same way and stay 100%. Three
  adapter casts remain because the callee's public symbol is still an
  integer: `update_window_mode_from_progress` casts its `s32` `this`,
  `TWindowSubComCard_80271E7C` casts its `s32` lookup into the three
  `set_window_mode_4` calls (widening that file's lookup renames
  `create_for_card__14TWindowComCardFlll`), and `open_yes_no_prompt` stays
  the unmangled `s32` symbol and casts into `create_titled_window_menu`.
  All three are function-100%. The other lookup files still declare
  `get_window_layout_position` as returning `s32`. That remainder still
  runs through `check_room_seq_4__16TAdChrSelASlotGCFl`,
  `draw_card_icon__17TWindowSubComCardFll`, and the mangled
  `TWindowHelpItem` / `TWindowInputNumber` ctors.
- **The window constructor chain.** A cast-free factory is
  `return new TWindowMessage(...)`. Retyping `TWindowMessage__ct` alone only
  moves the cast, because the `__nw` result and the ctor result share one
  variable. A real ctor needs real ctors on every base (`TUnk_804CDFE8`'s
  `construct_with_parent`, then `TWindowDD::construct_base`), and each class
  must declare virtuals matching its DOL vtable. About 18 window ctors in
  other files call those bases as C-named functions today.
- **`TLobby::send_and_handle(int, int)`.** It has 127 call sites, so a text
  pointer is still passed as an integer.
- **Eight local `create_yes_no_window(s32, ...)` prototypes.** In
  `THunterGuildSeqOffline`, `THunterGuildSeqOffline_80213788` and
  `TMedicalCenterSequence` the same integer layout also goes to
  `TShopSequence::create_message_window(s32, s32)` (8 caller files), some
  through a two-argument lookup. `TShopGetItemWindow`,
  `TShopJudgmentItemWindow`, `TShopArmorListWindow` and
  `TShopEquipmentListWindow` pass it to local mangled `TWindowHelpItem` /
  `TWindowInputNumber` ctor prototypes. A `new` expression there calls
  `__nw__15TWindowHelpItemFUl` / `__nw__18TWindowInputNumberFUl`, while these
  originals call `__nw__7TObjectFUl`. `TWindowSubComCard_802A5748` passes a
  `s32` local filled by `get_position_offset`.
- **Four local `TWindow__close` prototypes.** `TWindowChatSymbol_802486A8`,
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
