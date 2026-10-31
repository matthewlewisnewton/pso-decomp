#include "pso/TNECFontEORFunction.h"
#include "pso/unk/text_803DAFA8.h"

#include "types.h"
#include "dolphin/os/OSCache.h"

extern "C" {
__declspec(section ".data") GinjaTextureList menu_font_texture_list = {
    lbl_8050C090, 2,
};
s32 menu_font_char_advance_table[191] = {
    7, 9, 13, 11, 15, 14, 7, 8, 8, 11, 11, 7, 11, 7, 11, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 7, 7, 9, 11, 9, 10, 15,
    13, 12, 13, 12, 11, 11, 13, 12, 8, 11, 12, 11, 15, 12, 13, 11,
    13, 12, 11, 13, 12, 13, 15, 12, 13, 11, 8, 11, 8, 8, 9, 8,
    12, 11, 12, 11, 12, 10, 12, 11, 6, 9, 11, 6, 14, 11, 12, 11,
    11, 9, 11, 10, 11, 12, 15, 11, 11, 11, 9, 8, 9, 9, 9, 12,
    7, 10, 13, 10, 10, 7, 10, 8, 17, 9, 12, 11, 9, 17, 9, 7,
    11, 8, 8, 8, 11, 11, 8, 7, 6, 9, 12, 13, 13, 13, 10, 13,
    13, 13, 13, 13, 13, 17, 13, 11, 11, 11, 11, 8, 8, 8, 8, 12,
    12, 13, 13, 13, 13, 13, 11, 13, 12, 12, 12, 12, 15, 11, 10, 12,
    12, 12, 12, 12, 12, 17, 12, 12, 12, 12, 12, 6, 6, 6, 6, 11,
    11, 12, 12, 12, 12, 12, 11, 12, 11, 11, 11, 11, 11, 11, 11,
};
}

void TNECFontEORFunction::run_task() {
    if (menu_font_upload_flags & 2) {
        DCFlushRange(menu_font_palette, 0x80);
        init_and_load_tlut(0, 2, 0x80, menu_font_palette);
        menu_font_upload_flags &= 0xFFFFFFFD;
    }
    if (menu_font_upload_flags & 1) {
        menu_font_upload_flags &= 0xFFFFFFFE;
        lbl_805D56C0 += 1;
    }
}
TNECFontEORFunction::~TNECFontEORFunction() {}
