#include "pso/misc/TOVS2WallResources.h"
#include "pso/object/TObjChip.h"
#include "pso/object/TObjMotion.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/system/BmlResourceClass.h"

extern "C" {
static __declspec(section ".rodata") const char lbl_80442F40[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_vs2gareki01.gj";
static __declspec(section ".rodata") const char lbl_80442F58[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_vs2gareki02.gj";
static __declspec(section ".rodata") const char lbl_80442F70[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_vs2gareki03.gj";
static __declspec(section ".rodata") const char lbl_80442F88[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_vs2gareki04.gj";
static __declspec(section ".rodata") const char lbl_80442FA0[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_vs2gareki05.gj";
static __declspec(section ".rodata") const char lbl_80442FB8[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_vs2gareki06.gj";
static __declspec(section ".rodata") const char lbl_80442FD0[] ATTRIBUTE_ALIGN(4) = "kakusi_hahen27.gj";
static __declspec(section ".rodata") const char lbl_80442FE4[] ATTRIBUTE_ALIGN(4) = "kakusi_hahen01.gj";
static __declspec(section ".rodata") const char lbl_80442FF8[] ATTRIBUTE_ALIGN(4) = "kakusi_hahen02.gj";
static __declspec(section ".rodata") const char lbl_8044300C[] ATTRIBUTE_ALIGN(4) = "kakusi_hahen03.gj";
static __declspec(section ".rodata") const char lbl_80443020[] ATTRIBUTE_ALIGN(4) = "kakusi_hahen04.gj";
static __declspec(section ".rodata") const char lbl_80443034[] ATTRIBUTE_ALIGN(4) = "kakusi_hahen05.gj";
static __declspec(section ".rodata") const char lbl_80443048[] ATTRIBUTE_ALIGN(4) = "kakusi_hahen06.gj";
static __declspec(section ".rodata") const char lbl_8044305C[] ATTRIBUTE_ALIGN(4) = "kakusi_hahen07.gj";
static __declspec(section ".rodata") const char lbl_80443070[] ATTRIBUTE_ALIGN(4) = "kakusi_hahen08.gj";
static __declspec(section ".rodata") const char lbl_80443084[] ATTRIBUTE_ALIGN(4) = "kakusi_hahen09.gj";
static __declspec(section ".rodata") const char lbl_80443098[] ATTRIBUTE_ALIGN(4) = "bm_o_vs2.bml";
static __declspec(section ".rodata") const char lbl_804430A8[] ATTRIBUTE_ALIGN(4) = "TOVS2";
static __declspec(section ".rodata") const char lbl_804430B0[] ATTRIBUTE_ALIGN(4) = "TOVS2Wreck01";
static __declspec(section ".rodata") const char lbl_804430C0[] ATTRIBUTE_ALIGN(4) = "TOVS2Wreck02";
static __declspec(section ".rodata") const char lbl_804430D0[] ATTRIBUTE_ALIGN(4) = "TOVS2Wreck03";
static __declspec(section ".rodata") const char lbl_804430E0[] ATTRIBUTE_ALIGN(4) = "TOVS2Wreck04";
static __declspec(section ".rodata") const char lbl_804430F0[] ATTRIBUTE_ALIGN(4) = "TOVS2Wreck05";
static __declspec(section ".rodata") const char lbl_80443100[] ATTRIBUTE_ALIGN(4) = "TOVS2Wreck06";
static __declspec(section ".rodata") const char lbl_80443110[] ATTRIBUTE_ALIGN(4) = "TOVS2Wall01";

extern const TObjChipParams vs2_wall_debris_desc = {
    {0.25f, 0.07f, 0.26f}, {0.0f, 0.0f, 0.0f}, {5.0f, 7.5f, 5.0f},
    {1024, 256, 1024}, {1, 20}, {0.0f, 0.6f}, 0, 0, 20,
};

const char *bm_o_vs2_model_names[17] = {
    lbl_80442F40, lbl_80442F58, lbl_80442F70, lbl_80442F88, lbl_80442FA0,
    lbl_80442FB8, lbl_80442FD0, lbl_80442FE4, lbl_80442FF8, lbl_8044300C,
    lbl_80443020, lbl_80443034, lbl_80443048, lbl_8044305C, lbl_80443070,
    lbl_80443084, NULL,
};
const char *bm_o_vs2_motion_names[1] = {NULL};
BmlResourceDescriptor bm_o_vs2_resource_descriptor = {lbl_80443098, bm_o_vs2_model_names, bm_o_vs2_motion_names, 16, 0};

CollisionBody ovs2wall01_collision_parts[7] = {
    {{0.0f, 0.0f, 0.0f}, 20.0f, 30.0f, 0, 0x20010003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 15.0f, 15.0f, 0, 0x20010003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 12.0f, 12.0f, 0, 0x20010003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 12.0f, 12.0f, 0, 0x20010003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 12.0f, 27.0f, 1, 0x20010003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 10.0f, 10.0f, 0, 0x20010003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 20.0f, 0.0f}, 10.0f, 20.0f, 1, 0x38003, {0.0f, 0.0f, 0.0f}, 0.0f}
};

const char *lbl_805D31C4 = lbl_804430A8;
const char *lbl_805D31C8 = lbl_804430B0;
const char *lbl_805D31CC = lbl_804430C0;
const char *lbl_805D31D0 = lbl_804430D0;
const char *lbl_805D31D4 = lbl_804430E0;
const char *lbl_805D31D8 = lbl_804430F0;
const char *TOVS2Wreck06__class_name = lbl_80443100;
const char *TOVS2Wall01__class_name = lbl_80443110;

BmlResource *TOVS2Wall01__bml_resource;

extern __declspec(section ".sdata2") const f32 lbl_805DBAA8 = 0.0f;
extern __declspec(section ".sdata2") const f32 lbl_805DBAAC = 800.0f;
extern __declspec(section ".sdata2") const f32 lbl_805DBAB0 = 50.0f;
extern __declspec(section ".sdata2") const f32 lbl_805DBAB4 = 10.0f;
}
