#include "pso/system/CurrentTextureList.h"
#include "types.h"
#include "pso/misc/TWindowSubStatusDisp_803DEE6C.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/object/TObjFish.h"

extern s32 lbl_805D6668;
extern f32 lbl_805DDF88;

void TWindowSubStatusDisp::render_status_pair(s32 arg1) {
    s32 arg0 = (s32)this;
    begin_screen_draw(1);
    set_current_texture_list((GinjaTextureList *)(lbl_805D6668));
    set_draw_texture_and_color(0, arg1);
    draw_textured_quad_at_depth((f32 *)(arg0 + 0x1C), lbl_805DDF88);
    TWindowSubStatusDisp::get_player();
    begin_screen_draw(1);
    set_current_texture_list((GinjaTextureList *)(lbl_805D6668));
    set_draw_texture_and_color(0, arg1);
    draw_textured_quad_at_depth((f32 *)(arg0 + 0x3C), lbl_805DDF88);
    TWindowSubStatusDisp::get_player();
}
