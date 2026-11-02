#ifndef PSO_TBOSS5GRYPHONLIGHTNINGWING_H
#define PSO_TBOSS5GRYPHONLIGHTNINGWING_H
#include "pso/TBoss5GryphonLightning.h"
#include "types.h"

class TBoss5GryphonLightningWing : public TBoss5GryphonLightning {
public:
    TBoss5GryphonLightningWing(TObject *parent, const Vec *start, Vec *middle, const Vec *end, s32 duration, s32 delay);
    virtual ~TBoss5GryphonLightningWing();
    void update_wing_segments();
    virtual void run_task();
    virtual void render();
public:
    void get_wing_position(s32 arg1);
public:
    void apply_lightning_effect();
    s32 m_98;
    s32 m_9c;
};

typedef char GryphonLightningWingSize[sizeof(TBoss5GryphonLightningWing) == 0xA0 ? 1 : -1];
typedef char GryphonLightningWingTimers[offsetof(TBoss5GryphonLightningWing, m_98) == 0x98 ? 1 : -1];

#endif
