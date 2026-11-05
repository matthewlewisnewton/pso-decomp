#ifndef PSO_MISC_TMOVIE_80143988_H
#define PSO_MISC_TMOVIE_80143988_H

#include "types.h"

// Plane table filled by the movie decoder callback in flip_frame_buffer.
// Strides are in bytes.
struct MovieFramePlanes {
    u32 *luma;
    u32 *cb;
    u32 *cr;
    u32 luma_stride;
    u32 chroma_stride;
    u32 chroma_stride2;
};

extern "C" {
void pack_movie_frame(MovieFramePlanes *frame);
}

#endif
