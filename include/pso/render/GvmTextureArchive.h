#ifndef PSO_RENDER_GVMTEXTUREARCHIVE_H
#define PSO_RENDER_GVMTEXTUREARCHIVE_H

#include "types.h"

struct GinjaTextureList;

extern "C" {
GinjaTextureList *load_gvm_texture_file(const char *filename);
s32 load_gvm_texture_archive(void *archive, GinjaTextureList *list);
s32 find_texture_entry_by_name(const GinjaTextureList *list, const char *name);
}

#endif
