#ifndef PSO_BOSS_BARBARAY_TBOSS7PHOTONPAD_H
#define PSO_BOSS_BARBARAY_TBOSS7PHOTONPAD_H
#include "pso/system/task/TObject.h"
#include "pso/system/vector.h"
#include "types.h"

class TBoss7PhotonPad : public TObject {
public:
    TBoss7PhotonPad(TObject *parent, const Vec *arg2, const Vec *arg3, s32 arg4);
    virtual ~TBoss7PhotonPad();
    virtual void run_task();
    virtual void render();
public:
};

#endif
