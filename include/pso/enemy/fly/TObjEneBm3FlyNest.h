#ifndef PSO_ENEMY_FLY_TOBJENEBM3FLYNEST_H
#define PSO_ENEMY_FLY_TOBJENEBM3FLYNEST_H

#include "types.h"
#include "pso/enemy/dd/TObjEneDD.h"

struct TObjEneBm3FlyNest : public TObjEneDD {
    virtual ~TObjEneBm3FlyNest();
    virtual void run_task();
    virtual void render();
    virtual void vfunc_88();
    virtual void render_with_state_debug();
    virtual void render_shadows();
    void init_params();
    void state_initial_emit(s32);
    void vfunc_63();
    void vfunc_62();
    void vfunc_61();
    void vfunc_28();
    u8 unk_374[0x4];
    u32 m_394;
    u8 _pad398[0x10];
    u32 m_3a8;
    u32 m_3ac;
    u32 m_3b0;
    u32 m_3b4;
    u8 _pad3B8[0xC];
    u16 m_3c4;
    u8 _pad3C6[0x7A];
    void* m_440;
    u8 _pad444[0x70];
    u32 m_4b4;
    u32 m_4b8;
    u32 m_4bc;
    u32 m_4c0;
    u32 m_4c4;
    u32 m_4c8;
    u32 m_4cc;
    u32 m_4d0;
    u32 m_4d4;
    static void capture_attachment(void * _w0);
    static int init(void* p);
    void remove_child(u8 *child);
    s32 has_free_attack_slot(u16 id);
    void spawn_child();
    void update_replenish();
    void copy_pos();
    static void free_fly();
    static void *create(void *arg0);
    static void load_resources();
    static void init_vertex_table();
    u8 unk_4BC[0x20];
};

typedef char TObjEneBm3FlyNest_size[sizeof(TObjEneBm3FlyNest) == 0x4DC ? 1 : -1];

extern "C" {
u8 *__ct__26TObjEneBm3FlyNest_CarryFlyFP7TObjectlllll(u8 *self, void *parent, s32 a, s32 b, s32 unused, s32 c, s32 d);
void *__ct__17TObjEneBm3FlyNestFP7TObjectP14EnemySetRecord(void *arg0, void *arg1, void *arg2);
void *get_spawn_point__17TObjEneBm3FlyNestFv(void *p);
void TObjEneBm3FlyNest__sub_800B318C(u8 *arg0, s32 arg1);
s32 has_pending_spawns__17TObjEneBm3FlyNestCFv(u8 *arg0);
int get_resources__17TObjEneBm3FlyNestFv(void);
void *__dt__26TObjEneBm3FlyNest_CarryFlyFv(void *arg0, s16 arg1);
int remap_child_sound__17TObjEneBm3FlyNestFl(void *p, s32 sound_id);
void dispatch_action__17TObjEneBm3FlyNestFUll(s32 arg0, u32 arg1, s32 arg2);
void handle_appear__17TObjEneBm3FlyNestFl(u8 *arg0, s32 arg1);
void sample_carrier_attachments__17TObjEneBm3FlyNestFP10NJS_OBJECT(s32 arg0);
void handle_event__17TObjEneBm3FlyNestFl(void *arg0, s32 arg1);
void handle_motion_event__17TObjEneBm3FlyNestFl(u8 *arg0, s32 arg1);
void handle_state__17TObjEneBm3FlyNestFl(void *arg0, s32 arg1);
void render__17TObjEneBm3FlyNestFv(u8 *arg0);
void run_task__17TObjEneBm3FlyNestFv(u8 *arg0);
void state_dying__17TObjEneBm3FlyNestFl(u8 *actor, s32 arg1);
void state_spawn__17TObjEneBm3FlyNestFl(void *arg0, s32 arg1);
void state_wait__17TObjEneBm3FlyNestFl(void *arg0, s32 arg1);
void update_state__17TObjEneBm3FlyNestFl(void *arg0, s32 arg1);
}

#endif
