#ifndef PSO_MISC_TPLYPTCLOBJECTLEFTHAND_H
#define PSO_MISC_TPLYPTCLOBJECTLEFTHAND_H

#include "types.h"
#include "pso/misc/TPlyFollowParticleCtrl.h"

struct TPlyPtclObjectLeftHand : public TPlyFollowParticleCtrl {
    virtual ~TPlyPtclObjectLeftHand();
    static s32 update_attachment(s32 arg0);
};

typedef char TPlyPtclObjectLeftHand_size[sizeof(TPlyPtclObjectLeftHand) == 0xB0 ? 1 : -1];
#endif
