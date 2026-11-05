#include "pso/system/ModelNodePositionCapture.h"
#include "pso/enemy/BattleParameters.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/protocol/protocol_types.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/misc/TLobby_801E43E4.h"
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "types.h"
#include "pso/system/vector.h"
#include "pso/boss/TBoss4Type2.h"
#include "pso/boss/TBoss6PlotFalz.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TNowLoading.h"
#include "pso/player/TObjChara.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/boss/TBoss6Type1.h"
#include "pso/boss/TBoss6Mine.h"
#include "pso/system/SoundEffect.h"
#include "pso/player/TObjPlayer.h"
#include "pso/object/TObjMapCsn.h"
#include "pso/TParticleCtrl.h"
#include "pso/math/AngleLookup.h"
#include "pso/unk/text_802AA8FC.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/unk/text_803E2D70.h"

extern const Vec boss6_map_csn_offset;
extern const Vec boss6_map_csn_scale;

struct RecoveredGlobal_802B7E88_lbl_80470CEC {
    s32 values[12];
};

#include <stddef.h>
struct Boss6AnimBlock { s32 a; s32 b; s32 rest[14]; };



struct EffectSlotEntry { s32 a; s32 b; };





struct MotionSetEntry { s32 mode; s32 next; s32 ids[2]; };
struct Boss6ActionPacket { u8 b[0x10]; };



struct PartPositionSource { s32 kind; s32 idx; };

typedef void (TBoss6Type1::*ActionFn)();

struct ActionEntry { s32 f0; s32 anim; s32 f8; ActionFn act; ActionFn idle; ActionFn update; };

struct Boss6ActionArgs {
    s8 b0;
    u8 b1;
    s8 b2;
};








struct Line3 { Vec p; Vec d; };




struct MotionBlendPair { Boss6Motion *motions[2]; f32 ts[2]; };



void handle_6xA4_olga_flow_boss_actions(void *arg);
extern "C" {


u8 *get_enemy_entity(u16 arg0);
f32 vector_length(void *);
f32 subtract_vector(void *, const void *);
f32 fabs_float(f32);
s32 get_entity_id(void *);
extern const Vec TBoss6Type1__data_80470FB4;
extern const f32 TBoss6Type1__data_805DE2D0;
s32 TBoss6Type1__sub_802B5FDC(TBoss6Type1 *arg0);
s32 TBoss6Type1__sub_802B5FF4(TBoss6Type1 *arg0);
s32 TBoss6Type1__sub_802B600C(TBoss6Type1 *arg0);
s32 rand();
extern u8 boss6_type1_random_action_table[];
extern const f32 lbl_805DE3D8;
extern const f32 lbl_805DE3D4;
void TBoss6Type1__sub_802B8BB4(TBoss6Type1 *arg0);
s32 is_active__14TBoss6PlotFalzFv();
void TBoss6PlotFalz__sub_802AC724(void *, void *);
void vec3_cross(void *, void *, void *);
void normalize_vector(void *);
f32 project_point_onto_line(void *, void *, void *);
f32 xyz_distance(void *, void *);
f32 vec3_add_to(void *, const void *);
void TBoss6Type1__sub_802B6C30(TBoss6Type1 *self);
s32 TObjFish__sub_8001EDB0(s32, s32);
s32 get_bml_model(s32, s32);

void draw_model_motion(void *arg0, void *arg1, f32 farg0);
// init_collision_body_parts copies these 7 spheres in TBoss6Type1__ct.
CollisionBody lbl_804DF4E0[7] = {
    {{0.0f, 0.0f, 0.0f}, 35.0f, 0.0f, 0, 0x801B, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 50.0f, 0.0f, 0, 0x801B, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 10.0f, 0.0f, 0, 0x801B, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 10.0f, 0.0f, 0, 0x801B, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 10.0f, 0.0f, 0, 0x801B, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 10.0f, 0.0f, 0, 0x801B, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 10.0f, 0.0f, 0, 0x801B, {0.0f, 0.0f, 0.0f}, 0.0f},
};
__declspec(section ".data") s32 lbl_804DF614[2] = {3, 6};
MotionSetEntry TBoss6Type1__motion_set_table[21] = {
    {0, 0, 44, 45}, {0, 1, 42, 45}, {0, 2, 44, 56}, {2, 0, 40, 41}, {2, 2, 44, 53},
    {2, 0, 37, 38}, {2, 2, 37, 38}, {2, 8, 29, 30}, {0, 8, 13, 14}, {2, 1, 47, 48},
    {2, 2, 44, 22}, {2, 2, 44, 23}, {2, 2, 44, 43}, {2, 2, 44, 46}, {2, 2, 51, 52},
    {2, 16, 44, 17}, {0, 16, 44, 18}, {2, 18, 44, 19}, {0, 18, 44, 20}, {2, 2, 44, 21},
    {2, 2, 44, 15},
};
extern const s32 lbl_805DE3C8;
extern s32 lbl_80470FAC[];

void TBoss6Type1__sub_802B4B04(TBoss6Type1 *arg0);
void TBoss6Type1__sub_802B5598(TBoss6Type1 *self, Vec *out);
s32 TBoss6Type1__sub_802B6060(TBoss6Type1 *arg0);
extern Vec lbl_80470FFC;
extern Vec lbl_80471008;
extern Vec lbl_80470FE4;
extern Vec lbl_80470FF0;
void TBoss6Type1__sub_802B5970(TBoss6Type1 *arg0);
extern RecoveredGlobal_802B7E88_lbl_80470CEC TBoss6Type1__param_table;
extern const s32 lbl_805DE3A8;
extern const s32 lbl_805DE3B0;
void TBoss6Type1__sub_802B7D50(TBoss6Type1 *arg0);
extern const Vec lbl_80470CD4;
extern const Vec lbl_80470CE0;
void TBoss6Type1__sub_802B5140(TBoss6Type1 *arg0, s32 arg1, s32 arg2);
void TBoss6Type1__sub_802B4CF4(TBoss6Type1 *arg0);
void TBoss6Type1__sub_802B59A8(TBoss6Type1 *self);
void TBoss6Type1__sub_802B59CC(TBoss6Type1 *self);
void TBoss6Type1__sub_802B5AB0(TBoss6Type1 *self);
extern const s32 lbl_805DE2D4;
void TBoss6Type1__sub_802B4D38(TBoss6Type1 *self);
void TBoss6Type1__sub_802B5DD4(TBoss6Type1 *self);
void *create_particle_emitter(void *pos, s32 id);
extern EffectSlotEntry TBoss6Type1__effect_slot_table[];
extern u8 lbl_80471014[];
Boss6Motion *get_bml_motion(s32, s32);
extern const s32 TBoss6Type1__data_805DE3C4;
void TBoss6Type1__sub_802B909C(TBoss6Type1 *self, Boss6ActionArgs *atk);
extern const f32 lbl_805DE3DC;
void TBoss6Type1__sub_802B8E1C(TBoss6Type1 *arg0);
TObjPlayer *get_player_by_client_id(u16 client);
s32 matrix_mult_vec(int, void *, void *);
void set_matrix_identity(u8 *arg0);
s32 rotate_matrix_y(int, int);
s32 push_matrix();
void post_translate_matrix(Vec *pos);
void rotate_vector_by_matrix(int matrix, const Vec *in, Vec *out);
void rotate_matrix_x(int matrix, int angle);
void rotate_matrix_z(int matrix, int angle);
void scale_matrix(int matrix, f32 x, f32 y, f32 z);
extern PartPositionSource TBoss6Type1__part_position_sources[];
extern ActionEntry boss6_type1_action_table[];

u8 *fn_8035648C(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
extern f32 TBoss6Type1__sword_shot_hit_radii[];
extern s32 game_difficulty_selection;
void TBoss6Type1__sub_802B73AC(TBoss6Type1 *self);
f32 atan2_float(f64, f64);
extern const f64 TBoss6Type1__data_80471038;
void request_follow_camera_offsets(void *, void *, int);
extern const Vec lbl_80470FC0;
s32 angle_diff_s16(s32, s32);
extern const s8 lbl_805DE2C8[2];
extern const s8 lbl_805DE2CC[2];
extern const f32 lbl_805DE3E0;
extern const f32 lbl_805DE3E8;
extern const f32 lbl_805DE3E4;
extern const s32 lbl_805DE3AC;
extern const s32 lbl_805DE3B4;
void TBoss6Type1__sub_802B4A70(void* p);
void TBoss6Type1__sub_802B4A90(TBoss6Type1 *p);
void TBoss6Type1__sub_802B4B14(TBoss6Type1 *p);
void TBoss6Type1__sub_802B4A9C(TBoss6Type1 *);




extern const Vec lbl_80470FCC;
extern const Vec lbl_80470FD8;

extern f32 lbl_805DE350;
}

void draw_model_blend_motion(void *arg0, void *arg1, f32 farg0);

 extern u32 boss6_type1_trail_point_offsets[];

struct ByteBlock_C_boss6_1 { u8 bytes[0xc]; };

#include <stddef.h>
#include "pso/boss/TBoss3Volopt.h"
#include "pso/enemy/TObjEneLappy.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/player/TObjPlayer.h"
extern "C" TObjEnemy *__ct__9TObjEnemyFP7TObject(void *, void *);
struct Stack_802B9204_boss6_1 {
    s32 sp8;
    s8 spC;
    u8 trailing_storage[0xF];
};
extern "C" {



u8 * TBoss6Type1__sub_802B96C0(s32 arg0, s32 arg1);
extern const f32 lbl_805DE3D0;
s32 angle_difference_abs(int, int);
s32 approach_angle_limited(int, int, int);
s32 TBoss6Type1__ct(s32, s32, s32);
s32 __ct__11TObjControlFP7TObject(s32, s32);
s32 __nw__7TObjectFUl(s32);
#define VLEN(p) vector_length(p)


f32 vec3_dot(void *, void *);
void *spawn_particle_effect_with_flags(void *pos, s32 id, s32 flags);



typedef char RecoveredGlobal_802B7E88_lbl_80470CEC_size[sizeof(RecoveredGlobal_802B7E88_lbl_80470CEC) == 0x30 ? 1 : -1];

extern Boss6AnimBlock lbl_80470ECC;
extern u8 lbl_80470F0C[];
}

void build_6xA4_olga_flow_boss_actions(void* p);
extern "C" {



s32 submit_cursor_candidate(void *, int);
s32 add_radar_scaled_marker(void *, int, int, int, f32);
}

extern const f32 lbl_805DE3CC;

/* 6xA4: the Olga Flow boss action sent by send_6xA4_action. */
struct OlgaFlowActionMsg {
    u8 command;
    u8 size;
    u16 entity_id;
    s8 action;
    u8 action_args[3];
    u8 sync_params[3];
};

extern "C" {


extern f32 lbl_805DE3EC;


extern s32 tl_04;

struct VBase_18_f05d67 { char pad[0x18]; };
struct VObj_18_f05d67 : VBase_18_f05d67 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual void m63();
    virtual void m64();
    virtual void m65();
    virtual void m66();
    virtual void m67();
    virtual void m68();
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual void m72();
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76();
    virtual void m77();
    virtual void m78();
    virtual s32 m79(void *);
};

struct ObjectStateTmp { s32 a; s16 b; s16 c; u8 pad[0x10]; };


void TBoss6Type1__sub_802B854C(TBoss6Type1 *);
extern u8 lbl_80470D1C[];
extern u8 boss6_type1_model_node_desc[];
extern u8 boss6_type1_model_node_desc_b[];
extern u8 boss6_type1_build_table[];
extern u8 lbl_80470EA0[];
extern u8 lbl_80470EAC[];
extern u8 __vt__11TBoss6Type1[];
extern s32 lbl_805D3EB0;

}

