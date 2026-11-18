#ifndef PSO_BOSS_TBOSS4URO_H
#define PSO_BOSS_TBOSS4URO_H

#include "types.h"
#include "pso/boss/TBoss4Zako.h"

struct BmlResource;

struct TBoss4Uro : public TBoss4Zako {
    virtual ~TBoss4Uro();
    void run_task();
    s32 get_phase();
    static BmlResource *get_instance_count();
};

#endif
