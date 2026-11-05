#include "pso/misc/ParticleFactory.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/SoundEffect.h"
#include "pso/misc/PersistentSound.h"
#include "pso/npc/NpcAnimationBinding.h"
#include "pso/npc/NpcModelRegistry.h"
#include "pso/player/demo_mode.h"
#include "pso/enemy/BattleParameters.h"
#include "pso/unk/text_80086B64.h"
#include "pso/system/ModelNodePositionCapture.h"
#include "pso/misc/GroundEffects.h"
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "types.h"
#include "pso/TObjControl.h"
#include "pso/misc/TLobby.h"
#include "pso/system/BmlResource.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/TParticleCtrl.h"
#include "pso/TObject.h"
#include "pso/system/vector.h"
#include "pso/object/TObjMotion.h"
#include "pso/enemy/TObjEnemy.h"

#include <dolphin/mtx.h>
#include <stddef.h>
#include "pso/enemy/TObjEnePanarms.h"
#include "pso/enemy/TObjEnePanBARA.h"
#include "pso/enemy/TObjEnePanarmsAtkColli.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"



extern "C" {
extern const char lbl_8043C948[];
extern const char lbl_8043C95C[];
extern const char lbl_8043C970[];
extern const char lbl_8043C984[];
extern const char lbl_8043C9A0[];
extern const char lbl_8043C9BC[];
extern const char lbl_8043C9D8[];
extern const char lbl_8043C9F4[];
extern const char lbl_8043CA10[];
extern const char lbl_8043CA2C[];
extern const char lbl_8043CA48[];
extern const char lbl_8043CA64[];
extern const char lbl_8043CA7C[];
extern const char lbl_8043CA98[];
extern const char lbl_8043CAB4[];
extern const char lbl_8043CAD0[];
extern const char lbl_8043CAEC[];
extern const char lbl_8043CB08[];
extern const char lbl_8043CB24[];
extern const char lbl_8043CB40[];
extern const char lbl_8043CB5C[];
extern const char lbl_8043CB78[];
extern const char lbl_8043CB94[];
extern const char lbl_8043CBB0[];
extern const char lbl_8043CBC8[];
extern const char lbl_8043CBE0[];
extern const char lbl_8043CBF8[];
extern const char lbl_8043CC10[];
extern const char lbl_8043CC28[];
extern const char lbl_8043CC40[];
extern const char lbl_8043CC58[];
extern const char lbl_8043CC70[];
extern const char lbl_8043CC88[];
extern const char lbl_8043CCA4[];
extern const char lbl_8043CCC0[];
const char *bm7_s_paa_body_model_names[] = { lbl_8043C948, lbl_8043C95C, lbl_8043C970, 0 };
const char *bm7_s_paa_body_motion_names[] = {
    lbl_8043C984,
    lbl_8043C9A0,
    lbl_8043C9BC,
    lbl_8043C9D8,
    lbl_8043C9F4,
    lbl_8043CA10,
    lbl_8043CA2C,
    lbl_8043CA48,
    lbl_8043CA64,
    lbl_8043CA7C,
    lbl_8043CA98,
    lbl_8043CAB4,
    lbl_8043CAD0,
    lbl_8043CAEC,
    lbl_8043CB08,
    lbl_8043CB24,
    lbl_8043CB40,
    lbl_8043CB5C,
    lbl_8043CB78,
    lbl_8043CB94,
    lbl_8043CBB0,
    lbl_8043CBC8,
    lbl_8043CBE0,
    lbl_8043CBF8,
    lbl_8043CC10,
    lbl_8043CC28,
    lbl_8043CC40,
    lbl_8043CC58,
    lbl_8043CC70,
    lbl_8043CC88,
    lbl_8043CCA4,
    0
};
BmlResourceDescriptor lbl_80494F10 = {lbl_8043CCC0, bm7_s_paa_body_model_names, bm7_s_paa_body_motion_names, 3, 31};
CollisionBody lbl_80494F20 = {{0.0f, 15.000000953674316f, 0.0f}, 12.5f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f};
TObjMotionAction lbl_80494F4C[] = {
    {1, 0, 23, 0.7f, 0}, {1, 0, 29, 0.6f, 0},
    {1, 0, 30, 0.6f, 0}, {3, 0, 9, 0.6f, 0},
    {3, 0, 12, 0.7f, 0}, {3, 0, 15, 0.7f, 0},
    {3, 0, 5, 0.7f, 0}, {2, 0, 3, 0.9f, 0},
    {3, 0, 4, 0.6f, 0}, {2, 0, 2, 0.8f, 0},
    {3, 0, 8, 0.6f, 0}, {1, 0, 26, 1.0f, 0}
};
TObjEnePanarms::ActionPair lbl_8049515C[] = {
    {&TObjEnePanarms::fn_800DE2B0, &TObjEnePanarms::try_activate},
    {&TObjEnePanarms::init_state, &TObjEnePanarms::fn_800DE124},
    {&TObjEnePanarms::set_hidden_flags, &TObjEnePanarms::update_fall},
    {&TObjEnePanarms::fn_800DDED8, &TObjEnePanarms::fn_800DDC30},
    {&TObjEnePanarms::fn_800DDAD8, &TObjEnePanarms::fn_800DD9A0},
    {&TObjEnePanarms::set_state_flags_6, &TObjEnePanarms::update_particle_emitters_set2},
    {&TObjEnePanarms::fn_800DD7F4, &TObjEnePanarms::update_destroy_child},
    {&TObjEnePanarms::set_flags_and_field_b8, &TObjEnePanarms::update_particle_emitters},
    {&TObjEnePanarms::fn_800DD5C8, &TObjEnePanarms::update_wait_then_set_state},
    {&TObjEnePanarms::fn_800DD488, &TObjEnePanarms::update_hit_effect},
    {&TObjEnePanarms::fn_800DD368, &TObjEnePanarms::update_separated_parts},
    {&TObjEnePanarms::merge_halves, &TObjEnePanarms::update_timed_action},
    {&TObjEnePanarms::fn_800DCFE0, &TObjEnePanarms::update_state_effect},
    {&TObjEnePanarms::enter_down_state, &TObjEnePanarms::update_spin},
};
ModelNodePositionEntry lbl_804952AC[] = {
    {0x35, {0, 0, 0}}, {0x22, {0, 0, 0}}, {0x38, {0, 0, 0}},
    {0x46, {0, 0, 0}}, {0x3B, {0, 0, 0}}, {-1, {0, 0, 0}}
};
}

