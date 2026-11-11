#include "pso/misc/WordSelectMessage.h"
#include "pso/misc/TextEntryMeasurement.h"
#include "pso/misc/TLobby_8001D6A0.h"
#include "pso/misc/TLobby_8026B06C.h"
#include "pso/misc/TWindowChat.h"
#include "pso/misc/TWindowChatSymbol.h"
#include "pso/misc/TWindowShortCut.h"
#include "pso/misc/TWindowSubStatusDisp_8025B050.h"
#include "pso/misc/TWindowSubStatusDisp_8025A9B4.h"
#include "pso/misc/TWindowSubSymbolChat.h"
#include "pso/unk/text_80076BC4.h"
#include "pso/unk/text_80266BD0.h"
#include "pso/misc/TWindowDrawContext.h"
#include "pso/misc/TWindowOptionCtrl_8026CBA4.h"
#include "types.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowMenuIconLine.h"
#include "pso/misc/TUnk_804D0948.h"
#include "pso/misc/TWindowSubStatusDisp.h"

extern "C" {
s32 draw_visible_window_entries(void *, void *, int);
s32 draw_item_list_capacity(void *, int, int, int);
s32 draw_window_scrollbar(void *, int, void *);
s32 forward_render__20TWindowSubStatusDispFv(void *, int);
extern s32 local_client_id;

#pragma push
#pragma fp_contract on
void TUnk_804D0948::render() {
    u8 *arg0 = (u8 *)this;
    s32 temp_r3;
    s32 n;
    void *p;
    temp_r3 = (s32)get_draw_context__11TWindowBaseFPv(this);
    ((TWindowBase *)arg0)->draw_window_frame((void *)temp_r3);
    draw_visible_window_entries(arg0, arg0 + 0x24, temp_r3);
    if (!(this->state_flags & 0x80)) {
        ((TWindowMenuIconLine *)arg0)->draw_selected_list_entry(temp_r3);
    }
    n = *(s32 *)&this->unk_88;
    if (n > 0) {
        draw_item_list_capacity(arg0, temp_r3, this->entry_count, n);
    }
    p = this->status_display;
    if (p != NULL) {
        forward_render__20TWindowSubStatusDispFv(p, temp_r3);
    }
    p = *(void * *)&this->unk_84;
    if (p != NULL) {
        draw_window_scrollbar(p, temp_r3, (u8 *)&this->m_68);
    }
}
#pragma pop

void TUnk_804D0948::run_task() {
    TWindowMenuIconLine::run_task();
}

TUnk_804D0948::~TUnk_804D0948() {}

TUnk_804D0948::TUnk_804D0948(void *position, s32 heading, u32 count, u8 *descriptor)
    : TWindowMenuIconLine((u8 *)position, count, (s16)local_client_id, descriptor) {
    sub_8026DE94(heading);
}

TUnk_804D0948::TUnk_804D0948(s32 heading, u32 count, s32 client)
    : TWindowMenuIconLine((u8 *)get_window_layout_position(0x26), count, (s16)client) {
    sub_8026DE94(heading);
}

}

namespace {

struct ShortcutEntry {
    u16 flags;
    u8 reserved[0xE];
    f32 width;
    f32 height;
};

struct SpriteOrigin {
    f32 u;
    f32 v;
};

struct PreviewPair {
    f32 x;
    f32 y;
};

enum ShortcutKind {
    SHORTCUT_EMPTY,
    SHORTCUT_TEXT,
    SHORTCUT_WORD_SELECT,
    SHORTCUT_SYMBOL_CHAT,
};

} // namespace

extern const u8 shortcut_kind_sprites[4];
extern const f32 shortcut_preview_center_x;
extern const f32 shortcut_preview_center_y;
extern const f32 shortcut_preview_max_text_width;
extern const f32 shortcut_preview_width_bias;
extern const f32 shortcut_preview_horizontal_padding;
extern const f32 shortcut_preview_height_bias;
extern const f32 shortcut_preview_vertical_padding;
extern const f32 shortcut_preview_half;
extern const f32 shortcut_preview_depth;
extern const f32 shortcut_symbol_preview_width;
extern const f32 shortcut_symbol_preview_height;

extern "C" {
void measure_message_text_width(void *entry, f32 max_width);
}