void build_6xA4_olga_flow_boss_actions(void* p) {
    OlgaFlowActionMsg *msg = (OlgaFlowActionMsg *)p;
    msg->command = 0xA4;
    msg->size = 5;
}
void TBoss6Type1::step_and_send_60() { read_be16_field2(); send_subcommand((u8 *)this); }
void TBoss6Type1::read_be16_field2() { ((G_ClientIDHeader *)this)->bswap(); }
int TBoss6Type1::is_idle() { return this->m_374 == 0; }
void*TBoss6Type1::get_mag_mine_ptr() { return &this->hist[4]; }
void TBoss6Type1::clear_harmful_statuses() {  }
void TBoss6Type1::apply_shock_status() {  }
void TBoss6Type1::apply_movement_ailment(s32) {  }
void TBoss6Type1::apply_confusion_status() {  }
void TBoss6Type1::apply_slow_status() {  }
void TBoss6Type1::apply_paralysis() {  }

void TBoss6Type1::apply_poison_status() {  }

s32 TBoss6Type1::create(s32 arg2_) {
    s32 arg0_;
    s32 var_r4;

    arg0_ = __nw__7TObjectFUl(0x684);
    if (arg0_ != 0) {
        var_r4 = __nw__7TObjectFUl(0x20);
        if (var_r4 != 0) {
            var_r4 = __ct__11TObjControlFP7TObject(var_r4, tl_04);
        }
        arg0_ = TBoss6Type1__ct(arg0_, var_r4, arg2_);
    }
    return arg0_;
}
extern "C" {


u8 * TBoss6Type1__sub_802B96C0(s32 arg0, s32 arg1) {
    *(ByteBlock_C_boss6_1 *)(arg0) = *(const ByteBlock_C_boss6_1 *)(arg1);
    return (u8 *)arg0;
}
#define arg0 ((u8 *)arg0_)
#define arg2 ((s32 *)arg2_)
#pragma push
#pragma opt_common_subs off
s32 TBoss6Type1__ct(s32 arg0_, s32 parent, s32 arg2_) {
    TBoss6Type1 *self = (TBoss6Type1 *)arg0_;
    ObjectStateTmp tmp;
    s32 i;

    __ct__9TObjEnemyFP7TObject(arg0, (void *)parent);
    *(u8 **)((s8 *)arg0 + 0x18) = __vt__11TBoss6Type1;
    self->m_name = (const char *)lbl_805D3EB0;
    self->add_flags_2e4(8);
    self->m_3f8 = arg2[0];
    ((VObj_18_f05d67 *)self)->m79(arg2 + 1);
    if (self->exchange_object_state(&tmp, (s16)1) != 0) {
        tmp.a = 0;
        tmp.c = 0;
        self->exchange_object_state(&tmp, (s16)0);
    }
    self->m_3fc = TObjFish::get_fish_count();
    self->texlist = 0;
    self->model = 0;
    VecCopy(&self->position, &lbl_80470CD4);
    copy_xyz(&self->rotation, lbl_80470D1C);
    VecCopy(&self->prev_position, (const Vec *)((void *)VecCopy(&self->home_position, (const Vec *)((void *)VecCopy(&self->center, &self->position)))));
    init_collision_body_parts(self, lbl_804DF4E0, 7);
    self->update_position();
    self->movement_velocity.z = 0.0f;
    self->movement_velocity.y = 0.0f;
    self->movement_velocity.x = 0.0f;
    self->target = 0;
    self->bind_enemy_combat_stats((u8 *)(get_battle_base_stats(0x2B)), (u8 *)(get_battle_attack_params(0x2B)), (u8 *)(get_battle_resistance_params(0x2B)));
    self->referenceHp = self->hp;
    ((TBoss3Volopt *)self)->reset_photon_effect();
    self->set_param(0x4E);
    TBoss6Type1__sub_802B854C(self);
    self->draw_callback_lists[1] = (ModelNodePositionCapture *)ModelNodePositionCapture::create((ModelNodePositionEntry *)(boss6_type1_model_node_desc), &self->node_positions_578[0].v);
    self->draw_callback_lists[0] = (ModelNodePositionCapture *)ModelNodePositionCapture::create((ModelNodePositionEntry *)(boss6_type1_model_node_desc_b), &self->node_positions_5FC[0]);
    TBoss6PlotFalz::build_tables(self->scroll_strips_u, boss6_type1_build_table, 2);
    TBoss6PlotFalz::build_tables(self->scroll_strips_v, lbl_80470EA0, 1);
    self->trail_point_receiver = TBoss6Type1::create_zanzo(self, (void *)7, (void *)0xF);
    self->effect_point_receiver = TBoss6Type1::create_zanzo(self, (void *)2, (void *)0xF);
    self->m_414 = 0;
    self->m_41c = 0;
    TBoss6Type1__sub_802B96C0((s32)&self->m_420, (s32)lbl_80470EAC);
    VecCopy(&self->m_420, &self->position);
    TBoss6Type1__sub_802B96C0((s32)&self->m_42C, (s32)lbl_80470EAC);
    self->m_438 = 1;
    self->unk_418 = 0;
    for (i = 0; i < 32; i++) {
        self->hist[i] = 0;
    }
    self->load_params_from_table();
    self->m_4ac = 0;
    self->m_4b4 = 1.0f;
    self->latch_phase_counter();
    self->unk_4b8 = 0;
    self->unk_4bc = 0;
    self->unk_4c0 = 0;
    self->unk_4c4 = 0;
    self->m_4d4 = 0.0f;
    self->m_4d8 = 1.0f;
    self->reset_fields_4e0();
    self->reset_param();
    TBoss6Type1__sub_802B7D50(self);
    self->unk_408 = 0;
    TBoss6Type1__sub_802B4D38(self);
    self->clear_slot_array();
    TBoss6Type1__sub_802B4A90(self);
    VecCopy(&self->m_56C, &self->position);
    self->set_action_state(0);
    return arg0_;
}
#pragma pop
#undef arg0
#undef arg2

TBoss6Type1::~TBoss6Type1() {
    s32 i;
    TBoss6Type1__sub_802B4A70(this);
    TBoss6Type1__sub_802B4B14(this);
    TBoss6Type1__sub_802B4CF4(this);
    ((TBoss6PlotFalz *)scroll_strips_v)->free_buffer_pairs();
    ((TBoss6PlotFalz *)scroll_strips_u)->free_buffer_pairs();
    for (i = 0; i < 2; i++) {
        if (draw_callback_lists[i] != NULL) {
            ModelNodePositionCapture::destroy(draw_callback_lists[i]);
            draw_callback_lists[i] = NULL;
        }
    }
    free_collision_body_parts(this);
}

void TBoss6Type1::set_sync_data(void *arg1) {
    OlgaFlowActionMsg *msg = (OlgaFlowActionMsg *)arg1;
    msg->entity_id = (u16) this->entity_id;
    msg->sync_params[0] = (s8) this->m_438;
    msg->sync_params[1] = (s8) this->m_414;
    msg->sync_params[2] = (s8) (lbl_805DE3EC * ((1.0f / 32768.0f) * (f32) rand()));
}

void TBoss6Type1::load_params(void *arg1) {
    OlgaFlowActionMsg *msg = (OlgaFlowActionMsg *)arg1;
    this->m_438 = (s32) (s8) msg->sync_params[0];
    this->m_414 = (s32) (s8) msg->sync_params[1];
    this->m_41c = msg->sync_params[2];
}

void TBoss6Type1::send_flow_action_if_idle(TBoss6Type1 *boss6_type1, int action) {
    typedef char sp8_offset[(offsetof(Stack_802B9204_boss6_1, sp8) == 0x0) ? 1 : -1];
    typedef char spC_offset[(offsetof(Stack_802B9204_boss6_1, spC) == 0x4) ? 1 : -1];
    Stack_802B9204_boss6_1 stack;
    if (((s32)((TBoss6Type1 *)(boss6_type1->m_3f8))->is_idle()) != 0) {
        build_6xA4_olga_flow_boss_actions(&stack.sp8);
        boss6_type1->set_sync_data(&stack.sp8);
        stack.spC = action;
        ((TBoss6Type1 *)(&stack.sp8))->step_and_send_60();
    }
}

s32 TBoss6Type1::send_6xA4_action(s32 t, s32 *src) {
    Boss6ActionPacket m;
    u8 *s;
    s32 i;
    if (((TBoss6Type1 *)(this->m_3f8))->is_idle() != 0) {
        build_6xA4_olga_flow_boss_actions(&m);
        set_sync_data(&m);
        m.b[4] = t;
        s = (u8 *)src;
        for (i = 1; i < 4; i++) {
            m.b[i + 4] = *s++;
        }
        ((TBoss6Type1 *)(&m))->step_and_send_60();
    }
}

void TBoss6Type1__sub_802B909C(TBoss6Type1 *self, Boss6ActionArgs *atk) {
    s8 dir = (u8)((u32)self->rotation.yaw >> 8);
    u8 kind;
    dir += lbl_805DE3E8 * ((1.0f / 32768.0f) * (f32)rand() - 0.5f);
    atk->b0 = dir;
    kind = 0x12;
    if ((1.0f / 32768.0f) * (f32)rand() < 0.5f) {
        kind = 0x1C;
    }
    atk->b1 = kind;
    atk->b2 = 10;
}
void TBoss6Type1::randomize_attack(void *self_, void *atk_) {
    Boss6ActionArgs *atk = (Boss6ActionArgs *)atk_;
    const s8 *tab;
    s8 base;
    s8 v;
    f32 r;
    s8 w;
    s8 u;
    TBoss6Type1__sub_802B909C(((TBoss6Type1 *)self_), atk);
    base = (u8)((u32)((TBoss6Type1 *)self_)->rotation.yaw >> 8);
    v = 80.0f * ((1.0f / 32768.0f) * (f32)rand()) + lbl_805DE3E0;
    if ((1.0f / 32768.0f) * (f32)rand() < 0.5f) {
        v = -v;
    }
    atk->b0 = base + v;
    if ((s32)atk->b1 == 0x12 && TBoss6Type1__sub_802B600C(((TBoss6Type1 *)self_)) == 0) return;
    atk->b1 = 0x1C;
    if (TBoss6Type1__sub_802B5FF4(((TBoss6Type1 *)self_)) != 0) {
        r = (1.0f / 32768.0f) * (f32)rand();
        w = 0x12;
        if (r < 0.1f) {
            w = -2;
        } else if (r < lbl_805DE3E4) {
            w = 10;
        }
        atk->b2 = w;
        return;
    }
    tab = TBoss6Type1__sub_802B5FDC(((TBoss6Type1 *)self_)) != 0 ? lbl_805DE2C8 : lbl_805DE2CC;
    u = tab[0];
    if ((1.0f / 32768.0f) * (f32)rand() < 0.5f) {
        u = tab[1];
    }
    atk->b2 = u;
}

void TBoss6Type1::do_attack() {
    s32 sp8;

    if (this->m_414 == 0) {
        TBoss6Type1__sub_802B909C(this, (Boss6ActionArgs *)(&sp8));
    } else {
        randomize_attack(this, &sp8);
    }
    this->m_438 = 1;
    send_6xA4_action(2, &sp8);
}

void TBoss6Type1__sub_802B8E1C(TBoss6Type1 *arg0) {
    Boss6ActionArgs s;
    s32 r4;
    TBoss6Type1__sub_802B909C(arg0, (Boss6ActionArgs *)(&s));
    s.b1 = 0x1C;
    r4 = 0x21;
    arg0->m_438 = 1;
    if (arg0->position.y < lbl_805DE3DC) {
        r4 = 0x26;
    }
    arg0->send_6xA4_action(r4, (s32 *)((s32 *)&s));
}

void TBoss6Type1__sub_802B8BB4(TBoss6Type1 *arg0) {
    Boss6ActionArgs s;
    s32 r4;
    s32 n;
    s32 id;
    switch (arg0->m_414) {
    case 0:
        if (TBoss6Type1__sub_802B600C(arg0) != 0) {
            TBoss6Type1::send_flow_action_if_idle(arg0, TBoss6Type1::rand_range_inclusive((s32)arg0, 5, 6));
            break;
        }
        switch (arg0->pick_remapped_list_value(3, 5, 0x20)) {
        case 3:
            TBoss6Type1::send_flow_action_if_idle(arg0, 3);
            return;
        case 5:
            TBoss6Type1::send_flow_action_if_idle(arg0, TBoss6Type1::rand_range_inclusive((s32)arg0, 5, 6));
            return;
        case 4:
            return;
        }
        break;
    case 1:
        TBoss6Type1::randomize_attack(arg0, &s);
        if (TBoss6Type1__sub_802B5FDC(arg0) != 0) {
            id = 0x15;
            n = arg0->count_matches(0x15, 8);
            if (n == 0 || (1.0f / 32768.0f) * (f32)rand() < lbl_805DE3D8 / (f32)n) {
                s.b2 = -2;
            } else {
                id = 2;
            }
            arg0->send_6xA4_action(id, (s32 *)&s);
            break;
        }
        if (TBoss6Type1__sub_802B5FF4(arg0) != 0) {
            arg0->send_6xA4_action(4, (s32 *)&s);
            break;
        }
        r4 = TBoss6Type1::pick_random_entry((s32)arg0, (s32)boss6_type1_random_action_table, 5);
        switch (r4) {
        case 4:
            if (s.b2 == -2) {
                r4 = 2;
            } else {
                s.b1 = 0x1C;
            }
            break;
        case 22:
            s.b2 = 10;
            break;
        case 5:
            s.b2 = 10;
            r4 = TBoss6Type1::rand_range_inclusive((s32)arg0, 6, 7);
            break;
        case 8:
            s.b2 = 10;
            r4 = TBoss6Type1::rand_range_inclusive((s32)arg0, 8, 10);
            break;
        }
        arg0->send_6xA4_action(r4, (s32 *)&s);
        break;
    }
}
#pragma push
#pragma opt_lifetimes off
void TBoss6Type1__sub_802B8A70(TBoss6Type1 *self) {
    Boss6ActionArgs atk;
    s8 v;
    f32 ratio;
    s32 total;
    v = ((u32)self->rotation.yaw >> 8) & 0xFF;
    v = lbl_805DE3D4 * ((1.0f / 32768.0f) * (f32)rand() - 0.5f) + v;
    ratio = 0.5f;
    atk.b1 = 0x1C;
    atk.b0 = v;
    total = self->unk_4c0 + self->unk_4c4;
    if (total > 0) {
        ratio = (f32)self->unk_4c0 / (f32)total;
    }
    v = 20;
    if ((1.0f / 32768.0f) * (f32)rand() < ratio) {
        v = -5;
    }
    atk.b2 = v;
    self->m_438 = 1;
    self->send_6xA4_action(0x18, (s32 *)&atk);
}
#pragma pop
}


