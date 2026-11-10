#include "pso/TBoss7Tentacle.h"
#include "pso/boss/Boss7DeRolLeCBehavior.h"
#include "pso/boss/TBoss7DeRolLeC.h"
#include "pso/boss/TBoss7Joint.h"
#include "pso/boss/TBoss7LaserLight.h"
#include "pso/enemy/AttackTargetHistory.h"
#include "pso/math/MatrixVector.h"
#include "pso/misc/TUnk_804F1C58.h"
#include "pso/object/TObjFish_8001ED90.h"
#include "pso/system/ArrayAllocation.h"
#include "pso/system/BmlResource.h"
#include "pso/system/ControllerInputState.h"
#include "pso/system/vector.h"
#include "pso/unk/text_8035A860.h"

namespace {
// The constructor addresses these three records from the same .data base.
struct Boss7ConstructorTables {
    u8 leading_tables[0x9C];
    u8 movement_data[0xA0];
    TObjMotionAction first_action;
    u8 before_vtable[0x118];
    void *first_virtual_entry;
};

struct SavedEnemyState {
    u32 flags;
    u8 remaining[8];
};

typedef char Boss7ActionTable_offset[offsetof(Boss7ConstructorTables, first_action) == 0x13C ? 1 : -1];
typedef char Boss7Vtable_offset[offsetof(Boss7ConstructorTables, first_virtual_entry) == 0x264 ? 1 : -1];
}

extern "C" {
extern Boss7ConstructorTables lbl_804E3BF0;
extern const Vec lbl_80473F6C;
extern const CollisionBody lbl_80473C3C;
extern BmlResource *lbl_805D6918;
extern TBoss7DeRolLeC *boss7_joint_state;
extern const char *TBoss7DeRolLeC__class_name;
extern const f32 lbl_805DEA10;
extern const f32 lbl_805DEA30;

void __ct__12TObjEneDD_STFP7TObject(TObjEneDD_ST *, TObject *);
void __ct__7TObjectFP7TObject(TObject *, TObject *);
void init_resources__13TBoss2DeRolLeFi(Boss7FloatBlock *);
void init_float_block__13TBoss2DeRolLeFPv(Boss7FloatBlock *);
void TObjPlayer__sub_802E7EA0(void *);
void fill_value_array(PointerBuffer *);
}

