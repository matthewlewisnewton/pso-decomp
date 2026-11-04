# GuildWarning recovery — source linked, still draft

`THunterGuildWarning` has a warning mode, a timer and four message-window pointers.
Construction, destruction, task dispatch and the renderer at 0x80211718–0x802119F0
are byte-exact. This is not a claim that every callee's type is the original one.

Base: main `6238fdf1ca8ed743483794185fe5b5af2257c930`, merged normally.

## Measured state

Every touched function is 100% under objdiff. `THunterGuildWarning_80211718`
(`close_windows`, `THunterGuildWarning__sub_80211774` at 600 bytes, and
`THunterGuildWarning__sub_802119CC`) is linked. On main, `sub_80211774` was
unmatched and the unit was 17.58%.

`ninja -j8 && python3 tools/check_pr.py --no-build` reports one new exact
function, zero regressions, and linked units 3554 → 3555, with complete code
+728. The renderer references `lbl_8044BC7C` and `lbl_8044BC84` instead of
defining them. `force_active` is unchanged.

`queue_destruction` calls `TObject::queue_destruction`. `send_and_handle` calls
`TLobby::send_and_handle`. `TWindow__close` is the unmangled symbol at
`0x80244A14`, called with the `TWindowMessage *` member.
`THunterGuildWarning__sub_80211774` and `THunterGuildWarning__sub_802119CC` are
the names in the original symbol table, so they stay `extern "C"`.

## Still open

`create_message_window__6TLobbyFllUls` is still named directly. The real
`TLobby::create_message_window` takes `s16` for the slot, and GC/2.6 then
emits `extsh`. The original call site copies the register with `mr` (case 0/1
from the `clrlwi` of `get_nth_view_player_id`, case 2 from the `s32` loop
index). No `s`-mangled parameter type reproduces both. `send_and_handle` is
reached with a `TLobby *` cast of the `TWindowMessage *`: `TLobby` is a
non-empty `TObject`, so it cannot share offset 0 with `TUnk_804CDFE8`.
`lbl_8044BC7C` is copied as two floats (`Pair_8044BC7C`); that name is only
the symbol address. Message, CDF and base construction contracts are not
settled by the match. These two call-site gaps are porting exceptions for #315.
