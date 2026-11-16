#include "pso/system/BmlTextureList.h"
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/object/TObjDFDemo4.h"
#include "pso/TParticleCtrl.h"
#include "pso/boss/TBoss4Uro.h"
#include "pso/boss/TBoss4Type2_800874F4.h"
#include "pso/misc/CameraHelpers.h"
#include "pso/misc/ParticleFactory.h"
#include "pso/misc/TCameraCtrl_800687BC.h"
#include "pso/object/TObjFish_8001ED90.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_80052374.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/system/BmlResource.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/ModelNodePositionCapture.h"
#include "pso/system/PadRumble.h"
#include "pso/system/SoundEffect.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/unk/text_803D8F74.h"

struct Demo4StripNode {
    s32 model;
    s32 node;
    s32 texture_filter;
};

extern "C" {
extern s32 boss4_zanzo_bml_index_table[2];
extern s32 lbl_80486FB0[3];
void init_model_node_tables(void *strips, const Demo4StripNode *nodes, s32 count);
void fn_8004AA04(void *strips);
// The same strip state is used by the boss and the demo.
void scroll_strips__11TBoss4Type2Fv(void *strips);
s32 push_matrix();
void post_translate_matrix(const Vec *position);
}

// Deferred generation emits these functions in reverse definition order
// and places the camera initializers ahead of the conversion constant.
#pragma readonly_strings on
#pragma defer_codegen on

static const char *dfdemo4_name = "TObjDFDemo4";
static s32 afterimage_motion_indices[2] = {0x12, 0x11};
static s32 body_motion_indices[3] = {0x20, 0x21, 0x22};
static ModelNodePositionEntry emitter_nodes[3] = {{0x34}, {0x35}, {-1}};

// CodeWarrior addresses this table directly when it is weak. The constructor
// still shares one .data base for the motion tables and the vtable.
#ifdef __MWERKS__
__declspec(weak)
#endif
extern const Demo4StripNode dfdemo4_strip_nodes[2] = {{0xC, 0x4A, 1}, {0xE, 0x4A, 1}};

namespace {
// Volatile preserves the separate alpha loads in draw_afterimages.
extern const volatile f32 afterimage_max_alpha;
extern const f32 afterimage_fade_rate;
extern const f32 afterimage_frame;
extern const f32 body_frame_step;
extern const f32 body_last_frame;
extern const f32 body_first_frame;
}

TObjDFDemo4 *TObjDFDemo4::create(TObject *parent, const Vec *position, s32 angle) {
    return new TObjDFDemo4(parent, position, angle);
}

TObjDFDemo4::TObjDFDemo4(TObject *parent, const Vec *position, s32 angle) : TObjBase(parent) {
    m_name = dfdemo4_name;
    VecCopy(&camera_position, position);
    this->angle = angle;
    BmlResource *resource = (BmlResource *)TBoss4Uro::get_instance_count();
    for (s32 i = 0; i < 2; i++) {
        const s32 model = boss4_zanzo_bml_index_table[i];
        afterimages[i].model = get_bml_model(resource, model);
        afterimages[i].texlist = (s32)TObjFish__sub_8001EDB0((BmlResource *)resource, (s32)model);
        afterimages[i].motion = get_bml_motion(resource, afterimage_motion_indices[i]);
    }
    for (s32 i = 0; i < 3; i++) {
        const s32 model = lbl_80486FB0[i];
        body_parts[i].model = get_bml_model(resource, model);
        body_parts[i].texlist = (s32)TObjFish__sub_8001EDB0((BmlResource *)resource, (s32)model);
        body_parts[i].motion = get_bml_motion(resource, body_motion_indices[i]);
    }
    frame = body_first_frame;
    init_model_node_tables(strips, dfdemo4_strip_nodes, 2);
    for (s32 i = 0; i < 2; i++) {
        particle_emitters[i] = NULL;
    }
    activate_camera_mode(5);
    CameraPlayback playback = {0, 3, 0, 0.0f, 0.5f};
    CameraAngles angles = {0, this->angle, 0};
    set_scripted_camera_pose(&camera_position, &camera_position, &angles);
    cache_target_and_forward__11TCameraCtrlFl(&playback, 0x416C);
    node_capture = ModelNodePositionCapture::create(emitter_nodes, emitter_positions);
    timer = 0;
}

