#ifndef PSO_SYSTEM_RELMODULEBUFFER_H
#define PSO_SYSTEM_RELMODULEBUFFER_H

#include "types.h"

// Backing storage and linked image managed by the REL loader.
struct RelModuleBuffer {
    void *bss;
    void *image;
};

typedef char RelModuleBuffer_size[sizeof(RelModuleBuffer) == 0x8 ? 1 : -1];

extern "C" {
void *fn_803204B0(RelModuleBuffer *module);
RelModuleBuffer *fn_80320358(RelModuleBuffer *module, s16 should_delete);
RelModuleBuffer *load_rel_module(RelModuleBuffer *module, s32 resource);
}

#endif
