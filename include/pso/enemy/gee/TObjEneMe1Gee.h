#ifndef PSO_ENEMY_GEE_TOBJENEME1GEE_H
#define PSO_ENEMY_GEE_TOBJENEME1GEE_H

#include "types.h"
#include "pso/enemy/dd/TObjEneDD_ST.h"
#include "pso/render/MaterialOpacityFade.h"

struct NJS_OBJECT;

struct TObjEneMe1Gee : public TObjEneDD_ST {
    virtual ~TObjEneMe1Gee();
    virtual s32 vfunc_104(f32);
    virtual void dispatch_action(u32 state, s32 reason);
    void init_state();
    virtual void vfunc_88();
    virtual u8 *vfunc_101(u8 *);
    virtual void vfunc_89();
    virtual void vfunc_105();
    virtual void vfunc_106();
    virtual void vfunc_107();
    virtual s32 vfunc_108();
    virtual int vfunc_109();
    virtual void vfunc_110(s32);
    virtual void vfunc_111(s32);
    virtual void vfunc_112(s32);
    virtual void vfunc_113();
    virtual void vfunc_114();
    virtual void vfunc_115();
    virtual int vfunc_116(void *);
    virtual void remove_child(TObjEneMe1Gee *);
    virtual void vfunc_28();
    virtual void vfunc_63();
    virtual void vfunc_62();
    virtual void vfunc_61();
    void sync_body_position();
    void start_color_sequence(s32);
    void apply_behavior_parameters();
    void sub_800CBF58(f32);
    void sub_800CBE6C();
    void update_hover_height();
    void update_animation_frame();
    void update_fade_sequence();
    void update_packed_color();
    void set_low_appearance();
    void set_high_appearance();
    void set_in_fighter();
    void set_out_fighter();
    void set_flag3c8_bit2();
    void state_attack_loop(s32);
    void render();
    void run_task();
    u8 unk_374[0x1C];
    u32 m_390;
    u8 unk_394[0xC];
    f32 m_3a0;
    u8 pad_3a4[0x20];
    u32 m_3e0;
    u32 pad_3c8;
    MaterialOpacityFade fade;
    u8 pad_3e8[0x7C];
    TObject *unk_464;
    u8 pad_468[0x28];
    static void load_resources();
    static void cache_result_805D6660();
    static void queue_debug_text(s32 arg0, char *arg1);
    static void advance_camera_ctrl_step(NJS_OBJECT *);
    void state_orbit(s32 arg1);
    void handle_event(s32 arg1);
    void state_return_home(s32 arg1);
    void state_attack(s32 arg1);
    void state_hover(s32 arg1);
    void state_move(s32 arg1);
    void set_flag3c8_bit40();
    void set_flag3c8_bit8();
    void update_photon_target();
    s32 remap_gee_sound(s32 arg1);
    s32 return_home_if_target_lost();
    s32 check_can_attack();
    void update_angle();
    void update_from_float_sum();
    void set_move_speed_x();
    static void free_globals();
    static void *create(void *arg0);
    void set_flag3c8_bit4();
    void activate_with_target(void *arg1, s32 arg2);
    void update();
};

typedef char TObjEneMe1Gee_size[sizeof(TObjEneMe1Gee) == 0x490 ? 1 : -1];
#endif
