#include "types.h"
#include "pso/misc/TWindowKeyBoardSoft_8024E68C.h"
#include "pso/misc/WindowViewport.h"
#include "pso/misc/TWindowDrawContext.h"
#include "pso/system/memory.h"
#include "pso/misc/TWindowKeyBoardSoft.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct Vec2_8024EC34 { f32 x; f32 y; };

extern u32 soft_keyboard_instance;
extern "C" {
s32 __cvt_fp2unsigned(f32);
extern const f32 lbl_805DCC84;
extern const f32 lbl_805DCC88;
extern const float lbl_805DCC78;
extern const f32 lbl_805DCC7C;
extern const f32 lbl_805DCC80;
void apply_context_transform_to_rect(TWindowDrawContext *c, f32 *q);
s32 is_split_screen();
f32 TCameraCtrl__sub_80068A04(s32);
Vec2_8024EC34 *get_zero_vec2();
extern Vec2_8024EC34 keyboard_soft_viewport_offset_table[];
extern Vec2_8024EC34 lbl_8044EC80[];
extern Vec2_8024EC34 lbl_8044EC98[];
extern const float lbl_805DCC94;
s32 clip_textured_quad__19TWindowKeyBoardSoftFPvPv(TWindowDrawContext *w, f32 *b);
static const f32 lbl_805DCC98 = 4.0f;
static const f32 lbl_805DCC9C = 10.0f;
static const f32 lbl_805DCCA0 = 0.5f;
static const f32 lbl_805DCCA4 = 2.0f;
u32 init_text_window_layout(TWindowDrawContext *win, f32 *pos, f32 *size, f32 *scale, u32 flags, f32 depth);

void TWindowDrawContext::scale_point_about_pivot(f32 *q) {
    if (lbl_805DCC78 != scale[0]) {
        q[0] = scale[0] * (q[0] - pivot[0]) + pivot[0];
    }
    if (lbl_805DCC78 != scale[1]) {
        q[1] = scale[1] * (q[1] - pivot[1]) + pivot[1];
    }
}

void apply_context_transform_to_rect(TWindowDrawContext *c, f32 *q) {
    if ((*(const f32 *)&lbl_805DCC78) != c->scale[0]) {
        q[0] = c->scale[0] * (q[0] - c->pivot[0]) + c->pivot[0];
        q[2] = c->scale[0] * (q[2] - c->pivot[0]) + c->pivot[0];
    }
    if ((*(const f32 *)&lbl_805DCC78) != c->scale[1]) {
        q[1] = c->scale[1] * (q[1] - c->pivot[1]) + c->pivot[1];
        q[3] = c->scale[1] * (q[3] - c->pivot[1]) + c->pivot[1];
    }
}
}

void apply_window_closing_stretch(TWindowDrawContext *context, int arg1) {
  f32 temp_f2;
  if (arg1 != 0)
  {
    temp_f2 = lbl_805DCC80;
    context->scale[0] = (f32) (context->scale[0] * ((lbl_805DCC7C * (temp_f2 * ((f32) arg1))) + (*(const f32 *)&lbl_805DCC78)));
    context->scale[1] = (f32) (context->scale[1] * ((*(const f32 *)&lbl_805DCC78) - (temp_f2 * ((f32) arg1))));
  }
}

#pragma push
#pragma opt_common_subs off

void TWindowDrawContext::set_open_tick(s32 arg1) {
    s32 temp_r0;
    open_tick = arg1;
    temp_r0 = open_tick;
    if (temp_r0 < 0) {
        color = (u32) ((__cvt_fp2unsigned(lbl_805DCC84 * ((lbl_805DCC88 + (f32) temp_r0) / lbl_805DCC88)) << 0x18) | 0xFF0000 | 0xFFFF);
    }
}
#pragma pop

void TWindowDrawContext::set_bounds(f32 a, f32 b, f32 c, f32 d) {
    clip_left = a;
    clip_top = b;
    clip_right = c;
    clip_bottom = d;
}

