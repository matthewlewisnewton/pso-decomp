#ifndef PSO_BOSS_TBOSS6TUBE_H
#define PSO_BOSS_TBOSS6TUBE_H

#include "types.h"
#include "pso/TObject.h"

struct TBoss6Tube : public TObject {
    virtual ~TBoss6Tube();
    void sub_802B1218();
    u32 m_1c;
    u32 m_20;
    u32 m_24;
    u32 m_28;
    u32 m_2c;
    virtual void run_task();
    virtual void render();
    static f32 scale_by_const(f32 farg0);
    static f32 calc_tube_progress(s32 arg0);
    static void reset_state();
    void update_wobble();
    void spawn_trap();
    void update_timer();
    // Defined in TBoss6EmptyWarp_802B0E2C.cpp: that unit owns 0x802B0FC8 and
    // 0x802B1004, and both write this object's m_1c / m_20.
    void activate_warp();
    void sub_802B1004();
    static TBoss6Tube *create(void *arg0);
    static void free_resources();
    static void load_resources();
};

typedef char TBoss6Tube_size[sizeof(TBoss6Tube) == 0x30 ? 1 : -1];
#endif
