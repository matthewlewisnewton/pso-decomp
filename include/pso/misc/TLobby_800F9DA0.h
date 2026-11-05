#ifndef PSO_MISC_TLOBBY_800F9DA0_H
#define PSO_MISC_TLOBBY_800F9DA0_H

#include "types.h"

// --- C functions defined in TLobby_800F9DA0.cpp ---
extern "C" {
// Reads the whole disc file `filename` into `buffer`; returns its size, or -1.
s32 read_disc_file(const char *filename, void *buffer);
}
// --- end of C functions

#endif
