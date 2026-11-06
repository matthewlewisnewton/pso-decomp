#ifndef PSO_MATH_SCRATCHVECTORSTORAGE_H
#define PSO_MATH_SCRATCHVECTORSTORAGE_H

#include "types.h"
#include <dolphin/mtx/GeoTypes.h>

struct ScratchVectorStorage {
    Vec vector;
    u8 unknown[0x14];
};

typedef char ScratchVectorStorage_size_check[sizeof(ScratchVectorStorage) == 0x20 ? 1 : -1];

extern ScratchVectorStorage scratch_vec;
extern ScratchVectorStorage lbl_8050BF00;

#endif
