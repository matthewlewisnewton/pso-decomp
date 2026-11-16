#ifndef PSO_BOSS_TBOSS7JOINT_H
#define PSO_BOSS_TBOSS7JOINT_H

#include "types.h"
#include "pso/enemy/TObjEneDD.h"

struct TBoss7DeRolLeC;

struct TBoss7Joint : public TObjEneDD {
    virtual ~TBoss7Joint();
    void init_boss_stats();
    virtual void vfunc_62();
    virtual void clear_harmful_statuses();
    virtual void apply_shock_status();
    virtual void apply_movement_ailment(s32);
    virtual void apply_confusion_status();
    virtual void apply_slow_status();
    virtual void apply_paralysis();
    virtual void apply_poison_status();
    virtual void vfunc_61();
    virtual void vfunc_63();
    virtual void vfunc_28();
    virtual void vfunc_88();
    virtual void vfunc_93();
    u8 unk_38c[0x10];
    u32 m_3b8;
    u8 _pad3BC[0x4];
    u32 m_3c0;
    u32 m_3c4;
    void store_position();
    void run_task();
    s32 init_params();
    static TBoss7DeRolLeC *get_state();
    int is_part_active();
    u8 unk_3AC[0x1C];
};

typedef char TBoss7Joint_size[sizeof(TBoss7Joint) == 0x3C8 ? 1 : -1];

extern "C" {
TBoss7Joint *TBoss7Joint__ct(TBoss7Joint *joint, TBoss7DeRolLeC *boss, u16 entity_id, s16 set_index,
                            Vec *position, s32 segment);
void TBoss7Joint__vt85(void);
void *__dt__11TBoss7JointFv(void *arg0, s16 arg1);
}

#endif
