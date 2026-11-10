#ifndef PSO_BOSS_TBOSS7DEROLLEC_H
#define PSO_BOSS_TBOSS7DEROLLEC_H

#include "types.h"
#include "pso/enemy/TObjEneDD_ST.h"

struct ControllerInputContext;
struct TBoss7Joint;
class AreaAttackHistory;
class TBoss7LaserLight;
class TBoss7Tentacle;
class TUnk_804F1C58;

struct Boss7FloatBlock {
    u32 active;
    f32 values[7];
};

struct TBoss7DeRolLeC : public TObjEneDD_ST {
    virtual ~TBoss7DeRolLeC();
    void update_projectile_spawns();
    virtual void run_task();
    virtual void render();
    void update_or_dispatch();
    void flee_if_disturbed();
    void set_state_and_send(s32);
    void emit_hit_effect(void *arg1);
    u8 sub_802ECB10();
    void sub_802ECAA4();
    void advance_action_sequence();
    void sub_802E8234();
    void set_flag_800();
    virtual void vfunc_88();
    virtual void render_shadows();
    void vfunc_63();
    void vfunc_62();
    void vfunc_61();
    void clear_harmful_statuses();
    void apply_shock_status();
    void apply_movement_ailment(s32);
    void apply_confusion_status();
    void apply_slow_status();
    void apply_paralysis();
    void apply_poison_status();
    void vfunc_28();
    CollisionBody collision_body;
    Vec segment_positions[20];
    Vec tentacle_positions[4];
    Vec recent_positions[3];
    Vec joint_positions[10];
    u8 unknown_5a8[0x50];
    TBoss7Joint *joints[10];
    BattleMovementParams *movement;
    ControllerInputContext *controller;
    u32 flags;
    u32 m_62c;
    Boss7FloatBlock float_blocks[3];
    TObject tentacle_root;
    u32 m_6ac;
    u32 m_6b0;
    u32 action_sequence_index;
    u32 m_6b8;
    u32 m_6bc;
    u32 m_6c0;
    u32 m_6c4;
    u32 m_6c8;
    u32 m_6cc;
    u32 m_6d0;
    Mtx34 *segment_matrices;
    Mtx34 *tentacle_matrices;
    TBoss7Tentacle *tentacles[4];
    Vec m_6ec;
    u32 m_6f8;
    u32 m_6fc;
    u32 m_700;
    u32 m_704;
    TBoss7LaserLight *laser_light;
    Vec laser_position;
    AreaAttackHistory *attack_history;
    TObject *m_71c;
    TObject *m_720;
    u32 m_724;
    u32 m_728;
    u32 m_72c;
    u32 m_730;
    u32 m_734;
    u32 m_738;
    u32 m_73c;
    u32 m_740;
    f32 m_744[16];
    TObject *m_784;
    TObject *effects[6];
    u32 m_7a0;
    TObject *effect_root;
    u32 m_7a8;
    TUnk_804F1C58 *matrix_cache;
    u32 m_7b0;
    f32 m_7b4[6];
    u16 m_7cc;
    u16 m_7ce;
    u16 m_7d0;
    u16 m_7d2;

    static void run_exit_callbacks();
    static void *create(void *arg0);
};

typedef char TBoss7DeRolLeC_size[sizeof(TBoss7DeRolLeC) == 0x7D4 ? 1 : -1];
typedef char TBoss7DeRolLeC_collision_body_offset[offsetof(TBoss7DeRolLeC, collision_body) == 0x3C0 ? 1 : -1];
typedef char TBoss7DeRolLeC_tentacle_root_offset[offsetof(TBoss7DeRolLeC, tentacle_root) == 0x690 ? 1 : -1];
typedef char TBoss7DeRolLeC_action_sequence_offset[offsetof(TBoss7DeRolLeC, action_sequence_index) == 0x6B4 ? 1 : -1];
typedef char TBoss7DeRolLeC_matrix_cache_offset[offsetof(TBoss7DeRolLeC, matrix_cache) == 0x7AC ? 1 : -1];
extern "C" TBoss7DeRolLeC *TBoss7DeRolLeC__ct(TBoss7DeRolLeC *boss, TObject *parent, void *set_data);

#endif
