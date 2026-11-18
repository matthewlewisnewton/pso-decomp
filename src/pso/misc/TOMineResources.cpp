#include "pso/object/TObjMotion.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/system/BmlResourceDescriptor.h"

extern "C" {
static __declspec(section ".rodata") const char lbl_80441F40[] ATTRIBUTE_ALIGN(4) = "de_obj_o_zirai02_light.gj";
static __declspec(section ".rodata") const char lbl_80441F5C[] ATTRIBUTE_ALIGN(4) = "de_obj_o_zirai01_light.gj";
static __declspec(section ".rodata") const char lbl_80441F78[] ATTRIBUTE_ALIGN(4) = "de_obj_o_zirai03_light.gj";
static __declspec(section ".rodata") const char lbl_80441F94[] ATTRIBUTE_ALIGN(4) = "de_obj_o_zirai04_light.gj";
static __declspec(section ".rodata") const char lbl_80441FB0[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_zirai01.gj";
static __declspec(section ".rodata") const char lbl_80441FC4[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_zirai02.gj";
static __declspec(section ".rodata") const char lbl_80441FD8[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_zirai03.gj";
static __declspec(section ".rodata") const char lbl_80441FEC[] ATTRIBUTE_ALIGN(4) = "fe_obj_o_zirai04.gj";
static __declspec(section ".rodata") const char lbl_80442000[] ATTRIBUTE_ALIGN(4) = "bm_o_mine.bml";
static __declspec(section ".rodata") const char lbl_80442010[] ATTRIBUTE_ALIGN(4) = "TOMine";

extern const s32 mine_trap_keymachine_table[36] = {
    -1,         0x4bc12,    0x4bc12,    0x43c11,    0x43c11,    0x43c11,    0x4004bc0b, 0x4004bc0b, 0x4004bc12,
    0x4004bc12, 0x4004bc12, -1,         -1,         -1,         -1,         -1,         0x4004bc07, 0x4004bc07,
    -1,         0x4bc07,    0x4bc07,    0x4004bc07, 0x4004bc07, 0x4bc19,    0x4bc19,    0x4bc19,    0x4bc19,
    0x4bc19,    0x4004bc19, 0x4004bc19, -1,         -1,         -1,         -1,         0x4004bc19, 0x4004bc19,
};
extern const s32 mine_trap_effect_table[36] = {
    -1,         0x4b913,    0x4b913,    0x43912,    0x43912,    0x43912,    0x4004b90c, 0x4004b90c, 0x4004b913,
    0x4004b913, 0x4004b913, -1,         -1,         -1,         -1,         -1,         0x4004b908, 0x4004b908,
    -1,         0x4b908,    0x4b908,    0x4004b908, 0x4004b908, 0x4b91a,    0x4b91a,    0x4b91a,    0x4b91a,
    0x4b91a,    0x4004b91a, 0x4004b91a, -1,         -1,         -1,         -1,         0x4004b91a, 0x4004b91a,
};
extern const f32 lbl_80442138[36] = {
    0.0f,  1.0f,  1.0f,  1.15f, 1.15f, 1.15f, 1.3f,  1.3f,  1.45f, 1.45f, 1.45f, 0.0f,
    0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.15f, 1.15f, 1.3f,
    1.3f,  1.3f,  1.3f,  1.3f,  1.45f, 1.45f, 0.0f,  0.0f,  0.0f,  0.0f,  1.45f, 1.45f,
};

static __declspec(section ".rodata") const char lbl_804421C8[] ATTRIBUTE_ALIGN(4) = "TOMineTrap";
static __declspec(section ".rodata") const char lbl_804421D4[] ATTRIBUTE_ALIGN(4) = "TOMineDisp";

const char *bm_o_mine_model_names[9] = {
    lbl_80441F40, lbl_80441F5C, lbl_80441F78, lbl_80441F94,
    lbl_80441FB0, lbl_80441FC4, lbl_80441FD8, lbl_80441FEC,
    NULL,
};
const char *bm_o_mine_motion_names[1] = {NULL};
BmlResourceDescriptor mine_resource_desc = {lbl_80442000, bm_o_mine_model_names, bm_o_mine_motion_names, 8, 0};
CollisionBody mine_collision_body_parts[1] = {
    {{0.0f, 0.0f, 0.0f}, 3.0f, 0.0f, 0, 0x18005, {0.0f, 0.0f, 0.0f}, 0.0f},
};

const char *TOMine__name = lbl_80442010;
s32 mine_trap_instance_id = 1;
f32 lbl_805D307C = 700.0f;
const char *TOMineTrap__data_805D3080 = lbl_804421C8;
const char *TOMineDisp__name = lbl_804421D4;

BmlResource *lbl_805D5A50;
s32 mine_trap_count;

extern __declspec(section ".sdata2") const f32 lbl_805DB850 = 4e+04f;
extern __declspec(section ".sdata2") const f32 lbl_805DB854 = 4e+02f;
extern __declspec(section ".sdata2") const f32 lbl_805DB858 = 2e+01f;
}
