#ifndef PSO_MISC_SCROLL_8026D790_H
#define PSO_MISC_SCROLL_8026D790_H

#include "types.h"
#include <stddef.h>

// Existing address-based name; no original semantic class name is asserted.
// The input carries an observed two-float prefix; its void * type does not
// assert input mutation or recovery of a particular vector type.
struct Scroll_8026D790 {
    f32 m_0;
    f32 height;
    s32 frame;

    Scroll_8026D790(void *pair);
    void copy_position(void *pair);
};

typedef char Scroll_8026D790_size[sizeof(Scroll_8026D790) == 0xC ? 1 : -1];
typedef char Scroll_8026D790_height[offsetof(Scroll_8026D790, height) == 4 ? 1 : -1];
typedef char Scroll_8026D790_frame[offsetof(Scroll_8026D790, frame) == 8 ? 1 : -1];

// Keep the counter/release protocol type-erased: one positive producer remains
// unrecovered. No destructor or complete producer identity is inferred for it.
extern "C" {
void fn_8026D9C0(void *storage);
void *fn_8026D9D0(void *storage, s16 release);
}

#endif
