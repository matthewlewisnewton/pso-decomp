#include "pso/system/SoundEffect.h"
struct Vec;
#include "types.h"
#include "pso/misc/TLobby.h"
#include "pso/item/TUnk_804CC048.h"
#include "pso/map/FloorArea.h"
#include "pso/misc/TLobby_80207644.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/misc/TWindowSubStatusDisp_803DEE6C.h"
#include "pso/system/MatrixOps.h"
#include "pso/math/MatrixVector.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/render/model_render_state.h"

// Sprite frame draw ported from upstream zeroz41/pso-decomp #208 (Matchpass 15,
// squash ae797d392), which matches it under GC/1.3.2.

// One frame of a sprite sheet: its size, the offset of its origin, its
// texture coordinates in 1/256 units and its texture.
struct SpriteFrame_80228154 {
    s16 width;
    s16 height;
    s16 origin_x;
    s16 origin_y;
    s16 u0;
    s16 v0;
    s16 u1;
    s16 v1;
    s16 texture;
    u8 pad_12[0x14 - 0x12];
};

struct Sprite_80228154 {
    f32 x;
    f32 y;
    u8 pad_8[0xC - 0x8];
    f32 scale_x;
    f32 scale_y;
    s32 angle;
    GinjaTextureList *texture_list;
    SpriteFrame_80228154 *frames;
};

// The screen quad draw_textured_quad_at_depth reads.
struct ScreenQuad_80228154 {
    f32 x0, y0, x1, y1;
    f32 u0, v0, u1, v1;
};

union SpriteColor_80228154 {
    struct { u8 a, r, g, b; } channels;
    u32 packed;
};

extern "C" {
// Draws one frame of a sprite on the screen; flags 1 rotates the quad by the
// sprite's angle, 2 tints it with the model material colour, 0x20 blends.
void TLobby__sub_80228154(Sprite_80228154 *sprite, s32 frame_index, s32 flags, f32 depth) {
    ScreenQuad_80228154 quad;
    union SpriteColor_80228154 color;
    if (sprite == NULL) {
        return;
    }
    if (sprite->texture_list == NULL) {
        return;
    }
    set_current_texture_list(sprite->texture_list);
    SpriteFrame_80228154 *frame = &sprite->frames[frame_index];
    f32 left = -frame->origin_x;
    f32 top = -frame->origin_y;
    f32 right = left + frame->width;
    f32 bottom = top + frame->height;
    left *= sprite->scale_x;
    right *= sprite->scale_x;
    top *= sprite->scale_y;
    bottom *= sprite->scale_y;
    quad.x0 = sprite->x + left;
    quad.y0 = sprite->y + top;
    quad.x1 = sprite->x + right;
    quad.y1 = sprite->y + bottom;
    quad.u0 = frame->u0 / 256.0f;
    if (1.0f < quad.u0) {
        quad.u0 = 1.0f;
    }
    quad.v0 = frame->v0 / 256.0f;
    if (1.0f < quad.v0) {
        quad.v0 = 1.0f;
    }
    quad.u1 = frame->u1 / 256.0f;
    if (1.0f < quad.u1) {
        quad.u1 = 1.0f;
    }
    quad.v1 = frame->v1 / 256.0f;
    if (1.0f < quad.v1) {
        quad.v1 = 1.0f;
    }
    color.packed = 0xFFFFFFFF;
    if (flags & 1) {
        Vec offset;
        f32 cx = (quad.x1 + quad.x0) / 2.0f;
        f32 cy = (quad.y1 + quad.y0) / 2.0f;
        offset.x = quad.x0 - cx;
        offset.y = quad.y0 - cy;
        offset.z = 0.0f;
        push_matrix_from(identity_matrix);
        rotate_matrix_z(NULL, sprite->angle);
        rotate_vector_by_matrix(0, &offset, &offset);
        pop_matrix();
        quad.x0 = cx + offset.x;
        quad.y0 = cy + offset.y;
        quad.x1 = cx - offset.x;
        quad.y1 = cy - offset.y;
    }
    if (flags & 2) {
        color.channels.b = 255.0f * model_material_color.b;
        color.channels.g = 255.0f * model_material_color.g;
        color.channels.r = 255.0f * model_material_color.r;
        color.channels.a = 255.0f * model_material_color.a;
    }
    // The original's flip paths overwrite one coordinate with the other
    // instead of swapping them (and flag 8 writes u0); kept as compiled.
    if (flags & 4) {
        quad.u1 = quad.u0;
        quad.u0 = quad.u1;
    }
    if (flags & 8) {
        quad.v1 = quad.v0;
        quad.u0 = quad.v1;
    }
    depth = -1.0f / depth;
    begin_screen_draw(0x20 == (flags & 0x20));
    set_draw_texture_and_color(frame->texture, color.packed);
    draw_textured_quad_at_depth(&quad.x0, depth);
    TWindowSubStatusDisp::get_player();
}
}

