#ifndef PSO_MISC_PARTICLEDEFINITION_H
#define PSO_MISC_PARTICLEDEFINITION_H

#include "types.h"

struct GinjaTextureList;

// One quad-sprite particle kind; create_quad_sprites builds sprite_type's
// TQuadSprite* class for each. Field names inferred from the users.
struct ParticleDefinition {
    u32 flags;
    GinjaTextureList *texlist;
    s32 texture;
    s32 uv_count;
    f32 (*uvs)[4];
    f32 width;
    f32 height;
    u32 color;
    s32 texlist_index;
    s32 sprite_type;
};
typedef char ParticleDefinition_size[sizeof(ParticleDefinition) == 0x28 ? 1 : -1];

#endif