#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_lifetimes off
extern "C" TBoss7DeRolLeC *TBoss7DeRolLeC__ct(TBoss7DeRolLeC *boss, TObject *parent, void *set_data) {
    Boss7ConstructorTables *tables = &lbl_804E3BF0;
    __ct__12TObjEneDD_STFP7TObject(boss, parent);
    // The vtable is owned by the existing data split and used by the destructor.
    *reinterpret_cast<void ***>(reinterpret_cast<u8 *>(boss) + 0x18) = &tables->first_virtual_entry;
    init_resources__13TBoss2DeRolLeFi(&boss->float_blocks[0]);
    init_resources__13TBoss2DeRolLeFi(&boss->float_blocks[1]);
    init_resources__13TBoss2DeRolLeFi(&boss->float_blocks[2]);
    __ct__7TObjectFP7TObject(&boss->tentacle_root, NULL);

    boss->m_name = TBoss7DeRolLeC__class_name;
    if (boss7_joint_state == NULL) {
        boss7_joint_state = boss;
    }

    boss->reset_hp(get_battle_base_stats(15), get_battle_attack_params(15), get_battle_resistance_params(15));
    boss->movement = get_battle_movement_params(15);
    boss->invoke_initialization_hook(set_data);
    boss->flags = 0;
    SavedEnemyState saved;
    if (boss->exchange_object_state(&saved, 1) && (saved.flags & 0x12008) == 0x12008) {
        boss->flags |= 0x8000;
    }
    boss->init_position_vectors();
    boss->model = reinterpret_cast<void *>(get_bml_model(lbl_805D6918, 0));
    boss->texlist = TObjFish__sub_8001EDB0(lbl_805D6918, 0);
    TObjPlayer__sub_802E7EA0(boss);
    copy_collision_body(&boss->collision_body, &lbl_80473C3C);
    boss->set_collision_body(&boss->collision_body);
    boss->transform_part_positions();

    boss->motion_flags = 0;
    boss->set_action_table(&tables->first_action);
    boss->set_motion_list(lbl_805D6918->motions);
    boss->requested_action = 0;
    boss->set_animation(boss->requested_action);
    boss->set_field_b8(boss->requested_action);
    boss->check_state_flag_2();
    boss->movementParameters = tables->movement_data;
    boss->initialize_enemy_state(0x49);
    boss->m_37c = lbl_805DEA30;
    boss->enemy_init_acquire_period(30);
    boss->enemy_init_validate_period(30);

    boss->m_7a8 = 0;
    boss->effect_root = new TObject(boss);
    boss->m_62c = 0;
    boss->m_6b0 = 0;
    boss->action_sequence_index = 0;
    s32 part;
    for (part = 0; part < 20; ++part) {
        boss->segment_positions[part].x = lbl_805DEA10;
        boss->segment_positions[part].y = lbl_805DEA10;
        boss->segment_positions[part].z = lbl_805DEA10;
    }
    for (part = 0; part < 4; ++part) {
        boss->tentacle_positions[part].x = lbl_805DEA10;
        boss->tentacle_positions[part].y = lbl_805DEA10;
        boss->tentacle_positions[part].z = lbl_805DEA10;
    }

    boss->tentacle_matrices = new Mtx34[4];
    for (part = 0; part < 4; ++part) {
        set_matrix_identity(reinterpret_cast<u8 *>(&boss->tentacle_matrices[part]));
        boss->tentacles[part] = new TBoss7Tentacle(&boss->tentacle_root, boss->tentacle_matrices[part], part);
    }

    Vec joint_position = lbl_80473F6C;
    u16 next_entity_id = boss->entity_id + 1;
    s32 next_set_index = boss->set_index + 1;
    for (part = 0; part < 10; ++part) {
        VecCopy(&boss->joint_positions[part], &joint_position);
        TBoss7Joint *joint = static_cast<TBoss7Joint *>(TObject::operator new(sizeof(TBoss7Joint)));
        if (joint != NULL) {
            joint = TBoss7Joint__ct(joint, boss, next_entity_id++, next_set_index++, &boss->joint_positions[part], part);
        }
        boss->joints[part] = joint;
    }

    boss->m_6c0 = 0;
    boss->m_6c4 = 0;
    boss->m_6c8 = 0;
    boss->m_6cc = 0;
    boss->m_6d0 = 0;
    init_float_block__13TBoss2DeRolLeFPv(&boss->float_blocks[0]);
    init_float_block__13TBoss2DeRolLeFPv(&boss->float_blocks[1]);
    init_float_block__13TBoss2DeRolLeFPv(&boss->float_blocks[2]);
    boss->m_6ec.x = lbl_805DEA10;
    boss->m_6ec.y = lbl_805DEA10;
    boss->m_6ec.z = lbl_805DEA10;
    boss->m_6f8 = boss->m_6fc = boss->movement->m_18;
    boss->m_700 = boss->movement->m_20;
    boss->hp = 20000;
    boss->hpmax = 20000;
    boss->m_704 = 0;

    boss->laser_light = new TBoss7LaserLight(&boss->tentacle_root, &boss->laser_position);
    boss->laser_position.x = lbl_805DEA10;
    boss->laser_position.y = lbl_805DEA10;
    boss->laser_position.z = lbl_805DEA10;
    boss->attack_history = new AreaAttackHistory(4);
    fill_value_array(boss->attack_history);
    s32 index;
    boss->m_71c = NULL;
    boss->m_720 = NULL;
    for (index = 0; index < 3; ++index) {
        VecCopy(&boss->recent_positions[index], &boss->position);
    }

    boss->m_6bc = 0;
    boss->segment_matrices = new Mtx34[12];
    for (index = 0; index < 12; ++index) {
        set_matrix_identity(reinterpret_cast<u8 *>(&boss->segment_matrices[index]));
    }
    for (index = 0; index < 6; ++index) {
        boss->effects[index] = NULL;
    }

    boss->m_7a0 = 0;
    boss->m_724 = 0;
    boss->m_728 = 0;
    boss->m_72c = 0;
    boss->m_730 = 0;
    boss->m_734 = 0;
    boss->m_738 = 0;
    boss->m_73c = 0;
    boss->m_740 = 0;
    boss->m_744[0] = lbl_805DEA10;
    boss->m_744[1] = lbl_805DEA10;
    boss->m_744[2] = lbl_805DEA10;
    boss->m_744[3] = lbl_805DEA10;
    boss->m_744[4] = lbl_805DEA10;
    boss->m_744[5] = lbl_805DEA10;
    boss->m_744[6] = lbl_805DEA10;
    boss->m_744[7] = lbl_805DEA10;
    boss->m_744[8] = lbl_805DEA10;
    boss->m_744[9] = lbl_805DEA10;
    boss->m_744[10] = lbl_805DEA10;
    boss->m_744[11] = lbl_805DEA10;
    boss->m_744[12] = lbl_805DEA10;
    boss->m_744[13] = lbl_805DEA10;
    boss->m_744[14] = lbl_805DEA10;
    boss->m_744[15] = lbl_805DEA10;
    boss->m_784 = NULL;
    boss->m_6ac = 0;
    boss->controller = &controller_input_state.controllers[1];

    if (boss->is_main_phase_15()) {
        if (boss->update_lobby_state()) {
            boss->m_6b8 = 0;
        } else {
            boss->m_6b8 = 1;
        }
    } else {
        boss->m_6b8 = 0;
    }
    TBoss7DeRolLeC__sub_802EC994(boss);
    if (!(boss->flags & 0x8000)) {
        boss->mode = 1;
        boss->dispatch_action(boss->mode, 4);
    }

    void *storage = TObject::operator new(sizeof(TUnk_804F1C58));
    if (storage != NULL) {
        storage = fn_8035A860(static_cast<u8 *>(storage), reinterpret_cast<s32>(boss), reinterpret_cast<s32>(boss->model));
    }
    boss->matrix_cache = static_cast<TUnk_804F1C58 *>(storage);
    if (boss->matrix_cache != NULL) {
        boss->matrix_cache->set_capture_callback(TObjPlayer__sub_802E8274);
    }

    boss->m_7b0 = 0;
    boss->m_7b4[0] = lbl_805DEA10;
    boss->m_7b4[1] = lbl_805DEA10;
    boss->m_7b4[2] = lbl_805DEA10;
    boss->m_7b4[3] = lbl_805DEA10;
    boss->m_7b4[4] = lbl_805DEA10;
    boss->m_7b4[5] = lbl_805DEA10;
    boss->m_7cc = 0xFFFF;
    boss->m_7ce = 0xFFFF;
    boss->m_7d0 = 0xFFFF;
    boss->m_7d2 = 0xFFFF;
    return boss;
}
#pragma pop
