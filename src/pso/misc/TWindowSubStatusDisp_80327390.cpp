#include "pso/system/CurrentTextureList.h"
#include "types.h"
#include "pso/misc/TWindowSubStatusDisp_803DEE6C.h"
#include "pso/ui/TAdScrollWinGC.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/object/TObjFish.h"

extern s32 scroll_win_texture_handle;
extern const f32 lbl_805DF698;

void TAdScrollWinGC::render_status_value() {
    u8 *arg0 = (u8 *)this;
    begin_screen_draw(1);
    set_current_texture_list((GinjaTextureList *)(scroll_win_texture_handle));
    set_draw_texture_and_color(0, ((this->m_3c << 0x18) | 0xFF0000 | 0xFFFF));
    draw_textured_quad_at_depth((f32 *)(arg0 + 0x1C), lbl_805DF698);
    TWindowSubStatusDisp::get_player();
}
