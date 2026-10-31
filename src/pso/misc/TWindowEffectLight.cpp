// Reverse definitions plus deferred emission reproduce the native vtable and jump-table order.
#pragma defer_codegen on
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/system/CurrentTextureList.h"
#include "pso/TWindowEffectLight.h"
#include "pso/misc/TWindowEffectLight.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/render/render_util.h"

#include "types.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/TWindowKeyBoardSoft.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/misc/TWindowSubSymbolChatPartsSet.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"

struct Quad_802AD1CC { f32 x0, y0, x1, y1, u0, v0, u1, v1; };

extern "C" {
extern const f32 lbl_805DE0E0;
extern const f32 TWindowEffectLight__data_805DE0E4;
extern const f32 lbl_805DE0E8;
extern const f32 lbl_805DE0EC;
extern const f32 lbl_805DE0F0;
extern const f32 lbl_805DE0F4;
extern const f32 lbl_805DE0F8;
extern const f32 lbl_805DE0FC;
extern const f32 lbl_805DE100;
extern const f32 lbl_805DE104;
extern const f32 lbl_805DE108;
extern const f32 lbl_805DE10C;
extern const f32 lbl_805DE110;
extern const f32 lbl_805DE114;
extern const f32 lbl_805DE118;
extern const f32 lbl_805DE11C;
extern const f32 lbl_805DE120;
extern const f32 lbl_805DE124;
extern const f32 lbl_805DE128;
extern const f32 lbl_805DE12C;
extern const f32 lbl_805DE130;
s32 __cvt_fp2unsigned(f32);
s32 is_split_screen(void);
void TCameraCtrl__sub_80068EF0(void);
s32 is_window_display_enabled(void);
void TWindowEffectLight__sub_802AD040(TWindowEffectLight *, f32);
void begin_screen_draw(s32);
extern s32 lbl_805D63F0;
extern s32 lbl_805D3E60;
extern s32 tl_window;
void draw_textured_quad_at_depth(f32 *q, f32 depth);
void set_draw_texture_and_color(s32 idx, s32 arg1);

}

extern "C" {

void *__nw__7TObjectFUl(int);

#pragma fp_contract on

}

