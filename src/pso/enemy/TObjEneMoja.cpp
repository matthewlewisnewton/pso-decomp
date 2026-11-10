#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/system/ArrayAllocation.h"
#include "pso/enemy/BattleParameters.h"
#include "pso/enemy/TObjEneMoja.h"
#include "pso/TObjControl.h"
#include "pso/unk/TUnk_80494968.h"
#include "pso/misc/SampledMotionPoints.h"
#include "pso/npc/NpcAnimationBinding.h"
#include "pso/npc/NpcModelRegistry.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/player/demo_mode.h"

namespace {

// The constructor selects one of these 0x1C-byte records by variant.
struct MojaMovementParameters {
    f32 target_range;
    f32 movement_speed;
    s32 turn_step;
    u32 unknown_0c;
    u32 unknown_10;
    u32 unknown_14;
    u32 unknown_18;
};

typedef char MojaMovementParametersSize[sizeof(MojaMovementParameters) == 0x1C ? 1 : -1];

struct MojaNpcModelIds {
    s16 ids[3];
};

}

extern "C" {
// File names live in the original read-only data range.
extern const char lbl_8043AEF8[], lbl_8043AF0C[], lbl_8043AF20[];
extern const char lbl_8043AF34[], lbl_8043AF50[], lbl_8043AF6C[], lbl_8043AF88[], lbl_8043AFA4[], lbl_8043AFC0[];
extern const char lbl_8043AFDC[], lbl_8043AFF4[], lbl_8043B010[], lbl_8043B02C[], lbl_8043B048[], lbl_8043B064[], lbl_8043B078[];

// The descriptors, actions and collision body share the original .data base.
const char *moja_enemy_standard_model_names[4] = {lbl_8043AEF8, lbl_8043AF0C, lbl_8043AF20, NULL};
const char *moja_enemy_standard_motion_names[12] = {
    lbl_8043AF34, lbl_8043AF50, lbl_8043AF6C, lbl_8043AF88, lbl_8043AFA4, lbl_8043AFC0,
    lbl_8043AFDC, lbl_8043AFF4, lbl_8043B010, lbl_8043B02C, lbl_8043B048, NULL
};
BmlResourceDescriptor moja_enemy_standard_descriptor = {
    lbl_8043B064, moja_enemy_standard_model_names, moja_enemy_standard_motion_names, 3, 11,
};
const char *moja_enemy_ultimate_model_names[4] = {lbl_8043AEF8, lbl_8043AF0C, lbl_8043AF20, NULL};
const char *moja_enemy_ultimate_motion_names[12] = {
    lbl_8043AF34, lbl_8043AF50, lbl_8043AF6C, lbl_8043AF88, lbl_8043AFA4, lbl_8043AFC0,
    lbl_8043AFDC, lbl_8043AFF4, lbl_8043B010, lbl_8043B02C, lbl_8043B048, NULL
};
BmlResourceDescriptor moja_enemy_ultimate_descriptor = {
    lbl_8043B078, moja_enemy_ultimate_model_names, moja_enemy_ultimate_motion_names, 3, 11,
};
TObjMotionAction moja_enemy_actions[9] = {
    { MOTION_MODE_LOOP, 0, 9, 0.5f, 0x1 },
    { MOTION_MODE_CHAIN, 2, 6, 0.7f, 0x20 },
    { MOTION_MODE_LOOP, 0, 10, 0.6f, 0x1 },
    { MOTION_MODE_CHAIN, 0, 8, 0.7f, 0x4 },
    { MOTION_MODE_CHAIN, 0, 5, 0.4f, 0x4 },
    { MOTION_MODE_CHAIN, 0, 7, 0.5f, 0x4 },
    { MOTION_MODE_CHAIN, 0, 2, 0.8f, 0x8 },
    { MOTION_MODE_ONCE, 7, 4, 0.7f, 0x10 },
    { MOTION_MODE_ONCE, 7, 3, 0.7f, 0x10 },
};
MojaMovementParameters moja_enemy_movement_parameters[2] = {
    { 250.0f, 0.75f, 0x400, 0x001E0000, 0, 0, 0 },
    { 250.0f, 0.75f, 0x400, 0, 0x001E0000, 0, 0 },
};
CollisionBody moja_enemy_collision_body = {
    { 0.0f, 20.0f, 0.0f }, 12.5f, 0.0f, 0, 0x8003, { 0.0f, 0.0f, 0.0f }, 0.0f,
};

extern const MojaNpcModelIds moja_enemy_npc_model_ids;
extern const NpcAnimationBinding moja_enemy_npc_animation_template;
extern s32 game_difficulty_selection;
extern BattleBaseStats **lbl_805D50C8;
extern AttackParams **lbl_805D50CC;
extern ActorParamBlock **lbl_805D50D0;
extern BattleMovementParams **lbl_805D50D4;
extern BmlResource *lbl_805D50D8;
extern SampledMotionPoints *lbl_805D50DC;
extern const f32 lbl_805D9BD8;
extern const f32 lbl_805D9BF8;
extern const f32 lbl_805D9C28;
extern const f32 lbl_805D9C2C;
extern const f32 lbl_805D9C5C;
extern const f32 lbl_805D9BDC;

struct Obj_800ACFE8;
struct Moja_800AE450;
struct Moja_800AE7F4;
void update_attack_jump__11TObjEneMojaFv(Obj_800ACFE8 *);
void update_appearance_drop__11TObjEneMojaFv(Moja_800AE450 *);
void update_appearance_jump__11TObjEneMojaFv(Moja_800AE7F4 *);
s32 submit_cursor_candidate(void *, int);
s32 minimap_render_dot(void *, int, int, int, f32);
s32 get_current_floor();
TObjChara *get_enemy_entity(u16);
TObjPlayer *get_player_by_client_id(s32);
extern TObject *tl_04;
extern const char *TObjEneMoja__name;
extern const f32 moja_technique_chance_offset;
extern const f32 moja_jump_chance_offset;
}

