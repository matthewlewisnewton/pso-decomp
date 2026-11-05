#ifndef PSO_ITEMS_TITEMWEAPONMECHGUN_H
#define PSO_ITEMS_TITEMWEAPONMECHGUN_H
#include "types.h"
struct TItemWeaponMechgun {
    void prepareMarker();
    u8 baseFields[0x1F8];
    f32 muzzle[2][3];
    s32 effectJoint, effectAngle, effectScaleJoint, effectFrame;
};
#endif
