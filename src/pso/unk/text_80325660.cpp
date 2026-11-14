#include "pso/system/CurrentTextureList.h"
#include "types.h"
#include "pso/TAdChrSelMovePlateGC.h"
#include "pso/misc/TWindowSubStatusDisp_803DEE6C.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/object/TObjFish.h"

extern "C" {
extern s32 chr_sel_move_plate_texture;
static const f32 lbl_805DF600 = 0.5199999809265137f;
void draw_move_plate_quads(TAdChrSelMovePlateGC *arg0) {
    u32 i;
    for (i = 0; i < arg0->count; i++) {
        begin_screen_draw(1);
        set_current_texture_list((GinjaTextureList *)(chr_sel_move_plate_texture));
        set_draw_texture_and_color(0, ((u32)arg0->opacity[i] << 24) | 0xFFFFFF);
        draw_textured_quad_at_depth(arg0->quads[i].values, lbl_805DF600);
        TWindowSubStatusDisp::get_player();
    }
}

}
