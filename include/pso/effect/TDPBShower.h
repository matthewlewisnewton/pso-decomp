#ifndef PSO_EFFECT_TDPBSHOWER_H
#define PSO_EFFECT_TDPBSHOWER_H

#include "pso/TObject.h"
#include <dolphin/mtx/GeoTypes.h>

class TParticleCtrl;

class TDPBShower : public TObject {
public:
    Vec m_position;
    s32 m_countdown;
    TParticleCtrl *m_emitter;

    TDPBShower(TObject *parent, const Vec *position);
    virtual ~TDPBShower();
    virtual void run_task();
};

#include <stddef.h>
typedef char TDPBShowerSize[(sizeof(TDPBShower) == 0x30) ? 1 : -1];
typedef char TDPBShowerPositionOffset[(offsetof(TDPBShower, m_position) == 0x1C) ? 1 : -1];
typedef char TDPBShowerCountdownOffset[(offsetof(TDPBShower, m_countdown) == 0x28) ? 1 : -1];
typedef char TDPBShowerEffectOffset[(offsetof(TDPBShower, m_emitter) == 0x2C) ? 1 : -1];

// Legacy callers pass a task parent and the address of three position floats.
void *create_TDPBShower(void *parent, void *position);

#endif
