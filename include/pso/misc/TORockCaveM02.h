#ifndef PSO_MISC_TOROCKCAVEM02_H
#define PSO_MISC_TOROCKCAVEM02_H

#include "types.h"
#include "pso/misc/TORockCave.h"

struct TORockCaveM02 : public TORockCave {
    virtual ~TORockCaveM02();
};

typedef char TORockCaveM02_size[sizeof(TORockCaveM02) == 0xB4 ? 1 : -1];

extern "C" {
void *TORockCaveM02__create(void *arg0);
void *__dt__13TORockCaveM02Fv(void *arg0, s16 arg1);
}

// --- C functions defined in TORockCaveM02.cpp ---
extern "C" {
void *TORockCaveM02__create(void *arg0);
void *__dt__13TORockCaveM02Fv(void *arg0, s16 arg1);
}
// --- end of C functions

#endif
