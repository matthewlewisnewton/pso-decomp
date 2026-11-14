#include "types.h"
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/boss/TUnk_804E4B3C.h"
#include "pso/TMainTask.h"
#include "pso/boss/TObjBoss7Dust.h"
#include <dolphin/mtx/GeoTypes.h>

#include <stddef.h>
#include "pso/boss/TObjBoss2Tunnel.h"
#include "pso/item/TItemEffOrgaFlowShot.h"

extern "C" {
u32 boss2_tunnel_state_flags;
}

extern "C" {
s32 fn_802F1FB0(void *, TObject *, s32, f32, Vec *);
extern u32 boss2_tunnel_state_flags;
void TObjBoss2Tunnel__sub_802F2278(void);
s32 TObjBoss2Tunnel__sub_802F22F4(void);
extern const f32 lbl_805DEC68;
extern const f32 lbl_805DEC98;
extern const f32 lbl_805DEC9C;
extern const f32 lbl_805DECA8;
extern const f32 lbl_805DECB8;
extern const f32 lbl_805DECBC;
extern const f32 lbl_805DECC0;
extern const f32 lbl_805DECC4;
extern const f32 lbl_805DECC8;
extern u8 lbl_804E4A44[];
extern const f32 lbl_805DECB4;
extern const f32 lbl_805DECFC;
f32 fabs_float(f32);
extern const f32 lbl_805DECF8;
extern const f32 lbl_805DED00;
extern const f32 lbl_805DED04;
extern const f32 lbl_805DED08;
extern s32 lbl_804E4B3C[];
void TObjBoss2Tunnel__sub_802F2C4C(void);
void TObjBoss2Tunnel__sub_802F2C50(void);
void TObjBoss2Tunnel__sub_802F2C84(void);
void TObjBoss2Tunnel__sub_802F22DC(void);
void TObjBoss2Tunnel__sub_802F22C4(void);
s32 query_teammate_state__9TObjEneDDFv();
void __dt__7TObjectFv(void *, int);
void draw_particle_effect(void *a0);
void draw_tunnel_segment(TObject *segment);
void fn_802F1DAC(TObject *segment);
void fn_802F1E54(TObject *segment);
s32 is_split_screen();
s32 get_current_floor();
s32 is_room_enemy_set_cleared(s32, int);
u32 __ct__7TObjectFP7TObject(void *, void *);
s32 TObjBoss7RaftSplash__ct(void *, void *, void *, void *, void *);
s32 TObjBoss2Tunnel__sub_802F1AE0(void *, TObject *, int);
TObject *TObjBoss7TunnelCol__ct(void *, TObject *);

extern u8 TObjBoss2Tunnel__raft_splash_offset_table[];
extern const f32 lbl_805DED0C;
extern const f32 lbl_805DED10;
TUnk_804E4B3C *TObjBoss2Tunnel__sub_802F2A2C(TUnk_804E4B3C *self, TObject *parent);
f32 rand_signed_unit();
s32 rand();
s32 TObjBoss2Tunnel__sub_802F2070(void);

}
extern const f32 lbl_805DECAC, lbl_805DECB0;

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
s32 boss2_tunnel_spawn_timer_table_b[10] = {
    1, 1, 3, 4, 3, 3, 3, 3, 3, 3,
};
u8 lbl_804E4A44[0x18] = {
    0x42, 0x9C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0xA6, 0x00, 0x00,
    0xC2, 0x9C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0xA6, 0x00, 0x00,
};
}

void TObjBoss2Tunnel__sub_802F2C84(void) { boss2_tunnel_state_flags = 0; }

void TObjBoss2Tunnel__sub_802F2C50(void) {
    void *obj = TObject::operator new(0x94);
    if (obj != NULL) {
        TObjBoss2Tunnel__sub_802F2A2C((TUnk_804E4B3C *)obj, tl_04);
    }
}

void TObjBoss2Tunnel__sub_802F2C4C(void) {  }

