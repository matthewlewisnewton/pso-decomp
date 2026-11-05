#include "types.h"
#include "pso/boss/TBoss6Zanzo.h"

TBoss6Zanzo *TBoss6Zanzo::create(TObject *parent, s32 arg2, s32 arg3) {
    return new TBoss6Zanzo(parent, arg2, arg3);
}
