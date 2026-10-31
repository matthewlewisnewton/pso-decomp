#ifndef PSO_MISC_TITLE_SCENE_TABLES_H
#define PSO_MISC_TITLE_SCENE_TABLES_H

#include "pso/misc/TLobby.h"
#include "pso/system/NinjaTypes.h"

typedef void (TLobby::*TitleStateHandler)();
typedef char TitleStateHandlerSize[sizeof(TitleStateHandler) == 12 ? 1 : -1];

extern "C" {
extern NJS_TEXNAME title_texture_entries[21];
// This eight-byte object belongs to the shared .data pool, not .sdata.
__declspec(section ".data") extern NJS_TEXLIST title_texture_list;
extern void (*lobby_load_callback_table[8])();
extern TitleStateHandler TLobby__state_handler_pmf_table[4];
}

typedef char TitleTextureListSize[sizeof(NJS_TEXLIST) == 8 ? 1 : -1];
typedef char TitleLoadCallbackTableSize[sizeof(lobby_load_callback_table) == 0x20 ? 1 : -1];
typedef char TitleStateHandlerTableSize[sizeof(TLobby__state_handler_pmf_table) == 0x30 ? 1 : -1];

#endif
