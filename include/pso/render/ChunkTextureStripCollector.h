#ifndef PSO_RENDER_CHUNKTEXTURESTRIPCOLLECTOR_H
#define PSO_RENDER_CHUNKTEXTURESTRIPCOLLECTOR_H

#include "pso/system/NinjaTypes.h"
#include "pso/system/StripBufferPair.h"

// Scratch cursors for the two-pass collector; the buffer-pair constructor
// resets the texture filter before each traversal.
extern "C" {
extern StripReference *plist_strip_write_ptr;
extern s16 *plist_strip_uv_write_ptr;
extern s32 plist_texture_matches_filter;
void collect_model_strips_by_texture(StripBufferPair *buffers, NJS_OBJECT *node, s32 texture);
void count_model_strips_by_texture(StripBufferPair *buffers, NJS_OBJECT *node, s32 texture);
}

void collect_plist_strips_by_texture(StripBufferPair *buffers, s16 *polygon_list, s32 texture);
void count_plist_strips_by_texture(StripBufferPair *buffers, s16 *polygon_list, s32 texture);

#endif
