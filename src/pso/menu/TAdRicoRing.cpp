#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/TAdRicoRing.h"
#include "pso/ui/TAdRicoRingCtrl.h"
#include "pso/system/BmlResource.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/system/BmlTextureList.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/NinjaTypes.h"
#include "pso/system/vector.h"
#include "pso/render/ColorLineList.h"
#include "pso/render/TriangleFan3D.h"
#include "pso/TMath.h"
#include "pso/object/TObjFish.h"
#include "pso/misc/TKeyBoardControl_8000F764.h"
#include "pso/unk/text_803D853C.h"
#include "pso/system/MatrixStack.h"
#include "pso/unk/text_803E2D70.h"

#if defined(__MWERKS__)
#define RICO_SECTION(name) __declspec(section name)
#else
#define RICO_SECTION(name)
#endif

extern "C" {
int test_flags_any(void *, s32);
u32 __cvt_fp2unsigned(f32);
extern TObject *tl_04;
extern const char *TAdRicoRing__class_name;
extern const char *TAdRicoRingCtrl__class_name;
extern BmlResource *TAdRicoRing__resource_bundle;
extern const f32 lbl_80434828[];
extern const ColorLineList rico_ring_render_params;
extern const f32 lbl_805D7E48, lbl_805D7E4C, TAdRicoRingCtrl__data_805D7E50;
extern const f32 lbl_805D7E54, lbl_805D7E58, lbl_805D7E5C, lbl_805D7E60, lbl_805D7E64, lbl_805D7E68;
extern BmlResourceDescriptor TAdRicoRingCtrl__resource_descriptor;
const char *rico_ring_model_names[] = { "rico_ring.nj", NULL };
const char *rico_ring_motion_names[] = { "rico_ring.njm", NULL };
BmlResourceDescriptor TAdRicoRingCtrl__resource_descriptor = {
    "rico_ring.bml", rico_ring_model_names, rico_ring_motion_names, 1, 1
};
const char *TAdRicoRing__class_name = "TAdRicoRing";
const char *TAdRicoRingCtrl__class_name = "TAdRicoRingCtrl";
RICO_SECTION(".data") u32 lbl_804809D0[4] = { 0xB0, 0xB0, 0xB0, 0xB0 };
RICO_SECTION(".data") Vec lbl_804809E0[4] = {
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }
};
RICO_SECTION(".data") TriangleFan3D lbl_80480A10 = {
    lbl_804809E0, lbl_804809D0, 0, 4
};
RICO_SECTION(".data") ColorLineVertex lbl_80480A20[4] = {
    { 350.0f, 0.0f }, { 640.0f, 0.0f },
    { 640.0f, 600.0f }, { 350.0f, 600.0f }
};
BmlResource *TAdRicoRing__resource_bundle;
u32 lbl_804FE138[4];
}

// Definitions use deferred emission order, including the two native vtables.
void TAdRicoRing::fn_8001BED0(f32 value) {
    target_scale = value;
}

void TAdRicoRingCtrl::load_static_resource() {
    TAdRicoRing__resource_bundle = new BmlResource(1, &TAdRicoRingCtrl__resource_descriptor, 0, 0, NULL);
}

void TAdRicoRingCtrl::release_global_805D4A00() {
    if (TAdRicoRing__resource_bundle != NULL) {
        delete TAdRicoRing__resource_bundle;
        TAdRicoRing__resource_bundle = NULL;
    }
}

TAdRicoRing *TAdRicoRingCtrl::create(TObject *parent) {
    return new TAdRicoRing(parent);
}

TAdRicoRing::TAdRicoRing(TObject *parent) : TObject(parent) {
    m_name = TAdRicoRing__class_name;
    model = get_bml_model(TAdRicoRing__resource_bundle, 0);
    textures = TObjFish__sub_8001EDB0(TAdRicoRing__resource_bundle, 0);
    scale[3] = lbl_805D7E4C;
    scale[2] = lbl_805D7E4C;
    scale[1] = lbl_805D7E4C;
    scale[0] = lbl_805D7E4C;
    scale_step[3] = lbl_805D7E4C;
    scale_step[2] = lbl_805D7E4C;
    scale_step[1] = lbl_805D7E4C;
    scale_step[0] = lbl_805D7E4C;
    position.z = lbl_805D7E4C;
    position.y = lbl_805D7E4C;
    position.x = lbl_805D7E4C;
    angles[2] = 0;
    angles[1] = 0;
    angles[0] = 0;
    target_scale = lbl_805D7E4C;
    angular_velocity = 0x5B0;
    flags.set(4);
    switch (TKeyBoardControl__sub_8000F828()) {
    case 0: angular_acceleration = 0x12; break;
    case 1: angular_acceleration = 0x15; break;
    }
}

