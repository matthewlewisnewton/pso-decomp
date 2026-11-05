#ifndef PSO_ENEMY_TOBJENESLIMEWATERBOMB_H
#define PSO_ENEMY_TOBJENESLIMEWATERBOMB_H

#include "pso/enemy/TObjEnemy.h"

struct TObjEneSlimeOne;
struct TParticleCtrl;

struct TObjEneSlimeWaterBomb : public TObjEnemy {
    TObjEneSlimeWaterBomb(TObjEneSlimeOne *parent, TObjEneSlimeOne *owner);
    virtual ~TObjEneSlimeWaterBomb();
    virtual void run_task();
    virtual void render();
    int find_nearest_enemy_masked(f32);
    s32 check_hits();
    static TObjEneSlimeWaterBomb *create(TObjEneSlimeOne *parent, TObjEneSlimeOne *owner);

    Vec movement;
    f32 ground_height;
    f32 lifetime;
    TParticleCtrl *particle;
    TObjEneSlimeOne *owner;
    f32 attack_power;
    s32 elapsed_frames;
};

typedef char TObjEneSlimeWaterBomb_size[sizeof(TObjEneSlimeWaterBomb) == 0x398 ? 1 : -1];
#endif
