#ifndef PSO_OBJECT_TOBJ_WARP_RESOURCES_H
#define PSO_OBJECT_TOBJ_WARP_RESOURCES_H

#include "pso/system/BmlResourceDescriptor.h"
#include <dolphin/mtx/GeoTypes.h>

struct BmlResource;
struct GinjaTextureList;

union WarpScreenCoordinate {
    f32 value;
    u32 bits;
};

struct WarpStringScreenPosition {
    WarpScreenCoordinate x;
    WarpScreenCoordinate y;
};

union WarpDebugOffset {
    Vec position;
    u32 words[3];
};

extern "C" {
extern BmlResourceDescriptor forest_warp_resource_descriptor;
extern BmlResource *forest_warp_bml_resource;
extern GinjaTextureList *forest_warp_texture_list;
extern const Vec map_warp_destination_offsets[4];
extern const WarpDebugOffset lbl_804462FC;
extern const WarpStringScreenPosition warp_string_screen_position_table[10];
extern s32 quest_warp_enabled;
extern s32 lobby_quest_progress_flag;
}

#endif
