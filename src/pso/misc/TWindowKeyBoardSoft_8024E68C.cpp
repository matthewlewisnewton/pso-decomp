#include "types.h"
#include "pso/misc/TWindowKeyBoardSoft_8024E68C.h"
#include "pso/system/memory.h"
#include "pso/misc/TWindowKeyBoardSoft.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct Vec2_8024EC34 { f32 x; f32 y; };

struct Box_8024E8E8 { f32 x0, y0, x1, y1; f32 u0, v0, u1, v1; };


extern TWindowDrawContext *soft_keyboard_instance;
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
Vec2_8024EC34 *get_viewport_offset__19TWindowKeyBoardSoftFi(s32);
Vec2_8024EC34 *get_zero_vec2();
extern Vec2_8024EC34 keyboard_soft_viewport_offset_table[];
extern Vec2_8024EC34 lbl_8044EC80[];
extern Vec2_8024EC34 lbl_8044EC98[];
extern const float lbl_805DCC94;
s32 clip_textured_quad__19TWindowKeyBoardSoftFPvPv(TWindowDrawContext *w, Box_8024E8E8 *b);
extern const f32 lbl_805DCC98;
extern const f32 lbl_805DCC9C;
extern const f32 lbl_805DCCA0;
extern const f32 lbl_805DCCA4;
TWindowDrawContext *init_text_window_layout(TWindowDrawContext *win, f32 *pos, f32 *size, f32 *scale, u32 flags, f32 depth);

#pragma fp_contract on

