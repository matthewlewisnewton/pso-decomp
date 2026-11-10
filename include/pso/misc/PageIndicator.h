#ifndef PSO_MISC_PAGEINDICATOR_H
#define PSO_MISC_PAGEINDICATOR_H

#include "types.h"
#include <stddef.h>

// Allocated by the status, shortcut and card-list windows. The page-flip
// controller at 0x8026C9DC and renderer at 0x8026C800 share this layout.
struct PageIndicator {
    s8 page;
    s8 count;
    u8 pad_02[2];
    s32 input_port;
    f32 arrow_offset;

    s8 get_type();
};

typedef char PageIndicator_size[sizeof(PageIndicator) == 0xC ? 1 : -1];
typedef char PageIndicator_input_port[offsetof(PageIndicator, input_port) == 4 ? 1 : -1];
typedef char PageIndicator_arrow_offset[offsetof(PageIndicator, arrow_offset) == 8 ? 1 : -1];

#endif
