#ifndef PSO_MISC_TOROCKCAVEBL01_H
#define PSO_MISC_TOROCKCAVEBL01_H

#include "types.h"
#include "pso/misc/TORockCaveBrakable.h"

struct TORockCaveBL01 : public TORockCaveBrakable {
    virtual ~TORockCaveBL01();
};

typedef char TORockCaveBL01_size[sizeof(TORockCaveBL01) == 0xBC ? 1 : -1];

extern "C" {
void *TORockCaveBL01__create(void *arg0);
void *__dt__14TORockCaveBL01Fv(void *arg0, s16 arg1);
}

// --- C functions defined in TORockCaveBL01.cpp ---
extern "C" {
void *TORockCaveBL01__create(void *arg0);
void *__dt__14TORockCaveBL01Fv(void *arg0, s16 arg1);
}
// --- end of C functions

#endif