typedef NpcAnimationBinding PanarmsNpcSpawnDescriptor;

extern "C" {
s32 obj_setFlags30(void *, int);

extern const f32 lbl_805DA4DC;
s32 spawn_continuous_particle_with_direction(void *, void *, int, int);
f32 sin_table_lookup(int);
f32 cos_table_lookup(int);
void *spawn_directional_particle(void *pos, void *dir, s32 id);

void set_field_b8__10TObjMotionFs(void *, int);
f32 vec3_add_to(void *, void *);
extern const f32 lbl_805DA4D8;
s32 queue_destruction__7TObjectFv(void *);
extern TObjMotionAction lbl_80494F4C[12];
extern f32 lbl_805D527C;
extern u8 lbl_805D5280;
s32 project_actor_to_ground(void *, void *, int);
u16 find_nearest_visible_player(void *, f32 *, f32);
f64 atan2_float(f32, f32);
extern const f64 TObjEnePanarms__data_8043CD20;
s32 approach_angle_limited(s32, s32, s32);
extern const f32 lbl_805DA4F0;
f32 vector_length(void *);
extern const f32 lbl_805DA4F4;

extern PanarmsNpcSpawnDescriptor panarms_npc_spawn_descriptor[];

extern u32 TObjEnePanarms__entry_params_resource;
extern const f32 lbl_805DA51C;
f32 random_ratio__9TObjCharaFv(s32 arg0);
extern const f32 lbl_805DA4D4;
extern const f32 lbl_805DA4E8;
extern const f32 lbl_805DA4EC;
s32 subtract_vector(void *, void *);
s32 normalize_vector(void *);
u32 csnLookAt(void *, void *);
f32 horizontal_distance_squared(void *, void *);
extern const f32 lbl_805DA4E4;
void *create_particle_emitter(void *pos, s32 id);
extern s32 lbl_8043CD04[];
extern s32 lbl_8043CD0C[];
extern s32 lbl_8043CCF4[];
extern s32 lbl_8043CCFC[];
extern s32 registered_player_count;
int TObjEnePanarms__sub_800DFBC4(void *p);
extern const f32 lbl_805DA4C4;
extern const f32 lbl_805DA4C8;
extern const f32 lbl_805DA4CC;
extern const f32 lbl_805DA4D0;
void free_collision_body_parts(void *);
int post_translate_matrix(void*);
int rotate_matrix_y(void*, void*);
int push_matrix(void*);
int pop_matrix(void);
void draw_blob_shadow(s32 arg0);
}
void direction_to_rotation_xz(u8 *arg0, s32 *arg1, s32 *arg2);
extern "C" {
s32 rotate_matrix_z(int, int);
void translate_matrix(u32 arg0, f32 x, f32 y, f32 z);
s32 rotate_matrix_x(int, int);
s32 scale_current_matrix(Vec *);
extern const f32 lbl_805DA4F8;
extern const f32 lbl_805DA4FC;
extern const f32 lbl_805DA500;
extern const f32 lbl_805DA504;
extern const f32 lbl_805DA508;
extern const f32 lbl_805DA50C;
extern const f32 lbl_805DA510;
extern const f32 lbl_805DA514;
extern const f32 lbl_805DA518;

extern const f32 lbl_805DA4E0;

extern "C" {
s32 is_split_screen();
s32 get_camera_mode__11TCameraCtrlFv();
extern s32 model_render_flags;
extern s32 saved_model_render_flags;
s32 submit_cursor_candidate(void *, s32);
s32 minimap_render_dot(void *, s32, s32, s32);
}

struct PanarmsSetData {
    s16 set_index;
    u16 m_2;
    u16 m_4;
    u16 entity_id;
    s16 room;
    s16 group;
    u32 m_c;
    Vec position;
    s32 rotation[3];
    f32 parameters[5];
    s16 variant;
    s16 state;
};
struct PanarmsMovementParameters {
    f32 m_0;
    f32 m_4[5];
    s32 range;
    s32 wait;
};
extern "C" {
extern const char *TObjEnePanarms__name;
s32 TObjFish__sub_8001EDB0(BmlResource *, s32);
CollisionBody *init_collision_body_parts(TObjCollidable *, const CollisionBody *, s32);
void register_entity_by_id(TObjBase *);
}

}

extern "C" {

extern s32 tl_04;

}

void TObjEnePanarms::update_spin() {
    s32 temp_r0;

    if (this->m_3ec & 2) {
        this->rotation.yaw = (this->rotation.yaw + 0x111);
    } else {
        this->rotation.yaw = (this->rotation.yaw - 0x111);
    }
    temp_r0 = this->state_timer - 1;
    this->state_timer = temp_r0;
    if (temp_r0 < 0) {
        set_state(7);
    }
}

void TObjEnePanarms::enter_down_state() {
    collision_body->flags |= 1;
    obj_clearFlags30(0x04040000U);
    this->state_timer = 0x1E;
    this->m_3f0 = (s32) (this->m_3f0 + 1);
    set_field_b8__10TObjMotionFs(this, 0xB);
}

