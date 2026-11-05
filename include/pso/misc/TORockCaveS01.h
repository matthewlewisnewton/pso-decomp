#ifndef PSO_MISC_TOROCKCAVES01_H
#define PSO_MISC_TOROCKCAVES01_H

#include "types.h"
#include "pso/misc/TORockCave.h"

struct TORockCaveS01 : public TORockCave {
    virtual ~TORockCaveS01();
};

typedef char TORockCaveS01_size[sizeof(TORockCaveS01) == 0xB4 ? 1 : -1];
#endif
