#include "pso/system/SoundEffect.h"
#include "types.h"
#include "pso/misc/TKeyBoardControl_8025CB70.h"
#include "pso/misc/TWindowSubMag_802627D8.h"
#include "pso/misc/TWindowSubStatusDisp_803DEE6C.h"
#include "pso/misc/TWindowKeyBoardSoft.h"
#include "pso/misc/TWindowKeyBoardSoft_8025B85C.h"
#include "pso/misc/TWindowChoiceSetting.h"
#include "pso/ui/TAdMultiPlyChrSelectGC.h"
#include "pso/ui/Language.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/unk/text_8026C664.h"
#include "pso/misc/TWindowKeyBoardBase.h"

struct UV_80262038 {
    f32 u;
    f32 v;
};

struct Quad_80262038 {
    f32 x;
    f32 y;
    f32 x2;
    f32 y2;
    f32 u;
    f32 v;
    f32 u2;
    f32 v2;
};

#include <stddef.h>
#include "pso/misc/TKeyBoardControl.h"
#include "pso/TWindowEffectLight.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowSubMag.h"
struct RecoveredGlobal_8026088C_lbl_8050E208 {
    s32 value;
    u8 remaining[0x1AC];
};

struct RecoveredFields_8026088C_arg0 {
    u8 unknown_0[0x60];
    s32 field_60;
    u8 unknown_64[0x8];
    u32 field_6C;
};

typedef void (TWindowKeyBoardSoft::*SoftKeyAction)();
struct SoftKeyActionData_80260904 {
    u8 window_descriptor[0x14];
    SoftKeyAction initial[22];
    SoftKeyAction active[22];
};
struct SoftKeyLayout_80260904 {
    u8 page_count;
    u8 page_width;
    u8 pad[2];
    const u16 **pages;
};
typedef char SoftKeyActionData_size_80260904[sizeof(SoftKeyActionData_80260904) == 0x224 ? 1 : -1];