#pragma push
#pragma fp_contract on
void scale_point_about_pivot__19TWindowKeyBoardSoftFPf(TWindowDrawContext *c, f32 *q) {
    if ((*(const f32 *)&lbl_805DCC78) != c->scale[0]) {
        q[0] = c->scale[0] * (q[0] - c->pivot[0]) + c->pivot[0];
    }
    if ((*(const f32 *)&lbl_805DCC78) != c->scale[1]) {
        q[1] = c->scale[1] * (q[1] - c->pivot[1]) + c->pivot[1];
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
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
#pragma pop

extern "C" void apply_window_closing_stretch__FPUci(TWindowDrawContext *context, int tick) {
    f32 temp_f2;
    if (tick != 0) {
        temp_f2 = lbl_805DCC80;
        context->scale[0] = context->scale[0] * ((lbl_805DCC7C * (temp_f2 * (f32)tick)) + (*(const f32 *)&lbl_805DCC78));
        context->scale[1] = context->scale[1] * ((*(const f32 *)&lbl_805DCC78) - (temp_f2 * (f32)tick));
    }
}

#pragma push
#pragma opt_common_subs off

extern "C" void set_open_tick__19TWindowKeyBoardSoftFl(TWindowDrawContext *context, s32 arg1) {
    s32 temp_r0;
    context->open_tick = arg1;
    temp_r0 = context->open_tick;
    if (temp_r0 < 0) {
        context->color = (u32) ((__cvt_fp2unsigned(lbl_805DCC84 * ((lbl_805DCC88 + (f32) temp_r0) / lbl_805DCC88)) << 0x18) | 0xFF0000 | 0xFFFF);
    }
}
#pragma pop

extern "C" void set_bounds__19TWindowKeyBoardSoftFffff(TWindowDrawContext *c, f32 a, f32 b, f32 x, f32 y) { c->clip_left = a; c->clip_top = b; c->clip_right = x; c->clip_bottom = y; }
extern const f32 lbl_805DCC8C;
extern "C" void shrink_clip_right__19TWindowKeyBoardSoftFv(TWindowDrawContext *c) { c->inner_w -= lbl_805DCC8C; c->clip_right -= lbl_805DCC8C; }
extern const f32 lbl_805DCC90;
extern "C" void animate_scale__19TWindowKeyBoardSoftFv(TWindowDrawContext *c) { c->inner_y += lbl_805DCC90; c->inner_h -= lbl_805DCC90; c->clip_top += lbl_805DCC90; }
extern "C" s32 is_point_in_bounds__19TWindowKeyBoardSoftFPv(TWindowDrawContext *c, void *quad) {
    f32 *p = (f32 *)quad;
    if (p[2] < c->clip_left || p[3] < c->clip_top || p[0] > c->clip_right || p[1] > c->clip_bottom) return 0;
    return 1;
}

#pragma push
#pragma fp_contract on
s32 clip_textured_quad__19TWindowKeyBoardSoftFPvPv(TWindowDrawContext *w, Box_8024E8E8 *b) {
    f32 sx;
    f32 sy;
    f32 d;
    if (is_point_in_bounds__19TWindowKeyBoardSoftFPv(w, b) == 0) {
        return 0;
    }
    sx = (b->u1 - b->u0) / (b->x1 - b->x0);
    sy = (b->v1 - b->v0) / (b->y1 - b->y0);
    d = w->clip_left - b->x0;
    if (d > (*(const f32 *)&lbl_805DCC94)) {
        b->x0 = w->clip_left;
        b->u0 = d * sx + b->u0;
    }
    d = w->clip_top - b->y0;
    if (d > (*(const f32 *)&lbl_805DCC94)) {
        b->y0 = w->clip_top;
        b->v0 = d * sy + b->v0;
    }
    d = b->x1 - w->clip_right;
    if (d > (*(const f32 *)&lbl_805DCC94)) {
        b->x1 = w->clip_right;
        b->u1 = -(d * sx - b->u1);
    }
    d = b->y1 - w->clip_bottom;
    if (d > (*(const f32 *)&lbl_805DCC94)) {
        b->y1 = w->clip_bottom;
        b->v1 = -(d * sy - b->v1);
    }
    return 1;
}
#pragma pop

s32 try_open__19TWindowKeyBoardSoftFii(s32 arg0, s32 arg1) {
    if (clip_textured_quad__19TWindowKeyBoardSoftFPvPv((TWindowDrawContext *)(arg0), (Box_8024E8E8 *)(arg1)) == 0) {
        return 0;
    }
    apply_context_transform_to_rect((TWindowDrawContext *)(arg0), (f32 *)arg1);
    return 1;
}

#pragma push
#pragma fp_contract on
TWindowDrawContext *init_text_window_layout(TWindowDrawContext *win, f32 *pos, f32 *size, f32 *scale, u32 flags, f32 depth) {
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
    win->color = -1;
    win->depth = depth;
    if (!(flags & 0x1000) && is_split_screen() != 0) {
        cam = TCameraCtrl::get_camera_no();
        if (cam != 100) {
            adjust_pos_for_split_screen__19TWindowKeyBoardSoftFl(win->pivot, cam);
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
#pragma pop

extern "C" void adjust_pos_for_split_screen__19TWindowKeyBoardSoftFl(f32 *arg0, s32 i) {
    Vec2_8024EC34 *p;
    if (is_split_screen() == 0 || i == 0x64) {
        return;
    }
    p = get_viewport_offset__19TWindowKeyBoardSoftFi(i);
    arg0[0] = arg0[0] + (p->x + TCameraCtrl__sub_80068A04(i));
    arg0[1] = arg0[1] + (p->y + TCameraCtrl::get_split_offset(i));
    arg0[0] = arg0[0] / TCameraCtrl::get_view_scale();
    arg0[1] = arg0[1] / TCameraCtrl::get_fov();
}

Vec2_8024EC34 *get_viewport_offset__19TWindowKeyBoardSoftFi(s32 i) {
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

extern "C" TWindowDrawContext *open_singleton__19TWindowKeyBoardSoftFiiii(f32 *pos, f32 *size, f32 *scale, u32 flags, f32 depth) {
    if (soft_keyboard_instance == NULL) return NULL;
    init_text_window_layout(soft_keyboard_instance, pos, size, scale, flags, depth);
    return soft_keyboard_instance;
}

extern "C" TWindowDrawContext *get_or_create_instance__19TWindowKeyBoardSoftFv() {
    TWindowDrawContext *context;
    if (soft_keyboard_instance != NULL) return soft_keyboard_instance;
    context = new TWindowDrawContext;
    if (context != NULL) context = init_layout__19TWindowKeyBoardSoftFv(context);
    soft_keyboard_instance = context;
    return context;
}

extern "C" TWindowDrawContext *free_singleton__19TWindowKeyBoardSoftFUls(TWindowDrawContext *context, s16 flag) {
    if (context != NULL) {
        if (soft_keyboard_instance == context) soft_keyboard_instance = NULL;
        if (flag > 0) ::operator delete(context);
    }
    return context;
}

extern "C" TWindowDrawContext *init_layout__19TWindowKeyBoardSoftFv(TWindowDrawContext *context) {
    context->x = lbl_805DCC94; context->y = lbl_805DCC94;
    context->w = lbl_805DCC94; context->h = lbl_805DCC94;
    context->inner_x = lbl_805DCC94; context->inner_y = lbl_805DCC94;
    context->inner_w = lbl_805DCC94; context->inner_h = lbl_805DCC94;
    context->clip_left = lbl_805DCC94; context->clip_top = lbl_805DCC94;
    context->clip_right = lbl_805DCC94; context->clip_bottom = lbl_805DCC94;
    context->pivot[0] = lbl_805DCC94; context->pivot[1] = lbl_805DCC94;
    context->scale[0] = lbl_805DCC78; context->scale[1] = lbl_805DCC78;
    context->open_tick = 0; context->color = 0xffffffffU; context->depth = lbl_805DCC94;
    return context;
}
