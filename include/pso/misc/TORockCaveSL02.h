#ifndef PSO_MISC_TOROCKCAVESL02_H
#define PSO_MISC_TOROCKCAVESL02_H

#include "types.h"
#include "pso/misc/TORockCaveSimple.h"

struct TORockCaveSL02 : public TORockCaveSimple {
    virtual ~TORockCaveSL02();
};

typedef char TORockCaveSL02_size[sizeof(TORockCaveSL02) == 0xB4 ? 1 : -1];

extern "C" {
void *TORockCaveSL02__create(void *arg0);
void *__dt__14TORockCaveSL02Fv(void *arg0, s16 arg1);
}

// --- C functions defined in TORockCaveSL02.cpp ---
extern "C" {
void *TORockCaveSL02__create(void *arg0);
void *__dt__14TORockCaveSL02Fv(void *arg0, s16 arg1);
}
// --- end of C functions

#endif
