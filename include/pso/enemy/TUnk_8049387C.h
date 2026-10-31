#ifndef PSO_ENEMY_TUNK_8049387C_H
#define PSO_ENEMY_TUNK_8049387C_H
#include "types.h"
#include "pso/enemy/TObjEneMe1Gee.h"

class TUnk_8049387C : public TObjEneMe1Gee {
public:
    virtual ~TUnk_8049387C();
    virtual void run_task();
    virtual void vfunc_107();
    virtual void remove_child(TObjEneMe1Gee *child);
    virtual void vfunc_106();
    virtual void vfunc_105();
    virtual s32 vfunc_108();
    virtual int vfunc_116(void *target);
    virtual void vfunc_113();
    virtual int vfunc_109();
    virtual void vfunc_110(s32);
    virtual void vfunc_111(s32);
    virtual void vfunc_112(s32);
    void update_swarm_phase();
    s32 max_children;
    s32 child_count;
    TObjEneMe1Gee *children[8];
    s32 swarm_phase;
};

typedef char GeeSwarmCountOffset[offsetof(TUnk_8049387C, child_count) == 0x494 ? 1 : -1];
typedef char GeeSwarmChildrenOffset[offsetof(TUnk_8049387C, children) == 0x498 ? 1 : -1];
typedef char GeeSwarmSize[sizeof(TUnk_8049387C) == 0x4BC ? 1 : -1];
#endif