void handle_6xA4_olga_flow_boss_actions(void *arg) {
    OlgaFlowActionMsg *msg = (OlgaFlowActionMsg *)arg;
    TBoss6Type1 *boss;
    s32 action;

    ((TBoss6Type1 *)msg)->read_be16_field2();
    boss = (TBoss6Type1 *)get_enemy_entity(msg->entity_id);
    if (boss == NULL) {
        return;
    }
    ((TBoss6Type1 *)&msg->action)->handle_6xa4_action((u8 *)&boss->m_420);
    boss->load_params(msg);
    action = msg->action;
    if (action < 0 || action >= 41) {
        return;
    }
    boss->set_action_state(action);
}

void TBoss6Type1::vfunc_62() {
    this->actorFlags = (s32) (this->actorFlags & 0xFFFFFDFF);
    this->m_4d4 = 1.0f;
    play_sound_effect(0x39E01, &this->node_positions_578[1].v, 0, 1);
}

void TBoss6Type1::vfunc_63() { if (this->m_374 != 40) { set_action_state(40); } }

void TBoss6Type1::render_shadows() {
    if (this->position.y >= lbl_805DE3D0) {
        TObjEnemy::render_shadows();
    }
}

void TBoss6Type1::run_task() {
    ActionFn a;
    a = boss6_type1_action_table[this->m_374].update;
    if (a != 0) {
        (this->*a)();
    }
    if (((TBoss6Type1 *)this->m_3f8)->is_idle() != 0) {
        a = boss6_type1_action_table[this->m_374].idle;
        if (a != 0) {
            (this->*a)();
        }
    }
    advance_animations();
    update_turn_to_center();
    update_position();
    update_part_positions();
    update_parts_flags();
    ((TObjPlayer *)this)->update_collisions();
    submit_cursor_candidate(this, -1);
    add_radar_scaled_marker(&this->node_positions_578[1].v, -0x5DB4, 1, 1, 5.0f);
    sub_802B5CB4();
    this->m_4d4 += lbl_805DE3CC;
    if (this->m_4d4 < 0.0f) {
        this->m_4d4 = 0.0f;
    }
    this->m_4d8 = (f32)this->hp / (f32)this->referenceHp;
    ((TBoss6PlotFalz *)scroll_strips_u)->scroll_strips_uv(8, 0);
    ((TBoss6PlotFalz *)scroll_strips_v)->scroll_strips_uv(0, 0x22);
    update_sway();
    sub_802B4C28();
    this->unk_408 += 1;
}
void TBoss6Type1::set_action_state(s32 arg1) {
    ActionFn a;
    ActionEntry *e;
    s32 i;
    this->m_374 = arg1;
    for (i = 31; i > 0; i--) {
        this->hist[i] = this->hist[i - 1];
    }
    this->hist[0] = this->m_374;
    switch (this->m_374) {
    case 24:
        this->unk_4b8++;
        break;
    case 26:
        this->unk_4bc++;
        this->unk_4c0++;
        break;
    case 34:
        this->unk_4bc++;
        this->unk_4c4++;
        break;
    }
    e = &boss6_type1_action_table[this->m_374];
    this->set_motion_set(e->anim);
    this->unk_418 = e->f8;
    a = e->act;
    if (a != 0) {
        (this->*a)();
    }
}

