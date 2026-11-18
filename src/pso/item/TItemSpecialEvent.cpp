#include "types.h"
#include "pso/item/TItemSpecialEvent.h"
#include "pso/item/armor/TItemProShield.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/system/task/TMainTask.h"

// Hits the owner with a direct attack of the given kind (15-18 by the use
// effects below) and no power.
void TItemSpecialEvent::send_obj_position_event(s32 kind) {
    if (owner != NULL) {
        DirectAttackPayload payload;
        payload.kind = kind;
        payload.power = 0.0f;
        owner->receive_direct_attack(owner, payload, NULL, -1, -1);
    }
}

// The use effects, picked by apply_use_effect from the item's technique byte.
void TItemSpecialEvent::sub_8035307C() {
    send_obj_position_event(18);
}

void TItemSpecialEvent::sub_803530A0() {
    send_obj_position_event(17);
}

void TItemSpecialEvent::sub_803530C4() {
    if (TObjPlayer::is_locally_controlled(owner) != 0) {
        owner->apply_shock_status();
    }
}

void TItemSpecialEvent::sub_80353110() {
    send_obj_position_event(16);
}

void TItemSpecialEvent::sub_80353134() {
    send_obj_position_event(15);
}

void TItemSpecialEvent::sub_80353158() {
    add_actor_hp((u8 *)owner, ((TItemProShield *)owner)->get_field_2b8());
}

void TItemSpecialEvent::sub_80353194() {
    add_actor_tp((u8 *)owner, obj_getS16_2BA((u8 *)owner));
}

// The Star Atomizer's effect (see send_nearby_player_ids).
void TItemSpecialEvent::sub_803531D0() {
    send_nearby_player_ids(owner, 10000.0f);
}

void TItemSpecialEvent::sub_803531F8() {}

void TItemSpecialEvent::apply_use_effect() {
    void (TItemSpecialEvent::*effects[9])() = {
        &TItemSpecialEvent::sub_803531F8, &TItemSpecialEvent::sub_803531D0, &TItemSpecialEvent::sub_80353194,
        &TItemSpecialEvent::sub_80353158, &TItemSpecialEvent::sub_80353134, &TItemSpecialEvent::sub_80353110,
        &TItemSpecialEvent::sub_803530C4, &TItemSpecialEvent::sub_803530A0, &TItemSpecialEvent::sub_8035307C,
    };
    u8 technique = get_technique();
    if (technique < 9) {
        void (TItemSpecialEvent::*effect)() = effects[technique];
        (this->*effect)();
    }
}

TItemSpecialEvent::~TItemSpecialEvent() {}

TItemSpecialEvent::TItemSpecialEvent(TObject *parent, u8 *item) : TItemObject(parent, item) {}

TItemSpecialEvent *TItemSpecialEvent::create(u8 *item) {
    if (item != NULL) {
        return new TItemSpecialEvent(tl_05, item);
    }
    return NULL;
}
