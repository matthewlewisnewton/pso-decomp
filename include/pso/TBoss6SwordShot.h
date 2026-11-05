#ifndef PSO_TBOSS6SWORDSHOT_H
#define PSO_TBOSS6SWORDSHOT_H

#include "pso/TObject.h"
#include "types.h"

class TBoss6SwordShot : public TObject {
public:
    virtual ~TBoss6SwordShot();
    virtual void run_task();
    static TBoss6SwordShot *create(TObject *owner, const Vec *pos, s32 with_particles, f32 speed);
};

#endif
