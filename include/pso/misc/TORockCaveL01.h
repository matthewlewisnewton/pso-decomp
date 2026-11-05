#ifndef PSO_MISC_TOROCKCAVEL01_H
#define PSO_MISC_TOROCKCAVEL01_H

#include "types.h"
#include "pso/misc/TORockCave.h"

struct TORockCaveL01 : public TORockCave {
    virtual ~TORockCaveL01();
};

typedef char TORockCaveL01_size[sizeof(TORockCaveL01) == 0xB4 ? 1 : -1];

extern "C" {
void *TORockCaveL01__create(void *arg0);
void *__dt__13TORockCaveL01Fv(void *arg0, s16 arg1);
}

// --- C functions defined in TORockCaveL01.cpp ---
extern "C" {
void *TORockCaveL01__create(void *arg0);
void *__dt__13TORockCaveL01Fv(void *arg0, s16 arg1);
}
// --- end of C functions

#endif
