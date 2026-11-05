#ifndef PSO_MISC_TOROCKCAVES02_H
#define PSO_MISC_TOROCKCAVES02_H

#include "types.h"
#include "pso/misc/TORockCave.h"

struct TORockCaveS02 : public TORockCave {
    virtual ~TORockCaveS02();
};

typedef char TORockCaveS02_size[sizeof(TORockCaveS02) == 0xB4 ? 1 : -1];
#endif
