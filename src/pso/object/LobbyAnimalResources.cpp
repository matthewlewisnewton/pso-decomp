#include "pso/system/BmlResourceDescriptor.h"

extern "C" {
static __declspec(section ".rodata") const char lbl_80471540[] ATTRIBUTE_ALIGN(4) = "d_dolf.nj";
static __declspec(section ".rodata") const char lbl_8047154C[] ATTRIBUTE_ALIGN(4) = "d_20mcircle.njm";
static __declspec(section ".rodata") const char lbl_8047155C[] ATTRIBUTE_ALIGN(4) = "d_30mcircle.njm";
static __declspec(section ".rodata") const char lbl_8047156C[] ATTRIBUTE_ALIGN(4) = "d_30mx_01.njm";
static __declspec(section ".rodata") const char lbl_8047157C[] ATTRIBUTE_ALIGN(4) = "d_30mx_02.njm";
static __declspec(section ".rodata") const char lbl_8047158C[] ATTRIBUTE_ALIGN(4) = "d_30mx_03.njm";
static __declspec(section ".rodata") const char lbl_8047159C[] ATTRIBUTE_ALIGN(4) = "d_dolf.njm";
static __declspec(section ".rodata") const char lbl_804715A8[] ATTRIBUTE_ALIGN(4) = "bm_obj_seabed_dolphin.bml";
static __declspec(section ".rodata") const char lbl_804715C4[] ATTRIBUTE_ALIGN(4) = "fe_obj_h_ebi.nj";
static __declspec(section ".rodata") const char lbl_804715D4[] ATTRIBUTE_ALIGN(4) = "fe_obj_h_ebi.njm";
static __declspec(section ".rodata") const char lbl_804715E8[] ATTRIBUTE_ALIGN(4) = "path01_h_ebi.njm";
static __declspec(section ".rodata") const char lbl_804715FC[] ATTRIBUTE_ALIGN(4) = "path02_h_ebi.njm";
static __declspec(section ".rodata") const char lbl_80471610[] ATTRIBUTE_ALIGN(4) = "path03_h_ebi.njm";
static __declspec(section ".rodata") const char lbl_80471624[] ATTRIBUTE_ALIGN(4) = "bm_obj_jungle_ebi.bml";
static __declspec(section ".rodata") const char lbl_8047163C[] ATTRIBUTE_ALIGN(4) = "fe_obj_h_tori.nj";
static __declspec(section ".rodata") const char lbl_80471650[] ATTRIBUTE_ALIGN(4) = "fe_obj_h_tori.njm";
static __declspec(section ".rodata") const char lbl_80471664[] ATTRIBUTE_ALIGN(4) = "path01_h_tori.njm";
static __declspec(section ".rodata") const char lbl_80471678[] ATTRIBUTE_ALIGN(4) = "path02_h_tori.njm";
static __declspec(section ".rodata") const char lbl_8047168C[] ATTRIBUTE_ALIGN(4) = "path03_h_tori.njm";
static __declspec(section ".rodata") const char lbl_804716A0[] ATTRIBUTE_ALIGN(4) = "bm_obj_jungle_bird.bml";
static __declspec(section ".rodata") const char lbl_804716B8[] ATTRIBUTE_ALIGN(4) = "fe_obj_h_kamome.nj";
static __declspec(section ".rodata") const char lbl_804716CC[] ATTRIBUTE_ALIGN(4) = "fe_obj_h_kamome.njm";
static __declspec(section ".rodata") const char lbl_804716E0[] ATTRIBUTE_ALIGN(4) = "path01_h2_tori.njm";
static __declspec(section ".rodata") const char lbl_804716F4[] ATTRIBUTE_ALIGN(4) = "path02_h2_tori.njm";
static __declspec(section ".rodata") const char lbl_80471708[] ATTRIBUTE_ALIGN(4) = "path03_h2_tori.njm";
static __declspec(section ".rodata") const char lbl_8047171C[] ATTRIBUTE_ALIGN(4) = "bm_obj_jungle_kamome.bml";

__declspec(section ".data") const char *bm_obj_seabed_dolphin_model_names[2] = { lbl_80471540, NULL };
const char *bm_obj_seabed_dolphin_motion_names[7] = { lbl_8047154C, lbl_8047155C, lbl_8047156C, lbl_8047157C, lbl_8047158C, lbl_8047159C, NULL };
BmlResourceDescriptor bm_obj_seabed_dolphin_resource_descriptor = { lbl_804715A8, bm_obj_seabed_dolphin_model_names, bm_obj_seabed_dolphin_motion_names, 1, 6 };
__declspec(section ".data") const char *bm_obj_jungle_ebi_model_names[2] = { lbl_804715C4, NULL };
const char *bm_obj_jungle_ebi_motion_names[5] = { lbl_804715D4, lbl_804715E8, lbl_804715FC, lbl_80471610, NULL };
BmlResourceDescriptor bm_obj_jungle_ebi_resource_descriptor = { lbl_80471624, bm_obj_jungle_ebi_model_names, bm_obj_jungle_ebi_motion_names, 1, 4 };
__declspec(section ".data") const char *bm_obj_jungle_bird_model_names[2] = { lbl_8047163C, NULL };
const char *bm_obj_jungle_bird_motion_names[5] = { lbl_80471650, lbl_80471664, lbl_80471678, lbl_8047168C, NULL };
BmlResourceDescriptor bm_obj_jungle_bird_resource_descriptor = { lbl_804716A0, bm_obj_jungle_bird_model_names, bm_obj_jungle_bird_motion_names, 1, 4 };
__declspec(section ".data") const char *bm_obj_jungle_kamome_model_names[2] = { lbl_804716B8, NULL };
const char *bm_obj_jungle_kamome_motion_names[5] = { lbl_804716CC, lbl_804716E0, lbl_804716F4, lbl_80471708, NULL };
BmlResourceDescriptor bm_obj_jungle_kamome_resource_descriptor = { lbl_8047171C, bm_obj_jungle_kamome_model_names, bm_obj_jungle_kamome_motion_names, 1, 4 };

u32 seabed_dolphin_bml_archive;
s32 seabed_dolphin_texture_handle;
u32 jungle_ebi_model_resource;
u32 jungle_ebi_texture_gvm_handle;
u32 jungle_bird_bml_resource;
u32 lobby_pigeon_texture_gvm;
u32 lobby_kamome_model_resource;
u32 lobby_kamome_texture_gvm_handle;
u32 lobby_pigeon_bml_archive;
u32 lobby_pigeon_lobby_type;
}
