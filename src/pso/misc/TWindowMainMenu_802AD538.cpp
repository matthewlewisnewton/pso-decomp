#include "pso/system/SoundEffect.h"
#include "pso/system/CurrentTextureList.h"
#include "types.h"
#include "pso/misc/TWindowCtrl_8024A054.h"
struct TWindowSubComCard;
#include "pso/misc/TWindowMenuMainMenu.h"
#include "pso/misc/TWindowMainMenu.h"
#include "pso/misc/TLanguage.h"
#include "pso/misc/TWindowKeyBoardSoft.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/unk/text_8026CB5C.h"

struct RecoveredGlobal_802AE59C_lbl_8050E208 {
    s32 value;
    u8 remaining[0x1AC];
};

struct Rect_802AE2B0 { f32 x, y, w, h; u8 pad[0x34 - 0x10]; u32 color; };

typedef char RecoveredGlobal_802AE59C_lbl_8050E208_size[sizeof(RecoveredGlobal_802AE59C_lbl_8050E208) == 0x1B0 ? 1 : -1];

struct UV_802AD538 { f32 u, v; };

struct Rect_802AD538 {
    f32 x0, y0, x1, y1;
    f32 u0, v0, u1, v1;
};

extern "C" {
s32 is_split_screen();
int copy_vec2__28TWindowSubSymbolChatPartsSetFPv(void *, void *);
void begin_render__20TWindowSubStatusDispFl(void);
s32 test_flag_4c__23TAdSinglePlyChrSelectGCFv(void *, int);
s32 TWindowShortListCtrl__check_controller_button(int, int);
s32 apply_choice__20TWindowChoiceSettingFllll(void *, int, int, int);
f32 TWindowSubComCard__sub_80244784(TWindowSubComCard *);
s32 is_window_reveal_complete__13TUnk_804CE018Fv();
s32 sub_80246948__13TUnk_804CE018Fv();
s32 try_open__19TWindowKeyBoardSoftFii(s32 arg0, s32 arg1);
void begin_screen_draw(s32 arg0);
void draw_textured_quad_at_depth(f32 *q, f32 depth);
void set_draw_texture_and_color(s32 idx, s32 arg1);

extern UV_802AD538 main_menu_label_uv_table[];
extern RecoveredGlobal_802AE59C_lbl_8050E208 controller_input_state;
}

void TMainMenuEntry::draw_item_labels(TWindowDrawContext *w) {
    Rect_802AD538 r;
    f32 scale;
    UV_802AD538 *uv;
    u32 color;
    u32 rgb;
    f32 a;

    if (is_item_active() != 0 && fade > 0) {
        scale = -1.0f / (0.299f + w->depth);
        uv = &main_menu_label_uv_table[icon];
        begin_render__20TWindowSubStatusDispFl();
        switch (kind) {
        case 0:
            rgb = 0xFFFFFF;
            if (flags & 2) {
                rgb = 0x686868;
            }
            if (fade >= 4) {
                a = 1.0f;
            } else {
                a = (f32)fade / 4.0f;
            }
            color = rgb | ((s32)(255.0f * a) << 24);
            break;
        case 1:
            TLanguage::set_entry_index(2, 0x4C);
            color = 0xFFFF6121;
            break;
        case 2:
            TLanguage::set_entry_index(2, 0x4C);
            color = 0xFF51EAFF;
            break;
        }
        begin_screen_draw(1);
        set_draw_texture_and_color(2, color);
        r.x0 = w->clip_left + cur_x;
        r.y0 = w->clip_top + cur_y;
        r.x1 = 98.0f + r.x0;
        r.y1 = 16.0f + r.y0;
        r.u0 = uv->u / 256.0f;
        r.v0 = uv->v / 256.0f;
        r.u1 = (98.0f + uv->u) / 256.0f;
        r.v1 = (16.0f + uv->v) / 256.0f;
        if (try_open__19TWindowKeyBoardSoftFii((s32)w, (s32)&r) != 0) {
            draw_textured_quad_at_depth((f32 *)&r, scale);
        }
        TWindowSubStatusDisp::get_player();
        TLanguage::set_entry_index(2, 0x4B);
    }
}

int TMainMenuEntry::is_item_active() { return flags & 1; }

void TMainMenuEntry::sub_802AD74C() { flags |= 2; }

void TMainMenuEntry::set_symbol_chat_parts(TMainMenuRow *row) {
    copy_vec2__28TWindowSubSymbolChatPartsSetFPv(this, row);
    tween = 8;
}

