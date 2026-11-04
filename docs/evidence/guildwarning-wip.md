# GuildWarning recovery — source linked, still draft

`THunterGuildWarning` has a warning mode, a timer and four message-window pointers.
Construction, destruction, task dispatch and the renderer at 0x80211718–0x802119F0
are byte-exact. This is not a claim that every callee's type is the original one.

Base: main `55fab55621154476f6b411367ade52a6a1e7c4a4`, merged normally.

## Measured state

Every touched function is 100% under objdiff. `THunterGuildWarning_80211718`
(`close_windows`, `THunterGuildWarning__sub_80211774` at 600 bytes, and
`THunterGuildWarning__sub_802119CC`) is linked. On main, `sub_80211774` was
unmatched and the unit was 17.58%.

`ninja -j8 && python3 tools/check_pr.py --no-build` reports one new exact
function, zero regressions, and linked units 3551 → 3552, with complete code
+728. The renderer references `lbl_8044BC7C` and `lbl_8044BC84` instead of
defining them. `force_active` is unchanged.

`queue_destruction` calls `TObject::queue_destruction`. `send_and_handle` calls
`TLobby::send_and_handle` on the `TWindowMessage *`. `TUnk_804CE018` derives
from `TLobby`, which adds no fields past `TObject` (`sizeof` 0x1C), so both
`send_and_handle` and `set_position_xy` are offset 0 and the call needs no
receiver cast. `TWindow__close` is the unmangled symbol at `0x80244A14`,
called with the `TWindowMessage *` member.
`THunterGuildWarning__sub_80211774` and `THunterGuildWarning__sub_802119CC` are
the names in the original symbol table, so they stay `extern "C"`.

## Still open

`create_message_window__6TLobbyFllUls` is still declared as `extern "C"` with
the mangled name and an `s32` slot. The linked definition is
`TLobby::create_message_window(s32, s32, u32, s16)`. Calling that member makes
GC/2.6 (`-O4,s -inline off`) emit `extsh` at all three sites. The original
copies the register with `mr` (case 0/1 from the `clrlwi` of
`get_nth_view_player_id`, case 2 from the `s32` loop index). GC/2.0, GC/2.6,
GC/2.7 and GC/1.3.2 all `extsh` that call. GC/1.2.5 uses `addi rN, rN, 0` for
the narrowed id, which is not the original `mr`. `lbl_8044BC7C` is copied as
two floats (`Pair_8044BC7C`); that name is only the symbol address. Message,
CDF and base construction contracts are not settled by the match.
