#ifndef PSO_MISC_PAGEINDICATOR_8026CB44_H
#define PSO_MISC_PAGEINDICATOR_8026CB44_H

#include "types.h"
#include <stddef.h>

struct TWindowDrawContext;

// Address-based recovered layout; no original class name or TObject base inferred.
struct PageIndicator_8026CB44 {
    s8 page;
    s8 count;
    u8 padding[2];
    s32 port;
    f32 phase;

    // Observed dynamic callers already sign-extend the two byte values.
    PageIndicator_8026CB44(s8 page, s8 count, s32 client);
};

typedef char PageIndicator_8026CB44_size[sizeof(PageIndicator_8026CB44) == 0xC ? 1 : -1];
typedef char PageIndicator_8026CB44_port[offsetof(PageIndicator_8026CB44, port) == 4 ? 1 : -1];
typedef char PageIndicator_8026CB44_phase[offsetof(PageIndicator_8026CB44, phase) == 8 ? 1 : -1];

extern "C" {
void draw_list_page_indicator(PageIndicator_8026CB44 *, TWindowDrawContext *);
s32 handle_list_page_flip_input(PageIndicator_8026CB44 *);
void decay_page_arrow_offset(PageIndicator_8026CB44 *);
}

// Ordinary global-storage release; the known page object has a trivial destructor.
void *delete_if_allocated(void *storage, s16 release);

#endif