void TObjEnePanarms::update_state_effect() {
    f32 temp_f1;
    temp_f1 = this->frame;
    if ((temp_f1 >= 20.0f) && (temp_f1 < 20.6f)) {
        spawn_particle_effect((const Vec *)((&position)), 0xF0);
    }
    if (this->motion_flags & 0x10) {
        set_state(3);
    }
}

void TObjEnePanarms::fn_800DCFE0() {
    visible = 1;
    collision_body->flags &= ~1U;
    this->obj_clearFlags30((u32)(0x40000));
    obj_setFlags30(this, 0x04000000);
    play_sound_effect((s32)(this->remap_sound_for_area(0x4003BC31)), (const Vec *)(&draw_positions[1]), 0, 0);
    play_sound_effect((s32)(this->remap_sound_for_area(0x4003BC30)), (const Vec *)(&draw_positions[3]), 0, 0);
    this->init(0xA);
}

void TObjEnePanarms::update_timed_action() {
    s32 temp_r0;

    if ((first_half->is_in_state_7_or_8() != 0) || (second_half->is_in_state_7_or_8() != 0)) {
        set_state(0xA);
        return;
    }
    temp_r0 = this->state_timer - 1;
    this->state_timer = temp_r0;
    if (temp_r0 <= 0) {
        set_state(0xC);
        return;
    }
    if ((s32) this->state_timer == 0x13) {
        play_sound_effect((s32)(this->remap_sound_for_area(0x4003BC32)), (const Vec *)(&position), 0, 0);
    }
}

void TObjEnePanarms::merge_halves() {
    this->visible = 0;
    collision_body->flags &= ~1U;
    obj_clearFlags30(0x40000U);
    obj_setFlags30(this, (int)(0x04000000U));
    fn_800DE430(0x2D, 0x25);
    this->hp = (s16) (this->first_half->hp + this->second_half->hp);
    first_half->fn_800E1D94();
    second_half->fn_800E1D94();
    this->state_timer = 0x40;
}

void TObjEnePanarms::update_separated_parts() {
    s32 temp_r0;
    this->hp = (s16) ((this->first_half->hp) + this->second_half->hp);
    if ((this->first_half->is_in_state_8() != 0) && (this->second_half->is_in_state_8() != 0)) {
        this->send_entity_set_flags();
        queue_destruction__7TObjectFv(this);
        return;
    }
    if (first_half->is_in_state_7_or_8() == 0) {
        switch (second_half->is_in_state_7_or_8()) {
        case 0:
        this->state_timer = (this->state_timer - 1);
        temp_r0 = this->state_timer;
        if (temp_r0 == 0) {
            if ((this->first_half->is_in_state_11() != 0) || (this->second_half->is_in_state_11() != 0)) {
                this->state_timer += 15.0f;
                return;
            }
            find_combine_position();
            first_half->init_state();
            second_half->init_state();
            return;
        }
        if (temp_r0 < 0) {
            if ((this->first_half->is_state_4_timer_expired() != 0) && (this->second_half->is_state_4_timer_expired() != 0)) {
                if ((first_half->get_state_flag() != 0) || (second_half->get_state_flag() != 0)) {
                    this->state_timer = -1;
                    return;
                }
                set_state(0xB);
                return;
            }
            if ((s32) this->state_timer < -0x12C) {
                first_half->do_action_2();
                second_half->do_action_2();
                this->state_timer = 0x384;
            }
        }
        break;
        }
    }
}

void TObjEnePanarms::fn_800DD368() {
    collision_body->flags &= ~1U;
    this->obj_clearFlags30((u32)(0x40000));
    obj_setFlags30(this, 0x04000000);
    visible = 0;
    this->state_timer = 0x384;
    this->m_3f8 = 1;
    play_sound_effect((s32)(this->remap_sound_for_area(0x4003BC2E)), (const Vec *)(&position), 0, 0);
    if (this->first_half->is_in_state_7_or_8() == 0) {
        first_half->start_split_at_body();
    }
    if (this->second_half->is_in_state_7_or_8() == 0) {
        second_half->start_split_at_body();
    }
}

void TObjEnePanarms::update_hit_effect() {
    f32 temp_f1;
    temp_f1 = this->frame;
    if ((temp_f1 >= 20.0f) && (temp_f1 < 20.6f)) {
        spawn_particle_effect((const Vec *)((&position)), 0xF0);
    }
    if (this->motion_flags & 0x10) {
        set_state(0xA);
    }
}

void TObjEnePanarms::fn_800DD488() {
    collision_body->flags &= ~1U;
    this->obj_clearFlags30((u32)(0x40000));
    obj_setFlags30(this, 0x04000000);
    fn_800DE430(0x22, 0x3C);
    play_sound_effect((s32)(this->remap_sound_for_area(0x4003BC2D)), (const Vec *)(&draw_positions[1]), 0, 0);
    play_sound_effect((s32)(this->remap_sound_for_area(0x4003BC2C)), (const Vec *)(&draw_positions[3]), 0, 0);
    set_field_b8__10TObjMotionFs(this, 0xA);
}

void TObjEnePanarms::update_wait_then_set_state() {
    s32 temp_r0;
    void *temp_r3;
    if (this->frame >= 5.0f) {
        temp_r3 = particle_emitters[0];
        if (temp_r3 != 0) {
            TParticleCtrl::release((void *)temp_r3);
            particle_emitters[0] = 0;
        }
    }
    temp_r0 = this->state_timer - 1;
    this->state_timer = temp_r0;
    if (temp_r0 <= 0) {
        if (!(m_3ec & 1) && ((s32) this->m_3f0 < 4)) {
            set_state(0xD);
            return;
        }
        set_state(3);
    }
}

