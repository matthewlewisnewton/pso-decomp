struct NJS_OBJECT;
#ifndef PSO_ENEMY_TOBJENESLIMETAILATTACK_H
#define PSO_ENEMY_TOBJENESLIMETAILATTACK_H

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
u8 *TObjEneSlimeOne__ct(u8 *actor, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void TObjEneSlimeOne__sub_800E969C(TObjEneSlimeOne *arg0);
void *TObjEneSlimeTailAttack__ct(TObjEneSlimeTailAttack *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
void *TObjEneSlimeWaterBomb__ct(TObjEneSlimeWaterBomb *arg0, void *arg1, void *arg2);
void TObjPlayer__sub_800E80C0(u8 *dst);
void TObjPlayer__sub_800E8128(NJS_OBJECT *);
void TObjPlayer__sub_800E81A8(void);
void sub_800E841C__22TObjEneSlimeTailAttackFv(u8 *arg0);
void render__22TObjEneSlimeTailAttackFv(u8 *arg0);
void run_task__22TObjEneSlimeTailAttackFv(u8 *arg0);
void TObjPlayer__sub_800E9D7C(void *p);
void TObjPlayer__sub_800E9EFC(u8 *arg0);
void TObjPlayer__sub_800EA120(u8 *actor);
void TObjPlayer__sub_800EA364(u8 *arg0);
void TObjPlayer__sub_800EA56C(u8 *actor);
void TObjPlayer__sub_800EA678(u8 *arg0);
void TObjPlayer__sub_800EA820(u8 *arg0);
void *__dt__15TObjEneSlimeOneFv(void *arg0, s16 arg1);
void *__dt__21TObjEneSlimeWaterBombFv(void *arg0, s16 arg1);
void begin_appear__15TObjEneSlimeOneFPv(void *p);
void *create__22TObjEneSlimeTailAttackFiiii(s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void *dt__22TObjEneSlimeTailAttackFPvs(void *arg0, s16 arg1);
void enter_appear_state__10TObjPlayerFPv(u8 *arg0);
void enter_slime_state__10TObjPlayerFPv(u8 *arg0);
void fn_800E9238(s32 arg0);
void fn_800E9538(u8 *arg0);
void fn_800E95F4(u8 *arg0);
u8 *init__15TObjEneSlimeOneFPviii(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void init_slime_display__10TObjPlayerFPv(void *a0);
void init_slime_state__10TObjPlayerFPv(void *actor);
void init_split_effect__15TObjEneSlimeOneFPv(u8 *arg0);
void init_state__15TObjEneSlimeOneFPv(void *a0);
void initialize_slime_instance_state__15TObjEneSlimeOneFv(u8 *actor);
void render__15TObjEneSlimeOneFv(TObjEneSlimeOne *arg0);
void reset_display__15TObjEneSlimeOneFPv(void *a0);
void reset_display_state__15TObjEneSlimeOneFPv(void *a0);
void set_display_mode__15TObjEneSlimeOneFPvi(void *arg0, s32 arg1);
void set_random_timer__15TObjEneSlimeOneFPvii(void *arg0, s32 arg1, s32 arg2);
void tick_timer__15TObjEneSlimeOneFPv(TObjEneSlimeOne *arg0);
s32 try_spawn_child__15TObjEneSlimeOneFPv(int origin, void *arg1);
void update_dive_timer__10TObjPlayerFPv(u8 *arg0);
}
void update_effect_fade_lifetime(u8 *arg0);
extern "C" {
void update_slime_timer__10TObjPlayerFPv(u8 *arg0);
void update_tick__15TObjEneSlimeOneFPv(TObjEneSlimeOne *arg0);
void update_wait_search__15TObjEneSlimeOneFPv(TObjEneSlimeOne *arg0);
void update_water_bomb_timer__15TObjEneSlimeOneFPv(u8 *arg0);
}
s32 water_bomb_hit_nearby(u8 *target);

#endif
