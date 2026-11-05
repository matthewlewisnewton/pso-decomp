#ifndef PSO_ENEMY_TOBJENESLIMETAILATTACK_H
#define PSO_ENEMY_TOBJENESLIMETAILATTACK_H

#include "types.h"
#include "pso/enemy/TObjEnemy.h"

struct TObjEneSlimeOne;

struct SlimeTailPose {
    Vec attachment;
    Vec shadows[4];
};

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
    SlimeTailPose pose;
};

typedef char SlimeTailSize[sizeof(TObjEneSlimeTailAttack) == 0x3CC ? 1 : -1];

struct TObjEneSlimeWaterBomb;
extern "C" {
void get_slime_tail_pose(SlimeTailPose *dst);
void capture_slime_tail_node(NJS_OBJECT *);
void reset_slime_tail_node_index(void);
void sub_800E841C__22TObjEneSlimeTailAttackFv(u8 *arg0);
void render__22TObjEneSlimeTailAttackFv(u8 *arg0);
void run_task__22TObjEneSlimeTailAttackFv(u8 *arg0);
void initialize_slime_instance_state__15TObjEneSlimeOneFv(u8 *actor);
void render__15TObjEneSlimeOneFv(TObjEneSlimeOne *arg0);
}

#endif
