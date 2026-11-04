#include "types.h"
#include "pso/boss/TUnk_804E4B3C.h"
#include "pso/boss/TunnelSceneController.h"

#include <stddef.h>
#include "pso/boss/TObjBoss2Tunnel.h"
#include "pso/item/TItemEffOrgaFlowShot.h"
struct RecoveredGlobal_802F2400_lbl_804E4A1C {
    s32 value;
    u8 remaining[0x24];
};

struct Stack_802F2664 {
    f32 sp8;
    f32 spC;
    f32 sp10;
};

struct Nd_802F2348 { u8 pad[0xC]; Nd_802F2348 *next; };

struct Li_802F2348 { u8 pad[0x14]; Nd_802F2348 *head; };

struct Vec_802F25AC { f32 x, y, z; };

extern "C" {
u32 __nw__7TObjectFUl(s32);
s32 fn_802F1FB0(void *, s32, s32, f32, s32);
void spawn__13TUnk_804E4B3CFll(void *arg0, s32 arg1, s32 arg2);
extern u32 boss2_tunnel_state_flags;
void TObjBoss2Tunnel__sub_802F2278(void);
s32 TObjBoss2Tunnel__sub_802F22F4(void);
void queue_destruction__7TObjectFv(void *arg0);
extern const f32 lbl_805DEC68;
extern const f32 lbl_805DEC98;
extern const f32 lbl_805DEC9C;
extern const f32 lbl_805DECA8;
extern const f32 lbl_805DECB8;
extern const f32 lbl_805DECBC;
extern const f32 lbl_805DECC0;
extern const f32 lbl_805DECC4;
extern const f32 lbl_805DECC8;
extern const f32 lbl_805DECCC;
extern const f32 lbl_805DECD0;
extern const f32 lbl_805DECD4;
extern const f32 lbl_805DECD8;
extern const f32 lbl_805DECDC;
extern const f32 lbl_805DECE0;
extern const f32 lbl_805DECE4;
extern RecoveredGlobal_802F2400_lbl_804E4A1C boss2_tunnel_spawn_timer_table_b;
extern s32 boss2_tunnel_spawn_timer_table[];
extern u8 lbl_804E4A44[];
extern const f32 lbl_805DECB4;
extern const f32 lbl_805DECFC;
f32 fabs_float(f32);
extern const f32 lbl_805DECF8;
extern const f32 lbl_805DED00;
extern const f32 lbl_805DED04;
extern const f32 lbl_805DED08;
void __dl__7TObjectFPv(void *);
void __dt__7TObjectFv(void *, int);
extern s32 lbl_804E4B3C[];
void TObjBoss2Tunnel__sub_802F2C4C(void);
extern s32 tl_04;
void TObjBoss2Tunnel__sub_802F2C50(void);
void TObjBoss2Tunnel__sub_802F2C84(void);
void TObjBoss2Tunnel__sub_802F22DC(void);
void TObjBoss2Tunnel__sub_802F22C4(void);
s32 query_teammate_state__9TObjEneDDFv();
void draw_particle_effect(void *a0);
void draw_tunnel_segment(u8 *arg0);
void fn_802F1DAC(u8 *arg0);
void fn_802F1E54(u8 *arg0);
s32 is_split_screen();
s32 get_current_floor();
s32 is_room_enemy_set_cleared(s32, int);
u32 __ct__7TObjectFP7TObject(void *, void *);
s32 TObjBoss7RaftSplash__ct(void *, void *, void *, void *, void *);
s32 TObjBoss2Tunnel__sub_802F1AE0(void *, u32, int);
u32 TObjBoss7TunnelCol__ct(void *, void *);

extern u8 TObjBoss2Tunnel__raft_splash_offset_table[];
s32 lbl_805D696C;
s8 lbl_805D6970;
extern const f32 lbl_805DED0C;
extern const f32 lbl_805DED10;
void *TObjBoss2Tunnel__sub_802F2A2C(void *arg0p, s32 parent);
f32 rand_signed_unit();
u8 *__ct__13TObjBoss7DustFv(u8 *arg0, s32 arg1, s32 arg2);
s32 rand();
extern s32 tl_05;
s32 TObjBoss2Tunnel__sub_802F2070(void);

s32 TObjBoss2Tunnel__sub_802F2070(void) {
    return ((u32) boss2_tunnel_state_flags >> 0xFU) & 1;
}
}
struct TunnelVector3 { f32 x,y,z; };
 extern const f32 lbl_805DEC9C,lbl_805DECAC,lbl_805DECB0,lbl_805DECB4; void TunnelSceneController::spawn_segment_row_a() {
    TunnelVector3 position;
    position.x=segment_x;
    position.y=lbl_805DEC9C;
    for (position.z=half_length;position.z > -half_length;position.z-=lbl_805DECB4) {
        if (lbl_805DECAC > position.z && position.z > lbl_805DECB0) {
            ((void (*)(void*,s32,TunnelVector3*))spawn__13TUnk_804E4B3CFll)(this,4,&position);
        } else {
            ((void (*)(void*,s32,TunnelVector3*))spawn__13TUnk_804E4B3CFll)(this,3,&position);
        }
    }
}

