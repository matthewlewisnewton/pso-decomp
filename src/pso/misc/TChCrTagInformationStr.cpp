#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/TChCrTagInformationStr.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/render/render_util.h"
#include "pso/ui/MenuText.h"
#include "pso/math/AngleLookup.h"
#include "pso/misc/TLobby_80132ED0.h"

extern "C" {
extern s32 char_creation_tag_info_selected_index;
void TCameraCtrl__sub_80068EF0();
}
extern const char *TChCrTagInformationStr__class_name;
extern const f32 TChCrTagInformationStr__data_805DF108;
extern const f32 lbl_805DF10C, lbl_805DF110, lbl_805DF114, lbl_805DF118;
extern const f32 lbl_805DF11C, lbl_805DF120, lbl_805DF124, lbl_805DF128, lbl_805DF12C;

TChCrTagInformationStr *TChCrTagInformationStr::create(TObject *parent, s32 index) {
    return new TChCrTagInformationStr(parent, index);
}

void TChCrTagInformationStr::render() {
    f32 x, y, radius, value, intensity, square;
    if (TChCrTagInformationStr__data_805DF108 != opacity) {
        TCameraCtrl::restore_full_screen_view();
        set_depth_buffer_settings_1();
        value = opacity;
        square = value * value;
        struct Position { f32 x, y; };
        Position position = { 315.0f, 280.0f };
        u32 color = ((u32)(lbl_805DF10C * square) << 24) | 0xFFFFFF;
        intensity = lbl_805DF110 - square;
        u32 glow = ((u32)(lbl_805DF114 * opacity * sin_table_lookup((s32)(lbl_805DF118 * value))) << 24) | 0xFFFFFF;
        radius = lbl_805DF11C * intensity;
        for (s32 line = 0; line < 7; ++line) {
            const char *text = reinterpret_cast<const char *>(get_localized_text_entry(text_group, first_line + line));
            draw_menu_text(position.x, position.y, text, color);
            if (intensity > TChCrTagInformationStr__data_805DF108) {
                y = position.y;
                x = position.x;
                for (s32 ring = 1; ring < 5; ++ring) {
                    f32 distance = (f32)ring * radius;
                    for (s32 angle = 0; angle < 0x10000; angle += 0x10000 / (ring * 4)) {
                        f32 dx = distance * sin_table_lookup(angle);
                        f32 dy = distance * cos_table_lookup(angle);
                        draw_menu_text(x + dx, y + dy, text, glow);
                    }
                }
            }
            position.y += lbl_805DF120;
        }
        restore_saved_depth_alpha_state();
        TCameraCtrl__sub_80068EF0();
    }
}

#pragma push
#pragma opt_common_subs off
void TChCrTagInformationStr::run_task() {
    ++frame;
    if (state != 2 && index != char_creation_tag_info_selected_index) state = 2;
    switch (state) {
    case 0:
        if (--delay <= 0) { delay = 0; state = 1; }
        break;
    case 1:
        opacity += lbl_805DF124;
        if (opacity > lbl_805DF110) opacity = lbl_805DF110;
        break;
    case 2:
        if (char_creation_tag_info_selected_index == -1) opacity += lbl_805DF128;
        else opacity += lbl_805DF12C;
        if (opacity <= TChCrTagInformationStr__data_805DF108) {
            opacity = TChCrTagInformationStr__data_805DF108;
            queue_destruction();
        }
        break;
    }
}
#pragma pop

TChCrTagInformationStr::~TChCrTagInformationStr() {}

TChCrTagInformationStr::TChCrTagInformationStr(TObject *parent, s32 selected) : TObject(parent) {
    m_name = TChCrTagInformationStr__class_name;
    index = selected;
    if (index <= 2) { text_group = 0x11; first_line = index * 7; }
    else { text_group = 0x12; first_line = (index - 3) * 7; }
    frame = 0;
    delay = 5;
    opacity = TChCrTagInformationStr__data_805DF108;
    state = 0;
}
