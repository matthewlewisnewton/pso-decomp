#include "types.h"
#include "pso/ui/window/TWindowKeyBoardSoft_8024E68C.h"
#include "pso/system/memory.h"
#include "pso/ui/window/TWindowKeyBoardSoft.h"
#include "pso/camera/TCameraCtrl.h"
#include "pso/ui/frontend/TAdSinglePlyChrSelectGC.h"
#include "pso/ui/window/TWindowCtrlMain_8024EEF8.h"
#include "pso/ui/window/TWindowCtrlMain.h"
#include "pso/system/NinjaTypes.h"
#include "pso/player/TObjPlayer_80011014.h"

struct Ctx_8024E6D8 { u8 pad[0x20]; f32 pivot[2]; f32 scale[2]; };

struct Box_8024E8E8 { f32 x0, y0, x1, y1; f32 u0, v0, u1, v1; };

struct Win_8024E8E8 { u8 pad[0x3C]; f32 x0, y0, x1, y1; };

u32 window_draw_context_instance;
// Keyboard offsets per player viewport for two, three and four split-screen views (camera ids 2-4).
// inferred: _3p/_4p names from the camera-count switch in get_viewport_offset.
extern const NJS_POINT2 keyboard_soft_viewport_offset_table[2] = {
    {0.0f, 40.0f}, {0.0f, 0.0f},
};
extern const NJS_POINT2 keyboard_soft_viewport_offset_table_3p[3] = {
    {8.0f, 40.0f}, {0.0f, 40.0f}, {0.0f, 0.0f},
};
extern const NJS_POINT2 keyboard_soft_viewport_offset_table_4p[4] = {
    {8.0f, 40.0f}, {0.0f, 40.0f}, {8.0f, 0.0f}, {0.0f, 0.0f},
};

