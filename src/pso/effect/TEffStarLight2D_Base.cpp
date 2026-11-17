#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/render/render_util.h"
#include "pso/system/NinjaTypes.h"
#include "pso/effect/TEffStarLight2D_Base.h"
#include "pso/effect/TEffStarLight2D.h"
#include "pso/effect/TEffStarLightChild.h"
#include "pso/system/vector.h"
#include "pso/system/MatrixStack.h"
#include "pso/unk/text_803D853C.h"

extern "C" {
extern TObject *tl_particle;
}
void set_additive_blend();
void set_default_alpha_blend();

extern const char TEffStarLightChild_class_name[] = "TEffStarLightChild";
extern const char TEffStarLight2D_class_name[] = "TEffStarLight2D";
const char *TEffStarLightChild__name = TEffStarLightChild_class_name;
const char *TEffStarLight2D__name = TEffStarLight2D_class_name;

__declspec(section ".rodata") NJS_ARGB star_light_2d_base_color = {0.5f, 1.0f, 1.0f, 1.0f};

extern "C" {
f32 vector_length(const Vec *);
f32 normalize_vector(Vec *);
f32 newton_sqrtf(f32);
}

// Reverse definitions preserve the native function, literal and vtable order.
// See docs/evidence/starlight-native-unit.md.
#pragma defer_codegen on

#pragma push
#pragma fp_contract on
TEffStarLightChild::TEffStarLightChild(ColorLineVertex *a, ColorLineVertex *b, TObject *parent, f32 width, f32 speed) : TObject(parent) {
    Vec d;
    m_name = TEffStarLightChild__name;
    if (speed <= 0.0f) {
        speed = 1.0f;
    }
    d.x = b->x - a->x;
    d.y = b->y - a->y;
    d.z = 0.0f;
    if (0.0f != vector_length(&d)) {
        normalize_vector(&d);
    } else {
        d.x = 0.0f;
        d.y = 0.0f;
        d.z = 0.0f;
    }
    edges[0].x = d.y * width + b->x;
    edges[0].y = d.x * width + b->y;
    edges[1].x = -d.y * width + b->x;
    edges[1].y = -d.x * width + b->y;
    if (edges[0].y <= edges[1].y) {
        f32 t0 = edges[0].y;
        f32 t1 = edges[1].y;
        edges[1].y = t0;
        edges[0].y = t1;
    }
    shrink_distance = newton_sqrtf((edges[0].x - edges[1].x) * (edges[0].x - edges[1].x) + (edges[0].y - edges[1].y) * (edges[0].y - edges[1].y)) / 2.0f / speed;
}
#pragma pop

TEffStarLightChild::~TEffStarLightChild() {}

void TEffStarLightChild::run_task() {
    Vec a;
    Vec b;
    Vec c;
    s32 inside = 0;
    c.z = 0.0f;
    c.x = 0.5f * (edges[0].x + edges[1].x);
    c.y = 0.5f * (edges[0].y + edges[1].y);
    a.z = 0.0f;
    a.x = edges[0].x;
    a.y = edges[0].y;
    b.z = 0.0f;
    b.x = edges[1].x;
    b.y = edges[1].y;
    approach_vector_fixed_distance(&a, &c, &a, shrink_distance);
    edges[0].x = a.x;
    edges[0].y = a.y;
    approach_vector_fixed_distance(&b, &c, &b, shrink_distance);
    edges[1].x = b.x;
    edges[1].y = b.y;
    if (edges[0].x >= -100.0f && edges[0].x <= 740.0f) {
        if (edges[0].y >= -100.0f && edges[0].y <= 580.0f) {
            if (edges[1].x >= -100.0f && edges[1].x <= 740.0f) {
                if (edges[1].y >= -100.0f && edges[1].y <= 580.0f) {
                    inside = 1;
                }
            }
        }
    }
    if (inside == 0) {
        queue_destruction();
    } else if (c.x == b.x && c.y == b.y) {
        queue_destruction();
    }
}

void TEffStarLightChild::render() {  }

#pragma push
#pragma opt_common_subs off
TEffStarLight2D::TEffStarLight2D(void *source_position, void *source_parameters, TObject *parent) : TObject(parent) {
    ColorLineVertex p;
    m_name = TEffStarLight2D__name;
    parameters.copy_from((StarLightParameters *)source_parameters);
    VecCopy(&position, (const Vec *)source_position);
    project_world_to_screen(NULL, &position, &p.x);
    previous_screen_position.x = p.x;
    previous_screen_position.y = p.y;
    screen_position.x = previous_screen_position.x;
    screen_position.y = previous_screen_position.y;
}

#pragma pop

TEffStarLight2D::~TEffStarLight2D() {}

// The mutable borrow preserves GC/2.6's alternating loads and stores.
// This copies the parameter subobject, not a TObject prefix.
void StarLightParameters::copy_from(StarLightParameters *source) {
    width = source->width;
    speed = source->speed;
    color.channels.a = source->color.channels.a;
    color.channels.r = source->color.channels.r;
    color.channels.g = source->color.channels.g;
    color.channels.b = source->color.channels.b;
    blend_mode = source->blend_mode;
    alpha_step = source->alpha_step;
}

void TEffStarLight2D::copy_from_subobject(void *source) {
    parameters.copy_from((StarLightParameters *)source);
}

