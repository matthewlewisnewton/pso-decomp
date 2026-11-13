#include "types.h"
#include "pso/render/render_util.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/unk/text_803E2D70.h"
#include "pso/enemy/slime/TObjEneSlimeOne_800EC394.h"
#include "pso/quest/TQuestListVM_8007EAF8.h"
#include "pso/enemy/sorcerer/TObjEneRe4Bit.h"
#include "pso/object/base/TObjMotion.h"
#include "pso/enemy/slime/TObjEneSlimeWaterBomb.h"
#include "pso/enemy/slime/TObjEneSlimeOne.h"
#include "pso/enemy/slime/SlimeAnimationState.h"
#include "pso/enemy/panarms/TObjEnePanarms.h"
#include "pso/enemy/berura/TObjEneRe7Berura.h"
#include "pso/object/ambient/TObjFish.h"
#include "pso/player/TObjPlayer.h"

struct O_800EC39C { u8 pad[0x384]; s32 state; };

struct E12_800EC7F4
{
  s32 a;
  s32 b;
  f32 c;
};

struct E20_800EC7F4
{
  s32 a;
  s32 b;
  s32 c;
  s32 d;
  f32 e;
};

struct Tbl_800EC7F4
{
  E12_800EC7F4 e[2];
  u8 pad18[0x68 - 0x18];
  E20_800EC7F4 *ptrs[2];
  s32 ids[2];
};

