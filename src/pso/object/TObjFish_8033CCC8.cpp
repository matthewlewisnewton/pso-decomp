#include "pso/system/ModelNodePositionCapture.h"
#include "pso/system/BmlResource.h"
#include "pso/misc/CameraHelpers.h"
#include "pso/object/TObjFish_8001ED90.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/SoundEffect.h"
#include "pso/misc/PersistentSound.h"
#include "types.h"
#include "pso/system/PadRumble.h"
#include "pso/misc/TOTrapAncient01_80226534.h"
#include "pso/boss/TBoss4Type2_800874F4.h"
#include "pso/misc/TCameraCtrl_800687BC.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/unk/text_80087278.h"
#include "pso/system/MatrixStack.h"
#include "pso/object/TBoss6Demo11_TYPE1_DEAD.h"
#include "pso/boss/TBoss6PlotFalz.h"
#include "pso/object/TObjFish.h"
#include "pso/boss/TBoss3Volopt.h"
#include "pso/boss/TBoss4Type2.h"
#include "pso/misc/TNowLoading.h"
#include "pso/player/TObjPlayer.h"
#include "pso/TParticleCtrl.h"

struct ParticleWindow {
    s32 first_frame;
    s32 end_frame;
    s32 node;
};

struct DeathClassTag {
    const char *name;
    u32 padding;
};

extern "C" {
extern s32 lbl_804DF614[];

extern const char lbl_80477E48[];
extern const ParticleWindow fish_spawn_entry_table[];

#ifdef __MWERKS__
// Keep direct relocations for the capture and camera tables.
__declspec(weak) extern ModelNodePositionEntry lbl_80477E60[];
__declspec(weak) extern const CameraAngles lbl_80477EC0;
__declspec(weak) extern const CameraPlayback lbl_80477ECC;
#else
extern ModelNodePositionEntry lbl_80477E60[];
extern const CameraAngles lbl_80477EC0;
extern const CameraPlayback lbl_80477ECC;
#endif

__declspec(section ".rodata") const char lbl_80477E48[] ATTRIBUTE_ALIGN(4) = "TBoss6Demo11_TYPE1_DEAD";
__declspec(section ".rodata") ModelNodePositionEntry lbl_80477E60[] = {
    {0, {0.0f, 0.0f, 0.0f}},
    {4, {0.0f, 0.0f, 0.0f}},
    {6, {0.0f, 0.0f, 0.0f}},
    {25, {0.0f, 0.0f, 0.0f}},
    {49, {0.0f, 0.0f, 0.0f}},
    {-1, {0.0f, 0.0f, 0.0f}},
};
__declspec(section ".rodata") const CameraAngles lbl_80477EC0 = {0, 0, 0};
__declspec(section ".rodata") const CameraPlayback lbl_80477ECC = {1, 0, 0, 0.0f, 0.7f};
__declspec(section ".rodata") const ParticleWindow fish_spawn_entry_table[] = {
    {7, 42, 4}, {71, 128, 3}, {107, 137, 1}, {142, 185, 2},
};
__declspec(section ".data") static s32 death_motion_indices[] = {4, 5};
__declspec(section ".data") static Vec death_origin = {0.0f, 0.0f, 70.0f};
__declspec(section ".sdata") DeathClassTag lbl_805D42A0 = {lbl_80477E48, 0};
}

// CodeWarrior's deferred generation emits these definitions in reverse order.
void *TBoss6PlotFalz::create(void *parent, void *target) {
    return new TBoss6Demo11_TYPE1_DEAD(static_cast<TBoss6PlotFalz *>(parent), static_cast<const Vec *>(target));
}

TBoss6Demo11_TYPE1_DEAD::TBoss6Demo11_TYPE1_DEAD(TBoss6PlotFalz *parent, const Vec *)
    : TObject(parent) {
    m_name = lbl_805D42A0.name;
    plot = parent;
    VecCopy(&origin, &death_origin);

    // The legacy accessor returns the loaded BML archive as a 32-bit value.
    BmlResource *resource = reinterpret_cast<BmlResource *>(TObjFish::get_fish_count());
    for (s32 i = 0; i < 2; i++) {
        const s32 index = lbl_804DF614[i];
        models[i].object = get_bml_model(resource, index);
        models[i].textures = TObjFish__sub_8001EDB0(resource, index);
        models[i].motion = get_bml_motion(resource, death_motion_indices[i]);
    }
    capture = ModelNodePositionCapture::create(lbl_80477E60, captured_positions);
    emitter = NULL;
    activate_camera_mode(5);
    set_scripted_camera_pose(&origin, &origin, &lbl_80477EC0);
    cache_target_and_forward__11TCameraCtrlFl(&lbl_80477ECC, 0x416C);
    frame = 0.0f;
    elapsed = 0;
}

