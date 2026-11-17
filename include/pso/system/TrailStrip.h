#ifndef PSO_SYSTEM_TRAILSTRIP_H
#define PSO_SYSTEM_TRAILSTRIP_H

#include "types.h"

// Each vertex is three position floats followed by a packed ARGB word.
// The buffer is borrowed for the duration of the draw; it is not an actor.
extern "C" void draw_trail_strip(void *vertices, s32 count, s32 mode);
void draw_untextured_trail_strip(void *vertices, int count);

#endif
