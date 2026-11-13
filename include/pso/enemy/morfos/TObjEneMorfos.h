#ifndef PSO_ENEMY_MORFOS_TOBJENEMORFOS_H
#define PSO_ENEMY_MORFOS_TOBJENEMORFOS_H

#include "types.h"
#include "pso/enemy/dd/TObjEneDD_ST.h"

struct NJS_OBJECT;

struct TObjEneMorfos : public TObjEneDD_ST {
    virtual ~TObjEneMorfos();
    s32 render_reflection();
    virtual void vfunc_28();
    virtual void vfunc_63();
    virtual void vfunc_62();
    virtual void vfunc_61();
    virtual void vfunc_88();
    virtual void update_demo();
    virtual void render_demo();
    void render();
    void run_task();
    u8 unk_374[0x4];
    s32 m_378;
    u8 unk_37C[0x14];
    u8 * m_390;
    u8 unk_394[0xC];
    f32 m_3a0;
    u32 m_3c0;
    u32 m_3c4;
    u8 _pad3C8[0xC];
    u32 m_3d4;
    u8 _pad3D8[0x14];
    void* m_3ec;
    u8 _pad3F0[0x18];
    void* m_408;
    u8 _pad40C[0x18];
    void* m_424;
    u8 _pad428[0x6C];
    u32 m_494;
    void* m_498;
    static int get_resources();
    void draw_guard_wall();
    static void record_model_node_position(NJS_OBJECT *);
    void state_death(s32 arg1);
    void state_patrol(s32 arg1);
    void state_appear(s32 arg1);
    void handle_event_transition(s32 ev);
    void play_frame_sounds();
    void initialize_behavior_parameters();
    void update_body_center();
    s32 turn_toward_angle(s32 arg1, s32 arg2);
    s32 try_enter_low_hp_state();
    s32 check_low_hp_trigger();
    void init_instance();
    static void unload_static_data();
    static void *create(void *set_data);
    void update_ground_probe();
    s32 crosses_heading(s32 start, s32 end, s32 heading);
    u8 unk_480[0x1C];
    f32 m_49c;
    u8 unk_4A0[0x4];
    f32 m_4a4;
    u8 unk_4A8[0x4];
    f32 m_4ac;
    u8 unk_4B0[0x4];
    s32 m_4b4;
    u8 unk_4B8[0x4];
    s32 m_4bc;
    u8 unk_4C0[0x4];
    f32 m_4c4;
    u8 unk_4C8[0x4];
    f32 m_4cc;
    u8 unk_4D0[0x4];
    f32 m_4d4;
    void render_with_camera_fade(s32 idx, s32 mode);
    void state_rotating_projectile_burst(s32 arg1);
    s32 select_target_in_view();
};

typedef char TObjEneMorfos_size[sizeof(TObjEneMorfos) == 0x4D8 ? 1 : -1];

extern "C" {
void *__ct__13TObjEneMorfosFP7TObjectPv(void *arg0, void *arg1, void *arg2);
void state_damaged__13TObjEneMorfosFl(u8 *arg0, s32 arg1);
void state_melee_attack__13TObjEneMorfosFl(TObjEneMorfos *arg0, s32 arg1);
void state_projectile_attack__13TObjEneMorfosFl(TObjEneMorfos *arg0, s32 arg1);
void state_move__13TObjEneMorfosFl(u8 *arg0, s32 arg1);
void state_disappear__13TObjEneMorfosFl(u8 *arg0, s32 arg1);
void state_hidden__13TObjEneMorfosFl(u8 *arg0, s32 arg1);
void state_fade_in__13TObjEneMorfosFl(u8 *arg0, s32 arg1);
s32 TObjEneMorfos__sub_803344F0(void *arg0);
int get_parameters__13TObjEneMorfosFv(void);
void dispatch_action__13TObjEneMorfosFUll(u8 *arg0, u32 arg1, s32 ev);
u8 *__dt__13TObjEneMorfosFv(u8 *arg0, s16 arg1);
void render__13TObjEneMorfosFv(u8 *arg0);
void run_task__13TObjEneMorfosFv(u8 *arg0);
void state_rotating_projectile_burst__13TObjEneMorfosFl(u8 *arg0, s32 arg1);
}

#endif
