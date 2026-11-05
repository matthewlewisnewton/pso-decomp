#include "pso/misc/ParticleFactory.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/SoundEffect.h"
#include "pso/misc/PersistentSound.h"
#include "types.h"
#include "pso/render/render_util.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/enemy/SlimeAnimationState.h"
#include "pso/unk/text_803E2D70.h"
#include "pso/enemy/TObjEneSlimeOne_800EC394.h"
#include "pso/enemy/TObjEneRe4Bit.h"
#include "pso/object/TObjMotion.h"
#include "pso/enemy/TObjEneSlimeWaterBomb.h"
#include "pso/enemy/TObjEneSlimeOne.h"
#include "pso/enemy/TObjEnePanarms.h"
#include "pso/enemy/TObjEneRe7Berura.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"

struct O_800EC39C { u8 pad[0x384]; s32 state; };

extern "C" {
s32 find_nearest_hittable_enemy__10TObjPlayerFiPvf(void *, void *, f32);

extern s8 slime_one_animation_end_initialized;
extern f32 slime_one_animation_end_frame;
s32 TObjFish__sub_8001EDB0(s32, s32);
void draw_model_motion(void *arg0, void *arg1, f32 farg0);

extern s32 slime_one_part_texture_index_table[];
extern s32 model_render_flags;
s32 get_bml_motion(s32, s32);
s32 get_bml_model(s32, s32);
s32 init__14TObjEnePanarmsFs(void *, int);
extern SlimePairedMotion lbl_80496C68[2];
extern SlimePairedMotion lbl_80496C90[2];
int get_validated_attack_stage(void*);

s32 TObjEneSlimeOne::get_attack_target() { return *(s32*)((char*)this + 0x3f4); }

    extern int slime_bml_resource;

s32 TObjEneSlimeOne::is_in_water_bomb_states() {
    O_800EC39C *self = (O_800EC39C *)this;
    return self->state == 11 || self->state == 12 || self->state == 13;
}

int TObjEneSlimeOne::get_instance() {  return slime_bml_resource; }

int TObjEneSlimeWaterBomb::find_nearest_enemy_masked(f32 farg0) {
    u8 *arg0 = (u8 *)this;
    u16 temp_r3;
    this->actorFlags = (s32) (this->actorFlags | 0x02000000);
    temp_r3 = find_nearest_hittable_enemy__10TObjPlayerFiPvf(arg0, (void *)(0), farg0);
    this->actorFlags = (s32) (this->actorFlags & 0xFDFFFFFF);
    return temp_r3;
}

int TObjEneSlimeOne::is_timer_active() { return (this->actorFlags >> 4) & 0x1; }

int TObjEneSlimeOne::find_nearest_enemy_with_flag(s32 arg1, f32 farg0) {
    u8 *arg0 = (u8 *)this;
    u16 temp_r3;
    this->actorFlags = (s32) (this->actorFlags | 0x02000000);
    temp_r3 = find_nearest_hittable_enemy__10TObjPlayerFiPvf((void *)arg0, (void *)arg1, (f32)farg0);
    this->actorFlags = (s32) (this->actorFlags & 0xFDFFFFFF);
    return temp_r3;
}

void TObjEneSlimeOne__sub_800EC470(void* p) { *(s32*)((char*)p + 0x3f0) = 0; }

int TObjEneSlimeOne::check_player_field_7cc() { return get_validated_attack_stage((char*)this + 0x7cc); }

extern f32 TObjEneSlimeOne__target_depth;
extern u8 TObjEneSlimeOne__target_depth_initialized;

void SlimeAnimationState::draw(s32 deferred) {
    s32 state = this->state;
    if (state == -1) {
        return;
    }
    if (state < 7) {
        set_current_texture_list((GinjaTextureList *)(TObjFish__sub_8001EDB0(TObjEneSlimeOne::get_instance(), slime_one_part_texture_index_table[owner->get_attack_target()])));
        if (deferred != 0) {
            model_render_flags |= 0x400000;
            set_chunk_render_flags(1);
            owner->draw();
            clear_chunk_render_flags();
            model_render_flags &= ~0x400000;
            return;
        }
        set_cull_back();
        set_chunk_render_flags(2);
        owner->draw();
        set_cull_front();
        owner->draw();
        set_cull_none();
        clear_chunk_render_flags();
        return;
    }
    if (state < 9) {
        set_current_texture_list((GinjaTextureList *)(texture_list));
        if (deferred != 0) {
            model_render_flags |= 0x400000;
            set_chunk_render_flags(1);
            draw_chunk_model_with_shape_motion(model, motion, shape_motion, frame);
            clear_chunk_render_flags();
            model_render_flags &= ~0x400000;
            return;
        }
        set_chunk_render_flags(2);
        set_cull_back();
        draw_chunk_model_with_shape_motion(model, motion, shape_motion, frame);
        set_cull_front();
        draw_chunk_model_with_shape_motion(model, motion, shape_motion, frame);
        set_cull_none();
        clear_chunk_render_flags();
        return;
    }
    set_current_texture_list((GinjaTextureList *)(texture_list));
    set_motion_packed_rotation();
    if (deferred != 0) {
        model_render_flags |= 0x400000;
        set_chunk_render_flags(1);
        draw_model_motion(model, motion, frame);
        set_current_texture_list((GinjaTextureList *)(second_texture_list));
        draw_model_motion(second_model, second_motion, frame);
        clear_chunk_render_flags();
        model_render_flags &= ~0x400000;
    } else {
        set_chunk_render_flags(2);
        set_cull_back();
        draw_model_motion(model, motion, frame);
        set_cull_front();
        draw_model_motion(model, motion, frame);
        set_current_texture_list((GinjaTextureList *)(second_texture_list));
        set_cull_back();
        draw_model_motion(second_model, second_motion, frame);
        set_cull_front();
        draw_model_motion(second_model, second_motion, frame);
        set_cull_none();
        clear_chunk_render_flags();
    }
    clear_motion_packed_rotation();
}

void SlimeAnimationState::advance() {
    s32 s = state;
    if (s == -1) {
        return;
    }
    if (s < 7) {
        owner->advance_animation();
    } else if (s < 9) {
        f32 v = frame + speed;
        frame = v;
        if (v >= frame_count) {
            frame = frame - frame_count;
        }
    } else {
        if (slime_one_animation_end_initialized == 0) {
            f32 tmp = frame_count;
            slime_one_animation_end_initialized = 1;
            slime_one_animation_end_frame = tmp - 1.0f;
        }
        f32 v = frame + speed;
        f32 lim = slime_one_animation_end_frame;
        frame = v;
        if (v >= lim) {
            frame = lim;
        }
    }
}

s32 SlimeAnimationState::is_finished() {
    s32 temp_r0;

    temp_r0 = this->state;
    if (temp_r0 == -1) {
        return 1;
    }
    if (temp_r0 < 7) {
        return 0;
    }
    if ((s8) TObjEneSlimeOne__target_depth_initialized == 0) {
        f32 tmp = frame_count;
        TObjEneSlimeOne__target_depth_initialized = 1;
        TObjEneSlimeOne__target_depth = tmp - 1.0f;
    }
    if (frame == TObjEneSlimeOne__target_depth) {
        return 1;
    }
    return 0;
}

SlimeShapeMotion slime_one_motion_state_table[2] = {
    {11, 12, 0.7f}, {6, 7, 0.8f}
};
SlimePairedMotion lbl_80496C68[2] = {
    {4, 5, 0, 1, 0.6f}, {4, 0, 0, 4, 0.6f}
};
SlimePairedMotion lbl_80496C90[2] = {
    {5, 5, 2, 1, 0.6f}, {5, 0, 2, 4, 0.6f}
};
__declspec(section ".data") SlimePairedMotion *lbl_80496CB8[2] = {lbl_80496C68, lbl_80496C90};
__declspec(section ".data") s32 slime_one_attack_target_id_table[2] = {4, 5};
__declspec(section ".data") s32 slime_one_part_texture_index_table[2] = {0, 2};
f32 TObjEneSlimeOne__target_depth;
u8 TObjEneSlimeOne__target_depth_initialized;
f32 slime_one_animation_end_frame;
s8 slime_one_animation_end_initialized;

void SlimeAnimationState::set_state(s32 next_state) {
    s32 flag = state & 0x1000;
    state = next_state & ~0x1000;
    if (state == -1) {
        return;
    }
    if (state < 7) {
        if (flag != 0) {
            ((void (*)(void *, s16)) init__14TObjEnePanarmsFs)(owner, state);
        } else {
            owner->set_field_b8(state);
        }
        return;
    }
    if (state < 9) {
        s32 resource = TObjEneSlimeOne::get_instance();
        SlimeShapeMotion *entry = slime_one_motion_state_table + state - 7;
        u32 id = slime_one_attack_target_id_table[owner->get_attack_target()];
        model = (NJS_OBJECT *)get_bml_model(resource, id);
        texture_list = TObjFish__sub_8001EDB0(resource, id);
        motion = (AnimationMotion *)get_bml_motion(resource, entry->motion);
        shape_motion = (AnimationMotion *)get_bml_motion(resource, entry->shape_motion);
        frame_count = motion->frameCount;
        speed = entry->speed;
        frame = 0.0f;
        return;
    }
    s32 index = state - 9;
    s32 resource = TObjEneSlimeOne::get_instance();
    SlimePairedMotion *entry = &lbl_80496CB8[owner->get_attack_target()][index];
    model = (NJS_OBJECT *)get_bml_model(resource, entry->model);
    texture_list = TObjFish__sub_8001EDB0(resource, entry->model);
    motion = (AnimationMotion *)get_bml_motion(resource, entry->motion);
    second_model = (NJS_OBJECT *)get_bml_model(resource, entry->second_model);
    second_texture_list = TObjFish__sub_8001EDB0(resource, entry->second_model);
    second_motion = (AnimationMotion *)get_bml_motion(resource, entry->second_motion);
    frame_count = second_motion->frameCount;
    speed = entry->speed;
    frame = 0.0f;
}

SlimeAnimationState::~SlimeAnimationState() {}

SlimeAnimationState::SlimeAnimationState(TObjEneSlimeOne *owner)
    : owner(owner), state(-1) {}

void TObjEneRe4Bit::vfunc_106() {  }
s32 TObjEneRe4Bit::vfunc_83() {  }

}
