#include "pso/system/CurrentTextureList.h"
#include "pso/ui/window/TWindowDD.h"
#include "pso/system/task/TObject.h"
#include "pso/ui/window/TUnk_804EFBAC.h"
#include "pso/ui/window/TWindowDD_WS_ScrollBar.h"
#include "pso/object/ambient/TObjFish.h"

#include "types.h"
#include "pso/ui/window/TWindowDD_803488A8.h"
#include "pso/ui/window/TWindowKeyBoardSoft.h"
#include "pso/ui/window/TWindowSubStatusDisp.h"
#include "pso/ui/window/TWindowSubStatusDisp_803DEE6C.h"

struct RecoveredGlobal_80340508_lbl_8050E208
{
  s32 value;
  u8 remaining[0x1AC];
};

struct RecoveredGlobal_803404A4_lbl_8050E208
{
  s32 value;
  u8 remaining[0x1AC];
};

struct E_803403F8 { f32 a; f32 b; f32 c; f32 d; f32 e; s32 f; };
struct Src_80348A9C { f32 x; f32 y; };

extern const f32 lbl_805DFC34;
extern const f32 lbl_805DFC38;
extern const f32 lbl_805DFC3C;
extern "C" {
s32 test_flag_4c__23TAdSinglePlyChrSelectGCFv(void *, void *);
s32 TWindowShortListCtrl__check_controller_button(void *, void *);
extern RecoveredGlobal_80340508_lbl_8050E208 controller_input_state;
s32 apply_choice__20TWindowChoiceSettingFllll(void *, void *, int, int);
extern const f32 TWindowDD__data_805DFBFC;
extern const f32 lbl_805DFC00;
extern const f32 lbl_805DFC04;
extern const f32 lbl_805DFC08;
extern const f32 lbl_805DFC2C;
extern const f32 lbl_805DFC30;
void __dl__7TObjectFPv(void *);
void *__nw__7TObjectFUl(int);
int update_fade__11TWindowBaseFv(void*);

void TWindowDD::reset_entries(f32 v, s32) {
    E_803403F8 *p = (E_803403F8 *)this;
    s32 i;
    for (i = 0; i < 8; i++) {
        p->a = lbl_805DFC30;
        p->b = lbl_805DFC30;
        p->c = v;
        p->d = lbl_805DFC30;
        p->e = lbl_805DFC30;
        p->f = -1;
        p++;
    }
}

void TWindowDD::set_quad_corners_scaled(f32 farg0, f32 farg1, f32 farg2) {
    u8 *arg0 = (u8 *)this;
  f32 temp_f0;
  f32 temp_f1;
  f32 temp_f1_2;
  s8 *new_var;
  f32 temp_f2;
  f32 temp_f4;
  float new_var4;
  f32 temp_f5;
  int new_var3;
  f32 temp_f7;
  f32 temp_f8;
  s8 *new_var2;
  temp_f4 = farg0 + farg2;
  temp_f8 = lbl_805DFC34 * farg0;
  temp_f7 = lbl_805DFC34 * farg1;
  *((f32 *) (((s8 *) arg0) + 0)) = temp_f8;
  temp_f5 = lbl_805DFC34 * (lbl_805DFC38 + farg1);
  new_var4 = lbl_805DFC34 * temp_f4;
  *((f32 *) (((s8 *) arg0) + 4)) = temp_f7;
  temp_f1 = lbl_805DFC3C + farg0;
  temp_f2 = new_var4;
  *((f32 *) (((s8 *) arg0) + 8)) = temp_f8;
  temp_f1_2 = lbl_805DFC34 * temp_f1;
  *((f32 *) (((s8 *) arg0) + 0xC)) = temp_f5;
  temp_f0 = temp_f1;
  temp_f0 = lbl_805DFC34 * (temp_f0 - farg2);
  new_var2 = ((s8 *) arg0) + 0x28;
  *((f32 *) (((s8 *) arg0) + 0x10)) = temp_f2;
  *((f32 *) (((s8 *) arg0) + 0x14)) = temp_f7;
  *((f32 *) (((s8 *) arg0) + 0x18)) = temp_f2;
  *((f32 *) (((s8 *) arg0) + 0x1C)) = temp_f5;
  *((f32 *) (((s8 *) arg0) + 0x20)) = temp_f0;
  *((f32 *) (((s8 *) arg0) + 0x24)) = temp_f7;
  new_var3 = 0x30;
  *((f32 *) new_var2) = temp_f0;
  *((f32 *) (((s8 *) arg0) + 0x2C)) = temp_f5;
  *((f32 *) (((s8 *) arg0) + new_var3)) = temp_f1_2;
  *((f32 *) (((s8 *) arg0) + 0x34)) = temp_f7;
  new_var = ((s8 *) arg0) + 0x38;
  *((f32 *) new_var) = temp_f1_2;
  *((f32 *) (((s8 *) arg0) + 0x3C)) = temp_f5;
}

typedef struct RecoveredGlobal_80340508_lbl_8050E208 RecoveredGlobal_80340508_lbl_8050E208;
typedef char RecoveredGlobal_80340508_lbl_8050E208_size[((sizeof(RecoveredGlobal_80340508_lbl_8050E208)) == 0x1B0) ? (1) : (-1)];

#pragma push
#pragma opt_dead_assignments off
typedef struct RecoveredGlobal_803404A4_lbl_8050E208 RecoveredGlobal_803404A4_lbl_8050E208;
typedef char RecoveredGlobal_803404A4_lbl_8050E208_size[((sizeof(RecoveredGlobal_803404A4_lbl_8050E208)) == 0x1B0) ? (1) : (-1)];
s32 TWindowDD::apply_both_choices(s32 arg0, s32 arg1) {
  return apply_choice__20TWindowChoiceSettingFllll((void *) (((u8 *) (&(*(RecoveredGlobal_803404A4_lbl_8050E208 *)&controller_input_state).value)) + 0x20), (void *) arg1, 6, 1) | apply_choice__20TWindowChoiceSettingFllll((void *) (((u8 *) (&(*(RecoveredGlobal_803404A4_lbl_8050E208 *)&controller_input_state).value)) + 0x160), (void *) arg1, 6, 1);
}
}
#pragma pop

