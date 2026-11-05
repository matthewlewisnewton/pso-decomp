#ifndef PSO_BOSS_TBOSS6MINE_H
#define PSO_BOSS_TBOSS6MINE_H

#include "types.h"
#include <dolphin/mtx.h>
#include "pso/enemy/TObjEnemy.h"

struct TBoss6Type1;

// Spawn record TBoss6Type1 fills for each mine of its ring. The first 0x40
// bytes are the mag-mine block it copies from the plot; TBoss6Mine__ct reads
// owner, position, point, delay and rng.
struct Boss6MineSpawn {
    s16 a0;
    s16 a2;
    s16 a4;
    s16 a6;
    s16 a8;
    s16 aa;
    s16 ac;
    s16 ae;
    Vec inner;
    Vec c1c;
    u32 c28[5];
    s16 a3c;
    s16 a3e;
    TBoss6Type1 *owner;
    Vec position;
    Vec point;
    s32 delay;
    s32 rng;
};

struct TBoss6Mine : public TObjEnemy {
    virtual ~TBoss6Mine();
    virtual void run_task();
    virtual void vfunc_63();
    virtual void vfunc_62();
    virtual void render_shadows();
    virtual void render();
    u32 m_374;
    u32 m_378;
    s32 heading;
    s32 state;
    u32 m_384;
    u32 m_388;
    s32 state_frames;
    u32 m_390;
    u32 m_394;
    u32 m_398;
    f32 anim_frame;
    u32 rise_delay;
    u32 spread_frames;
    u32 arm_delay;
    f32 travel_distance;
    Vec start_pos;
    Vec target_pos;
    f32 fade_amount;
    void *emitter;
    void copy_pos();
    void draw();
    void update_facing_angles();
    s32 is_far_from_origin();
    // Callers null-check the allocation with cmplwi. s32 would be cmpwi.
    static u32 create(Boss6MineSpawn *spawn);
    static f32 next_random_float(s32 *arg0);
    void explode_damage_players();
    void state_0();
    void state_1();
    void state_2();
    void state_3();
    void state_4();
    void state_5();
    void state_6();
    void state_7();
};

typedef char TBoss6Mine_size[sizeof(TBoss6Mine) == 0x3D0 ? 1 : -1];

extern "C" {
s32 TBoss6Mine__ct(s32 arg0, s32 parent, Boss6MineSpawn *arg2);
void *__dt__10TBoss6MineFPvs(void *arg0, s16 arg1);
void explode_damage_players__10TBoss6MineFv(u8 *arg0);
}

#endif
