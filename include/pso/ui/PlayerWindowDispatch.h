#ifndef PSO_UI_PLAYER_WINDOW_DISPATCH_H
#define PSO_UI_PLAYER_WINDOW_DISPATCH_H

#include "types.h"
class TWindowCtrl;
typedef void (TWindowCtrl::*PlayerWindowCommand)();
typedef s32 (TWindowCtrl::*PlayerWindowQuery)();

extern "C" {
void dispatch_player_window_command(s32 client_id, PlayerWindowCommand command);
s32 dispatch_player_window_query(s32 client_id, PlayerWindowQuery query);
void disable_player_main_menu(s32 client_id);
void enable_player_main_menu(s32 client_id);
s32 has_player_active_menu(s32 client_id);
s32 is_player_window_visible(s32 client_id);
void suppress_player_window(s32 client_id);
void unsuppress_player_window(s32 client_id);
}

#endif
