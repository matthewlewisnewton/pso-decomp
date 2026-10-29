#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/enemy/TObjEnemy.h"
#include "pso/system/EnemyBmlResource.h"
#include "pso/system/BmlResourceClass.h"
#include "types.h"
#include "pso/player/TObjEneRe2Flower_Bomb.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/enemy/TObjEneDD_ST.h"
#include "pso/object/TObjMotion.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjChara.h"
#include "pso/enemy/TObjEneRe2Flower.h"
#include "pso/map/FloorArea.h"

#include "pso/player/TUnk_804928CC.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/system/BmlResource.h"
#include "pso/system/EnemyBmlResource.h"
#include "pso/npc/NpcAnimationBinding.h"
#include "pso/system/vector.h"
#include "pso/animation/ActorAnimationState.h"

#include "pso/misc/TLobby.h"
#include "pso/npc/NpcModelRegistry.h"

struct FlowerMotionSetup {
    BmlMotionEntry *motions;
    u32 unknown04;
    u32 unknown08;
    u32 unknown0c;
};

struct FlowerContactAttack {
    f32 power;
    u32 targetFlags;
};

extern "C" {
s32 TObjPlayer__sub_800F0928();
extern const FlowerMotionSetup lbl_8043BB90;
extern const char lbl_8043BBE0[];
extern const char lbl_8043BBF4[];
extern s32 lbl_805D5178, lbl_805D517C, lbl_805D5180;
extern u32 lbl_805D5174;
extern const char *lbl_805D2A48;
extern s32 lbl_8043BA7C[3], lbl_8043BA88[3], lbl_8043BA94[3], lbl_8043BAA0[3];
extern void *lbl_805D5170;
extern const f32 lbl_805D9FAC, lbl_805D9FBC, lbl_805D9FD8, lbl_805D9FFC, lbl_805DA000;
extern char lbl_8043BAAC[], lbl_8043BAC4[], lbl_8043BADC[], lbl_8043BAF4[];
extern char lbl_8043BB08[], lbl_8043BB20[], lbl_8043BB38[], lbl_8043BB50[], lbl_8043BB64[];
void TObjEneRe2Flower__sub_800C3BA8(TObjEneRe2Flower *);
void TObjEneDD__sub_800C2628(u8 *, s32);
void fn_800C2A88(void *, s32);
void fn_800C2AC4(u8 *, int);
s32 TObjEneRe2Flower__sub_800C2E64(void *, void *);
void fn_800C3088(u8 *, int);
void fn_800C32DC(u8 *, s32);
void handle_flower_state_change(TObjEneDD *, s32);
s32 obj_is_hit_receivable(void *);
f32 fabs_float(f32);
s32 is_area_attack_target_eligible(s32, s32);
s32 attack_target_history_add(s32, s32);
void TLobby__sub_8001FE7C(void *, int);
void free_collision_body_parts(void *);
void TObjPlayer__sub_800C4D44(void);
extern void *tl_04;
}

struct FlowerSetupData {
    f32 value00;
    u32 unknown04;
    u32 flags;
    u32 unknown0c[4];
};
typedef char FlowerSetupData_size[sizeof(FlowerSetupData) == 0x1C ? 1 : -1];
FlowerSetupData TObjEneRe2Flower__setup_data = {
    225.0f, 0, 0x200, {0, 0, 0, 0}
};
CollisionBody flower_normal_collision_parts[2] = {
    {{0.0f, 0.0f, 0.0f}, 5.0f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 5.0f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f}
};
CollisionBody flower_tower_collision_parts[2] = {
    {{0.0f, 0.0f, 0.0f}, 10.0f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 20.0f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f}
};
__declspec(section ".data") const char *bm_ene_re2_flower_model_names[2] = {
    lbl_8043BAAC, NULL
};
const char *bm_ene_re2_flower_motion_names[8] = {
    lbl_8043BAC4, lbl_8043BADC, lbl_8043BAF4, lbl_8043BB08,
    lbl_8043BB20, lbl_8043BB38, lbl_8043BB50, NULL
};
BmlResourceDescriptor TObjEneRe2Flower__resource_descriptor = {
    lbl_8043BB64, bm_ene_re2_flower_model_names,
    bm_ene_re2_flower_motion_names, 1, 7
};
TObjMotionAction TObjEneRe2Flower__animation_descriptors[8] = {
    {3, 0, 0, 0.6f, 0}, {1, 0, 4, 0.3f, 0},
    {1, 0, 5, 0.5f, 0}, {2, 2, 6, 0.6f, 0},
    {3, 0, 1, 0.5f, 0}, {3, 0, 2, 0.5f, 0},
    {1, 0, 3, 0.6f, 0}, {1, 0, 0, 2.0f, 0}
};


