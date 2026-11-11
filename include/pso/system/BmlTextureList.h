#ifndef PSO_SYSTEM_BML_TEXTURE_LIST_H
#define PSO_SYSTEM_BML_TEXTURE_LIST_H

#include "types.h"

struct BmlResource;
struct GinjaTextureList;

// Texture-list pointer owned by the index-th model entry of a loaded BML archive.
extern "C" GinjaTextureList *TObjFish__sub_8001EDB0(BmlResource *resource, s32 index);

#endif