extern "C" {



struct Boss6TransformWords {
    u32 word0;
    f32 word4;
    f32 word8;
    f32 wordC;
    f32 word10;
    u32 word14;
    f32 word18;
};

void TBoss6Type1::copy_transform(void* q) {
    Boss6TransformWords* dst = (Boss6TransformWords*)this;
    *dst = *(Boss6TransformWords*)q;
}

void *TBoss6Type1::copy_block(void *d, void *s) {
    *(Boss6AnimBlock *)d = *(Boss6AnimBlock *)s;
    return d;
}

void TBoss6Type1__sub_802B854C(TBoss6Type1 *self) {
    s32 i;
    Boss6Anim *a;
    TBoss6Type1::copy_block(&self->motion_set, &lbl_80470ECC);
    for (i = 0; i < TBoss6Type1__data_805DE3C4; i++) {
        a = &self->anims[i];
        ((TBoss6Type1 *)a)->copy_transform(lbl_80470F0C);
        a->motion = a->prev_motion = get_bml_motion(self->m_3fc, TBoss6Type1__motion_set_table[2].ids[i]);
    }
}

void TBoss6Type1::advance_animations() {
    s32 cur;
    s32 i;
    Boss6Anim *a;
    f32 len;
    f32 lim;
    s32 n;
    cur = lbl_805DE3C8;
    n = TBoss6Type1__data_805DE3C4;
    for (i = 0; i < n; i++) {
        if (i == cur) continue;
        a = &this->anims[i];
        len = a->motion->frames;
        a->t += a->speed;
        if (a->t >= len) a->t -= len;
        if (0.0f != a->blend) {
            if ((a->blend += a->rate) >= 1.0f) a->blend = 0.0f;
        }
    }
    a = &this->anims[lbl_805DE3C8];
    len = a->motion->frames;
    a->t += a->speed;
    switch (this->motion_mode) {
    case 0:
        if (a->t >= len) a->t -= len;
        break;
    case 1:
        break;
    case 2:
        lim = len - 1.0f;
        if (a->t >= lim) {
            a->t = lim;
            set_motion_set(TBoss6Type1__motion_set_table[this->motion_set].next);
        }
        break;
    }
    if (0.0f != a->blend) {
        if ((a->blend += a->rate) >= 1.0f) a->blend = 0.0f;
    }
}

void TBoss6Type1::set_motion_set(s32 arg1) {
    f32 z;
    s32 n;
    MotionSetEntry *t;
    s32 i;
    Boss6Anim *a;

    if (arg1 != -1 && arg1 != this->motion_set) {
    this->motion_set = arg1;
    z = TBoss6Type1__data_805DE2D0;
    n = TBoss6Type1__data_805DE3C4;
    t = &TBoss6Type1__motion_set_table[arg1];
    this->motion_mode = t->mode;
    for (i = 0; i < n; i++) {
        a = &this->anims[i];
        Boss6Motion *motion = get_bml_motion(this->m_3fc, t->ids[i]);
        a->blend = a->rate;
        a->prev_motion = a->motion;
        a->prev_t = a->t;
        a->motion = motion;
        a->t = z;
    }
    }
}
void TBoss6Type1::draw_part_motions() {
    MotionBlendPair b;
    s32 i;
    s32 id;
    s32 p;
    Boss6Anim *a;
    ModelNodePositionCapture *cb;
    set_motion_packed_rotation();
    for (i = 0; i < 2; i++) {
        id = lbl_804DF614[i];
        p = TObjFish__sub_8001EDB0(this->m_3fc, lbl_804DF614[i]);
        id = get_bml_model(this->m_3fc, id);
        cb = this->draw_callback_lists[i];
        a = &this->anims[i];
        if (cb != 0) {
            set_current_texture_list((GinjaTextureList *)(p));
            if (0.0f == a->blend) {
                cb->install();
                draw_model_motion((void *)id, a->motion, a->t);
                cb->clear();
            } else {
                b.motions[0] = a->prev_motion;
                b.ts[0] = a->prev_t;
                b.motions[1] = a->motion;
                b.ts[1] = a->t;
                cb->install();
                draw_model_blend_motion((void *)id, &b, a->blend);
                cb->clear();
            }
        }
    }
    clear_motion_packed_rotation();
}
void TBoss6Type1::load_params_from_table() {
    BattleMovementParams *params;
    params = get_battle_movement_params(0x2B);
    this->m_47c = (s32) params->m_00;
    if ((f32) this->m_47c <= 0.0f) {
        this->m_47c = TBoss6Type1__param_table.values[0];
    }
    this->unk_480 = (s32) params->m_08;
    if ((f32) this->unk_480 <= 0.0f) {
        this->unk_480 = TBoss6Type1__param_table.values[1];
    }
    this->m_484 = (s32) params->m_0c;
    if ((f32) this->m_484 <= 0.0f) {
        this->m_484 = TBoss6Type1__param_table.values[2];
    }
    this->unk_488 = (s32) params->m_10;
    if ((f32) this->unk_488 <= 0.0f) {
        this->unk_488 = TBoss6Type1__param_table.values[3];
    }
    this->m_4a4 = (s32) params->m_14;
    if ((f32) this->m_4a4 <= 0.0f) {
        this->m_4a4 = TBoss6Type1__param_table.values[10];
    }
    this->m_48c = (s32) params->m_18;
    if (this->m_48c <= 0) {
        this->m_48c = TBoss6Type1__param_table.values[4];
    }
    this->unk_490 = (s32) params->m_1c;
    if (this->unk_490 <= 0) {
        this->unk_490 = TBoss6Type1__param_table.values[5];
    }
    this->m_494 = (s32) params->m_20;
    if (this->m_494 <= 0) {
        this->m_494 = TBoss6Type1__param_table.values[6];
    }
    this->unk_498 = (s32) params->m_24;
    if (this->unk_498 <= 0) {
        this->unk_498 = TBoss6Type1__param_table.values[7];
    }
    this->m_49c = (s32) params->m_28;
    if (this->m_49c <= 0) {
        this->m_49c = TBoss6Type1__param_table.values[8];
    }
    this->laser_fire_time = (s32) params->m_2c;
    if (this->laser_fire_time <= 0) {
        this->laser_fire_time = TBoss6Type1__param_table.values[9];
    }
    this->unk_4A8 = (s32) get_battle_movement_params(0x2F)->m_14;
    if ((f32) this->unk_4A8 <= 0.0f) {
        this->unk_4A8 = TBoss6Type1__param_table.values[11];
    }
}

void TBoss6Type1::latch_phase_counter() {
    this->unk_4B0 = (s32) this->hp;
}

s32 TBoss6Type1::calc_field4b0_delta() {
    return this->unk_4B0 - this->hp;
}

void TBoss6Type1::update_turn_to_center() {
  Vec stack;
  s32 var_r5;
  int new_var;
  f32 temp_f1;
  s32 var_r31;
  s32 var_r4;
  var_r31 = 0;
  if ((this->m_438) != 0)
  {
    var_r31 = 0x8000;
  }
  if (angle_difference_abs((int) this->rotation.pitch, (int) var_r31) < 0x666)
  {
    this->rotation.pitch = var_r31;
  }
  else
  {
    this->rotation.pitch = this->rotation.pitch + 0x666;
  }
  stack.x = -this->position.x;
  temp_f1 = -this->position.z;
  stack.y = 0.0f;
  stack.z = temp_f1;
  if (!(vector_length(&stack) <= 1e-05f))
  {
    var_r4 = (s32) (TBoss6Type1__data_80471038 * atan2_float((f64) stack.x, (f64) stack.z));
    if ((this->m_438) != 0)
    {
      var_r4 += 0x8000;
    }
    var_r5 = 0x1555;
    new_var = this->rotation.yaw;
    if ((this->m_414) == 0)
    {
      var_r5 = 0x1B4;
    }
    this->rotation.yaw = approach_angle_limited(new_var, (int) var_r4, (int) var_r5);
  }
}

void TBoss6Type1__sub_802B7D50(TBoss6Type1 *self) {
    self->m_4e8 = 0.0f;
    self->m_4ec = 0;
    self->m_4f0 = (s32) lbl_805DE3A8;
    self->m_4f4 = (s32) lbl_805DE3B0;
}
void TBoss6Type1::update_sway() {
    f32 d;
    f32 target;
    s32 v;
    if (--this->m_4f4 < 0) {
        this->m_4f0 = (f32)lbl_805DE3AC * ((1.0f / 32768.0f) * (f32)rand()) + (f32)lbl_805DE3A8;
        this->m_4f4 = (f32)lbl_805DE3B4 * ((1.0f / 32768.0f) * (f32)rand()) + (f32)lbl_805DE3B0;
    }
    target = 0.0f;
    switch (this->m_374) {
    case 29:
    case 30:
    case 31:
    case 32:
    case 37:
        break;
    case 23:
        target = this->m_4e8 - 2.5f * fabs_float(sin_table_lookup(this->m_4ec));
        break;
    default:
        v = this->m_4f0;
        if (this->m_4e8 < 0.0f) {
            v = 5.0f * (f32)v;
        }
        this->m_4ec += v;
        target = 15.0f * sin_table_lookup(this->m_4ec);
        break;
    }
    d = 0.75f * (target - this->m_4e8);
    if (d < -5.0f) {
        d = -5.0f;
    } else if (d > 5.0f) {
        d = 5.0f;
    }
    this->m_4e8 += d;
}

void TBoss6Type1::update_position() {
    VecCopy(&this->body_center_position, &this->position);
    if (this->m_438 != 0) {
        this->body_center_position.y = (f32) (this->body_center_position.y - 75.0f);
        return;
    }
    this->body_center_position.y = (f32) (this->body_center_position.y - 50.0f);
}

void TBoss6Type1::update_part_positions() {
    Vec v;
    s32 i;
    Vec *base;
    CollisionBody *e;
    if (this->bodies != NULL) {
        for (i = 0; i < 7; i++) {
            PartPositionSource *t;
            e = &this->bodies[i];
            t = &TBoss6Type1__part_position_sources[i];
            base = NULL;
            switch (t->kind) {
            case 1:
                base = &this->node_positions_578[0].v;
                break;
            case 0:
                base = this->node_positions_5FC;
                break;
            }
            if (base == NULL) {
                return;
            }
            VecCopy(&v, &base[t->idx]);
            subtract_vector(&v, &this->position);
            push_matrix();
            set_matrix_identity(0);
            rotate_matrix_y(0, -this->rotation.yaw);
            matrix_mult_vec(0, &v, &e->offset);
            pop_matrix();
            VecCopy(&e->center, &e->offset);
            vec3_add_to(&e->center, &this->position);
        }
    }
}

void TBoss6Type1::update_parts_flags() {
    clear_part_flag_bit0();
    if (this->unk_418 & 1) {
        set_child_flags();
    }
    if (this->unk_418 & 2) {
        enable_parts();
    }
}

void TBoss6Type1::clear_part_flag_bit0() {
    CollisionBody *p = this->bodies;
    if (p != NULL) {
        // Seven bodies, the count init_collision_body_parts installs.
        CollisionBody *end = p + 7;
        for (; p < end; p++) {
            p->flags &= ~1u;
        }
    }
}

void TBoss6Type1::set_child_flags() {
    if (this->bodies != NULL) {
        this->bodies[0].flags |= 1;
        this->bodies[1].flags |= 1;
    }
}

void TBoss6Type1::enable_parts() {
    if (this->bodies != NULL) {
        this->bodies[2].flags |= 1;
        this->bodies[3].flags |= 1;
        this->bodies[4].flags |= 1;
        this->bodies[5].flags |= 1;
        this->bodies[6].flags |= 1;
    }
}
void TBoss6Type1::update_beam_attack() {
    Line3 line;
    Vec v;
    Vec w;
    Vec out;
    Vec A;
    Vec B;
    f32 t = this->anims[1].t;
    Boss6Motion *motion = this->anims[1].motion;
    s32 n;
    s32 i;

    if (motion != get_bml_motion(this->m_3fc, TBoss6Type1__motion_set_table[13].ids[1])) return;
    if (t < 12.5f || t > 22.0f) return;
    {
    f32 end = 12.5f + this->anims[1].speed;
    if (t >= 12.5f && t < end) {
        play_sound_effect(0x40039209, &this->node_positions_578[9].v, 0, 0);
    }
    }
    init_parts();
    n = TLobby::get_game_mode();
    for (i = 0; i < n; i++) {
        TObjPlayer *p = TObjPlayer::get_player_data(i);
        if (is_active__14TBoss6PlotFalzFv() != 0) {
            Vec *a = &this->node_positions_578[8].v;
            VecCopy(&v, &p->position);
            v.y = 0.0f;
            VecCopy(&w, &this->node_positions_578[9].v);
            subtract_vector(&w, a);
            line.p.x = a->x;
            line.p.y = 0.0f;
            line.p.z = a->z;
            line.d.x = w.x;
            line.d.y = 0.0f;
            line.d.z = w.z;
            if (!(project_point_onto_line(&v, &line, &out) > 15.0f)) {
                A.x = line.p.x;
                A.y = line.p.z;
                B.x = line.p.x + line.d.x;
                B.z = line.p.z + line.d.z;
                subtract_vector(&A, &out);
                subtract_vector(&B, &out);
                A.y = 0.0f;
                B.y = 0.0f;
                if (!(vec3_dot(&A, &B) > 0.0f)) {
                    s32 r = TBoss6PlotFalz::rand_vary_count(this->m_47c, 0.1f);
                    DirectAttackPayload payload;
                    payload.kind = 0;
                    payload.power = (f32)r;
                    p->receive_direct_attack(this, payload, 0, -1, -1);
                }
            }
        }
    }
    if (this->unk_408 & 1) return;
    Boss6NodePos c = this->node_positions_578[9];
    Boss6NodePos e;
    Vec dlt;
    f32 dist;
    c.v.y = 0.0f;
    dist = xyz_distance(&c.v, &this->m_56C);
    if (!(dist < 50.0f)) {
        f32 r = dist / 50.0f;
        s32 cnt;
        f32 s;
        s32 j;
        e.w.x = c.w.x;
        e.w.y = c.w.y;
        e.w.z = c.w.z;
        cnt = (s32)(1.0f + r);
        if (cnt > 4) cnt = 4;
        s = 1.0f / (f32)cnt;
        VecCopy(&dlt, &this->m_56C);
        subtract_vector(&dlt, &c.v);
        dlt.x *= s;
        dlt.y *= s;
        dlt.z *= s;
        for (j = 0; j < cnt; j++) {
            spawn_particle_effect_with_flags(&e.v, 0x212, 0x40);
            spawn_particle_effect_with_flags(&e.v, 0x213, 0x40);
            vec3_add_to(&e.v, &dlt);
        }
        VecCopy(&this->m_56C, &c.v);
    }
    {
        play_sound_effect(0x4003B00A, &c.v, 0, 0);
        TBoss6PlotFalz::apply_radial_effect_to_players(&c.v, 0xC0, 0xF, 100.0f);
    }
}
void TBoss6Type1__sub_802B73AC(TBoss6Type1 *self) {
    Vec *a;
    Vec *b;
    s32 ok;
    s32 flag;
    Vec p;
    Vec d;
    f32 sc;
    f32 t;
    s32 idx;
    self->update_trail_points();
    a = &self->node_positions_578[8].v;
    b = &self->node_positions_578[9].v;
    ok = 0;
    if ((b->y < a->y && b->y < 0.0f) || (b->y > a->y && b->y > 0.0f)) {
        ok = 1;
    }
    if (fabs_float(a->y) > 150.0f || fabs_float(b->y) > 150.0f) {
        ok = 0;
    }
    if (ok != 0) {
        VecCopy(&d, b);
        subtract_vector(&d, a);
        if (d.y <= 1e-05f) {
            t = 1.0f;
        } else {
            t = -a->y / d.y;
        }
        p.x = t * d.x + a->x;
        p.y = 0.0f;
        p.z = t * d.z + a->z;
        idx = game_difficulty_selection;
        if (idx < 0 || idx >= 4) {
            idx = 0;
        }
        sc = TBoss6Type1__sword_shot_hit_radii[idx];
        flag = 0;
        if ((self->unk_408 & 3) == 0) {
            flag = 1;
        }
        fn_8035648C((s32)self, (s32)&p, flag, sc);
        if (flag != 0) {
            play_sound_effect(0x4003B210, &p, 0, 0);
            TBoss6PlotFalz::apply_radial_effect_to_players(&p, 0xC0, 0xF, 100.0f);
        }
    }
}
void TBoss6Type1__sub_802B6C30(TBoss6Type1 *self) {
    s32 n;
    Vec *p4;
    Vec *p3;
    Vec *p2;
    Vec *p1;
    Vec *pA;
    Vec *pB;
    s32 i;
    TObjPlayer *pl;
    s32 inside;
    Vec *a;
    Vec *b;
    s32 j;
    f32 prev;
    f32 t;
    Vec pts[5];
    Line3 line;
    Vec A;
    Vec B;
    Vec mid;
    Vec off;
    Vec e;
    Vec f;
    Vec c;
    Vec m;
    Vec d3;
    Vec d0;
    Vec q2;
    Vec q1;
    if (0.0f == self->m_4dc) {
        return;
    }
    n = TLobby::get_game_mode();
    b = &self->node_positions_578[6].v;
    a = &self->node_positions_578[4].v;
    if (xyz_distance(a, b) < 10.0f) {
        return;
    }
    VecCopy(&mid, a);
    vec3_add_to(&mid, b);
    mid.x *= 0.5f;
    mid.y *= 0.5f;
    mid.z *= 0.5f;
    pA = &A;
    pB = &B;
    p4 = &pts[4];
    p3 = &pts[3];
    p2 = &pts[2];
    p1 = &pts[1];
    A.x = self->m_4dc * (a->x - mid.x) + mid.x;
    A.y = self->m_4dc * (a->y - mid.y) + mid.y;
    A.z = self->m_4dc * (a->z - mid.z) + mid.z;
    B.x = self->m_4dc * (b->x - mid.x) + mid.x;
    B.y = self->m_4dc * (b->y - mid.y) + mid.y;
    B.z = self->m_4dc * (b->z - mid.z) + mid.z;
    for (i = 0; i < n; i++) {
        pl = TObjPlayer::get_player_data(i);
        if (is_active__14TBoss6PlotFalzFv() == 0) {
            continue;
        }
        inside = 1;
        VecCopy(&pts[0], (const Vec *)((void *)VecCopy((p3), (const Vec *)((void *)VecCopy((p4), (pA))))));
        VecCopy(p1, (const Vec *)((void *)VecCopy((p2), (pB))));
        off.x = (-500.0f) * sin_table_lookup(self->rotation.yaw);
        off.y = 0.0f;
        off.z = (-500.0f) * cos_table_lookup(self->rotation.yaw);
        vec3_add_to(p2, &off);
        vec3_add_to(p3, &off);
        for (j = 0; j < 4; j++) {
            VecCopy(&e, &pts[j + 1]);
            subtract_vector(&e, &pts[j]);
            e.y = 0.0f;
            VecCopy(&f, &pl->position);
            subtract_vector(&f, &pts[j]);
            e.y = 0.0f;
            vec3_cross(&e, &f, &c);
            if (j > 0 && ((prev < 0.0f && c.y >= 0.0f)
                          || (prev > 0.0f && c.y <= 0.0f))) {
                inside = 0;
                break;
            }
            prev = c.y;
        }
        if (inside == 0) {
            continue;
        }
        {
            s32 r = TBoss6PlotFalz::rand_vary_count(self->m_484, 0.1f);
            DirectAttackPayload payload;
            payload.kind = 0;
            payload.power = (f32)r;
            pl->receive_direct_attack(self, payload, 0, -1, -1);
        }
        VecCopy(&d0, pA);
        subtract_vector(&d0, pB);
        d0.y = 0.0f;
        VecCopy(&d3, &pl->position);
        d3.y = 0.0f;
        line.p.x = 0.5f * (A.x + B.x);
        line.p.y = 0.0f;
        line.p.z = 0.5f * (A.z + B.z);
        line.d.x = -sin_table_lookup(self->rotation.yaw);
        line.d.y = 0.0f;
        line.d.z = -cos_table_lookup(self->rotation.yaw);
        t = project_point_onto_line(&d3, &line, NULL);
        t = 0.5f * VLEN(&d0) - t;
        if (t <= 0.0f) {
            continue;
        }
        VecCopy(&m, pA);
        subtract_vector(&m, pB);
        m.y = 0.0f;
        if (VLEN(&m) <= 1e-05f) {
            continue;
        }
        normalize_vector(&m);
        m.x *= t;
        m.z *= t;
        VecCopy(&q2, pA);
        subtract_vector(&q2, &pl->position);
        q2.y = 0.0f;
        VecCopy(&q1, pB);
        subtract_vector(&q1, &pl->position);
        q1.y = 0.0f;
        t = VLEN(&q1);
        if (VLEN(&q2) > t) {
            m.x *= (-1.0f);
            m.z *= (-1.0f);
        }
        vec3_add_to(&m, &pl->position);
        if (project_actor_to_ground(self, &m, 0) == 0) {
            m.y = 0.0f;
            if (VLEN(&m) <= 1e-05f) {
                continue;
            }
            normalize_vector(&m);
            m.x *= 95.0f;
            m.z *= 95.0f;
        }
        TBoss6PlotFalz__sub_802AC724(pl, &m);
    }
}
#undef VLEN

void TBoss6Type1::damage_players_in_range() {
    s32 n;
    s32 i;
    TObjPlayer *p;
    n = TLobby::get_game_mode();
    for (i = 0; i < n; i++) {
        p = TObjPlayer::get_player_data(i);
        if (is_active__14TBoss6PlotFalzFv() != 0) {
            Vec v = p->position;
            v.y = 0.0f;
            if (!(vector_length(&v) > 10.0f)) {
                s32 r = TBoss6PlotFalz::rand_vary_count(this->unk_488, 0.1f);
                DirectAttackPayload payload;
                payload.kind = 1;
                payload.power = (f32)r;
                p->receive_direct_attack(this, payload, 0, -1, -1);
            }
        }
    }
}
extern "C" {
void TBoss4DarkFalz__sub_8004B4F0(void *dst, void *src);
s32 TBoss6Type1__sub_802ABDEC(s32 seed);
s32 is_normal_difficulty();
extern const f32 lbl_805DE37C;
extern const f32 lbl_805DE380;
extern const f32 lbl_805DE384;
extern const f32 lbl_805DE390;
extern const s32 lbl_80470F70[5];
extern const Vec lbl_80470F84;
}

// Places a ring of TBoss6Mine around node 0. The ring count follows the plot phase
// (18 on phase 0, 36 otherwise); points sit on rings of radius k*95/rings.
extern "C" void TBoss6Type1__sub_802B6504(TBoss6Type1 *self) {
    s32 seed;
    s32 step;
    s32 count;
    s32 points;
    s32 rings;
    s32 add;
    s32 made;
    Vec *pts;
    s32 half;
    s32 i;
    Boss6MineSpawn spawn;

    seed = self->m_41c;
    self->reset_fields_4e0();
    TBoss4DarkFalz__sub_8004B4F0(&spawn, ((TBoss6Type1 *)self->m_3f8)->get_mag_mine_ptr());
    spawn.owner = self;
    VecCopy(&spawn.position, &self->node_positions_578[0].v);
    VecCopy(&spawn.point, &lbl_80470F84);
    spawn.a8 = 0;
    VecCopy(&spawn.inner, &spawn.position);
    step = 0;
    if (TBoss6PlotFalz::get_phase() == 0) {
        count = 0x12;
    } else {
        count = 0x24;
    }
    points = 1;
    rings = 0;
    add = 3;
    while (count > points) {
        points += add;
        add += 3;
        rings += 1;
    }
    pts = new Vec[points];
    VecCopy(&pts[0], &lbl_80470F84);
    if (points > 1 && rings > 0) {
        f32 spacing = 95.0f / (f32)rings;
        f32 radius = spacing;
        s32 pi = 1;
        s32 angle = 0;
        s32 ang_step = 0x5555;
        s32 ring = 1;
        s32 div = 3;
    ring_point:
        pts[pi].x = radius * sin_table_lookup(angle);
        pts[pi].y = 0.0f;
        pts[pi].z = radius * cos_table_lookup(angle);
        pi += 1;
        if (pi >= points) {
            goto ring_done;
        }
        angle += ang_step;
        if (angle <= 0x10000 - ang_step / 2) {
            goto ring_point;
        }
        div += 3;
        ang_step = 0x10000 / div;
        ring += 1;
        radius += spacing;
        angle = 0;
        if ((ring & 1) == 0) {
            goto ring_point;
        }
        angle = ang_step / 2;
        goto ring_point;
    ring_done:;
    }
    half = points / 2;
    if (half > 1) {
        for (i = 0; i < half; i++) {
            s32 a = TBoss6Type1__sub_802ABDEC(seed);
            s32 b;
            seed = TBoss6Type1__sub_802ABDEC(a);
            a = a % points;
            b = seed % points;
            if (a == b) {
                b = i + b;
                b += 1;
                b %= points;
            }
            Vec saved;
            __memcpy(&saved, &pts[a], sizeof(Vec));
            VecCopy(&pts[a], &pts[b]);
            VecCopy(&pts[b], &saved);
        }
    }
    self->m_4e0 = 0;
    made = 0;
    i = 0;
    while (made < count) {
        VecCopy(&spawn.point, &pts[i]);
        spawn.delay = step;
        seed = TBoss6Type1__sub_802ABDEC(seed);
        spawn.rng = seed;
        if (((TBoss6PlotFalz *)self->m_3f8)->get_next_point(&spawn.a0, &spawn.a6) == 0) {
            break;
        }
        if (TBoss6Mine::create(&spawn) == 0) {
            break;
        }
        made += 1;
        step = (made << 16) / count;
        i += 1;
        self->m_4e0 += 1;
    }
    delete[] pts;
    if (self->m_4e0 > 0) {
        play_sound_effect(0x4003B51B, &self->position, 0, 0);
    }
}

// Fires five kakusan shots from nodes {4, 3, 7, 5, 6}, each 46.25 further out.
extern "C" void TBoss6Type1__sub_802B6944(TBoss6Type1 *self) {
    u16 slot;
    s32 i;
    f32 radius;
    f32 lift;
    slot = self->m_41c & 3;
    lift = 5.0f * (self->m_41c & 3);
    radius = lbl_805DE37C;
    for (i = 0; i < 5; i++) {
        Boss6NodePos node = self->node_positions_578[lbl_80470F70[i]];
        Vec dir;
        f32 len;
        f32 scale;
        dir.x = radius * cos_table_lookup(-self->rotation.yaw);
        dir.y = lift;
        dir.z = radius * sin_table_lookup(-self->rotation.yaw);
        subtract_vector(&dir, &node.v);
        len = vector_length(&dir);
        if (len <= 1e-05f) {
            len = 1.0f;
            dir.x = 1.0f;
        }
        scale = lbl_805DE380 / len;
        dir.x *= scale;
        dir.y *= scale;
        dir.z *= scale;
        if (is_normal_difficulty() != 0) {
            TBoss6Type1::create_kakusan(self, &node.v, &dir, 0xFFFF, lbl_805DE380);
        } else {
            TBoss6Type1::create_kakusan(self, &node.v, &dir, slot, lbl_805DE380);
        }
        slot = (slot + 1) & 3;
        radius += lbl_805DE384;
    }
    play_sound_effect(0x4003A10B, &self->node_positions_578[7].v, 0, 0);
}

// Sword sweep: while anim set 14 is between 10.5 and 15, damage players inside the
// triangle position → m_4c8 → effect_points[1], then remember effect_points[1].
extern "C" void TBoss6Type1__sub_802B715C(TBoss6Type1 *self) {
    f32 t = self->anims[0].t;
    Boss6Motion *motion = self->anims[0].motion;
    Vec *tip = &self->effect_points[1];
    if (motion == get_bml_motion(self->m_3fc, TBoss6Type1__motion_set_table[14].ids[0]) &&
        !(t < lbl_805DE390) && !(t > 15.0f)) {
        f32 end = lbl_805DE390 + self->anims[0].speed;
        s32 n;
        s32 i;
        if (t >= lbl_805DE390 && t < end) {
            play_sound_effect(0x40038A0E, &self->effect_points[0], 0, 0);
        }
        self->update_effect_points();
        n = TLobby::get_game_mode();
        for (i = 0; i < n; i++) {
            Vec rel;
            Vec seg;
            Vec *chain[4];
            f32 cross_y[3];
            Vec c;
            s32 inside = 1;
            s32 k;
            TObjPlayer *p = TObjPlayer::get_player_data(i);
            if (is_active__14TBoss6PlotFalzFv() == 0) {
                continue;
            }
            chain[0] = chain[3] = &self->position;
            chain[1] = &self->m_4c8;
            chain[2] = tip;
            for (k = 0; k < 3; k++) {
                VecCopy(&seg, chain[k + 1]);
                subtract_vector(&seg, chain[k]);
                VecCopy(&rel, &p->position);
                subtract_vector(&rel, chain[k]);
                seg.y = 0.0f;
                rel.y = 0.0f;
                vec3_cross(&seg, &rel, &c);
                cross_y[k] = c.y;
                if (k > 0) {
                    f32 prev = cross_y[k - 1];
                    if ((prev < 0.0f && cross_y[k] >= 0.0f) || (prev > 0.0f && cross_y[k] <= 0.0f)) {
                        inside = 0;
                        break;
                    }
                }
            }
            if (inside != 0) {
                s32 r = TBoss6PlotFalz::rand_vary_count(self->unk_480, 0.1f);
                DirectAttackPayload payload;
                payload.kind = 0;
                payload.power = (f32)r;
                p->receive_direct_attack(self, payload, 0, -1, -1);
            }
        }
    }
    VecCopy(&self->m_4c8, tip);
}

void TBoss6Type1::spawn_grav_ball() {
    Vec v;
    s32 flag;
    TObjPlayer *pl;
    s8 b;
    s32 ang;
    f32 r;
    flag = 1;
    pl = get_player_by_client_id(this->m_41c & 3);
    if (is_active__14TBoss6PlotFalzFv() != 0) {
        VecCopy(&v, &pl->position);
        flag = 0;
        v.y = this->position.y;
    }
    b = this->m_41c;
    if (b & 0x40) {
        flag = 1;
    }
    if (flag != 0) {
        ang = (b & 0xF) << 12;
        r = 80.0f * ((f32)((b >> 3) & 0xF) / 15.0f) + 10.0f;
        VecCopy(&v, (&this->position));
        v.x += r * sin_table_lookup(ang);
        v.z += r * cos_table_lookup(ang);
    }
    TBoss6Type1::create_grav_ball(this, &v);
}
void TBoss6Type1::increase_field_clamped_max() {
    this->m_4dc += 1.0f / 30.0f;
    if (this->m_4dc > 1.0f) {
        this->m_4dc = 1.0f;
    }
}
void TBoss6Type1::decrease_field_clamped_min() {
    this->m_4dc += -2.0f / 15.0f;
    if (this->m_4dc < 0.0f) {
        this->m_4dc = 0.0f;
    }
}

void TBoss6Type1::reset_param() {
    this->m_4dc = 0.0f;
}
// Draws bml model 0 at sound_pos, turned to face the viewing player and scaled by m_4dc.
void TBoss6Type1__sub_802B626C(TBoss6Type1 *boss) {
    if (boss->m_4dc != 0.0f) {
        s32 fish = TObjFish__sub_8001EDB0(boss->m_3fc, 0);
        s32 model = get_bml_model(boss->m_3fc, 0);
        s32 pitch = 0;
        Vec pos = boss->node_positions_578[7].v;
        s32 yaw = boss->rotation.yaw + 0x8000;
        static f32 s_min_width = 0.15f;
        static f32 s_max_width = 0.625f;
        static f32 s_grow_end = 0.1f;
        f32 width = s_min_width;
        f32 height;
        if (boss->m_4dc < s_grow_end) {
            height = boss->m_4dc / s_grow_end;
        } else {
            width = (boss->m_4dc - s_grow_end) / (1.0f - s_grow_end) * (s_max_width - s_min_width) + s_min_width;
            height = 1.0f;
        }
        TObjPlayer *player = get_player_by_client_id(
            TCameraCtrl::get_split_screen_view_index(TCameraCtrl::get_camera_mode()));
        if (player != NULL) {
            Vec from;
            Vec to;
            VecCopy(&from, &boss->node_positions_578[7].v);
            VecCopy(&to, &player->position);
            to.y += 14.0f;
            subtract_vector(&to, &from);
            Vec flat = to;
            flat.y = 0.0f;
            pitch = (s32)(TBoss6Type1__data_80471038 * atan2_float(-to.y, vector_length(&flat)));
            if (pitch > 0x1000) {
                pitch = 0x1000;
            }
        }
        push_matrix();
        post_translate_matrix(&pos);
        rotate_matrix_y(0, yaw);
        rotate_matrix_x(0, pitch);
        rotate_matrix_z(0, 0);
        scale_matrix(0, width, 1.0f, height);
        set_current_texture_list((GinjaTextureList *)fish);
        draw_chunk_object((void *)model);
        pop_matrix();
    }
}
}


