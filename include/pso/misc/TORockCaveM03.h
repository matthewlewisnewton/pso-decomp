#ifndef PSO_MISC_TOROCKCAVEM03_H
#define PSO_MISC_TOROCKCAVEM03_H

#include "types.h"
#include "pso/misc/TORockCave.h"

struct TORockCaveM03 : public TORockCave {
    virtual ~TORockCaveM03();
};

typedef char TORockCaveM03_size[sizeof(TORockCaveM03) == 0xB4 ? 1 : -1];

extern "C" {
void *TORockCaveM03__create(void *arg0);
void *__dt__13TORockCaveM03Fv(void *arg0, s16 arg1);
}

// --- C functions defined in TORockCaveM03.cpp ---
extern "C" {
void *TORockCaveM03__create(void *arg0);
void *__dt__13TORockCaveM03Fv(void *arg0, s16 arg1);
}
// --- end of C functions

#endif
