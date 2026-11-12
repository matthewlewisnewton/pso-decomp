#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/ui/charcreate/TChCrTagInformationStr.h"
#include "pso/camera/TCameraCtrl.h"
#include "pso/math/AngleLookup.h"
#include "pso/render/render_util.h"
#include "pso/ui/MenuText.h"
#include "pso/unk/TLobby_80132ED0.h"

extern "C" {
extern s32 char_creation_tag_info_selected_index;
void TCameraCtrl__sub_80068EF0(void);
}
extern const char *TChCrTagInformationStr__class_name;
extern const f32 TChCrTagInformationStr__data_805DF108;
extern const f32 lbl_805DF10C, lbl_805DF110, lbl_805DF114, lbl_805DF118;
extern const f32 lbl_805DF11C, lbl_805DF120, lbl_805DF124, lbl_805DF128, lbl_805DF12C;

TChCrTagInformationStr *TChCrTagInformationStr::create(TObject *parent, s32 index) {
    return new TChCrTagInformationStr(parent, index);
}

// Where the first line of the tag text is drawn; each line goes 20 below the last.
struct TagTextOrigin {
    f32 x, y;
};

// Seven lines of text; while fading in, each line also gets rings of faint copies that close in on it.
void TChCrTagInformationStr::render() {
    if (TChCrTagInformationStr__data_805DF108 != alpha) {
        TCameraCtrl::restore_full_screen_view();
        set_depth_buffer_settings_1();
        TagTextOrigin pos = {315.0f, 280.0f};
        f32 radius_step;
        f32 spread;
        f32 sq;
        f32 a;
        u32 color;
        u32 glow_color;
        a = alpha;
        sq = a * a;
        color = ((u32)(lbl_805DF10C * sq) << 24) | 0xFFFFFF;
        spread = lbl_805DF110 - sq;
        glow_color = ((u32)(lbl_805DF114 * alpha * sin_table_lookup(lbl_805DF118 * a)) << 24) | 0xFFFFFF;
        radius_step = lbl_805DF11C * spread;
        s32 line;
        for (line = 0; line < 7; line++) {
            const char *text = (const char *)get_localized_text_entry(text_group, first_text_entry + line);
            draw_menu_text(pos.x, pos.y, text, color);
            if (spread > TChCrTagInformationStr__data_805DF108) {
                s32 ring;
                for (ring = 1; ring < 5; ring++) {
                    f32 radius = ring * radius_step;
                    s32 angle;
                    for (angle = 0; angle < 0x10000; angle += 0x10000 / (ring * 4)) {
                        f32 dx = radius * sin_table_lookup(angle);
                        f32 dy = radius * cos_table_lookup(angle);
                        draw_menu_text(pos.x + dx, pos.y + dy, text, glow_color);
                    }
                }
            }
            pos.y += lbl_805DF120;
        }
        restore_saved_depth_alpha_state();
        TCameraCtrl__sub_80068EF0();
    }
}

#pragma push
#pragma opt_common_subs off
void TChCrTagInformationStr::run_task() {
    ++frame;
    if (state != 2 && tag_index != char_creation_tag_info_selected_index) state = 2;
    switch (state) {
    case 0:
        if (--delay <= 0) { delay = 0; state = 1; }
        break;
    case 1:
        alpha += lbl_805DF124;
        if (alpha > lbl_805DF110) alpha = lbl_805DF110;
        break;
    case 2:
        if (char_creation_tag_info_selected_index == -1) alpha += lbl_805DF128;
        else alpha += lbl_805DF12C;
        if (alpha <= TChCrTagInformationStr__data_805DF108) {
            alpha = TChCrTagInformationStr__data_805DF108;
            queue_destruction();
        }
        break;
    }
}
#pragma pop

TChCrTagInformationStr::~TChCrTagInformationStr() {}

TChCrTagInformationStr::TChCrTagInformationStr(TObject *parent, s32 index) : TObject(parent) {
    m_name = TChCrTagInformationStr__class_name;
    tag_index = index;
    if (tag_index <= 2) { text_group = 0x11; first_text_entry = tag_index * 7; }
    else { text_group = 0x12; first_text_entry = (tag_index - 3) * 7; }
    frame = 0;
    delay = 5;
    alpha = TChCrTagInformationStr__data_805DF108;
    state = 0;
}
