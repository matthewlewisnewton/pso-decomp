#ifndef PSO_ITEM_WEAPONEFFECTDESCRIPTOR_H
#define PSO_ITEM_WEAPONEFFECTDESCRIPTOR_H

#include "pso/system/NinjaTypes.h"

struct Desc_8011E5C4 {
    u8 unk_00[0x10];
    s32 mode;
    u8 unk_14[0x24];
    f32 m_38;
    u8 unk_3c[4];
    u32 flags;
    NJS_OBJECT *model;
    u8 unk_48[4];
    f32 scale;
    s32 m_50;
    u8 unk_54[4];
    s32 m_58;
    u8 unk_5c[4];
    NJS_ARGB color;
    s32 *m_70;
    s32 *m_74;
};

#endif