void TunnelSceneController::spawn_segment_row_b() {
    TunnelVector3 position;
    position.x=segment_x;
    position.y=lbl_805DEC9C;
    for (position.z=half_length;position.z > -half_length;position.z-=lbl_805DECB4) {
        if (lbl_805DECAC > position.z && position.z > lbl_805DECB0) {
            ((void (*)(void*,s32,TunnelVector3*))spawn__13TUnk_804E4B3CFll)(this,0,&position);
        } else {
            ((void (*)(void*,s32,TunnelVector3*))spawn__13TUnk_804E4B3CFll)(this,2,&position);
        }
    }
}

void TUnk_804E4B3C::spawn(s32 arg1, s32 arg2) {
    void *new_obj = (void *) __nw__7TObjectFUl(0x78);
    if ((u32) new_obj != 0U) {
        fn_802F1FB0(new_obj, (s32)this->m_8c, arg1, this->m_84, arg2);
    }
}
void TObjBoss2Tunnel__sub_802F2278(void) { (*(int *)&boss2_tunnel_state_flags) = ((*(int *)&boss2_tunnel_state_flags) | 0x8); }
void TObjBoss2Tunnel::set_flag_0x200() { (*(int *)&boss2_tunnel_state_flags) = ((*(int *)&boss2_tunnel_state_flags) | 0x200); TObjBoss2Tunnel::clear_flags_0x3000(); }
void TObjBoss2Tunnel::clear_flags_0x3000() { (*(int *)&boss2_tunnel_state_flags) = ((*(int *)&boss2_tunnel_state_flags) & 0xffffcfff); }

void TObjBoss2Tunnel__sub_802F22C4(void) {
    boss2_tunnel_state_flags |= 0x2000;
    boss2_tunnel_state_flags &= ~0x1000;
}

void TObjBoss2Tunnel__sub_802F22DC(void) {
    boss2_tunnel_state_flags |= 0x1000;
    boss2_tunnel_state_flags &= ~0x2000;
}

s32 TObjBoss2Tunnel__sub_802F22F4(void) {
    return ((u32) boss2_tunnel_state_flags >> 0xDU) & 1;
}
s32 TObjBoss2Tunnel::is_phase_active(s32 _w0) {
    return ((u32) boss2_tunnel_state_flags >> 0xCU) & 1;
}
s32 TObjBoss2Tunnel::check_both(s32 arg0) {
    s32 temp_r31;
    s32 temp_r3;
    temp_r31 = TObjBoss2Tunnel__sub_802F22F4();
    temp_r3 = TObjBoss2Tunnel::is_phase_active(arg0);
    return temp_r3 | temp_r31;
}

