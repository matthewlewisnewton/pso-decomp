#include "pso/misc/ComCardEntryAbi.h"
#include "types.h"
#include "pso/TObject.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/unk/text_8026CB5C.h"
#include "pso/misc/TWindowCtrl.h"
#include "pso/misc/TWindowComCard.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TUnk_804CE964.h"

struct RecoveredGlobal_80249BA8_lbl_804CE8D0 {
    s32 value;
    u8 remaining[0x10];
};

struct RecoveredGlobal_80249BA8___vt__14TWindowComCard {
    s32 value;
    u8 remaining[0x18];
};

extern "C" {
s32 draw_visible_window_entries(void *, void *, int);
// Existing manual-table ABI entry; body is the native render member below.
void render__14TWindowComCardFv(s32 arg0);
s32 TWindowSubComCard__sub_8007B070(s32);
void *__nw__7TObjectFUl(int);
extern s32 local_client_id;
s32 update_com_card_display(s32, s32);
extern const char *lbl_805D38C0;
void TWindowComCard__sub_80249920(s32 arg0, s32 arg1, s32 arg2);
u8 TWindowComCard__sub_80249C18(void* p);
u8 TWindowComCard__sub_80249C20(void* p);
void run_task__14TWindowComCardFv(void* p);
s32 get_card_entry__17TWindowSubComCardFi(s32 arg0);
void __dl__7TObjectFPv(void *);
int initialize_subwindow__9TWindowDDFv(void*);

extern "C" u8 lbl_8044EB28[];
extern "C" u8 lbl_8044EB30[];
extern "C" u8 lbl_8044EB38[];
extern "C" u8 lbl_8044EB40[];
extern "C" u8 lbl_8044EB48[];
extern "C" u8 lbl_805D63F0[];
extern "C" u8 lbl_805DCBC8[];
extern "C" void render_shadows__7TObjectFv();
void run_task__13TUnk_804CE964Fv(u8 *arg0);
void render__13TUnk_804CE964Fv(s32 arg0);
extern void *lbl_804CE820[44];
void *lbl_804CE820[44] = {
    (void *)0x6, (void *)0x1, (void *)0x3, (void *)0x0,
    (void *)0x0, (void *)0x3f000000, (void *)0xffffffff, (void *)0x40,
    (void *)0x0, (void *)0x3, (void *)0x43460000, (void *)0x41a00000,
    (void *)0x3f000000, (void *)0xffffffff, (void *)0x40, (void *)0x0,
    (void *)0x3, (void *)0x0, (void *)0x42200000, (void *)0x3f000000,
    (void *)0xffffffff, (void *)0x40, (void *)0x0, (void *)0x3,
    (void *)0x0, (void *)0x42700000, (void *)0x3f000000, (void *)0xffffffff,
    (void *)0x40, (void *)0x0, (void *)0x3, (void *)0x0,
    (void *)0x42a00000, (void *)0x3f000000, (void *)0xffffffff, (void *)0x40,
    (void *)0x0, (void *)0x3, (void *)0x0, (void *)0x42c80000,
    (void *)0x3f000000, (void *)0xffffffff, (void *)0x0, (void *)0x0,
};
void *TWindowComCard__window_desc[5] = {
    (void *)0x434e0000, (void *)0x43340000, (void *)0x4743b400, (void *)&lbl_804CE820,
    (void *)0x23,
};
void *com_card_status_text_table[6] = {
    (void *)&lbl_8044EB28, (void *)&lbl_8044EB30, (void *)&lbl_8044EB38, (void *)&lbl_805DCBC8,
    (void *)&lbl_8044EB40, (void *)&lbl_8044EB48,
};
#define TWindowComCard__window_desc (*(RecoveredGlobal_80249BA8_lbl_804CE8D0 *)TWindowComCard__window_desc)

void TWindowComCard__sub_80249920(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp = arg2 + (arg1 * 0x90);
    if (temp != 0) {
        update_com_card_display(arg0 + 0x24, temp);
    }
}

void TWindowComCard::set_display_value(s32 arg1, s32 arg2) {
    s32 arg0 = (s32)this;
    s32 temp = arg2 + (arg1 << 8);
    if (temp != 0) {
        update_com_card_display(arg0 + 0x24, temp);
    }
}

u8 *TWindowComCard::create_for_card(s32 position, s32 index, s32 records) {
    if (index < 0) return NULL;
    s32 data = records + index * 0x90;
    return (u8 *)new TWindowComCard((void *)position, data);
}

void *TWindowComCard::create(void *position, void *index) {
    void *entry = (void *)get_card_entry__17TWindowSubComCardFi((s32)index);
    if (entry == NULL) return NULL;
    return new TWindowComCard(position, (s32)entry);
}

s32 TWindowSubComCard::create_com_card_window(s32 position) {
    s32 keyboard_mode = TWindowSubComCard::get_keyboard_mode();
    if (keyboard_mode == 0) return 0;
    if (TWindowSubComCard__sub_8007B070(keyboard_mode) != 0) {
        ((TWindowSubComCard *)keyboard_mode)->clear_and_init((void *)local_client_id);
    }
    return (s32)new TWindowComCard((void *)position, keyboard_mode);
}

void TWindowComCard::render() {
    s32 context = TWindowDD::draw_default_entry((s32)this);
    draw_window_frame((void *)context);
    draw_visible_window_entries(this, &m_24, context);
}

void TWindowComCard::run_task() { initialize_subwindow__9TWindowDDFv(this); update_fade(); update_window_entry_list(&m_24); }

TWindowComCard::~TWindowComCard() {}

typedef char RecoveredGlobal_80249BA8_lbl_804CE8D0_size[sizeof(RecoveredGlobal_80249BA8_lbl_804CE8D0) == 0x14 ? 1 : -1];
typedef char RecoveredGlobal_80249BA8___vt__14TWindowComCard_size[sizeof(RecoveredGlobal_80249BA8___vt__14TWindowComCard) == 0x1C ? 1 : -1];
TWindowComCard::TWindowComCard(void *position, s32 data)
    : TWindowBase((u8 *)&TWindowComCard__window_desc.value, 4, (u8 *)position) {
    m_name = lbl_805D38C0;
    update_com_card_display((s32)&m_24, data);
}

void*TWindowComCard::get_kbd_ptr() { return (char*)this + 0x20; }
u8 TWindowComCard__sub_80249C18(void* p) { return *(u8*)((char*)p + 0x8e); }
u8 TWindowComCard__sub_80249C20(void* p) { return *(u8*)((char*)p + 0x8d); }
}
extern u8 *text_language_group_table;
s32 get_class_name_text(s32 arg0);
s32 get_class_name_text(s32 arg0) {
    return *(s32 *)((s8 *)(*(s32 *)((s8 *)text_language_group_table + 0x1C)) + (arg0 * 4));
}

void set_sprite_uv_from_pixels(u8 *arg0, f32 farg0, f32 farg1);

extern u8 com_card_help_panel_rect_table[];

extern "C" void set_help_mode__14TWindowComCardFl(void *entry, s32 arg1) {
    void *temp_r4;

    if (arg1 == 0xE) {
        *(u16 *)entry = (u16) (*(u16 *)entry | 2);
        return;
    }
    *(u16 *)entry = (u16) (*(u16 *)entry & 0xFFFFFFFD);
    if (arg1 < 0xA) {
        *(s32 *)((u8 *)entry + 0x34) = 1;
    } else {
        *(s32 *)((u8 *)entry + 0x34) = 2;
    }
    temp_r4 = com_card_help_panel_rect_table + (arg1 * 8);
    set_sprite_uv_from_pixels((u8 *)entry, *(f32 *)((s8 *)temp_r4 + 0), *(f32 *)((s8 *)temp_r4 + 4));
}

void*TWindowComCard::get_card_name_ptr() { return (char*)this + 0xa; }
