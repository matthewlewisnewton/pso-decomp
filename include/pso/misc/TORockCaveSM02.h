#ifndef PSO_MISC_TOROCKCAVESM02_H
#define PSO_MISC_TOROCKCAVESM02_H

#include "types.h"
#include "pso/misc/TORockCaveSimple.h"

struct TORockCaveSM02 : public TORockCaveSimple {
    virtual ~TORockCaveSM02();
};

typedef char TORockCaveSM02_size[sizeof(TORockCaveSM02) == 0xB4 ? 1 : -1];

extern "C" {
void *TORockCaveSM02__create(void *arg0);
void *__dt__14TORockCaveSM02Fv(void *arg0, s16 arg1);
}

// --- C functions defined in TORockCaveSM02.cpp ---
extern "C" {
void *TORockCaveSM02__create(void *arg0);
void *__dt__14TORockCaveSM02Fv(void *arg0, s16 arg1);
}
// --- end of C functions

#endif
