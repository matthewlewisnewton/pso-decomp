#ifndef PSO_BOSS_TBOSS8DRAGONEFFBREATH_H
#define PSO_BOSS_TBOSS8DRAGONEFFBREATH_H

#include "types.h"
#include "pso/TObject.h"
#include <dolphin/mtx.h>

struct TBoss8DragonEffBreath : public TObject {
    TBoss8DragonEffBreath(TObject *parent, void *p, void *v, s32 a, s16 b);
    virtual ~TBoss8DragonEffBreath();
    Vec position;
    Vec velocity;
    u32 m_34; // Forwarded unchanged to the dragon's breath setup.
    u16 entity_id;
    void *attack_history;
    virtual void render();
    virtual void run_task();
};

#include <stddef.h>
typedef char TBoss8DragonEffBreath_position[offsetof(TBoss8DragonEffBreath, position) == 0x1C ? 1 : -1];
typedef char TBoss8DragonEffBreath_velocity[offsetof(TBoss8DragonEffBreath, velocity) == 0x28 ? 1 : -1];
typedef char TBoss8DragonEffBreath_entity[offsetof(TBoss8DragonEffBreath, entity_id) == 0x38 ? 1 : -1];
typedef char TBoss8DragonEffBreath_history[offsetof(TBoss8DragonEffBreath, attack_history) == 0x3C ? 1 : -1];
typedef char TBoss8DragonEffBreath_size[sizeof(TBoss8DragonEffBreath) == 0x40 ? 1 : -1];

extern "C" {
void *__dt__21TBoss8DragonEffBreathFv(void *arg0, s16 arg1);
}

#endif
