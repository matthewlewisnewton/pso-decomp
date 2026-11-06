#ifndef PSO_MISC_TPLYPTCLOBJECTRIGHTHAND_H
#define PSO_MISC_TPLYPTCLOBJECTRIGHTHAND_H

#include "types.h"
#include "pso/misc/TPlyFollowParticleCtrl.h"

struct TPlyPtclObjectRightHand : public TPlyFollowParticleCtrl {
    virtual ~TPlyPtclObjectRightHand();
};

typedef char TPlyPtclObjectRightHand_size[sizeof(TPlyPtclObjectRightHand) == 0xB0 ? 1 : -1];

extern "C" {
void *TPlyPtclObjectRightHand__ct(void *ply_ptcl_object_right_hand);
void *__dt__23TPlyPtclObjectRightHandFv(void *arg0, s16 arg1);
}

// --- C functions defined in TPlyPtclObjectRightHand.cpp ---
extern "C" {
void *TPlyPtclObjectRightHand__ct(void *ply_ptcl_object_right_hand);
void *__dt__23TPlyPtclObjectRightHandFv(void *arg0, s16 arg1);
}
// --- end of C functions

#endif