TAdRicoRing::~TAdRicoRing() {}

void TAdRicoRing::run_task() {
    if (test_flags_any(&flags, 1) != 0) {
        update_position();
        if (scale[0] <= lbl_805D7E54) {
            queue_destruction();
            return;
        }
    }
    if (test_flags_any(&flags, 2) != 0) {
        update_position();
        f32 limit = target_scale;
        if (limit <= scale[0]) {
            scale[0] = limit;
            scale[3] = lbl_805D7E4C;
            scale[2] = lbl_805D7E4C;
            scale[1] = lbl_805D7E4C;
            flags.clear(2);
        }
    }
    angles[1] += angular_velocity;
    if (test_flags_any(&flags, 4) != 0) {
        angular_velocity += angular_acceleration;
        if (angular_velocity >= 0xCCC) {
            flags.clear(4);
        }
    } else {
        angular_velocity -= angular_acceleration;
        if (angular_velocity <= 0x5B0) {
            flags.set(4);
        }
    }
}

void TAdRicoRing::update_position() {
    scale[0] += scale_step[0];
    scale[1] += scale_step[1];
    scale[2] = scale[1];
    scale[3] = scale[1];
}

void TAdRicoRing::set_scale4(f32 value) {
    scale[0] = value;
    scale[1] = value;
    scale[2] = value;
    scale[3] = value;
}

void TAdRicoRing::render() {
    push_matrix();
    set_current_texture_list(textures);
    post_translate_matrix(&position.x);
    rotate_matrix_zyx(NULL, angles[0], angles[1], angles[2]);
    set_chunk_render_flags(1);
    draw_chunk_object(model);
    set_chunk_render_flags(2);
    draw_chunk_object(model);
    clear_chunk_render_flags();
    pop_matrix();
}

void TAdRicoRing::start_anim(f32 farg0) {
    f32 step;

    if (test_flags_any(&flags, 2) != 0) {
        flags.clear(2);
    }
    flags.set(1);
    if (lbl_805D7E4C != farg0) {
        scale_step[0] = (lbl_805D7E54 - scale[0]) / farg0;
        step = (lbl_805D7E54 - scale[1]) / farg0;
        scale_step[1] = step;
        scale_step[2] = step;
        scale_step[3] = step;
    }
}

void TAdRicoRing::start_fade(f32 farg0) {
    f32 step;

    if (test_flags_any(&flags, 1) != 0) {
        flags.clear(1);
    }
    flags.set(2);
    if (lbl_805D7E4C != farg0) {
        scale_step[0] = (target_scale - scale[0]) / farg0;
        step = (target_scale - scale[1]) / farg0;
        scale_step[1] = step;
        scale_step[2] = step;
        scale_step[3] = step;
    }
}

TAdRicoRingCtrl::TAdRicoRingCtrl(TObject *parent) : TObject(parent) {
    m_name = TAdRicoRingCtrl__class_name;
    rings[0] = create(tl_04);
    TAdRicoRing *ring = rings[0];
    if (ring != NULL) {
        ring->fn_8001BED0(lbl_805D7E4C);
        rings[0]->set_scale4(lbl_805D7E4C);
    }
    rings[1] = create(tl_04);
    ring = rings[1];
    if (ring != NULL) {
        ring->fn_8001BED0(lbl_805D7E4C);
        rings[1]->set_scale4(lbl_805D7E4C);
    }
    fade = TAdRicoRingCtrl__data_805D7E50;
    fade_step = lbl_805D7E4C;
    Vec point = { 1.8f, 0.3f, -5.0f };
    sub_8001B424(&point);
}

TAdRicoRingCtrl::~TAdRicoRingCtrl() {
    s32 i;
    for (i = 0; i < 2; i++) {
        if (rings[i] != NULL) {
            rings[i]->queue_destruction();
        }
    }
}

#pragma push
#pragma opt_common_subs off
void TAdRicoRingCtrl::run_task() {
    f32 value;
    fade += fade_step;
    value = fade;
    if (value < lbl_805D7E4C) {
        fade = lbl_805D7E4C;
        return;
    }
    if (value > TAdRicoRingCtrl__data_805D7E50) {
        fade = TAdRicoRingCtrl__data_805D7E50;
    }
}
#pragma pop

