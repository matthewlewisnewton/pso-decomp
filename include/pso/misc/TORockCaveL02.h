#ifndef PSO_MISC_TOROCKCAVEL02_H
#define PSO_MISC_TOROCKCAVEL02_H

#include "types.h"
#include "pso/misc/TORockCave.h"

struct TORockCaveL02 : public TORockCave {
    virtual ~TORockCaveL02();
};

typedef char TORockCaveL02_size[sizeof(TORockCaveL02) == 0xB4 ? 1 : -1];

extern "C" {
void *TORockCaveL02__create(void *arg0);
void *__dt__13TORockCaveL02Fv(void *arg0, s16 arg1);
}

// --- C functions defined in TORockCaveL02.cpp ---
extern "C" {
void *TORockCaveL02__create(void *arg0);
void *__dt__13TORockCaveL02Fv(void *arg0, s16 arg1);
}
// --- end of C functions

#endif
