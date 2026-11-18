#ifndef PSO_MISC_TITLE_SCENE_TABLES_H
#define PSO_MISC_TITLE_SCENE_TABLES_H

#include "pso/misc/TUnk_804EEF64.h"
#include "pso/system/NinjaTypes.h"

typedef void (TUnk_804EEF64::*TitleStateHandler)();
typedef char TitleStateHandlerSize[sizeof(TitleStateHandler) == 12 ? 1 : -1];

struct NJS_SPRITE {
    NJS_POINT3 p;
    f32 sx, sy;
    s32 ang;
    NJS_TEXLIST *tlist;
    NJS_TEXANIM *tanim;
};

struct TitleTextureFilenameTable {
    const char *archive[5];
};

extern "C" {
extern NJS_TEXNAME title_texture_entries[21];
// This eight-byte object belongs to the shared .data pool, not .sdata.
__declspec(section ".data") extern NJS_TEXLIST title_texture_list;
extern void (*lobby_load_callback_table[8])();
extern TitleStateHandler TLobby__state_handler_pmf_table[4];
extern NJS_SPRITE lobby_record_table[46];
extern const TitleTextureFilenameTable title_texture_filename_table;
extern const NJS_POINT3 lobby_title_particle_position;
extern const char lobby_title_music[];
extern int lobby_game_mode_state;
}

typedef char TitleTextureListSize[sizeof(NJS_TEXLIST) == 8 ? 1 : -1];
typedef char TitleLoadCallbackTableSize[sizeof(lobby_load_callback_table) == 0x20 ? 1 : -1];
typedef char TitleStateHandlerTableSize[sizeof(TLobby__state_handler_pmf_table) == 0x30 ? 1 : -1];

typedef char TitleSpriteSize[sizeof(NJS_SPRITE) == 0x20 ? 1 : -1];

#endif
