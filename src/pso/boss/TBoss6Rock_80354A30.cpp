#include "types.h"
#include "pso/boss/TBoss6Rock.h"

extern s32 TBoss6Rock__data_805D6EF8;

u8 TBoss6Rock::is_active() {
    return (u8) (TBoss6Rock__data_805D6EF8 != 0);
}
