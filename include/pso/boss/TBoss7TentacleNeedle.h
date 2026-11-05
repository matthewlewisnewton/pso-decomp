#ifndef PSO_BOSS_TBOSS7TENTACLENEEDLE_H
#define PSO_BOSS_TBOSS7TENTACLENEEDLE_H

#include "types.h"
#include "pso/TObject.h"
#include <dolphin/mtx/GeoTypes.h>
#include <stddef.h>

class TParticleCtrl;

struct TBoss7TentacleNeedle : public TObject {
    TBoss7TentacleNeedle(TObject *parent, Vec *position);
    virtual ~TBoss7TentacleNeedle();
    void advance_needle_timer();
    Vec position;
    u32 m_28;
    u32 m_2c;
    u32 m_30;
    f32 m_34;
    u32 m_38;
    s32 m_3c;
    TParticleCtrl *m_40;
    s32 target_flags[12];
    f32 m_74;
    u32 m_78;
    virtual void render();
    virtual void run_task();
};

typedef char TBoss7TentacleNeedle_size[sizeof(TBoss7TentacleNeedle) == 0x7C ? 1 : -1];
typedef char NeedlePositionOffset[offsetof(TBoss7TentacleNeedle, position) == 0x1C ? 1 : -1];
typedef char NeedleParticleOffset[offsetof(TBoss7TentacleNeedle, m_40) == 0x40 ? 1 : -1];
typedef char NeedleTargetFlagsOffset[offsetof(TBoss7TentacleNeedle, target_flags) == 0x44 ? 1 : -1];
typedef char NeedleTimerOffset[offsetof(TBoss7TentacleNeedle, m_74) == 0x74 ? 1 : -1];

#endif
