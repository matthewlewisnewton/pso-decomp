#ifndef PSO_BOSS_TBOSS2JOINT_H
#define PSO_BOSS_TBOSS2JOINT_H

#include "types.h"
#include "pso/enemy/TObjEneDD.h"

struct TBoss2Joint : public TObjEneDD {
    virtual ~TBoss2Joint();
    virtual void vfunc_62();
    virtual void clear_harmful_statuses();
    virtual void apply_shock_status();
    virtual void apply_movement_ailment(s32);
    virtual void apply_confusion_status();
    virtual void apply_slow_status();
    virtual void apply_paralysis();
    virtual void apply_poison_status();
    virtual void vfunc_28();
    virtual void vfunc_63();
    virtual void vfunc_61();
    virtual void vfunc_88();
    virtual void vfunc_93();
    virtual void vfunc_105();
    void call_36A90_with_1();
    void init_joint_offset(s32 arg1);
    void update_position_history();
    void run_task();
    s32 init_params();
    void render();
    s32 m_38c;
    u8 unk_390[0x18];
    f32 m_3a8;
    u8 unk_3AC[0x10];
};

typedef char TBoss2Joint_size[sizeof(TBoss2Joint) == 0x3BC ? 1 : -1];

extern "C" {
u8 *TBoss2Joint__ct(u8 *arg0, u8 *arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6);
void TBoss2Joint__sub_8003688C(u8 *arg0);
void *__dt__11TBoss2JointFv(void *arg0, s16 arg1);
}

#endif
