#include "pso/misc/TWindowBase.h"
#include "pso/misc/WindowConstructorAbi.h"
#include "pso/misc/TWindowDD.h"
#include "pso/TObject.h"
#include "pso/misc/TUnk_804EFBAC.h"

#include "types.h"
#include "pso/misc/WindowVertexBufferAbi.h"
#include "pso/misc/TWindowDrawContext.h"
#include "pso/misc/SmallFontDrawing.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/misc/TWindowDD_WS_ScrollBar.h"
#include "pso/misc/TWindowDD_803488A8.h"
#include "pso/misc/TWindowSubStatusDisp_803DEE6C.h"
#include "pso/system/CurrentTextureList.h"

namespace {
struct WindowVertex {
    f32 x, y, depth;
    f32 u, v;
    u32 color;
};
struct WindowQuad {
    f32 left, top, right, bottom;
    f32 u0, v0, u1, v1;
};
typedef char WindowVertexSize[sizeof(WindowVertex) == 0x18 ? 1 : -1];
}

extern "C" {
extern GinjaTextureList *lbl_805D63F0;
void TWindowDD__sub_803489B8(TWindowDrawContext *, WindowVertex *, s32);
// These legacy helper symbols operate on vertex buffers, draw contexts and
// texture lists. Keep their existing link names at this bounded ABI boundary;
// the generic TWindowDD declarations do not describe their actual receivers.
void draw_transformed_primitive__9TWindowDDFPvPvPv(WindowVertex *, s32, s32, s32);
TWindowDrawContext *draw_default_entry__9TWindowDDFl(TWindowBase *);
s32 get_draw_count__9TWindowDDFPPv(GinjaTextureList *);
extern const f32 lbl_805DFC40, lbl_805DFC44, lbl_805DFC48;
extern const f32 TWindowDD__data_805DFB20, lbl_805DFB4C, lbl_805DFB48;
extern const f32 lbl_805DFC50, lbl_805DFC54, lbl_805DFC58, lbl_805DFC5C;
extern const f32 lbl_805DFC60, lbl_805DFC64, lbl_805DFC68;
extern const f32 lbl_805DFB28, lbl_805DFB24, lbl_805DFB38, lbl_805DFBCC;
extern f32 lbl_805D6DC0, lbl_805D6DC4, lbl_805D6DCC, lbl_805D6DD0;
extern f32 lbl_805D6DD4, lbl_805D6DD8, lbl_805D6DDC, lbl_805D6DE0;
extern f32 lbl_805D6DE4, lbl_805D6DE8, lbl_805D6DEC, lbl_805D6DF0;
extern f32 lbl_805D6DF4, lbl_805D6DF8, lbl_805D6DFC, lbl_805D6E00;

}

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