void TEffStarLight2D::run_task() {
    ColorLineVertex screen;
    Vec view;
    f32 dx;
    f32 dy;

    matrix_mult_vec(NULL, &position, &view);
    if (view.z > 0.0f) {
        return;
    }
    project_world_to_screen(NULL, &position, &screen.x);
    if (screen.x >= -100.0f && screen.x <= 740.0f && screen.y >= -100.0f && screen.y <= 580.0f) {
        previous_screen_position.x = screen_position.x;
        previous_screen_position.y = screen_position.y;
        screen_position.x = screen.x;
        screen_position.y = screen.y;
        dx = screen_position.x - previous_screen_position.x;
        dy = screen_position.y - previous_screen_position.y;
        if (dx * dx + dy * dy >= 1.0f) {
            new TEffStarLightChild(&previous_screen_position, &screen_position, this,
                                  parameters.width, parameters.speed);
        }
    }
}

void TEffStarLight2D::queue_child_destruction() {
    if (m_down != NULL && m_down->all_parents_unqueued_for_destruction() != 0) {
        m_down->queue_destruction();
    }
}

#pragma push
#pragma opt_propagation off
void TEffStarLight2D::render() {
    s32 index = 0;
    TEffStarLightChild *next;
    TEffStarLightChild *child;
    for (child = (TEffStarLightChild *)m_down; child != NULL; child = (TEffStarLightChild *)child->m_next) {
        if (child != NULL && child->m_next != NULL) {
            next = (TEffStarLightChild *)child->m_next;
            if (child->all_parents_unqueued_for_destruction() != 0 &&
                next->all_parents_unqueued_for_destruction() != 0) {
                draw_segment(&child->edges[0], &child->edges[1], &next->edges[1], &next->edges[0], index);
                index++;
            }
        }
    }
    set_default_alpha_blend();
}
#pragma pop

#pragma push
#pragma fp_contract on
#pragma opt_common_subs off
void TEffStarLight2D::draw_segment(ColorLineVertex *a, ColorLineVertex *b,
                                 ColorLineVertex *c, ColorLineVertex *d, s32 index) {
    ColorLineVertex vertices[4];
    ColorLineList polygon;
    u32 colors[4];
    StarLightColor start_color;
    StarLightColor end_color;
    u8 alpha = parameters.color.channels.a;
    f32 step = parameters.alpha_step;
    f32 start_alpha = (f32)index * step + (f32)alpha;
    f32 end_alpha = (f32)(index + 1) * step + (f32)alpha;
    f32 clamped_start = start_alpha < 0.0f ? 0.0f
        : start_alpha < 255.0f ? start_alpha : 255.0f;
    f32 clamped_end = end_alpha < 0.0f ? 0.0f
        : end_alpha < 255.0f ? end_alpha : 255.0f;
    if (parameters.blend_mode == 0) {
        set_additive_blend();
    }
    u8 r = parameters.color.channels.r;
    u8 g = parameters.color.channels.g;
    u8 b_color = parameters.color.channels.b;
    start_color.channels.a = clamped_start;
    polygon.verts = vertices;
    polygon.colors = colors;
    polygon.unk_8 = 0;
    polygon.count = 4;
    end_color.channels.a = clamped_end;
    polygon.verts[0].x = a->x;
    polygon.verts[0].y = a->y;
    start_color.channels.r = r;
    start_color.channels.g = g;
    start_color.channels.b = b_color;
    polygon.colors[0] = start_color.packed;
    polygon.verts[1].x = b->x;
    polygon.verts[1].y = b->y;
    polygon.colors[1] = start_color.packed;
    end_color.channels.r = r;
    end_color.channels.g = g;
    end_color.channels.b = b_color;
    polygon.verts[2].x = c->x;
    polygon.verts[2].y = c->y;
    polygon.colors[2] = end_color.packed;
    polygon.verts[3].x = d->x;
    polygon.verts[3].y = d->y;
    polygon.colors[3] = end_color.packed;
    polygon.draw_strip_swap_color(4, 7, -15.0f);
}
#pragma pop

void TEffStarLight2D::copy_position(const Vec *source) {
    VecCopy(&position, source);
}

TEffStarLight2D_Base::TEffStarLight2D_Base(TObject *parent, void *set_data) : TObjBase(parent) {
    StarLightParameters parameters;
    apply_object_set_data(set_data);
    parameters.width = scale.x;
    parameters.speed = scale.y;
    parameters.color.channels.a = scale.z;
    parameters.color.channels.r = set_params[0];
    parameters.color.channels.g = set_params[1];
    parameters.color.channels.b = set_params[2];
    parameters.blend_mode = 0;
    light = new TEffStarLight2D(&position, &parameters, tl_particle);
}

TEffStarLight2D_Base::~TEffStarLight2D_Base() {
    if (light != NULL) {
        light->queue_destruction();
        light = NULL;
    }
}

void TEffStarLight2D_Base::run_task() {
    StarLightParameters parameters;
    if (light == NULL) {
        return;
    }
    light->copy_position(&position);
    parameters.width = scale.x;
    parameters.speed = scale.y;
    parameters.color.channels.a = scale.z;
    parameters.color.channels.r = (f32)set_params[0];
    parameters.color.channels.g = (f32)set_params[1];
    parameters.color.channels.b = (f32)set_params[2];
    parameters.blend_mode = 0;
    light->copy_from_subobject(&parameters);
}

void TEffStarLight2D_Base::render() {
    NJS_ARGB color = star_light_2d_base_color;
    debug_draw_sphere(&position, &color, 2.0f);
}

void *TEffStarLight2D_Base::create(void *set_data) {
    return new TEffStarLight2D_Base(tl_particle, set_data);
}
