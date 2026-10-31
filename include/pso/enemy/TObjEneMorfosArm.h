#ifndef PSO_ENEMY_TOBJENEMORFOSARM_H
#define PSO_ENEMY_TOBJENEMORFOSARM_H

#include "types.h"
#include "pso/object/TObjMotion.h"

struct TObjEneMorfosArm : public TObjMotion {
    virtual ~TObjEneMorfosArm();
    u32 m_fc;
    u16 m_100;
    static void *create(void *arg0, void *arg1);
    static void init_global();
    static void unload_static_data();
    virtual void render();
    virtual void run_task();
    u8 unk_102[0x2];
};

typedef char TObjEneMorfosArm_size[sizeof(TObjEneMorfosArm) == 0x104 ? 1 : -1];

#endif