extern "C" {
s32 find_nearest_hittable_enemy__10TObjPlayerFiPvf(void *, void *, f32);
extern s8 slime_one_animation_end_initialized;
extern f32 slime_one_animation_end_frame;
s32 TObjFish__sub_8001EDB0(s32, s32);
void draw_model_motion(void *arg0, void *arg1, f32 farg0);
void draw_chunk_model_with_shape_motion(void *child, void *arg1, void *arg2, f32 farg0);
extern s32 slime_one_part_texture_index_table[];
extern s32 model_render_flags;
s32 get_bml_motion(s32, s32);
s32 get_bml_model(s32, s32);
s32 init__14TObjEnePanarmsFs(void *, int);
extern void *lbl_80496C68[10];
extern void *lbl_80496C90[10];
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

void SlimeAnimationState::draw(s32 arg1) {
    s32 state = this->state;
    if (state == -1) {
        return;
    }
    if (state < 7) {
        set_current_texture_list((GinjaTextureList *)(TObjFish__sub_8001EDB0(TObjEneSlimeOne::get_instance(), slime_one_part_texture_index_table[owner->get_attack_target()])));
        if (arg1 != 0) {
            model_render_flags |= 0x400000;
            set_chunk_render_flags(1);
            ((TObjMotion *)owner)->draw();
            clear_chunk_render_flags();
            model_render_flags &= ~0x400000;
            return;
        }
        set_cull_back();
        set_chunk_render_flags(2);
        ((TObjMotion *)owner)->draw();
        set_cull_front();
        ((TObjMotion *)owner)->draw();
        set_cull_none();
        clear_chunk_render_flags();
        return;
    }
    if (state < 9) {
        set_current_texture_list((GinjaTextureList *)(texture_list));
        if (arg1 != 0) {
            model_render_flags |= 0x400000;
            set_chunk_render_flags(1);
            draw_chunk_model_with_shape_motion((void *)(model), (void *)((s32)motion), (void *)(shape_motion), frame);
            clear_chunk_render_flags();
            model_render_flags &= ~0x400000;
            return;
        }
        set_chunk_render_flags(2);
        set_cull_back();
        draw_chunk_model_with_shape_motion((void *)(model), (void *)((s32)motion), (void *)(shape_motion), frame);
        set_cull_front();
        draw_chunk_model_with_shape_motion((void *)(model), (void *)((s32)motion), (void *)(shape_motion), frame);
        set_cull_none();
        clear_chunk_render_flags();
        return;
    }
    set_current_texture_list((GinjaTextureList *)(texture_list));
    set_motion_packed_rotation();
    if (arg1 != 0) {
        model_render_flags |= 0x400000;
        set_chunk_render_flags(1);
        draw_model_motion((void *)(model), (void *)((s32)motion), frame);
        set_current_texture_list((GinjaTextureList *)(second_texture_list));
        draw_model_motion((void *)(second_model), (void *)((s32)second_motion), frame);
        clear_chunk_render_flags();
        model_render_flags &= ~0x400000;
    } else {
        set_chunk_render_flags(2);
        set_cull_back();
        draw_model_motion((void *)(model), (void *)((s32)motion), frame);
        set_cull_front();
        draw_model_motion((void *)(model), (void *)((s32)motion), frame);
        set_current_texture_list((GinjaTextureList *)(second_texture_list));
        set_cull_back();
        draw_model_motion((void *)(second_model), (void *)((s32)second_motion), frame);
        set_cull_front();
        draw_model_motion((void *)(second_model), (void *)((s32)second_motion), frame);
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
        ((TObjMotion *)owner)->advance_animation();
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

typedef struct E12_800EC7F4 E12_800EC7F4;
typedef struct E20_800EC7F4 E20_800EC7F4;
typedef struct Tbl_800EC7F4 Tbl_800EC7F4;
void *slime_one_motion_state_table[6] = {(void *) 0xb, (void *) 0xc, (void *) 0x3f333333, (void *) 0x6, (void *) 0x7, (void *) 0x3f4ccccd};
void *lbl_80496C68[10] = {(void *) 0x4, (void *) 0x5, (void *) 0x0, (void *) 0x1, (void *) 0x3f19999a, (void *) 0x4, (void *) 0x0, (void *) 0x0, (void *) 0x4, (void *) 0x3f19999a};
void *lbl_80496C90[10] = {(void *) 0x5, (void *) 0x5, (void *) 0x2, (void *) 0x1, (void *) 0x3f19999a, (void *) 0x5, (void *) 0x0, (void *) 0x2, (void *) 0x4, (void *) 0x3f19999a};
__declspec(section ".data") void *lbl_80496CB8[2] = {
    (void *)&lbl_80496C68, (void *)&lbl_80496C90,
};
__declspec(section ".data") void *slime_one_attack_target_id_table[2] = {
    (void *)0x4, (void *)0x5,
};
__declspec(section ".data") s32 slime_one_part_texture_index_table[2] = { 0, 2 };

f32 TObjEneSlimeOne__target_depth;
u8 TObjEneSlimeOne__target_depth_initialized;
f32 slime_one_animation_end_frame;
s8 slime_one_animation_end_initialized;
void SlimeAnimationState::set_state(s32 arg1) {
    SlimeAnimationState *arg0 = this;
  s32 flag;
  flag = arg0->state & 0x1000;
  arg0->state = arg1 & (~0x1000);
  if (arg0->state == (-1))
  {
    return;
  }
  if (arg0->state < 7)
  {
    if (flag != 0)
    {
      ((void (*)(void *, s16)) init__14TObjEnePanarmsFs)(arg0->owner, arg0->state);
    }
    else
    {
      ((TObjMotion *)(arg0->owner))->set_field_b8(arg0->state);
    }
    return;
  }
  if (arg0->state < 9)
  {
    s32 inst = TObjEneSlimeOne::get_instance();
    E12_800EC7F4 *e = (((E12_800EC7F4 *) slime_one_motion_state_table) + arg0->state) - 7;
    unsigned int id = (s32) slime_one_attack_target_id_table[arg0->owner->get_attack_target()];
    arg0->model = get_bml_model(inst, id);
    arg0->texture_list = TObjFish__sub_8001EDB0(inst, id);
    arg0->motion = (SlimeMotionInfo *) get_bml_motion(inst, e->a);
    arg0->shape_motion = get_bml_motion(inst, e->b);
    arg0->frame_count = arg0->motion->frame_count;
    arg0->speed = e->c;
    arg0->frame = 0.0f;
    return;
  }
  {
    s32 st = arg0->state - 9;
    s32 inst = TObjEneSlimeOne::get_instance();
    E20_800EC7F4 *f = &((E20_800EC7F4 **) lbl_80496CB8)[arg0->owner->get_attack_target()][st];
    arg0->model = get_bml_model(inst, f->a);
    arg0->texture_list = TObjFish__sub_8001EDB0(inst, f->a);
    arg0->motion = (SlimeMotionInfo *) get_bml_motion(inst, f->b);
    arg0->second_model = get_bml_model(inst, f->c);
    arg0->second_texture_list = TObjFish__sub_8001EDB0(inst, f->c);
    arg0->second_motion = (SlimeMotionInfo *) get_bml_motion(inst, f->d);
    arg0->frame_count = arg0->second_motion->frame_count;
    arg0->speed = f->e;
    arg0->frame = 0.0f;
  }
}

s32 __dt__19SlimeAnimationStateFv(s32 arg0, s16 arg1) {
    if ((arg0 != 0) && (arg1 > 0)) {
        __dl__FPv();
    }
    return arg0;
}
void *__ct__19SlimeAnimationStateFP15TObjEneSlimeOne(void *arg0, s32 arg1) {
    *(s32 *)((s8 *)arg0 + 0) = arg1;
    *(s32 *)((s8 *)arg0 + 4) = -1;
    return arg0;
}

void TObjEneRe4Bit::vfunc_106() {  }
void TObjEneRe4Bit::vfunc_105() {  }

}
