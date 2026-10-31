#include "types.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TitleSceneTables.h"
#include "pso/misc/TLobby_80335E08.h"
#include "pso/misc/TLobby_80336E00.h"

// The native PMF initializer emits a static constructor and four 12-byte
// temporary records immediately before the destination table.

void clear_lobby_global_flags();
extern "C" {
extern char lbl_80477668[];
extern char lbl_80477670[];
extern char lbl_80477680[];
extern char lbl_80477690[];
extern char lbl_804776A4[];
extern char lbl_804776B8[];
extern char lbl_804776CC[];
extern char lbl_804776E0[];
extern char lbl_804776F4[];
extern char lbl_80477708[];
extern char lbl_8047771C[];
extern char lbl_80477730[];
extern char lbl_80477740[];
extern char lbl_80477750[];
extern char lbl_80477764[];
extern char lbl_80477778[];
extern char lbl_8047778C[];
extern char lbl_804777A0[];
extern char lbl_804777B4[];
extern char lbl_804777C8[];
extern char lbl_804777DC[];

NJS_TEXNAME title_texture_entries[21] = {
    {lbl_80477668, 0, 0},
    {lbl_80477670, 0, 0},
    {lbl_80477680, 0, 0},
    {lbl_80477690, 0, 0},
    {lbl_804776A4, 0, 0},
    {lbl_804776B8, 0, 0},
    {lbl_804776CC, 0, 0},
    {lbl_804776E0, 0, 0},
    {lbl_804776F4, 0, 0},
    {lbl_80477708, 0, 0},
    {lbl_8047771C, 0, 0},
    {lbl_80477730, 0, 0},
    {lbl_80477740, 0, 0},
    {lbl_80477750, 0, 0},
    {lbl_80477764, 0, 0},
    {lbl_80477778, 0, 0},
    {lbl_8047778C, 0, 0},
    {lbl_804777A0, 0, 0},
    {lbl_804777B4, 0, 0},
    {lbl_804777C8, 0, 0},
    {lbl_804777DC, 0, 0},
};
NJS_TEXLIST title_texture_list = {title_texture_entries, 21};

void (*lobby_load_callback_table[8])() = {
    TLobby__sub_80335E78, TLobby__sub_80335E74,
    clear_lobby_global_flags, TLobby__sub_80336E44,
    TLobby__sub_80335FE4, TLobby__sub_80335FE0,
    TLobby__sub_80336E68, TLobby__sub_80336E64
};

TitleStateHandler TLobby__state_handler_pmf_table[4] = {
    &TLobby::enter_chg_game_mode,
    &TLobby::enter_game_mode_change,
    &TLobby::request_change_game_mode,
    &TLobby::open_keyboard
};
}
