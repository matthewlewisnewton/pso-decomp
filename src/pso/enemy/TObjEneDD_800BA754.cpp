#include "types.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/player/TObjPlayer.h"

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
    this->vfunc_88();
    ((TObjPlayer *)this)->check_object_collisions();
    check_enemy_body_collisions(this);
}

void TObjEneDD::vfunc_88() {  }