// CodeWarrior emits these definitions in reverse order with deferred code generation.
// Keep the shared clamp bounds as small-data loads in the original registers.
#pragma push
#pragma opt_common_subs off
TObjEneMoja::TObjEneMoja(TObject *parent, void *set_data) : TObjEnemy(parent) {
    m_name = TObjEneMoja__name;
    apply_set_data(set_data);
    initialize_position_copies();
    mode = 0;
    phase = 0;

    {
        techniqueChance = moja_technique_chance_offset + parameters[1];
        f32 chance = techniqueChance;
        if (chance < lbl_805D9BD8) {
            techniqueChance = lbl_805D9BD8;
        } else if (lbl_805D9BDC < chance) {
            techniqueChance = lbl_805D9BDC;
        }
    }
    {
        jumpChance = moja_jump_chance_offset + parameters[2];
        f32 chance = jumpChance;
        if (chance < lbl_805D9BD8) {
            jumpChance = lbl_805D9BD8;
        } else if (lbl_805D9BDC < chance) {
            jumpChance = lbl_805D9BDC;
        }
    }

    clamp_appearance_parameter();
    select_rare_variant();
    subtype = 1;
    action_table = moja_enemy_actions;
    set_action_table(action_table);
    motion_list = lbl_805D50D8->motions;
    requested_action = 0;
    set_animation(requested_action);
    set_field_b8(requested_action);
    init_collision_body_parts(this, &moja_enemy_collision_body, 1);

    attack = 0;
    // Both pointer tables use the same byte stride. Keeping the shared offset
    // preserves register allocation; see docs/evidence/moja-compiler-tracing.md.
    const size_t variant_offset = variant * sizeof(*lbl_805D50C8);
    bind_enemy_combat_stats(
        reinterpret_cast<u8 *>(*reinterpret_cast<BattleBaseStats **>(
            reinterpret_cast<u8 *>(lbl_805D50C8) + variant_offset)),
        reinterpret_cast<u8 *>(lbl_805D50CC[attack + variant * 3]),
        reinterpret_cast<u8 *>(*reinterpret_cast<ActorParamBlock **>(
            reinterpret_cast<u8 *>(lbl_805D50D0) + variant_offset)));
    movementParameters = &moja_enemy_movement_parameters[variant];
    referenceHp = hp;
    update_prev_position();
    copy_body_to_center();
    register_object_by_id();
    resetTimer = 0;
    timer = resetTimer;
    unused_37C = 0;
    attackSequence = -1;
    roar = 1;
    add_flags_2e4(1);
    actorFlags |= 0x40000;
    sinkOffset = lbl_805D9BD8;
    effect = TUnk_80494968::create(0xff303030, 0x0a303030);
    for (s32 i = 0; i < 4; ++i) {
        fades[i].activate_and_dispatch();
    }
    clear_lobby_object_state();
}

