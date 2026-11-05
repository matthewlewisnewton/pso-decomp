#ifndef PSO_MISC_TOROCKCAVESS02_H
#define PSO_MISC_TOROCKCAVESS02_H

#include "types.h"
#include "pso/misc/TORockCaveSimple.h"

struct TORockCaveSS02 : public TORockCaveSimple {
    virtual ~TORockCaveSS02();
};

typedef char TORockCaveSS02_size[sizeof(TORockCaveSS02) == 0xB4 ? 1 : -1];
#endif
