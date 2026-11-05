#ifndef PSO_MISC_TOBOSS4TOWER_H
#define PSO_MISC_TOBOSS4TOWER_H

#include "types.h"
#include "pso/misc/TOBoss4.h"

struct TOBoss4Tower : public TOBoss4 {
    virtual ~TOBoss4Tower();
    virtual void render();
};

typedef char TOBoss4Tower_size[sizeof(TOBoss4Tower) == 0x98 ? 1 : -1];
#endif
