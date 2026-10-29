#ifndef PSO_ITEM_TITEMLOAD_8010FDF0_H
#define PSO_ITEM_TITEMLOAD_8010FDF0_H

#include "types.h"

// A data file TItemLoad::load_buffer read, decompressed and relocated: the
// buffer and its relocated root (apply_rel_relocations).
struct RelocatedFile {
    // Reads path into a size-byte buffer, decompresses and relocates it;
    // root stays NULL when that fails.
    RelocatedFile(const char *path, s32 size);
    ~RelocatedFile();
    void *get_root();

    void *buffer;
    void *root;
};


#endif
