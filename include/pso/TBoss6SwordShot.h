#ifndef PSO_TBOSS6SWORDSHOT_H
#define PSO_TBOSS6SWORDSHOT_H

#include "pso/TObject.h"
#include "types.h"

class TBoss6SwordShot : public TObject {
public:
    TBoss6SwordShot(TObject *owner, const Vec *pos, s32 with_particles, f32 speed);
    virtual ~TBoss6SwordShot();
    virtual void run_task();
    // The shot record continues through 0x38. operator new allocates sizeof(this).
    u8 m_shot_tail[0x38 - 0x1C];
    static TBoss6SwordShot *create(TObject *owner, const Vec *pos, s32 with_particles, f32 speed);
};

#endif
