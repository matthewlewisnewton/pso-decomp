#ifndef PSO_MISC_TOCONTAINERANCIENTITEMNONE_H
#define PSO_MISC_TOCONTAINERANCIENTITEMNONE_H

#include "types.h"
#include "pso/misc/TOContainerAncientItemRare.h"

struct TOContainerAncientItemNone : public TOContainerAncientItemRare {
    virtual ~TOContainerAncientItemNone();
    virtual void vfunc_6(s16 *, s32);
    static void *create(void *arg0);
};

typedef char TOContainerAncientItemNone_size[sizeof(TOContainerAncientItemNone) == 0x368 ? 1 : -1];

#endif