void TMainMenuEntry::init_row_entry(TMainMenuRow *row, s8 icon, s8 fade) {
    copy_vec2__28TWindowSubSymbolChatPartsSetFPv(this, row);
    copy_vec2__28TWindowSubSymbolChatPartsSetFPv(&cur_x, row);
    this->fade = fade;
    this->icon = icon;
    kind = 0;
    flags |= 1;
}

void TMainMenuEntry::update_item_tween() {
    if (is_item_active() != 0) {
        if (tween <= 0) {
            cur_x = x;
            cur_y = y;
        } else {
            cur_x += (x - cur_x) / tween;
            cur_y += (y - cur_y) / tween;
            tween--;
        }
        if (fade < 4) {
            fade++;
        }
    }
}

void TMainMenuEntry::init_color() {
    x = 0.0f;
    y = 0.0f;
    cur_x = 0.0f;
    cur_y = 0.0f;
    fade = 0;
    icon = -1;
    kind = 0;
    flags = 0;
    tween = 0;
}

void TWindowMenuMainMenu::pop_level() {
    s32 i;
    m_62--;
    m_60 |= 8;
    for (i = 0; i < 8; i++) {
        if (slots[i] != 0) {
            slots[i]->init_color();
            slots[i] = 0;
        }
    }
}

void TWindowMenuMainMenu::park_selection() {
    TMainMenuEntry buf;
    TMainMenuRow row;
    s32 i;
    TMainMenuEntry *slot;
    buf.copy_color_entry(slots[m_61]);
    for (i = 0; i < 8; i++) {
        if (slots[i] != NULL) {
            slots[i]->init_color();
            slots[i] = NULL;
        }
    }
    get_row_position(&row, m_62);
    slot = find_free_slot();
    slot->copy_color_entry(&buf);
    slot->set_symbol_chat_parts(&row);
    slot->kind = 2;
    m_60 |= 4;
    m_62++;
}

void TMainMenuEntry::copy_color_entry(TMainMenuEntry *src) {
    struct Hd { u32 w[4]; };
    struct Col { Hd h; };
    ((Col *)this)->h = ((Col *)src)->h;
    fade = src->fade;
    icon = src->icon;
    kind = src->kind;
    flags = src->flags;
    tween = src->tween;
    b5 = src->b5;
    b6 = src->b6;
    b7 = src->b7;
}

int TWindowMenuMainMenu::get_selected_item_type() {
    TMainMenuEntry *p = slots[m_61];
    if (p == 0) return 0x1f;
    return p->icon;
}

void TWindowMenuMainMenu::sub_802ADADC(int slot) {
    m_61 = slot;
    slots[m_61]->kind = 1;
}

int TWindowMenuMainMenu::sub_802ADB00() {
  return m_61;
}

void TWindowMenuMainMenu::clear_menu_flags() { m_60 &= 0xfc; }

int TWindowMenuMainMenu::is_flag_set() { return (this->m_60 >> 1) & 0x1; }

int TWindowMenuMainMenu::get_menu_flag() { return this->m_60 & 0x1; }

TMainMenuEntry *TWindowMenuMainMenu::find_active_item_by_id(int arg1) {
    s32 var_r31;
    TMainMenuEntry *entry;
    s32 var_r29;
    var_r29 = arg1;
    if (var_r29 == 0x1B) {
        var_r29 = 0x1A;
    }
    entry = entries;
    var_r31 = 0;
loop_3:
    if ((entry->is_item_active() != 0) && ((s8)entry->icon == var_r29)) {
        return entry;
    }
    var_r31 += 1;
    entry += 1;
    if (var_r31 >= 8) {
        return NULL;
    }
    goto loop_3;
}

TMainMenuEntry *TWindowMenuMainMenu::find_free_slot() {
    s32 counter;
    TMainMenuEntry *entry;

    entry = entries;
    counter = 0;
loop_1:
    if (entry->is_item_active() == 0) {
        return entry;
    }
    counter += 1;
    entry += 1;
    if (counter >= 8) {
        return 0;
    }
    goto loop_1;
}

int TWindowMenuMainMenu::find_free_item_slot() {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (slots[i] == 0) return i;
    }
    return 8;
}

s32 TWindowMenuMainMenu::count_active_items() {
    s32 counter;
    TMainMenuEntry *entry;

    entry = entries;
    counter = 0;
loop_1:
    if (entry->is_item_active() == 0) {
        return counter;
    }
    counter += 1;
    entry += 1;
    if (counter >= 8) {
        return 8;
    }
    goto loop_1;
}

