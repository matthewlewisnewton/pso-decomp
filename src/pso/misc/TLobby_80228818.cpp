#include "pso/system/SoundEffect.h"
struct Vec;
#include "types.h"
#include "pso/misc/TLobby.h"
#include "pso/item/TUnk_804CC048.h"
#include "pso/map/FloorArea.h"
#include "pso/misc/TLobby_80207644.h"

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





typedef char RecoveredGlobal_80228634_lbl_804CBE98_size[sizeof(RecoveredGlobal_80228634_lbl_804CBE98) == 0x1B0 ? 1 : -1];

typedef char RecoveredGlobal_80228754_lbl_804CBE98_size[sizeof(RecoveredGlobal_80228754_lbl_804CBE98) == 0x1B0 ? 1 : -1];

typedef char RecoveredGlobal_802286C4_lbl_804CBE98_size[sizeof(RecoveredGlobal_802286C4_lbl_804CBE98) == 0x1B0 ? 1 : -1];


typedef char RecoveredGlobal_802287F0_lbl_80515BA0_size[sizeof(RecoveredGlobal_802287F0_lbl_80515BA0) == 0x28 ? 1 : -1];

s32 TLobby::init_range_zero() {
    init_range(0);
    return (s32)this;
}

struct O_80228A74;

#pragma push
#pragma opt_propagation off
void TUnk_804CC048::render() {
    L_8022884C *self = (L_8022884C *)this;
    s32 off;
    s32 i;
    s32 t;
    i = 0;
    off = 0;
    while (i < self->count) {
        t = off + 0x1c;
        debug_printf_at((self->hi << 16) | (self->lo + i), (u8 *)self + t);
        i++;
        off += 0x20;
    }
}
#pragma pop

void TLobby::tokenize_args(char *s) {
    char *start;
    s32 quoted;
    clear_work_buffer((u8 *)this);
    start = s;
    quoted = 0;
    for (;;) {
        switch (*s) {
        case 0:
            this->add_token(start);
            return;
        case '"':
            if (quoted) {
                quoted = 0;
                *s = 0;
                s++;
            } else {
                s++;
                quoted = 1;
                start = s;
            }
            break;
        case '\t':
        case '\n':
            if (quoted) {
                s++;
            } else {
                *s = 0;
                s++;
                this->add_token(start);
                start = s;
            }
            break;
        default:
            s++;
            break;
        }
    }
}

void TLobby::parse_csv_line(char *s) {
    char *start;
    s32 quoted;
    clear_work_buffer((u8 *)this);
    start = s;
    quoted = 0;
    for (;;) {
        switch (*s) {
        case 0:
            this->add_token(start);
            return;
        case '"':
            if (quoted) {
                quoted = 0;
                *s = 0;
                s++;
            } else {
                s++;
                quoted = 1;
                start = s;
            }
            break;
        case '\t':
        case '\n':
        case ',':
            if (quoted) {
                s++;
            } else {
                *s = 0;
                s++;
                this->add_token(start);
                start = s;
            }
            break;
        default:
            s++;
            break;
        }
    }
}

void TLobby::add_token(const char *src) {
    O_80228A74 *self = (O_80228A74 *)this;
    strcpy(self->names[((P_80228A74 *)self)->count++], src);
}

void clear_work_buffer(u8 *arg0) {
    memset(arg0 + 0x1C, 0, 0x1000);
    *(s32 *)((s8 *)arg0 + 0x109C) = 0;
}

extern s32 lbl_804CC048[];

void *TUnk_804CC048::construct(void *arg1, void *arg2, void *arg3) {
    __ct__7TObjectFP7TObject(this);
    *(s32 **)((s8 *)this + 0x18) = lbl_804CC048;
    *(void **)((s8 *)this + 0x10A0) = arg2;
    this->m_10a4 = arg3;
    memset((void *)((void *)((char *)this + 28)), 0, 4096);
    this->m_109c = 0;
    return this;
}
void TLobby::trim_whitespace() {
    char *s = (char *)this;
    s32 len = strlen(s);
    s32 i;
    for (i = 0; i <= len && ((u8 *)s)[i] <= ' '; i++) {
    }
    if (i > len) {
        strcpy(s, lbl_805DC788);
    } else {
        for (; ((u8 *)s)[len] <= ' '; len--) {
            s[len] = 0;
        }
        strcpy(s, s + i);
    }
}

}

