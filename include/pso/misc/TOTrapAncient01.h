#ifndef PSO_MISC_TOTRAPANCIENT01_H
#define PSO_MISC_TOTRAPANCIENT01_H

#include "types.h"
#include "pso/misc/TOTrap.h"
#include "pso/misc/RenderFadeState.h"

struct TOTrapAncient01 : public TOTrap {
    virtual ~TOTrapAncient01();
    virtual void vfunc_82();
    virtual void vfunc_81();
    virtual void vfunc_84();
    virtual void play_sounds();
    virtual void vfunc_88();
    virtual void vfunc_86();
    virtual void vfunc_6(s16 *, s32);
    virtual f32 receive_physical_attack(void *, f32);
    virtual void render();
    DirectAttackPayload attack;
    f32 m_34C;
    f32 m_350;
    f32 m_354;
    RenderFadeState fades[4];
    void release_trapped_player();
    void *create();
    static void release_static_resource();
    static void load_resources();
    static s32 check_trigger_flag(s32 arg0, s32 arg1);
};

typedef char TOTrapAncient01_size[sizeof(TOTrapAncient01) == 0x3C8 ? 1 : -1];

extern "C" {
TOTrapAncient01 *TOTrapAncient01__ct(TOTrapAncient01 *self, void *parent, void *creator);
}

#endif