struct RecoveredGlobal_80227AA8_lbl_80514F64 {
    s32 value;
    u8 remaining[0xC38];
};

extern "C" {
void get_menu_field_280__6TLobbyFv(void);
void fn_8023F660(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern unsigned char sound_control_state[];
void TLobby__sub_80227AA8(s32 arg0);
int free__6TLobbyFPv(void* p);
int TLobby__sub_80227A4C(void* p);
void TLobby__sub_80227A6C(void);
int TLobby__sub_80227A70(void* p);
void TLobby__sub_80227A90(void);
void TLobby__sub_80227A94(void);
int get_music_base_gain(void);
void TLobby__sub_8022804C(void);
int xfree__FPv(void*);
int xmalloc__FUl(void*);


    extern int lbl_805D3710;
    extern int lbl_805D6314;

    extern int music_stream_base_gain;
typedef char RecoveredGlobal_80227AA8_lbl_80514F64_size[sizeof(RecoveredGlobal_80227AA8_lbl_80514F64) == 0xC3C ? 1 : -1];

}


struct RecoveredGlobal_8000F764_TKeyBoardControl__data_80506270 {
    s32 value;
    u8 remaining[0xAC];
};

struct RecoveredGlobal_8000F7FC_lbl_80515F48 {
    s32 value;
    u8 remaining[0x24];
};

struct RecoveredGlobal_8000F9E4_lbl_804FE120 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_8000F90C_lbl_804FE120 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_8000F9CC_lbl_804FE120 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_8000F8FC_lbl_804FE120 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_8000F8EC_lbl_804FE120 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_8000F91C_lbl_804FE120 {
    s32 value;
    u8 remaining[0x14];
};

#include <stddef.h>
#include "pso/misc/TScene.h"
struct RecoveredGlobal_80069094_camera_controller_registry { s32 value; u8 remaining[0x64]; };

struct RecoveredGlobal_80069024_TCameraCtrl__data_804FF634 {
    s32 value;
    u8 remaining[0x44];
};

struct RecoveredGlobal_80069024_lbl_804FF67C {
    s32 value;
    u8 remaining[0x44];
};

struct RecoveredGlobal_800695E8_TCameraCtrl__data_804FF628 {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_800691C8_TCameraCtrl__data_804FF6D0 {
    s32 value;
    u8 remaining[0x2C];
};

struct RecoveredGlobal_800691C8_TCameraCtrl__data_804FF700 {
    s32 value;
    u8 remaining[0xBC];
};

struct RecoveredGlobal_800691C8_main_task {
    s32 value;
    u8 remaining[0x30];
};

struct RecoveredGlobal_800687E4_TCameraCtrl__data_804FF6C4 {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_80069148_TCameraCtrl__data_804FF6D0 {
    s32 value;
    u8 remaining[0x2C];
};

struct RecoveredGlobal_80069148_TCameraCtrl__data_804FF700 {
    s32 value;
    u8 remaining[0xBC];
};

struct RecoveredGlobal_80069C94_camera_controller_registry {
    s32 value;
    u8 remaining[0x64];
};

struct RecoveredGlobal_80069C94_TCameraCtrl__data_804FF628 {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_80069D04_camera_controller_registry {
    s32 value;
    u8 remaining[0x64];
};

struct RecoveredGlobal_80069D04_TCameraCtrl__data_804FF628 {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_800687C8_TCameraCtrl__data_804FF6C4 {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_80069304_TCameraCtrl__data_804FF628 {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_8006961C_TCameraCtrl__data_804FF628 {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634 {
    s32 value;
    u8 remaining[0x44];
};

struct RecoveredGlobal_8006961C_lbl_8058CA60 {
    s32 value;
    u8 remaining[0x54];
};

struct RecoveredGlobal_80069258_TCameraCtrl__data_804FF6D0 {
    s32 value;
    u8 remaining[0x2C];
};

struct RecoveredGlobal_80069258_TCameraCtrl__data_804FF700 {
    s32 value;
    u8 remaining[0xBC];
};

struct RecoveredGlobal_80069258_main_task {
    s32 value;
    u8 remaining[0x30];
};

struct RecoveredGlobal_80069A6C_camera_controller_registry {
    s32 value;
    u8 remaining[0x64];
};

struct RecoveredGlobal_80069A6C_TCameraCtrl__data_804FF628 {
    u8 value;
    u8 remaining[0xB];
};

extern "C" {
s32 set_clamped_field27c__6TLobbyFPvf(s32 *);
void apply_clamped_field_27c__6TLobbyFv(void);
s32 get_field_0x280__6TLobbyFPv(void *p);
void set_menu_index__6TLobbyFPvi(void *p, s32 v);
s32 is_ready__6TLobbyFPv(s32 *);
void is_sound_enabled(void);
s32 is_special_sound_id(u32 x);
void set_sound_slot_special_scale(s32 slot, f32 scale);
s32 alloc_looping_sound_slot(u32 id, s32 actor, const void *position, s32 base, s32 flags);
extern const f32 lbl_805DC768;
s32 normalize_sound_request(u32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 alloc_one_shot_sound_slot(u32 id, const void *position, s32 base, s32 flags);
s32 play_packed_sound_once(u32 arg0, s32 arg1, s32 arg2, s32 arg3);
void TLobby__sub_80227AF8(s32 slot, const Vec *position);
int release_sound_with_fade(void* p);
int TLobby__sub_80227D38(void);
void handle_6xB2_play_sound_from_player(void *arg0);

u16 TCameraCtrl__sub_8006A5DC();
void TLobby__sub_8023F754(s32, s32);
int fade_out_sound_slot(void*, int);
int fade_voice_channels__6TLobbyFi(void*);
void *get_player_by_client_id(s32 i);
s32 bswap_6xB2_play_sound();
s32 on_set_mode__6TLobbyFv(s32);
void set_mode__6TLobbyFPvi(void *arg0, s32 arg1);


extern s32 local_client_id;

typedef char RecoveredGlobal_8000F764_TKeyBoardControl__data_80506270_size[sizeof(RecoveredGlobal_8000F764_TKeyBoardControl__data_80506270) == 0xB0 ? 1 : -1];
typedef char RecoveredGlobal_8000F7FC_lbl_80515F48_size[sizeof(RecoveredGlobal_8000F7FC_lbl_80515F48) == 0x28 ? 1 : -1];


typedef char RecoveredGlobal_8000F90C_lbl_804FE120_size[sizeof(RecoveredGlobal_8000F90C_lbl_804FE120) == 0x18 ? 1 : -1];
typedef char RecoveredGlobal_8000F8FC_lbl_804FE120_size[sizeof(RecoveredGlobal_8000F8FC_lbl_804FE120) == 0x18 ? 1 : -1];
typedef char RecoveredGlobal_8000F8EC_lbl_804FE120_size[sizeof(RecoveredGlobal_8000F8EC_lbl_804FE120) == 0x18 ? 1 : -1];
typedef char RecoveredGlobal_8000F91C_lbl_804FE120_size[sizeof(RecoveredGlobal_8000F91C_lbl_804FE120) == 0x18 ? 1 : -1];
typedef char RecoveredGlobal_8000F9E4_lbl_804FE120_size[sizeof(RecoveredGlobal_8000F9E4_lbl_804FE120) == 0x18 ? 1 : -1];
typedef char RecoveredGlobal_8000F9CC_lbl_804FE120_size[sizeof(RecoveredGlobal_8000F9CC_lbl_804FE120) == 0x18 ? 1 : -1];





typedef char RecoveredGlobal_80069094_camera_controller_registry_size[sizeof(RecoveredGlobal_80069094_camera_controller_registry) == 0x68 ? 1 : -1];
typedef char RecoveredGlobal_800687E4_TCameraCtrl__data_804FF6C4_size[sizeof(RecoveredGlobal_800687E4_TCameraCtrl__data_804FF6C4) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_800687C8_TCameraCtrl__data_804FF6C4_size[sizeof(RecoveredGlobal_800687C8_TCameraCtrl__data_804FF6C4) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_80069024_TCameraCtrl__data_804FF634_size[sizeof(RecoveredGlobal_80069024_TCameraCtrl__data_804FF634) == 0x48 ? 1 : -1];
typedef char RecoveredGlobal_80069024_lbl_804FF67C_size[sizeof(RecoveredGlobal_80069024_lbl_804FF67C) == 0x48 ? 1 : -1];
typedef char RecoveredGlobal_800691C8_TCameraCtrl__data_804FF6D0_size[sizeof(RecoveredGlobal_800691C8_TCameraCtrl__data_804FF6D0) == 0x30 ? 1 : -1];
typedef char RecoveredGlobal_800691C8_TCameraCtrl__data_804FF700_size[sizeof(RecoveredGlobal_800691C8_TCameraCtrl__data_804FF700) == 0xC0 ? 1 : -1];
typedef char RecoveredGlobal_800691C8_main_task_size[sizeof(RecoveredGlobal_800691C8_main_task) == 0x34 ? 1 : -1];
typedef char RecoveredGlobal_80069148_TCameraCtrl__data_804FF6D0_size[sizeof(RecoveredGlobal_80069148_TCameraCtrl__data_804FF6D0) == 0x30 ? 1 : -1];
typedef char RecoveredGlobal_80069148_TCameraCtrl__data_804FF700_size[sizeof(RecoveredGlobal_80069148_TCameraCtrl__data_804FF700) == 0xC0 ? 1 : -1];
typedef char RecoveredGlobal_80069258_TCameraCtrl__data_804FF6D0_size[sizeof(RecoveredGlobal_80069258_TCameraCtrl__data_804FF6D0) == 0x30 ? 1 : -1];
typedef char RecoveredGlobal_80069258_TCameraCtrl__data_804FF700_size[sizeof(RecoveredGlobal_80069258_TCameraCtrl__data_804FF700) == 0xC0 ? 1 : -1];
typedef char RecoveredGlobal_80069258_main_task_size[sizeof(RecoveredGlobal_80069258_main_task) == 0x34 ? 1 : -1];
typedef char RecoveredGlobal_800695E8_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_800695E8_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_80069304_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_80069304_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_8006961C_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634_size[sizeof(RecoveredGlobal_8006961C_TCameraCtrl__data_804FF634) == 0x48 ? 1 : -1];
typedef char RecoveredGlobal_8006961C_lbl_8058CA60_size[sizeof(RecoveredGlobal_8006961C_lbl_8058CA60) == 0x58 ? 1 : -1];
typedef char RecoveredGlobal_80069A6C_camera_controller_registry_size[sizeof(RecoveredGlobal_80069A6C_camera_controller_registry) == 0x68 ? 1 : -1];
typedef char RecoveredGlobal_80069A6C_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_80069A6C_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_80069C94_camera_controller_registry_size[sizeof(RecoveredGlobal_80069C94_camera_controller_registry) == 0x68 ? 1 : -1];
typedef char RecoveredGlobal_80069C94_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_80069C94_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_80069D04_camera_controller_registry_size[sizeof(RecoveredGlobal_80069D04_camera_controller_registry) == 0x68 ? 1 : -1];
typedef char RecoveredGlobal_80069D04_TCameraCtrl__data_804FF628_size[sizeof(RecoveredGlobal_80069D04_TCameraCtrl__data_804FF628) == 0xC ? 1 : -1];





}

struct RecoveredGlobal_80228634_lbl_804CBE98 {
    s32 value;
    u8 remaining[0x1AC];
};

struct RecoveredGlobal_80228754_lbl_804CBE98 {
    s32 value;
    u8 remaining[0x1AC];
};

struct RecoveredGlobal_802286C4_lbl_804CBE98 {
    s32 value;
    u8 remaining[0x1AC];
};

struct RecoveredGlobal_8022804C_lbl_80514F64 {
    s32 value;
    u8 remaining[0xC38];
};

struct RecoveredGlobal_80228074_lbl_80514F64 {
    s32 value;
    u8 remaining[0xC38];
};

struct RecoveredGlobal_8022809C_lbl_80514F64 {
    s32 value;
    u8 remaining[0xC38];
};

struct RecoveredGlobal_802280C4_lbl_80514F64 {
    s32 value;
    u8 remaining[0xC38];
};

struct RecoveredGlobal_802287F0_lbl_80515BA0 {
    s32 value;
    u8 remaining[0x24];
};

struct O_80228A74 { u8 pad[0x1c]; char names[1][0x20]; };

struct P_80228A74 { u8 pad[0x109c]; s32 count; };

struct L_8022884C { u8 pad[0x109c]; s32 count; s32 hi; s32 lo; };

extern "C" {
s32 select_area_entrance(void *arg0);
s32 lookup_scene_object__6TLobbyFPv(s32, void *);
extern RecoveredGlobal_80228634_lbl_804CBE98 area_initializer_dispatch_table;
void run_area_scene_cleanup(u8 *arg0);
void promote_area_floor(u8 *arg0);
void load_area_scene_and_init(u8 *arg0);
s32 TLobby__sub_802401C8(void *);
s32 update_sound_frame(void *);
void update_global_sound_frame(void);
s32 reset_sound_state__6TLobbyFPv(u8 *arg0);
void TLobby__sub_8022809C(void);
int render_tick__Fv(void);
s32 init_sound_aux_effects(void *);
s32 validate_and_set_selection__6TLobbyFPvi(void *, int);
void TLobby__sub_803382E4(void);
s32 TLobby__sub_803CB81C();
extern RecoveredGlobal_802287F0_lbl_80515BA0 lbl_80515BA0;
void *reset_sound_owner_state(void *self);
void *TLobby__sub_80240808(void *arg0, s16 arg1);
void *__register_global_object(void *obj, void *dtor, void *entry);
extern char lbl_80514F58[];
void TLobby__sub_80228118(void);
char *strcpy(char *dst, const char *src);
void clear_work_buffer(u8 *arg0);
extern char lbl_805DC788[4];
u32 strlen(const char *s);
s32 debug_printf_at(u32, void *, ...);
s32 TLobby__sub_80226B64(int);
extern s32 floor_sound_bank_table[];
extern s32 floor_sound_bank_volume_table[];
void load_floor_sound_bank(s32 arg0);
s32 get_floor_map_terrain(s32);
s32 pop_sound_groups__6TLobbyFPvi(void *p, s32 arg1);
void __ct__7TObjectFP7TObject(void *);
void memset(void *, int, int);

    extern float lbl_805DC76C;


typedef char RecoveredGlobal_8022804C_lbl_80514F64_size[sizeof(RecoveredGlobal_8022804C_lbl_80514F64) == 0xC3C ? 1 : -1];

typedef char RecoveredGlobal_80228074_lbl_80514F64_size[sizeof(RecoveredGlobal_80228074_lbl_80514F64) == 0xC3C ? 1 : -1];

typedef char RecoveredGlobal_8022809C_lbl_80514F64_size[sizeof(RecoveredGlobal_8022809C_lbl_80514F64) == 0xC3C ? 1 : -1];

typedef char RecoveredGlobal_802280C4_lbl_80514F64_size[sizeof(RecoveredGlobal_802280C4_lbl_80514F64) == 0xC3C ? 1 : -1];


void TLobby::clear_ready_flag_unless_locked() {
    if (get_current_floor_area() != AREA_LOBBY) {
        *(s32 *)((s8 *)this + 0x20) = (s32) (*(s32 *)((s8 *)this + 0x20) & 0xFFFFFFFE);
    }
}

void TLobby::set_area(s32 arg1) {
    *(s32 *)&this->m_next = arg1;
    *(s32 *)((s8 *)this + 0x18) = get_floor_map_terrain(*(s32 *)&this->m_next);
}

#pragma push
#pragma fp_contract on
s32 select_area_entrance(void *arg0) {
    s32 temp_r0;
    s32 temp_r3;
    if ((s32) *(s32 *)((s8 *)arg0 + 0) > 0x11) {
        return 4;
    }
    if (*(s32 *)((s8 *)arg0 + 0x20) & 1) {
        return 2;
    }
    if ((TLobby::get_instance() == 0) && (get_floor_area(*(s32 *)((s8 *)arg0 + 0)) == 0xD)) {
        switch (get_floor_area(*(s32 *)((s8 *)arg0 + 4))) {
        case 8:
        case 9:
        case 10:
            return 1;
        default:
            return 0;
        }
    }
    temp_r0 = *(s32 *)((s8 *)arg0 + 4) - *(s32 *)((s8 *)arg0 + 0);
    if (temp_r0 >= 0) {
        return 1;
    }
    return (temp_r0 < 0) ? 0 : 4;
}
#pragma pop

typedef char RecoveredGlobal_80228634_lbl_804CBE98_size[sizeof(RecoveredGlobal_80228634_lbl_804CBE98) == 0x1B0 ? 1 : -1];
void run_area_scene_cleanup(u8 *arg0) {
    s32 sp8;
    s32 (*var_r12)(s32);
    s32 *var_r4;
    s32 var_r3;
    u8 *var_r31;
    var_r4 = &sp8;
    var_r31 = arg0;
    var_r3 = *(s32 *)((s8 *)arg0 + 4);
    if (lookup_scene_object__6TLobbyFPv(var_r3, var_r4) != 0) {
        var_r3 = (s32) &area_initializer_dispatch_table.value;
        var_r3 = (s32) &area_initializer_dispatch_table.value;
        var_r3 += sp8 * 0xC;
        var_r12 = *(s32 (**)(s32))((s8 *)var_r3 + 8);
        var_r12(var_r3);
    } else {
        var_r3 = (s32) &area_initializer_dispatch_table.value;
        var_r3 = (s32) &area_initializer_dispatch_table.value;
        var_r3 += *(s32 *)((s8 *)var_r31 + 4) * 0xC;
        var_r12 = *(s32 (**)(s32))((s8 *)var_r3 + 8);
        var_r12(var_r3);
    }
    *(s32 *)((s8 *)var_r31 + 4) = 0;
    *(s32 *)((s8 *)var_r31 + 8) = 0;
    *(s32 *)((s8 *)var_r31 + 0xC) = 0;
}

typedef char RecoveredGlobal_80228754_lbl_804CBE98_size[sizeof(RecoveredGlobal_80228754_lbl_804CBE98) == 0x1B0 ? 1 : -1];

typedef char RecoveredGlobal_802286C4_lbl_804CBE98_size[sizeof(RecoveredGlobal_802286C4_lbl_804CBE98) == 0x1B0 ? 1 : -1];
void load_area_scene_and_init(u8 *arg0) {
    s32 sp8;
    s32 (*var_r12)(s32);
    s32 *var_r4;
    s32 var_r3;
    u8 *var_r31;
    var_r31 = arg0;
    var_r3 = *(s32 *)((s8 *)arg0 + 4);
    set_current_floor_area((var_r3));
    var_r3 = *(s32 *)((s8 *)var_r31 + 0x10);
    TScene::set_scene(var_r3);
    var_r3 = *(s32 *)((s8 *)var_r31 + 4);
    var_r4 = &sp8;
    if (lookup_scene_object__6TLobbyFPv(var_r3, var_r4) != 0) {
        var_r3 = (s32) &(*(RecoveredGlobal_802286C4_lbl_804CBE98 *)&area_initializer_dispatch_table).value;
        var_r3 = (s32) &(*(RecoveredGlobal_802286C4_lbl_804CBE98 *)&area_initializer_dispatch_table).value;
        var_r3 += sp8 * 0xC;
        var_r12 = *(s32 (**)(s32))((s8 *)var_r3 + 4);
        var_r12(var_r3);
        return;
    }
    var_r3 = (s32) &(*(RecoveredGlobal_802286C4_lbl_804CBE98 *)&area_initializer_dispatch_table).value;
    var_r3 = (s32) &(*(RecoveredGlobal_802286C4_lbl_804CBE98 *)&area_initializer_dispatch_table).value;
    var_r3 += *(s32 *)((s8 *)var_r31 + 4) * 0xC;
    var_r12 = *(s32 (**)(s32))((s8 *)var_r3 + 4);
    var_r12(var_r3);
}

void promote_area_floor(u8 *arg0) {
    s32 sp8;
    s32 (*var_r12)(s32);
    s32 *var_r4;
    s32 var_r3;
    u8 *var_r31;
    var_r4 = &sp8;
    var_r31 = arg0;
    var_r3 = *(s32 *)((s8 *)arg0 + 4);
    if (lookup_scene_object__6TLobbyFPv(var_r3, var_r4) != 0) {
        var_r3 = (s32) &(*(RecoveredGlobal_80228754_lbl_804CBE98 *)&area_initializer_dispatch_table).value;
        var_r3 = (s32) &(*(RecoveredGlobal_80228754_lbl_804CBE98 *)&area_initializer_dispatch_table).value;
        var_r3 += sp8 * 0xC;
        var_r12 = *(s32 (**)(s32))((s8 *)var_r3 + 8);
        var_r12(var_r3);
    } else {
        var_r3 = (s32) &(*(RecoveredGlobal_80228754_lbl_804CBE98 *)&area_initializer_dispatch_table).value;
        var_r3 = (s32) &(*(RecoveredGlobal_80228754_lbl_804CBE98 *)&area_initializer_dispatch_table).value;
        var_r3 += *(s32 *)((s8 *)var_r31 + 4) * 0xC;
        var_r12 = *(s32 (**)(s32))((s8 *)var_r3 + 8);
        var_r12(var_r3);
    }
    *(s32 *)((s8 *)var_r31 + 0) = (s32) *(s32 *)((s8 *)var_r31 + 4);
    *(s32 *)((s8 *)var_r31 + 4) = (s32) *(s32 *)((s8 *)var_r31 + 0xC);
    *(s32 *)((s8 *)var_r31 + 0x10) = (s32) *(s32 *)((s8 *)var_r31 + 0x18);
    TLobby::reset_story_select_state();
}

typedef char RecoveredGlobal_802287F0_lbl_80515BA0_size[sizeof(RecoveredGlobal_802287F0_lbl_80515BA0) == 0x28 ? 1 : -1];
s32 TLobby::init_range_zero_global() { return ((TLobby *)((s32) &lbl_80515BA0.value))->init_range_zero(); }


struct O_80228A74;






extern s32 lbl_804CC048[];


}

RecoveredGlobal_802287F0_lbl_80515BA0 lbl_80515BA0;

__declspec(section ".ctors") static void *const __sinit_TLobby_80228154_cpp_ref = (void *)TLobby::init_range_zero_global;
