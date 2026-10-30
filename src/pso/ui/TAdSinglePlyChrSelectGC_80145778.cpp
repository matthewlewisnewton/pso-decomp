#include "pso/ui/MenuText.h"
#include "pso/TNECFontEORFunction.h"
#include "pso/system/GinjaTexture.h"
#include "pso/misc/TWindowSubStatusDisp_80144B14.h"
#include "types.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

void draw_menu_text(f32 x, f32 y, const char *text, u32 color) {
    draw_menu_font_string(text, color, 0, x, y, 0.5f);
}

extern "C" {
void mem_free(void *p);
extern s32 menu_font_glyph_data;
extern s32 menu_font_glyph_table;
void draw_menu_font_string(const char *s, s32 arg1, u32 flags, f32 x, f32 y, f32 scale);

void TAdSinglePlyChrSelectGC::render_status_disp(f32 arg1, f32 arg2) {
    draw_menu_font_string((const char *)this, -1, (u32)(0), (f32)arg1, (f32)arg2, (f32)0.5f);
}
#pragma push
#pragma fp_contract on
void TAdSinglePlyChrSelectGC::free_resources() {
    delete menu_font_object;
    release_texture_list(&menu_font_texture_list);
    mem_free((void *)menu_font_glyph_table);
    mem_free(menu_font_palette);
    TAdSinglePlyChrSelectGC::safe_free(menu_font_glyph_data);
}
#pragma pop

}
