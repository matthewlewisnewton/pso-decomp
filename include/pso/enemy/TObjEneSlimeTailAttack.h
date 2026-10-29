#ifndef PSO_ENEMY_TOBJENESLIMETAILATTACK_H
#define PSO_ENEMY_TOBJENESLIMETAILATTACK_H

#include "types.h"
#include "pso/enemy/TObjEnemy.h"

struct TObjEneSlimeOne;

struct TObjEneSlimeTailAttack : public TObjEnemy {
    TObjEneSlimeTailAttack(TObject *parent, const Vec *position, s32 angle, TObjEneSlimeOne *owner);
    virtual ~TObjEneSlimeTailAttack();
    static TObjEneSlimeTailAttack *create(s32, const Vec *, s32, TObjEneSlimeOne *);
    void draw_blob_shadows();
    s32 check_hits();
    void draw_stretched_segment(void *, void *, f32);
    void sub_800E841C();
    virtual void run_task();
    virtual void render();
    int find_nearest_enemy_with_flag(f32);

    TObjEneSlimeOne *owner;
    s32 active;
    s32 last_hit_player;
    Vec stretch_scale;
    f32 fade;
    Vec attachment_position;
    Vec shadow_positions[4];
};

typedef char SlimeTailSize[sizeof(TObjEneSlimeTailAttack) == 0x3CC ? 1 : -1];

struct TObjEneSlimeWaterBomb;
extern "C" {
void TObjPlayer__sub_800E80C0(u8 *dst);
void TObjPlayer__sub_800E8128(void);
void TObjPlayer__sub_800E81A8(void);
void sub_800E841C__22TObjEneSlimeTailAttackFv(u8 *arg0);
void render__22TObjEneSlimeTailAttackFv(u8 *arg0);
void run_task__22TObjEneSlimeTailAttackFv(u8 *arg0);
void fn_800E9238(s32 arg0);
void initialize_slime_instance_state__15TObjEneSlimeOneFv(u8 *actor);
void render__15TObjEneSlimeOneFv(TObjEneSlimeOne *arg0);
void set_display_mode__15TObjEneSlimeOneFPvi(void *arg0, s32 arg1);
void set_random_timer__15TObjEneSlimeOneFPvii(void *arg0, s32 arg1, s32 arg2);
s32 try_spawn_child__15TObjEneSlimeOneFPv(int origin, void *arg1);
}
extern "C" {
}

#endif