TBoss6Demo11_TYPE1_DEAD::~TBoss6Demo11_TYPE1_DEAD() {
    restore_player_cameras();
    if (capture != NULL) {
        ModelNodePositionCapture::destroy(capture);
        capture = NULL;
    }
    if (emitter != NULL) {
        TParticleCtrl::release(emitter);
        emitter = NULL;
    }
}

void TBoss6Demo11_TYPE1_DEAD::run_task() {
    s32 found;
    s32 i;
    Vec *p;
    Vec *q;
    const ParticleWindow *t;
    if ((frame += 0.7f) > 179.0f) {
        frame = 179.0f;
    }
    switch (elapsed) {
    case 0x98:
        play_sound_effect(0x40032104, 0, 0, 0);
        break;
    case 0xF9:
        play_sound_effect(0x40032B25, 0, 0, 0);
        break;
    case 0x1E:
        play_sound_effect(0x4003A811, 0, 0, 0);
        break;
    case 0x3C:
    case 0x5A:
    case 0x14:
    case 0xA:
        play_sound_effect(0x40032E23, 0, 0, 0);
        break;
    }
    if (elapsed >= 0x89) {
        play_persistent_sound(0x4003A424, this, NULL, 0, 0);
    }
    switch (elapsed) {
    case 0xE:
        q = &captured_positions[4];
        spawn_particle_effect_with_flags(q, 0x21C, 0x40);
        spawn_particle_effect_with_flags(q, 0x21D, 0x40);
        break;
    case 0x4E:
        q = &captured_positions[3];
        spawn_particle_effect_with_flags(q, 0x21C, 0x40);
        spawn_particle_effect_with_flags(q, 0x21D, 0x40);
        break;
    }
    if (elapsed >= 0xB9 && !(elapsed & 3)) {
        q = &captured_positions[0];
        spawn_particle_effect_with_flags(q, 0x13C, 0x40);
        spawn_particle_effect_with_flags(q, 0x13D, 0x40);
    }
    found = 0;
    for (i = 0; i < 4; i++) {
        t = &fish_spawn_entry_table[i];
        if (elapsed >= t->first_frame && elapsed < t->end_frame) {
            p = &captured_positions[t->node];
            if (emitter == NULL) {
                emitter = create_particle_emitter(p, 0x21F);
                if (emitter != NULL) {
                    emitter->set_flags(0x40);
                }
            } else {
                emitter->set_position(p);
            }
            found = 1;
            break;
        }
    }
    if (found == 0 && emitter != NULL) {
        TParticleCtrl::release(emitter);
        emitter = NULL;
    }
    switch (elapsed) {
    case 5:
    case 0x19:
    case 0x46:
    case 0x5F:
    case 0x6E:
    case 0x8C:
    case 0xBE:
    case 0xFF:
        start_pad_rumble_all(0xC0, 0xF);
        break;
    }
    elapsed++;
    if (elapsed >= 0x101 || ((TObjFish *)plot)->get_phase() != 3) {
        queue_destruction__7TObjectFv(this);
    }
}

void TBoss6Demo11_TYPE1_DEAD::render() {
    render_fade_model();
}

void TBoss6Demo11_TYPE1_DEAD::render_fade_model() {
    f32 alpha;
    const s32 tick = elapsed;
    if (tick < 0xBF) {
        alpha = 1.0f;
    } else if (tick >= 0xCC) {
        alpha = 0.0f;
    } else {
        alpha = (f32) (0xCC - tick) / 13.0f;
    }
    if (0.0f != alpha) {
        if (alpha < 1.0f) {
            TBoss6PlotFalz::set_fade_material_color(alpha);
        }
        push_matrix();
        set_motion_packed_rotation();
        post_translate_matrix(&origin.x);
        set_current_texture_list(reinterpret_cast<GinjaTextureList *>(models[0].textures));
        draw_model_motion(reinterpret_cast<void *>(models[0].object), models[0].motion, frame);
        set_current_texture_list(reinterpret_cast<GinjaTextureList *>(models[1].textures));
        capture->install();
        draw_model_motion(reinterpret_cast<void *>(models[1].object), models[1].motion, frame);
        capture->clear();
        clear_motion_packed_rotation();
        pop_matrix();
        if (alpha < 1.0f) {
            TObjFish::reset_fish_globals();
        }
    }
}