extern const f32 lbl_805DCC8C;

void TWindowDrawContext::shrink_clip_right() {
    inner_w = inner_w - lbl_805DCC8C;
    clip_right = clip_right - lbl_805DCC8C;
}

extern const f32 lbl_805DCC90;

void TWindowDrawContext::animate_scale() {
    inner_y = inner_y + lbl_805DCC90;
    inner_h = inner_h - lbl_805DCC90;
    clip_top = clip_top + lbl_805DCC90;
}

s32 TWindowDrawContext::is_point_in_bounds(f32 *quad) {
    if ((quad[2] < clip_left) || (quad[3] < clip_top) || (quad[0] > clip_right) || (quad[1] > clip_bottom)) {
        return 0;
    }
    return 1;
}

s32 clip_textured_quad__19TWindowKeyBoardSoftFPvPv(TWindowDrawContext *w, f32 *b) {
    f32 sx;
    f32 sy;
    f32 d;
    if (w->is_point_in_bounds(b) == 0) {
        return 0;
    }
    sx = (b[6] - b[4]) / (b[2] - b[0]);
    sy = (b[7] - b[5]) / (b[3] - b[1]);
    d = w->clip_left - b[0];
    if (d > (*(const f32 *)&lbl_805DCC94)) {
        b[0] = w->clip_left;
        b[4] = d * sx + b[4];
    }
    d = w->clip_top - b[1];
    if (d > (*(const f32 *)&lbl_805DCC94)) {
        b[1] = w->clip_top;
        b[5] = d * sy + b[5];
    }
    d = b[2] - w->clip_right;
    if (d > (*(const f32 *)&lbl_805DCC94)) {
        b[2] = w->clip_right;
        b[6] = -(d * sx - b[6]);
    }
    d = b[3] - w->clip_bottom;
    if (d > (*(const f32 *)&lbl_805DCC94)) {
        b[3] = w->clip_bottom;
        b[7] = -(d * sy - b[7]);
    }
    return 1;
}

s32 TWindowKeyBoardSoft::try_open(TWindowDrawContext *context, f32 *quad) {
    if (clip_textured_quad__19TWindowKeyBoardSoftFPvPv(context, quad) == 0) {
        return 0;
    }
    apply_context_transform_to_rect(context, quad);
    return 1;
}

u32 init_text_window_layout(TWindowDrawContext *win, f32 *pos, f32 *size, f32 *scale, u32 flags, f32 depth) {
    f32 mx;
    f32 my;
    s32 cam;
    f32 t;
    if (flags & 0x800) {
        mx = (*(const f32 *)&lbl_805DCC94);
        my = mx;
    } else {
        mx = lbl_805DCC98;
        my = lbl_805DCC9C;
    }
    win->w = size[0];
    win->h = size[1];
    win->scale[0] = scale[0];
    win->scale[1] = scale[1];
    if (flags & 0x4000) {
        win->pivot[0] = lbl_805DCCA0 * win->w + pos[0];
        win->pivot[1] = lbl_805DCCA0 * win->h + pos[1];
    } else {
        t = lbl_805DCCA0 * win->w;
        win->pivot[0] = t * win->scale[0] + pos[0];
        t = lbl_805DCCA0 * win->h;
        win->pivot[1] = t * win->scale[1] + pos[1];
    }
    win->open_tick = 0;
    win->color = (u32)-1;
    win->depth = depth;
    if (!(flags & 0x1000) && is_split_screen() != 0) {
        cam = TCameraCtrl::get_camera_no();
        if (cam != 100) {
            adjust_window_position_for_split_screen(win->pivot, cam);
            win->scale[0] = win->scale[0] / TCameraCtrl::get_view_scale();
            win->scale[1] = win->scale[1] / TCameraCtrl::get_fov();
        }
    }
    win->x = win->pivot[0] - lbl_805DCCA0 * win->w;
    win->y = win->pivot[1] - lbl_805DCCA0 * win->h;
    win->inner_x = win->x + mx;
    win->inner_y = win->y + my;
    win->inner_w = win->w - lbl_805DCCA4 * mx;
    win->inner_h = win->h - lbl_805DCCA4 * my;
    win->clip_left = win->x + mx;
    win->clip_top = win->y + my;
    win->clip_right = (win->x + win->w) - mx;
    win->clip_bottom = (win->y + win->h) - my;
    return soft_keyboard_instance;
}

