#ifndef PSO_MISC_TOVS2WRECK03_H
#define PSO_MISC_TOVS2WRECK03_H

#include "types.h"
#include "pso/misc/TOVS2.h"

struct TOVS2Wreck03 : public TOVS2 {
    virtual ~TOVS2Wreck03();
};

typedef char TOVS2Wreck03_size[sizeof(TOVS2Wreck03) == 0xD0 ? 1 : -1];

extern "C" {
void *TOVS2Wreck03__create(void *arg0);
void *TOVS2Wreck03__ct(void *arg0, void *arg1);
}

// --- C functions defined in TOVS2Wreck03.cpp ---
extern "C" {
void *TOVS2Wreck03__create(void *arg0);
void *TOVS2Wreck03__ct(void *arg0, void *arg1);
}
// --- end of C functions

#endif
