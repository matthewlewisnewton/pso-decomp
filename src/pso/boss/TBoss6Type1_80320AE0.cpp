#include "pso/boss/TBoss6Type1.h"
#include "pso/boss/TBoss6Zanzo.h"

TBoss6Zanzo *TBoss6Type1::create_zanzo(TObject *parent, s32 points, s32 frames) {
    return new TBoss6Zanzo(parent, points, frames);
}
