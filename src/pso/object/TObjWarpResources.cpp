#include "pso/object/TObjWarpResources.h"

extern "C" {
static __declspec(section ".rodata") const char forest_warp_model[] ATTRIBUTE_ALIGN(4) = "fs_obj_warp.gj";
static __declspec(section ".rodata") const char forest_warp_beam_model[] ATTRIBUTE_ALIGN(4) = "fs_obj_warp_beam.gj";
static __declspec(section ".rodata") const char forest_warp_base_model[] ATTRIBUTE_ALIGN(4) = "fs_obj_warp_dai.gj";
static __declspec(section ".rodata") const char forest_warp_base_beam_model[] ATTRIBUTE_ALIGN(4) = "fs_obj_warp_dai_beam.gj";
static __declspec(section ".rodata") const char forest_warp_alternate_model[] ATTRIBUTE_ALIGN(4) = "fs_obj_warp_n.gj";
static __declspec(section ".rodata") const char forest_warp_alternate_beam_model[] ATTRIBUTE_ALIGN(4) = "fs_obj_warp_n_beam.gj";
static __declspec(section ".rodata") const char forest_warp_beam_motion[] ATTRIBUTE_ALIGN(4) = "fs_obj_warp_beam.njm";
static __declspec(section ".rodata") const char forest_warp_base_beam_motion[] ATTRIBUTE_ALIGN(4) = "fs_obj_warp_dai_beam.njm";
static __declspec(section ".rodata") const char forest_warp_alternate_beam_motion[] ATTRIBUTE_ALIGN(4) = "fs_obj_warp_n_beam.njm";
static __declspec(section ".rodata") const char forest_warp_archive[] ATTRIBUTE_ALIGN(4) = "fs_obj_warp.bml";

static __declspec(section ".rodata") const char TObjWarpBase__class_name_string[] ATTRIBUTE_ALIGN(4) = "TObjWarpBase";
static __declspec(section ".rodata") const char TObjMapWarp__class_name_string[] ATTRIBUTE_ALIGN(4) = "TObjMapWarp";
extern const WarpDebugOffset lbl_804462FC = {{0.0f, 0.0f, -3.0f}};
static __declspec(section ".rodata") const char TObjMapWarpForest__class_name_string[] ATTRIBUTE_ALIGN(4) = "TObjMapWarpForest";
static __declspec(section ".rodata") const char TObjAreaWarp__class_name_string[] ATTRIBUTE_ALIGN(4) = "TObjAreaWarp";
static __declspec(section ".rodata") const char TObjAreaWarpForest__class_name_string[] ATTRIBUTE_ALIGN(4) = "TObjAreaWarpForest";
static __declspec(section ".rodata") const char TObjAreaWarpQuest__class_name_string[] ATTRIBUTE_ALIGN(4) = "TObjAreaWarpQuest";
static __declspec(section ".rodata") const char TObjAreaWarpEnding__class_name_string[] ATTRIBUTE_ALIGN(4) = "TObjAreaWarpEnding";
static __declspec(section ".rodata") const char TObjMapForceWarp__class_name_string[] ATTRIBUTE_ALIGN(4) = "TObjMapForceWarp";
static __declspec(section ".rodata") const char TObjWarpString__class_name_string[] ATTRIBUTE_ALIGN(4) = "TObjWarpString";
static __declspec(section ".rodata") const char TObjAreaWarpEndingJung__class_name_string[] ATTRIBUTE_ALIGN(4) = "TObjAreaWarpEndingJung";
extern __declspec(section ".rodata") const char lbl_804463A4[] ATTRIBUTE_ALIGN(4) = "<- COLOR : RED";
extern __declspec(section ".rodata") const char lbl_804463B4[] ATTRIBUTE_ALIGN(4) = "<- COLOR : BLUE";

static const char *fs_obj_warp_model_names[] = {
    forest_warp_model, forest_warp_beam_model, forest_warp_base_model, forest_warp_base_beam_model,
    forest_warp_alternate_model, forest_warp_alternate_beam_model, NULL,
};
static const char *fs_obj_warp_motion_names[] = {
    forest_warp_beam_motion, forest_warp_base_beam_motion, forest_warp_alternate_beam_motion, NULL,
};
BmlResourceDescriptor forest_warp_resource_descriptor = {
    forest_warp_archive, fs_obj_warp_model_names, fs_obj_warp_motion_names, 6, 3,
};

// The warp transforms these offsets into world-space destinations for four players.
extern __declspec(section ".data") const Vec map_warp_destination_offsets[4] = {
    {10.0f, 0.0f, 10.0f},
    {10.0f, 0.0f, -10.0f},
    {-10.0f, 0.0f, 10.0f},
    {-10.0f, 0.0f, -10.0f},
};

// One default position, then the camera's display positions for each split-screen mode.
extern __declspec(section ".data") const WarpStringScreenPosition warp_string_screen_position_table[10] = {
    {{320.0f}, {200.0f}},
    {{320.0f}, {120.0f}},
    {{320.0f}, {260.0f}}, {{160.0f}, {120.0f}},
    {{480.0f}, {120.0f}}, {{320.0f}, {260.0f}}, {{160.0f}, {120.0f}},
    {{480.0f}, {120.0f}}, {{160.0f}, {260.0f}}, {{480.0f}, {260.0f}},
};

s32 quest_warp_enabled = 1;
const char *TObjWarpBase__name = TObjWarpBase__class_name_string;
const char *TObjMapWarp__name = TObjMapWarp__class_name_string;
const char *TObjMapWarpForest__name = TObjMapWarpForest__class_name_string;
const char *TObjAreaWarp__name = TObjAreaWarp__class_name_string;
const char *TObjAreaWarpForest__name = TObjAreaWarpForest__class_name_string;
const char *TObjAreaWarpQuest__name = TObjAreaWarpQuest__class_name_string;
const char *TObjAreaWarpEnding__name = TObjAreaWarpEnding__class_name_string;
const char *TObjMapForceWarp__name = TObjMapForceWarp__class_name_string;
const char *TObjWarpString__name = TObjWarpString__class_name_string;
const char *TObjAreaWarpEndingJung__name = TObjAreaWarpEndingJung__class_name_string;

BmlResource *forest_warp_bml_resource;
GinjaTextureList *forest_warp_texture_list;
s32 lobby_quest_progress_flag;
}
