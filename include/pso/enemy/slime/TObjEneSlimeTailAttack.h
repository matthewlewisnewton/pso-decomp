#ifndef PSO_ENEMY_SLIME_TOBJENESLIMETAILATTACK_H
#define PSO_ENEMY_SLIME_TOBJENESLIMETAILATTACK_H

#include "types.h"
#include "pso/enemy/TObjEnemy.h"

struct TObjEneSlimeTailAttack : public TObjEnemy {
    virtual ~TObjEneSlimeTailAttack();
    void draw_stretched_segment(void *, void *, f32);
    void sub_800E841C();
    virtual void run_task();
    virtual void render();
    int find_nearest_enemy_with_flag(f32);
};

struct TObjEneSlimeOne;
struct TObjEneSlimeWaterBomb;
extern "C" {
u8 *__ct__15TObjEneSlimeOneFP7TObjectP12TObjEneSlimePvPC3Vec(u8 *actor, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void *__ct__22TObjEneSlimeTailAttackFP7TObjectPC3VeclP15TObjEneSlimeOne(TObjEneSlimeTailAttack *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
void *__ct__21TObjEneSlimeWaterBombFP15TObjEneSlimeOneP15TObjEneSlimeOne(TObjEneSlimeWaterBomb *arg0, void *arg1, void *arg2);
void get_slime_tail_pose(u8 *dst);
void capture_slime_tail_node(void);
void reset_slime_tail_node_index(void);
void sub_800E841C__22TObjEneSlimeTailAttackFv(u8 *arg0);
void render__22TObjEneSlimeTailAttackFv(u8 *arg0);
void run_task__22TObjEneSlimeTailAttackFv(u8 *arg0);
void *__dt__15TObjEneSlimeOneFv(void *arg0, s16 arg1);
void *__dt__21TObjEneSlimeWaterBombFv(void *arg0, s16 arg1);
void *create__22TObjEneSlimeTailAttackFlPC3VeclP15TObjEneSlimeOne(s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void *__dt__22TObjEneSlimeTailAttackFv(void *arg0, s16 arg1);
void update_trail_position__15TObjEneSlimeOneFv(s32 arg0);
u8 *__ct__15TObjEneSlimeOneFP7TObjectP12TObjEneSlimePv(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void initialize_slime_instance_state__15TObjEneSlimeOneFv(u8 *actor);
void render__15TObjEneSlimeOneFv(TObjEneSlimeOne *arg0);
void set_display_mode__15TObjEneSlimeOneFl(void *arg0, s32 arg1);
void set_random_timer__15TObjEneSlimeOneFll(void *arg0, s32 arg1, s32 arg2);
s32 try_spawn_child__15TObjEneSlimeOneFPv(int origin, void *arg1);
}
extern "C" {
}
s32 water_bomb_hit_nearby(u8 *target);

#endif
