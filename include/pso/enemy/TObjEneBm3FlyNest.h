#ifndef PSO_ENEMY_TOBJENEBM3FLYNEST_H
#define PSO_ENEMY_TOBJENEBM3FLYNEST_H

#include "types.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/misc/RenderFadeState.h"

struct BmlResource;

struct TObjEneBm3FlyNest : public TObjEneDD {
    virtual ~TObjEneBm3FlyNest();
    virtual void run_task();
    virtual void render();
    virtual void vfunc_88();
    virtual void render_with_state_debug();
    virtual void render_shadows();
    void handle_state(s32);
    void state_dying(s32);
    void handle_motion_event(s32);
    void state_spawn(s32);
    void update_state(s32);
    void fn_800B318C(s32);
    void handle_event(s32);
    void state_wait(s32);
    void handle_appear(s32);
    void init_params();
    void state_initial_emit(s32);
    void vfunc_63();
    void vfunc_62();
    void vfunc_61();
    void vfunc_28();
    s32 demo_state;
    s32 initial_child_count;
    s32 spawn_limit;
    s32 unknown_398[4];
    s32 damage_phase;
    s32 visible;
    s32 child_count;
    s32 children_spawned;
    u16 child_ids[6];
    u16 next_child_id;
    Vec attachment_points[2];
    Vec carrier_points[8];
    RenderFadeState camera_fades[4];
    f32 model_height;
    s32 replenish_phase;
    s32 pending_spawns;
    s32 replenish_timer;
    s32 replenish_count;
    s32 replenish_delay;
    s32 state_timer;
    s32 state_counter;
    s32 substate;
    s32 state_angle;
    f32 sink_distance;
    static void capture_attachment(NJS_OBJECT *);
    static void sample_carrier_attachments(NJS_OBJECT *);
    static BmlResource *get_resources();
    static int init(void* p);
    s32 remap_child_sound(s32);
    void remove_child(u8 *child);
    s32 has_free_attack_slot(u16 id);
    Vec *get_spawn_point();
    s32 has_pending_spawns() const;
    void spawn_child();
    void update_replenish();
    void copy_pos();
    static void free_fly();
    static void *create(void *arg0);
    static void load_resources();
    static void init_vertex_table();
};

typedef char TObjEneBm3FlyNest_size[sizeof(TObjEneBm3FlyNest) == 0x4DC ? 1 : -1];

extern "C" {
void *TObjEneBm3FlyNest__ct(void *arg0, void *arg1, void *arg2);
void dispatch_state__17TObjEneBm3FlyNestFiUii(s32 arg0, u32 arg1, s32 arg2);
void render__17TObjEneBm3FlyNestFv(u8 *arg0);
void run_task__17TObjEneBm3FlyNestFv(u8 *arg0);
}

#endif
