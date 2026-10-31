#ifndef PSO_SYSTEM_GINJATEXTUREINPUT_H
#define PSO_SYSTEM_GINJATEXTUREINPUT_H

#include "types.h"

// Input to the texture loader; distinct from a loaded Ginja surface.
struct GinjaTextureInput {
    void *data;
    s32 format;
    u8 unknown08[8];
    s32 width;
    s32 height;
    u8 unknown18[0xC];

    void configure(void *input, s32 input_format, s32 input_width, s32 input_height);
};

typedef char GinjaTextureInput_size[sizeof(GinjaTextureInput) == 0x24 ? 1 : -1];

#endif