#pragma push
#pragma opt_common_subs off
#pragma opt_dead_assignments off
void TAdRicoRingCtrl::render() {
    f32 t = fade;
    if (t >= TAdRicoRingCtrl__data_805D7E50) {
        return;
    }
    static f32 x0 = lbl_80434828[0] - lbl_805D7E58;
    static f32 x1 = lbl_805D7E58 + lbl_80434828[0];
    static f32 y0 = lbl_805D7E5C + (lbl_80434828[1] - TAdRicoRingCtrl__data_805D7E50);
    static f32 y1 = lbl_805D7E60 + (lbl_80434828[1] - TAdRicoRingCtrl__data_805D7E50);
    static f32 z0 = lbl_80434828[2];
    static f32 z1 = lbl_805D7E58 + lbl_80434828[2];
    static s8 vertices_initialized;
    if (vertices_initialized == 0) {
        f32 b = y1;
        f32 c = z0;
        f32 d = x1;
        f32 a = x0;
        f32 e = y0;
        f32 g = z1;
        Vec *v = lbl_804809E0;
        v[0].x = a;
        v[0].y = b;
        v[0].z = c;
        v[1].x = d;
        v[1].y = b;
        v[1].z = c;
        v[2].x = d;
        v[2].y = e;
        v[2].z = g;
        v[3].x = a;
        v[3].y = e;
        v[3].z = g;
        vertices_initialized = 1;
    }
    draw_tri_fan_3d(&lbl_80480A10, 4, 6);
    t = fade;
    if (t > lbl_805D7E4C) {
        ColorLineList args = rico_ring_render_params;
        u32 cnt = __cvt_fp2unsigned(lbl_805D7E64 * t);
        s32 i;
        for (i = 0; i < 4; i++) {
            lbl_804FE138[i] = cnt;
        }
        args.draw_tri_fan_2d(4, 6, lbl_805D7E68);
    }
}
#pragma pop

void TAdRicoRingCtrl::start_fade_all(f32 x) {
    s32 i;
    for (i = 0; i != 2; i++) {
        if (rings[i] != NULL) {
            rings[i]->start_fade(x);
        }
    }
    if (lbl_805D7E4C != x) {
        fade_step = lbl_805D7E54 / x;
    }
}

void TAdRicoRingCtrl::fn_8001B4A0(f32 x) {
    s32 i;
    for (i = 0; i != 2; i++) {
        if (rings[i] != NULL) {
            rings[i]->start_anim(x);
            rings[i] = NULL;
        }
    }
    f32 t = lbl_805D7E48 + x;
    if (lbl_805D7E4C != t) {
        fade_step = TAdRicoRingCtrl__data_805D7E50 / t;
    }
}

#pragma push
#pragma fp_contract on
void TAdRicoRingCtrl::sub_8001B424(const Vec *point) {
    if (point != NULL) {
        TAdRicoRing *ring = rings[0];
        if (ring != NULL) {
            VecCopy(&ring->position, point);
        }
        ring = rings[1];
        if (ring != NULL) {
            VecCopy(&ring->position, point);
            ring = rings[1];
            ring->position.y = -(lbl_805D7E48 * ((NJS_CNK_MODEL *)ring->model->model)->r - ring->position.y);
        }
    }
}
#pragma pop

extern "C" {
RICO_SECTION(".rodata") extern const f32 lbl_80434828[] = {1.8f, 0.3f, -5.0f};
RICO_SECTION(".rodata") extern const ColorLineList rico_ring_render_params = { lbl_80480A20, lbl_804FE138, 0, 4 };
RICO_SECTION(".sdata2") extern const f32 lbl_805D7E48 = 2.0f;
RICO_SECTION(".sdata2") extern const f32 lbl_805D7E4C = 0.0f;
RICO_SECTION(".sdata2") extern const f32 TAdRicoRingCtrl__data_805D7E50 = 1.0f;
RICO_SECTION(".sdata2") extern const f32 lbl_805D7E54 = -1.0f;
RICO_SECTION(".sdata2") extern const f32 lbl_805D7E58 = 50.0f;
RICO_SECTION(".sdata2") extern const f32 lbl_805D7E5C = -8.75f;
RICO_SECTION(".sdata2") extern const f32 lbl_805D7E60 = 0.025f;
RICO_SECTION(".sdata2") extern const f32 lbl_805D7E64 = 255.0f;
RICO_SECTION(".sdata2") extern const f32 lbl_805D7E68 = -2.0f;
}

#undef RICO_SECTION