void TUnk_804E4B3C::render() {
    u8 *arg0 = (u8 *)this;
    Nd_802F2348 *n;
    if (query_teammate_state__9TObjEneDDFv() == 0) {
        for (n = (*(Li_802F2348 **)&this->m_90)->head; n != 0; n = n->next) {
            draw_particle_effect(n);
        }
        for (n = (*(Li_802F2348 * *)&this->m_8c)->head; n != 0; n = n->next) {
            fn_802F1E54((u8 *)n);
        }
        for (n = (*(Li_802F2348 * *)&this->m_8c)->head; n != 0; n = n->next) {
            fn_802F1DAC((u8 *)n);
        }
        for (n = (*(Li_802F2348 * *)&this->m_8c)->head; n != 0; n = n->next) {
            draw_tunnel_segment((u8 *)n);
        }
    }
}

void TUnk_804E4B3C::sub_802F23FC() {}
void TUnk_804E4B3C::sub_802F2400() {
    f32 temp_f1;
    u32 temp_r3;
    update_spawn_timer((s32)&boss2_tunnel_spawn_timer_table_b.value, 0xA, 1);
    if ((*(s32 *)&boss2_tunnel_state_flags) & 8) {
        temp_f1 = m_80;
        if (temp_f1 < lbl_805DEC98) {
            m_1c = 2;
            m_5c = lbl_805DEC9C;
            value = lbl_805DECB8;
            temp_r3 = (u32)m_88;
            if (temp_r3 != 0U) {
                queue_destruction__7TObjectFv((void *)temp_r3);
                m_88 = 0;
            }
            (*(s32 *)&boss2_tunnel_state_flags) |= 0x8000;
            return;
        }
        if (temp_f1 < lbl_805DECBC) {
            TItemEffOrgaFlowShot::approach_value(&m_5c, (f32)lbl_805DECC0, (f32)((f32) (lbl_805DECC4 * lbl_805DEC68)));
            TItemEffOrgaFlowShot::approach_value(&value, (f32)lbl_805DECC8, (f32)lbl_805DECB8);
            return;
        }
        if (temp_f1 < lbl_805DECCC) {
            TItemEffOrgaFlowShot::approach_value(&m_5c, (f32)lbl_805DECD0, (f32)((f32) (lbl_805DECD4 * lbl_805DEC68)));
            TItemEffOrgaFlowShot::approach_value(&value, (f32)lbl_805DECC8, (f32)lbl_805DECD8);
            return;
        }
        if (temp_f1 < lbl_805DECA8) {
            TItemEffOrgaFlowShot::approach_value(&m_5c, (f32)lbl_805DECDC, (f32)((f32) (lbl_805DECE0 * lbl_805DEC68)));
            TItemEffOrgaFlowShot::approach_value(&value, (f32)lbl_805DECC8, (f32)lbl_805DECE4);
        }
    }
}
void TUnk_804E4B3C::init_effect() {
    advance_effect_timer();
    update_spawn_timer((s32)boss2_tunnel_spawn_timer_table, 0x1F, 0);
    if ((*(s32 *)&boss2_tunnel_state_flags) & 0x200) {
        (*(s32 *)&boss2_tunnel_state_flags) &= 0xFFFFFDFF;
        m_1c = 1;
        m_70 = 0;
    }
    update_dust_spawn();
}

void TUnk_804E4B3C::update_dust_spawn() {
    u8 *arg0 = (u8 *)this;
    Vec_802F25AC v;
    u32 p;
    *(s32 *)((s8 *)arg0 + 0x74) = *(s32 *)((s8 *)arg0 + 0x74) - 1;
    if (*(s32 *)((s8 *)arg0 + 0x74) <= 0) {
        v.x = 200.0f * rand_signed_unit();
        v.y = 90.0f * (3.0517578125e-05f * (f32)rand()) + 10.0f;
        v.z = 600.0f;
        p = __nw__7TObjectFUl(0x30);
        if (p != 0U) {
            __ct__13TObjBoss7DustFv((u8 *)p, (s32)tl_05, (s32)&v);
        }
        *(s32 *)((s8 *)arg0 + 0x74) = 0x1E;
    }
}