s32 TWindowDD_check_input_mask(void *input_context, s32 arg1) {
  return TWindowShortListCtrl__check_controller_button((void *) (((u8 *)&controller_input_state.value) + 0x20), (void *) arg1) | test_flag_4c__23TAdSinglePlyChrSelectGCFv((void *) (((u8 *)&controller_input_state.value) + 0x160), (void *) arg1);
}
extern "C" {

void TWindowDD__sub_803489B8(void *ctx, E_803403F8 *points, s32 row);
extern s32 lbl_805D63F0;
extern const f32 TWindowDD__data_805DFB20;
extern const f32 lbl_805DFB48;
extern const f32 lbl_805DFB4C;
extern const f32 lbl_805DFC40;
extern const f32 lbl_805DFC44;
extern const f32 lbl_805DFC48;

struct Quad_8034055C { f32 x0, y0, x1, y1, u0, v0, u1, v1; };

#pragma push
#pragma opt_propagation off
void TWindowDD__sub_8034055C(TUnk_804EFBAC *self) {
    E_803403F8 points[8];
    Quad_8034055C q;
    s32 count;
    s32 result;
    TWindowKeyBoardSoft *ctx;
    s32 sel;
    s32 i;
    f32 depth;
    f32 step;
    f32 dv;
    f32 h;
    u32 color;

    ctx = (TWindowKeyBoardSoft *)TWindowDD::draw_default_entry((s32)self);
    if (ctx->open_tick < 0) {
        return;
    }
    self->calc_inner_rect((u8 *)ctx);
    ((TWindowDD *)points)->reset_entries(TWindowDD__sub_80348AD4(self->pad_54, lbl_805DFC40), -1);
    ((TWindowDD *)points)->copy_point_table(0);
    TWindowDD__sub_80348A2C(ctx, points);
    TWindowDD__sub_803489B8(ctx, points, 0);
    result = TWindowDD::get_draw_count((void **)lbl_805D63F0);
    if (self->pad_60 == 0) {
        sel = self->pad_68;
    } else {
        sel = -1;
    }
    i = 0;
    count = result;
    for (; i < 3; i++) {
        TWindowDD__sub_803489B8(ctx, points, i);
        if (i == sel) {
            ((TWindowDD *)points)->copy_point_table(1);
            ((TWindowDD *)points)->draw_transformed_primitive((void *)8, (void *)count, (void *)1);
            ((TWindowDD *)points)->copy_point_table(0);
        } else {
            ((TWindowDD *)points)->draw_transformed_primitive((void *)8, (void *)count, (void *)1);
        }
    }
    depth = TWindowDD__sub_80348AD4(self->pad_54, lbl_805DFC44);
    TWindowDD__sub_803489B8(ctx, points, 0);
    h = ctx->scale[1];
    step = TWindowDD__data_805DFB20 * h;
    dv = lbl_805DFB4C * lbl_805DFB48;
    q.x0 = points[0].a;
    q.x1 = points[7].a;
    q.y0 = points[0].b + h;
    q.y1 = points[7].b - h;
    q.u0 = lbl_805DFC40;
    q.u1 = lbl_805DFC48;
    q.v0 = q.u0;
    q.v1 = dv;
    TWindowSubStatusDisp::begin_render();
    begin_screen_draw(1);
    set_draw_texture_and_color(4, -1);
    for (s32 j = 0; j < 3; j++) {
        if (j == self->pad_68 && self->pad_60 == 0) {
            color = 0xFF000000;
        } else if (self->pad_64 <= j) {
            color = 0xFFFFFFFF;
        } else {
            color = 0xFF808080;
        }
        set_constant_material_color(color);
        draw_textured_quad_at_depth((f32 *)&q, depth);
        q.y0 += step;
        q.y1 += step;
        q.v0 = q.v1;
        q.v1 += dv;
    }
    TWindowSubStatusDisp::get_player();
}
#pragma pop

void update_draw__9TWindowDDFPv(void* p) { ((TWindowDD *)p)->initialize_subwindow(); update_fade__11TWindowBaseFv(p); }

void TWindowDD::set_clamped_page(s32 arg1) {
    if (arg1 < 0) {
        this->m_80 = 0;
        return;
    }
    if (arg1 >= 3) {
        this->m_80 = 2;
        return;
    }
    this->m_80 = arg1;
}

s32 TWindowDD__sub_80340820(void* p) { return *(s32*)((char*)p + 0x68); }

#pragma push
#pragma opt_common_subs off
void TWindowDD::handle_input() {
    u8 *arg0 = (u8 *)this;
    s32 temp_r0;
    s32 temp_r31;
    s32 temp_r3;
    temp_r31 = this->m_84;
    if (TWindowDD::apply_both_choices((s32)(arg0 + 0x60), 0x10) != 0) {
        this->m_84 = (this->m_84 - 1);
    } else if (TWindowDD::apply_both_choices((s32)(arg0 + 0x60), 0x20) != 0) {
        this->m_84 = (this->m_84 + 1);
    } else if (TWindowDD::apply_both_choices((s32)(arg0 + 0x60), 0x20000) != 0) {
        this->m_84 = 0;
    } else if (TWindowDD::apply_both_choices((s32)(arg0 + 0x60), 0x10000) != 0) {
        this->m_84 = 2;
    }
    temp_r0 = this->m_84;
    temp_r3 = this->m_80;
    if (temp_r0 < temp_r3) {
        this->m_84 = temp_r3;
    } else if (temp_r0 >= 3) {
        this->m_84 = 2;
    }
    if ((s32) this->m_84 != temp_r31) {
        TWindowDD::spawn_window();
    }
}
#pragma pop

void TWindowDD__sub_80340910(void* p) { *(s32*)((char*)p + 0x60) = 1; }

void render_shadows__7TObjectFv();
__declspec(section ".data") void *TWindowDD__layout_constant_pair[2] = {
    (void *)0x0, (void *)0x0,
};
void *TWindowDD__layout_constants[5] = {
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x3,
};
void *lbl_804EFBAC[7] = {
    (void *)0x0, (void *)0x0, (void *)&__dt__13TUnk_804EFBACFv, (void *)&update_draw__9TWindowDDFPv,
    (void *)&TWindowDD__sub_8034055C, (void *)&render_shadows__7TObjectFv, (void *)0x0,
};
#define TWindowDD__layout_constant_pair ((f32 *)TWindowDD__layout_constant_pair)
#define TWindowDD__layout_constants ((f32 *)TWindowDD__layout_constants)
#define lbl_804EFBAC ((s32 *)lbl_804EFBAC)

void TWindowDD::set_clamped_selection(s32 arg1) {
    s32 temp_r0;
    s32 var_r4;
    var_r4 = arg1;
    temp_r0 = this->m_80;
    if (var_r4 < temp_r0) {
        var_r4 = temp_r0;
    } else if (var_r4 >= 3) {
        var_r4 = 2;
    }
    this->m_84 = var_r4;
    this->m_7c = 0;
}

void *__dt__13TUnk_804EFBACFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = lbl_804EFBAC;
        ((TWindowDD *)arg0)->destroy_window_base(0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

struct W_803409A4 { u8 pad0[0x18]; void *p18; u8 pad1c[0x5C - 0x1C]; s32 f5c; s32 f60; s32 f64; s32 f68; };

#define arg0 ((W_803409A4 *)arg0v)
void *TWindowDD::construct_variant_a(void *arg0v) {
    ((TWindowDD *)arg0)->construct_base((u8 *)TWindowDD__layout_constants, (s16)4, (u8 *)TWindowDD__layout_constant_pair);
    arg0->p18 = lbl_804EFBAC;
    arg0->f60 = 1;
    arg0->f64 = 2;
    arg0->f68 = 2;
    arg0->f5c = 0x01000000;
    return arg0;
}
#undef arg0

void *TWindowDD::create() {
    void *o = __nw__7TObjectFUl(0x6C);
    if (o != NULL) {
        o = TWindowDD::construct_variant_a(o);
    }
    return o;
}

void TWindowDD::init_layout_constants() {
    TWindowDD__layout_constant_pair[0] = TWindowDD__data_805DFBFC;
    TWindowDD__layout_constant_pair[1] = lbl_805DFC00;
    TWindowDD__layout_constants[0] = lbl_805DFC04;
    TWindowDD__layout_constants[1] = lbl_805DFC08;
    TWindowDD__layout_constants[2] = lbl_805DFC2C;
}

extern f32 lbl_805D6DC0;
extern f32 lbl_805D6DC4;
extern f32 lbl_805D6DCC;
extern f32 lbl_805D6DD0;
extern f32 lbl_805D6DD4;
extern f32 lbl_805D6DD8;
extern f32 lbl_805D6DDC;
extern f32 lbl_805D6DE0;
extern f32 lbl_805D6DE4;
extern f32 lbl_805D6DE8;
extern f32 lbl_805D6DEC;
extern f32 lbl_805D6DF0;
extern f32 lbl_805D6DF4;
extern f32 lbl_805D6DF8;
extern f32 lbl_805D6DFC;
extern f32 lbl_805D6E00;
extern const f32 lbl_805DFB24;
extern const f32 lbl_805DFB28;
extern const f32 lbl_805DFB38;
extern const f32 lbl_805DFBCC;
extern Src_80348A9C TWindowDD__data_805434E8[7][8];
extern const f32 lbl_805DFC50;
extern const f32 lbl_805DFC54;
extern const f32 lbl_805DFC58;
extern const f32 lbl_805DFC5C;
extern const f32 lbl_805DFC60;
extern const f32 lbl_805DFC64;
extern const f32 lbl_805DFC68;

// Scroll bar render (slot 4 of the TWindowDD_WS_ScrollBar table lbl_804EFBE4).
#pragma push
#pragma fp_contract on
#pragma opt_propagation off
#pragma opt_common_subs off
void TWindowDD__sub_80340A78(TWindowDD_WS_ScrollBar *self) {
    f32 edge;
    f32 width_factor;
    f32 left;
    f32 half_width_scale;
    f32 half_width;
    f32 thumb_v1;
    f32 center;
    f32 inner_bottom;
    f32 horizontal_size;
    f32 x_origin;
    f32 right;
    f32 half_width_source;
    f32 half_width_unscaled;
    f32 thumb_v0;
    f32 inset;
    f32 track_bottom;
    f32 item_height;
    f32 thumb_top;
    f32 half;
    f32 horizontal_factor;
    f32 horizontal_half;
    f32 half_width_factor;
    f32 inset_source;
    f32 thumb_height;
    f32 cap_gap;
    f32 cap_v1;
    f32 cap_v0;
    f32 cap_end;
    f32 scaled_half;
    f32 inner_top;
    f32 horizontal_scale;
    f32 cap_size;
    f32 x_center;
    f32 track_top;
    f32 width;
    f32 depth;
    f32 scale;
    f32 top;
    f32 bottom;
    E_803403F8 verts[8];
    f32 quad[8];
    TWindowKeyBoardSoft *rect = (TWindowKeyBoardSoft *)TWindowDD::draw_default_entry((s32)self);
    self->calc_inner_rect((u8 *)rect);
    s32 tex = TWindowDD::get_draw_count((void **)lbl_805D63F0);
    depth = TWindowDD__sub_80348AD4(self->pad_54, lbl_805DFC50);
    ((TWindowDD *)verts)->reset_entries(depth, -1);
    Src_80348A9C *uv = TWindowDD__data_805434E8[6];
    E_803403F8 *v = verts;
    scale = rect->scale[1];
    for (s32 i = 0; i < 8; ++i) {
        v->d = uv->x;
        v->e = uv->y;
        ++uv;
        ++v;
    }
    half = lbl_805DFC54 * self->pad_4C;
    center = self->pad_44 + half;
    scaled_half = half * scale;
    top = center - scaled_half;
    bottom = center + scaled_half;
    if (scaled_half < lbl_805DFB28) {
        edge = (bottom - top) / lbl_805DFC58;
    } else {
        edge = lbl_805DFC5C;
    }
    inner_top = top + edge;
    verts[1].b = top;
    inner_bottom = bottom - edge;
    horizontal_factor = lbl_805DFC54;
    verts[0].b = top;
    verts[3].b = inner_top;
    width_factor = lbl_805DFB24;
    verts[2].b = inner_top;
    verts[5].b = inner_bottom;
    verts[4].b = inner_bottom;
    verts[7].b = bottom;
    verts[6].b = bottom;
    horizontal_size = self->pad_48;
    horizontal_scale = rect->scale[0];
    horizontal_half = horizontal_factor * horizontal_size;
    x_origin = self->pad_40;
    width = width_factor * horizontal_scale;
    x_center = x_origin + horizontal_half;
    left = horizontal_half * horizontal_scale;
    left = x_center - left;
    right = left + width;
    v = verts;
    for (s32 i = 0; i < 4; ++i, v += 2) {
        v[0].a = left;
        v[1].a = right;
    }
    half_width_factor = lbl_805DFC54;
    half_width_source = lbl_805DFB38;
    half_width_scale = rect->scale[0];
    half_width_unscaled = half_width_factor * half_width_source;
    half_width = half_width_unscaled * half_width_scale;
    quad[0] = x_center - half_width;
    quad[2] = x_center + half_width;
    ((TWindowDD *)verts)->draw_transformed_primitive((void *)8, (void *)tex, (void *)1);
    depth = TWindowDD__sub_80348AD4(self->pad_54, lbl_805DFC60);
    set_current_texture_list((GinjaTextureList *)(lbl_805D63F0));
    begin_screen_draw(1);
    set_draw_texture_and_color(0, -1);
    quad[5] = lbl_805D6DCC;
    quad[7] = lbl_805D6DD0;
    quad[4] = lbl_805D6DD4;
    quad[6] = lbl_805D6DD8;
    quad[1] = lbl_805DFBCC * scale + top;
    quad[3] = scale * (lbl_805DFBCC + lbl_805DFB38) + top;
    draw_textured_quad_at_depth(quad, depth);
    quad[4] = lbl_805D6DDC;
    quad[6] = lbl_805D6DE0;
    quad[1] = bottom - scale * (lbl_805DFBCC + lbl_805DFB38);
    quad[3] = bottom - lbl_805DFBCC * scale;
    draw_textured_quad_at_depth(quad, depth);
    quad[4] = lbl_805D6DE4;
    quad[6] = lbl_805D6DE8;
    quad[5] = lbl_805D6DEC;
    quad[7] = lbl_805D6DF0;
    quad[1] = lbl_805D6DC0 * scale + top;
    quad[3] = scale * (lbl_805DFC64 + lbl_805D6DC0) + top;
    draw_textured_quad_at_depth(quad, depth);
    cap_v0 = lbl_805D6DF4;
    cap_v1 = lbl_805D6DF8;
    quad[5] = cap_v0;
    quad[7] = cap_v1;
    cap_size = lbl_805D6DC0;
    cap_gap = lbl_805DFC64;
    cap_end = cap_gap + cap_size;
    quad[1] = bottom - scale * cap_end;
    quad[3] = bottom - cap_size * scale;
    draw_textured_quad_at_depth(quad, depth);
    thumb_v0 = lbl_805D6DFC;
    thumb_v1 = lbl_805D6E00;
    inset_source = lbl_805D6DC4;
    quad[5] = thumb_v0;
    inset = inset_source * scale;
    quad[7] = thumb_v1;
    track_top = top + inset;
    track_bottom = bottom - inset;
    if (self->pad_64 <= self->pad_68) {
        quad[1] = track_top;
        quad[3] = track_bottom;
    } else {
        item_height = self->pad_60 * (track_bottom - track_top);
        thumb_height = item_height * self->pad_68;
        if (thumb_height < lbl_805DFC68) {
            thumb_height = lbl_805DFC68;
        }
        thumb_top = item_height * self->pad_6C + track_top;
        quad[1] = thumb_top;
        quad[3] = thumb_top + thumb_height;
    }
    draw_textured_quad_at_depth(quad, depth);
    TWindowSubStatusDisp::get_player();
}
#pragma pop

__declspec(section ".ctors") static void *const windowdd_init_ref = (void *)TWindowDD::init_layout_constants;

void TWindowDD::init() { initialize_subwindow(); update_fade__11TWindowBaseFv(this); }

extern const f32 lbl_805DFC6C;

void TWindowDD::set_value_f32(s32 arg1) {
    *(f32 *)&this->m_88 = (f32) arg1;
}

void TWindowDD::set_scale(s32 arg1, s32 arg2) {
    *(f32 *)&this->m_80 = (f32) arg1;
    *(f32 *)&this->m_84 = (f32) arg2;
    *(f32 *)&this->m_7c = (f32) (lbl_805DFC6C / *(f32 *)&this->m_80);
}
}
