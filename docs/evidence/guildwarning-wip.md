# GuildWarning recovery — source linked, still draft

`THunterGuildWarning` has a warning mode, a timer and four message-window pointers.
Construction, destruction, task dispatch and the renderer at 0x80211718–0x802119F0
are byte-exact. Callee types here are the ones that match this translation unit.

Base: main `9759a32c140b66adea51215cab1d43c5482d3057`, merged normally.

## Measured state

Every touched function is 100% under objdiff. `THunterGuildWarning_80211718`
(`close_windows`, `THunterGuildWarning__sub_80211774` at 600 bytes, and
`THunterGuildWarning__sub_802119CC`) is linked. On main, `sub_80211774` was
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
`THunterGuildWarning__sub_80211774` and `THunterGuildWarning__sub_802119CC` are
the names in the original symbol table, so they stay `extern "C"`.

`THunterGuildWarning__sub_80211774` calls
`TLobby::create_message_window(const void *, const void *, u32, s32)`.
The original copies the slot with `mr` (case 0/1 from the `clrlwi` of
`get_nth_view_player_id`, case 2 from the `s32` loop index). The factory
`mr`s that register into `TWindowMessage__ct`. The ctor's `extsh` is the
narrowing into `construct_with_parent`, whose third parameter in this
translation unit is `s16`. The DOL does not contain the old mangled string;
`symbols.txt` carries the project-assigned name. Other translation units that
already called this address keep their local prototypes, including `u16`
slots, and name the corrected symbol.

## Still open

Message, CDF and base construction contracts are open. `lbl_8044BC7C` is
copied as two floats (`Pair_8044BC7C`); that name is only the symbol address.