extern "C" {
void apply_context_transform_to_rect(Ctx_8024E6D8 *c, f32 *q);
f32 TCameraCtrl__sub_80068A04(s32);
const NJS_POINT2 *get_viewport_offset__19TWindowKeyBoardSoftFi(s32);
NJS_POINT2 *get_zero_vec2();
s32 clip_textured_quad__19TWindowKeyBoardSoftFPvPv(Win_8024E8E8 *w, Box_8024E8E8 *b);
u32 init_text_window_layout(TWindowDrawContext *win, f32 *pos, f32 *size, f32 *scale, u32 flags, f32 depth);

#pragma fp_contract on

#pragma push
#pragma fp_contract on
void TWindowDrawContext::scale_point_about_pivot(f32 *q) {
    if (1.0f != scale[0]) {
        q[0] = scale[0] * (q[0] - pivot[0]) + pivot[0];
    }
    if (1.0f != scale[1]) {
        q[1] = scale[1] * (q[1] - pivot[1]) + pivot[1];
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
void apply_context_transform_to_rect(Ctx_8024E6D8 *c, f32 *q) {
    if (1.0f != c->scale[0]) {
        q[0] = c->scale[0] * (q[0] - c->pivot[0]) + c->pivot[0];
        q[2] = c->scale[0] * (q[2] - c->pivot[0]) + c->pivot[0];
    }
    if (1.0f != c->scale[1]) {
        q[1] = c->scale[1] * (q[1] - c->pivot[1]) + c->pivot[1];
        q[3] = c->scale[1] * (q[3] - c->pivot[1]) + c->pivot[1];
    }
}
}
#pragma pop

void apply_window_closing_stretch(TWindowDrawContext *context, int tick) {
    if (tick != 0) {
        const f32 stretch_per_tick = 2.0f / 9.0f;
        context->scale[0] *= 2.3f * (stretch_per_tick * tick) + 1.0f;
        context->scale[1] *= 1.0f - stretch_per_tick * tick;
    }
}

#pragma push
#pragma opt_common_subs off

void TWindowDrawContext::set_open_tick(s32 tick) {
    open_tick = tick;
    if (open_tick < 0) {
        f32 fade = (7.5f + open_tick) / 7.5f;
#ifndef __MWERKS__
        // The GameCube unsigned conversion returns zero for negative alpha.
        if (fade < 0.0f) {
            fade = 0.0f;
        }
#endif
        color = (static_cast<u32>(255.0f * fade) << 24) | 0x00ffffff;
    }
}
#pragma pop

void TWindowDrawContext::set_bounds(f32 a, f32 b, f32 c, f32 d) {
    clip_left = a;
    clip_top = b;
    clip_right = c;
    clip_bottom = d;
}


void TWindowDrawContext::shrink_clip_right() {
    inner_w -= 5.0f;
    clip_right -= 5.0f;
}


void TWindowDrawContext::animate_scale() {
    inner_y += 6.0f;
    inner_h -= 6.0f;
    clip_top += 6.0f;
}

s32 TWindowDrawContext::is_point_in_bounds(void *arg1) {
    if ((*(f32 *)((s8 *)arg1 + 8) < *(f32 *)((s8 *)this + 0x3C)) || (*(f32 *)((s8 *)arg1 + 0xC) < *(f32 *)((s8 *)this + 0x40)) || (*(f32 *)((s8 *)arg1 + 0) > *(f32 *)((s8 *)this + 0x44)) || (*(f32 *)((s8 *)arg1 + 4) > *(f32 *)((s8 *)this + 0x48))) {
        return 0;
    }
    return 1;
}

#pragma push
#pragma fp_contract on
s32 clip_textured_quad__19TWindowKeyBoardSoftFPvPv(Win_8024E8E8 *w, Box_8024E8E8 *b) {
    f32 sx;
    f32 sy;
    f32 d;
    if (((TWindowDrawContext *)w)->is_point_in_bounds(b) == 0) {
        return 0;
    }
    sx = (b->u1 - b->u0) / (b->x1 - b->x0);
    sy = (b->v1 - b->v0) / (b->y1 - b->y0);
    d = w->x0 - b->x0;
    if (d > 0.0f) {
        b->x0 = w->x0;
        b->u0 = d * sx + b->u0;
    }
    d = w->y0 - b->y0;
    if (d > 0.0f) {
        b->y0 = w->y0;
        b->v0 = d * sy + b->v0;
    }
    d = b->x1 - w->x1;
    if (d > 0.0f) {
        b->x1 = w->x1;
        b->u1 = -(d * sx - b->u1);
    }
    d = b->y1 - w->y1;
    if (d > 0.0f) {
        b->y1 = w->y1;
        b->v1 = -(d * sy - b->v1);
    }
    return 1;
}
#pragma pop

s32 try_open__19TWindowKeyBoardSoftFii(s32 arg0, s32 arg1) {
    if (clip_textured_quad__19TWindowKeyBoardSoftFPvPv((Win_8024E8E8 *)(arg0), (Box_8024E8E8 *)(arg1)) == 0) {
        return 0;
    }
    apply_context_transform_to_rect((Ctx_8024E6D8 *)(arg0), (f32 *)arg1);
    return 1;
}

#pragma push
#pragma fp_contract on
u32 init_text_window_layout(TWindowDrawContext *win, f32 *pos, f32 *size, f32 *scale, u32 flags, f32 depth) {
    f32 mx;
    f32 my;
    s32 cam;
    f32 t;
    if (flags & 0x800) {
        mx = 0.0f;
        my = mx;
    } else {
        mx = 4.0f;
        my = 10.0f;
    }
    win->w = size[0];
    win->h = size[1];
    win->scale[0] = scale[0];
    win->scale[1] = scale[1];
    if (flags & 0x4000) {
        win->pivot[0] = 0.5f * win->w + pos[0];
        win->pivot[1] = 0.5f * win->h + pos[1];
    } else {
        t = 0.5f * win->w;
        win->pivot[0] = t * win->scale[0] + pos[0];
        t = 0.5f * win->h;
        win->pivot[1] = t * win->scale[1] + pos[1];
    }
    win->open_tick = 0;
    win->color = -1;
    win->depth = depth;
    if (!(flags & 0x1000) && is_split_screen() != 0) {
        cam = TCameraCtrl::get_camera_no();
        if (cam != 100) {
            adjust_window_position_for_split_screen(win->pivot, cam);
            win->scale[0] = win->scale[0] / TCameraCtrl::get_view_scale();
            win->scale[1] = win->scale[1] / TCameraCtrl::get_fov();
        }
    }
    win->x = win->pivot[0] - 0.5f * win->w;
    win->y = win->pivot[1] - 0.5f * win->h;
    win->inner_x = win->x + mx;
    win->inner_y = win->y + my;
    win->inner_w = win->w - 2.0f * mx;
    win->inner_h = win->h - 2.0f * my;
    win->clip_left = win->x + mx;
    win->clip_top = win->y + my;
    win->clip_right = (win->x + win->w) - mx;
    win->clip_bottom = (win->y + win->h) - my;
    return window_draw_context_instance;
}
#pragma pop

void adjust_window_position_for_split_screen(f32 *position, s32 i) {
    const NJS_POINT2 *p;
    if (is_split_screen() == 0 || i == 0x64) {
        return;
    }
    p = get_viewport_offset__19TWindowKeyBoardSoftFi(i);
    position[0] = position[0] + (p->x + TCameraCtrl__sub_80068A04(i));
    position[1] = position[1] + (p->y + TCameraCtrl::get_split_offset(i));
    position[0] = position[0] / TCameraCtrl::get_view_scale();
    position[1] = position[1] / TCameraCtrl::get_fov();
}

const NJS_POINT2 *get_viewport_offset__19TWindowKeyBoardSoftFi(s32 i) {
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
            return &keyboard_soft_viewport_offset_table_3p[i];
        }
        break;
    case 4:
        if (i >= 0 && i <= 4) {
            return &keyboard_soft_viewport_offset_table_4p[i];
        }
        break;
    }
    return get_zero_vec2();
}