#pragma pop

TObjEneMoja::~TObjEneMoja() {
    if (effect != NULL) {
        effect->queue_destruction();
        effect = NULL;
    }
    free_collision_body_parts(this);
}

void TObjEneMoja::load_resources() {
    switch (game_difficulty_selection) {
    case 3:
        lbl_805D50D8 = new BmlResource(1, &moja_enemy_ultimate_descriptor, 0, 0, NULL);
        break;
    default:
        lbl_805D50D8 = new BmlResource(1, &moja_enemy_standard_descriptor, 0, 0, NULL);
        break;
    }

    SampledMotionPoints *points = new SampledMotionPoints(2, lbl_805D9C28, lbl_805D9C2C, lbl_805D9C5C);
    lbl_805D50DC = points;
    Vec origin;
    Vec offset;
    origin.x = origin.y = origin.z = lbl_805D9BD8;
    offset.x = lbl_805D9BF8;
    offset.y = lbl_805D9BD8;
    offset.z = lbl_805D9BD8;
    points->sample_node_offsets(reinterpret_cast<NJS_OBJECT *>(lbl_805D50D8->models[1].model),
        reinterpret_cast<NJS_MOTION *>(lbl_805D50D8->motions[moja_enemy_actions[3].motion].motion), 0x26, &origin, &offset);

    lbl_805D50C8 = new BattleBaseStats *[2];
    lbl_805D50CC = new AttackParams *[6];
    lbl_805D50D0 = new ActorParamBlock *[2];
    lbl_805D50D4 = new BattleMovementParams *[2];

    lbl_805D50C8[0] = get_battle_base_stats(0x49);
    lbl_805D50C8[1] = get_battle_base_stats(0x4A);
    lbl_805D50CC[0] = get_battle_attack_params(0x48);
    lbl_805D50CC[1] = get_battle_attack_params(0x49);
    lbl_805D50CC[2] = get_battle_attack_params(0x4A);
    lbl_805D50CC[3] = get_battle_attack_params(0x4B);
    lbl_805D50CC[4] = get_battle_attack_params(0x4C);
    lbl_805D50CC[5] = get_battle_attack_params(0x4D);
    lbl_805D50D0[0] = get_battle_resistance_params(0x48);
    lbl_805D50D0[1] = get_battle_resistance_params(0x49);
    lbl_805D50D4[0] = get_battle_movement_params(0x48);
    lbl_805D50D4[1] = get_battle_movement_params(0x49);

    MojaNpcModelIds model_ids = moja_enemy_npc_model_ids;
    NpcAnimationBinding binding = moja_enemy_npc_animation_template;
    binding.motions = lbl_805D50D8->motions;
    for (s32 i = 0; i < 3; ++i) {
        NpcModelRegistry::register_animated_chunk(model_ids.ids[i],
            reinterpret_cast<void *>(lbl_805D50D8->models[i].model),
            reinterpret_cast<void *>(lbl_805D50D8->models[i].m_c),
            &binding, moja_enemy_collision_body.radius, lbl_805D9BD8);
    }
}