s32 TObjEneRe2Flower_Bomb::area_attack_deliver_direct(void *recoil, s32 attackData, void *history, f32 range) {
    s32 result = 0;
    u32 contactFlags = 0;
    TObjChara *target;
    s32 i;
    if (m_ac == 0) {
        return 0;
    }
    TObjPlayer::init_all_slots();
    if (((FlowerContactAttack *)recoil)->targetFlags & 1) {
        update_body_contact_flag(range);
        contactFlags |= 0x80000;
    }
    if (((FlowerContactAttack *)recoil)->targetFlags & 2) {
        mark_enemy_body_contacts();
        contactFlags |= 0x100000;
    }
    if (bodies->flags & contactFlags) {
        for (i = 0; i < 16; i++) {
            target = (TObjChara *)TObjPlayer::get_battle_param(i);
            if (target == NULL) {
                break;
            }
            if (obj_is_hit_receivable(target) != 0 && (u32)target != m_ac &&
                is_area_attack_target_eligible((s32)this, target->actorFlags) != 0 &&
                !(fabs_float(startPosition.y - target->m_300) > lbl_805DA000)) {
                s32 eligible = 1;
                if (history != NULL && attack_target_history_add((s32)history, (s32)target) == 0) {
                    eligible = 0;
                }
                if (eligible != 0) {
                    area_attack_receive_direct(target, (f32 *)recoil, (void *)attackData);
                    result = 1;
                }
            }
        }
    }
    return result;
}

void TObjEneRe2Flower::initialize_resources() {
    FlowerMotionSetup motionSetup;
    if (get_current_floor_area() == AREA_TOWER) {
        lbl_805D5174 = (u32)load_enemy_bml_resource_named(&TObjEneRe2Flower__resource_descriptor, lbl_8043BBE0);
    } else if (TObjEneDD::check_v2_mode() != 0) {
        lbl_805D5174 = (u32)load_enemy_bml_resource_named(&TObjEneRe2Flower__resource_descriptor, lbl_8043BBF4);
    } else {
        lbl_805D5174 = (u32)load_enemy_bml_resource(&TObjEneRe2Flower__resource_descriptor);
    }
    lbl_805D5178 = 0;
    lbl_805D517C = 0;
    lbl_805D5180 = 0;
    TObjPlayer::create_render_texture();
    TObjPlayer__sub_800F0928();
    motionSetup.motions = lbl_8043BB90.motions;
    motionSetup.unknown04 = lbl_8043BB90.unknown04;
    motionSetup.unknown08 = lbl_8043BB90.unknown08;
    motionSetup.unknown0c = lbl_8043BB90.unknown0c;
    motionSetup.motions = ((BmlResource *)lbl_805D5174)->motions;
    BmlModelEntry *modelEntry = ((BmlResource *)lbl_805D5174)->models;
    NpcModelRegistry::register_animated_chunk(0x37, modelEntry->model, modelEntry->m_c,
                          (const NpcAnimationBinding *)&motionSetup, lbl_805D9FBC, lbl_805D9FAC);
}

void *TObjEneRe2Flower::create(void *arg0) {
    return new TObjEneRe2Flower((TObject *)tl_04, arg0);
}

void TObjEneRe2Flower::destroy_instance() {
    TObjPlayer__sub_800C4D44();
    if ((u32) lbl_805D5174 != 0U) {
        delete (BmlResource *)((void*)lbl_805D5174);
        lbl_805D5174 = 0U;
    }
}

