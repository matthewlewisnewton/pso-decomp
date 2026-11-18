#include "types.h"
#include "pso/misc/TitleSceneTables.h"
#include "pso/misc/TLobby_80335E08.h"
#include "pso/misc/TLobby_80336E00.h"

// The native PMF initializer emits a static constructor and four 12-byte
// temporary records immediately before the destination table.

void clear_lobby_global_flags();
extern "C" {
static __declspec(section ".rodata") const char lobby_title_texture_name_f256_ad[] ATTRIBUTE_ALIGN(4) = "f256_ad";
static __declspec(section ".rodata") const char lobby_title_texture_name_f256_psotitle[] ATTRIBUTE_ALIGN(4) = "f256_psotitle";
static __declspec(section ".rodata") const char lobby_title_texture_name_f256_psotitle02[] ATTRIBUTE_ALIGN(4) = "f256_psotitle02";
static __declspec(section ".rodata") const char lobby_title_texture_name_f256_titlealpha01[] ATTRIBUTE_ALIGN(4) = "f256_titlealpha01";
static __declspec(section ".rodata") const char lobby_title_texture_name_f256_titlealpha02[] ATTRIBUTE_ALIGN(4) = "f256_titlealpha02";
static __declspec(section ".rodata") const char lobby_title_texture_name_f256_titlealpha03[] ATTRIBUTE_ALIGN(4) = "f256_titlealpha03";
static __declspec(section ".rodata") const char lobby_title_texture_name_f256_titlealpha04[] ATTRIBUTE_ALIGN(4) = "f256_titlealpha04";
static __declspec(section ".rodata") const char lobby_title_texture_name_f256_titlealpha05[] ATTRIBUTE_ALIGN(4) = "f256_titlealpha05";
static __declspec(section ".rodata") const char lobby_title_texture_name_f256_titlealpha06[] ATTRIBUTE_ALIGN(4) = "f256_titlealpha06";
static __declspec(section ".rodata") const char lobby_title_texture_name_f256_titlealpha07[] ATTRIBUTE_ALIGN(4) = "f256_titlealpha07";
static __declspec(section ".rodata") const char lobby_title_texture_name_f256_titlealpha08[] ATTRIBUTE_ALIGN(4) = "f256_titlealpha08";
static __declspec(section ".rodata") const char lobby_title_texture_name_f512_mahoujin[] ATTRIBUTE_ALIGN(4) = "f512_mahoujin";
static __declspec(section ".rodata") const char lobby_title_texture_name_f512_mahoujin_b[] ATTRIBUTE_ALIGN(4) = "f512_mahoujin_b";
static __declspec(section ".rodata") const char lobby_title_texture_name_s256_1st_title01[] ATTRIBUTE_ALIGN(4) = "s256_1st_title01";
static __declspec(section ".rodata") const char lobby_title_texture_name_s256_1st_title02[] ATTRIBUTE_ALIGN(4) = "s256_1st_title02";
static __declspec(section ".rodata") const char lobby_title_texture_name_s256_1st_title03[] ATTRIBUTE_ALIGN(4) = "s256_1st_title03";
static __declspec(section ".rodata") const char lobby_title_texture_name_s256_1st_title04[] ATTRIBUTE_ALIGN(4) = "s256_1st_title04";
static __declspec(section ".rodata") const char lobby_title_texture_name_s256_1st_title05[] ATTRIBUTE_ALIGN(4) = "s256_1st_title05";
static __declspec(section ".rodata") const char lobby_title_texture_name_s256_1st_title06[] ATTRIBUTE_ALIGN(4) = "s256_1st_title06";
static __declspec(section ".rodata") const char lobby_title_texture_name_s256_1st_title07[] ATTRIBUTE_ALIGN(4) = "s256_1st_title07";
static __declspec(section ".rodata") const char lobby_title_texture_name_s256_1st_title08[] ATTRIBUTE_ALIGN(4) = "s256_1st_title08";

NJS_TEXNAME title_texture_entries[21] = {
    {const_cast<char *>(lobby_title_texture_name_f256_ad), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_f256_psotitle), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_f256_psotitle02), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_f256_titlealpha01), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_f256_titlealpha02), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_f256_titlealpha03), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_f256_titlealpha04), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_f256_titlealpha05), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_f256_titlealpha06), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_f256_titlealpha07), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_f256_titlealpha08), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_f512_mahoujin), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_f512_mahoujin_b), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_s256_1st_title01), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_s256_1st_title02), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_s256_1st_title03), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_s256_1st_title04), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_s256_1st_title05), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_s256_1st_title06), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_s256_1st_title07), 0, 0},
    {const_cast<char *>(lobby_title_texture_name_s256_1st_title08), 0, 0},
};
NJS_TEXLIST title_texture_list = {title_texture_entries, 21};