extern "C" {
extern SoftKeyActionData_80260904 soft_keyboard_window_and_action_data;
extern s8 lbl_805D6458;
s32 get_chat_shortcut(s32);
s32 set_input_mode__20TWindowSubStatusDispFUc(s32, s32);
s32 TWindowShortListCtrl__check_controller_button(void *, int, int);
struct RecoveredGlobal_80260808_lbl_8050E208 {
    s32 value;
    u8 remaining[0x1AC];
};

struct RecoveredGlobal_8026062C_TWindowKeyBoardSoft__data_8044F124
{
  s32 value;
  u8 remaining[0x10];
};

struct RecoveredGlobal_8026062C_TWindowKeyBoardSoft__data_804CB7C8
{
  s32 value;
  u8 remaining[0x6C];
};

struct Win_802605DC { u8 p0[0x65]; s8 f65; s8 f66; };

typedef struct RecoveredGlobal_8026062C_TWindowKeyBoardSoft__data_8044F124 RecoveredGlobal_8026062C_TWindowKeyBoardSoft__data_8044F124;

typedef struct RecoveredGlobal_8026062C_TWindowKeyBoardSoft__data_804CB7C8 RecoveredGlobal_8026062C_TWindowKeyBoardSoft__data_804CB7C8;

typedef char RecoveredGlobal_8026062C_TWindowKeyBoardSoft__data_8044F124_size[((sizeof(RecoveredGlobal_8026062C_TWindowKeyBoardSoft__data_8044F124)) == 0x14) ? (1) : (-1)];

typedef char RecoveredGlobal_8026062C_TWindowKeyBoardSoft__data_804CB7C8_size[((sizeof(RecoveredGlobal_8026062C_TWindowKeyBoardSoft__data_804CB7C8)) == 0x70) ? (1) : (-1)];

typedef char RecoveredGlobal_80260808_lbl_8050E208_size[sizeof(RecoveredGlobal_80260808_lbl_8050E208) == 0x1B0 ? 1 : -1];

struct Vec2_802615B8 {
    f32 x;
    f32 y;
};

struct Lines_80261DD8 {
    Vec2_802615B8 *verts;
    u32 *colors;
    s32 f8;
    s32 count;
};


s32 draw_default_entry__9TWindowDDFl();
int update_keyboard_close_mode(void*);
void calc_cursor_step__19TWindowKeyBoardSoftFiPvPv(s32 arg0, s32 *arg1, s32 *arg2);
f32 calc_key_x__19TWindowKeyBoardSoftFiii(s32 arg0, s32 arg1, s32 arg2);
s32 calc_key_index__19TWindowKeyBoardSoftFiii(s32 arg1, s32 arg2, s32 arg3);
f32 TWindowKeyBoardSoft__sub_802606E0(TWindowKeyBoardSoft *);
void TWindowKeyBoardSoft__sub_80260760(void *self, s32 key, s32 *count, u32 *color);
void TWindowKeyBoardSoft__sub_80260E30(void *self, s32 port);
void TWindowKeyBoardSoft__sub_80261134(void *self);
extern u8 lbl_8044F138[];
void TKeyBoardControl__sub_802613A4(TKeyBoardControl *arg0);
f32 TWindowKeyBoardSoft__sub_802614DC(u8 *, u8 *, f32, f32, f32, f32);
s32 TWindowKeyBoardSoft__sub_802616BC(void *, int);
void reset_gauge__20TWindowSubStatusDispFPv(s32);
s32 end_render_forward__20TWindowSubStatusDispFPv();
void render_forward__20TWindowSubStatusDispFPv();
void begin_render__20TWindowSubStatusDispFl();
u16 map_char_to_font_code(u16);
u8 calc_gauge_scale__20TWindowSubStatusDispFPvPvi(s32, void *, s32);
void set_glyph_quad_extents(u8, void *);
extern const f32 lbl_805DD09C, lbl_805DD0A0, lbl_805DD0A4, lbl_805DD0A8;
extern const f32 lbl_805DD0AC, lbl_805DD0B0;
extern const f32 lbl_8044F164[][2], lbl_8044F1B4[][2], lbl_8044F204[][2];
void TWindowKeyBoardSoft__sub_80261DD8(TWindowKeyBoardSoft *, TWindowKeyBoardSoft *);
s32 TWindowKeyBoardSoft__sub_8026227C(TWindowKeyBoardSoft *, TWindowKeyBoardSoft *);
s32 get_player__20TWindowSubStatusDispFv();
extern GinjaTextureList *lbl_805D63F0;
extern const f32 TWindowKeyBoardSoft__data_805DD098;
extern const f32 lbl_805DD0B8;
extern const f32 lbl_805DD0CC;
extern const f32 lbl_805DD0D0;
s32 get_flag_bit5__19TWindowKeyBoardSoftFv();

extern RecoveredGlobal_8026062C_TWindowKeyBoardSoft__data_8044F124 TWindowKeyBoardSoft__data_8044F124;
extern RecoveredGlobal_8026062C_TWindowKeyBoardSoft__data_804CB7C8 TWindowKeyBoardSoft__data_804CB7C8;
extern u8 *TWindowKeyBoardSoft__language_text_resources;
extern const f32 TWindowKeyBoardSoft__data_805DD078;
extern const f32 TWindowKeyBoardSoft__data_805DD07C;
extern const f32 TWindowKeyBoardSoft__data_805DD080;
extern const f32 TWindowKeyBoardSoft__data_805DD088;
extern const f32 TWindowKeyBoardSoft__data_805DD094;
extern RecoveredGlobal_80260808_lbl_8050E208 controller_input_state;
extern void *local_client_id;
extern const f32 lbl_805DD084;
extern const f32 lbl_805DD08C;
void apply_context_transform_to_rect(void *, void *);
void draw_color_lines(Lines_80261DD8 *l, s32 n, s32 flags, f32 scale);
extern UV_80262038 keyboard_key_frame_uv_table[];
extern const f32 TWindowKeyBoardSoft__data_805DD090;
extern const f32 lbl_805DD0C8;

void calc_cursor_step__19TWindowKeyBoardSoftFiPvPv(s32 arg0, s32 *arg1, s32 *arg2) {
    switch (current_language) {
    case LANGUAGE_JAPANESE:
        if ((get_flag_bit5__19TWindowKeyBoardSoftFv() != 0) || (((TWindowKeyBoardSoft *)arg0)->get_flag_bit6() != 0) || (((TWindowKeyBoardSoft *)arg0)->is_cursor_locked() != 0)) {
            *arg1 = 4;
            *arg2 = 4;
            return;
        }
        if (TWindowSubMag__sub_802627D8((void *)arg0) != 0) {
            *arg1 = 4;
            *arg2 = 5;
            return;
        }
        *arg1 = 0;
        *arg2 = 5;
        return;
    case LANGUAGE_ENGLISH:
        if ((get_flag_bit5__19TWindowKeyBoardSoftFv() != 0) || (((TWindowKeyBoardSoft *)arg0)->get_flag_bit6() != 0) || (((TWindowKeyBoardSoft *)arg0)->is_cursor_locked() != 0)) {
            *arg1 = 0;
            *arg2 = 0;
            return;
        }
        *arg1 = 0;
        *arg2 = 1;
        return;
    case LANGUAGE_GERMAN:
    case LANGUAGE_FRENCH:
    case LANGUAGE_SPANISH:
        if ((get_flag_bit5__19TWindowKeyBoardSoftFv() != 0) || (((TWindowKeyBoardSoft *)arg0)->get_flag_bit6() != 0) || (((TWindowKeyBoardSoft *)arg0)->is_cursor_locked() != 0)) {
            *arg1 = 0;
            *arg2 = 0;
            return;
        }
        if (TWindowSubMag__sub_802627D8((void *)arg0) != 0) {
            *arg1 = 0;
            *arg2 = 1;
            return;
        }
        *arg1 = 0;
        *arg2 = 2;
        return;
    }
}

#pragma push
#pragma fp_contract on
s32 TWindowKeyBoardSoft::sub_802605DC() {
    s32 idx = calc_key_index__19TWindowKeyBoardSoftFiii((s32)(((Win_802605DC *)this)), (s32)(((Win_802605DC *)this)->f65), (s32)(((Win_802605DC *)this)->f66));
    return idx + ((s8 *)&TWindowKeyBoardSoft__data_8044F124)[((u8 *)&TWindowKeyBoardSoft__data_804CB7C8)[idx]];
}
#pragma pop

#pragma push
#pragma fp_contract on
f32 calc_key_x__19TWindowKeyBoardSoftFiii(s32 arg0, s32 arg1, s32 arg2) {
  f32 new_var;
  s32 sp8;
  s32 temp_r31;
  s32 temp_r3;
  temp_r3 = calc_key_index__19TWindowKeyBoardSoftFiii(arg0, arg1, arg2);
  temp_r31 = arg1 + ((s8) (*((u8 *) (((s8 *) (((u8 *)&TWindowKeyBoardSoft__data_8044F124.value) + (*((u8 *) (((s8 *) (((u8 *)&TWindowKeyBoardSoft__data_804CB7C8.value) + temp_r3)) + 0))))) + 0))));
  TWindowKeyBoardSoft__sub_80260760((void *) arg0, (int) temp_r3, &sp8, NULL);
  new_var = TWindowKeyBoardSoft::calc_key_coord(arg0, sp8);
  return TWindowKeyBoardSoft__data_805DD078 + ((TWindowKeyBoardSoft__data_805DD07C * ((f32) temp_r31)) + (TWindowKeyBoardSoft__data_805DD080 * new_var));
}
#pragma pop

#pragma push
#pragma fp_contract on
s32 calc_key_index__19TWindowKeyBoardSoftFiii(s32 arg1, s32 arg2, s32 arg3) {
    return arg2 + (arg3 * 0x10);
}
#pragma pop

#pragma push
#pragma fp_contract on
#pragma fp_contract on
f32 TWindowKeyBoardSoft__sub_802606E0(TWindowKeyBoardSoft *) {
    return -((TWindowKeyBoardSoft__data_805DD080 * (f32) (*(u8 *)((s8 *)TWindowKeyBoardSoft__language_text_resources + 0) * *(u8 *)((s8 *)TWindowKeyBoardSoft__language_text_resources + 1))) - lbl_805DD084);
}
#pragma pop

#pragma push
#pragma fp_contract on
#pragma fp_contract on
f32 TWindowKeyBoardSoft::calc_key_coord(s32 arg0, s32 arg1) {
    return (TWindowKeyBoardSoft__data_805DD07C * (f32) arg1) + TWindowKeyBoardSoft__data_805DD078;
}
#pragma pop

void TWindowKeyBoardSoft__sub_80260760(void *self, s32 key, s32 *count, u32 *color) {
    s32 n;
    u32 c;
    switch (((u8 *)&TWindowKeyBoardSoft__data_804CB7C8.value)[key]) {
    case 0:
        n = 1;
        c = 0xFF173D84;
        break;
    case 1:
        n = 1;
        c = 0xFF621784;
        break;
    case 2:
    case 3:
        n = 2;
        c = 0xFF6A6E13;
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        n = 4;
        c = 0xFF4F700C;
        break;
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
        n = 10;
        c = 0xFF842317;
        break;
    }
    if (count != NULL) {
        *count = n;
    }
    if (color != NULL) {
        *color = c;
    }
}

#pragma push
#pragma fp_contract on
void TWindowKeyBoardSoft::sub_80260808(s32 arg1) {
    s32 temp_r5;
    temp_r5 = arg1 * 0x50;
    if ((TWindowShortListCtrl__check_controller_button((void *) ((u8 *)&controller_input_state.value + temp_r5 + 0x20), 2, temp_r5) != 0) && ((u32) *(u32 *)((s8 *)((u8 *)this) + 0x6C) != 0U)) {
        this->m_7c = (s32) (this->m_7c & 0xFFFFFFEF);
        play_sound_effect(0x52F16, 0, 0, 0);
        ((TWindowKeyBoardSoft *)(*(u32 *)((s8 *)((u8 *)this) + 0x6C)))->handle_backspace();
    }
}
#pragma pop

typedef char RecoveredGlobal_8026088C_lbl_8050E208_size[sizeof(RecoveredGlobal_8026088C_lbl_8050E208) == 0x1B0 ? 1 : -1];
typedef char RecoveredFields_8026088C_arg0_60_offset[offsetof(RecoveredFields_8026088C_arg0, field_60) == 0x60 ? 1 : -1];
typedef char RecoveredFields_8026088C_arg0_6C_offset[offsetof(RecoveredFields_8026088C_arg0, field_6C) == 0x6C ? 1 : -1];
void TWindowKeyBoardSoft::update_keyboard_child_input_from_controller(s32 arg1) {
    u32 temp_r3;
    if (((s32 (*)(void *, int))TWindowShortListCtrl__check_controller_button)((void *)((void *) ((u8 *)&(*(RecoveredGlobal_8026088C_lbl_8050E208 *)&controller_input_state).value + (arg1 * 0x50) + 0x20)), 0x400) != 0) {
        temp_r3 = ((RecoveredFields_8026088C_arg0 *)((u8 *)this))->field_6C;
        if (temp_r3 != 0U) {
            ((TWindowKeyBoardSoft *)temp_r3)->update_input_state2();
            if (((TWindowKeyBoardSoft *)(((RecoveredFields_8026088C_arg0 *)((u8 *)this))->field_6C))->is_key_state_2() != 0) {
                ((RecoveredFields_8026088C_arg0 *)((u8 *)this))->field_60 = (s32) (((RecoveredFields_8026088C_arg0 *)((u8 *)this))->field_60 | 0x10);
            }
        }
    }
}

struct KeyCursor_80260904 {
    u8 pad0[0x60];
    u32 flags;
    s8 page;
    s8 cursor_x;
    s8 cursor_y;
    u8 pad67[5];
    TWindowKeyBoardSoft *child;
};

// The original initializes the 22 member-function actions once by copying
// their descriptors from the adjacent keyboard data object. The object and
// its owner remain external; this view records only the observed boundaries.
void TWindowKeyBoardSoft__sub_80260904(void *self, s32 port) {
    KeyCursor_80260904 *kb = (KeyCursor_80260904 *)self;
    SoftKeyLayout_80260904 *layout = (SoftKeyLayout_80260904 *)TWindowKeyBoardSoft__language_text_resources;
    if (!lbl_805D6458) {
        // Individual descriptor copies preserve the original expanded initialization.
        soft_keyboard_window_and_action_data.active[0] = soft_keyboard_window_and_action_data.initial[0];
        soft_keyboard_window_and_action_data.active[1] = soft_keyboard_window_and_action_data.initial[1];
        soft_keyboard_window_and_action_data.active[2] = soft_keyboard_window_and_action_data.initial[2];
        soft_keyboard_window_and_action_data.active[3] = soft_keyboard_window_and_action_data.initial[3];
        soft_keyboard_window_and_action_data.active[4] = soft_keyboard_window_and_action_data.initial[4];
        soft_keyboard_window_and_action_data.active[5] = soft_keyboard_window_and_action_data.initial[5];
        soft_keyboard_window_and_action_data.active[6] = soft_keyboard_window_and_action_data.initial[6];
        soft_keyboard_window_and_action_data.active[7] = soft_keyboard_window_and_action_data.initial[7];
        soft_keyboard_window_and_action_data.active[8] = soft_keyboard_window_and_action_data.initial[8];
        soft_keyboard_window_and_action_data.active[9] = soft_keyboard_window_and_action_data.initial[9];
        soft_keyboard_window_and_action_data.active[10] = soft_keyboard_window_and_action_data.initial[10];
        soft_keyboard_window_and_action_data.active[11] = soft_keyboard_window_and_action_data.initial[11];
        soft_keyboard_window_and_action_data.active[12] = soft_keyboard_window_and_action_data.initial[12];
        soft_keyboard_window_and_action_data.active[13] = soft_keyboard_window_and_action_data.initial[13];
        soft_keyboard_window_and_action_data.active[14] = soft_keyboard_window_and_action_data.initial[14];
        soft_keyboard_window_and_action_data.active[15] = soft_keyboard_window_and_action_data.initial[15];
        soft_keyboard_window_and_action_data.active[16] = soft_keyboard_window_and_action_data.initial[16];
        soft_keyboard_window_and_action_data.active[17] = soft_keyboard_window_and_action_data.initial[17];
        soft_keyboard_window_and_action_data.active[18] = soft_keyboard_window_and_action_data.initial[18];
        soft_keyboard_window_and_action_data.active[19] = soft_keyboard_window_and_action_data.initial[19];
        soft_keyboard_window_and_action_data.active[20] = soft_keyboard_window_and_action_data.initial[20];
        soft_keyboard_window_and_action_data.active[21] = soft_keyboard_window_and_action_data.initial[21];
        lbl_805D6458 = 1;
    }
    if (((s32 (*)(void *, int))TWindowShortListCtrl__check_controller_button)(
            (u8 *)&controller_input_state.value + port * 0x50 + 0x20, 4) == 0 || kb->child == NULL) {
        return;
    }
    if (!(kb->flags & 1)) ((TWindowKeyBoardSoft *)self)->update_focus_flags();
    ((TWindowKeyBoardSoft *)self)->spawn_key_effect(kb->cursor_x, kb->cursor_y);
    if (kb->flags & 0x10) {
        kb->child->vt0();
        if (!kb->child->is_key_state_2()) kb->flags &= ~0x10;
        return;
    }
    u16 code = layout->pages[kb->page][kb->cursor_y * 16 + kb->cursor_x];
    if (code >= 3 && code <= 14) {
        if (TWindowSubMag__sub_80262808(kb->child)) play_sound_effect(0x53F06, 0, 0, 0);
        else if (*(s32 *)get_chat_shortcut(code + 5) != 3) play_sound_effect(0x52D01, 0, 0, 0);
    } else if (code == 2 && (kb->flags & 8)) {
        play_sound_effect(0x53F06, 0, 0, 0);
    } else {
        play_sound_effect(0x52D01, 0, 0, 0);
    }
    if (code < 0x20) {
        if (code < 22) (kb->child->*soft_keyboard_window_and_action_data.active[code])();
        return;
    }
    if (((TWindowKeyBoardSoft *)self)->get_flag_bit5() && (code < 'A' || code > 'Z')) return;
    if (((TWindowKeyBoardSoft *)self)->get_flag_bit6() && !is_alnum__19TWindowKeyBoardSoftFUs(code)) return;
    if (((TWindowKeyBoardSoft *)self)->is_cursor_locked() && (code < '0' || code > '9')) return;
    set_input_mode__20TWindowSubStatusDispFUc((s32)kb->child, 2);
    ((TWindowKeyBoardBase *)kb->child)->insert_character(code);
}

struct KeyCursor_80260E30 {
    u8 pad0[0x60];
    u32 flags;
    u8 layout;
    u8 cursor_x;
    u8 cursor_y;
    u8 pad67[0x6C - 0x67];
    TWindowKeyBoardSoft *child;
};

void TWindowKeyBoardSoft__sub_80260E30(void *self, s32 port) {
    KeyCursor_80260E30 *kb = (KeyCursor_80260E30 *)self;
    s8 dx = 0;
    s8 dy = 0;
    s32 input;
    if (kb->flags & 2) {
        input = (s32)((u8 *)&controller_input_state.value + port * 0x50 + 0x20);
        if (TWindowChoiceSetting::apply_choice(input, 0xF0, 6, 2) == 0) {
            return;
        }
        if (TWindowChoiceSetting::apply_choice(input, 0x10, 6, 2) != 0) {
            dy = -1;
        }
        if (TWindowChoiceSetting::apply_choice(input, 0x20, 6, 2) != 0) {
            dy++;
        }
        if (TWindowChoiceSetting::apply_choice(input, 0x40, 6, 2) != 0) {
            dx = -1;
        }
        if (TWindowChoiceSetting::apply_choice(input, 0x80, 6, 2) != 0) {
            dx++;
        }
    } else {
        input = (s32)((u8 *)&controller_input_state.value + port * 0x50 + 0x20);
        if (TAdMultiPlyChrSelectGC::dispatch_draw_command(input, 0xF0, 6, 2) == 0) {
            return;
        }
        if (TAdMultiPlyChrSelectGC::dispatch_draw_command(input, 0x10, 6, 2) != 0) {
            dy = -1;
        }
        if (TAdMultiPlyChrSelectGC::dispatch_draw_command(input, 0x20, 6, 2) != 0) {
            dy++;
        }
        if (TAdMultiPlyChrSelectGC::dispatch_draw_command(input, 0x40, 6, 2) != 0) {
            dx = -1;
        }
        if (TAdMultiPlyChrSelectGC::dispatch_draw_command(input, 0x80, 6, 2) != 0) {
            dx++;
        }
    }
    play_sound_effect(0x54100, 0, 0, 0);
    if (kb->flags & 0x10) {
        if (dx > 0) {
            kb->child->vt15();
        } else if (dx < 0) {
            kb->child->vt16();
        }
        if (dy > 0) {
            kb->child->vt18();
        } else if (dy < 0) {
            kb->child->vt17();
        }
        return;
    }
    if (dx > 0) {
        kb->cursor_x += lbl_8044F138[((u8 *)&TWindowKeyBoardSoft__data_804CB7C8.value)[(s8)kb->cursor_x + (s8)kb->cursor_y * 16]] + 1;
    }
    if (dx < 0) {
        kb->cursor_x += ((u8 *)&TWindowKeyBoardSoft__data_8044F124.value)[((u8 *)&TWindowKeyBoardSoft__data_804CB7C8.value)[(s8)kb->cursor_x + (s8)kb->cursor_y * 16]] - 1;
    }
    kb->cursor_y += dy;
    if ((s8)kb->cursor_x < 0) {
        kb->cursor_x += 16;
    }
    if ((s8)kb->cursor_x >= 16) {
        kb->cursor_x -= 16;
    }
    if ((s8)kb->cursor_y < 0) {
        kb->cursor_y += 7;
    }
    if ((s8)kb->cursor_y >= 7) {
        kb->cursor_y -= 7;
    }
}

void TWindowKeyBoardSoft__sub_80261134(void *self) {
    KeyCursor_80260E30 *kb = (KeyCursor_80260E30 *)self;
    switch (current_language) {
    case LANGUAGE_JAPANESE:
        kb->layout = 4;
        break;
    case LANGUAGE_ENGLISH:
        kb->layout = 0;
        break;
    case LANGUAGE_GERMAN:
    case LANGUAGE_FRENCH:
    case LANGUAGE_SPANISH:
        kb->layout = 0;
        break;
    }
    ((TWindowKeyBoardSoft *)self)->update_focus_flags();
}

#pragma push
#pragma fp_contract on
void TWindowKeyBoardSoft::update_focus_flags() {
    void *temp_r3;
    void *temp_r3_2;
    void *temp_r4;
    void *temp_r4_2;

    if (current_language != LANGUAGE_JAPANESE) {
        if ((s32) current_language < 0) {
            return;
        }
        return;
    }
    if ((s8) *(u8 *)((s8 *)this + 0x64) == 0) {
        temp_r4 = *(void **)((s8 *)this + 0x6C);
        *(s32 *)((s8 *)temp_r4 + 0xB4) = (s32) (*(s32 *)((s8 *)temp_r4 + 0xB4) | 1);
        temp_r3 = *(void **)((s8 *)this + 0x6C);
        *(s32 *)((s8 *)temp_r3 + 0xB4) = (s32) (*(s32 *)((s8 *)temp_r3 + 0xB4) & 0xFFFFFFBF);
        return;
    }
    temp_r4_2 = *(void **)((s8 *)this + 0x6C);
    *(s32 *)((s8 *)temp_r4_2 + 0xB4) = (s32) (*(s32 *)((s8 *)temp_r4_2 + 0xB4) & 0xFFFFFFFE);
    temp_r3_2 = *(void **)((s8 *)this + 0x6C);
    *(s32 *)((s8 *)temp_r3_2 + 0xB4) = (s32) (*(s32 *)((s8 *)temp_r3_2 + 0xB4) | 0x40);
}
#pragma pop

#pragma push
#pragma fp_contract on
void TWindowKeyBoardSoft::handle_page_cycle_input(s32 arg1) {
    s32 spC;
    s32 sp8;
    u8 *temp_r30;
    temp_r30 = (u8 *)&controller_input_state.value + (arg1 * 0x50) + 0x20;
    if (((s32 (*)(int, int))TWindowShortListCtrl__check_controller_button)((int)temp_r30, 0x30000) != 0) {
        play_sound_effect(0x54100, 0, 0, 0);
        calc_cursor_step__19TWindowKeyBoardSoftFiPvPv((s32)this, &spC, &sp8);
        if (((s32 (*)(int, int))TWindowShortListCtrl__check_controller_button)((int)temp_r30, 0x10000) != 0) {
            *(f32 *)((s8 *)((u8 *)this) + 0x68) = (f32) TWindowKeyBoardSoft__data_805DD088;
            *(u8 *)((s8 *)((u8 *)this) + 0x64) = (u8) (*(u8 *)((s8 *)((u8 *)this) + 0x64) + 1);
        }
        if (((s32 (*)(int, int))TWindowShortListCtrl__check_controller_button)((int)temp_r30, 0x20000) != 0) {
            *(f32 *)((s8 *)((u8 *)this) + 0x68) = (f32) lbl_805DD08C;
            *(u8 *)((s8 *)((u8 *)this) + 0x64) = (u8) (*(u8 *)((s8 *)((u8 *)this) + 0x64) - 1);
        }
        if ((s8) *(u8 *)((s8 *)((u8 *)this) + 0x64) < spC) {
            *(u8 *)((s8 *)((u8 *)this) + 0x64) = (u8) sp8;
        }
        if ((s8) *(u8 *)((s8 *)((u8 *)this) + 0x64) > sp8) {
            *(u8 *)((s8 *)((u8 *)this) + 0x64) = (u8) spC;
        }
        this->update_focus_flags();
    }
}
#pragma pop

void TKeyBoardControl::close() {
    void *temp_r3;
    *(s32 *)((s8 *)this + 0x60) = (s32) (*(s32 *)((s8 *)this + 0x60) | 0x80);
    temp_r3 = *(void **)((s8 *)this + 0x6C);
    if (temp_r3 != NULL) {
        TKeyBoardControl__sub_8025CBC0(temp_r3);
        release();
    }
}

void TKeyBoardControl::release_input() {
    void *temp_r3;
    *(s32 *)((s8 *)this + 0x60) = (s32) (*(s32 *)((s8 *)this + 0x60) | 0x40);
    temp_r3 = *(void **)((s8 *)this + 0x6C);
    if (temp_r3 != NULL) {
        TKeyBoardControl__sub_8025CBCC((u8 *)temp_r3);
        release();
    }
}

void TKeyBoardControl__sub_802613A4(TKeyBoardControl *key_board_control) {
    *(s32 *)((s8 *)key_board_control + 0x60) = (s32) (*(s32 *)((s8 *)key_board_control + 0x60) | 0x20);
    if (*(void **)((s8 *)key_board_control + 0x6C) != NULL) {
        TKeyBoardControl__sub_8025CC04((u8 *)(*(void **)((s8 *)key_board_control + 0x6C)));
        key_board_control->release();
    }
}

void TKeyBoardControl::release() {
    if ((u32) *(u32 *)((s8 *)this + 0x6C) != 0U) {
        *(s32 *)((s8 *)this + 0x60) = (s32) (*(s32 *)((s8 *)this + 0x60) | 1);
        TKeyBoardControl__sub_8025CC3C((void *)(*(u32 *)((s8 *)this + 0x6C)));
        TWindowKeyBoardSoft__sub_80261134(this);
    }
}

void TWindowKeyBoardSoft::close() { if (*(unsigned int*)((char*)this + 0x6c) != 0) { update_keyboard_close_mode(*(void**)((char*)this + 0x6c)); update_focus_flags(); } }

s32 TWindowKeyBoardSoft::hit_test_relative(u8 *arg1, u8 *arg2) {
    u8 *arg0 = (u8 *)this;
    f32 temp_f3;
    f32 temp_f5;
    temp_f3 = *(f32 *)((s8 *)arg2 + 4);
    temp_f5 = *(f32 *)((s8 *)arg2 + 0);
    return TWindowKeyBoardSoft__sub_802614DC(arg0, arg1, temp_f5 - *(f32 *)((s8 *)arg1 + 0), temp_f3 - *(f32 *)((s8 *)arg1 + 4), *(f32 *)((s8 *)arg2 + 8) - temp_f5, *(f32 *)((s8 *)arg2 + 0xC) - temp_f3) >= TWindowKeyBoardSoft__data_805DD078;
}

f32 TWindowKeyBoardSoft__sub_802614DC(u8 *window_sub_com_card, u8 *arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    f32 t;
    f32 v;

    t = ((TWindowSubComCard *)window_sub_com_card)->get_normalized_progress();
    if (t >= 1.0f) {
        return 1.0f;
    }
    v = (t * (*(f32 *)((s8 *)arg1 + 8) + *(f32 *)((s8 *)arg1 + 0xC))) - (farg0 + farg1);
    if (v <= 0.0f) {
        return 0.0f;
    }
    v = v / (farg2 + farg3);
    if (v >= 1.0f) {
        v = 1.0f;
    }
    return v;
}

#pragma push
#pragma fp_contract on
void TWindowKeyBoardSoft::spawn_key_effect(s32 arg1, s32 arg2) {
    s32 type;
    Vec2_802615B8 pos;
    s32 kind;

    ((void (*)(void *, s32, s32 *, s32))TWindowKeyBoardSoft__sub_80260760)(this, ((s32 (*)(void *, s32, s32))calc_key_index__19TWindowKeyBoardSoftFiii)(this, arg1, arg2), &type, 0);
    pos.x = *(f32 *)(((u8 *)this) + 0x40) + ((f32 (*)(void *, s32, s32))calc_key_x__19TWindowKeyBoardSoftFiii)(this, arg1, arg2);
    pos.y = TWindowKeyBoardSoft__data_805DD094 + (TWindowKeyBoardSoft__data_805DD088 + (TWindowKeyBoardSoft__data_805DD07C * (f32)arg2 + *(f32 *)(((u8 *)this) + 0x44)));
    switch (type) {
    case 1:
        kind = 3;
        break;
    case 2:
        kind = 4;
        break;
    case 4:
        kind = 5;
        break;
    case 10:
        kind = 6;
        break;
    }
    TWindowEffectLight::create(&pos, (void *)kind, (void *)local_client_id);
}
#pragma pop

// Glyphs and icon rectangles use external tables owned by neighboring data
// ranges. Their precise source-level types and the rendering API are provisional.
s32 TWindowKeyBoardSoft__sub_802616BC(void *self, int context) {
    TWindowKeyBoardSoft *kb = (TWindowKeyBoardSoft *)self;
    TWindowKeyBoardSoft *ctx = (TWindowKeyBoardSoft *)context;
    SoftKeyLayout_80260904 *layout = (SoftKeyLayout_80260904 *)TWindowKeyBoardSoft__language_text_resources;
    f32 scale = TWindowKeyBoardSoft__data_805DD098 / (lbl_805DD09C + ctx->depth);
    s32 selected = kb->sub_802605DC();
    const u16 *keys = layout->pages[*(s8 *)((u8 *)self + 0x64)];
    Quad_80262038 q;
    reset_gauge__20TWindowSubStatusDispFPv(0);
    for (s32 row = 0; row < 7; ++row) {
        f32 y = TWindowKeyBoardSoft__data_805DD07C * (f32)row;
        for (s32 col = 0; col < 16; ++col) {
            u16 code = *keys++;
            if (code < 0x20) continue;
            if (kb->get_flag_bit5() && (code < 'A' || code > 'Z')) code = 0x16;
            if (kb->get_flag_bit6() && !is_alnum__19TWindowKeyBoardSoftFUs(code)) code = 0x16;
            if (kb->is_cursor_locked() && (code < '0' || code > '9')) code = 0x16;
            if (code == 0x16) continue;
            u16 glyph = map_char_to_font_code(code);
            s32 index = calc_key_index__19TWindowKeyBoardSoftFiii((s32)self, col, row);
            s32 color = index == selected ? (s32)0xFF000000 : (s32)0xFF999999;
            q.x = TWindowKeyBoardSoft__data_805DD078 + (TWindowKeyBoardSoft__data_805DD078 + (TWindowKeyBoardSoft__data_805DD07C * (f32)col + ctx->x));
            q.y = TWindowKeyBoardSoft__data_805DD078 + (TWindowKeyBoardSoft__data_805DD094 + (ctx->y + y));
            u8 advance = calc_gauge_scale__20TWindowSubStatusDispFPvPvi(glyph, &q, color);
            q.x += TWindowKeyBoardSoft__data_805DD080 * (f32)(18 - advance);
            set_glyph_quad_extents(advance, &q);
            if (kb->hit_test_relative((u8 *)ctx, (u8 *)&q)) {
                apply_context_transform_to_rect(ctx, &q);
                draw_textured_quad_at_depth((f32 *)&q, scale);
            }
        }
    }
    end_render_forward__20TWindowSubStatusDispFPv();
    begin_screen_draw(1);
    render_forward__20TWindowSubStatusDispFPv();
    set_draw_texture_and_color(0, 0xFF999999);
    s32 index = calc_key_index__19TWindowKeyBoardSoftFiii((s32)self, 2, 0);
    for (s32 i = 0; i < 12; ++i, ++index) {
        q.x = TWindowKeyBoardSoft__data_805DD078 + (TWindowKeyBoardSoft__data_805DD078 + (TWindowKeyBoardSoft__data_805DD07C * (f32)(i + 2) + ctx->x));
        q.x2 = lbl_805DD0A0 + q.x;
        q.y = TWindowKeyBoardSoft__data_805DD078 + (TWindowKeyBoardSoft__data_805DD094 + ctx->y);
        q.y2 = lbl_805DD0A0 + q.y;
        q.u = (lbl_805DD0A0 * (f32)i) * lbl_805DD0A4;
        q.v = TWindowKeyBoardSoft__data_805DD090;
        q.u2 = (lbl_805DD0A0 * (f32)(i + 1)) * lbl_805DD0A4;
        q.v2 = lbl_805DD0A8;
        if (kb->hit_test_relative((u8 *)ctx, (u8 *)&q)) {
            set_constant_material_color(index == selected ? 0xFF000000 : 0xFF999999);
            apply_context_transform_to_rect(ctx, &q);
            draw_textured_quad_at_depth((f32 *)&q, scale);
        }
    }
    begin_render__20TWindowSubStatusDispFl();
    set_draw_texture_and_color(3, 0xFF999999);
    f32 x = TWindowKeyBoardSoft__sub_802606E0(kb);
    s32 min_page, max_page;
    calc_cursor_step__19TWindowKeyBoardSoftFiPvPv((s32)self, &min_page, &max_page);
    for (s32 page = 0; page < layout->page_count; ++page) {
        u32 color;
        if (page == *(s8 *)((u8 *)self + 0x64)) color = 0xFF000000;
        else if (page < min_page || page > max_page) color = 0xFF646464;
        else color = 0xFF999999;
        q.x = TWindowKeyBoardSoft__data_805DD078 + (ctx->x + x);
        q.y = TWindowKeyBoardSoft__data_805DD078 + (TWindowKeyBoardSoft__data_805DD098 + ctx->y);
        q.x2 = (q.x + (f32)(s32)layout->page_width) - lbl_805DD0AC;
        q.y2 = lbl_805DD0A0 + q.y;
        q.u = TWindowKeyBoardSoft__data_805DD090;
        q.v = (lbl_805DD0A0 * (f32)page) * lbl_805DD0B0;
        q.u2 = ((f32)(s32)layout->page_width - lbl_805DD0AC) * lbl_805DD0B0;
        q.v2 = (lbl_805DD0A0 * (f32)(page + 1)) * lbl_805DD0B0;
        if (kb->hit_test_relative((u8 *)ctx, (u8 *)&q)) {
            apply_context_transform_to_rect(ctx, &q);
            set_constant_material_color(color);
            draw_textured_quad_at_depth((f32 *)&q, scale);
        }
        x += (f32)(s32)layout->page_width;
    }
    for (s32 i = 0; i < 10; ++i) {
        s32 col = (s32)lbl_8044F164[i][0], row = (s32)lbl_8044F164[i][1];
        index = calc_key_index__19TWindowKeyBoardSoftFiii((s32)self, col, row);
        u32 color = index == selected ? 0xFF000000 : 0xFF999999;
        f32 center = ctx->x + calc_key_x__19TWindowKeyBoardSoftFiii((s32)self, col, row);
        f32 width = lbl_8044F1B4[i][0], height = lbl_8044F1B4[i][1];
        f32 u = lbl_8044F204[i][0], v = lbl_8044F204[i][1];
        q.x = center - TWindowKeyBoardSoft__data_805DD080 * width;
        q.y = TWindowKeyBoardSoft__data_805DD078 + (TWindowKeyBoardSoft__data_805DD094 + (TWindowKeyBoardSoft__data_805DD07C * lbl_8044F164[i][1] + ctx->y));
        q.x2 = q.x + width;
        q.y2 = q.y + height;
        q.u = u * lbl_805DD0B0;
        q.v = v * lbl_805DD0B0;
        q.u2 = (u + width) * lbl_805DD0B0;
        q.v2 = (v + height) * lbl_805DD0B0;
        if (kb->hit_test_relative((u8 *)ctx, (u8 *)&q)) {
            set_constant_material_color(color);
            apply_context_transform_to_rect(ctx, &q);
            draw_textured_quad_at_depth((f32 *)&q, scale);
        }
    }
    return get_player__20TWindowSubStatusDispFv();
}

void TWindowKeyBoardSoft__sub_80261DD8(TWindowKeyBoardSoft *self, TWindowKeyBoardSoft *ctx) {
    Vec2_802615B8 v[5];
    u32 col[5];
    Lines_80261DD8 d;
    f32 depth;
    u8 *res;

    depth = 0.0598f + ctx->depth;
    res = TWindowKeyBoardSoft__language_text_resources;
    d.verts = v;
    d.colors = col;
    d.f8 = 0;
    d.colors[0] = (ctx->color & 0xFF000000) | 0xA6B3;
    d.colors[1] = d.colors[0];
    d.colors[2] = d.colors[0];
    d.colors[3] = d.colors[0];
    d.colors[4] = d.colors[0];
    d.count = 5;
    v[0].x = (1.0f + ctx->x) - 1.0f;
    v[0].y = (26.0f + ctx->y) - 1.0f;
    v[1].x = 3.0f + (304.0f + v[0].x);
    v[1].y = v[0].y;
    v[2].x = v[1].x;
    v[2].y = 3.0f + (133.0f + v[0].y);
    v[3].x = v[0].x;
    v[3].y = v[2].y;
    ctx->scale_point_about_pivot(&v[0].x);
    ctx->scale_point_about_pivot(&v[1].x);
    ctx->scale_point_about_pivot(&v[2].x);
    ctx->scale_point_about_pivot(&v[3].x);
    v[4].x = v[0].x;
    v[4].y = v[0].y;
    draw_color_lines(&d, 5, 0x14, depth);
    v[0].x = (ctx->x + TWindowKeyBoardSoft__sub_802606E0(self)) - 1.0f;
    v[0].y = (-1.0f + ctx->y) - 1.0f;
    v[1].x = 3.0f + (v[0].x + (f32)(res[0] * res[1]));
    v[1].y = v[0].y;
    v[2].x = 3.0f + (v[0].x + (f32)(res[0] * res[1]));
    v[2].y = 2.0f + (20.0f + v[0].y);
    v[3].x = v[0].x;
    v[3].y = v[2].y;
    ctx->scale_point_about_pivot(&v[0].x);
    ctx->scale_point_about_pivot(&v[1].x);
    ctx->scale_point_about_pivot(&v[2].x);
    ctx->scale_point_about_pivot(&v[3].x);
    v[4].x = v[0].x;
    v[4].y = v[0].y;
    draw_color_lines(&d, 5, 0x14, depth);
}

void TWindowKeyBoardSoft::draw_key_frame(void *self, f32 *rect, u32 color, s32 idx, f32 x0, f32 y, f32 w, f32 scale) {
    Quad_80262038 q;
    f32 v;
    f32 y2;
    f32 x2;
    f32 x3;
    f32 x4;
    UV_80262038 *uv;

    v = ((f32 (*)(void *, f32, f32, f32, f32))TWindowKeyBoardSoft__sub_802614DC)(self, x0, y, w, 20.0f);
    if (v <= TWindowKeyBoardSoft__data_805DD090) {
        return;
    }
    if (v < TWindowKeyBoardSoft__data_805DD078) {
        color = ((u32)(lbl_805DD0C8 * v) << 24) | (color & 0x00FFFFFF);
    }
    x0 += rect[0];
    y += rect[1];
    uv = &keyboard_key_frame_uv_table[idx];
    set_constant_material_color(color);
    x2 = 10.0f + x0;
    y2 = 20.0f + y;
    q.x = x0;
    q.y = y;
    q.x2 = x2;
    q.y2 = y2;
    q.u = uv->u / 256.0f;
    q.v = uv->v / 256.0f;
    q.u2 = (10.0f + uv->u) / 256.0f;
    q.v2 = (20.0f + uv->v) / 256.0f;
    apply_context_transform_to_rect(rect, &q);
    draw_textured_quad_at_depth((f32 *)&q, scale);
    x3 = x0 + w;
    x4 = x3 - 10.0f;
    q.x = x4;
    q.y = y;
    q.x2 = x3;
    q.y2 = y2;
    q.u = (10.0f + uv->u) / 256.0f;
    q.v = uv->v / 256.0f;
    q.u2 = (20.0f + uv->u) / 256.0f;
    q.v2 = (20.0f + uv->v) / 256.0f;
    apply_context_transform_to_rect(rect, &q);
    draw_textured_quad_at_depth((f32 *)&q, scale);
    if (w <= 20.0f) {
        return;
    }
    q.x = x2;
    q.y = y;
    q.x2 = x4;
    q.y2 = y2;
    q.u = (10.0f + uv->u) / 256.0f;
    q.v = uv->v / 256.0f;
    q.u2 = (10.0f + uv->u) / 256.0f;
    q.v2 = (20.0f + uv->v) / 256.0f;
    apply_context_transform_to_rect(rect, &q);
    draw_textured_quad_at_depth((f32 *)&q, scale);
}

// Draw the key grid followed by the language-page selector. The input object
// layout at 0x64/0x68 remains a bounded view, pending its owning type.
s32 TWindowKeyBoardSoft__sub_8026227C(TWindowKeyBoardSoft *self, TWindowKeyBoardSoft *ctx) {
    u8 *resources = TWindowKeyBoardSoft__language_text_resources;
    f32 scale = TWindowKeyBoardSoft__data_805DD098 / ctx->depth;
    s32 selected = self->sub_802605DC();
    s32 count;
    u32 color;
    s32 min_page, max_page;
    s32 frame;
    f32 x;
    begin_screen_draw(1);
    set_current_texture_list(lbl_805D63F0);
    set_draw_texture_and_color(0, -1);
    for (s32 row = 0; row < 7; row++) {
        f32 y = TWindowKeyBoardSoft__data_805DD07C * (f32)row + TWindowKeyBoardSoft__data_805DD094;
        for (s32 col = 0; col < 16; col += count) {
            s32 index = calc_key_index__19TWindowKeyBoardSoftFiii((s32)self, col, row);
            TWindowKeyBoardSoft__sub_80260760((void *)self, index, &count, &color);
            f32 width = TWindowKeyBoardSoft::calc_key_coord((s32)self, count);
            if (index == selected) { color = 0xFFFFFFFF; frame = 1; }
            else { frame = 0; }
            TWindowKeyBoardSoft::draw_key_frame((void *)self, (f32 *)ctx, color, frame,
                TWindowKeyBoardSoft__data_805DD07C * (f32)col + TWindowKeyBoardSoft__data_805DD078,
                y, width, scale);
        }
    }
    x = TWindowKeyBoardSoft__sub_802606E0(self);
    calc_cursor_step__19TWindowKeyBoardSoftFiPvPv((s32)self, &min_page, &max_page);
    for (s32 page = 0; page < resources[0]; page++) {
        if (page == *(s8 *)((u8 *)self + 0x64)) { color = 0xFFFFFFFF; frame = 2; }
        else {
            if (page < min_page) color = 0xFF4D4D4D;
            else if (page > max_page) color = 0xFF4D4D4D;
            else color = 0xFF0C5B38;
            frame = 0;
        }
        TWindowKeyBoardSoft::draw_key_frame((void *)self, (f32 *)ctx, color, frame, x,
            TWindowKeyBoardSoft__data_805DD098, (f32)(resources[1] + 1), scale);
        x += (f32)(s32)resources[1];
    }
    set_constant_material_color(ctx->color);
    x = TWindowKeyBoardSoft__sub_802606E0(self);
    fn_8026C664((u8 *)ctx, (ctx->x + x) - lbl_805DD0CC,
        lbl_805DD0B8 + (TWindowKeyBoardSoft__data_805DD098 + ctx->y),
        scale, *(f32 *)((u8 *)self + 0x68));
    fn_8026C708((u8 *)ctx,
        lbl_805DD0D0 + (ctx->x + (x + (TWindowKeyBoardSoft__data_805DD078 + (f32)(resources[1] * resources[0])))),
        lbl_805DD0B8 + (TWindowKeyBoardSoft__data_805DD098 + ctx->y),
        scale, *(f32 *)((u8 *)self + 0x68));
    return get_player__20TWindowSubStatusDispFv();
}

void TWindowKeyBoardSoft::render() {
    s32 temp_r3;
    temp_r3 = draw_default_entry__9TWindowDDFl();
    TWindowKeyBoardSoft__sub_8026227C(this, (TWindowKeyBoardSoft *)temp_r3);
    TWindowKeyBoardSoft__sub_80261DD8(this, (TWindowKeyBoardSoft *)temp_r3);
    TWindowKeyBoardSoft__sub_802616BC(this, (int)temp_r3);
}

}
