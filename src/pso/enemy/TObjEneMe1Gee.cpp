#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/math/FloatRounding.h"
#include "pso/misc/PositionSoundEffects.h"
#include "pso/player/demo_mode.h"
#include "pso/misc/MaterialOpacityFade.h"
#include "pso/enemy/BattleParameters.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/system/EnemyBmlResource.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/enemy/TObjEneRe7Berura_803E4CE0.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/system/vector.h"
#include "pso/system/NinjaTypes.h"
#include "types.h"
#include "pso/system/NinjaUtil.h"
#include "pso/misc/TBreakUpMdl.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/enemy/TObjEneDD_ST.h"
#include "pso/enemy/PlayerTargetCandidate.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjChara.h"
#include "pso/enemy/TUnk_8049387C.h"
#include "pso/object/TObjMotion.h"
#include "pso/enemy/TObjEneMe1Gee.h"
#include "pso/enemy/TObjEneMe1Gee_802A4BB8.h"
#include "pso/map/FloorArea.h"
#include "pso/system/MatrixOps.h"
#include "pso/math/AngleLookup.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/math/ViewPoint.h"
#include "pso/system/BmlResource.h"
#include "pso/system/SoundEffect.h"
#include "pso/misc/TOTrapAncient01_80226534.h"
#include "pso/player/TObjPlayer_800F0810.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/enemy/TObjEnemyCustom.h"
class TObjEneMe1Gee_NEEDLE;
#include "pso/object/TObjMotion.h"
#include "pso/TObject.h"
#include "pso/TParticleCtrl.h"
#include "pso/boss/TBoss3Volopt.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/boss/TObjBoss2Tunnel.h"

#include "pso/enemy/TObjEneRe7Berura.h"
#include "pso/object/TObjFish.h"

extern "C" {
BmlResource *TObjEneMe1Gee__resource_bundle;
NJS_OBJECT *gee_cached_model_node;
s32 TObjEneMe1Gee__render_node_index;
Vec *gee_camera_ctrl_step_ptr;
TUnk_8048FA00 *gee_swarm_breakup_model;
TUnk_8048FA00 *gee_breakup_model;
u32 *gee_model_packed_color;
s32 create_breakup_mdl__12TBoss3VoloptFlllll(s32, s32, s32, void *, s32);
void queue_destruction__7TObjectFv(void *arg0);
void * __nw__7TObjectFUl(u32);
extern const NJS_ARGB TObjEneMe1Gee__data_8043BDB0;
extern const char *lbl_805D2A68;
extern "C" void vfunc_28__13TObjEneMe1GeeFv();
extern "C" void vfunc_61__13TObjEneMe1GeeFv();

extern "C" void vfunc_113__13TUnk_8049387CFv();
extern "C" const char lbl_8043BD08[];
extern "C" const char lbl_8043BD14[];
extern "C" const char lbl_8043BD24[];
extern "C" const char lbl_8043BD38[];
extern "C" const char lbl_8043BD4C[];
extern "C" const char lbl_8043BD60[];
extern "C" const char lbl_8043BD74[];
extern "C" const char lbl_8043BD88[];
extern "C" const char lbl_8043BD98[];
extern "C" const char lbl_8043BDE0[];
extern "C" const char lbl_8043BDFC[];
extern "C" const char lbl_8043BE08[];
extern "C" const char lbl_8043BE28[];
extern "C" const char lbl_8043BE38[];
struct GeeMovementParameters {
    EnemyMoveParams movement;
    u32 unknown0C[4];
};

GeeMovementParameters me1_gee_init_params[1] = {
    { { 225.0f, 0.0f, 0x600 }, { 0, 0, 0, 0 } },
};
CollisionBody gee_collision_template[1] = {
    { { 0.0f, 0.0f, 0.0f }, 8.0f, 0.0f, 0, 0x8003,
      { 0.0f, 0.0f, 0.0f }, 0.0f },
};
const char *bm_ene_me1_gee_model_names[3] = {
    lbl_8043BD08, lbl_8043BD14, NULL,
};
const char *bm_ene_me1_gee_motion_names[5] = {
    lbl_8043BD24, lbl_8043BD38, lbl_8043BD4C, lbl_8043BD60, NULL,
};
BmlResourceDescriptor bm_ene_me1_gee_resource_descriptor = {
    lbl_8043BD74, bm_ene_me1_gee_model_names, bm_ene_me1_gee_motion_names, 2, 4,
};
const char *bm_ene_me1_gee_low_model_names[3] = {
    lbl_8043BD88, lbl_8043BD14, NULL,
};
const char *bm_ene_me1_gee_low_motion_names[5] = {
    lbl_8043BD24, lbl_8043BD38, lbl_8043BD4C, lbl_8043BD60, NULL,
};
BmlResourceDescriptor bm_ene_me1_gee_low_resource_descriptor = {
    lbl_8043BD98, bm_ene_me1_gee_low_model_names, bm_ene_me1_gee_low_motion_names, 2, 4,
};
TObjMotionAction gee_actions[4] = {
    { MOTION_MODE_LOOP, 0, 3, 0.9f, 0 },
    { MOTION_MODE_CHAIN, 0, 2, 1.0f, 0 },
    { MOTION_MODE_CHAIN, 0, 0, 1.0f, 0 },
    { MOTION_MODE_CHAIN, 0, 1, 0.8f, 0 },
};
const char *gee_color_sequences[5] = {
    lbl_8043BDE0, lbl_8043BDFC, lbl_8043BE08, lbl_8043BE28, lbl_8043BE38,
};

static BattleBaseStats *gee_base_stats[3];
static AttackParams *gee_attack_params[3];
static ActorParamBlock *gee_resistance_params[3];
static BattleMovementParams *gee_movement_params[3];
static Vec gee_camera_ctrl_vec;


s32 transition_enemy_state__9TObjEneDDFl(void *, s32);
extern const f32 TObjEneMe1Gee__data_805DA0A8;
extern const f32 lbl_805DA0AC;

void vfunc_113__13TUnk_8049387CFv(void);

}

extern "C" {

}

#include <stddef.h>

extern "C" {
s32 VecCopy__FP3VecPC3Vec(void *, void *);
extern const f32 TObjEneMe1Gee__data_805DA0B4;
extern const f32 TObjEneMe1Gee__data_805DA0C8;
extern const f32 TObjEneMe1Gee__data_805DA0D4;
extern const f32 TObjEneMe1Gee__data_805DA0E8;
extern const f32 lbl_805DA0B0;
f64 atan2_float(f32, f32);
void rotate_xz_pair_by_angle(f32 *arg0, f32 *arg1, s32 arg2);
extern const f64 lbl_8043BF28;
extern const f32 lbl_805DA0F0;
extern const f32 lbl_805DA0F4;
extern const f32 lbl_805DA0F8;
extern const f32 lbl_805DA0FC;
void TObjEneEpsilon__sub_800B92F8(u8 *arg0, s32 arg1, f32 farg0);

void matrix_mult_vec(void *, Vec *, Vec *);
s32 rotate_matrix_y(int, int);
s32 push_matrix_from(void *src);
s32 pop_matrix();
s32 post_translate_matrix(void *);
extern const NJS_ARGB TObjEneMe1Gee__data_8043BDC0;
extern const Vec lbl_8043BE7C;
extern const f32 lbl_805DA124;
s16 get_entity_id(void *);
s32 initialize_enemy_state__9TObjEneDDFl(void *, int);
s32 set_part_position__9TObjEneDDFPvPvi(void *, int, int);
s32 rand(f32);
extern const f32 lbl_805DA0B8;
extern const f32 TObjEneMe1Gee__data_805DA0C0;
extern const f32 lbl_805DA148;
extern const f32 lbl_805DA14C;
extern "C" const char lbl_8043BD08[];
extern "C" const char lbl_8043BD14[];
extern "C" const char lbl_8043BD24[];
extern "C" const char lbl_8043BD38[];
extern "C" const char lbl_8043BD4C[];
extern "C" const char lbl_8043BD60[];
extern "C" const char lbl_8043BD74[];
extern "C" const char lbl_8043BD88[];
extern "C" const char lbl_8043BD98[];
}

extern "C" {



typedef struct Gee_800CBB34 {
    u8 pad0[0x390];
    void *target;
    u8 pad394[0x3C0 - 0x394];
    TObjEneMe1Gee *owner;
    u8 pad3C4[0x48C - 0x3C4];
    u16 ownerIdx;
} Gee_800CBB34;

f32 newton_sqrtf(f32);
s32 set_target_player__12TObjEneDD_STFPv();
void translate_matrix(u32 arg0, f32 x, f32 y, f32 z);
extern s32 saved_model_render_flags;
extern s32 model_render_flags;
extern const f32 lbl_805D9E84;
extern const f32 lbl_805D9E88;
// Legacy collector ABI remains pending its independently reviewed shared signature.
s32 collect_enemy_target_candidates(void *, PlayerTargetCandidate *);
s32 pack_debug_text_position(s32, s32);
s32 find_attack_target__13TObjEneMe1GeeFPvPv(Gee_800CBB34 *arg0, f32 *out);
void vfunc_61__13TObjEneMe1GeeFv(void);
void vfunc_28__13TObjEneMe1GeeFv(void);
s32 approach_angle_limited(s32, s32, s32);
void *get_player_by_client_id(s32 i);
s32 push_matrix();
void draw_chunk_object(void *child);

extern const f32 TObjEneMe1Gee__data_805DA0EC;
extern const NJS_ARGB lbl_8043BDD0;
extern s32 lbl_8043BE98[];
extern s32 lbl_8043BEA8[];
extern s32 lbl_8043BEBC[];
extern s32 lbl_8043BEC8[];
extern s32 lbl_8043BED8[];
extern s32 lbl_8043BEEC[];
extern s32 lbl_8043BF0C[];
extern const f32 lbl_805DA0BC;
extern const f32 lbl_805DA0C4;
extern const f32 lbl_805DA0CC;
extern const f32 lbl_805DA0D0;
extern const f32 lbl_805DA110;
extern const f32 lbl_805DA128;
extern const f32 lbl_805DA130;
extern const f32 lbl_805DA134;
extern const f32 lbl_805DA138;
extern const f32 lbl_805DA13C;
extern const f32 lbl_805DA140;
extern const f32 lbl_805DA144;

extern "C" {
void TObjEneEpsilon__sub_800B92AC(u8 *arg0, s32 arg1, f32 farg0);
extern const DirectAttackPayload lbl_8043BE88;
extern const f32 lbl_805DA100;
extern const f32 lbl_805DA104;
extern const f32 lbl_805DA108;
extern const f32 lbl_805DA10C;
extern const f32 lbl_805DA114;
extern const f32 lbl_805DA118;
extern const f32 lbl_805DA11C;
extern const f32 lbl_805DA120;

}

extern "C" {
extern const f32 lbl_805DA12C;

}

}

