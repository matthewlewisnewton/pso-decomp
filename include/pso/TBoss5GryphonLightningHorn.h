#ifndef PSO_TBOSS5GRYPHONLIGHTNINGHORN_H
#define PSO_TBOSS5GRYPHONLIGHTNINGHORN_H
#include "pso/TBoss5GryphonLightning.h"
#include "types.h"

class TBoss5GryphonLightningHorn : public TBoss5GryphonLightning {
public:
    TBoss5GryphonLightningHorn(TObject *parent, const Vec *source, s32 angle);
    virtual ~TBoss5GryphonLightningHorn();
    void rebuild_lightning_segments();
    Vec velocity;
    s32 angle;
    virtual void run_task();
    virtual void render();
public:
};

typedef char GryphonLightningHornSize[sizeof(TBoss5GryphonLightningHorn) == 0xA8 ? 1 : -1];
typedef char GryphonLightningHornVelocity[offsetof(TBoss5GryphonLightningHorn, velocity) == 0x98 ? 1 : -1];
typedef char GryphonLightningHornAngle[offsetof(TBoss5GryphonLightningHorn, angle) == 0xA4 ? 1 : -1];

#endif