TObjEneRe2Flower::TObjEneRe2Flower(TObject *parent, void *setData)
    : TObjEneDD_ST(parent) {
    m_name = lbl_805D2A48;
    invoke_initialization_hook(setData);
    TObjEneRe2Flower__sub_800C3BA8(this);
    flowerFlags = 0;
    if (get_current_floor_area() == AREA_TOWER) {
        flowerFlags |= 0x800;
    } else if (random_ratio() <= lbl_805D9FFC) {
        flowerFlags |= 0x400;
    }
    init_position_vectors();
    model = (void *)((BmlResource *)lbl_805D5174)->models->model;
    texlist = ((BmlResource *)lbl_805D5174)->models->m_c;
    if (get_flag_11())
        init_model(flower_tower_collision_parts, 2);
    else
        init_model(flower_normal_collision_parts, 2);
    set_field_d8((s32)TObjEneRe2Flower__animation_descriptors);
    set_field_dc((s32)((BmlResource *)lbl_805D5174)->motions);
    m_b8 = 1;
    set_animation(m_b8);
    set_field_b8(m_b8);
    sub_8002AE64();
    s32 variantIndex;
    if (get_flag_11()) variantIndex = 2;
    else if (sub_800C3B8C()) variantIndex = 1;
    else variantIndex = 0;
    reset_hp((BattleBaseStats *)TLobby::register_boss(lbl_8043BA7C[variantIndex]),
             (AttackParams *)TLobby::dispatch_shared_handler_b(lbl_8043BA88[variantIndex]),
             (ActorParamBlock *)TLobby::register_object(lbl_8043BA94[variantIndex]));
    lbl_805D5170 = TLobby::dispatch_shared_handler_a(lbl_8043BAA0[variantIndex]);
    if (get_flag_11()) set_state_8();
    else check_state_flag_2();
    movementParameters = &TObjEneRe2Flower__setup_data;
    if (get_flag_11()) initialize_enemy_state(0x53);
    else if (sub_800C3B8C()) initialize_enemy_state(0x0e);
    else initialize_enemy_state(0x0d);
    m_37c = lbl_805D9FBC;
    enemy_init_acquire_period(30);
    enemy_init_validate_period(30);
    renderRotationY = rotation_y;
    renderOffsetY = lbl_805D9FAC;
    m_3cc = 0;
    m_3d0 = 0;
    m_3d4 = 0;
    m_3d8 = 0;
    for (s32 i = 0; i < 2; i++) {
        VecCopy(&renderAnchors[i], &position);
        renderAnchors[i].y += lbl_805D9FD8;
    }
    fade.reset_obstruction_fade();
    m_410 = 0;
    m_414 = 0;
    m_418 = 0;
    m_41c = 0;
    m_420 = 0;
    m_424 = lbl_805D9FAC;
    m_428 = NULL;
    sub_800C3DC4();
    vfunc_88();
    transform_part_positions();
    mode = 0;
    dispatch_action(mode, 4);
}

TObjEneRe2Flower::~TObjEneRe2Flower() {
    if (m_428 != NULL) {
        m_428->queue_destruction();
        m_428 = NULL;
    }
    free_collision_body_parts(this);
}

void TObjEneRe2Flower::run_task() {
    s16 currentMode;
    if (TObjPlayer::check_demo_mode() != 0) {
        this->vfunc_105();
        return;
    }
    if (this->vfunc_83() != 4) {
        this->vfunc_85();
    } else {
        currentMode = mode;
        if ((currentMode == 0) || (currentMode == 1)) {
            fade.reset_color();
            transition_enemy_state(2);
        }
    }
    this->sub_800C3DC4();
    submit_default_cursor_candidate();
    this->vfunc_100();
}

void TObjEneRe2Flower::dispatch_action(u32 state, s32 reason) {
    switch (state) {
    case 0:
        dispatch_action(reason);
        return;
    case 1:
        handle_state(reason);
        return;
    case 2:
        handle_flower_state_change(this, reason);
        return;
    case 3:
        state_chase_target(reason);
        return;
    case 4:
        fn_800C32DC((u8 *)this, reason);
        return;
    case 5:
        fn_800C3088((u8 *)this, reason);
        return;
    case 9:
        state_damaged(reason);
        return;
    case 10:
        fn_800C2AC4((u8 *)this, reason);
        return;
    case 6:
        TObjEneRe2Flower__sub_800C2E64((void *)this, (void *)reason);
        return;
    case 7:
        handle_event(reason);
        return;
    case 8:
        TObjEneDD__sub_800C2628((u8 *)this, reason);
        return;
    case 11:
        fn_800C2A88((void *)this, reason);
    default:
        return;
    }
}

void TObjEneRe2Flower::vfunc_28() {  }

void TObjEneRe2Flower::vfunc_63() {
    s16 currentMode;

    currentMode = mode;
    if ((currentMode != 0xA) && (currentMode != 0xB)) {
        transition_enemy_state(0xA);
    }
}

void TObjEneRe2Flower::vfunc_62() {
    s16 currentMode;

    currentMode = mode;
    if (currentMode != 9) {
        if (currentMode == 8) {
            begin_state_242();
            clear_attack_receipts();
            return;
        }
        transition_enemy_state(9);
    }
}

void TObjEneRe2Flower::vfunc_61() {  }
