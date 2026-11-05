#ifndef PSO_SYSTEM_CURRENTTEXTURELIST_H
#define PSO_SYSTEM_CURRENTTEXTURELIST_H
#include "types.h"
struct GinjaTextureList;
extern "C" {
s32 set_current_texture_list(GinjaTextureList *list);
}
#endif