TUnk_804E4B3C *TObjBoss2Tunnel__sub_802F2A2C(TUnk_804E4B3C *self, TObject *parent) {
    s32 i;
    void *p;
    TObject *col;
    __ct__7TObjectFP7TObject(self, parent);
    *(s32 **)((s8 *)self + 0x18) = lbl_804E4B3C;
    TObjBoss2Tunnel::reset_floats_pass(&self->motion);
    self->m_90 = new TObject(self);
    self->m_8c = new TObject(self);
    self->m_1c = 0;
    if (is_split_screen() == 0) {
        self->m_84 = lbl_805DED0C;
    } else {
        self->m_84 = lbl_805DED10;
    }
    TObjBoss2Tunnel::reset_floats(&self->motion);
    self->phase = 0;
    self->rate = lbl_805DEC98;
    self->value = lbl_805DEC9C;
    self->m_5c = lbl_805DEC9C;
    boss2_tunnel_state_flags = 0;
    self->m_58 = lbl_805DEC9C;
    self->m_70 = 0;
    self->m_78 = lbl_805DEC9C;
    self->m_7c = lbl_805DEC9C;
    self->m_80 = lbl_805DEC9C;
    self->m_74 = 0x1E;
    for (i = 0; i < 2; i++) {
        p = TObject::operator new(0x40);
        if (p != NULL) {
            TObjBoss7RaftSplash__ct(p, self, lbl_804E4A44 + i * 0xC, TObjBoss2Tunnel__raft_splash_offset_table + i * 0xC, &self->m_5c);
        }
    }
    p = TObject::operator new(0x2C);
    if (p != NULL) {
        TObjBoss2Tunnel__sub_802F1AE0(p, self->m_90, 0);
    }
    p = TObject::operator new(0x2C);
    if (p != NULL) {
        TObjBoss2Tunnel__sub_802F1AE0(p, self->m_90, 1);
    }
    p = TObject::operator new(0x2C);
    if (p != NULL) {
        TObjBoss2Tunnel__sub_802F1AE0(p, self->m_90, 2);
    }
    static s32 constructed = 1;
    if (is_room_enemy_set_cleared(get_current_floor(), 1) == 0) {
        self->spawn_segment_row_b();
        col = (TObject *)TObject::operator new(0xD8);
        if (col != NULL) {
            col = TObjBoss7TunnelCol__ct(col, self);
        }
        self->m_88 = col;
    } else {
        self->m_84 = lbl_805DED0C;
        self->spawn_segment_row_a();
        self->m_1c = 2;
        self->m_5c = lbl_805DEC9C;
        self->value = lbl_805DECB8;
        self->m_88 = 0;
        boss2_tunnel_state_flags |= 0x8000;
    }
    return self;
}