TObjDFDemo4::~TObjDFDemo4() {
    fn_8004AA04(strips);
    if (node_capture != NULL) {
        ModelNodePositionCapture::destroy(node_capture);
        node_capture = NULL;
    }
    for (s32 i = 0; i < 2; i++) {
        if (particle_emitters[i] != NULL) {
            TParticleCtrl::release(particle_emitters[i]);
            particle_emitters[i] = NULL;
        }
    }
    restore_player_cameras();
}

void TObjDFDemo4::run_task() {
    TParticleCtrl *effect;
    if (timer <= 0x3C && (effect = spawn_particle_effect(&camera_position, 0x14E)) != NULL) {
        effect->set_flags(0x40);
    }
    if (timer == 0x44) {
        effect = spawn_particle_effect(&camera_position, 0x17B);
        if (effect != NULL) {
            effect->set_flags(0x40);
        }
        effect = spawn_particle_effect(&camera_position, 0x17C);
        if (effect != NULL) {
            effect->set_flags(0x40);
        }
    }
    if (timer == 0x48) {
        effect = spawn_particle_effect(&camera_position, 0x17A);
        if (effect != NULL) {
            effect->set_flags(0x40);
        }
        play_sound_effect(0x40039E09, &camera_position, 0, 1);
        start_pad_rumble_all(0xC0, 0xF);
    }
    if (timer == 0x72) {
        play_sound_effect(0x4003B227, &camera_position, 0, 1);
    }
    if (timer >= 0xAA) {
        TParticleCtrl **emitter = &particle_emitters[0];
        for (s32 i = 0; i < 2; i++) {
            Vec *position = &emitter_positions[i];
            if (*emitter == NULL) {
                *emitter = create_particle_emitter(position, 0x147);
                if (*emitter != NULL) {
                    (*emitter)->set_flags(0x40);
                }
            } else {
                (*emitter)->set_position(position);
            }
            emitter = &particle_emitters[1];
        }
    }
    if (timer == 0x72) {
        Vec position = {10000.0f, -10.0f, 0.0f};
        CameraAngles angles = {0, 0, 0};
        VecCopy(&camera_position, &position);
        angle = 0;
        set_scripted_camera_pose(&camera_position, &camera_position, &angles);
    }
    f32 next_frame = frame + body_frame_step;
    frame = next_frame;
    // Bind the limit at the comparison to preserve CodeWarrior's register order.
    const f32 *last_frame;
    if (next_frame > *(last_frame = &body_last_frame)) {
        frame = *last_frame;
    }
    scroll_strips__11TBoss4Type2Fv(strips);
    if (++timer >= 0xF0) {
        queue_destruction();
    }
}

void TObjDFDemo4::render() {
    draw_afterimages();
    draw_body();
}

void TObjDFDemo4::draw_afterimages() {
    f32 alpha = afterimage_max_alpha;
    if (timer > 0x4C) {
        return;
    }
    if (timer > 0x44) {
        alpha = (f32)(0x4C - timer) * afterimage_fade_rate;
    }
    if (alpha < afterimage_max_alpha) {
        TObjPlayer__sub_80052390(alpha);
    }
    push_matrix();
    set_motion_packed_rotation();
    post_translate_matrix(&camera_position);
    rotate_matrix_y(0, angle);
    for (s32 i = 0; i < 2; i++) {
        set_current_texture_list((GinjaTextureList *)afterimages[i].texlist);
        draw_model_motion(afterimages[i].model, afterimages[i].motion, afterimage_frame);
    }
    clear_motion_packed_rotation();
    pop_matrix();
    if (alpha < afterimage_max_alpha) {
        TObjPlayer::sync_player_globals();
    }
}

void TObjDFDemo4::draw_body() {
    if (timer >= 0x44) {
        push_matrix();
        set_motion_packed_rotation();
        post_translate_matrix(&camera_position);
        rotate_matrix_y(0, angle);
        s32 i = 0;
        do {
            set_current_texture_list((GinjaTextureList *)body_parts[i].texlist);
            if (i == 0) {
                node_capture->install();
            }
            draw_model_motion(body_parts[i].model, body_parts[i].motion, frame);
            if (i == 0) {
                node_capture->clear();
            }
            i++;
        } while (i < 3);
        clear_motion_packed_rotation();
        pop_matrix();
    }
}

// Keep these definitions after their users so CodeWarrior emits separate loads.
namespace {
const volatile f32 afterimage_max_alpha = 1.0f;
const f32 afterimage_fade_rate = 0.125f;
const f32 afterimage_frame = 120.0f;
const f32 body_frame_step = 0.5f;
const f32 body_last_frame = 119.0f;
const f32 body_first_frame = -0.5f;
}
