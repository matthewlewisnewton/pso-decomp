#include "types.h"
#include "pso/misc/TPlyPtclObjectLeftHand_8030A4C8.h"
#include "pso/misc/TPlyPtclObjectRightHand.h"

extern "C" {

void TPlyFollowParticleCtrl__ct(void *);
void __dl__7TObjectFPv(void *);

extern s32 __vt__23TPlyPtclObjectRightHand[];

void *__dt__23TPlyPtclObjectRightHandFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__23TPlyPtclObjectRightHand;
        __dt__22TPlyFollowParticleCtrlFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

extern void *TPlyPtclObjectRightHand__class_name;

void *TPlyPtclObjectRightHand__ct(void *ply_ptcl_object_right_hand) {
    TPlyFollowParticleCtrl__ct(ply_ptcl_object_right_hand);
    *(s32 **)((s8 *)ply_ptcl_object_right_hand + 0x18) = __vt__23TPlyPtclObjectRightHand;
    *(void * *)&((TPlyPtclObjectRightHand *)ply_ptcl_object_right_hand)->m_name = TPlyPtclObjectRightHand__class_name;
    return ply_ptcl_object_right_hand;
}

}