void TWindowMenuMainMenu::get_row_position(TMainMenuRow *row, int index) {
    row->x = 0.0f;
    row->y = 16.0f * (f32)index;
}

s32 TWindowMenuMainMenu::is_not_split_screen() {
    return (u32)__cntlzw(is_split_screen()) >> 5;
}

TMainMenuEntry *TWindowMenuMainMenu::update_if_active(s32 id) {
    TMainMenuEntry *entry;

    entry = append_child_rows(id);
    if (entry != 0) {
        entry->sub_802AD74C();
    }
    return entry;
}

TMainMenuEntry *TWindowMenuMainMenu::append_child_rows(int id) {
    TMainMenuRow row;
    s32 n;
    TMainMenuEntry *slot;
    n = find_free_item_slot();
    if (n >= 8) {
        return 0;
    }
    get_row_position(&row, n + m_62);
    slot = find_active_item_by_id(id);
    if (slot == 0) {
        slot = find_free_slot();
        if (slot == 0) {
            return 0;
        }
        slot->init_row_entry(&row, id, -(n * 2));
    } else {
        slot->set_symbol_chat_parts(&row);
    }
    slots[n] = slot;
    m_60 &= ~4;
    return slot;
}

void TWindowMenuMainMenu::set_target_y(f32 farg0) {
    if (is_not_split_screen() != 0) {
        farg0 += 51.0f;
    } else {
        farg0 += 42.0f;
    }
    farg0 += 39.0f;
    if (unk_3c != farg0) {
        unk_3c = farg0;
        unk_50 = 8;
    }
}

void TWindowMenuMainMenu::update_scaled_position() {
    set_target_y(16.0f * (f32)count_active_items());
}

void TWindowMenuMainMenu::draw_entries_reversed(TWindowDrawContext *context) {
    s32 var_r31;
    TMainMenuEntry *entry;
    entry = &entries[7];
    var_r31 = 0;
    do {
        entry->draw_item_labels(context);
        var_r31 += 1;
        entry -= 1;
    } while (var_r31 < 8);
}

extern "C" {
extern GinjaTextureList *lbl_805D63F0;
void apply_context_transform_to_rect(void *, void *);
}

void TWindowMenuMainMenu::draw_frame(TWindowDrawContext *context) {
    Rect_802AD538 r;
    f32 depth = -1.0f / (0.299f + m_54);
    f32 offset = 0.0f;
    f32 remaining = context->inner_h;
    f32 height;
    begin_screen_draw(1);
    set_current_texture_list(lbl_805D63F0);
    set_draw_texture_and_color(11, context->color);
    if (is_not_split_screen()) {
        r.x0 = context->x;
        r.y0 = context->y + offset;
        r.x1 = 18.0f + r.x0;
        r.y1 = 28.0f + r.y0;
        r.u0 = 0.8984375f; r.v0 = 0.0f;
        r.u1 = 0.96875f; r.v1 = 0.109375f;
        apply_context_transform_to_rect(context, &r);
        draw_textured_quad_at_depth(&r.x0, depth);
        offset += 28.0f;
        remaining -= 28.0f;
        r.x0 = context->x; r.y0 = context->y + offset;
        r.x1 = r.x0 + context->w; r.y1 = 23.0f + r.y0;
        r.u0 = 0.0f; r.v0 = 0.3125f;
        r.u1 = 0.453125f; r.v1 = 0.40234375f;
        apply_context_transform_to_rect(context, &r);
        draw_textured_quad_at_depth(&r.x0, depth);
        offset += 23.0f;
        remaining -= 23.0f;
    } else {
        r.x0 = context->x;
        r.y0 = context->y + offset;
        r.x1 = context->x + context->w;
        r.y1 = 3.0f + (39.0f + r.y0);
        r.u0 = 0.453125f; r.v0 = 0.6796875f;
        r.u1 = 0.0f; r.v1 = 0.515625f;
        apply_context_transform_to_rect(context, &r);
        draw_textured_quad_at_depth(&r.x0, depth);
        offset += 42.0f;
        remaining -= 42.0f;
    }
    remaining -= 39.0f;
    while (remaining >= 4.0f) {
        if (remaining < 16.0f) {
            height = 4.0f;
        } else {
            height = 16.0f;
        }
        r.x0 = context->x; r.y0 = context->y + offset;
        r.x1 = r.x0 + context->w; r.y1 = r.y0 + height;
        r.u0 = 0.0f; r.v0 = 0.40234375f;
        r.u1 = 0.453125f; r.v1 = (103.0f + height) / 256.0f;
        apply_context_transform_to_rect(context, &r);
        draw_textured_quad_at_depth(&r.x0, depth);
        offset += height;
        remaining -= height;
    }
    r.x0 = context->x; r.y0 = context->y + offset;
    r.x1 = r.x0 + context->w; r.y1 = 39.0f + r.y0;
    r.u0 = 0.0f; r.v0 = 0.52734375f;
    r.u1 = 0.453125f; r.v1 = 0.6796875f;
    apply_context_transform_to_rect(context, &r);
    draw_textured_quad_at_depth(&r.x0, depth);
    TWindowSubStatusDisp::get_player();
}