#pragma push
#pragma opt_common_subs off
void TUnk_804E4B3C::update_spawn_timer(s32 arg1, s32 arg2, s32 arg3) {
    u8 *arg0 = (u8 *)this;
    typedef char sp8_offset[(offsetof(Stack_802F2664, sp8) == 0x0) ? 1 : -1];
    typedef char spC_offset[(offsetof(Stack_802F2664, spC) == 0x4) ? 1 : -1];
    typedef char sp10_offset[(offsetof(Stack_802F2664, sp10) == 0x8) ? 1 : -1];
    Stack_802F2664 stack;
    f32 temp_f1;
    *(f32 *)((s8 *)arg0 + 0x58) = (f32) (*(f32 *)((s8 *)arg0 + 0x58) + *(f32 *)((s8 *)arg0 + 0x5C));
    temp_f1 = *(f32 *)((s8 *)arg0 + 0x58);
    if (temp_f1 >= lbl_805DECB4) {
        *(f32 *)((s8 *)arg0 + 0x58) = (f32) (temp_f1 - lbl_805DECB4);
        *(s32 *)((s8 *)arg0 + 0x70) = (s32) (*(s32 *)((s8 *)arg0 + 0x70) + 1);
        if ((s32) *(s32 *)((s8 *)arg0 + 0x70) == arg2) {
            if (arg3 != 0) {
                *(s32 *)((s8 *)arg0 + 0x70) = (arg2 - 1);
            } else {
                *(s32 *)((s8 *)arg0 + 0x70) = 0;
            }
        }
        stack.sp8 = *(f32 *)((s8 *)arg0 + 0x54);
        stack.spC = lbl_805DEC9C;
        stack.sp10 = *(f32 *)((s8 *)arg0 + 0x84) - *(f32 *)((s8 *)arg0 + 0x58);
        spawn__13TUnk_804E4B3CFll(arg0, *(s32 *)((s8 *)(arg1 + (*(s32 *)((s8 *)arg0 + 0x70) * 4)) + 0), (s32) &stack.sp8);
    }
}
#pragma pop

void TUnk_804E4B3C::advance_effect_timer() {
    *(f32 *)((s8 *)this + 0x5C) = (f32) (*(f32 *)((s8 *)this + 0x5C) + lbl_805DECFC);
    if (*(f32 *)((s8 *)this + 0x5C) > lbl_805DEC68) {
        *(f32 *)((s8 *)this + 0x5C) = (f32) lbl_805DEC68;
    }
}
void TUnk_804E4B3C::sub_802F273C() {}
void TUnk_804E4B3C::update_phase_motion() {
    f32 sp8;
    switch (phase) {
    case 0:
        if (TObjBoss2Tunnel::check_both((s32)this) != 0) {
            if (TObjBoss2Tunnel::is_phase_active((s32)this) != 0) {
                rate = lbl_805DECC8;
            } else {
                rate = lbl_805DEC98;
            }
            phase = 1;
            init_piecewise_curve(&motion, lbl_805DECC4, lbl_805DED00, lbl_805DED04, lbl_805DED08, lbl_805DECF8);
            value = lbl_805DEC9C;
        }
        break;
    case 1:
        if (TObjBoss2Tunnel::check_both((s32)this) == 0) {
            phase = 3;
            sp8 = fabs_float(value);
            init_piecewise_curve(&motion, lbl_805DECC4, lbl_805DED00, value, -TObjBoss2Tunnel::update_position(&motion), lbl_805DECF8);
            return;
        }
        if (TObjBoss2Tunnel::advance_phase(&motion, &sp8) != 0) {
            phase = 2;
        }
        value = sp8 * rate;
        return;
    case 2:
        if (TObjBoss2Tunnel::check_both((s32)this) == 0) {
            phase = 3;
            init_piecewise_curve(&motion, lbl_805DECC4, lbl_805DED00, lbl_805DED04, lbl_805DEC9C, lbl_805DECF8);
            return;
        }
        break;
    case 3:
        if (TObjBoss2Tunnel::advance_phase(&motion, &sp8) != 0) {
            value = lbl_805DEC9C;
            phase = 0;
            return;
        }
        value = rate * (lbl_805DED04 - sp8);
        break;
    }
}