TWindowDrawContext *TWindowDrawContext::open_singleton(f32 *pos, f32 *size, f32 *scale, f32 depth, int flags) {
    if (window_draw_context_instance == 0) {
        return NULL;
    }
    init_text_window_layout((TWindowDrawContext *)window_draw_context_instance, pos, size, scale, flags, depth);
    return (TWindowDrawContext *)window_draw_context_instance;
}

u32 TWindowDrawContext::get_or_create_instance() {
    u32 temp_r3;
    u32 var_r0;
    if ((u32) window_draw_context_instance != 0U) {
        return window_draw_context_instance;
    }
    temp_r3 = (int)::operator new(0x4C);
    var_r0 = temp_r3;
    if (var_r0 != 0U) {
        var_r0 = ((TWindowDrawContext *)temp_r3)->init_layout();
    }
    window_draw_context_instance = var_r0;
    return var_r0;
}

u32 TWindowDrawContext::free_singleton(u32 arg0, s16 arg1) {
    if (arg0 != 0U) {
        if ((u32) window_draw_context_instance == arg0) {
            window_draw_context_instance = 0U;
        }
        if (arg1 > 0) {
            ::operator delete((void *)arg0);
        }
    }
    return arg0;
}

u32 TWindowDrawContext::init_layout() {
    x = 0.0f;
    y = 0.0f;
    w = 0.0f;
    h = 0.0f;
    inner_x = 0.0f;
    inner_y = 0.0f;
    inner_w = 0.0f;
    inner_h = 0.0f;
    clip_left = 0.0f;
    clip_top = 0.0f;
    clip_right = 0.0f;
    clip_bottom = 0.0f;
    pivot[0] = 0.0f;
    pivot[1] = 0.0f;
    scale[0] = 1.0f;
    scale[1] = 1.0f;
    open_tick = 0;
    color = (u32)-1;
    depth = 0.0f;
    return (u32)this;
}

void TWindowCtrlMain::free_keyboard_soft() {
    if ((u32) window_draw_context_instance != 0U) {
        TWindowDrawContext::free_singleton((u32)((void*)window_draw_context_instance), (s16)1);
        window_draw_context_instance = 0U;
    }
}
void TWindowCtrlMain__sub_8024EF30(void) { (*(int *)&window_draw_context_instance) = 0; }