void TBoss6Type1::init_parts() { TBoss6Type1::set_part_default_value((int)this, &this->node_positions_578[8].v); TBoss6Type1::set_part_default_value((int)this, &this->node_positions_578[9].v); TBoss6Type1::set_part_default_value((int)this, &this->node_positions_578[10].v); this->update_trail_points(); }

void TBoss6Type1::update_trail_points() {
    Boss6EffectPoint points[7];
    Boss6EffectPoint delta;
    VecCopy(&points[0], &node_positions_578[8].v);
    VecCopy(&points[3], &node_positions_578[9].v);
    VecCopy(&delta, &node_positions_578[10].v);
    subtract_vector(&delta,&points[3]);
    f32 length=vector_length(&delta);
    if(length <= 1e-05f) length=1.0f;
    f32 scale=15.0f/length;
    delta.x*=scale;delta.y*=scale;delta.z*=scale;
    VecCopy(&points[1], &points[0]);
    VecCopy(&points[5], &points[0]);
    subtract_vector(&points[1],&delta);
    vec3_add_to(&points[5],&delta);
    VecCopy(&points[2], &points[1]);
    VecCopy(&points[4], &points[1]);
    subtract_vector(&points[2],&delta);
    vec3_add_to(&points[4],&delta);
    VecCopy(&points[6], &points[0]);
    ((TBoss6Type1 *)trail_point_receiver)->set_effect_points((f32 *)points, (u32 *)boss6_type1_trail_point_offsets);
}