extern "C" {
extern const char lbl_804743B0[];
extern const char lbl_804743BC[];
extern const char lbl_804743CC[];
extern const char lbl_804743D8[];
extern const char lbl_804743E4[];
struct Boss2EffectName {
    s32 count;
    const char *name;
};
Boss2EffectName boss2_tunnel_effect_name_table[5] = {
    {3, lbl_804743B0},
    {4, lbl_804743BC},
    {3, lbl_804743CC},
    {3, lbl_804743D8},
    {4, lbl_804743E4},
};
s32 boss2_tunnel_spawn_timer_table[31] = {
    2, 1, 2, 1, 1, 2, 2, 1, 2, 1, 2, 2, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2, 1,
};
RecoveredGlobal_802F2400_lbl_804E4A1C boss2_tunnel_spawn_timer_table_b = {
    1,
    {
        0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04,
        0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03,
        0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03,
    },
};
u8 lbl_804E4A44[0x18] = {
    0x42, 0x9C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0xA6, 0x00, 0x00,
    0xC2, 0x9C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0xA6, 0x00, 0x00,
};
}

void TUnk_804E4B3C::run_task() {
    update_phase_motion();
    static void (TUnk_804E4B3C::*handlers[3])() = {
        &TUnk_804E4B3C::init_effect,
        &TUnk_804E4B3C::sub_802F2400,
        &TUnk_804E4B3C::sub_802F23FC,
    };
    void (TUnk_804E4B3C::*handler)() = handlers[m_1c];
    (this->*handler)();
    sub_802F273C();
}

