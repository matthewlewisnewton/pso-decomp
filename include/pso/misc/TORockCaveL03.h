#ifndef PSO_MISC_TOROCKCAVEL03_H
#define PSO_MISC_TOROCKCAVEL03_H

#include "types.h"
#include "pso/misc/TORockCave.h"

struct TORockCaveL03 : public TORockCave {
    virtual ~TORockCaveL03();
};

typedef char TORockCaveL03_size[sizeof(TORockCaveL03) == 0xB4 ? 1 : -1];

extern "C" {
void *TORockCaveL03__create(void *arg0);
void *__dt__13TORockCaveL03Fv(void *arg0, s16 arg1);
}

// --- C functions defined in TORockCaveL03.cpp ---
extern "C" {
void *TORockCaveL03__create(void *arg0);
void *__dt__13TORockCaveL03Fv(void *arg0, s16 arg1);
}
// --- end of C functions

#endif
