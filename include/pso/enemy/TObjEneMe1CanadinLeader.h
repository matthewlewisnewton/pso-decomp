#ifndef PSO_ENEMY_TOBJENEME1CANADINLEADER_H
#define PSO_ENEMY_TOBJENEME1CANADINLEADER_H

#include "pso/enemy/TObjEneMe1Canadin.h"

struct TObjEneMe1CanadinLeader : public TObjEneMe1Canadin
{
    TObjEneMe1CanadinLeader(TObject *parent, void *set_data);
    virtual ~TObjEneMe1CanadinLeader();
    void run_task();
    virtual void vfunc_105();
    virtual void vfunc_106();
    virtual void vfunc_107();
    virtual s32 vfunc_108();
    virtual int vfunc_109();
    virtual void vfunc_110(s32);
    virtual void vfunc_111(s32);
    virtual void vfunc_112(s32);
    virtual void vfunc_113();
    virtual int vfunc_116(TObjChara *);
    virtual void vfunc_117(TObjEneMe1Canadin *);
    s32 m_4cc;
    s32 m_4d0;
    TObjEneMe1Canadin *m_4d4[8];
    s32 m_4f4;
    void update_formation_state();
    static void *create(void *arg0);
    static f32 get_status_value_f32();
    static TObjEneMe1Canadin *create_canadin(TObjEneMe1Canadin *leader, Vec *position, s32 id, s32 index);
};

typedef char CanadinLeaderSize[sizeof(TObjEneMe1CanadinLeader) == 0x4F8 ? 1 : -1];
typedef char CanadinLeaderMembersOffset[offsetof(TObjEneMe1CanadinLeader, m_4d4) == 0x4D4 ? 1 : -1];

#endif