extern "C" {
static u8 boss2_tunnel_effect_tail[0x30] = {
    0x41, 0xD0, 0x00, 0x00, 0xC1, 0x98, 0x00, 0x00, 0x42, 0x78, 0x00, 0x00,
    0xC1, 0xD0, 0x00, 0x00, 0xC1, 0x98, 0x00, 0x00, 0x42, 0x78, 0x00, 0x00,
    0x41, 0xD0, 0x00, 0x00, 0xC1, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xC1, 0xD0, 0x00, 0x00, 0xC1, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
}

void *TUnk_804E4B3C::destroy(s16 arg1) {
    if (this != NULL) {
        *(s32 **)((s8 *)this + 0x18) = lbl_804E4B3C;
        if (this->m_88 != NULL) { queue_destruction__7TObjectFv(this->m_88); }
        TObjBoss2Tunnel::dt((s32)&motion, (s16)(-1));
        __dt__7TObjectFv(this, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(this);
        }
    }
    return this;
}

#pragma push
#pragma opt_common_subs off
#pragma opt_loop_invariants off
#define arg0 ((u8 *)arg0p)
void *TObjBoss2Tunnel__sub_802F2A2C(void *arg0p, s32 parent) {
    s32 i;
    u32 p;
    __ct__7TObjectFP7TObject(arg0, (void *) parent);
    *(s32 **)((s8 *)arg0 + 0x18) = lbl_804E4B3C;
    TObjBoss2Tunnel::reset_floats((s32)&((TUnk_804E4B3C *)arg0p)->motion);
    p = __nw__7TObjectFUl(0x1C);
    if (p != 0) {
        p = __ct__7TObjectFP7TObject((void *) p, arg0);
    }
    ((TUnk_804E4B3C *)arg0p)->m_90 = (void *)p;
    p = __nw__7TObjectFUl(0x1C);
    if (p != 0) {
        p = __ct__7TObjectFP7TObject((void *) p, arg0);
    }
    ((TUnk_804E4B3C *)arg0p)->m_8c = (void *)p;
    ((TUnk_804E4B3C *)arg0p)->m_1c = 0;
    if (is_split_screen() == 0) {
        ((TUnk_804E4B3C *)arg0p)->m_84 = lbl_805DED0C;
    } else {
        ((TUnk_804E4B3C *)arg0p)->m_84 = lbl_805DED10;
    }
    TObjBoss2Tunnel::reset_floats(&((TUnk_804E4B3C *)arg0p)->motion);
    ((TUnk_804E4B3C *)arg0p)->phase = 0;
    ((TUnk_804E4B3C *)arg0p)->rate = lbl_805DEC98;
    ((TUnk_804E4B3C *)arg0p)->value = lbl_805DEC9C;
    *(f32 *)((s8 *)arg0 + 0x5C) = lbl_805DEC9C;
    boss2_tunnel_state_flags = 0;
    *(f32 *)((s8 *)arg0 + 0x58) = lbl_805DEC9C;
    *(s32 *)((s8 *)arg0 + 0x70) = 0;
    *(f32 *)((s8 *)arg0 + 0x78) = lbl_805DEC9C;
    *(f32 *)((s8 *)arg0 + 0x7C) = lbl_805DEC9C;
    *(f32 *)((s8 *)arg0 + 0x80) = lbl_805DEC9C;
    *(s32 *)((s8 *)arg0 + 0x74) = 0x1E;
    for (i = 0; i < 2; i++) {
        p = __nw__7TObjectFUl(0x40);
        if (p != 0) {
            TObjBoss7RaftSplash__ct((void *) p, arg0, lbl_804E4A44 + i * 0xC, TObjBoss2Tunnel__raft_splash_offset_table + i * 0xC, arg0 + 0x5C);
        }
    }
    p = __nw__7TObjectFUl(0x2C);
    if (p != 0) {
        TObjBoss2Tunnel__sub_802F1AE0((void *) p, (u32)((TUnk_804E4B3C *)arg0p)->m_90, 0);
    }
    p = __nw__7TObjectFUl(0x2C);
    if (p != 0) {
        TObjBoss2Tunnel__sub_802F1AE0((void *) p, (u32)((TUnk_804E4B3C *)arg0p)->m_90, 1);
    }
    p = __nw__7TObjectFUl(0x2C);
    if (p != 0) {
        TObjBoss2Tunnel__sub_802F1AE0((void *) p, (u32)((TUnk_804E4B3C *)arg0p)->m_90, 2);
    }
    if (lbl_805D6970 == 0) {
        lbl_805D696C = 1;
        lbl_805D6970 = 1;
    }
    if (is_room_enemy_set_cleared(get_current_floor(), 1) == 0) {
        ((TunnelSceneController*)arg0)->spawn_segment_row_b();
        p = __nw__7TObjectFUl(0xD8);
        if (p != 0) {
            p = TObjBoss7TunnelCol__ct((void *) p, arg0);
        }
        ((TUnk_804E4B3C *)arg0p)->m_88 = (void *)p;
    } else {
        ((TUnk_804E4B3C *)arg0p)->m_84 = lbl_805DED0C;
        ((TunnelSceneController*)arg0)->spawn_segment_row_a();
        ((TUnk_804E4B3C *)arg0p)->m_1c = 2;
        *(f32 *)((s8 *)arg0 + 0x5C) = lbl_805DEC9C;
        ((TUnk_804E4B3C *)arg0p)->value = lbl_805DECB8;
        ((TUnk_804E4B3C *)arg0p)->m_88 = 0;
        boss2_tunnel_state_flags |= 0x8000;
    }
    return arg0;
}
#undef arg0
#pragma pop

void TObjBoss2Tunnel__sub_802F2C4C(void) {  }
void TObjBoss2Tunnel__sub_802F2C50(void) {
    void* obj = ((void*)__nw__7TObjectFUl(0x94));
    if (obj != 0) {
        TObjBoss2Tunnel__sub_802F2A2C(obj, tl_04);
    }
}
void TObjBoss2Tunnel__sub_802F2C84(void) { (*(int *)&boss2_tunnel_state_flags) = 0; }

typedef char RecoveredGlobal_802F2400_lbl_804E4A1C_size[sizeof(RecoveredGlobal_802F2400_lbl_804E4A1C) == 0x28 ? 1 : -1];
