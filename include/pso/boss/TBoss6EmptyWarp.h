#ifndef PSO_BOSS_TBOSS6EMPTYWARP_H
#define PSO_BOSS_TBOSS6EMPTYWARP_H

#include "types.h"
#include "pso/TObject.h"

struct TBoss6EmptyWarp : public TObject {
    virtual ~TBoss6EmptyWarp();
    void render();
    void run_task();
    static void *create();
    static void init_warp();
    u8 unk_1C[0x4];
};

typedef char TBoss6EmptyWarp_size[sizeof(TBoss6EmptyWarp) == 0x20 ? 1 : -1];
#endif