void TObjEnePanarms::fn_800DD5C8() {
    s32 buffer_14[3];
    f32 buffer_8[3];
    s32 temp_r6;
    collision_body->flags |= 1;
    this->obj_clearFlags30(0x04040000U);
    spawn_directional_particle((&draw_positions[4]), (&this->rotation.pitch), 0x109);
    temp_r6 = this->rotation.yaw - 0x4000;
    buffer_14[1] = 0;
    buffer_14[0] = temp_r6;
    buffer_14[2] = 0x4000;
    particle_emitters[0] = (void *)spawn_continuous_particle_with_direction(&draw_positions[4], &buffer_14[0], 0x108, temp_r6);
    buffer_8[1] = 0.0f;
    buffer_8[0] = sin_table_lookup((int) (this->rotation.yaw));
    buffer_8[2] = cos_table_lookup((int) (this->rotation.yaw));
    ((TObjEnePanarmsAtkColli *)this)->create(&draw_positions[4], &buffer_8[0], (void *)1);
    set_field_b8__10TObjMotionFs(this, 9);
    state_timer = 0x5A;
}

void TObjEnePanarms::update_particle_emitters() {
    s32 i;
    if (frame >= 10.0f) {
        for (i = 0; i < 2; i++) {
            void **slot = &particle_emitters[i];
            if (*slot == 0) {
                *slot = create_particle_emitter(&draw_positions[lbl_8043CD0C[i]], lbl_8043CD04[i]);
            }
        }
    }
    if (motion_flags & 0x10) {
        set_state(8);
    }
}

void TObjEnePanarms::set_flags_and_field_b8() {
    collision_body->flags |= 1;
    obj_clearFlags30(0x04040000U);
    set_field_b8__10TObjMotionFs(this, 8);
}

void TObjEnePanarms::update_destroy_child() {
    s32 temp_r0;
    void *temp_r3;
    if (this->frame >= 5.0f) {
        temp_r3 = particle_emitters[0];
        if (temp_r3 != 0) {
            TParticleCtrl::release((void *)temp_r3);
            particle_emitters[0] = 0;
        }
    }
    temp_r0 = this->state_timer - 1;
    this->state_timer = temp_r0;
    if (temp_r0 <= 0) {
        set_state(3);
    }
}

void TObjEnePanarms::fn_800DD7F4() {
    s32 buffer_14[3];
    f32 buffer_8[3];
    s32 temp_r6;
    collision_body->flags |= 1;
    this->obj_clearFlags30(0x04040000U);
    temp_r6 = this->rotation.yaw + 0x4000;
    buffer_14[1] = 0;
    buffer_14[0] = temp_r6;
    buffer_14[2] = 0x4000;
    particle_emitters[0] = (void *)spawn_continuous_particle_with_direction(&draw_positions[2], &buffer_14[0], 0x105, temp_r6);
    buffer_8[1] = 0.0f;
    buffer_8[0] = sin_table_lookup((int) (this->rotation.yaw));
    buffer_8[2] = cos_table_lookup((int) (this->rotation.yaw));
    ((TObjEnePanarmsAtkColli *)this)->create(&draw_positions[2], &buffer_8[0], NULL);
    set_field_b8__10TObjMotionFs(this, 7);
    state_timer = 0x5A;
}

void TObjEnePanarms::update_particle_emitters_set2() {
    s32 i;
    if (frame >= 10.0f) {
        for (i = 0; i < 2; i++) {
            void **it = &particle_emitters[i];
            if (*it == 0) {
                *it = create_particle_emitter(&draw_positions[lbl_8043CCFC[i]], lbl_8043CCF4[i]);
            }
        }
    }
    if (motion_flags & 0x10) {
        set_state(6);
    }
}

void TObjEnePanarms::set_state_flags_6() {
    collision_body->flags |= 1;
    obj_clearFlags30(0x04040000U);
    set_field_b8__10TObjMotionFs(this, 6);
}

