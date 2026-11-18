#ifndef PSO_MISC_TITLE_SCENE_TABLES_H
#define PSO_MISC_TITLE_SCENE_TABLES_H

#include "pso/misc/TUnk_804EEF64.h"
#include "pso/system/NinjaTypes.h"

#include "pso/render/SpriteDescriptor.h"

struct TitleTextureFilenameTable {
    const char *archive[5];
};

typedef void (TUnk_804EEF64::*TitleStateHandler)();
typedef char TitleStateHandlerSize[sizeof(TitleStateHandler) == 12 ? 1 : -1];

extern "C" {
extern const TitleTextureFilenameTable title_texture_filename_table;
extern const NJS_POINT3 title_particle_position;
extern const char title_music_filename[];
extern SpriteDescriptor lobby_record_table[46];
extern s32 lobby_game_mode_state;
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
