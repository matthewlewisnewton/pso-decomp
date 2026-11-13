#ifndef PSO_ENEMY_CANADIN_TOBJENEME1CANADIN_H
#define PSO_ENEMY_CANADIN_TOBJENEME1CANADIN_H

#include "types.h"

class TObjChara;
#include "pso/enemy/dd/TObjEneDD_ST.h"
#include "pso/render/MaterialOpacityFade.h"
#include "pso/enemy/canadin/TObjEneMe1Canadin_EffLight.h"

struct TObjEneMe1Canadin : public TObjEneDD_ST {
    TObjEneMe1Canadin(TObject *parent, void *set_data, s32 kind);
    TObjEneMe1Canadin(TObject *parent, TObjEneMe1Canadin *leader, Vec *pos, s32 id, s32 sub_id);
    virtual ~TObjEneMe1Canadin();
    virtual void dispatch_action(u32 state, s32 reason);
    virtual s32 vfunc_104(f32);
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
    virtual void update_if_ready();
    virtual void render_canadin_model_with_debug_type();
    virtual int vfunc_116(TObjChara *);
    virtual void vfunc_117(TObjEneMe1Canadin *);
    void vfunc_63();
    void vfunc_62();
    void vfunc_61();
    void vfunc_28();
    void render();
    u8 pad_374[0x58];
    MaterialOpacityFade fade;
    u8 pad_3E8[0x20];
    TObjEneMe1Canadin_EffLight *eff_light;  // created in setup_enemy, queued in the dtor
    u8 pad_40C[0x94];
    TObject *unk_4A0;  // queued for destruction in the dtor; writer not in this TU
    u8 pad_4A4[0x28];
    void update_by_state(s32 arg1);
    void update_walk_animation(s32 arg1);
    void run_task(s32 arg1);
    void move(s32 arg1);
    void action(s32 arg1);
    void handle_state(s32 arg1);
    void pack_color_rgba();
    void reset_map_core(NJS_ARGB *color);
    s32 try_trigger_action();
    void advance_state_4_to_5();
    s32 check_target();
    void update_move();
    void set_flag3c8_bit40();
    void set_flag3c8_bit20();
    void set_flag3c8_bit8();
    void set_attack_flag();
    void set_leader_index(TObjChara *target, s32 index);
    void update_fade_sequence();
    void update_angle();
    void update_hover_height();
    void set_target_speed_z();
    void update_position_with_offset();
    void update_by_field_0x354();
    void copy_pos();
    void run_task();
    void setup_enemy();
    static void *create(void *arg0);
    static void load_resources();
    static void free_resources();
};

typedef char TObjEneMe1Canadin_size[sizeof(TObjEneMe1Canadin) == 0x4CC ? 1 : -1];

extern "C" {
void TObjEneMe1CanadinLeader__sub_8009E258(u8 *arg0);
void TObjEneMe1CanadinLeader__sub_8009E27C(void *p);
u8 TObjEneMe1CanadinLeader__sub_8009E31C(u8 *arg0, s32 arg1);
void TObjEneMe1CanadinLeader__sub_8009E334(u8 *arg0);
void TObjEneMe1CanadinLeader__sub_8009E350(u8 *arg0);
int TObjEneMe1CanadinLeader__sub_8009E36C(void *p);
void TObjEneMe1CanadinLeader__sub_8009E4AC(u8 *arg0, s32 arg1);
void TObjEneMe1Canadin__sub_8009BFF8(u8 *arg0, s32 arg1);
void TObjEneMe1Canadin__sub_8009C178(u8 *arg0, s32 arg1);
void TObjEneMe1Canadin__sub_8009C2EC(u8 *arg0, s32 arg1);
void TObjEneMe1Canadin__sub_8009C510(u8 *arg0, s32 arg1);
void TObjEneMe1Canadin__sub_8009C91C(void *arg0, s32 arg1);
void TObjEneMe1Canadin__sub_8009D320(void *arg0, s32 arg1);
void TObjEneMe1Canadin__sub_8009DE90(void *argv0, s32 arg1);
s32 TObjEneMe1Canadin__sub_8009E76C(u8 *arg0);
void TObjEneMe1Canadin__sub_8009E930(u8 *arg0);
void TObjEneMe1Canadin__sub_8009E948(u8 *arg0);
void update_hover_position__17TObjEneMe1CanadinFf(u8 *arg0, f32 height);
void approach_hover_y__17TObjEneMe1CanadinFf(u8 *arg0, f32 farg0);
void advance_state_5_to_4__17TObjEneMe1CanadinFv(void *arg0);
void calc_move_vector__17TObjEneMe1CanadinFP3Vec(s32 actor, void *arg1);
void fn_8009BD00(void);
void fn_8009E1D4(u8 *arg0, s32 arg1);
void fn_8009E2DC(u8 *arg0);
s32 fn_8009E300(u8 *arg0);
void fn_8009E378(void *arg0);
void noop__17TObjEneMe1CanadinFv(void);
}

#endif
