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
// Original filename-size helper at 0x800F9D80; it forwards the path to
// TLobby::get_resource_file_size. Kept under its link name for exact matching.
s32 update_lobby_scene__6TSceneFv(const char *filename);
RelModuleBuffer *load_rel_module(RelModuleBuffer *module, const char *filename);
}

#endif
