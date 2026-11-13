#include "pso/effect/TEffClitical.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/ParticleFactory.h"
#include "pso/render/render_util.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/ChunkMaterialState.h"
#include "pso/system/MatrixStack.h"
#include "pso/system/MatrixOps.h"
#include "pso/system/vector.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/unk/text_803E2D70.h"
#include "pso/unk/text_80087278.h"
#include "pso/object/TObject_80019A50.h"

extern "C" {
#ifdef __MWERKS__
__declspec(section ".data")
#endif
extern GinjaTextureList lbl_8048E2E0;
extern s32 technique_ringwave_texture_list[];
extern u8 *camera_ctrl_instance;
extern s32 saved_model_render_flags;
extern s32 model_render_flags;
f32 vector_length(const Vec *);
extern const f32 TEffClitical__alpha_approach_step;
extern const char *TEffClitical__class_name;
#ifdef __MWERKS__
__declspec(section ".sdata2")
#endif
extern const f32 lbl_805D93B0[2];
}

extern "C" {
GinjaTextureEntry lbl_80500610;
#ifdef __MWERKS__
__declspec(section ".data")
#endif
GinjaTextureList lbl_8048E2E0 = {&lbl_80500610, 1};
extern const char TEffClitical__name[] = "TEffClitical";
}

void TEffClitical::render() {
    TextureFrameSlot slot;
    set_depth_buffer_settings_1();
    init_texture_copy_rect(&slot, (s32)&lbl_8048E2E0, (s32)technique_ringwave_texture_list, 0, texture_frame + 1);
    saved_model_render_flags = model_render_flags;
    model_render_flags |= 0x10;
    TParticleCtrl::begin_effect_render();
    set_constant_material(&color);
    copy_anim_frame_to_slot(&slot);
    push_matrix();
    set_current_texture_list(&lbl_8048E2E0);
    post_translate_matrix(&position.x);
    rotate_matrix_y(NULL, *(s32 *)(camera_ctrl_instance + 0x194));
    scale_matrix(NULL, scale.x, scale.y, scale.z);
    draw_chunk_object((void *)*(s32 *)effect_rel);
    pop_matrix();
    copy_slot_to_anim_frame(&slot);
    model_render_flags = saved_model_render_flags;
    TParticleCtrl::end_effect_render();
    restore_saved_depth_alpha_state();
}

void TEffClitical::run_task() {
    NJS_ARGB target_color = {0.0f, 1.0f, 1.0f, 1.0f};
    Vec target_scale = {2.0f, 2.0f, 2.0f};
    Vec particle_position;
    switch (spawn_state) {
    case 1:
        break;
    case 0:
        for (s32 i = 0; i < 4; ++i) {
            switch (i) {
            case 0:
                spawn_particle_effect(&position, 7);
                break;
            case 1:
                spawn_particle_effect(&position, 0xB);
                break;
            case 2:
                particle_position.x = position.x;
                particle_position.y = position.y - 20.0f;
                particle_position.z = position.z;
                spawn_particle_effect(&particle_position, 0xC);
                break;
            case 3:
                spawn_particle_effect(&position, 0xE);
                break;
            }
        }
        spawn_state = 1;
        break;
    }
    if (approach_alpha_clamped(&color.a, &target_color.a, TEffClitical__alpha_approach_step)) {
        queue_destruction__7TObjectFv(this);
        return;
    }
    approach_vector_in_place(&scale, &target_scale, 0.2f);
    ++texture_frame;
    if (texture_frame >= 7) {
        texture_frame = 0;
    }
}

TEffClitical::~TEffClitical() {}

TEffClitical::TEffClitical(const Vec *pos) : TEffect() {
    m_name = TEffClitical__class_name;
    VecCopy(&position, pos);
    texture_frame = 0;
    color.a = lbl_805D93B0[0];
    color.r = lbl_805D93B0[0];
    color.g = lbl_805D93B0[0];
    color.b = lbl_805D93B0[0];
    scale.x = lbl_805D93B0[0];
    scale.y = lbl_805D93B0[0];
    scale.z = lbl_805D93B0[0];
    spawn_state = 0;
}

void TEffClitical::create(const Vec *position) {
    new TEffClitical(position);
}

extern "C" void init_texture_copy_rect(void *storage, s32 texlist, s32 frames, s32 index, s32 frame) {
    TextureFrameSlot *slot = (TextureFrameSlot *)storage;
    slot->frames = (GinjaTextureList *)frames;
    slot->texlist = (GinjaTextureList *)texlist;
    slot->frame = frame;
    slot->slot = index;
}

extern "C" void approach_position_if_far(u8 *current, u8 *target, f32 step) {
    Vec delta;
    delta.x = ((Vec *)current)->x - ((Vec *)target)->x;
    delta.y = ((Vec *)current)->y - ((Vec *)target)->y;
    delta.z = ((Vec *)current)->z - ((Vec *)target)->z;
    f32 distance = vector_length(&delta);
    if (distance > step) {
        approach_vector_fixed_distance((Vec *)current, (Vec *)target, (Vec *)current, distance * step);
    }
}

extern "C" {
const f32 TEffClitical__alpha_approach_step = 0.15f;
const char *TEffClitical__class_name = TEffClitical__name;
// Keep the original eight-byte scalar object, including its zero tail.
#ifdef __MWERKS__
__declspec(section ".sdata2")
#endif
const f32 lbl_805D93B0[2] = {1.0f, 0.0f};
}
