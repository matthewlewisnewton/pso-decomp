#include "types.h"
#include "pso/object/TObjMotion.h"
#include "pso/boss/TBoss7Crawfish.h"

struct Pair_80308F8C { void *a; s32 b; };

struct Craw_80308F8C {
    u8 pad0[0x38];
    u8 f38[0xA4 - 0x38];
    s32 *fA4;
    u8 padA8[0x326 - 0xA8];
    s16 state;
    u8 pad328[0x3A0 - 0x328];
    s32 *f3A0;
    s32 f3A4;
    Pair_80308F8C pairs[4];
    s32 f3C8;
    s32 f3CC;
};

extern "C" {
void *create_particle_emitter(void *pos, s32 id);

extern const f32 lbl_805DF0F8;

void TBoss7Crawfish::update_attack_state() {
    s32 temp_r0;
    s32 temp_r3;
    void *temp_r4;

    temp_r0 = this->m_3c8 - 1;
    this->m_3c8 = temp_r0;
    if (temp_r0 < 0) {
        change_state(1);
    }
    if ((get_floor() == 2) && (is_passing_frame((f32)lbl_805DF0F8) != 0)) {
        temp_r4 = this->bodies;
        if (*(s32 *)((s8 *)temp_r4 + 0x18) & 0x02000000) {
            *(s32 *)((s8 *)temp_r4 + 0x18) &= ~0x02000000;
        }
        if (sub_80308AA8() != 0) {
            spawn_effect(0x3A80A);
        } else {
            spawn_effect(0x3A80B);
        }
    }
    if (*(s32 *)((s8 *)this->bodies + 0x18) & 0x02000000) {
        register_attack_hits();
    }
}
s32 TBoss7Crawfish__sub_80308ED8(void *object, void *displacement) {
    s32 moved;
    TBoss7Crawfish *o = (TBoss7Crawfish *)object;
    Vec proposed;

    // Callers borrow either Vec or a separate three-float struct at this ABI.
    // Address each live f32 member through the borrowed representation, rather
    // than treating the two complete vector types as interchangeable.
    f32 component = *(const f32 *)((const u8 *)displacement + 0);
    f32 dy = *(const f32 *)((const u8 *)displacement + 4);

    // Borrow position.x at its established offset. These scalar stages and
    // explicit f32 assignments preserve the original three-register lifetimes.
    f32 x = *(const f32 *)((const u8 *)object + 0x38);
    x += component;
    component = *(const f32 *)((const u8 *)displacement + 8);
    proposed.x = x;
    f32 y = o->position.y;
    y = (f32)(y + dy);
    proposed.y = y;
    f32 z = o->position.z;
    z = (f32)(z + component);
    proposed.z = z;
    if (o->vfunc_18((u8 *)&proposed) != NULL) {
        if (o->sub_80308688() != 0) {
            o->position.x = proposed.x;
            o->position.z = proposed.z;
            moved = 1;
        } else {
            moved = 0;
        }
    } else {
        moved = 0;
    }
    o->update_prev_position();
    return moved;
}

void TBoss7Crawfish::change_state(s32 state) {
    Craw_80308F8C *o = (Craw_80308F8C *)this;
    s32 i;
    o->state = state;
    o->fA4[6] |= 0x02000000;
    switch (o->state) {
    case 0:
        o->f3C8 = o->f3A0[6] - 10;
        break;
    case 1:
        break;
    case 2:
        ((TBoss7Crawfish *)o)->set_anim_timer(0);
        for (i = 0; i < 4; i++) {
            o->pairs[i].a = 0;
            o->pairs[i].b = 0;
        }
        o->f3A4 = 0;
        ((TBoss7Crawfish *)o)->free_child();
        o->f3CC = (s32)create_particle_emitter(o->f38, 0x20B);
        break;
    case 3:
        ((TBoss7Crawfish *)o)->set_anim_timer(4);
        break;
    case 4:
        ((TBoss7Crawfish *)o)->spawn_effect(0x3990E);
        ((TBoss7Crawfish *)o)->set_anim_timer(1);
        break;
    case 5:
        break;
    }
}

}
