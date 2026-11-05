#ifndef PSO_TBOSS7PHOTONPAD_H
#define PSO_TBOSS7PHOTONPAD_H
#include "pso/TObject.h"
#include "types.h"
#include <dolphin/mtx/GeoTypes.h>

class TBoss7PhotonPad : public TObject {
public:
    TBoss7PhotonPad(TObject *parent, const Vec *origin, const Vec *direction, s32 level);
    virtual ~TBoss7PhotonPad();
    virtual void run_task();
    virtual void render();
    const Vec *origin;
    Vec pos;
    s32 level;
    s32 shots;
    s32 timer;
};

#endif