extern "C" {
void TObjEneMe1Gee__sub_802A4D4C(void);

extern TObject *tl_04;

}

#include "pso/misc/TLobby.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/npc/NpcModelRegistry.h"
#include "pso/npc/NpcAnimationBinding.h"

extern "C" {
s32 is_split_screen();
s32 init_from_model__11TBreakUpMdlFl(s32, s32);
extern const s32 lbl_8043BCD8[3];
extern const s32 lbl_8043BCE4[3];
extern const s32 lbl_8043BCF0[3];
extern const s32 lbl_8043BCFC[3];
extern const NpcAnimationBinding lbl_8043BE6C;
extern const f32 lbl_805DA150;

}

// This unit uses the repository's deferred compiler profile. Definitions are
// in reverse emission order so native vtables, switch tables and code retain
// their original addresses. See the per-file exception in configure.py.
#pragma fp_contract reset
#pragma opt_common_subs reset
#pragma opt_loop_invariants reset
#pragma opt_propagation reset

extern "C" {

void TObjEneMe1Gee::load_resources() {
    s32 i;
    s32 p;
    s32 t;
    Vec *v;
    v = &gee_camera_ctrl_vec;
    v->x = TObjEneMe1Gee__data_805DA0B4;
    v->y = TObjEneMe1Gee__data_805DA0B4;
    v->z = TObjEneMe1Gee__data_805DA0B4;
    if (((s32 (*)(void *))is_split_screen)(v) != 0) {
        TObjEneMe1Gee__resource_bundle = load_enemy_bml_resource(&bm_ene_me1_gee_low_resource_descriptor);
    } else {
        TObjEneMe1Gee__resource_bundle = load_enemy_bml_resource(&bm_ene_me1_gee_resource_descriptor);
    }
    TObjEneMe1Gee::cache_result_805D6660();
    gee_cached_model_node = (NJS_OBJECT *)find_model_node(TObjEneMe1Gee__resource_bundle->models->model, 7);
    for (i = 0; i < 3; i++) {
        gee_base_stats[i] = get_battle_base_stats(lbl_8043BCD8[i]);
        gee_attack_params[i] = get_battle_attack_params(lbl_8043BCE4[i]);
        gee_resistance_params[i] = get_battle_resistance_params(lbl_8043BCF0[i]);
        gee_movement_params[i] = get_battle_movement_params(lbl_8043BCFC[i]);
    }
    TObjEneMe1Gee__render_node_index = 0;
    p = (int)::operator new(0x10);
    if (p != 0) {
        p = init_from_model__11TBreakUpMdlFl(p, TObjEneMe1Gee__resource_bundle->models->model);
    }
    gee_swarm_breakup_model = (TUnk_8048FA00 *)p;
    p = (int)::operator new(0x10);
    if (p != 0) {
        p = init_from_model__11TBreakUpMdlFl(p, TObjEneMe1Gee__resource_bundle->models->model);
    }
    gee_breakup_model = (TUnk_8048FA00 *)p;
    t = *(s32 *)((s8 *)(*(u8 **)((s8 *)(find_model_node(TObjEneMe1Gee__resource_bundle->models->model, 4)) + 4)) + 4);
    gee_model_packed_color = (u32 *)(t + 4);
    TObjPlayer__sub_800F0928();
    {
        NpcAnimationBinding sp8 = lbl_8043BE6C;
        sp8.motions = TObjEneMe1Gee__resource_bundle->motions;
        NpcModelRegistry::register_animated_chunk((s16)0x10, (void *)TObjEneMe1Gee__resource_bundle->models->model, (void *)TObjEneMe1Gee__resource_bundle->models->m_c, &sp8, lbl_805DA150, TObjEneMe1Gee__data_805DA0C0);
    }
}

void *TObjEneMe1Gee::create(void *set_data) {
    return new TObjEneMe1Gee(tl_04, set_data, 0);
}

TObjEneMe1Gee *TObjEneMe1Gee::create_child(TObjEneMe1Gee *leader,
        const Vec *initial_position, u16 child_id, s32 child_index) {
    return new TObjEneMe1Gee(tl_04, leader, initial_position, child_id, child_index);
}

void TObjEneMe1Gee::free_globals() {
    if (gee_breakup_model != NULL) {
        delete gee_breakup_model;
        gee_breakup_model = NULL;
    }
    if (gee_swarm_breakup_model != NULL) {
        delete gee_swarm_breakup_model;
        gee_swarm_breakup_model = NULL;
    }
    if (TObjEneMe1Gee__resource_bundle != NULL) {
        delete TObjEneMe1Gee__resource_bundle;
        TObjEneMe1Gee__resource_bundle = NULL;
    }
    TObjEneMe1Gee__sub_802A4D4C();
}

TObjEneMe1Gee::TObjEneMe1Gee(TObject *parent, void *set_data, s32 actor_role)
    : TObjEneDD_ST(parent) {
    m_name = lbl_805D2A68;
    invoke_initialization_hook(set_data);
    gee_flags = 0;
    apply_behavior_parameters();
    leader = this;
    role = actor_role;
    init_state();
}

TObjEneMe1Gee::TObjEneMe1Gee(TObject *parent, TObjEneMe1Gee *swarm_leader,
        const Vec *initial_position, u16 child_id, s32 child_index)
    : TObjEneDD_ST(parent) {
    m_name = lbl_805D2A68;
    leader = swarm_leader;
    init_common_from((u8 *)leader);
    entity_id = child_id;
    set_index = child_index;
    random_child_position(leader, &position);
    VecCopy(&position, initial_position);
    rotation_y = leader->rotation_y;
    gee_flags = 0;
    role = 1;
    init_state();
}

#pragma push
#pragma fp_contract on
#pragma opt_loop_invariants off
#define copy_argb ((int (*)(void *, void *))copy_argb)
void TObjEneMe1Gee::init_state() {
    s32 temp_r0;
    s32 i;
    s32 var_r30;
    u8 *temp_r4;
    this->init_position_vectors();
    this->vfunc_106();
    this->init_model(gee_collision_template, 1);
    set_action_table(gee_actions);
    set_motion_list(TObjEneMe1Gee__resource_bundle->motions);
    this->requested_action = 0;
    set_animation((this->requested_action));
    this->set_field_b8((int) (this->requested_action));
    reset_hp(gee_base_stats[role], gee_attack_params[role], gee_resistance_params[role]);
    this->check_state_flag_1();
    movementParameters = me1_gee_init_params;
    initialize_enemy_state__9TObjEneDDFl(this, 0x36);
    m_37c = lbl_805DA0B8;
    this->enemy_init_acquire_period(0x2D);
    this->enemy_init_validate_period(0x2D);
    this->set_active();
    this->actorFlags = (s32) (this->actorFlags | 0x01000000);
    gee_parameters = (GeeParameters *)gee_movement_params[role];
    this->fade.reset_color();
    this->attack_height = (f32) lbl_805DA148;
    this->hover_height = (f32) TObjEneMe1Gee__data_805DA0C0;
    this->alternate_height = (f32) ((TObjEneMe1Gee__data_805DA0C8 * (lbl_805DA14C * (f32) rand(lbl_805DA148))) + TObjEneMe1Gee__data_805DA0C0);
    this->model_height = (f32) this->hover_height;
    this->world_height = (f32) (this->position.y + this->model_height);
    this->activation_delay = 0;
    this->attack_count = 0;
    this->field_40C = 0;
    this->alternate_model_index = 0;
    for (i = 0; i < 2; i++) {
        VecCopy(&node_positions[i], &position);
    }
    this->attack_cycle = 0;
    this->state_step = 0;
    this->state_timer = 0;
    this->state_count = 0;
    this->field_440 = 0;
    this->rotation_step = 0;
    this->field_448 = (f32) TObjEneMe1Gee__data_805DA0B4;
    this->field_44C = (f32) TObjEneMe1Gee__data_805DA0B4;
    this->field_450 = (f32) TObjEneMe1Gee__data_805DA0B4;
    this->attack_destination.x = (f32) TObjEneMe1Gee__data_805DA0B4;
    this->attack_destination.y = (f32) TObjEneMe1Gee__data_805DA0B4;
    this->attack_destination.z = (f32) TObjEneMe1Gee__data_805DA0B4;
    this->effect_460 = NULL;
    this->effect_464 = NULL;
    copy_argb(&color, (void *)((void *) (((u8 *)&TObjEneMe1Gee__data_8043BDC0))));
    color.a = TObjEneMe1Gee__data_805DA0B4;
    this->color_sequence = 0;
    this->packed_color = 0;
    this->color_script = 0;
    this->color_timer = 0;
    this->color_cursor = 0;
    this->sync_body_position();
    set_part_position__9TObjEneDDFPvPvi(this, (int) (*(s32 *)((s8 *)this + 0xA4)), 0);
    this->mode = 0;
    dispatch_action(this->mode, 4);
    if (this->leader != NULL) {
        this->leader_id = get_entity_id(this->leader);
        return;
    }
    this->leader_id = 0xFFFF;
}
#undef copy_argb
#pragma pop

TObjEneMe1Gee::~TObjEneMe1Gee() {
    if (effect_464 != NULL) {
        effect_464->queue_destruction();
        effect_464 = NULL;
    }
    free_collision_body_parts(this);
}

void TObjEneMe1Gee::run_task() {
    TObjEneMe1Gee *object;
    if (check_demo_mode() != 0) {
        vfunc_114();
        return;
    }
    if (role == 1 && ((leader = (TObjEneMe1Gee *)find_entity_by_id(leader_id), object = leader, object == NULL) || object->all_parents_unqueued_for_destruction() == 0)) {
        queue_destruction();
        return;
    }
    if (vfunc_83() != 4) {
        vfunc_85();
        update_fade_sequence();
    }
    sync_body_position();
    submit_default_cursor_candidate();
    vfunc_100();
}

BmlResource *TObjEneMe1Gee::get_resources() { return TObjEneMe1Gee__resource_bundle; }

void TObjEneMe1Gee::vfunc_28() {  }

void TObjEneMe1Gee::vfunc_63() {
        s16 temp_r0;
    temp_r0 = this->mode;
    if ((temp_r0 != 0xE) && (temp_r0 != 0xC)) {
        transition_enemy_state(0xE);
    }
}

void TObjEneMe1Gee::vfunc_62() { if (this->mode != 13) { transition_enemy_state(13); } }

void TObjEneMe1Gee::vfunc_61() {  }

void TObjEneMe1Gee::sync_body_position() {
    body_center_position.x = position.x;
    body_center_position.y = world_height;
    body_center_position.z = position.z;
    VecCopy(&center, &body_center_position);
}

void TObjEneMe1Gee::vfunc_88() {
    this->model_height = (f32) (this->world_height - this->position.y);
    if (this->model_height < TObjEneMe1Gee__data_805DA0E8) {
        vfunc_98();
    } else {
        vfunc_97();
    }
    bodies[0].offset.y = (f32) this->model_height;
}

#pragma push
#pragma opt_common_subs off
void TObjEneMe1Gee::apply_behavior_parameters() {
        if ((s32) floor_to_float((f32) (this->parameters[0])) == 0) {
        this->set_in_fighter();
    } else {
        this->set_out_fighter();
    }
    if ((s32) floor_to_float((f32) (this->parameters[1])) == 0) {
        this->set_low_appearance();
    } else {
        this->set_high_appearance();
    }
    this->needle_speed = (f32) (lbl_805DA140 + this->parameters[3]);
    if (this->needle_speed < lbl_805DA144) {
        this->needle_speed = (f32) lbl_805DA144;
    }
    this->height_step = (f32) (TObjEneMe1Gee__data_805DA0EC + this->parameters[2]);
    if (this->height_step < TObjEneMe1Gee__data_805DA0EC) {
        this->height_step = (f32) TObjEneMe1Gee__data_805DA0EC;
    }
}
#pragma pop

void TObjEneMe1Gee::vfunc_106() {
    model = (void *)TObjEneMe1Gee__resource_bundle->models->model;
    texlist = TObjEneMe1Gee__resource_bundle->models->m_c;
}

#pragma push
#pragma fp_contract on
void TObjEneMe1Gee::random_child_position(TObjEneMe1Gee *actor, Vec *result) {
    f32 temp_f1;
    f32 temp_f31;
    s32 random_scaled;

    random_scaled = actor->get_random_scaled();
    f32 fv = actor->random_ratio();
    temp_f31 = (TObjEneMe1Gee__data_805DA0E8 * fv) + lbl_805DA0B8;
    temp_f1 = temp_f31 * sin_table_lookup(random_scaled);
    result->x = temp_f1;
    result->y = TObjEneMe1Gee__data_805DA0B4;
    result->z = temp_f31 * cos_table_lookup(random_scaled);
    vec3_add_to(result, &actor->position);
}
#pragma pop

u8 *TObjEneMe1Gee::vfunc_101(u8 *destination) {
    u8 *result = TObjEneDD::vfunc_101(destination);
    if (result == NULL) {
        gee_flags &= ~0x01000000;
        return result;
    }
    gee_flags |= 0x01000000;
    return result;
}

void TObjEneMe1Gee::sub_800CBF58(f32 farg0) {
        f32 temp_f3;
    temp_f3 = farg0 - this->world_height;
    this->gee_flags &= 0xFFF7FFFF;
    if (temp_f3 >= TObjEneMe1Gee__data_805DA0D4) {
        this->world_height = (f32) (this->world_height + TObjEneMe1Gee__data_805DA0D4);
        return;
    }
    if (temp_f3 <= lbl_805DA13C) {
        this->world_height = (f32) (this->world_height - TObjEneMe1Gee__data_805DA0D4);
        return;
    }
    this->world_height = farg0;
    this->gee_flags |= 0x80000;
}

void TObjEneMe1Gee::approach_world_height(f32 target_height) {
    f32 difference = target_height - world_height;
    gee_flags &= ~0x80000;
    if (difference >= height_step) {
        world_height += height_step;
    } else if (difference <= -height_step) {
        world_height -= height_step;
    } else {
        world_height = target_height;
        gee_flags |= 0x80000;
    }
}

void TObjEneMe1Gee::set_move_speed_x() {
    sub_800CBF58(this->position.y + this->attack_height);
}

void TObjEneMe1Gee::fn_800CBE6C(f32 target_height) {
    Vec proposed_position;
    sub_800CBF58(target_height);
    VecCopy(&proposed_position, &position);
    proposed_position.y = world_height;
    vfunc_101((u8 *)&proposed_position);
}

void TObjEneMe1Gee::update_hover_height() {
    fn_800CBE6C(this->hover_height + this->position.y);
}

void TObjEneMe1Gee::update_animation_frame() {
    fn_800CBE6C(this->attack_height + this->position.y);
}

void TObjEneMe1Gee::fn_800CBDBC(f32 target_height) {
    Vec proposed_position;
    approach_world_height(target_height);
    VecCopy(&proposed_position, &position);
    proposed_position.y = world_height;
    vfunc_101((u8 *)&proposed_position);
}

void TObjEneMe1Gee::update_from_float_sum() {
    fn_800CBDBC(this->hover_height + this->position.y);
}

void TObjEneMe1Gee::update_angle() {
    this->rotation_y = approach_angle_limited(this->rotation_y, (s32) (lbl_8043BF28 * atan2_float(this->target_direction.x, this->target_direction.z)), 0x400);
    this->rotation_y = (s32) (s16) this->rotation_y;
}

void TObjEneMe1Gee::update() { if (this->enemy_has_live_target() != 0) { this->enemy_copy_target_destination(); this->update_velocity(); this->update_angle(); } }

void TObjEneMe1Gee::vfunc_105() {
    u8 *arg0 = (u8 *)this;
        if (this->gee_flags & IN_FIGHTER) {
        ((s32 (*)(void *, int))transition_enemy_state__9TObjEneDDFl)(arg0, 8);
        return;
    }
    if ((s32) this->role == 0) {
        if ((s32) this->attack_cycle < 2) {
            ((s32 (*)(void *, int))transition_enemy_state__9TObjEneDDFl)(arg0, 7);
            this->attack_cycle = (s32) (this->attack_cycle + 1);
            return;
        }
        ((s32 (*)(void *, int))transition_enemy_state__9TObjEneDDFl)(arg0, 8);
        this->attack_cycle = 0;
        return;
    }
    ((s32 (*)(void *, int))transition_enemy_state__9TObjEneDDFl)(arg0, 7);
}

void TObjEneMe1Gee::vfunc_89() { TObjEneDD::vfunc_89(); }

void TObjEneMe1Gee::enable_attack_body() {
    bodies[0].flags |= 0x28;
}

void TObjEneMe1Gee::disable_attack_body() {
    bodies[0].flags &= ~0x28;
}

s32 find_attack_target__13TObjEneMe1GeeFPvPv(Gee_800CBB34 *arg0, f32 *out) {
    PlayerTargetCandidate recs[5];
    s32 found;
    s32 n;
    void *p;
    s32 i;
    found = 0;
    *out = lbl_805DA110;
    n = collect_enemy_target_candidates(arg0, recs);
    for (i = 0; i < n; i++) {
        p = get_player_by_client_id(recs[i].id);
        if (p != arg0->target) {
            arg0->owner = (TObjEneMe1Gee *)find_entity_by_id(arg0->ownerIdx);
            if (arg0->owner->vfunc_116(p) != 0) {
                *out = newton_sqrtf(recs[i].distance_squared);
                found = 1;
                ((void (*)(void *, void *))set_target_player__12TObjEneDD_STFPv)(arg0, p);
                break;
            }
        }
    }
    return found;
}

s32 TObjEneMe1Gee::check_can_attack() {
    f32 sp8;
    s32 var_r31;

    var_r31 = 0;
    if (target_distance < lbl_805DA0FC) {
        var_r31 = 1;
        this->leader = (TObjEneMe1Gee *)find_entity_by_id(this->leader_id);
        if ((leader->vfunc_116(target) == 0) && (((s32 (*)(void *, f32 *, f32))find_attack_target__13TObjEneMe1GeeFPvPv)(this, &sp8, lbl_805DA138) != 0) && (sp8 > lbl_805DA0FC)) {
            var_r31 = 0;
        }
    }
    return var_r31;
}

s32 TObjEneMe1Gee::fn_800CBA80() {
    return model_height < lbl_805DA134;
}

void TObjEneMe1Gee::vfunc_107() {  }

s32 TObjEneMe1Gee::vfunc_108() {
    u8 *arg0 = (u8 *)this;
        s32 temp_r4;
    temp_r4 = this->gee_flags;
    if (temp_r4 & 0x40) {
        this->gee_flags = (s32) (temp_r4 & 0xFFFFFFBF);
        transition_enemy_state__9TObjEneDDFl(arg0, 0xC);
        return 1;
    }
    return 0;
}

s32 TObjEneMe1Gee::return_home_if_target_lost() {
    if (target == NULL) {
        transition_enemy_state(15);
        return 1;
    }
    return 0;
}

s32 TObjEneMe1Gee::remap_gee_sound(s32 arg1) {
    s32 var_r3;

    if (arg1 == 0x3A843) {
        var_r3 = 0x3A843;
        if (get_current_floor_area() == AREA_SEASIDE_NIGHT) {
            return 0x4003B20D;
        }
        return var_r3;
    }
    var_r3 = remap_sound_for_area(arg1);
    return var_r3;
}

void TObjEneMe1Gee::fn_800CB968() {
    play_persistent_sound(remap_gee_sound(0x3BC16), (s32)this, (u32)&body_center_position, 0, 0);
}

s32 TObjEneMe1Gee::vfunc_104(f32 distance) {
    return select_and_apply_target(distance);
}

#define copy_argb ((int (*)(void *, void *))copy_argb)
void TObjEneMe1Gee::update_fade_sequence() {
    u8 *arg0 = (u8 *)this;
    switch (this->color_sequence) {
    case 0:
        break;
    case 1:
        if (this->color.a > TObjEneMe1Gee__data_805DA0B4) {
            this->color.a = this->color.a - lbl_805DA130;
        } else {
            this->color.a = TObjEneMe1Gee__data_805DA0B4;
            this->color_sequence = 0;
        }
        this->update_packed_color();
        break;
    case 2:
        if (this->color.a < TObjEneMe1Gee__data_805DA0EC) {
            this->color.a = this->color.a + lbl_805DA130;
        } else {
            this->color.a = TObjEneMe1Gee__data_805DA0EC;
            this->color_sequence = 0;
        }
        this->update_packed_color();
        break;
    case 3:
        (this->color_timer)++;
        if ((f32)this->color_timer >= lbl_805DA0CC) {
            this->color_timer = 0;
            switch (gee_color_sequences[this->color_script][(this->color_cursor)++]) {
            case 'b':
                this->color.a = TObjEneMe1Gee__data_805DA0B4;
                break;
            case 'c':
                this->color_sequence = 0;
                ((void (*)(void *, void *))copy_argb)(arg0 + 0x468, (void *)&TObjEneMe1Gee__data_8043BDB0);
                break;
            case 'a':
                this->color.a = TObjEneMe1Gee__data_805DA0EC;
                break;
            }
            this->update_packed_color();
        }
        break;
    }
}
#undef copy_argb

void TObjEneMe1Gee::start_color_sequence(s32 sequence) {
    set_color(&lbl_8043BDD0);
    this->color_sequence = 3;
    this->color_script = sequence;
    this->color_timer = 2;
    this->color_cursor = 0;
}

void TObjEneMe1Gee::set_color(const NJS_ARGB *source) {
    // The shared copy_argb declaration still lacks its const source contract.
    ((void (*)(NJS_ARGB *, const NJS_ARGB *))copy_argb)(&color, source);
    update_packed_color();
}

#pragma push
#pragma opt_common_subs off
void TObjEneMe1Gee::update_packed_color() {
    u8 r = (u32)(lbl_805DA12C * color.g);
    u8 a = (u32)(lbl_805DA0D0 * (lbl_805DA12C * color.b));
    u8 g = (u32)(lbl_805DA12C * color.r);
    u8 b = (u32)(lbl_805DA12C * color.a);
    packed_color = (a << 24) | (r << 16) | (g << 8) | b;
}
#pragma pop

void TObjEneMe1Gee::vfunc_113() {
    if (gee_model_packed_color != NULL) {
        *gee_model_packed_color = packed_color;
    }
}

int TObjEneMe1Gee::vfunc_109() { return 1; }

void TObjEneMe1Gee::update_photon_target() {
    if ((s16) this->mode == 3) {
        this->leader = (TObjEneMe1Gee *)find_entity_by_id(this->leader_id);
        leader->activate_immediately();
    }
}

int TObjEneMe1Gee::has_materialized() {
    return (gee_flags >> 15) & 1;
}

void TObjEneMe1Gee::set_low_appearance() {
    this->gee_flags |= LOW_APPEARANCE;
    this->gee_flags &= ~HIGH_APPEARANCE;
}

void TObjEneMe1Gee::set_high_appearance() {
    this->gee_flags |= HIGH_APPEARANCE;
    this->gee_flags &= ~LOW_APPEARANCE;
}

void TObjEneMe1Gee::set_in_fighter() {
    this->gee_flags |= IN_FIGHTER;
    this->gee_flags &= ~OUT_FIGHTER;
}

void TObjEneMe1Gee::set_out_fighter() {
    this->gee_flags |= OUT_FIGHTER;
    this->gee_flags &= ~IN_FIGHTER;
}

s32 TObjEneMe1Gee::has_gee_flags(u32 flags) {
    return (gee_flags & flags) != 0;
}

void *TObjEneMe1Gee::get_committed_target() {
    if (gee_flags & 0x40000) {
        return target;
    }
    return 0;
}

void TObjEneMe1Gee::remove_child(TObjEneMe1Gee *) {  }

int TObjEneMe1Gee::vfunc_116(void *) { return 1; }

void TObjEneMe1Gee::activate_immediately() {
    activation_delay = 0;
    gee_flags = gee_flags | 1;
}

void TObjEneMe1Gee::activate_with_target(void *actor_target, s32 delay) {
    set_target_player(actor_target);
    this->activation_delay = delay;
    this->gee_flags |= 1;
}

void TObjEneMe1Gee::set_flag3c8_bit2() { this->gee_flags |= 0x2; }

void TObjEneMe1Gee::set_flag3c8_bit4() { this->gee_flags |= 0x4; }

void TObjEneMe1Gee::set_flag3c8_bit8() { this->gee_flags |= 0x8; }

void TObjEneMe1Gee::fn_800CB4DC() {
    gee_flags = gee_flags | 0x100000 | 4;
}

void TObjEneMe1Gee::set_flag3c8_bit40() { this->gee_flags |= 0x40; }

void TObjEneMe1Gee::dispatch_action(u32 state, s32 reason) {
    switch (state) {
    case 0:
        state_attack_loop(reason);
        break;
    case 1:
        state_move(reason);
        break;
    case 2:
        fn_800CAFD8(reason);
        break;
    case 3:
        state_hover(reason);
        break;
    case 4:
        vfunc_110(reason);
        break;
    case 5:
        vfunc_111(reason);
        break;
    case 6:
        state_attack(reason);
        break;
    case 7:
        fn_800CA454(reason);
        break;
    case 8:
        fn_800C9DF8(reason);
        break;
    case 9:
        fn_800C9A94(reason);
        break;
    case 10:
        fn_800C9964(reason);
        break;
    case 12:
        state_despawn(reason);
        break;
    case 13:
        state_hit_recovery(reason);
        break;
    case 14:
        vfunc_112(reason);
        break;
    case 15:
        state_return_home(reason);
        break;
    case 17:
        handle_event(reason);
        break;
    case 18:
        state_orbit(reason);
        break;
    }
}

void TObjEneMe1Gee::state_attack_loop(s32 arg1) {
    switch (arg1) {
    case 4:
        this->requested_action = 0;
        set_field_378(3);
        this->vfunc_95();
        this->gee_flags |= 0x400000;
        this->color_sequence = 1;
        this->state_step = 0;
        return;
    case 3:
        if ((s32) this->state_step >= 4) {
            if ((s32) this->role == 0) {
                this->gee_flags |= 0x100000;
            }
            if (this->gee_flags & LOW_APPEARANCE) {
                transition_enemy_state__9TObjEneDDFl(this, 1);
            } else {
                transition_enemy_state__9TObjEneDDFl(this, 2);
            }
        }
    case 5:
        break;
    case 0:
        this->state_step = (s32) (this->state_step + 1);
        if ((s32) this->state_step == 2) {
            this->vfunc_107();
        }
        this->gee_flags &= 0xFEFFFFFF;
        break;
    }
}

void TObjEneMe1Gee::state_move(s32 arg1) {
    s32 temp_r4;

    switch (arg1) {
    case 4:
        this->requested_action = 0;
        set_field_378(3);
        this->gee_flags &= 0xFFBFFFFF;
        this->vfunc_95();
        temp_r4 = this->actorFlags & 0xFEFFFFFF;
        this->actorFlags = temp_r4;
        this->color_sequence = 1;
        this->fade.start_fade_in();
        play_area_sound_and_particles_b(&position);
        return;
    case 3:
        if (this->fade.advance_toward_max() != 0) {
            transition_enemy_state__9TObjEneDDFl(this, 3);
        }
    case 5:
        return;
    case 0:
        advance_animation();
        if ((s32) this->role == 2) {
            fn_800CBE6C(lbl_805DA0AC + this->position.y);
        } else {
            this->update_hover_height();
        }
        this->vfunc_88();
        break;
    }
}

void TObjEneMe1Gee::fn_800CAFD8(s32 reason) {
    Vec effect_position;
    f32 effect_height;
    switch (reason) {
    case 4:
        requested_action = 0;
        set_field_378(3);
        gee_flags &= 0xFFBFFFFF;
        gee_flags &= 0xFFF7FFFF;
        actorFlags |= 0x01000000;
        vfunc_95();
        color_sequence = 1;
        fade.start_fade_in();
        VecCopy(&effect_position, &position);
        effect_height = effect_position.y + lbl_805DA128;
        effect_position.y = effect_height;
        world_height = effect_height;
        play_area_sound_and_particles_a(&effect_position);
        vfunc_91();
        state_step = 0;
        return;
    case 3:
        if (gee_flags & 0x80000) {
            transition_enemy_state__9TObjEneDDFl(this, 3);
            vfunc_92();
        }
        return;
    case 0:
        advance_animation();
        switch (state_step) {
        case 0:
            if (fade.advance_toward_max() != 0) {
                state_step = 1;
            }
            break;
        case 1:
            update_from_float_sum();
            break;
        }
        vfunc_88();
        fn_800CB968();
        return;
    case 5:
        vfunc_92();
        actorFlags &= 0xFEFFFFFF;
        break;
    }
}

void TObjEneMe1Gee::state_hover(s32 arg1) {
    s32 temp_r3;

    switch (arg1) {
    case 4:
        this->requested_action = 0;
        set_field_378(3);
        this->gee_flags &= 0xFFBFFFFF;
        this->vfunc_96();
        this->actorFlags = (s32) (this->actorFlags & 0xFEFFFFFF);
        this->color_sequence = 1;
        break;
    case 3:
        if (this->vfunc_108() == 0) {
            temp_r3 = this->gee_flags;
            if (temp_r3 & 1) {
                this->gee_flags = (s32) (temp_r3 & 0xFFFFFFFE);
                transition_enemy_state__9TObjEneDDFl(this, 4);
            } else if (this->enemy_has_live_target() != 0) {
                transition_enemy_state__9TObjEneDDFl(this, 4);
            }
        }
        break;
    case 0:
        advance_animation();
        if ((s32) this->role != 1) {
            this->update_linked_position(TObjEneMe1Gee__data_805DA0A8);
        }
        if ((s32) this->role == 2) {
            fn_800CBE6C(lbl_805DA0AC + this->position.y);
        } else {
            this->update_hover_height();
        }
        this->vfunc_89();
        break;
    case 5:
        this->actorFlags = (s32) (this->actorFlags & 0xFEFFFFFF);
        break;
    case 1:
        break;
    }
}

void TObjEneMe1Gee::vfunc_110(s32 arg1) {
    u8 *arg0 = (u8 *)this;
        s32 temp_r3;

    switch (arg1) {
    case 4:
        this->requested_action = 0;
        this->set_field_378(4);
        this->gee_flags &= 0xFFBFFFFF;
        this->vfunc_96();
        this->actorFlags = (s32) (this->actorFlags & 0xFEFFFFFF);
        this->color.r = TObjEneMe1Gee__data_8043BDB0.r;
        this->color.g = TObjEneMe1Gee__data_8043BDB0.g;
        this->color.b = TObjEneMe1Gee__data_8043BDB0.b;
        this->update_packed_color();
        this->state_step = 0;
        return;
    case 3:
        if (this->vfunc_108() == 0) {
            temp_r3 = this->gee_flags;
            if (temp_r3 & 2) {
                this->gee_flags = (s32) (temp_r3 & 0xFFFFFFFD);
                if ((s32) this->role == 1) {
                    transition_enemy_state__9TObjEneDDFl(arg0, 6);
                } else {
                    transition_enemy_state__9TObjEneDDFl(arg0, 5);
                }
            }
        }
        break;
    case 1:
        break;
    case 0:
        advance_animation();
        this->update_linked_position(TObjEneMe1Gee__data_805DA0A8);
        switch (this->state_step) {
        case 2:
            break;
        case 0:
            this->activation_delay = (s32) (this->activation_delay - 1);
            if ((s32) this->activation_delay <= 0) {
                this->color_sequence = 2;
                this->state_step = 1;
            }
            break;
        case 1:
            if ((s32) this->color_sequence == 0) {
                this->gee_flags |= 0x8000;
                switch (this->role) {
                case 0:
                    set_flag3c8_bit2();
                case 1:
                    this->state_step = 3;
                    break;
                }
            }
            this->update();
            break;
        case 3:
            this->update();
            break;
        }
        this->update_hover_height();
        this->vfunc_89();
        return;
    case 5:
        this->vfunc_92();
        break;
    }
}

void TObjEneMe1Gee::vfunc_111(s32 arg1) {
    switch (arg1) {
    case 4:
        this->requested_action = 0;
        set_field_378(5);
        this->gee_flags &= 0xFFBFFFFF;
        this->vfunc_96();
        this->actorFlags = (s32) (this->actorFlags | 0x01000000);
        return;
    case 3:
        if (this->gee_flags & 0x80000) {
            this->attack_count = 0;
            this->vfunc_105();
        }
        break;
    case 5:
        break;
    case 0:
        advance_animation();
        update_linked_position(TObjEneMe1Gee__data_805DA0A8);
        update();
        update_animation_frame();
        this->vfunc_89();
        break;
    }
}

void TObjEneMe1Gee::state_attack(s32 arg1) {
    s32 temp_r3;

    switch (arg1) {
    case 4:
        this->requested_action = 0;
        set_field_378(6);
        this->gee_flags &= 0xFFBFFFFF;
        this->vfunc_96();
        this->actorFlags = (s32) (this->actorFlags | 0x01000000);
        this->state_step = 0;
        return;
    case 3:
        if ((this->vfunc_108() == 0) && ((s32) this->state_step == 3)) {
            this->attack_count = 0;
            this->vfunc_105();
        }
    case 5:
    case 1:
        return;
    case 0:
        advance_animation();
        this->update_linked_position(TObjEneMe1Gee__data_805DA0A8);
        switch (this->state_step) {
        case 0:
            temp_r3 = this->gee_flags;
            if (temp_r3 & 4) {
                this->gee_flags = (s32) (temp_r3 & 0xFFFFFFFB);
                if (has_gee_flags(TObjEneMe1Gee::OUT_FIGHTER) != 0) {
                    this->state_step = 1;
                    start_color_sequence(1);
                } else {
                    this->state_step = 2;
                    start_color_sequence(3);
                }
            }
            update();
            this->update_animation_frame();
            break;
        case 1:
            if ((s32) this->color_sequence == 0) {
                this->state_step = 3;
            }
            update();
            this->update_animation_frame();
            break;
        case 2:
            update();
            if ((s32) this->color_sequence != 0) {
                this->update_animation_frame();
            } else {
                fn_800CBE6C(this->position.y + this->alternate_height);
                if (this->gee_flags & 0x80000) {
                    this->state_step = 3;
                }
            }
            break;
        }
        this->vfunc_89();
        break;
    }
}

#pragma push
#pragma fp_contract on
#pragma opt_common_subs off
void TObjEneMe1Gee::fn_800CA454(s32 reason) {
    Vec *dir = &attack_destination;
    switch (reason) {
    case 4:
        set_field_378(7);
        gee_flags |= 0x10000;
        gee_flags &= ~0x400000;
        vfunc_96();
        actorFlags |= 0x1000000;
        set_color(&TObjEneMe1Gee__data_8043BDB0);
        state_step = 1;
        state_timer = 0;
        effect_460 = NULL;
        effect_464 = NULL;
        break;
    case 3:
        if (vfunc_108() == 0 && return_home_if_target_lost() == 0 && state_step == 6) {
            if (gee_flags & 0x100000) {
                transition_enemy_state(9);
            } else {
                transition_enemy_state(10);
            }
        }
        break;
    case 0:
        advance_animation();
        if (state_step == 1) {
            if (update_linked_position(TObjEneMe1Gee__data_805DA0A8) == 0) {
                break;
            }
        } else if (check_target_validity() == 0) {
            break;
        }
        enemy_copy_target_destination();
        switch (state_step) {
        case 1:
            update_velocity();
            if (check_can_attack() != 0) {
                state_step = 2;
                gee_flags |= 0x40000;
            }
            TObjEneEpsilon__sub_800B92F8((u8 *)this, 0x200, (f32)TObjEneMe1Gee__data_805DA0D4);
            break;
        case 2:
            update_velocity();
            update_angle();
            state_step = 3;
            set_color(&TObjEneMe1Gee__data_8043BDC0);
            VecCopy(dir, &target_destination);
            break;
        case 3: {
            Vec d;
            update_velocity();
            update_angle();
            VecCopy(&d, &target_destination);
            subtract_vector(&d, dir);
            if (normalize_vector_xz(&d) < lbl_805DA124) {
                VecCopy(dir, &target_destination);
            } else {
                dir->x = lbl_805DA124 * d.x + dir->x;
                dir->y = lbl_805DA124 * d.y + dir->y;
                dir->z = lbl_805DA124 * d.z + dir->z;
            }
            state_timer++;
            if (state_timer > gee_parameters->needle_charge_frames) {
                requested_action = 1;
                state_step = 4;
                state_timer = 0;
                if (effect_460 != NULL) {
                    effect_460->queue_destruction();
                    effect_460 = NULL;
                }
                if (effect_464 != NULL) {
                    effect_464->queue_destruction();
                    effect_464 = NULL;
                }
                play_sound_effect(remap_gee_sound(0x3AD17), &body_center_position, 0, 0);
            } else {
                play_persistent_sound((s32)(remap_gee_sound(0x3A914)), (s32)this, (u32)&body_center_position, 0, 0);
            }
            break;
        }
        case 4:
            state_timer++;
            if (state_timer >= 15) {
                state_step = 5;
                gee_flags &= ~0x40000;
                set_color(&TObjEneMe1Gee__data_8043BDB0);
                attack_count++;
                advance_animation();
                push_matrix_from(identity_matrix);
                post_translate_matrix(&position);
                rotate_matrix_y(0, rotation_y);
                set_motion_packed_rotation();
                calc_joint_matrices(state_timer);
                clear_motion_packed_rotation();
                pop_matrix();
                state_timer = 0;
                push_matrix_from(anim_model_matrix_array[7]);
                {
                    Vec out;
                    Vec in = lbl_8043BE7C;
                    void *p;
                    matrix_mult_vec(0, &in, &out);
                    pop_matrix();
                    out.y += attack_height;
                    p = __nw__7TObjectFUl(0xC4);
                    if (p != NULL) {
                        TObjEneMe1Gee_NEEDLE__ct((TObjEneMe1Gee_NEEDLE *)p, (s32)this,
                            (u8 *)&out, (u8 *)dir, needle_speed, gee_parameters->needle_parameter);
                    }
                }
            }
            break;
        case 5:
            state_timer++;
            if (state_timer > gee_parameters->needle_recovery_frames) {
                state_timer = 0;
                if (attack_count >= gee_parameters->needle_count) {
                    state_step = 6;
                } else {
                    state_step = 1;
                }
            }
            break;
        }
        set_move_speed_x();
        vfunc_89();
        break;
    case 5:
        gee_flags &= ~0x40000;
        set_color(&TObjEneMe1Gee__data_8043BDB0);
        if (effect_460 != NULL) {
            effect_460->queue_destruction();
            effect_460 = NULL;
        }
        if (effect_464 != NULL) {
            effect_464->queue_destruction();
            effect_464 = NULL;
        }
        break;
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
#pragma opt_common_subs off
void TObjEneMe1Gee::fn_800C9DF8(s32 reason) {
    f32 dist;

    switch (reason) {
    case 4:
        requested_action = 0;
        set_field_378(8);
        gee_flags &= ~0x400000;
        vfunc_96();
        actorFlags &= ~0x1000000;
        gee_flags &= ~0x80000;
        state_step = 0;
        state_timer = 0x28;
        state_count = 0;
        field_448 = TObjEneMe1Gee__data_805DA0B4;
        field_44C = TObjEneMe1Gee__data_805DA0B4;
        break;
    case 3:
        if (vfunc_108() == 0 && return_home_if_target_lost() == 0 && state_step == 5) {
            transition_enemy_state(9);
        }
        break;
    case 0:
        advance_animation();
        if (state_step == 0) {
            if (update_linked_position(TObjEneMe1Gee__data_805DA0A8) == 0) {
                break;
            }
        } else if (check_target_validity() == 0) {
            break;
        }
        switch (state_step) {
        case 0:
            enemy_copy_target_destination();
            update_velocity();
            update_angle();
            state_timer++;
            if (state_timer > 0x28) {
                state_timer = 0;
                state_step = 1;
                if (gee_flags & 0x40000) {
                    if (target_distance < lbl_805DA0B0) {
                        state_step = 2;
                        set_color(&TObjEneMe1Gee__data_8043BDC0);
                    }
                } else if (target_distance < lbl_805DA100) {
                    leader = (TObjEneMe1Gee *)find_entity_by_id(leader_id);
                    if (leader->vfunc_116(target) != 0) {
                        gee_flags |= 0x40000;
                    } else if (((s32 (*)(void *, f32 *, f32))find_attack_target__13TObjEneMe1GeeFPvPv)(this, &dist, lbl_805DA104) != 0) {
                        if (dist < lbl_805DA100) {
                            gee_flags |= 0x40000;
                        }
                    } else {
                        state_step = 5;
                    }
                }
            }
            fn_800CBE6C(position.y + model_height);
            break;
        case 1:
            if (state_timer == 0) {
                f32 z;
                f32 x;
                f32 c;
                f32 s;
                f32 inv;
                f32 k;
                enemy_copy_target_destination();
                update_velocity();
                play_sound_effect(remap_gee_sound(0x3AD13), &body_center_position, 0, 0);
                k = lbl_805DA108;
                inv = TObjEneMe1Gee__data_805DA0EC / newton_sqrtf(k);
                k *= inv;
                c = TObjEneMe1Gee__data_805DA0E8 * inv;
                s = lbl_805DA10C * inv;
                if (state_count == 1) {
                    state_count = 0;
                    s *= lbl_805DA110;
                } else {
                    state_count = 1;
                }
                x = target_direction.x;
                z = target_direction.z * c - x * s;
                target_direction.x = x * c + target_direction.z * s;
                target_direction.z = z;
                field_448 = lbl_805DA114 * k;
                field_44C = lbl_805DA114 * (hover_height - model_height);
            }
            enable_attack_body();
            state_timer++;
            if (state_timer >= 4) {
                state_timer = 0;
                state_step = 0;
                disable_attack_body();
            }
            world_height += field_44C;
            move_to_wall_clamped_destination(target_direction.x, target_direction.z, field_448);
            break;
        case 2:
            enemy_copy_target_destination();
            update_velocity();
            update_angle();
            sub_800CBF58(position.y + hover_height);
            if (target_distance < lbl_805DA118) {
                if (fn_800CBA80() != 0) {
                    state_timer = 0;
                    state_step = 3;
                }
            } else {
                if (target_distance > lbl_805DA0B0) {
                    state_step = 1;
                }
                TObjEneEpsilon__sub_800B92AC((u8 *)this, 0x200, gee_parameters->chase_speed);
            }
            break;
        case 3:
            requested_action = 1;
            state_step = 4;
            play_sound_effect(remap_gee_sound(0x3AD15), &body_center_position, 0, 0);
        case 4:
            enemy_copy_target_destination();
            update_velocity();
            update_angle();
            state_timer++;
            if (requested_action == 0) {
                if (attack_count >= 3) {
                    state_step = 5;
                } else {
                    state_timer = 0;
                    if (target_distance < lbl_805DA11C) {
                        state_step = 3;
                    } else if (target_distance < lbl_805DA0B0) {
                        state_step = 2;
                    } else {
                        state_step = 1;
                        set_color(&TObjEneMe1Gee__data_8043BDB0);
                        if (target_distance > lbl_805DA100) {
                            gee_flags &= ~0x40000;
                        }
                    }
                }
            } else if (is_passing_frame((f32)lbl_805DA0B8) != 0) {
                attack_count++;
                if (fn_800CBA80() != 0) {
                    if (static_cast<TObjChara *>(target)->select_melee_contact_body(this, TObjEneMe1Gee__data_805DA0EC) != 0) {
                        static_cast<TObjChara *>(target)->receive_physical_attack(this, TObjEneMe1Gee__data_805DA0EC);
                        static_cast<TObjChara *>(target)->apply_knockback_from_attacker((u8 *)this, lbl_805DA120);
                        if (random_ratio() <= lbl_805DA114) {
                            DirectAttackPayload payload = lbl_8043BE88;
                            static_cast<TObjChara *>(target)->receive_direct_attack(this, payload, NULL, -1, -1);
                        }
                    }
                }
            }
            update_hover_height();
            break;
        case 5:
            break;
        }
        vfunc_89();
        break;
    case 5:
        gee_flags &= ~0x40000;
        set_color(&TObjEneMe1Gee__data_8043BDB0);
        disable_attack_body();
        break;
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEneMe1Gee::fn_800C9A94(s32 reason) {
    Vec *dir = &attack_destination;
    switch (reason) {
    case 4:
        requested_action = 0;
        set_field_378(9);
        gee_flags &= 0xFFBFFFFF;
        vfunc_96();
        attack_count = 0;
        state_step = 1;
        enable_attack_body();
        state_timer = 0;
        state_count = 0;
        rotation_step = 0;
        field_448 = TObjEneMe1Gee__data_805DA0B4;
        field_44C = TObjEneMe1Gee__data_805DA0B4;
        field_450 = TObjEneMe1Gee__data_805DA0B4;
        dir->x = TObjEneMe1Gee__data_805DA0B4;
        dir->y = TObjEneMe1Gee__data_805DA0B4;
        dir->z = TObjEneMe1Gee__data_805DA0B4;
        break;
    case 3:
        if (vfunc_108() == 0 && return_home_if_target_lost() == 0 && state_count >= 4) {
            vfunc_105();
        }
        break;
    case 0:
        advance_animation();
        if (update_linked_position(TObjEneMe1Gee__data_805DA0A8) != 0) {
            switch (state_step) {
            case 1: {
                if (state_timer == 0) {
                    f32 t;
                    enemy_copy_target_destination();
                    update_velocity();
                    t = lbl_805DA0F0 * calc_elapsed_scaled();
                    if (t >= TObjEneMe1Gee__data_805DA0B4) {
                        t += lbl_805DA0F4;
                    } else {
                        t -= lbl_805DA0F4;
                    }
                    t *= lbl_805DA0F8;
                    rotation_step = t;
                    dir->x = -target_direction.x;
                    dir->z = -target_direction.z;
                    field_448 = lbl_805DA0F8 * (attack_height - model_height);
                    field_450 = lbl_805DA0F8 * (lbl_805DA0FC - target_distance);
                    field_44C = target_distance;
                    play_sound_effect(remap_gee_sound(0x3AD13), &body_center_position, 0, 0);
                }
                state_timer++;
                if (state_timer >= 8) {
                    state_count++;
                    state_step = 0;
                    disable_attack_body();
                }
                world_height += field_448;
                rotate_xz_pair_by_angle(&dir->x, &dir->z, rotation_step);
                {
                    Vec v;
                    f32 c;
                    field_44C += field_450;
                    v.x = dir->x * field_44C + target_destination.x;
                    v.z = dir->z * field_44C + target_destination.z;
                    subtract_vector(&v, &position);
                    c = normalize_vector_xz(&v);
                    move_to_wall_clamped_destination(v.x, v.z, c);
                }
                rotation_y = (s32)(lbl_8043BF28 * atan2_float(dir->x, dir->z)) + 0x8000;
                break;
            }
            case 0:
                enemy_copy_target_destination();
                update_velocity();
                update_angle();
                update_animation_frame();
                state_timer++;
                if (state_timer > 30) {
                    state_timer = 0;
                    state_step = 1;
                }
                break;
            }
            vfunc_89();
        }
        break;
    case 5:
        disable_attack_body();
        break;
    }
}
#pragma pop

void TObjEneMe1Gee::fn_800C9964(s32 reason) {
    switch (reason) {
    case 4:
        requested_action = 0;
        set_field_378(10);
        gee_flags &= 0xFFBFFFFF;
        vfunc_95();
        if (role == 1) {
            leader = (TObjEneMe1Gee *)find_entity_by_id(leader_id);
            leader->set_flag3c8_bit8();
        }
        attack_count = 0;
        return;
    case 3:
        if (vfunc_108() == 0 && target_distance < TObjEneMe1Gee__data_805DA0EC) {
            transition_enemy_state(6);
        }
    case 5:
        return;
    case 0:
        advance_animation();
        set_target_destination(&home_position);
        update_velocity();
        update_angle();
        set_move_speed_x();
        move_with_wall_slide_commit(target_direction.x, target_direction.z, lbl_805DA0D0);
        vfunc_88();
        break;
    }
}

void TObjEneMe1Gee::state_hit_recovery(s32 reason) {
    Vec v;
    f32 len;
    switch (reason) {
    case 4:
        requested_action = 3;
        advance_animation();
        update_photon_target();
        gee_flags &= ~0x400000;
        vfunc_96();
        actorFlags &= ~0x1000000;
        state_step = 0;
        if (world_height > TObjEneMe1Gee__data_805DA0C8 + (position.y + hover_height)) {
            state_timer = 0;
        } else {
            state_timer = 2;
        }
        field_448 = TObjEneMe1Gee__data_805DA0B4;
        field_44C = TObjEneMe1Gee__data_805DA0B4;
        break;
    case 3:
        if (state_timer == 3) {
            transition_enemy_state(m_378);
        }
        break;
    case 0:
        advance_animation();
        VecCopy(&v, &movement_velocity);
        len = normalize_vector_xz(&v);
        move_with_wall_slide_on_ground(v.x, v.z, len);
        len *= TObjEneMe1Gee__data_805DA0D4;
        movement_velocity.x = v.x * len;
        movement_velocity.z = v.z * len;
        switch (state_timer) {
        case 0:
            field_448 = field_448 - 0.13f;
            if (field_448 < -4.0f) {
                field_448 = -4.0f;
            }
            world_height += field_448;
            if (world_height < 12.0f + (position.y + hover_height)) {
                state_timer = 1;
                if (field_448 > -2.0f) {
                    field_448 = -2.0f;
                }
                field_44C = (field_448 * field_448) / TObjEneMe1Gee__data_805DA0E8;
            }
            break;
        case 1:
            field_448 += field_44C;
            world_height += field_448;
            if (field_448 >= TObjEneMe1Gee__data_805DA0B4) {
                if (world_height > position.y + hover_height) {
                    world_height = position.y + hover_height;
                    state_step = 0;
                    state_timer = 2;
                }
            }
            break;
        case 2:
            state_step++;
            if (state_step >= gee_parameters->hit_recovery_frames) {
                state_timer = 3;
            }
            break;
        }
        vfunc_89();
        break;
    case 5:
        clear_attack_receipts();
        requested_action = 0;
        break;
    }
}

#pragma push
#pragma opt_common_subs off
void TObjEneMe1Gee::state_despawn(s32 reason) {
    switch (reason) {
    case 4:
        requested_action = 0;
        set_field_378(12);
        vfunc_95();
        gee_flags &= ~0x400000;
        actorFlags |= 0x800;
        if (role == 1) {
            leader = (TObjEneMe1Gee *)find_entity_by_id(leader_id);
            leader->remove_child(this);
        } else {
            send_entity_set_flags();
        }
        fade.set_rate_from_divisor(25);
        fade.reset_color();
        return;
    case 3:
        if (fade.decay_value_toward_floor() != 0 && vfunc_109() != 0) {
            queue_destruction();
        }
    case 5:
    case 0:
        return;
    }
}
#pragma pop

void TObjEneMe1Gee::state_return_home(s32 arg1) {

    switch (arg1) {
    case 4:
        set_field_378(0xF);
        this->gee_flags &= 0xFFBFFFFF;
        this->vfunc_96();
        this->state_step = 0;
        return;
    case 3:
        if ((s32) this->state_step == 2) {
            this->vfunc_105();
        }
    case 5:
        return;
    case 0:
        advance_animation();
        if (this->update_linked_position(TObjEneMe1Gee__data_805DA0A8) != 0) {
            this->state_step = 2;
        }
        switch (this->state_step) {
        case 0:
            this->state_timer = (s32) (this->state_timer + 1);
            if ((s32) this->state_timer >= 0x3C) {
                this->state_step = 1;
            }
            fn_800CBE6C(this->position.y + this->model_height);
            break;
        case 1:
            set_target_destination((const Vec *)((u8 *)this + 0x50));
            this->update_velocity();
            update_angle();
            set_move_speed_x();
            if (target_distance > lbl_805DA0CC) {
                this->move_with_wall_slide_commit(this->target_direction.x, this->target_direction.z, lbl_805DA0D0);
            }
            break;
        }
        this->vfunc_89();
        break;
    }
}

void TObjEneMe1Gee::vfunc_112(s32 arg1) {
    Vec effect_position;
    switch (arg1) {
    case 4:
        if ((s32) this->role == 1) {
            this->leader = (TObjEneMe1Gee *)find_entity_by_id(this->leader_id);
            leader->remove_child(this);
        }
        create_breakup_mdl__12TBoss3VoloptFlllll((s32)gee_breakup_model, 0, texlist, &body_center_position, rotation_y);
        play_sound_effect(remap_gee_sound(0x3A843), &position, 0, 0);
        this->gee_flags |= 0x400000;
        this->actorFlags = (s32) (this->actorFlags | 0x01000000);
        VecCopy(&effect_position, &body_center_position);
        effect_position.y -= TObjEneMe1Gee__data_805DA0C8;
        refresh_and_send_entity_flags();
        return;
    case 0:
        queue_destruction();
    case 3:
    case 5:
        return;
    }
}

void TObjEneMe1Gee::handle_event(s32 arg1) {
    switch (arg1) {
    case 4:
        this->requested_action = 0;
        this->state_step = 0;
        return;
    case 0:
        advance_animation();
        this->state_step = (s32) (this->state_step + 1);
        if ((s32) this->state_step > 0x5A) {
            this->state_step = 0;
            this->requested_action = (this->requested_action + 1);
            if ((s16) this->requested_action >= 4) {
                this->requested_action = 0;
            }
        }
    case 3:
    case 5:
    case 1:
        return;
    }
}

void TObjEneMe1Gee::state_orbit(s32 arg1) {
    f32 temp_f1;

    switch (arg1) {
    case 4:
        this->requested_action = 0;
        temp_f1 = this->position.y;
        this->world_height = (f32) (temp_f1 + this->hover_height);
        this->field_448 = sin_table_lookup(rotation_y);
        this->field_44C = cos_table_lookup(*(s32 *)((s8 *)this + 0x60));
        return;
    case 0:
        advance_animation();
        this->world_height = (f32) (this->position.y + this->hover_height);
        this->body_center_position.y = (f32) this->world_height;
        this->move_with_wall_slide_commit(this->field_448, this->field_44C, lbl_805DA0C4);
    case 3:
    case 5:
    case 1:
        return;
    }
}

void TObjEneMe1Gee::advance_camera_ctrl_step() {
    Vec *pos;
    Vec *temp_r4_2;
    switch ((s32) TObjEneMe1Gee__render_node_index) {
    case 4:
        pos = gee_camera_ctrl_step_ptr;
        gee_camera_ctrl_step_ptr = pos + 1;
        transform_point_to_view(&gee_camera_ctrl_vec, pos);
        break;
    case 7:
        temp_r4_2 = gee_camera_ctrl_step_ptr;
        gee_camera_ctrl_step_ptr = temp_r4_2 + 1;
        transform_point_to_view(&gee_camera_ctrl_vec, temp_r4_2);
        break;
    }
    TObjEneMe1Gee__render_node_index += 1;
}

void TObjEneMe1Gee::render() {
    u8 *ene_me1_gee = (u8 *)this;
    s16 temp_r0;
    s16 temp_r0_2;
    s32 var_r30;
    s32 var_r29;

    if (check_demo_mode() != 0) {
        this->vfunc_115();
        return;
    }
    if (this->gee_flags & 0x400000) {
        var_r30 = 0;
    } else if (TObjEneDD::is_main_phase_15() != 0) {
        var_r30 = classify_actor_view_detail(lbl_805D9E88, lbl_805D9E84, TObjEneMe1Gee__data_805DA0C0);
    } else if (update_object_view_visibility(lbl_805DA0BC, TObjEneMe1Gee__data_805DA0C0) != 0) {
        var_r30 = 1;
    } else {
        var_r30 = 0;
    }
    if (var_r30 != 0) {
        if (this->gee_flags & 0x01000000) {
            draw_ground_shadow(NULL, 0);
        }
        this->update_secondary_light();
        TObjFish::set_global_param((int) (this->texlist));
        saved_model_render_flags = model_render_flags;
        TObjEneDD::clear_global_flag_400();
        TObjPlayer::toggle_particle_effect();
        this->vfunc_113();
        push_matrix();
        post_translate_matrix(ene_me1_gee + 0x38);
        translate_matrix(0, TObjEneMe1Gee__data_805DA0B4, (f32) (this->model_height), TObjEneMe1Gee__data_805DA0B4);
        rotate_matrix_y(0, (int) (this->rotation_y));
        temp_r0 = this->mode;
        var_r29 = 1;
        if ((temp_r0 == 1) || (temp_r0 == 0xC)) {
            fade.set_flags_and_apply_damage_color();
            if (defer_render() != 0) {
                var_r29 = 0;
            }
        }
        if (var_r29 != 0) {
            if ((s16) this->mode != 0xB) {
                TObjEneMe1Gee__render_node_index = 0;
                gee_camera_ctrl_step_ptr = node_positions;
                set_chunk_model_node_callback((s32)((void *)TObjEneMe1Gee::advance_camera_ctrl_step));
                if (var_r30 == 1) {
                    set_motion_packed_rotation();
                    this->draw();
                    clear_motion_packed_rotation();
                } else {
                    set_motion_packed_rotation();
                    this->draw_motion_model();
                    clear_motion_packed_rotation();
                }
                set_chunk_model_node_callback((s32)NULL);
            } else {
                rotate_matrix_z(0, (int) (this->rotation_z));
                TObjEneMe1Gee__render_node_index = -1;
                gee_camera_ctrl_step_ptr = node_positions;
                set_chunk_model_node_callback((s32)((void *)TObjEneMe1Gee::advance_camera_ctrl_step));
                this->draw_with_alt_model((int) (*(s32 *)((s8 *)ene_me1_gee + 0x410)));
                set_chunk_model_node_callback((s32)NULL);
            }
        }
        temp_r0_2 = this->mode;
        if ((temp_r0_2 == 1) || (temp_r0_2 == 0xC)) {
            fade.clear_flag_and_notify();
        }
        pop_matrix();
        TParticleCtrl::end_effect_render();
        model_render_flags = saved_model_render_flags;
        this->update_primary_light();
        return;
    }
    VecCopy__FP3VecPC3Vec(ene_me1_gee + 0x414, ene_me1_gee + 0x2FC);
    VecCopy__FP3VecPC3Vec(ene_me1_gee + 0x420, ene_me1_gee + 0x2FC);
}

void TObjEneMe1Gee::vfunc_114() {
    if (get_target_info() != 0) {
        apply_behavior_parameters();
    }
}

void TObjEneMe1Gee::vfunc_115() {
    u8 *arg0 = (u8 *)this;
        s32 temp_r3;
    s32 temp_r3_2;
    if (get_target_info() != 0) {
        if ((s32) this->role == 0) {
            temp_r3 = this->gee_flags;
            if (temp_r3 & IN_FIGHTER) {
                TObjEneMe1Gee::queue_debug_text((s32)(pack_debug_text_position(0, 2)), (char *)lbl_8043BE98);
            } else if (temp_r3 & OUT_FIGHTER) {
                TObjEneMe1Gee::queue_debug_text((s32)(pack_debug_text_position(0, 2)), (char *)lbl_8043BEA8);
            } else {
                TObjEneMe1Gee::queue_debug_text((s32)(pack_debug_text_position(0, 2)), (char *)lbl_8043BEBC);
            }
            temp_r3_2 = this->gee_flags;
            if (temp_r3_2 & LOW_APPEARANCE) {
                TObjEneMe1Gee::queue_debug_text((s32)(pack_debug_text_position(0, 3)), (char *)lbl_8043BEC8);
            } else if (temp_r3_2 & HIGH_APPEARANCE) {
                TObjEneMe1Gee::queue_debug_text((s32)(pack_debug_text_position(0, 3)), (char *)lbl_8043BED8);
            } else {
                TObjEneMe1Gee::queue_debug_text((s32)(pack_debug_text_position(0, 3)), (char *)lbl_8043BEBC);
            }
        }
        TObjEneMe1Gee::queue_debug_text((s32)(pack_debug_text_position(0, 4)), (char *)lbl_8043BEEC);
        TObjEneMe1Gee::queue_debug_text((s32)(pack_debug_text_position(0, 5)), (char *)lbl_8043BF0C);
    }
    if (update_object_view_visibility(lbl_805DA0BC, TObjEneMe1Gee__data_805DA0C0) != 0) {
        draw_ground_shadow(NULL, 0);
        TObjPlayer::toggle_particle_effect();
        TObjFish::set_global_param(this->texlist);
        push_matrix();
        post_translate_matrix((u8 *)&this->position);
        rotate_matrix_y(0, this->rotation_y);
        TObjEneDD::clear_global_flag_400();
        draw_chunk_object((void *)(this->model));
        pop_matrix();
        TParticleCtrl::end_effect_render();
    }
}

TUnk_8049387C::~TUnk_8049387C() {}

void TUnk_8049387C::run_task() {
    if (check_demo_mode() != 0) {
        vfunc_114();
        return;
    }
    if (vfunc_83() != 4) {
        vfunc_85();
        update_fade_sequence();
        update_swarm_phase();
    }
    sync_body_position();
    submit_default_cursor_candidate();
    vfunc_100();
}

void TUnk_8049387C::vfunc_106() {
    model = (void *)TObjEneMe1Gee__resource_bundle->models->model;
    texlist = TObjEneMe1Gee__resource_bundle->models->m_c;
}

void TUnk_8049387C::vfunc_105() {
    switch (attack_cycle) {
    case 0:
    case 1:
        attack_cycle++;
        transition_enemy_state(7);
        break;
    case 2:
        attack_cycle = 0;
        transition_enemy_state(8);
        break;
    }
}

void TUnk_8049387C::vfunc_107() {
    s32 n;
    s32 i;
    s32 j;
    u16 a;
    s32 b;
    s32 angle;
    Vec v;
    n = (s32)ceil_to_float((f32)max_children / (f32)gee_parameters->swarm_group_divisor);
    if (n < 1) {
        n = 1;
    }
    a = entity_id + 1;
    angle = rotation_y;
    b = set_index + 1;
    for (i = 0; i < n; i++) {
        v.x = lbl_805DA0B0 * sin_table_lookup(angle);
        v.y = TObjEneMe1Gee__data_805DA0B4;
        v.z = lbl_805DA0B0 * cos_table_lookup(angle);
        vec3_add_to(&v, &position);
        angle += 0x10000 / max_children;
        children[i] = create_child(this, &v, a++, b++);
        children[i]->set_out_fighter();
        this->child_count++;
    }
    for (j = n; j < max_children; j++) {
        v.x = lbl_805DA0B0 * sin_table_lookup(angle);
        v.y = TObjEneMe1Gee__data_805DA0B4;
        v.z = lbl_805DA0B0 * cos_table_lookup(angle);
        vec3_add_to(&v, &position);
        angle += 0x10000 / max_children;
        children[j] = create_child(this, &v, a++, b++);
        children[j]->set_in_fighter();
        this->child_count++;
    }
}

s32 TUnk_8049387C::vfunc_108() {
    s32 i;
    if (gee_flags & 0x40) {
        gee_flags &= ~0x40;
        transition_enemy_state(12);
        for (i = 0; i < this->child_count; i++) {
            children[i]->set_flag3c8_bit40();
        }
        return 1;
    }
    return 0;
}

void TUnk_8049387C::remove_child(TObjEneMe1Gee *arg1) {
    s32 i;
    TObjEneMe1Gee *tmp;

    for (i = 0; i < child_count; i++) {
        if (children[i] == arg1) {
            child_count--;
            tmp = children[child_count];
            children[child_count] = arg1;
            children[i] = tmp;
            break;
        }
    }
    if (swarm_phase == 3) {
        s32 lim = (s32)ceil_to_float((f32)max_children / (f32)gee_parameters->swarm_group_divisor);
        if (child_count <= max_children - lim) {
            leader = (TObjEneMe1Gee *)find_entity_by_id(leader_id);
            leader->set_flag3c8_bit8();
        }
    }
    if (!(gee_flags & 0x100000) && child_count <= max_children / 2) {
        gee_flags |= 0x10;
    }
    if (child_count <= 2) {
        gee_flags |= 0x40;
    }
}

int TUnk_8049387C::vfunc_116(void *) {
    s32 n = 0;
    s32 i;
    for (i = 0; i < child_count; i++) {
        if (children[i]->get_committed_target() == target) {
            n++;
        }
    }
    if (TObjEneDD::check_v2_mode() != 0) {
        return n < 4;
    }
    return n < 2;
}

void TUnk_8049387C::vfunc_113() {  }

int TUnk_8049387C::vfunc_109() {
    return (u8) (this->child_count <= 0);
}

void TUnk_8049387C::update_swarm_phase() {

    s32 j;
    s32 i;

    if (this->gee_flags & 0x10) {
        this->gee_flags &= ~0x10;
        this->swarm_phase = 7;
    }
    switch (this->swarm_phase) {
    case 1:
        start_color_sequence(0);
        this->swarm_phase = 2;
        break;
    case 2:
        if (this->color_sequence == 0) {
            this->swarm_phase = 3;
            this->gee_flags &= ~8;
            copy_argb(&color, (NJS_ARGB *)((void *)&TObjEneMe1Gee__data_8043BDB0));
            for (i = 0; i < this->child_count; i++) {
                if (this->children[i]->has_gee_flags(TObjEneMe1Gee::OUT_FIGHTER) != 0) {
                    children[i]->set_flag3c8_bit4();
                }
            }
        }
        break;
    case 3:
        if (this->gee_flags & 8) {
            this->swarm_phase = 4;
        }
        break;
    case 4:
        start_color_sequence(2);
        this->swarm_phase = 5;
        break;
    case 5:
        if (this->color_sequence == 0) {
            copy_argb(&color, (NJS_ARGB *)((void *)&TObjEneMe1Gee__data_8043BDB0));
            this->swarm_phase = 6;
            for (i = 0; i < this->child_count; i++) {
                if (this->children[i]->has_gee_flags(TObjEneMe1Gee::IN_FIGHTER) != 0) {
                    children[i]->set_flag3c8_bit4();
                }
            }
        }
        break;
    case 7:
        start_color_sequence(4);
        this->swarm_phase = 8;
        break;
    case 8:
        if (this->color_sequence == 0) {
            this->swarm_phase = 9;
            copy_argb(&color, (NJS_ARGB *)((void *)&TObjEneMe1Gee__data_8043BDB0));
            for (j = 0; j < this->child_count; j++) {
                this->children[j]->fn_800CB4DC();
            }
            fn_800CB4DC();
        }
        break;
    case 9:
        break;
    }
}

void TUnk_8049387C::vfunc_110(s32 arg1) {

    s32 k;
    s32 i;
    s32 j;
    s32 m;

    switch (arg1) {
    case 4:
        requested_action = 0;
        set_field_378(4);
        this->vfunc_96();
        this->color.r = TObjEneMe1Gee__data_8043BDB0.r;
        this->color.g = TObjEneMe1Gee__data_8043BDB0.g;
        this->color.b = TObjEneMe1Gee__data_8043BDB0.b;
        this->state_step = 0;
        for (k = 2, i = 0; i < this->child_count; k += 2, i++) {
            children[i]->activate_with_target(target, k);
        }
        break;
    case 3:
        if (this->gee_flags & 2) {
            this->gee_flags &= ~2;
            this->swarm_phase = 1;
            transition_enemy_state(5);
        }
        break;
    case 0:
        advance_animation();
        update_linked_position(TObjEneMe1Gee__data_805DA0A8);
        switch (this->state_step) {
        case 0:
            (this->activation_delay)--;
            if (this->activation_delay <= 0) {
                this->color_sequence = 2;
                this->state_step = 1;
            }
            break;
        case 1:
            if (this->color_sequence == 0) {
                this->gee_flags |= 0x8000;
                for (j = 0; j < this->child_count; j++) {
                    if (this->children[j]->has_materialized() == 0) {
                        break;
                    }
                }
                if (j == this->child_count) {
                    set_flag3c8_bit2();
                    for (m = 0; m < this->child_count; m++) {
                        children[m]->set_flag3c8_bit2();
                    }
                }
            }
            update();
            break;
        }
        fn_800CBE6C(lbl_805DA0AC + position.y);
        this->vfunc_89();
        break;
    case 5:
        this->vfunc_92();
        break;
    }
}

void TUnk_8049387C::vfunc_111(s32 arg1) {
    switch (arg1) {
    case 4:
        this->requested_action = 0;
        set_field_378(5);
        this->vfunc_96();
        break;
    case 3:
        if (this->gee_flags & 4) {
            this->vfunc_105();
        }
        break;
    case 0:
        advance_animation();
        update_linked_position(TObjEneMe1Gee__data_805DA0A8);
        update();
        update_animation_frame();
        this->vfunc_89();
        break;
    case 5:
        break;
    }
}

void TUnk_8049387C::vfunc_112(s32 arg1) {
    switch (arg1) {
    case 4:
        create_breakup_mdl__12TBoss3VoloptFlllll((s32)gee_swarm_breakup_model, 0, texlist, &body_center_position, rotation_y);
        this->gee_flags |= 0x400000;
        distribute_experience_and_request_drop();
        return;
    case 0:
        if (this->vfunc_109() != 0) {
            send_entity_set_flags();
            queue_destruction();
        }
    case 3:
    case 1:
        return;
    case 5:
        actorFlags &= ~0x200;
        break;
    }
}

}

extern "C" const char lbl_8043BE5C[];
extern "C" const char *lbl_805D2A68 = lbl_8043BE5C;