extern const f32 lbl_805DFC34;
extern const f32 lbl_805DFC38;
extern const f32 lbl_805DFC3C;
extern "C" {
s32 test_flag_4c__23TAdSinglePlyChrSelectGCFv(void *, void *);
s32 TWindowShortListCtrl__check_controller_button(void *, void *);
extern RecoveredGlobal_80340508_lbl_8050E208 controller_input_state;
s32 apply_choice__20TWindowChoiceSettingFllll(void *, void *, int, int);
extern const f32 TWindowDD__data_805DFBFC;
static const f32 lbl_805DFC00 = 310.0f;
static const f32 lbl_805DFC04 = 64.0f;
static const f32 lbl_805DFC08 = 18.0f;
extern const f32 lbl_805DFC2C;
extern const f32 lbl_805DFC30;
void __dl__7TObjectFPv(void *);
void *__nw__7TObjectFUl(int);
int update_fade__11TWindowBaseFv(void*);

void reset_entries__9TWindowDDFf(void *storage, s32 unused_word, f32 depth) {
    E_803403F8 *p = (E_803403F8 *)storage;
    s32 i;
    for (i = 0; i < 8; i++) {
        p->a = lbl_805DFC30;
        p->b = lbl_805DFC30;
        p->c = depth;
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

#pragma push
#pragma opt_propagation off
void TWindowDD__sub_8034055C(TUnk_804EFBAC *self) {
    f32 last_y;
    f32 row_height;
    f32 texture_right;
    f32 next_v;
    f32 advanced_bottom;
    f32 texture_left;
    f32 previous_v;
    f32 step;
    f32 row_bottom;
    f32 inner_bottom;
    f32 inner_top;
    f32 row_top;
    f32 right;
    f32 left;
    f32 scale;
    f32 texture_scale;
    f32 texture_height;
    f32 v_step;
    f32 row_y;
    f32 depth;
    WindowVertex vertices[8];
    WindowQuad quad;
    s32 texture;
    TWindowDrawContext *context = draw_default_entry__9TWindowDDFl(self);
    if (context->open_tick >= 0) {
        self->calc_inner_rect(context);
        depth = TWindowDD__sub_80348AD4(self->m_54, lbl_805DFC40);
        reset_entries__9TWindowDDFf(vertices, -1, depth);
        copy_vertex_uv_table(vertices, 0);
        TWindowDD__sub_80348A2C(context, vertices);
        TWindowDD__sub_803489B8(context, vertices, 0);
        s32 texture_result = get_draw_count__9TWindowDDFPPv(lbl_805D63F0);
        s32 selected;
        if (self->selection_disabled == 0) {
            selected = self->selected_row;
        } else {
            selected = -1;
        }
        s32 row = 0;
        texture = texture_result;
        do {
            TWindowDD__sub_803489B8(context, vertices, row);
            if (row == selected) {
                copy_vertex_uv_table(vertices, 1);
                draw_transformed_primitive__9TWindowDDFPvPvPv(vertices, 8, texture, 1);
                copy_vertex_uv_table(vertices, 0);
            } else {
                draw_transformed_primitive__9TWindowDDFPvPvPv(vertices, 8, texture, 1);
            }
        } while (++row < 3);
        depth = TWindowDD__sub_80348AD4(self->m_54, lbl_805DFC44);
        TWindowDD__sub_803489B8(context, vertices, 0);
        scale = context->scale[1];
        row_y = vertices[0].y;
        last_y = vertices[7].y;
        texture_left = lbl_805DFC40;
        inner_top = row_y + scale;
        inner_bottom = last_y - scale;
        row_height = TWindowDD__data_805DFB20;
        left = vertices[0].x;
        right = vertices[7].x;
        step = row_height * scale;
        texture_right = lbl_805DFC48;
        texture_height = lbl_805DFB4C;
        texture_scale = lbl_805DFB48;
        quad.left = left;
        v_step = texture_height * texture_scale;
        quad.right = right;
        quad.top = inner_top;
        quad.bottom = inner_bottom;
        quad.u0 = texture_left;
        quad.u1 = texture_right;
        quad.v0 = texture_left;
        quad.v1 = v_step;
        bind_small_font_texture_list();
        begin_screen_draw(1);
        set_draw_texture_and_color(4, -1);
        for (s32 row = 0; row < 3; ++row) {
            u32 color;
            if (row == self->selected_row && self->selection_disabled == 0) {
                color = 0xFF000000;
            } else if (self->first_enabled_row <= row) {
                color = 0xFFFFFFFF;
            } else {
                color = 0xFF808080;
            }
            set_constant_material_color(color);
            draw_textured_quad_at_depth(&quad, depth);
            previous_v = quad.v1;
            row_top = quad.top;
            next_v = previous_v + v_step;
            row_bottom = quad.bottom;
            row_top = row_top + step;
            quad.v0 = previous_v;
            advanced_bottom = row_bottom + step;
            quad.v1 = next_v;
            quad.top = row_top;
            quad.bottom = advanced_bottom;
        }
        TWindowSubStatusDisp::get_player();
    }
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

void TWindowDD__sub_8034055C(TUnk_804EFBAC *);
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
        __dt__11TWindowBaseFv((TWindowBase *)(arg0), 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

struct W_803409A4 { u8 pad0[0x18]; void *p18; u8 pad1c[0x5C - 0x1C]; s32 f5c; s32 f60; s32 f64; s32 f68; };

#define arg0 ((W_803409A4 *)arg0v)
void *TWindowDD::construct_variant_a(void *arg0v) {
    __ct__11TWindowBaseFPUcsPUc((TWindowBase *)((TWindowBase *)arg0), (u8 *)((u8 *)TWindowDD__layout_constants), (s16)((s16)4), (u8 *)((u8 *)TWindowDD__layout_constant_pair));
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
    WindowVertex vertices[8];
    WindowQuad quad;
    TWindowDrawContext *context = draw_default_entry__9TWindowDDFl(self);
    self->calc_inner_rect(context);
    s32 texture = get_draw_count__9TWindowDDFPPv(lbl_805D63F0);
    depth = TWindowDD__sub_80348AD4(self->m_54, lbl_805DFC50);
    reset_entries__9TWindowDDFf(vertices, -1, depth);
    WindowTexturePoint *point = TWindowDD__data_805434E8[6];
    WindowVertex *vertex = vertices;
    scale = context->scale[1];
    for (s32 i = 0; i < 8; ++i) {
        vertex->u = point->u;
        vertex->v = point->v;
        ++point;
        ++vertex;
    }
    half = lbl_805DFC54 * self->m_4c;
    center = self->m_44 + half;
    scaled_half = half * scale;
    top = center - scaled_half;
    bottom = center + scaled_half;
    if (scaled_half < lbl_805DFB28) {
        edge = (bottom - top) / lbl_805DFC58;
    } else {
        edge = lbl_805DFC5C;
    }
    inner_top = top + edge;
    vertices[1].y = top;
    inner_bottom = bottom - edge;
    horizontal_factor = lbl_805DFC54;
    vertices[0].y = top;
    vertices[3].y = inner_top;
    width_factor = lbl_805DFB24;
    vertices[2].y = inner_top;
    vertices[5].y = inner_bottom;
    vertices[4].y = inner_bottom;
    vertices[7].y = bottom;
    vertices[6].y = bottom;
    horizontal_size = self->m_48;
    horizontal_scale = context->scale[0];
    horizontal_half = horizontal_factor * horizontal_size;
    x_origin = self->m_40;
    width = width_factor * horizontal_scale;
    x_center = x_origin + horizontal_half;
    left = horizontal_half * horizontal_scale;
    left = x_center - left;
    right = left + width;
    vertex = vertices;
    for (s32 i = 0; i < 4; ++i, vertex += 2) {
        vertex[0].x = left;
        vertex[1].x = right;
    }
    half_width_factor = lbl_805DFC54;
    half_width_source = lbl_805DFB38;
    half_width_scale = context->scale[0];
    half_width_unscaled = half_width_factor * half_width_source;
    half_width = half_width_unscaled * half_width_scale;
    quad.left = x_center - half_width;
    quad.right = x_center + half_width;
    draw_transformed_primitive__9TWindowDDFPvPvPv(vertices, 8, texture, 1);
    depth = TWindowDD__sub_80348AD4(self->m_54, lbl_805DFC60);
    set_current_texture_list(lbl_805D63F0);
    begin_screen_draw(1);
    set_draw_texture_and_color(0, -1);
    quad.v0 = lbl_805D6DCC;
    quad.v1 = lbl_805D6DD0;
    quad.u0 = lbl_805D6DD4;
    quad.u1 = lbl_805D6DD8;
    quad.top = lbl_805DFBCC * scale + top;
    quad.bottom = scale * (lbl_805DFBCC + lbl_805DFB38) + top;
    draw_textured_quad_at_depth(&quad, depth);
    quad.u0 = lbl_805D6DDC;
    quad.u1 = lbl_805D6DE0;
    quad.top = bottom - scale * (lbl_805DFBCC + lbl_805DFB38);
    quad.bottom = bottom - lbl_805DFBCC * scale;
    draw_textured_quad_at_depth(&quad, depth);
    quad.u0 = lbl_805D6DE4;
    quad.u1 = lbl_805D6DE8;
    quad.v0 = lbl_805D6DEC;
    quad.v1 = lbl_805D6DF0;
    quad.top = lbl_805D6DC0 * scale + top;
    quad.bottom = scale * (lbl_805DFC64 + lbl_805D6DC0) + top;
    draw_textured_quad_at_depth(&quad, depth);
    cap_v0 = lbl_805D6DF4;
    cap_v1 = lbl_805D6DF8;
    quad.v0 = cap_v0;
    quad.v1 = cap_v1;
    cap_size = lbl_805D6DC0;
    cap_gap = lbl_805DFC64;
    cap_end = cap_gap + cap_size;
    quad.top = bottom - scale * cap_end;
    quad.bottom = bottom - cap_size * scale;
    draw_textured_quad_at_depth(&quad, depth);
    thumb_v0 = lbl_805D6DFC;
    thumb_v1 = lbl_805D6E00;
    inset_source = lbl_805D6DC4;
    quad.v0 = thumb_v0;
    inset = inset_source * scale;
    quad.v1 = thumb_v1;
    track_top = top + inset;
    track_bottom = bottom - inset;
    if (self->item_count <= self->visible_count) {
        quad.top = track_top;
        quad.bottom = track_bottom;
    } else {
        item_height = self->inverse_item_count * (track_bottom - track_top);
        thumb_height = item_height * self->visible_count;
        if (thumb_height < lbl_805DFC68) {
            thumb_height = lbl_805DFC68;
        }
        thumb_top = item_height * self->first_index + track_top;
        quad.top = thumb_top;
        quad.bottom = thumb_top + thumb_height;
    }
    draw_textured_quad_at_depth(&quad, depth);
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
