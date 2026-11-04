# GuildWarning recovery — source linked, still draft

`THunterGuildWarning` has a warning mode, a timer and four message-window pointers.
Construction, destruction, task dispatch and the renderer at 0x80211718–0x802119F0
are byte-exact. Callee types here are the ones that match this translation unit.

Base: main `9759a32c140b66adea51215cab1d43c5482d3057`, merged normally.

## Measured state

Every touched function that this branch changes stays 100% under objdiff, except the challenge caller left unchanged (see below). `THunterGuildWarning_80211718`
(`close_windows`, `sub_80211774__19THunterGuildWarningFl` at 600 bytes, and
`sub_802119CC__19THunterGuildWarningFv`) is linked. On main, `sub_80211774` was
unmatched and the unit was 17.58%.

`ninja -j8 && python3 tools/check_pr.py --no-build` reports one new exact
function, zero regressions, and linked units 3553 → 3554, with complete code
+728 and matched code +600. The same address `0x80269CC0` is renamed from
`create_message_window__6TLobbyFllUls` to
`create_message_window__6TLobbyFPCvPCvUll` and stays 100% (100 bytes). The
renderer references the split-owned `lbl_8044BC7C` / `lbl_8044BC84` symbols.
`force_active` is unchanged.

`queue_destruction` calls `TObject::queue_destruction`. `send_and_handle` calls
`TLobby::send_and_handle` on the `TWindowMessage *`. `TUnk_804CE018` derives
from `TLobby`, which adds no fields past `TObject` (`sizeof` 0x1C), so both
`send_and_handle` and `set_position_xy` are offset 0 on that pointer. `TWindow__close` is the unmangled symbol at `0x80244A14`,
called with the `TWindowMessage *` member.

`sub_80211774` and `sub_802119CC` are ordinary non-static members. `symbols.txt`
names them `sub_80211774__19THunterGuildWarningFl` and
`sub_802119CC__19THunterGuildWarningFv`. Implicit `this` stays in r3, and both
functions stay 100% (600 and 36 bytes).

`THunterGuildWarning::sub_80211774` calls
`TLobby::create_message_window(const void *, const void *, u32, s32)`.
The original copies the slot with `mr` (case 0/1 from the `clrlwi` of
`get_nth_view_player_id`, case 2 from the `s32` loop index). The factory
`mr`s that register into `TWindowMessage__ct`. The ctor's `extsh` is the
narrowing into `construct_with_parent`, whose third parameter in this
translation unit is `s16`. Callers in other units call that same member.
`update_selection__19TQuestListChallengeFv` still declares the old local
prototype with a `u16` slot: calling the real `s32` parameter keeps the
`clrlwi` but swaps the callee-saved registers of `sel` and the slot
(r29/r30, 99.72%, 568 bytes). That caller is left on the local prototype.

## Still open

Message, CDF and base construction contracts are open. `lbl_8044BC7C` is
copied as two floats (`Pair_8044BC7C`); that name is only the symbol address.
