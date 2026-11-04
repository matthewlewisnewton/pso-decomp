#include "pso/system/CurrentTextureList.h"
#include "types.h"
#include "pso/misc/TWindowSubStatusDisp_8036D774.h"
#include "pso/misc/TWindowSubStatusDisp_803DEE6C.h"
#include "pso/render/render_util.h"

#include "pso/misc/TLobby_801E2F94.h"

#include <stddef.h>
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"

extern "C" {
extern s32 TBGMulti__textures;
s32 TCameraCtrl__sub_80068EF0();
extern s32 split_screen_hud_animation_frame;

void TWindowSubStatusDisp::draw_split_screen_dividers() {
    ColorLineVertex verts[4];
    ColorLineList d;
    u32 cols[4];
    d.verts = verts;
    d.colors = cols;
    d.unk_8 = 0;
    d.count = 4;
    d.verts[0].x = (1.6e+02f);
    d.verts[0].y = (2.4e+02f);
    d.colors[0] = 0xFF000000;
    d.verts[1].x = (4.8e+02f);
    d.verts[1].y = (2.4e+02f);
    d.colors[1] = 0xFF000000;
    d.verts[2].x = (4.8e+02f);
    d.verts[2].y = (4.8e+02f);
    d.colors[2] = 0xFF000000;
    d.verts[3].x = (1.6e+02f);
    d.verts[3].y = (4.8e+02f);
    d.colors[3] = 0xFF000000;
    d.draw_strip_swap_color(4, 0x16, (-2.0f));
    d.verts[0].x = (0.0f);
    d.verts[0].y = (0.0f);
    d.verts[1].x = (6.4e+02f);
    d.verts[1].y = (0.0f);
    d.verts[2].x = (6.4e+02f);
    d.verts[2].y = (2.4e+02f);
    d.verts[3].x = (0.0f);
    d.verts[3].y = (2.4e+02f);
    d.draw_strip_swap_color(4, 0x16, (-2.0f));
}

void TWindowSubStatusDisp::draw_tiled_background() {
    s32 i;
    s32 j;
    f32 buf[8];
    begin_screen_draw(1);
    set_current_texture_list((GinjaTextureList *)(TBGMulti__textures));
    set_draw_texture_and_color(0, -1);
    i = 0;
    buf[4] = 0.5f;
    buf[5] = 0.0f;
    buf[6] = 1.0f;
    buf[7] = 0.5f;
    buf[0] = 0.0f;
    buf[2] = 64.0f;
    do {
        buf[1] = 192.0f;
        j = 0;
        buf[3] = 256.0f;
        do {
            draw_textured_quad_at_depth(buf, 0.5f);
            j++;
            buf[1] += 64.0f;
            buf[3] += 64.0f;
        } while (j < 5);
        i++;
        buf[0] += 64.0f;
        buf[2] += 64.0f;
    } while (i < 10);
    TWindowSubStatusDisp::get_player();
}

#pragma push
#pragma fp_contract on
void TWindowSubStatusDisp__sub_8036D994(void) {
    s32 i;
    f32 buf[8];
    if (split_screen_hud_animation_frame <= 0x1E) {
        set_additive_blend();
        begin_screen_draw(1);
        set_current_texture_list((GinjaTextureList *)(TBGMulti__textures));
        set_draw_texture_and_color(0, -1);
        i = 0;
        buf[0] = 0.0f;
        buf[1] = 10.133333f * split_screen_hud_animation_frame + 176.0f;
        buf[2] = 64.0f;
        buf[3] = buf[1] + 64.0f;
        buf[4] = 0.5f;
        buf[5] = 0.5f;
        buf[6] = 1.0f;
        buf[7] = 1.0f;
        do {
            draw_textured_quad_at_depth(buf, 0.5f);
            i++;
            buf[0] += 64.0f;
            buf[2] += 64.0f;
        } while (i < 10);
        TWindowSubStatusDisp::get_player();
        set_default_alpha_blend();
    }
}
#pragma pop

void TWindowSubStatusDisp::draw_bottom_bar() {
  s32 var_r31;
  f32 buffer_8[8];
  f32 temp_f31;
  begin_screen_draw(1);
  set_current_texture_list((GinjaTextureList *)(((void *) TBGMulti__textures)));
  set_draw_texture_and_color(0, -1);
  var_r31 = 0;
  ;
  buffer_8[0] = (0.0f);
  buffer_8[1] = (352.0f);
  buffer_8[2] = (64.0f);
  buffer_8[3] = (4.8e+02f);
  buffer_8[4] = (0.0f);
  buffer_8[5] = (0.0f);
  buffer_8[6] = (0.5f);
  buffer_8[7] = (1.0f);
  do
  {
    draw_textured_quad_at_depth((&buffer_8[0]), (f32) (0.5f));
    var_r31 += 1;
    buffer_8[0] += (64.0f);
    buffer_8[2] += (64.0f);
  }
  while (var_r31 < 0xA);
  TWindowSubStatusDisp::get_player();
}
void TWindowSubStatusDisp::draw_split_screen_hud() {
    s32 var_r3;
    if ((u32) (*(u32 *)&TBGMulti__textures) != 0U) {
        set_depth_buffer_settings_2();
        set_default_alpha_blend();
        TParticleCtrl::begin_effect_render();
        TCameraCtrl::restore_full_screen_view();
        TWindowSubStatusDisp::draw_bottom_bar();
        TWindowSubStatusDisp__sub_8036D994();
        TWindowSubStatusDisp::draw_tiled_background();
        TWindowSubStatusDisp::draw_split_screen_dividers();
        TCameraCtrl__sub_80068EF0();
        TParticleCtrl::end_effect_render();
        restore_saved_depth_alpha_state();
        var_r3 = split_screen_hud_animation_frame;
        split_screen_hud_animation_frame = var_r3 + 1;
        if (var_r3 > 0x708) {
            split_screen_hud_animation_frame = 0;
        }
    }
}

}
