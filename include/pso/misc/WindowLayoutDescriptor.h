#ifndef PSO_MISC_WINDOWLAYOUTDESCRIPTOR_H
#define PSO_MISC_WINDOWLAYOUTDESCRIPTOR_H

#include "types.h"
#include <stddef.h>

// Observed constructor input. Field names are provisional; the referenced
// entry tables remain opaque. This does not assert an original type name.
struct WindowLayoutDescriptor {
    f32 extent[2];
    f32 order;
    void *layout_entries;
    u32 flags;
};

typedef char WindowLayoutDescriptor_size[sizeof(WindowLayoutDescriptor) == 0x14 ? 1 : -1];
typedef char WindowLayoutDescriptor_entries[offsetof(WindowLayoutDescriptor, layout_entries) == 0xC ? 1 : -1];
typedef char WindowLayoutDescriptor_flags[offsetof(WindowLayoutDescriptor, flags) == 0x10 ? 1 : -1];

#endif
