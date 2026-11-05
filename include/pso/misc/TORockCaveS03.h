#ifndef PSO_MISC_TOROCKCAVES03_H
#define PSO_MISC_TOROCKCAVES03_H

#include "types.h"
#include "pso/misc/TORockCave.h"

struct TORockCaveS03 : public TORockCave {
    virtual ~TORockCaveS03();
};

typedef char TORockCaveS03_size[sizeof(TORockCaveS03) == 0xB4 ? 1 : -1];
#endif
