#ifndef PSO_ENEMY_TOBJENEME1CANADIN_H
#define PSO_ENEMY_TOBJENEME1CANADIN_H

#include "types.h"
#include "pso/enemy/TObjEneDD_ST.h"
#include "pso/enemy/TUnk_80494938.h"
#include "pso/system/vector.h"
#include <stddef.h>

struct CanadinActionParameters {
    s32 field_0;
    f32 field_4;
    f32 field_8;
    s32 field_c;
    s32 field_10;
};

struct CanadinMovementParameters {
    f32 field_0;
    f32 field_4;
    s32 field_8;
    s32 field_c[4];
};

struct CanadinParameters {
    f32 field_0;
    f32 field_4;
    f32 field_8;
    f32 field_c;
    f32 field_10;
    f32 field_14;
    s32 field_18;
    s32 field_1c;
    s32 field_20;
    s32 field_24;
    s32 field_28;
    s32 field_2c;
};

struct TObjEneMe1Canadin : public TObjEneDD_ST {
    TObjEneMe1Canadin(TObject *parent, TObjEneMe1Canadin *leader, Vec *spawn_position, s32 id, s32 index);
    TObjEneMe1Canadin(TObject *parent, void *set_data, s32 kind);
    virtual ~TObjEneMe1Canadin();
    virtual void dispatch_action(u32, s32);
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
    TObjEneMe1Canadin *m_3c0;
    s32 m_3c4;
    u32 m_3c8;
    TUnk_80494938 m_3cc;
    f32 m_3e8;
    f32 m_3ec;
    f32 m_3f0;
    f32 m_3f4;
    f32 hover_y;
    s32 m_3fc;
    s32 m_400;
    s32 m_404;
    TObject *m_408;
    s32 m_40c;
    s32 m_410;
    Vec m_414[7];
    CanadinParameters *m_468;
    s32 m_46c;
    s32 m_470;
    s32 m_474;
    s32 m_478;
    s32 m_47c;
    s32 m_480;
    f32 m_484;
    f32 m_488;
    f32 m_48c;
    Vec m_490;
    TObject *m_49c;
    TObject *m_4a0;
    NJS_ARGB m_4a4;
    u32 m_4b4;
    s32 m_4b8;
    s32 m_4bc;
    s32 m_4c0;
    s32 m_4c4;
    u16 m_4c8;
    void fn_8009BFF8(s32 arg1);
    void fn_8009C178(s32 arg1);
    void fn_8009C2EC(s32 arg1);
    void fn_8009C510(s32 arg1);
    void fn_8009C91C(s32 arg1);
    void fn_8009CC74(s32 arg1);
    void fn_8009D320(s32 arg1);
    void fn_8009DE90(s32 arg1);
    s32 fn_8009E76C();
    s32 fn_8009E860(f32 *out, f32 _w2);
    void fn_8009E930();
    void fn_8009E948();
    void update_hover_position(f32 height);
    void approach_hover_y(f32 target_y);
    void fn_8009E258();
    void fn_8009E27C();
    s32 fn_8009E31C(s32 arg1);
    void fn_8009E334();
    void fn_8009E350();
    int fn_8009E36C();
    void fn_8009E4AC(s32 arg1);
    void fn_8009E1D4(Vec *position);
    void fn_8009E2DC();
    TObjChara *fn_8009E300();
    void fn_8009E378();
    void advance_state_5_to_4();
    void fn_8009E6B0();
    void calc_move_vector(Vec *arg1);
    void set_flag3c8_bit40();
    void set_flag3c8_bit20();
    void set_flag3c8_bit8();
    void set_attack_flag();
    void set_leader_index(TObjChara *target, s32 index);
    void update_by_state(s32 arg1);
    void update_walk_animation(s32 arg1);
    void run_task(s32 arg1);
    void move(s32 arg1);
    void action(s32 arg1);
    void handle_state(s32 arg1);
    void update_fade_sequence();
    void pack_color_rgba();
    void reset_map_core(NJS_ARGB *color);
    s32 try_trigger_action();
    void advance_state_4_to_5();
    s32 check_target();
    void update_move();
    void update_angle();
    void update_hover_height();
    void set_target_speed_z();
    void update_position_with_offset();
    void update_by_field_0x354();
    void copy_pos();
    void run_task();
    void setup_enemy();
    static void *create(void *arg0);
};

typedef char TObjEneMe1Canadin_size[sizeof(TObjEneMe1Canadin) == 0x4CC ? 1 : -1];

typedef char CanadinTargetOffset[offsetof(TObjEneMe1Canadin, target) == 0x390 ? 1 : -1];
typedef char CanadinFadeOffset[offsetof(TObjEneMe1Canadin, m_3cc) == 0x3CC ? 1 : -1];
typedef char CanadinHistoryOffset[offsetof(TObjEneMe1Canadin, m_414) == 0x414 ? 1 : -1];
typedef char CanadinColorOffset[offsetof(TObjEneMe1Canadin, m_4b4) == 0x4B4 ? 1 : -1];

#endif
