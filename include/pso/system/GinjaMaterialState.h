#ifndef PSO_GINJA_MATERIAL_STATE_H
#define PSO_GINJA_MATERIAL_STATE_H
#ifndef TYPES_H
#include "types.h"
#endif
typedef struct GinjaMaterialCache {
  u8 prefix[8];
  u32 parameters[11];
  u32 dirty[11];
  u8 reserved60[12];
  u32 inherited_flags;
  u8 reserved70[12];
  u32 blend_valid;
  u32 blend;
  u32 textured;
  u32 texture;
} GinjaMaterialCache;
typedef struct GinjaParameter {
  u8 kind;
  u8 reserved[3];
  u32 value;
} GinjaParameter;
typedef struct GinjaSurfaceState {
  u32 id;
  u32 format;
  u8 reserved8[0x14];
  u32 flags;
  void *pixels;
} GinjaSurfaceState;
typedef struct GinjaTextureState {
  u8 reserved0[12];
  GinjaSurfaceState *surface;
} GinjaTextureState;
// Ninja's texture name: a file name, or a texture input for memory textures.
typedef struct GinjaTextureEntry {
  const void *name;
  u32 value04;
  // The global texture index until the list is loaded, then the texture.
  union {
    GinjaTextureState *texture;
    u32 global_index;
  };
} GinjaTextureEntry;
typedef struct GinjaTextureList {
  GinjaTextureEntry *entries;
  u32 count;
  // The index of the entry with this name, or -1.
  s32 find_entry_by_name(const char *name);
} GinjaTextureList;
typedef struct GinjaSceneState {
  u8 reserved0[0x20];
  GinjaTextureList *textures;
} GinjaSceneState;
typedef char
    GinjaMaterialCacheSize[(sizeof(GinjaMaterialCache) == 0x8c) ? 1 : -1];
#endif
