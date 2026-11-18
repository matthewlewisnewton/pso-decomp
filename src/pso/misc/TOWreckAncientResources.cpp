#include "pso/misc/TOWreckAncientResources.h"
#include "pso/system/BmlResourceDescriptor.h"

extern "C" {
static __declspec(section ".rodata") const char wreck_model_02[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_zangai02.gj";
static __declspec(section ".rodata") const char wreck_model_01[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_zangai01.gj";
static __declspec(section ".rodata") const char wreck_model_03[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_zangai03.gj";
static __declspec(section ".rodata") const char wreck_model_05[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_zangai05.gj";
static __declspec(section ".rodata") const char wreck_model_04[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_zangai04.gj";
static __declspec(section ".rodata") const char wreck_model_07[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_zangai07.gj";
static __declspec(section ".rodata") const char wreck_model_06[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_zangai06.gj";
static __declspec(section ".rodata") const char wreck_archive[] ATTRIBUTE_ALIGN(4) = "bm_o_wreck_ancient.bml";
static __declspec(section ".rodata") const char debris_model_01[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_hahen01.gj";
static __declspec(section ".rodata") const char debris_model_02[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_hahen02.gj";
static __declspec(section ".rodata") const char debris_model_03[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_hahen03.gj";
static __declspec(section ".rodata") const char debris_model_04[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_hahen04.gj";
static __declspec(section ".rodata") const char debris_model_05[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_hahen05.gj";
static __declspec(section ".rodata") const char debris_model_06[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_hahen06.gj";
static __declspec(section ".rodata") const char debris_model_07[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_hahen07.gj";
static __declspec(section ".rodata") const char debris_model_08[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_hahen08.gj";
static __declspec(section ".rodata") const char debris_model_09[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_hahen09.gj";
static __declspec(section ".rodata") const char debris_archive[] ATTRIBUTE_ALIGN(4) = "bm_fe_obj_o_hahen.bml";
static __declspec(section ".rodata") const char TOWreckAncient__class_name_string[] ATTRIBUTE_ALIGN(4) = "TOWreckAncient";
static __declspec(section ".rodata") const char TOWreckAncient01__class_name_string[] ATTRIBUTE_ALIGN(4) = "TOWreckAncient01";
static __declspec(section ".rodata") const char TOWreckAncient04__class_name_string[] ATTRIBUTE_ALIGN(4) = "TOWreckAncient04";
static __declspec(section ".rodata") const char TOWreckAncient05__class_name_string[] ATTRIBUTE_ALIGN(4) = "TOWreckAncient05";
static __declspec(section ".rodata") const char TOWreckAncient06__class_name_string[] ATTRIBUTE_ALIGN(4) = "TOWreckAncient06";
static __declspec(section ".rodata") const char TOWreckAncient07__class_name_string[] ATTRIBUTE_ALIGN(4) = "TOWreckAncient07";
static __declspec(section ".rodata") const char TOWreckAncientBrakable__class_name_string[] ATTRIBUTE_ALIGN(4) = "TOWreckAncientBrakable";
static __declspec(section ".rodata") const char TOWreckAncientBrakable05__class_name_string[] ATTRIBUTE_ALIGN(4) = "TOWreckAncientBrakable05";

extern const AncientWreckDebrisOffsets TOWreckAncientBrakable__debris_table = {{
    {-7.0f, 12.0f, 9.0f},
    {0.0f, 25.0f, -5.0f},
    {-8.0f, 12.0f, -6.0f},
    {-8.0f, 27.0f, 5.0f},
    {8.0f, 14.0f, -6.0f},
    {8.0f, 15.0f, 9.0f},
    {4.0f, 30.0f, 9.0f},
    {-7.0f, 32.0f, 4.0f},
    {3.0f, 29.0f, -1.0f},
}};

extern const TObjChipParams TOWreckAncientBrakable__debris_param_table = {
    {0.25f, 0.07f, 0.26f},
    {0.0f, 0.0f, 0.0f},
    {5.0f, 7.5f, 5.0f},
    {0x400, 0x100, 0x400},
    {1, 30},
    {0.0f, 0.6f},
    0, 0, 30,
};

static const char *bm_o_wreck_ancient_model_names[8] = {
    wreck_model_02, wreck_model_01, wreck_model_03, wreck_model_05,
    wreck_model_04, wreck_model_07, wreck_model_06, NULL,
};
static const char *bm_o_wreck_ancient_motion_names[1] = {NULL};
BmlResourceDescriptor bm_o_wreck_ancient_resource_descriptor = {
    wreck_archive, bm_o_wreck_ancient_model_names, bm_o_wreck_ancient_motion_names, 7, 0,
};

static const char *bm_fe_obj_o_hahen_model_names[10] = {
    debris_model_01, debris_model_02, debris_model_03, debris_model_04, debris_model_05,
    debris_model_06, debris_model_07, debris_model_08, debris_model_09, NULL,
};
static const char *bm_fe_obj_o_hahen_motion_names[1] = {NULL};
BmlResourceDescriptor TOWreckAncient__resource_descriptor = {
    debris_archive, bm_fe_obj_o_hahen_model_names, bm_fe_obj_o_hahen_motion_names, 9, 0,
};

extern __declspec(section ".data") const CollisionBody TOWreckAncient__collision_body_templates[7] = {
    {{0.0f, 0.0f, 0.0f}, 20.0f, 0.0f, 0, 0x10003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 12.0f, 0.0f, 0, 0x10003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 30.0f, 0.0f, 0, 0x10003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 17.0f, 0.0f, 0, 0x10003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 23.0f, 0.0f, 0, 0x10003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 18.0f, 0.0f, 0, 0x10003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 15.0f, 0.0f, 0, 0x10003, {0.0f, 0.0f, 0.0f}, 0.0f},
};

const char *TOWreckAncient__name = TOWreckAncient__class_name_string;
const char *TOWreckAncient01__name = TOWreckAncient01__class_name_string;
const char *TOWreckAncient04__name = TOWreckAncient04__class_name_string;
const char *TOWreckAncient05__name = TOWreckAncient05__class_name_string;
const char *TOWreckAncient06__name = TOWreckAncient06__class_name_string;
const char *TOWreckAncient07__name = TOWreckAncient07__class_name_string;
const char *TOWreckAncientBrakable__name = TOWreckAncientBrakable__class_name_string;
const char *TOWreckAncientBrakable05__name = TOWreckAncientBrakable05__class_name_string;

BmlResource *wreck_ancient_bml_resource;
BmlResource *wreck_ancient_brakable_bml_resource;
}
