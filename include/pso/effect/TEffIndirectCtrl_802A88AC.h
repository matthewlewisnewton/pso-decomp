#ifndef PSO_MISC_TEFFINDIRECTCTRL_802A88AC_H
#define PSO_MISC_TEFFINDIRECTCTRL_802A88AC_H

#include "types.h"

extern "C" {
u32 calc_i8_tiled_texel_offset(u8 x, u8 y, u32 w);
void deform_indirect_texture_scroll(u8 *p, u32 px, u32 py, u32 amp, u32 phase);
u8 *get_indirect_source_pixels(u8 id);
}
void deform_indirect_texture_wave(u8 *buf, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5);
s32 get_indirect_source_id(u8 id);
void update_indirect_texture_wave(u8 *buf, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5);

#endif