void *TUnk_804E4B3C::destroy(s16 arg1) {
    if (this != NULL) {
        *(s32 **)((s8 *)this + 0x18) = lbl_804E4B3C;
        if (this->m_88 != NULL) { this->m_88->queue_destruction(); }
        TObjBoss2Tunnel::dt(&motion, (s16)(-1));
        __dt__7TObjectFv(this, 0);
        if (arg1 > 0) {
            TObject::operator delete(this);
        }
    }
    return this;
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

void TUnk_804E4B3C::update_phase_motion() {
    f32 sp8;
    switch (phase) {
    case 0:
        if (check_both() != 0) {
            if (is_phase_active() != 0) {
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
        if (check_both() == 0) {
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
        if (check_both() == 0) {
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

void TUnk_804E4B3C::sub_802F273C() {}

void TUnk_804E4B3C::advance_effect_timer() {
    m_5c = m_5c + lbl_805DECFC;
    if (m_5c > lbl_805DEC68) {
        m_5c = lbl_805DEC68;
    }
}

#pragma push
// Porting exception (approved by Matt 2026-11-04 4:38 PM PT, see docs/porting-exceptions.md):
// the threshold has to land in f0 before m_58/m_5c. Remove this pragma when porting off MWCC.
#pragma opt_common_subs off
void TUnk_804E4B3C::update_spawn_timer(const s32 *table, s32 arg2, s32 arg3) {
    Vec stack;
    f32 temp_f1;
    m_58 = m_58 + m_5c;
    temp_f1 = m_58;
    if (temp_f1 >= lbl_805DECB4) {
        m_58 = temp_f1 - lbl_805DECB4;
        m_70 = m_70 + 1;
        if (m_70 == arg2) {
            if (arg3 != 0) {
                m_70 = arg2 - 1;
            } else {
                m_70 = 0;
            }
        }
        stack.x = value;
        stack.y = lbl_805DEC9C;
        stack.z = m_84 - m_58;
        spawn(table[m_70], &stack);
    }
}
#pragma pop

void TUnk_804E4B3C::update_dust_spawn() {
    Vec v;
    void *p;
    m_74 = m_74 - 1;
    if (m_74 <= 0) {
        v.x = 200.0f * rand_signed_unit();
        v.y = 90.0f * (3.0517578125e-05f * (f32)rand()) + 10.0f;
        v.z = 600.0f;
        p = TObject::operator new(0x30);
        if (p != NULL) {
            __ct__13TObjBoss7DustFv((u8 *)p, tl_05, &v);
        }
        m_74 = 0x1E;
    }
}

void TUnk_804E4B3C::init_effect() {
    advance_effect_timer();
    update_spawn_timer(boss2_tunnel_spawn_timer_table, 0x1F, 0);
    if (boss2_tunnel_state_flags & 0x200) {
        boss2_tunnel_state_flags &= 0xFFFFFDFF;
        m_1c = 1;
        m_70 = 0;
    }
    update_dust_spawn();
}

void TUnk_804E4B3C::sub_802F2400() {
    f32 temp_f1;
    TObject *col;
    update_spawn_timer(boss2_tunnel_spawn_timer_table_b, 0xA, 1);
    if (boss2_tunnel_state_flags & 8) {
        temp_f1 = m_80;
        if (temp_f1 < lbl_805DEC98) {
            m_1c = 2;
            m_5c = lbl_805DEC9C;
            value = lbl_805DECB8;
            col = m_88;
            if (col != NULL) {
                col->queue_destruction();
                m_88 = NULL;
            }
            boss2_tunnel_state_flags |= 0x8000;
            return;
        }
        if (temp_f1 < lbl_805DECBC) {
            TItemEffOrgaFlowShot::approach_value(&m_5c, lbl_805DECC0, lbl_805DECC4 * lbl_805DEC68);
            TItemEffOrgaFlowShot::approach_value(&value, lbl_805DECC8, lbl_805DECB8);
            return;
        }
        if (temp_f1 < 200.0f) {
            TItemEffOrgaFlowShot::approach_value(&m_5c, 0.04f, 0.2f * lbl_805DEC68);
            TItemEffOrgaFlowShot::approach_value(&value, lbl_805DECC8, -30.000002f);
            return;
        }
        if (temp_f1 < lbl_805DECA8) {
            TItemEffOrgaFlowShot::approach_value(&m_5c, 0.06f, 0.3f * lbl_805DEC68);
            TItemEffOrgaFlowShot::approach_value(&value, lbl_805DECC8, -15.000001f);
        }
    }
}

void TUnk_804E4B3C::sub_802F23FC() {}

void TUnk_804E4B3C::render() {
    TObject *n;
    if (query_teammate_state__9TObjEneDDFv() == 0) {
        for (n = m_90->m_down; n != NULL; n = n->m_next) {
            draw_particle_effect(n);
        }
        for (n = m_8c->m_down; n != NULL; n = n->m_next) {
            fn_802F1E54(n);
        }
        for (n = m_8c->m_down; n != NULL; n = n->m_next) {
            fn_802F1DAC(n);
        }
        for (n = m_8c->m_down; n != NULL; n = n->m_next) {
            draw_tunnel_segment(n);
        }
    }
}

s32 TUnk_804E4B3C::check_both() {
    s32 temp_r31;
    s32 temp_r3;
    temp_r31 = TObjBoss2Tunnel__sub_802F22F4();
    temp_r3 = is_phase_active();
    return temp_r3 | temp_r31;
}

s32 TUnk_804E4B3C::is_phase_active() {
    return (boss2_tunnel_state_flags >> 0xCU) & 1;
}

s32 TObjBoss2Tunnel__sub_802F22F4(void) {
    return (boss2_tunnel_state_flags >> 0xDU) & 1;
}

void TObjBoss2Tunnel__sub_802F22DC(void) {
    boss2_tunnel_state_flags |= 0x1000;
    boss2_tunnel_state_flags &= ~0x2000;
}

void TObjBoss2Tunnel__sub_802F22C4(void) {
    boss2_tunnel_state_flags |= 0x2000;
    boss2_tunnel_state_flags &= ~0x1000;
}

void TObjBoss2Tunnel::clear_flags_0x3000() { boss2_tunnel_state_flags &= 0xffffcfff; }

void TObjBoss2Tunnel::set_flag_0x200() { boss2_tunnel_state_flags |= 0x200; TObjBoss2Tunnel::clear_flags_0x3000(); }

void TObjBoss2Tunnel__sub_802F2278(void) { boss2_tunnel_state_flags |= 0x8; }

void TUnk_804E4B3C::spawn(s32 kind, Vec *position) {
    void *new_obj = TObject::operator new(0x78);
    if (new_obj != NULL) {
        fn_802F1FB0(new_obj, this->m_8c, kind, this->m_84, position);
    }
}

void TUnk_804E4B3C::spawn_segment_row_b() {
    Vec position;
    position.x = value;
    position.y = lbl_805DEC9C;
    for (position.z = m_84; position.z > -m_84; position.z -= lbl_805DECB4) {
        if (lbl_805DECAC > position.z && position.z > lbl_805DECB0) {
            spawn(0, &position);
        } else {
            spawn(2, &position);
        }
    }
}

void TUnk_804E4B3C::spawn_segment_row_a() {
    Vec position;
    position.x = value;
    position.y = lbl_805DEC9C;
    for (position.z = m_84; position.z > -m_84; position.z -= lbl_805DECB4) {
        if (lbl_805DECAC > position.z && position.z > lbl_805DECB0) {
            spawn(4, &position);
        } else {
            spawn(3, &position);
        }
    }
}

extern "C" {
s32 TObjBoss2Tunnel__sub_802F2070(void) {
    return (boss2_tunnel_state_flags >> 0xFU) & 1;
}
}