void adjust_window_position_for_split_screen(f32 *position, s32 i) {
    Vec2_8024EC34 *p;
    if (is_split_screen() == 0 || i == 0x64) {
        return;
    }
    p = TWindowKeyBoardSoft::get_viewport_offset(i);
    position[0] = position[0] + (p->x + TCameraCtrl__sub_80068A04(i));
    position[1] = position[1] + (p->y + TCameraCtrl::get_split_offset(i));
    position[0] = position[0] / TCameraCtrl::get_view_scale();
    position[1] = position[1] / TCameraCtrl::get_fov();
}

Vec2_8024EC34 *TWindowKeyBoardSoft::get_viewport_offset(int i) {
    switch (TCameraCtrl::get_camera_id()) {
    case 1:
        break;
    case 2:
        if (i >= 0 && i <= 2) {
            return &keyboard_soft_viewport_offset_table[i];
        }
        break;
    case 3:
        if (i >= 0 && i <= 3) {
            return &lbl_8044EC80[i];
        }
        break;
    case 4:
        if (i >= 0 && i <= 4) {
            return &lbl_8044EC98[i];
        }
        break;
    }
    return get_zero_vec2();
}

TWindowDrawContext *TWindowDrawContext::open_singleton(f32 *pos, f32 *size, f32 *scale, f32 depth, int flags) {
    if ((u32) soft_keyboard_instance == 0U) {
        return 0;
    }
    init_text_window_layout((TWindowDrawContext *)(soft_keyboard_instance), pos, size, scale, (u32)flags, depth);
    return (TWindowDrawContext *)soft_keyboard_instance;
}

u32 TWindowDrawContext::get_or_create_instance() {
    u32 temp_r3;
    u32 var_r0;
    if ((u32) soft_keyboard_instance != 0U) {
        return soft_keyboard_instance;
    }
    temp_r3 = (int)::operator new(0x4C);
    var_r0 = temp_r3;
    if (var_r0 != 0U) {
        var_r0 = ((TWindowDrawContext *)temp_r3)->init_layout();
    }
    soft_keyboard_instance = var_r0;
    return var_r0;
}

u32 TWindowDrawContext::free_singleton(u32 arg0, s16 arg1) {
    if (arg0 != 0U) {
        if ((u32) soft_keyboard_instance == arg0) {
            soft_keyboard_instance = 0U;
        }
        if (arg1 > 0) {
            ::operator delete((void *)arg0);
        }
    }
    return arg0;
}

u32 TWindowDrawContext::init_layout() {
    x = lbl_805DCC94;
    y = lbl_805DCC94;
    w = lbl_805DCC94;
    h = lbl_805DCC94;
    inner_x = lbl_805DCC94;
    inner_y = lbl_805DCC94;
    inner_w = lbl_805DCC94;
    inner_h = lbl_805DCC94;
    clip_left = lbl_805DCC94;
    clip_top = lbl_805DCC94;
    clip_right = lbl_805DCC94;
    clip_bottom = lbl_805DCC94;
    pivot[0] = lbl_805DCC94;
    pivot[1] = lbl_805DCC94;
    scale[0] = lbl_805DCC78;
    scale[1] = lbl_805DCC78;
    open_tick = 0;
    color = (u32)-1;
    depth = lbl_805DCC94;
    return (u32)this;
}
