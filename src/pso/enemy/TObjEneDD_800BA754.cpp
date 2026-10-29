#include "types.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/player/TObjPlayer.h"

struct Base_800BA8E8_800BA754 { char pad[0x18]; };
struct VObj_800BA8E8_800BA754 : Base_800BA8E8_800BA754 {
    virtual void m0();  virtual void m1();  virtual void m2();  virtual void m3();
    virtual void m4();  virtual void m5();  virtual void m6();  virtual void m7();
    virtual void m8();  virtual void m9();  virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
    virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27();
    virtual void m28(); virtual void m29(); virtual void m30(); virtual void m31();
    virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35();
    virtual void m36(); virtual void m37(); virtual void m38(); virtual void m39();
    virtual void m40(); virtual void m41(); virtual void m42(); virtual void m43();
    virtual void m44(); virtual void m45(); virtual void m46(); virtual void m47();
    virtual void m48(); virtual void m49(); virtual void m50(); virtual void m51();
    virtual void m52(); virtual void m53(); virtual void m54(); virtual void m55();
    virtual void m56(); virtual void m57(); virtual void m58(); virtual void m59();
    virtual void m60(); virtual void m61(); virtual void m62(); virtual void m63();
    virtual void m64(); virtual void m65(); virtual void m66(); virtual void m67();
    virtual void m68(); virtual void m69(); virtual void m70(); virtual void m71();
    virtual void m72(); virtual void m73(); virtual void m74(); virtual void m75();
    virtual void m76(); virtual void m77(); virtual void m78(); virtual void m79();
    virtual void m80(); virtual void m81(); virtual void m82(); virtual void m83();
    virtual void m84(); virtual void m85(); virtual void m86();
};

struct E_800BA8A8 { u8 pad[0x18]; u32 flags; u8 pad2[0x10]; };

struct O_800BA8A8 { u8 pad[0xa4]; E_800BA8A8 *entries; s32 count; };

extern "C" {
u32 is_player_entity_id(u16 arg0);
s32 *csnLookAt(s32 arg0, s32 arg1);
s32 is_alive__8TObjBaseFv(void *arg0);
int TObjEneDD__sub_800BA804(u16 arg0);
void check_enemy_body_collisions(void *arg0);
s32 all_parents_unqueued_for_destruction__7TObjectFv();

s32 TObjEneDD::is_target_unobstructed(s32 arg1) {
    s32 arg0 = (s32)this;
    if ((is_alive__8TObjBaseFv((void *)arg0) != 0) && (csnLookAt((arg1), (arg0 + 0x2FC)) == 0U)) {
        return 1;
    }
    return 0;
}

u8 TObjEneDD::is_valid_target() {
    int var_r31;

    var_r31 = 0;
    if ((this != NULL) && (all_parents_unqueued_for_destruction__7TObjectFv() != 0) && !(this->actorFlags & 0x06040800)) {
        var_r31 = 1;
    }
    return (u8)var_r31;
}

int TObjEneDD__sub_800BA804(u16 arg0) {
    u8 var_r3;
    var_r3 = 0;
    if ((arg0 >= 0x1000U) && (arg0 < 0x4000U)) {
        var_r3 = 1;
    }
    return var_r3;
}

u32 is_player_entity_id(u16 arg0) {
    return (u32)(arg0 - 0x1000) >> 0x1FU;
}
}
void set_collider_contact_low(u8 *arg0);
void set_collider_contact_high(u8 *arg0);
void update_collider_contact_by_height(u8 *arg0, f32 farg0);

void update_collider_contact_by_height(u8 *arg0, f32 farg0) {
    if (*(f32 *)((s8 *)arg0 + 4) >= farg0) {
        set_collider_contact_high(arg0);
        return;
    }
    set_collider_contact_low(arg0);
}

void set_collider_contact_low(u8 *arg0) {
    *(s32 *)((s8 *)arg0 + 0x18) = (s32) (*(s32 *)((s8 *)arg0 + 0x18) & 0xFFFFFFFB);
    *(s32 *)((s8 *)arg0 + 0x18) = (s32) (*(s32 *)((s8 *)arg0 + 0x18) | 2);
}

void set_collider_contact_high(u8 *arg0) {
    *(s32 *)((s8 *)arg0 + 0x18) = (s32) (*(s32 *)((s8 *)arg0 + 0x18) | 4);
    *(s32 *)((s8 *)arg0 + 0x18) = (s32) (*(s32 *)((s8 *)arg0 + 0x18) & 0xFFFFFFFD);
}

s32 TObjEneDD::vfunc_90() {
    O_800BA8A8 *self = (O_800BA8A8 *)this;
    s32 i;
    for (i = 0; i < self->count; i++) {
        if (self->entries[i].flags & 0x380000) {
            return 1;
        }
    }
    return 0;
}

void TObjEneDD::vfunc_89() {
    struct VObj_800BA8E8_800BA754 *o = (struct VObj_800BA8E8_800BA754 *)this;
    o->m86();
    ((TObjPlayer *)this)->check_object_collisions();
    check_enemy_body_collisions(this);
}

void TObjEneDD::vfunc_88() {  }