#pragma push
#pragma fp_contract on
#pragma opt_propagation off
void TWindowShortCut::initialize_preview(s32 index, s32 *shortcut) {
    u8 icon;
    u8 icon_detail;
    PreviewPair position;
    s32 kind;
    PreviewPair size;

    u8 *shortcut_label = static_cast<u8 *>(this->get_array_entry(0));
    ShortcutEntry *shortcut_icon = static_cast<ShortcutEntry *>(this->get_array_entry(2));
    u8 *detail_icon = static_cast<u8 *>(this->get_array_entry(3));
    u8 *kind_label = static_cast<u8 *>(this->get_array_entry(4));
    u8 *kind_icon = static_cast<u8 *>(this->get_array_entry(6));
    u8 *kind_name = static_cast<u8 *>(this->get_array_entry(7));
    u8 *preview_label = static_cast<u8 *>(this->get_array_entry(8));
    ShortcutEntry *preview = static_cast<ShortcutEntry *>(this->get_array_entry(10));

    kind = shortcut[0];
    set_text_entry_string(shortcut_label, (u32)TWindowSubStatusDisp::get_message_10(0xC4), 0);
    fn_80266BD0(index, &icon, &icon_detail, this->m_20);
    if (icon != 0x33) {
        const SpriteOrigin *origin = static_cast<const SpriteOrigin *>(TWindowSubStatusDisp::get_entry_ptr(icon));
        shortcut_icon->flags &= ~2;
        set_sprite_uv_from_pixels(reinterpret_cast<u8 *>(shortcut_icon), origin->u, origin->v);
    } else {
        shortcut_icon->flags |= 2;
    }

    const SpriteOrigin *detail_origin = static_cast<const SpriteOrigin *>(TWindowSubStatusDisp::get_entry_ptr(icon_detail));
    set_sprite_uv_from_pixels(detail_icon, detail_origin->u, detail_origin->v);
    set_text_entry_string(kind_label, (u32)TWindowSubStatusDisp::get_message_10(0xC5), 0);
    set_text_entry_string(kind_name, (u32)TWindowSubStatusDisp::get_message_10(0xC0 + kind), 0);
#ifdef __MWERKS__
    // The GameCube lookup for kind zero reads the separator's trailing zero.
    const s32 kind_sprite_id = shortcut_kind_sprites[kind - 1];
#else
    const s32 kind_sprite_id = kind == SHORTCUT_EMPTY ? 0 : shortcut_kind_sprites[kind - 1];
#endif
    const SpriteOrigin *kind_origin = static_cast<const SpriteOrigin *>(TWindowSubStatusDisp::get_entry_ptr(kind_sprite_id));
    set_sprite_uv_from_pixels(kind_icon, kind_origin->u, kind_origin->v);

    position.x = shortcut_preview_center_x;
    position.y = shortcut_preview_center_y;
    set_text_entry_string(preview_label, (u32)TWindowSubStatusDisp::get_message_10(0x35), 0);

    switch (kind) {
    case SHORTCUT_EMPTY:
        break;
    case SHORTCUT_TEXT: {
        s32 *text = fn_80076BC4(shortcut + 1);
        set_text_entry_string(reinterpret_cast<u8 *>(preview), (u32)text, 0);
        measure_message_text_width(preview, shortcut_preview_max_text_width);

        preview->flags |= 2;
        size.x = shortcut_preview_width_bias + (shortcut_preview_horizontal_padding + preview->width);
        size.y = shortcut_preview_height_bias + (shortcut_preview_vertical_padding + preview->height);
        position.x = TWindowSubStatusDisp::round_away_from_zero(position.x - shortcut_preview_half * size.x);
        position.y = TWindowSubStatusDisp::round_away_from_zero(position.y - shortcut_preview_half * size.y);
        m_64 = (TWindowBase *)create_quest_message_window_at((s32)&position, (s32)&size);
        dispatch_message_window_text(m_64, (s32)text, 0x402);
        m_64->set_depth(shortcut_preview_depth);
        break;
    }
    case SHORTCUT_WORD_SELECT: {
        s32 *buffer = get_shared_text_buffer();
        const u16 player = (u16)local_client_id;
        s32 *words = shortcut + 1;
        format_word_select_message((WordSelectMessage *)words, (char *)buffer, player);
        set_text_entry_string(reinterpret_cast<u8 *>(preview), (u32)get_shared_text_buffer(), 0);
        measure_text_entry(preview);

        preview->flags |= 2;
        size.x = shortcut_preview_width_bias + (shortcut_preview_horizontal_padding + preview->width);
        size.y = shortcut_preview_height_bias + (shortcut_preview_vertical_padding + preview->height);
        position.x = TWindowSubStatusDisp::round_away_from_zero(position.x - shortcut_preview_half * size.x);
        position.y = TWindowSubStatusDisp::round_away_from_zero(position.y - shortcut_preview_half * size.y);
        m_64 = (TWindowBase *)create_quest_message_window_at((s32)&position, (s32)&size);
        dispatch_message_window_text(m_64, (s32)get_shared_text_buffer(), 2);
        m_64->set_depth(shortcut_preview_depth);
        break;
    }
    case SHORTCUT_SYMBOL_CHAT: {
        u8 *preset = TWindowChat::open_symbol_chat(shortcut + 1);
        set_text_entry_string(reinterpret_cast<u8 *>(preview),
            (u32)((TWindowSubSymbolChat *)preset)->get_symbol_chat_data(), 0);

        f32 half;
        f32 height;
        f32 width;
        width = shortcut_symbol_preview_width;
        height = shortcut_symbol_preview_height;
        half = shortcut_preview_half;
        size.x = width;
        position.x -= half * width;
        size.y = height;
        position.y -= half * height;
        TWindowChatSymbol *symbol = new TWindowChatSymbol(&position, &size);
        m_68 = symbol;
        m_68->set_selection((u32)preset);
        m_68->set_depth(shortcut_preview_depth);
        break;
    }
    }
}
#pragma pop

__declspec(section ".sdata2") extern const char shortcut_item_list_separator[4] = ":";
__declspec(section ".sdata2") const u8 shortcut_kind_sprites[4] = {0x12, 0x10, 0x11, 0};
__declspec(section ".sdata2") const f32 shortcut_preview_center_x = 211.0f;
__declspec(section ".sdata2") const f32 shortcut_preview_center_y = 380.0f;
__declspec(section ".sdata2") const f32 shortcut_preview_max_text_width = 200.0f;
__declspec(section ".sdata2") const f32 shortcut_preview_width_bias = 0.1f;
__declspec(section ".sdata2") const f32 shortcut_preview_horizontal_padding = 8.0f;
__declspec(section ".sdata2") const f32 shortcut_preview_height_bias = 3.0f;
__declspec(section ".sdata2") const f32 shortcut_preview_vertical_padding = 20.0f;
__declspec(section ".sdata2") const f32 shortcut_preview_half = 0.5f;
__declspec(section ".sdata2") const f32 shortcut_preview_depth = 50060.0f;
__declspec(section ".sdata2") const f32 shortcut_symbol_preview_width = 203.0f;
__declspec(section ".sdata2") const f32 shortcut_symbol_preview_height = 78.0f;