#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma fp_contract on
void TObjEnePanarms::fn_800DD9A0() {
    Vec particle;
    Vec ground;
    f32 temp_f2;
    s32 temp_r0;
    state_timer = (s32) (state_timer - 1);
    if ((s8) lbl_805D5280 == 0) {
        lbl_805D5280 = 1;
        lbl_805D527C = lbl_80494F4C[4].speed;
    }
    temp_f2 = frame;
    if ((temp_f2 >= 21.0f) && (temp_f2 < (21.0f + lbl_805D527C))) {
        VecCopy((Vec *)(&particle), (const Vec *)(&body_center_position.x));
        particle.y += 5.0f;
        spawn_particle_effect((const Vec *)((&particle)), 0xF0);
    }
    temp_r0 = state_timer;
    if (temp_r0 <= 0x78) {
        if (temp_r0 == 0x78) {
            ground.x = (0.5f * position.x) + (0.5f * draw_positions[0].x);
            ground.y = position.y;
            ground.z = (0.5f * position.z) + (0.5f * draw_positions[0].z);
            spawn_ground_effect((Vec *)(&ground), 0x78);
            TObjPlayer::spawn_dead_spot_default((s32)((void *)&ground), 6);
        }
        if ((s32) state_timer == 0x5A) {
            shadow_enabled = 0;
        }
        position.y = (f32) (position.y - 0.104166664f);
        if ((s32) state_timer <= 0) {
            queue_destruction__7TObjectFv(this);
        }
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEnePanarms::fn_800DDAD8() {
    s16 st;
    Vec v;
    this->state_timer = 0xA4;
    distribute_experience_and_request_drop();
    this->send_entity_set_flags();
    st = 5;
    if (find_nearest_visible_player(this, &v.x, 200.0f) != 0xFFFF) {
        if (v.x * sin_table_lookup(this->rotation.yaw) + v.z * cos_table_lookup(this->rotation.yaw) < 0.0f) {
            st = 4;
        }
    }
    set_field_b8__10TObjMotionFs(this, st);
    play_sound_effect((s32)(this->remap_sound_for_area(0x4003B836)), (const Vec *)(&draw_positions[1]), 0, 0);
    play_sound_effect((s32)(this->remap_sound_for_area(0x4003BB35)), (const Vec *)(&draw_positions[3]), 0, 0);
    if (visible != 0) {
        if (this->first_half->is_in_state_7_or_8() == 0) {
            this->first_half->reset_split();
        }
        if (this->second_half->is_in_state_7_or_8() == 0) {
            this->second_half->reset_split();
        }
    } else {
        if (this->first_half->is_in_state_7_or_8() == 0) {
            first_half->fn_800E1D38();
        }
        if (this->second_half->is_in_state_7_or_8() == 0) {
            second_half->fn_800E1D38();
        }
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEnePanarms::fn_800DDC30() {
    f32 s;
    if (frame >= 0.0f && frame <= 12.0f) {
        s32 mode = 1;
        if ((f32)state_timer < 49.999996185302734375f) {
            mode = 0;
        }
        if (TObjEnePanarms__sub_800DFBC4(this) != 0) {
            turn_toward_target(0x100);
        } else {
            turn_to_nearest_player(0x100, mode);
        }
    }
    if (frame >= 14.0f && frame <= 20.0f) {
        s = sin_table_lookup((s32)(lbl_805DA4C4 * (frame - 14.0f) / lbl_805DA4C8));
    } else {
        s = 0.0f;
    }
    if (s > 0.0f) {
        Vec pos = position;
        f32 r = lbl_805DA4CC * s;
        if (m_38c == 1) {
            r *= lbl_805DA4D0;
        }
        pos.x += r * cos_table_lookup(this->rotation.yaw);
        pos.z += -r * sin_table_lookup(this->rotation.yaw);
        try_warp_to_position((Vec *)&pos);
    }
    if (TObjEnePanarms__sub_800DFBC4(this) == 0) {
        if (no_player_within_range() != 0) {
            set_state(1);
            return;
        }
        if (m_3f8 == 0 && hp <= initial_hp / 3 &&
            has_ground_around((Vec *)&position) != 0) {
            set_state(9);
            return;
        }
    }
    if (--state_timer > 0) {
        return;
    }
    if (TObjEnePanarms__sub_800DFBC4(this) == 0 && m_3fc >= 3 &&
        has_ground_around((Vec *)&position) != 0) {
        m_3fc = 0;
        set_state(9);
        return;
    }
    switch (m_38c) {
    case 0:
        m_3ec++;
        m_3f0 = 0;
        set_state(7);
        break;
    case 1:
        set_state(5);
        break;
    }
}
#pragma pop

void TObjEnePanarms::fn_800DDED8() {
    s16 var_r30;
    switch (m_38c) {
    case 0:
        m_38c = 1;
        var_r30 = 2;
        break;
    case 1:
        m_38c = 0;
        var_r30 = 1;
        break;
    default:
        return;
    }
    m_3fc += 1;
    collision_body->flags &= ~0x08000000;
    collision_body->flags |= 1;
    obj_clearFlags30(0x04040000);
    state_timer = (s32) (49.999996185302734375f * (f32) ((s32) (lbl_805DA4D4 * random_ratio__9TObjCharaFv((s32)this)) + 1));
    set_field_b8__10TObjMotionFs(this, var_r30);
}

void TObjEnePanarms::update_fall() {
    Vec particle;
    velocity.y += lbl_805DA4D8;
    vec3_add_to(&position, &velocity);
    if (velocity.y <= 0.0f && position.y <= ground_height) {
        position.y = ground_height;
        spawn_particle_effect((const Vec *)(&position), 0xF0);
        set_state(3);
        return;
    }
    state_timer++;
    if (!(state_timer & 7) && velocity.y > 0.0f) {
        VecCopy(&particle, (const Vec *)&body_center_position.x);
        particle.y = 5.0f + ground_height;
        spawn_particle_effect((const Vec *)(&particle), 0xF0);
    }
}

void TObjEnePanarms::set_hidden_flags() {
    this->velocity.x = (f32) 0.0f;
    this->velocity.y = (f32) lbl_805DA4DC;
    this->velocity.z = (f32) 0.0f;
    this->shadow_enabled = 1;
    this->visible = 1;
    collision_body->flags &= ~1U;
    obj_clearFlags30(0x40000U);
    obj_setFlags30(this, (int)(0x04000000U));
}

void TObjEnePanarms::fn_800DE124() {
    f32 sp[3];
    s32 r = 0;
    s32 t;
    if (--state_timer < 0) {
        r = 1;
    } else if ((t = find_nearest_visible_player(this, sp, (f32) m_474)) != 0xFFFF) {
        this->rotation.yaw = (s32) (TObjEnePanarms__data_8043CD20 * atan2_float(sp[0], sp[2]));
        r = 1;
    }
    if (r != 0) {
        set_state(2);
    }
}

void TObjEnePanarms::init_state() {

    VecCopy((Vec *)(&position), (const Vec *)(&home_position));
    this->snap_to_ground();
    position.y = (f32) (lbl_805DA4E0 + ground_height);
    obj_setFlags30(this, 0x04040000);
    collision_body->flags &= ~1U;
    collision_body->flags |= 0x08000000;
    shadow_enabled = 0;
    visible = 0;
    this->state_timer = (s32) this->m_478;
}

void TObjEnePanarms::try_activate() { if (check_demo_mode() == 0) { set_state(1); } }

void TObjEnePanarms::fn_800DE2B0() {
    shadow_enabled = 1; visible = 1; }

void TObjEnePanarms::vfunc_61() { this->actorFlags &= 0xfffffeff; }

void TObjEnePanarms::vfunc_62() {
    switch (state) {
    case 1:
    case 2:
        return;
    default:
        actorFlags &= 0xFFFFFDFF;
        play_sound_effect((s32)(this->remap_sound_for_area(0x4003BC34)), (const Vec *)(&draw_positions[1]), 0, 0);
        play_sound_effect((s32)(this->remap_sound_for_area(0x4003BC33)), (const Vec *)(&draw_positions[3]), 0, 0);
        break;
    }
}

void TObjEnePanarms::vfunc_63() { if (state != 4) { set_state(4); } }

s32 TObjEnePanarms::sub_800DE390() {
    switch (state) {
    case 0:
    case 1:
    case 2:
    case 4:
    case 10:
    case 11:
        return 0;
    default:
        if (first_half->is_in_state_7_or_8() != 0 || second_half->is_in_state_7_or_8() != 0) {
            set_state(10);
            return 1;
        }
        return 0;
    }
}

void TObjEnePanarms::fn_800DE430(s32 arg1, s32 arg2) {
    Vec particle;
    VecCopy((Vec *)(&particle), (const Vec *)(&body_center_position.x));
    particle.y += 10.0f;
    create_particle_controller_with_rotation(&particle, (ParticleAngles *)&this->rotation.pitch, 0x106, arg1, arg2);
}

#pragma push
#pragma opt_loop_invariants off
s32 TObjEnePanarms::no_player_within_range() {
    s32 i;
    f32 best = lbl_805DA4E4;
    for (i = 0; i < registered_player_count; i++) {
        TObjPlayer *player = TObjPlayer::get_player_data(i);
        if (player != NULL) {
            f32 d = horizontal_distance_squared(&position, &player->body_center_position.x);
            if (d < best) {
                best = d;
            }
        }
    }
    if (best < lbl_805DA4E4) {
        return 0;
    }
    return 1;
}
#pragma pop

#pragma push
#pragma fp_contract on
s32 TObjEnePanarms::has_ground_around(Vec *arg1) {
    Vec v;
    f32 r;
    s32 step;
    s32 a;
    VecCopy((Vec *)&v, (const Vec *)arg1);
    v.y += 10.0f;
    if (project_actor_to_ground(this, &v, 0) == 0) {
        return 0;
    }
    for (r = 10.0f; r <= 20.0f; r += 10.0f) {
        step = (s32)(lbl_805DA4E8 / (lbl_805DA4EC * r));
        for (a = 0; a < 0x10000; a += step) {
            VecCopy((Vec *)&v, (const Vec *)arg1);
            v.x += r * sin_table_lookup(a);
            v.y += 10.0f;
            v.z += r * cos_table_lookup(a);
            if (project_actor_to_ground(this, &v, 0) == 0) {
                return 0;
            }
        }
    }
    return 1;
}
#pragma pop

s32 TObjEnePanarms::check_ground_along_path(Vec *arg1, Vec *arg2, f32 step, f32 dy) {
    Vec p = *arg1;
    Vec d = *arg2;
    f32 len;
    f32 t;
    subtract_vector(&d, &p);
    len = vector_length(&d);
    if (len < step) {
        return 1;
    }
    normalize_vector(&d);
    d.x *= step;
    d.y *= step;
    d.z *= step;
    for (t = 0.0f; t < len; ) {
        p.y += dy;
        if (project_actor_to_ground(this, &p, 0) == 0) {
            return 0;
        }
        t += step;
        vec3_add_to(&p, &d);
    }
    return 1;
}

#pragma push
#pragma opt_common_subs off
s32 TObjEnePanarms::find_combine_position() {
    Vec sp14;
    Vec sp8;
    f32 dist;
    f32 t;
    VecCopy((Vec *)&sp14, (const Vec *)(&first_half->position));
    vec3_add_to(&sp14, &second_half->position);
    sp14.x *= 0.5f;
    sp14.y *= 0.5f;
    sp14.z *= 0.5f;
    VecCopy((Vec *)&sp8, (const Vec *)(&position));
    subtract_vector(&sp8, &sp14);
    dist = vector_length(&sp8);
    if (dist >= 10.0f) {
        normalize_vector(&sp8);
        sp8.x *= 10.0f;
        sp8.y *= 10.0f;
        sp8.z *= 10.0f;
    }
    t = 0.0f;
    while (t < dist) {
        sp14.y += 10.0f;
        if (project_actor_to_ground(this, &sp14, 0) != 0 &&
            has_ground_around((Vec *) &sp14) != 0 &&
            check_ground_along_path((Vec *) (&first_half->position), (Vec *) &sp14, 10.0f, 10.0f) != 0 &&
            check_ground_along_path((Vec *) (&second_half->position), (Vec *) &sp14, 10.0f, 10.0f) != 0) {
            TObjEnePanBARA *a;
            TObjEnePanBARA *b;
            VecCopy((Vec *)(&position), (const Vec *)&sp14);
            a = first_half;
            b = second_half;
            this->rotation.yaw = (s32) (TObjEnePanarms__data_8043CD20 * atan2_float(
                b->position.x - a->position.x,
                b->position.z - a->position.z)) + 0x4000;
            return 1;
        }
        t += 10.0f;
        vec3_add_to(&sp14, &sp8);
    }
    return 0;
}
#pragma pop

void TObjEnePanarms::turn_toward_target(s32 arg1) {
    f32 sp[3];
    if (this->find_nearest_enemy_with_flag((s32)sp, (f32)lbl_805DA4F0) == 0xFFFF) {
        if (entity_id & 1) {
            arg1 *= -1;
        }
        this->rotation.yaw = this->rotation.yaw + arg1;
        return;
    }
    this->rotation.yaw = approach_angle_limited(this->rotation.yaw, (s32) (TObjEnePanarms__data_8043CD20 * atan2_float(sp[0], sp[2])), arg1);
}

u16 TObjEnePanarms::turn_to_nearest_player(s32 arg1, s32 arg2) {
    f32 sp[3];
    s32 t;
    s32 var;
    if ((t = find_nearest_visible_player(this, sp, 200.0f)) != 0xFFFF) {
        if (arg2 == 0 || vector_length(sp) < lbl_805DA4F4) {
            var = 0;
        } else {
            var = -0x1800;
            if ((s32)m_38c == 1) {
                var *= -1;
            }
        }
        this->rotation.yaw = approach_angle_limited(this->rotation.yaw, var + (s32) (TObjEnePanarms__data_8043CD20 * atan2_float(sp[0], sp[2])), arg1);
    }
    return t;
}

#pragma push
#pragma fp_contract on
s32 TObjEnePanarms::try_warp_to_position(Vec *arg1) {
    s32 ok;
    s32 i;
    s32 ang;
    f32 c;
    f32 s;
    f32 x;
    Vec d;
    Vec p;
    Vec hit;
    ok = 0;
    if (!(horizontal_distance_squared(&position, &home_position) > lbl_805DA4E4)) {
        VecCopy((Vec *)&d, (const Vec *)arg1);
        subtract_vector(&d, &position);
        if (0.0f != vector_length(&d)) {
            i = 1;
            do {
                VecCopy((Vec *)&p, (const Vec *)(&position));
                vec3_add_to(&p, &d);
                p.y += 10.0f;
                if (((s32 (*)(void *, void *, void *))project_actor_to_ground)(this, &p, &hit) != 0 && csnLookAt(&position, &p) == 0) {
                    VecCopy((Vec *)(&prev_position), (const Vec *)(&position));
                    VecCopy((Vec *)(&position), (const Vec *)&p);
                    ground_height = p.y;
                    VecCopy((Vec *)(&ground_normal.x), (const Vec *)&hit);
                    ok = 1;
                    break;
                }
                ang = i << 12;
                if (i & 1) {
                    ang *= -1;
                }
                c = sin_table_lookup(ang);
                s = cos_table_lookup(ang);
                i++;
                x = s * d.x - c * d.z;
                d.x = x;
                d.z = c * x + s * d.z;
            } while (i < 0x10);
        }
    }
    update_collisions();
    return ok;
}
#pragma pop

void TObjEnePanarms::snap_to_ground() {
    Vec v = position;
    v.y += 10.0f;
    if (project_actor_to_ground(this, &v, (int)&ground_normal.x) != 0) {
        ground_height = v.y;
    }
}

void TObjEnePanarms::set_state(s32 arg1) {
    state = arg1;
    if (state < 0 || state >= 14) {
        return;
    }
    destroy_handles();
    TObjEnePanarms::Action p = lbl_8049515C[state].enter;
    if (p) {
        (this->*p)();
    }
}

#pragma push
#pragma fp_contract on
#pragma opt_common_subs off
void TObjEnePanarms::draw_shadow() {
    Vec v;
    s32 spC;
    s32 sp8;
    f32 d;
    f32 k;
    f32 t;

    if (!(this->ground_height > lbl_805DA4F8 + position.y)) {
        push_matrix(this);
        translate_matrix(0, lbl_805DA4FC * position.x + lbl_805DA500 * draw_positions[0].x, lbl_805DA504 + this->ground_height, lbl_805DA4FC * position.z + lbl_805DA500 * this->draw_positions[0].z);
        direction_to_rotation_xz((u8 *)&ground_normal.x, &spC, &sp8);
        rotate_matrix_z(0, sp8);
        rotate_matrix_y((void *) 0, (void *)this->rotation.yaw);
        rotate_matrix_x(0, spC + 0x4000);
        d = position.y - this->ground_height;
        if (d > lbl_805DA508) {
            d = lbl_805DA508;
        } else if (d < 0.0f) {
            d = 0.0f;
        }
        t = lbl_805DA514 - d / lbl_805DA508;
        k = lbl_805DA510 * t + lbl_805DA50C;
        v.z = lbl_805DA514;
        v.x = 5.0f * k;
        v.y = lbl_805DA518 * k;
        scale_current_matrix(&v);
        draw_blob_shadow(0);
        pop_matrix();
    }
}
#pragma pop

void TObjEnePanarms::draw_model() {
    push_matrix(this);
    post_translate_matrix(&position);
    rotate_matrix_y(0, (void *)this->rotation.yaw);
    set_current_texture_list((GinjaTextureList *)(texlist));
    draw_callbacks->install();
    draw();
    draw_callbacks->clear();
    pop_matrix();
}

void TObjEnePanarms::render() {
    s32 cam;
    RenderFadeState *fade;
    s32 draw;
    if (update_object_view_visibility(lbl_805DA4F0, 20.0f) == 0) {
        return;
    }
    cam = 0;
    if (is_split_screen() != 0) {
        cam = get_camera_mode__11TCameraCtrlFv();
    }
    if (this->visible == 0) {
        return;
    }
    TObjPlayer::toggle_particle_effect();
    saved_model_render_flags = model_render_flags;
    fade = &camera_fades[cam];
    fade->update();
    if (fade->updateFromCamera(&this->body_center_position.x) != 0) {
        fade->set_flags_and_apply_damage_color();
        draw = 1;
        if (defer_render() != 0) {
            draw = 0;
        }
        if (draw != 0) {
            draw_model();
        }
        fade->clear_flag_and_notify();
    } else {
        model_render_flags |= 0x01000000;
        draw_model();
    }
    model_render_flags = saved_model_render_flags;
    TParticleCtrl::end_effect_render();
    if (this->shadow_enabled != 0) {
        draw_shadow();
    }
}

void TObjEnePanarms::run_task() {
    TObjEnePanarms::Action p;
    if (this->state != 0 && check_demo_mode() != 0) {
        set_state(0);
    }
    sub_800DE390();
    p = lbl_8049515C[this->state].update;
    if (p) {
        (this->*p)();
        if (this->visible != 0) {
            this->actorFlags &= ~0x02000000;
        } else {
            this->actorFlags |= 0x02000000;
        }
        update_prev_position();
        if (this->state != 0) {
            if (this->visible != 0) {
                submit_cursor_candidate(this, -1);
                advance_animation();
            }
            if ((this->visible != 0 && this->state != 4) || this->state == 1) {
                minimap_render_dot(&this->body_center_position.x, -0x5DB4, 1, 0);
            }
        }
    }
}

void TObjEnePanarms::destroy_handles() {
    s32 i;
    for (i = 0; i < 2; i++) {
        if (particle_emitters[i] != 0) {
            TParticleCtrl::release(particle_emitters[i]);
            particle_emitters[i] = 0;
        }
    }
}

TObjEnePanarms::~TObjEnePanarms() {
    ModelNodePositionCapture::destroy(draw_callbacks);
    first_half->queue_destruction();
    second_half->queue_destruction();
    free_collision_body_parts(this);
    collision_body = 0;
    destroy_handles();
}

#pragma defer_codegen on

s32 TObjEnePanarms::create(s32 arg0) {
    return (s32)new TObjEnePanarms(new TObjControl((TObject *)tl_04), (void *)arg0);
}

void TObjEnePanarms::load_and_spawn_npc() {
    BmlResource *o = new BmlResource(1, &lbl_80494F10, 0, 0, NULL);
    TObjEnePanarms__entry_params_resource = (u32) o;
    if (o != NULL) {
        PanarmsNpcSpawnDescriptor sp = panarms_npc_spawn_descriptor[0];
        sp.motions = o->motions;
        NpcModelRegistry::register_animated_chunk(0x23, (void *)o->models[0].model, (void *)o->models[0].m_c, &sp, lbl_805DA51C, 0.0f);
        TObjEnePanarms::spawn_npc_pair();
    }
}

void TObjEnePanarms::free_data() {
    if ((u32) TObjEnePanarms__entry_params_resource != 0U) {
        delete (BmlResource *)TObjEnePanarms__entry_params_resource;
        TObjEnePanarms__entry_params_resource = 0U;
    }
}

#pragma push
#pragma opt_common_subs on
TObjEnePanarms::TObjEnePanarms(TObject *parent, void *set_data) : TObjEnemy(parent) {
    m_name = TObjEnePanarms__name;
    add_flags_2e4(2);
    apply_set_data(set_data);
    clear_lobby_object_state();
    texlist = TObjFish__sub_8001EDB0((BmlResource *)TObjEnePanarms__entry_params_resource, 0);
    model = (void *)get_bml_model((BmlResource *)TObjEnePanarms__entry_params_resource, 0);
    VecCopy(&prev_position, VecCopy(&home_position, VecCopy(&center, &position)));
    collision_body = init_collision_body_parts(this, &lbl_80494F20, 1);
    set_action_table(lbl_80494F4C);
    set_motion_list(((BmlResource *)TObjEnePanarms__entry_params_resource)->motions);
    set_animation(0);
    set_field_b8(0);
    VecCopy((Vec *)&body_center_position.x, &position);
    movement_velocity.z = 0.0f;
    movement_velocity.y = 0.0f;
    movement_velocity.x = 0.0f;
    velocity.z = 0.0f;
    velocity.y = 0.0f;
    velocity.x = 0.0f;
    target = 0;
    bind_enemy_combat_stats((u8 *)get_battle_base_stats(0x31), (u8 *)get_battle_attack_params(0x31), (u8 *)get_battle_resistance_params(0x31));
    referenceHp = hp;
    register_entity_by_id(this);
    set_param(0x15);
    for (s32 i = 0; i < 2; ++i) particle_emitters[i] = 0;
    motion_flags &= ~1;
    draw_callbacks = ModelNodePositionCapture::create(lbl_804952AC, draw_positions);
    m_38c = 1;
    m_3ec = 0;
    initial_hp = hp;
    m_3f8 = 0;
    m_3fc = 0;
    m_470 = ((PanarmsMovementParameters *)get_battle_movement_params(0x31))->m_0;
    m_474 = ((PanarmsMovementParameters *)get_battle_movement_params(0x31))->range;
    if ((s32)m_474 < 5) m_474 = 5;
    m_478 = ((PanarmsMovementParameters *)get_battle_movement_params(0x31))->wait;
    if ((s32)m_478 < 0) m_478 = 0;
    for (s32 i = 0; i < 4; ++i) camera_fades[i].activate_and_dispatch();
    set_state(1);
    PanarmsSetData child = *(PanarmsSetData *)set_data;
    child.set_index = set_index + 1;
    child.entity_id = entity_id + 1;
    first_half = create_bara(&child, 0);
    child.set_index = set_index + 2;
    child.entity_id = entity_id + 2;
    second_half = create_bara(&child, 1);
    if (first_half == 0 || second_half == 0) return;
    first_half->bind_parts(this, second_half);
    second_half->bind_parts(this, first_half);
}
#pragma pop