extern "C" {
void *TWindowEffectLight::create(void *arg0, void *arg1, void *arg2) {
    void *o;
    o = __nw__7TObjectFUl(0x2C);
    if (o != NULL) {
        o = ((void *(*)(void *, void *, void *, void *))__ct__18TWindowEffectLightFPvsUl)(o, arg0, arg1, arg2);
    }
    return o;
}

TWindowEffectLight::TWindowEffectLight(void *arg1, s16 arg2, u32 id) : TObject((TObject *)tl_window) {
    m_name = (const char *)lbl_805D3E60;
    ((TWindowSubSymbolChatPartsSet *)(((u8 *)this) + 0x1C))->copy_vec2(arg1);
    ((TWindowKeyBoardSoft *)(((u8 *)this) + 0x1C))->adjust_pos_for_split_screen(TCameraCtrl::get_split_screen_view_index(id));
    effect_kind = arg2;
    age = -1;
    player_id = id;
}

TWindowEffectLight::~TWindowEffectLight() {}

void TWindowEffectLight::run_task() {
    s32 temp_r4;

    temp_r4 = age + 1;
    age = temp_r4;
    if ((s16)temp_r4 >= 8) {
        queue_destruction();
    }
}

void TWindowEffectLight::render() {
  TWindowEffectLight *window_effect_light = this;
  s16 temp_r0;
  temp_r0 = 0x28;
  if ((is_window_display_enabled() != 0) && ((is_split_screen() == 0) || (((s32) window_effect_light->player_id) == ((s32) TCameraCtrl::get_nth_view_player_id(TCameraCtrl::get_camera_no())))))
  {
    TParticleCtrl::begin_effect_render();
    TCameraCtrl::restore_full_screen_view();
    set_additive_blend();
    begin_screen_draw(1);
    set_current_texture_list((GinjaTextureList *)(lbl_805D63F0));
    temp_r0 = effect_kind;
    {
      switch (temp_r0)
      {
        case 0:
          ((TWindowEffectLight *)window_effect_light)->draw_outline_quad(0xAA0E);
          break;
        case 1:
          ((TWindowEffectLight *)window_effect_light)->draw_outline_quad(0xFF2417);
          break;
        case 2:
          ((TWindowEffectLight *)window_effect_light)->draw_outline_quad(0xFFFFFF);
          break;
        case 3:
          TWindowEffectLight__sub_802AD040((TWindowEffectLight *)window_effect_light, lbl_805DE0F4);
          break;
        case 4:
          TWindowEffectLight__sub_802AD040((TWindowEffectLight *)window_effect_light, lbl_805DE128);
          break;
        case 5:
          TWindowEffectLight__sub_802AD040((TWindowEffectLight *)window_effect_light, lbl_805DE12C);
          break;
        case 6:
          TWindowEffectLight__sub_802AD040((TWindowEffectLight *)window_effect_light, lbl_805DE130);
          break;
      }
    }
    TWindowSubStatusDisp::get_player();
    set_default_alpha_blend();
    TCameraCtrl__sub_80068EF0();
    TParticleCtrl::end_effect_render();
  }
}

void TWindowEffectLight::draw_outline_quad(s32 color) {
    Quad_802AD1CC q;
    f32 s;
    f32 w;
    f32 h;
    color |= this->calc_alpha();
    s = this->calc_scale();
    if (TCameraCtrl::get_camera_id() <= 2 && TCameraCtrl::get_camera_id() == 2) {
        s *= lbl_805DE10C;
    }
    set_draw_texture_and_color(2, color);
    q.x0 = this->x - lbl_805DE110 * s;
    q.y0 = this->y - lbl_805DE114 * s;
    q.x1 = this->x + lbl_805DE110 * s;
    q.y1 = this->y + lbl_805DE114 * s;
    q.u0 = lbl_805DE118;
    q.v0 = lbl_805DE11C;
    q.u1 = lbl_805DE120;
    q.v1 = lbl_805DE124;
    draw_textured_quad_at_depth((f32 *)&q, TWindowEffectLight__data_805DE0E4);
}

void TWindowEffectLight__sub_802AD040(TWindowEffectLight *self, f32 width) {
    
    Quad_802AD1CC q;
    u32 color = self->calc_alpha() | 0x00FFFFFF;
    f32 scale = self->calc_scale();
    set_draw_texture_and_color(2, color);
    f32 half_height;
    f32 half_width = TWindowEffectLight__data_805DE0E4 * (width - lbl_805DE0F4);
    half_height = lbl_805DE0F8 * scale;
    q.x0 = self->x - half_width - half_height;
    q.y0 = self->y - half_height;
    q.x1 = self->x - half_width;
    q.y1 = self->y + half_height;
    q.u0 = lbl_805DE0FC;
    q.v0 = TWindowEffectLight__data_805DE0E4;
    q.u1 = lbl_805DE100;
    q.v1 = lbl_805DE104;
    draw_textured_quad_at_depth((f32 *)&q, TWindowEffectLight__data_805DE0E4);
    q.x0 = self->x + half_width;
    q.y0 = self->y - half_height;
    q.x1 = self->x + half_width + half_height;
    q.y1 = self->y + half_height;
    q.u0 = lbl_805DE100;
    q.v0 = TWindowEffectLight__data_805DE0E4;
    q.u1 = lbl_805DE108;
    q.v1 = lbl_805DE104;
    draw_textured_quad_at_depth((f32 *)&q, TWindowEffectLight__data_805DE0E4);
    if (width > lbl_805DE0F4) {
        q.x0 = self->x - half_width;
        q.y0 = self->y - half_height;
        q.x1 = self->x + half_width;
        q.y1 = self->y + half_height;
        q.u0 = lbl_805DE100;
        q.v0 = TWindowEffectLight__data_805DE0E4;
        q.u1 = lbl_805DE100;
        q.v1 = lbl_805DE104;
        draw_textured_quad_at_depth((f32 *)&q, TWindowEffectLight__data_805DE0E4);
    }
}

u32 TWindowEffectLight::calc_alpha() {
  float new_var;
  new_var = lbl_805DE0F0 * ((f32) (*(&age)));
  return (u32)__cvt_fp2unsigned(lbl_805DE0EC * ((new_var * lbl_805DE0E8) + lbl_805DE0E0));
}

f32 TWindowEffectLight::calc_scale() {
  float new_var2;
  s16 *new_var;
  new_var2 = TWindowEffectLight__data_805DE0E4 * ((f32) (*(new_var = &age)));
  return (new_var2 * lbl_805DE0E8) + lbl_805DE0E0;
}
}

extern "C" {
extern const f32 lbl_805DE0E0 = 1.0f;
extern const f32 TWindowEffectLight__data_805DE0E4 = 0.5f;
extern const f32 lbl_805DE0E8 = 0.125f;
extern const f32 lbl_805DE0EC = 4278190080.0f;
extern const f32 lbl_805DE0F0 = -1.0f;
extern const f32 lbl_805DE0F4 = 20.0f;
extern const f32 lbl_805DE0F8 = 10.0f;
extern const f32 lbl_805DE0FC = 0.9140625f;
extern const f32 lbl_805DE100 = 0.953125f;
extern const f32 lbl_805DE104 = 0.578125f;
extern const f32 lbl_805DE108 = 0.9921875f;
extern const f32 lbl_805DE10C = 0.7f;
extern const f32 lbl_805DE110 = 25.0f;
extern const f32 lbl_805DE114 = 21.5f;
extern const f32 lbl_805DE118 = 0.79296875f;
extern const f32 lbl_805DE11C = 0.60546875f;
extern const f32 lbl_805DE120 = 0.98828125f;
extern const f32 lbl_805DE124 = 0.7734375f;
extern const f32 lbl_805DE128 = 39.0f;
extern const f32 lbl_805DE12C = 77.0f;
extern const f32 lbl_805DE130 = 191.0f;
}