void (*lobby_load_callback_table[8])() = {
    TLobby__sub_80335E78, TLobby__sub_80335E74,
    clear_lobby_global_flags, TLobby__sub_80336E44,
    TLobby__sub_80335FE4, TLobby__sub_80335FE0,
    TLobby__sub_80336E68, TLobby__sub_80336E64
};

TitleStateHandler TLobby__state_handler_pmf_table[4] = {
    &TUnk_804EEF64::enter_chg_game_mode,
    &TUnk_804EEF64::enter_game_mode_change,
    &TUnk_804EEF64::request_change_game_mode,
    &TUnk_804EEF64::open_keyboard
};

// Sprite cells of the title textures (size, centre, uv rectangle, texture id),
// shared by every lobby_record_table sprite.
static NJS_TEXANIM lobby_title_sprite_cells[46] = {
    {256, 256, 0, 0, 0, 0, 256, 256, 0, 0},
    {256, 256, 0, 0, 0, 0, 256, 256, 1, 0},
    {256, 256, 0, 0, 0, 0, 256, 256, 2, 0},
    {256, 256, 0, 0, 0, 0, 256, 256, 3, 0},
    {128, 128, 0, 0, 0, 0, 256, 256, 4, 0},
    {128, 128, 0, 0, 0, 0, 256, 256, 5, 0},
    {128, 128, 0, 0, 0, 0, 256, 256, 6, 0},
    {128, 128, 0, 0, 0, 0, 256, 256, 7, 0},
    {256, 96, 0, 0, 0, 0, 255, 95, 8, 0},
    {256, 160, 0, 0, 0, 96, 255, 255, 8, 0},
    {256, 32, 0, 0, 0, 0, 255, 31, 0, 0},
    {256, 32, 0, 0, 0, 32, 255, 63, 0, 0},
    {256, 32, 0, 0, 0, 64, 255, 95, 0, 0},
    {256, 32, 0, 0, 0, 96, 255, 127, 0, 0},
    {256, 32, 0, 0, 0, 128, 255, 159, 0, 0},
    {16, 18, 0, 0, 0, 224, 15, 241, 0, 0},
    {16, 18, 0, 0, 0, 224, 15, 241, 0, 0},
    {16, 18, 0, 0, 0, 224, 15, 241, 0, 0},
    {16, 18, 0, 0, 0, 224, 15, 241, 0, 0},
    {16, 18, 0, 0, 16, 224, 31, 241, 0, 0},
    {16, 18, 0, 0, 16, 224, 31, 241, 0, 0},
    {16, 18, 0, 0, 16, 224, 31, 241, 0, 0},
    {16, 18, 0, 0, 16, 224, 31, 241, 0, 0},
    {16, 18, 0, 0, 32, 224, 47, 241, 0, 0},
    {16, 18, 0, 0, 32, 224, 47, 241, 0, 0},
    {16, 18, 0, 0, 32, 224, 47, 241, 0, 0},
    {16, 18, 0, 0, 32, 224, 47, 241, 0, 0},
    {16, 18, 0, 0, 49, 224, 64, 241, 0, 0},
    {16, 18, 0, 0, 49, 224, 64, 241, 0, 0},
    {16, 18, 0, 0, 49, 224, 64, 241, 0, 0},
    {16, 18, 0, 0, 49, 224, 64, 241, 0, 0},
    {16, 18, 0, 0, 65, 224, 80, 241, 0, 0},
    {16, 18, 0, 0, 65, 224, 80, 241, 0, 0},
    {16, 18, 0, 0, 65, 224, 80, 241, 0, 0},
    {16, 18, 0, 0, 65, 224, 80, 241, 0, 0},
    {16, 18, 0, 0, 81, 224, 96, 241, 0, 0},
    {16, 18, 0, 0, 81, 224, 96, 241, 0, 0},
    {16, 18, 0, 0, 81, 224, 96, 241, 0, 0},
    {16, 18, 0, 0, 81, 224, 96, 241, 0, 0},
    {128, 24, 0, 0, 0, 128, 127, 151, 0, 0},
    {16, 18, 0, 0, 128, 32, 144, 50, 0, 0},
    {16, 18, 0, 0, 144, 32, 160, 50, 0, 0},
    {16, 18, 0, 0, 160, 32, 176, 50, 0, 0},
    {16, 18, 0, 0, 49, 224, 55, 242, 0, 0},
    {16, 18, 0, 0, 55, 224, 71, 242, 0, 0},
    {16, 18, 0, 0, 87, 224, 103, 242, 0, 0},
};

