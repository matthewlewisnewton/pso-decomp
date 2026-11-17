#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/item/TUnk_8049F038.h"
#include "pso/TItemEffEquip.h"
#include "pso/TItemAttacker.h"
#include "pso/TParticleCtrl.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/player/TObjPlayer_801AF2F0.h"
#include "pso/unk/text_801036CC.h"
#include "pso/unk/text_80087278.h"

extern const CollisionBody equipment_effect_body;
const CollisionBody equipment_effect_body = {
    {0.0f, 0.0f, 0.0f}, 3.0f, 0.0f, 0, 0x31F0B,
    {0.0f, 0.0f, 0.0f}, 0.0f
};
extern const char TItemEffEquip__class_name_string[];
const char TItemEffEquip__class_name_string[] = "TItemEffEquip";
const char *TItemEffEquip__class_name = TItemEffEquip__class_name_string;
extern "C" void advance_equipment_effect(TObject *effect);
extern "C" void retire_equipment_effect(TObject *effect);

// Deferred generation preserves the native function and vtable order.
#pragma defer_codegen on

TUnk_8049F038::TUnk_8049F038(TObject *parent, u16 client, s32 joint)
    : TObjCollidable(parent) {
    client_id = client;
    this->joint = joint;
    copy_collision_body(&body, &equipment_effect_body);
    if (get_entity_id(this) == 0xFFFF) {
        set_entity_id(pop_free_entity_id());
    }
    set_collision_body(&body);
    register_object_by_id();
    disallow_rendering();
}

TUnk_8049F038::~TUnk_8049F038() {
    if (bodies != NULL) {
        unregister_object_by_id();
        clear_collision_bodies();
        push_free_entity_id(get_entity_id(this));
        set_entity_id(0xFFFF);
    }
}

void TUnk_8049F038::run_task() {
    TObjPlayer *player = get_player_by_client_id(client_id);
    if (player != NULL) {
        player->get_anim_node_position(joint, &position);
    }
}

void *TUnk_8049F038::get_center() {
    TObjPlayer *player = get_player_by_client_id(client_id);
    if (player != NULL) {
        player->get_anim_node_position(joint, &position);
    }
    return &position;
}

void TItemEffEquip::create(TObject *parent, u16 client_id, s32 joint,
                          s32 effect_id, s32 next_effect_id) {
    new TItemEffEquip(parent, client_id, joint, effect_id, next_effect_id);
}

TItemEffEquip::TItemEffEquip(TObject *parent, u16 client_id, s32 joint,
                           s32 effect_id, s32 next_effect_id) : TObject(parent) {
    m_name = TItemEffEquip__class_name;
    disallow_rendering();
    attachment = new TUnk_8049F038(this, client_id, joint);
    effect = NULL;
    this->next_effect_id = next_effect_id;
    if (attachment != NULL) {
        spawn_equip_particle_effect(effect_id);
        TItemAttacker::spawn_item_timer(this, advance_equipment_effect, 10);
        TItemAttacker::spawn_item_timer(this, retire_equipment_effect, 20);
    } else {
        queue_destruction();
    }
}

TItemEffEquip::~TItemEffEquip() {
    TParticleCtrl::release(effect);
}

void TItemEffEquip::run_task() {
    if (attachment->all_parents_unqueued_for_destruction() == 0) {
        attachment = NULL;
        queue_destruction();
    }
}

void TItemEffEquip::release_effect() {
    if (attachment != NULL && next_effect_id != -1) {
        TParticleCtrl::release(effect);
        spawn_equip_particle_effect(next_effect_id);
    }
}

void advance_equipment_effect(TObject *effect) {
    if (effect != NULL) {
        static_cast<TItemEffEquip *>(effect)->release_effect();
    }
}

void retire_equipment_effect(TObject *effect) {
    if (effect != NULL) {
        effect->queue_destruction();
    }
}

void TItemEffEquip::spawn_equip_particle_effect(s32 effect_id) {
    effect = spawn_continuous_particle_effect_with_flags(attachment->get_center(), effect_id, 0x10);
    if (effect != NULL) {
        effect->set_owner_id(get_entity_id(attachment));
    }
}