void TBoss6Type1::update_effect_points() {
    Boss6EffectPoint points[2];
    VecCopy(&points[0], &effect_points[0]);
    VecCopy(&points[1], &effect_points[1]);
    TBoss6Type1::set_part_default_value((int)this, &points[1]);
    ((TBoss6Type1 *)effect_point_receiver)->set_effect_points((f32 *)points, (u32 *)lbl_80470FAC);
}

void TBoss6Type1::set_part_default_value(int a0, void* a1) {
    ((Boss6EffectPoint *)a1)->y = 10.0f;
}
extern "C" {


s32 TBoss6Type1__sub_802B6060(TBoss6Type1 *arg0) {
    return arg0->position.y > 100.0f;
}

s32 TBoss6Type1__sub_802B600C(TBoss6Type1 *arg0) {
    Vec v = arg0->position;
    v.y = 0.0f;
    return vector_length(&v) < 230.0f;
}

s32 TBoss6Type1__sub_802B5FF4(TBoss6Type1 *arg0) {
    return arg0->position.y > 140.0f;
}

s32 TBoss6Type1__sub_802B5FDC(TBoss6Type1 *arg0) {
    return arg0->position.y < 40.0f;
}

void TBoss6Type1::set_flag_on_threshold() {
    if ((this->m_4ac == 0) && (this->m_4d8 < 0.33333334f)) {
        this->m_4ac = 1;
    }
}

int TBoss6Type1::is_time_up() {
    if (this->m_414 == 0) {
        return 0;
    }
    return calc_field4b0_delta() >= this->unk_490 ? 1 : 0;
}

s32 TBoss6Type1::check_field4b0_threshold() {
    s32 temp_r31;
    temp_r31 = (s32) (this->m_4b4 * (f32) this->m_494);
    if (calc_field4b0_delta() >= temp_r31) {
        this->m_4b4 *= 1.5f;
        return 1;
    }
    return 0;
}

s32 TBoss6Type1::is_ready() {
    if ((this->m_414 == 0) && (calc_field4b0_delta() >= this->m_48c)) {
        return 1;
    }
    return 0;
}

int TBoss6Type1::is_field4b0_delta_reached() {
    return calc_field4b0_delta() >= this->unk_498 ? 1 : 0;
}
s32 TBoss6Type1::is_field3F8_over_0x20() {
    return TBoss6PlotFalz__sub_802AAC74((u8 *)this->m_3f8) > 0x20;
}

void TBoss6Type1::reset_fields_4e0() { this->m_4e0 = 0; this->unk_4e4 = 0; }

void TBoss6Type1__sub_802B5DD4(TBoss6Type1 *self) {
    if (self->m_4e0 <= 0 || self->unk_4e4 < 0) return;
    self->unk_4e4++;
}

u8 TBoss6Type1::is_timer_expired() {
    s32 temp_r0;
    s32 temp_r5;
    temp_r5 = this->m_4e0;
    if ((temp_r5 <= 0) || (temp_r0 = this->unk_4e4, ((temp_r0 < 0) != 0))) {
        return 1U;
    }
    return (u8) (temp_r5 <= temp_r0);
}

void TBoss6Type1::sub_802B5CB4() {
    switch (this->m_374) {
    case 1:
    case 2:
    case 4:
    case 24:
    case 25:
        TBoss6Type1__sub_802B5AB0(this);
        break;
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        TBoss6Type1__sub_802B5970(this);
        break;
    case 22:
        TBoss6Type1__sub_802B59CC(this);
        break;
    case 21:
        TBoss6Type1__sub_802B59A8(this);
        break;
    case 26:
        TBoss6Type1__sub_802B5AB0(this);
        break;
    case 30:
    case 31:
        TBoss6Type1__sub_802B5970(this);
        break;
    case 27:
        TBoss6Type1__sub_802B5970(this);
        break;
    case 32:
        TBoss6Type1__sub_802B5970(this);
        break;
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 34:
    case 35:
    case 36:
        this->request_default_jittered_camera();
        break;
    case 37:
        if (this->action_timer > (s32) ((f32) this->m_40c - 30.0f)) {
            this->request_default_jittered_camera();
            break;
        }
        break;
    default:
        TBoss6Type1::request_jittered_camera(this, NULL, NULL, 0xFFFF);
        break;
    }
}
void TBoss6Type1::fire_at_all_players(void *self, f32 dy) {
    Vec me;
    Vec pp;
    Vec ofs;
    Vec d;
    Vec out;
    s32 n;
    s32 i;
    TObjPlayer *p;
    f32 h;
    f32 dist;
    f32 a;
    f32 b;
    f32 c;

    n = TLobby::get_game_mode();
    VecCopy(&me, &((TBoss6Type1 *)self)->position);
    if (((TBoss6Type1 *)self)->m_438 != 0) {
        me.y -= dy;
    } else {
        me.y += dy;
    }
    for (i = 0; i < n; i++) {
        p = TObjPlayer::get_player_data(i);
        VecCopy(&ofs, &TBoss6Type1__data_80470FB4);
        if (p == 0) continue;
        VecCopy(&pp, &p->position);
        pp.y += ofs.y;
        VecCopy(&d, &me);
        subtract_vector(&d, &pp);
        h = d.y;
        d.y = 0.0f;
        dist = ofs.z + vector_length(&d);
        if (dist <= 1.0f) dist = 1.0f;
        out.x = 0.0f;
        out.z = 45.42f;
        out.y = 25.43f - h * out.z / dist;
        if (out.y < 5.0f) {
            out.y = 5.0f;
            if (h > 1e-5f) {
                a = 14.799999f * dist;
                out.z = a / h;
                if (out.z < 35.42f) {
                    b = 35.42f + dist;
                    out.z = 35.42f;
                    c = 35.42f * h - a;
                    if (fabs_float(b) > 1e-5f) {
                        a = c / b;
                        if (a > 10.0f) a = 10.0f;
                        ofs.y += a;
                    }
                }
            }
        }
        TBoss6Type1::request_jittered_camera(self, &ofs, &out, get_entity_id(p));
    }
}

void TBoss6Type1__sub_802B5AB0(TBoss6Type1 *self) {
    TBoss6Type1::fire_at_all_players(self, 80.0f);
}
void TBoss6Type1__sub_802B59CC(TBoss6Type1 *self) {
    Vec eye = TBoss6Type1__data_80470FB4;
    Vec target = lbl_80470FC0;
    f32 t = self->m_4dc;
    if (t > 0.0f) {
        eye.x += t * lbl_80470FCC.x;
        eye.y += t * lbl_80470FCC.y;
        eye.z += t * lbl_80470FCC.z;
        target.x += t * lbl_80470FD8.x;
        target.y += t * lbl_80470FD8.y;
        target.z += t * lbl_80470FD8.z;
    }
    TBoss6Type1::request_jittered_camera(self, &eye, &target, 0xFFFF);
}

void TBoss6Type1__sub_802B59A8(TBoss6Type1 *self) {
    TBoss6Type1::fire_at_all_players(self, 0.0f);
}
void TBoss6Type1__sub_802B5970(TBoss6Type1 *arg0) {
    TBoss6Type1::request_jittered_camera(arg0, &lbl_80470FE4, &lbl_80470FF0, 0xFFFF);
}

void TBoss6Type1::request_default_jittered_camera() {
    TBoss6Type1::request_jittered_camera(this, &lbl_80470FFC, &lbl_80471008, 0xFFFF);
}
s32 TBoss6Type1::request_jittered_camera(void *arg0, void *arg1, void *arg2, int arg3) {
    f32 dist;
    Vec off;
    if (arg1 == NULL) {
        arg1 = (void *)&TBoss6Type1__data_80470FB4;
    }
    if (arg2 == NULL) {
        arg2 = (void *)&lbl_80470FC0;
    }
    dist = 0.1f * xyz_distance(arg1, arg2);
    if (dist < 4.0f) {
        dist = 4.0f;
    }
    off.x = dist * ((1.0f / 32768.0f) * (f32)rand() - 0.5f);
    off.y = dist * ((1.0f / 32768.0f) * (f32)rand() - 0.5f);
    off.z = dist * ((1.0f / 32768.0f) * (f32)rand() - 0.5f);
    {
        Vec p = *(Vec *)arg1;
        vec3_add_to(&p, &off);
        request_follow_camera_offsets(&p, arg2, arg3);
    }
}

void TBoss6Type1::decode_polar_position(u8 *arg1) {
  const s8 *bytes = (const s8 *)this;
  Vec *out = (Vec *)arg1;
  f32 temp_f31;
  f32 temp_f30;
  s32 temp_r31;
  temp_r31 = bytes[0] << 8;
  temp_f31 = (f32) (bytes[1] * 0xA);
  temp_f30 = (f32) (bytes[2] * 0xA);
  out->x = (f32) (temp_f31 * sin_table_lookup(temp_r31));
  out->z = (f32) (temp_f31 * cos_table_lookup(temp_r31));
  out->y = temp_f30;
}

void TBoss6Type1::handle_6xa4_action(u8 * _w1) {
    // this points at OlgaFlowActionMsg::action; the polar bytes are the next three.
    struct ActionBytes { s8 action; s8 args[3]; };
    ActionBytes *bytes = (ActionBytes *)this;
    ((TBoss6Type1 *)bytes->args)->decode_polar_position(_w1);
}
void TBoss6Type1::calc_grid_cell_position(void *o_, void *out_) {
    TBoss6Type1 *o = (TBoss6Type1 *)o_;
    Vec *out = (Vec *)out_;
    u32 t = o->m_374;
    s8 b = o->m_41c;
    s32 sh = (t >> 1) & 3;
    s32 a = (b >> sh) & 0xF;
    s32 c = (b >> ((sh + 2) & 3)) & 0xF;
    if (t & 1) {
        a = ~a & 0xF;
        c = ~c & 0xF;
    }
    out->x = 7.9787235f * (f32)a - 63.82979f;
    out->y = o->position.y;
    out->z = 7.9787235f * (f32)c - 63.82979f;
}
void TBoss6Type1__sub_802B5598(TBoss6Type1 *self, Vec *out) {
    f32 var_f31;
    s32 temp_r31;
    s32 var_r4;
    u32 temp_r5;
    u32 var_r5;
    {
        s32 k = self->m_374 * 0x12D687;
        s8 c = self->m_41c;
        temp_r5 = c * k;
    }
    var_r4 = ((temp_r5 & 3) * 0x1800) + 0x2000;
    var_r5 = (temp_r5 >> 3U) & 1;
    if ((temp_r5 >> 2U) & 1) {
        var_r4 = -var_r4;
    }
    var_f31 = 180.0f;
    temp_r31 = self->rotation.yaw + var_r4;
    if ((s32) var_r5 != 0) {
        var_f31 = 280.0f;
    }
    out->x = (var_f31 * sin_table_lookup(temp_r31));
    out->y = (f32) 100.0f;
    out->z = (f32) (var_f31 * cos_table_lookup(temp_r31));
}

void TBoss6Type1::clamp_to_arena_radius(void *o_, void *out_, f32 _w2) {
    TBoss6Type1 *o = (TBoss6Type1 *)o_;
    Vec *out = (Vec *)out_;
    Vec v = o->position;
    f32 len;
    f32 s;
    v.y = 0.0f;
    len = vector_length(&v);
    if (len <= 1e-05f) {
        VecCopy((out), (&o->position));
        return;
    }
    s = 180.0f / len;
    v.x = v.x * s;
    v.z = v.z * s;
    out->x = v.x;
    out->y = 100.0f;
    out->z = v.z;
}

s32 TBoss6Type1::pick_remapped_list_value(s32 a, s32 b, s32 n) {
    s32 i;
    if (n > 0x20) {
        n = 0x20;
    }
    for (i = 0; i < n; i++) {
        s32 v = this->hist[i];
        if (v == a) {
            return b;
        }
        if (v == b) {
            return a;
        }
    }
    if ((1.0f / 32768.0f) * (f32)rand() < 0.5f) {
        return a;
    }
    return b;
}
int TBoss6Type1::rand_range_inclusive(s32 arg0, int arg1, int arg2) {
    if (arg1 >= arg2) {
        return arg1;
    }
    return (int) (((0.99f + ((f32) arg2 - (f32) arg1)) * ((1.0f / 32768.0f) * (f32) rand())) + (f32) arg1);
}

s32 TBoss6Type1::pick_random_entry(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_r0;
    var_r0 = (s32) (((f32) arg2 - 0.01f) * ((1.0f / 32768.0f) * (f32) rand()));
    if (var_r0 >= arg2) {
        var_r0 = 0;
    }
    return ((s32 *)arg1)[var_r0];
}

s32 TBoss6Type1::count_matches(s32 arg1, s32 arg2) {
    s32 i;
    s32 cnt;
    if (arg2 > 0x20) {
        arg2 = 0x20;
    }
    cnt = 0;
    for (i = 0; i < arg2; i++) {
        if (this->hist[i] == arg1) {
            cnt++;
        }
    }
    return cnt;
}

void TBoss6Type1__sub_802B5140(TBoss6Type1 *arg0, s32 arg1, s32 arg2) {
    Vec stack;
    f32 temp_f31;
    f32 var_f30;
    f32 var_f31;
    s32 temp_r31;
    var_f30 = 1.0f - ((f32) arg1 / (f32) arg2);
    if (var_f30 < 0.0f) {
        var_f30 = 0.0f;
    } else if (var_f30 > 1.0f) {
        var_f30 = 1.0f;
    }
    temp_r31 = (s32) (24576.0f * var_f30);
    temp_f31 = sin_table_lookup(0x6000);
    var_f31 = sin_table_lookup(temp_r31) / temp_f31;
    if (temp_r31 > 0x4000) {
        var_f31 += (1.0f - var_f31) * TBoss6PlotFalz::cosine_ease((var_f30 - 0.6666667f) / 0.3333333f);
    }
    VecCopy(&stack, &lbl_80470CE0);
    subtract_vector(&stack, &lbl_80470CD4);
    stack.x *= var_f31;
    stack.y *= var_f31;
    stack.z *= var_f31;
    vec3_add_to(&stack, &lbl_80470CD4);
    VecCopy(&arg0->position, &stack);
}
void TBoss6Type1::ease_toward_target(s32 a, s32 b) {
    s32 h = b / 2;
    if (b <= 0 || a <= h) return;
    this->position.y += 0.25f * (((-300.0f) + this->m_420.y) - this->position.y);
}
void TBoss6Type1::interpolate_pos_to_target(s32 step, s32 total) {
    Vec v;
    s32 a0;
    s32 a1;
    f32 r0;
    f32 r1;
    f32 t;
    f32 k;
    f32 r;
    s32 a;
    if (total <= 0) return;
    if (step <= 0) {
        VecCopy(&this->position, &this->m_420);
        return;
    }
    VecCopy(&v, &this->position);
    v.y = 0.0f;
    r0 = vector_length(&v);
    a0 = TBoss6Type1__data_80471038 * atan2_float(v.x, v.z);
    VecCopy(&v, &this->m_420);
    v.y = 0.0f;
    r1 = vector_length(&v);
    a1 = TBoss6Type1__data_80471038 * atan2_float(v.x, v.z);
    t = (f32)step / (f32)total;
    if (total <= 10 || t <= 0.1f) {
        k = 1.0f / (f32)step;
    } else {
        k = 2.0f * sin_table_lookup(32768.0f * t) / (f32)step;
    }
    r = k * (r1 - r0) + r0;
    a = k * (f32)angle_diff_s16(a0, a1) + (f32)a0;
    this->position.x = r * sin_table_lookup(a);
    this->position.z = r * cos_table_lookup(a);
    this->position.y += k * (this->m_420.y - this->position.y);
}

void TBoss6Type1::rotate_around_center(s32 num, s32 den) {
    Vec v;
    f32 dist;
    s32 angle;
    s32 off;
    if (den <= 0 || num <= 0) {
        return;
    }
    {
    {
        VecCopy(&v, &this->position);
        v.y = 0.0f;
        dist = vector_length(&v);
        angle = (s32)(TBoss6Type1__data_80471038 * atan2_float(v.x, v.z));
        off = (s32)(40960.0f * sin_table_lookup((s32)(32768.0f * ((f32)num / (f32)den))) / (f32)num);
        if (this->m_41c & 1) {
            off *= -1;
        }
        angle += off;
        this->position.x = dist * sin_table_lookup(angle);
        this->position.z = dist * cos_table_lookup(angle);
        }
    }
}

void TBoss6Type1__sub_802B4D38(TBoss6Type1 *self) {
    s32 i;
    for (i = 0; i < 4; i++) self->effect_slots[i] = 0;
}

void TBoss6Type1__sub_802B4CF4(TBoss6Type1 *arg0) {
    s32 var_r31;
    var_r31 = 0;
    do {
        arg0->release_effect_slot(var_r31);
        var_r31 += 1;
    } while (var_r31 < 4);
}
void TBoss6Type1::sub_802B4C28() {
    s32 i;
    EffectSlotEntry *t = TBoss6Type1__effect_slot_table;
    for (i = 0; i < 4; i++) {
        Vec v = this->position;
        EffectSlotEntry *e = &t[i];
        if (this->effect_slots[i] != 0) {
            s32 k = e->b;
            if (k >= 0) {
                VecCopy(&v, &this->node_positions_578[k].v);
            }
            ((TParticleCtrl *)this->effect_slots[i])->set_position(&v);
            switch (i) {
            case 0:
            case 1:
                ((TParticleCtrl *)(this->effect_slots[i]))->set_direction(lbl_80471014);
                break;
            }
        }
    }
}

void TBoss6Type1::spawn_effect_slot(s32 arg1) {
    if (this->effect_slots[arg1] == 0U) {
        Vec v = this->position;
        this->effect_slots[arg1] = (u32)create_particle_emitter(&v, TBoss6Type1__effect_slot_table[arg1].a);
        if (this->effect_slots[arg1] != 0U) {
            ((TParticleCtrl *)this->effect_slots[arg1])->set_flags(0x40);
        }
    }
}
void TBoss6Type1::release_effect_slot(s32 arg1) {
    if (this->effect_slots[arg1] != 0U) {
        TParticleCtrl::release((void *)this->effect_slots[arg1]);
        this->effect_slots[arg1] = 0U;
    }
}

void TBoss6Type1::clear_slot_array() {
    s32 i;
    this->m_508 = 0;
    for (i = 0; i < lbl_805DE2D4; i++) this->unk_50C[i] = 0;
}

void TBoss6Type1__sub_802B4B14(TBoss6Type1 *p) { TBoss6Type1__sub_802B4A9C(p); }

void TBoss6Type1__sub_802B4B04(TBoss6Type1 *self) {
    self->m_508 = self->m_508 + 1;
}

void TBoss6Type1__sub_802B4A9C(TBoss6Type1 *boss) {
    s32 i;
    boss->m_508 = 0;
    for (i = 0; i < lbl_805DE2D4; i++) {
        u32 slot = boss->unk_50C[i];
        if (slot != 0U) {
            TParticleCtrl::release((void *)slot);
            boss->unk_50C[i] = 0;
        }
    }
}
void TBoss6Type1__sub_802B4A90(TBoss6Type1 *p) { p->map_csn = 0; }

void TBoss6Type1__sub_802B4A70(void* p) { TBoss6Type1::release_object(p); }

void TBoss6Type1::spawn_map_csn() {
    MapCsnSetData data;
    Vec offset;
    VecCopy(&data.position, &position);
    push_matrix();
    set_matrix_identity(0);
    rotate_matrix_y(0, rotation.yaw);
    rotate_vector_by_matrix(0, &boss6_map_csn_offset, &offset);
    data.position.x += offset.x;
    data.position.y = 0.0f;
    data.position.z += offset.z;
    pop_matrix();
    data.rotation_x = 0;
    data.rotation_y = rotation.yaw;
    data.rotation_z = 0;
    VecCopy(&data.scale, &boss6_map_csn_scale);
    data.params[0] = 2;
    data.params[1] = 0;
    map_csn = (TObject *)TObjMapCsn::create((s32)&data);
}

void TBoss6Type1::release_object(void *p) {
    TBoss6Type1 *self = (TBoss6Type1 *)p;
    if (self->map_csn != 0) {
        self->map_csn->queue_destruction();
        self->map_csn = 0;
    }
}

void TBoss6Type1::render() {
    draw_model();
    TBoss6Type1__sub_802B626C(this);
}

void TBoss6Type1::draw_model() {
    TObjPlayer::toggle_particle_effect();
    push_matrix();
    Vec pos = *&position;
    pos.y = pos.y + m_4e8;
    post_translate_matrix(&pos);
    rotate_matrix_y(0, rotation.yaw);
    rotate_matrix_x(0, rotation.pitch);
    TBoss6PlotFalz__sub_802AC008(m_4d4, m_4d8);
    draw_part_motions();
    TBoss6PlotFalz::update_camera_target();
    pop_matrix();
    TParticleCtrl::end_effect_render();
}
}

