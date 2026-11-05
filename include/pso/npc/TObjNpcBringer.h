#ifndef PSO_NPC_TOBJNPCBRINGER_H
#define PSO_NPC_TOBJNPCBRINGER_H
#include "types.h"
#include "pso/npc/TObjNpcBase.h"

class TObjNpcBringer : public TObjNpcBase {
public:
    virtual ~TObjNpcBringer();
    virtual void vfunc_88();
public:
    static void *create(void *arg0);
};
typedef char TObjNpcBringer_size[sizeof(TObjNpcBringer) == 0x3B8 ? 1 : -1];

#endif
