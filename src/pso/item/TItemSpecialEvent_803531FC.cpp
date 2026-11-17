#include "types.h"
#include "pso/item/TItemSpecialEvent.h"

#include "pso/player/TObjPlayer.h"

extern "C" {
int send_nearby_player_ids(TObjPlayer *, f32);
s32 add_actor_hp(TObjPlayer *, s32);
s32 add_actor_tp(TObjPlayer *, s32);
s32 get_field_2b8__14TItemProShieldFv(TObjPlayer *);
s32 obj_getS16_2BA(TObjPlayer *);
}

void TItemSpecialEvent::send_obj_position_event(s32 arg1) {
    TObjPlayer *owner = this->owner;
    if (owner != NULL) {
        DirectAttackPayload attack;
        attack.kind = arg1;
        attack.power = 0.0f;
        owner->receive_direct_attack(owner, attack, NULL, -1, -1);
    }
}

void TItemSpecialEvent::sub_8035307C() { send_obj_position_event(18); }
void TItemSpecialEvent::sub_803530A0() { send_obj_position_event(17); }

void TItemSpecialEvent::sub_803530C4() {
    if (TObjPlayer::is_locally_controlled(this->owner) != 0) {
        this->owner->apply_shock_status();
    }
}

void TItemSpecialEvent::sub_80353110() { send_obj_position_event(16); }
void TItemSpecialEvent::sub_80353134() { send_obj_position_event(15); }
void TItemSpecialEvent::sub_80353158() {
    add_actor_hp(this->owner, get_field_2b8__14TItemProShieldFv(this->owner));
}
void TItemSpecialEvent::sub_80353194() {
    add_actor_tp(this->owner, obj_getS16_2BA(this->owner));
}

void TItemSpecialEvent::sub_803531D0() { send_nearby_player_ids(this->owner, 10000.0f); }

void TItemSpecialEvent::sub_803531F8() {  }

typedef void (TItemSpecialEvent::*Handler)();

// Technique index selects one of nine use-effect steps on this item. Each
// step only uses TObjPlayer *owner.
void TItemSpecialEvent::apply_use_effect() {
    Handler handlers[9] = {
        &TItemSpecialEvent::sub_803531F8,
        &TItemSpecialEvent::sub_803531D0,
        &TItemSpecialEvent::sub_80353194,
        &TItemSpecialEvent::sub_80353158,
        &TItemSpecialEvent::sub_80353134,
        &TItemSpecialEvent::sub_80353110,
        &TItemSpecialEvent::sub_803530C4,
        &TItemSpecialEvent::sub_803530A0,
        &TItemSpecialEvent::sub_8035307C,
    };
    u8 technique = get_technique();
    if (technique < 9) {
        Handler handler = handlers[technique];
        (this->*handler)();
    }
}