TWindowDrawContext *TWindowMenuMainMenu::setup_content_frame() {
    f32 v;
    TWindowKeyBoardSoft *window;
    window = TWindowKeyBoardSoft::open_singleton(m_40, m_48, fn_8026CB68(), m_54, m_2c);
    if (is_not_split_screen() != 0) {
        v = 51.0f;
    } else {
        v = 39.0f;
    }
    window->set_bounds(10.0f + window->x, window->y + v, (window->x + window->w) - 10.0f, (window->y + window->h) - 39.0f);
    window->color = ((s32)(255.0f * TWindowSubComCard__sub_80244784((TWindowSubComCard *)this)) << 24) | 0xFF0000 | 0xFFFF;
    return window;
}


void TWindowMenuMainMenu::update_slide_position() {
    if (sub_80246948__13TUnk_804CE018Fv() != 0) {
        set_target_y(0.0f);
        unk_50 = (u32)(4.5f - (f32)unk_22);
        return;
    }
    update_scaled_position();
}

void TWindowMenuMainMenu::handle_cancel() {
    play_sound_effect(0x52F16, 0, 0, 0);
    this->m_60 = (u8) (this->m_60 | 2);
}

void TWindowMenuMainMenu::handle_confirm() {
    TMainMenuEntry *item = slots[(s8)m_61];
    if (item != NULL) {
        if (item->flags & 2) {
            play_sound_effect(0x53F06, 0, 0, 0);
            return;
        }
        play_sound_effect(0x52D01, 0, 0, 0);
        m_60 |= 1;
    }
}

void TWindowMenuMainMenu::play_cursor_sound(int delta) {
    int n;
    play_sound_effect(0x54100, 0, 0, 0);
    slots[m_61]->kind = 0;
    n = find_free_item_slot();
    m_61 += delta;
    if (m_61 < 0) {
        m_61 = n - 1;
    }
    if (m_61 > n - 1) {
        m_61 = 0;
    }
    slots[m_61]->kind = 1;
}

void TWindowMenuMainMenu::handle_navigation_input() {
    u8 *window_choice_setting;
    if ((is_window_reveal_complete__13TUnk_804CE018Fv() != 0) && (this->get_menu_flag() == 0) && (this->is_flag_set() == 0) && !(this->m_60 & 4)) {
        window_choice_setting = (u8 *)&controller_input_state.value + (is_player_input_active((*(s16 *)&this->m_20)) * 0x50) + 0x20;
        if ((apply_choice__20TWindowChoiceSettingFllll(window_choice_setting, 0x10, 6, 1) != 0) || (apply_choice__20TWindowChoiceSettingFllll((void *) ((u8 *)&controller_input_state.value + 0x160), 0x10, 6, 1) != 0)) {
            play_cursor_sound(-1);
        }
        if ((apply_choice__20TWindowChoiceSettingFllll(window_choice_setting, 0x20, 6, 1) != 0) || (apply_choice__20TWindowChoiceSettingFllll((void *) ((u8 *)&controller_input_state.value + 0x160), 0x20, 6, 1) != 0)) {
            play_cursor_sound(1);
        }
        if ((TWindowShortListCtrl__check_controller_button((int)window_choice_setting, 4) != 0) || (test_flag_4c__23TAdSinglePlyChrSelectGCFv((void *) ((u8 *)&controller_input_state.value + 0x160), 4) != 0)) {
            this->handle_confirm();
        }
        if ((this->get_menu_flag() == 0) && ((TWindowShortListCtrl__check_controller_button((int)window_choice_setting, 2) != 0) || (test_flag_4c__23TAdSinglePlyChrSelectGCFv((void *) ((u8 *)&controller_input_state.value + 0x160), 2) != 0))) {
            this->handle_cancel();
        }
    }
}