// Title screen sprites; TLobby::get_record hands one to draw_with_camera.
NJS_SPRITE lobby_record_table[46] = {
    {{0.0f, -16.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{0.0f, 240.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{256.0f, -16.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{256.0f, 240.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{512.0f, -16.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{512.0f, 112.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{512.0f, 240.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{512.0f, 368.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{96.0f, 172.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{352.0f, 172.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{193.0f, 338.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{193.0f, 300.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{193.0f, 332.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{193.0f, 364.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{193.0f, 396.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{192.0f, 308.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{192.0f, 340.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{192.0f, 372.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{192.0f, 404.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{208.0f, 308.0f, 0.0f}, 14.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{208.0f, 340.0f, 0.0f}, 14.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{208.0f, 372.0f, 0.0f}, 14.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{208.0f, 404.0f, 0.0f}, 14.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{432.0f, 308.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{432.0f, 340.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{432.0f, 372.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{432.0f, 404.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{192.0f, 308.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{192.0f, 340.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{192.0f, 372.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{192.0f, 404.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{208.0f, 308.0f, 0.0f}, 14.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{208.0f, 340.0f, 0.0f}, 14.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{208.0f, 372.0f, 0.0f}, 14.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{208.0f, 404.0f, 0.0f}, 14.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{432.0f, 308.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{432.0f, 340.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{432.0f, 372.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{432.0f, 404.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{259.0f, 415.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{208.0f, 418.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{224.0f, 418.0f, 0.0f}, 12.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{416.0f, 418.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{192.0f, 418.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{208.0f, 418.0f, 0.0f}, 12.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
    {{432.0f, 418.0f, 0.0f}, 1.0f, 1.0f, 0, &title_texture_list, lobby_title_sprite_cells},
};

static __declspec(section ".rodata") const char japanese_title_archive[] ATTRIBUTE_ALIGN(4) = "Title";
static __declspec(section ".rodata") const char english_title_archive[] ATTRIBUTE_ALIGN(4) = "Title_eng";
extern __declspec(section ".rodata") const TitleTextureFilenameTable title_texture_filename_table = {
    {japanese_title_archive, english_title_archive, english_title_archive, english_title_archive, english_title_archive},
};
extern __declspec(section ".rodata") const NJS_POINT3 lobby_title_particle_position = {0.0f, 0.0f, -47.0f};
extern __declspec(section ".rodata") const char lobby_title_music[] ATTRIBUTE_ALIGN(4) = "title.adx";

}
