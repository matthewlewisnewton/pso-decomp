#ifndef PSO_MISC_TOCONTAINERANCIENTENEMYRARE_H
#define PSO_MISC_TOCONTAINERANCIENTENEMYRARE_H

#include "types.h"
#include "pso/misc/TOContainerAncientEnemy.h"

struct TOContainerAncientEnemyRare : public TOContainerAncientEnemy {
    virtual ~TOContainerAncientEnemyRare();
};

typedef char TOContainerAncientEnemyRare_size[sizeof(TOContainerAncientEnemyRare) == 0x368 ? 1 : -1];

extern "C" {
s32 TOContainerAncientEnemyCommon__create(s32 arg0);
u8 *TOContainerAncientEnemyRare__ct(u8 *arg0, s32 arg1);
}

// --- C functions defined in TOContainerAncientEnemyRare.cpp ---
extern "C" {
s32 TOContainerAncientEnemyCommon__create(s32 container_ancient_enemy_common);
u8 *TOContainerAncientEnemyRare__ct(u8 *container_ancient_enemy_rare, s32 arg1);
}
// --- end of C functions

#endif
