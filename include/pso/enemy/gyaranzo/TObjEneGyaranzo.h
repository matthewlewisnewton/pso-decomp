#ifndef PSO_ENEMY_GYARANZO_TOBJENEGYARANZO_H
#define PSO_ENEMY_GYARANZO_TOBJENEGYARANZO_H

#include "types.h"
#include "dolphin/mtx.h"
#include "pso/enemy/TObjEnemyCustom.h"
#include "pso/render/RenderFadeState.h"
#include "pso/render/TUnk_80494938.h"

struct TObjEneGyaranzo : public TObjEnemyCustom {
    TObjEneGyaranzo(TObject *parent, void *set_data);
    virtual ~TObjEneGyaranzo();
    void cancel_fade_state();
    virtual s32 update_movement_status();
    virtual s32 update_shock_clock();
    void sub_800D2A68();
    void select_targets();
    virtual void run_task();
    virtual void render();
    void sub_800D37F4();
    void sub_800D2900();
    void init_params_from_table();
    virtual void vfunc_62();
    virtual void vfunc_63();
    virtual void vfunc_58();
    virtual s32 is_target_in_attack_range();
    virtual void vfunc_59();
    virtual void vfunc_61();
    void spawn_missile();
    s32 hidden_part_count;
    Vec chase_destination;
    f32 distance_travelled;
    f32 chase_limit;
    f32 missile_distance;
    s32 armor_stage;
    s32 unknown_3ac;
    s32 charge_hp_threshold;
    s32 charge_count;
    s32 hit_debris_cooldown;
    u32 target_ids[4];
    s32 target_count;
    TUnk_80494938 fade;
    RenderFadeState camera_fades[4];
    static void *create(void *arg0);
    static void free_static_instances();
};

typedef char GyaranzoFadeOffset[offsetof(TObjEneGyaranzo, fade) == 0x3D0 ? 1 : -1];
typedef char GyaranzoCameraFadesOffset[offsetof(TObjEneGyaranzo, camera_fades) == 0x3EC ? 1 : -1];
typedef char TObjEneGyaranzo_size[sizeof(TObjEneGyaranzo) == 0x45C ? 1 : -1];
#endif