void TObjEneMoja::free_resources() {
    if (lbl_805D50C8 != NULL) {
        ::operator delete[](lbl_805D50C8);
        lbl_805D50C8 = NULL;
    }
    if (lbl_805D50CC != NULL) {
        ::operator delete[](lbl_805D50CC);
        lbl_805D50CC = NULL;
    }
    if (lbl_805D50D0 != NULL) {
        ::operator delete[](lbl_805D50D0);
        lbl_805D50D0 = NULL;
    }
    if (lbl_805D50D4 != NULL) {
        ::operator delete[](lbl_805D50D4);
        lbl_805D50D4 = NULL;
    }
    if (lbl_805D50DC != NULL) {
        delete lbl_805D50DC;
        lbl_805D50DC = NULL;
    }
    if (lbl_805D50D8 != NULL) {
        delete lbl_805D50D8;
        lbl_805D50D8 = NULL;
    }
}

void *TObjEneMoja::create(void *arg0) {
    TObjControl *control = new TObjControl(tl_04);
    return new TObjEneMoja(control, arg0);
}

void TObjEneMoja::run_task() {
    u8 *self = reinterpret_cast<u8 *>(this);
    f32 dot_phase;
    u16 target_id;
    TObjPlayer *player;
    TObjChara *current_target;
    if (check_demo_mode() == 1) {
        fn_800ACA0C();
        return;
    }
    target_id = this->targetId;
    if (target_id < 0x1000U) {
        player = get_player_by_client_id(target_id);
        if (player != NULL) {
            if (player->get_floor() == get_current_floor()) {
                this->target = player;
                goto done;
            }
        }
        this->target = NULL;
    done:;
    } else if (target_id < 0x4000U) {
        this->target = get_enemy_entity(target_id);
    } else {
        this->targetId = 0xFFFFU;
        this->target = NULL;
    }
    {
        switch (this->mode) {
        case 0:
            update_idle_state();
            break;
        case 1:
            update_appearance_jump__11TObjEneMojaFv(reinterpret_cast<Moja_800AE7F4 *>(self));
            break;
        case 2:
            update_appearance_drop__11TObjEneMojaFv(reinterpret_cast<Moja_800AE450 *>(self));
            break;
        case 3:
            update_approach_state();
            break;
        case 4:
            TObjEneMoja::update_punch_attack(self);
            break;
        case 5:
            TObjEneMoja::update_technique_state(self);
            break;
        case 6:
            update_attack_jump__11TObjEneMojaFv(reinterpret_cast<Obj_800ACFE8 *>(self));
            break;
        case 7:
            // Pre-existing: these two TObjPlayer helpers operate on the shared
            // TObjChara/TObjMotion layout, not a player instance.
            reinterpret_cast<TObjPlayer *>(self)->update_invincibility();
            break;
        case 8:
            reinterpret_cast<TObjPlayer *>(self)->update_ground_effect();
            break;
        case 9:
            update_death_state();
            break;
        }
    }
    update_prev_position();
    copy_body_to_center();
    submit_cursor_candidate(self, -1);
    current_target = this->target;
    if ((current_target != NULL) && (current_target->actorFlags & 0x02000800)) {
        this->attackSequence = -1;
        (this->timer) = 0;
        (this->actorFlags) = (s32) ((this->actorFlags) & 0xFFDFFFFF);
        this->target = NULL;
    }
    dot_phase = this->m_2b4;
    this->m_2b4 = dot_phase + lbl_805D9BDC;
    minimap_render_dot(&this->position, -0x5DB4, 1, 0, dot_phase);
}

// Definitions follow their use so CodeWarrior references the named small-data entries.
extern "C" {
extern const f32 moja_technique_chance_offset = 0.3f;
extern const f32 moja_jump_chance_offset = 0.6f;
}
