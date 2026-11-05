#include "pso/system/SoundEffect.h"
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/item/TItemMag.h"
#include "types.h"
#include "pso/player/TObjChara.h"
#include "pso/player/TObjPlayer.h"
#include "pso/TParticleCtrl.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TQuestVmDownLoadServer.h"
#include "pso/misc/PhotonBlastSummon.h"
#include "pso/system/vector.h"
#include "pso/unk/TUnk_804C349C.h"
#include "pso/unk/text_801AAB74.h"
#include "pso/unk/text_801AB370.h"
#include "pso/unk/text_801ABE14.h"
#include "pso/unk/text_801AE1F8.h"
#include "pso/unk/text_801A9CB8.h"
#include "pso/unk/text_80087278.h"
#include "pso/misc/TParticleCtrl_800867E4.h"
#include "pso/misc/TPhotonLeilla.h"
#include "pso/misc/TPhotonMylla.h"
#include "pso/player/TObjPlayer_801AF2F0.h"
#include "pso/player/TObjPlayer_801AA508.h"
#include "pso/player/TObjPlayer_801AA664.h"
#include "pso/player/TObjPlayer_803130BC.h"

struct Slot_801A8868 { u8 pad[0x18]; };
struct Counts_801A8868 { s32 v[4]; };
struct Rec_801A8868 { u8 pad[0x20]; s32 f20; };

struct Hit_801A86E0 { s32 kind; f32 value; };

// Same object TUnk_804C349C::run_task updates and then hands to these functions.
typedef TUnk_804C349C PhotonBlastSequence_801A9870;

struct PhotonSummonParams_801A9870 {
    Vec position;
    u16 owner_id;
    s32 is_first;
    s32 has_more;
    u8 pad18[4];
    u8 count;
    f32 level;
};
typedef char PhotonSummonParams_801A9870_size[sizeof(PhotonSummonParams_801A9870) == 0x24 ? 1 : -1];
struct VBase_18_b27ba1 { char pad[0x18]; };
struct VObj_18_b27ba1 : VBase_18_b27ba1 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21(void *, struct Hit_801A86E0 *, s32, s32, s32);
};

extern "C" {

extern const f32 lbl_805DC110;
extern const f32 lbl_805DC114;
extern const f32 lbl_805DC118;
extern const f32 lbl_805DC11C;
extern const f32 lbl_805DC120;
extern const f32 lbl_805DC124;
extern const f32 lbl_805DC128;
extern const f32 lbl_805DC12C;

extern u32 lbl_805D5D18;
void deliver_photon_blast_results_animated(PhotonBlastSequence_801A9870 *seq);
void deliver_photon_blast_results_delayed(PhotonBlastSequence_801A9870 *seq);
void step_photon_blast_sequence(PhotonBlastSequence_801A9870 *seq);

// identity, the blast entry's base value, and the blast kind. Same 12-byte
// record PhotonBlastSummon writes.
struct PhotonBlastHit {
    u32 identity;
    f32 value;
    s32 kind;
};
extern PhotonBlastHit photon_blast_hit_queue[32];
extern s32 photon_blast_hit_count;
extern PhotonBlastHit deferred_photon_blast_hit_queue[32];
extern s32 deferred_photon_blast_hit_count;
}
extern s32 photon_blast_donation_flags[];
void clear_photon_blast_donations(void);
extern s32 local_client_id;
s32 is_photon_blast_presentation_admitted(u32 owner_id, void *records);
extern Counts_801A8868 photon_blast_result_counts_init;
extern Rec_801A8868 photon_blast_sequence_table[];
void admit_photon_blast_sequence(u8 *players, void *self);
void apply_photon_blast_action_hold(s32 arg0, s32 arg1, s32 arg2);

#pragma push
#pragma fp_contract on

f32 TUnk_804C349C::calc_photon_blast_power(s32 arg1, f32 farg0) {
    f32 var_f30;
    TItemMag *mag;
    var_f30 = lbl_805DC110;
    if (owner != NULL) {
        mag = (TItemMag *)owner->activate_d04_slot();
        if (mag != 0) {
            switch (arg1) {
            case 0:
                var_f30 = farg0 + ((lbl_805DC114 * (f32)mag->get_iq()) + lbl_805DC118 * (f32)(mag->get_synchro() * (owner->get_field_2c8() + owner->get_actor_attack_params_atp_min())));
                break;
            case 1:
                var_f30 = farg0 + ((lbl_805DC11C * (f32)mag->get_iq()) + lbl_805DC120 * (f32)(owner->get_hp() * mag->get_synchro()));
                break;
            case 2:
                var_f30 = farg0 + ((lbl_805DC124 * (f32)mag->get_iq()) + lbl_805DC128 * (f32)(mag->get_synchro() * (owner->get_field_2c8() + owner->get_actor_attack_params_atp_min())));
                break;
            case 3:
                var_f30 = farg0 + ((lbl_805DC124 * (f32)mag->get_iq()) + lbl_805DC128 * (f32)(owner->get_ata() * mag->get_synchro()));
                break;
            case 4:
                var_f30 = (lbl_805DC12C * (f32)mag->get_iq()) + farg0;
                break;
            case 5:
                var_f30 = 0.1f * (f32)mag->get_iq();
                if (var_f30 >= 20.0f) {
                    var_f30 = 20.0f;
                }
                break;
            }
        }
    }
    return var_f30;
}
#pragma pop

s32 TObjPlayer::is_any_teammate_in_state() {
    struct { u8 _pad[0x20]; } sp8;
    s32 current_floor;
    s32 var_r30;

    TObjPlayer *player;
    current_floor = get_current_floor();
    var_r30 = 0;
loop_1:
    player = get_player_by_client_id(var_r30);
    if (player != NULL && current_floor == player->get_floor() && get_photon_blast_chain(&sp8, var_r30) == 2) {
        return 1;
    }
    var_r30 += 1;
    if (var_r30 >= 4) {
        return 0;
    }
    goto loop_1;
}

s32 is_photon_blast_presentation_admitted(u32 owner_id, void *records) {
    TObjPlayer *local;
    TObjPlayer *owner;
    s32 group;
    if (is_split_screen() != 0) {
        return 1;
    }
    if (local_client_id == ((TObjPlayer *)records)->get_section_id()) {
        return 1;
    }
    local = get_player_by_client_id(local_client_id);
    if (local == NULL) {
        return 0;
    }
    group = local->get_room();
    owner = get_player_by_client_id(owner_id);
    if (owner != NULL) {
        if (local->get_floor() == owner->get_floor() && group == owner->get_room()) {
            return 1;
        }
    }
    return 0;
}

void apply_photon_blast_action_hold(s32 arg0, s32 arg1, s32 arg2) {
    TObjPlayer *plr;
    TObjChara *ent;
    s32 i;
    Hit_801A86E0 tmp1;
    Hit_801A86E0 tmp2;

    ent = find_entity_by_id((u16)arg2);
    for (i = TLobby::get_game_mode(); i < TLobby::get_game_mode() + TObjEneDD::get_enemy_count(); i++) {
        plr = TObjPlayer::get_player_data(i);
        if (plr != NULL && !(plr->actorFlags & 0x40000000)) {
            if (is_split_screen() != 0) {
                tmp1.value = (f32)arg1;
                tmp1.kind = 0x14;
                Hit_801A86E0 hit1 = tmp1;
                ((VObj_18_b27ba1 *)plr)->m21(ent, &hit1, 0, -1, -1);
            } else if (plr->room == ent->get_room()) {
                tmp2.value = (f32)arg1;
                tmp2.kind = 0x14;
                Hit_801A86E0 hit2 = tmp2;
                ((VObj_18_b27ba1 *)plr)->m21(ent, &hit2, 0, -1, -1);
            }
        }
    }
}

void clear_photon_blast_donations(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        photon_blast_donation_flags[i] = 0;
    }
}
// set_type takes u16. 0xFFFF is the zero-extended immediate, and the section id is mr.
void admit_photon_blast_sequence(u8 *players, void *self) {
    Slot_801A8868 a[4];
    Slot_801A8868 b[4];
    s32 n;
    s32 j;
    s32 k;
    s32 flag;
    s32 delay;
    void *o;
    TObjPlayer *p;
    s32 i;
    s32 idx;
    s32 m;
    TObjPlayer *q;
    ((TObjPlayer *)(&a[0]))->init_arrays();
    ((TObjPlayer *)(&a[1]))->init_arrays();
    ((TObjPlayer *)(&a[2]))->init_arrays();
    ((TObjPlayer *)(&a[3]))->init_arrays();
    ((TObjPlayer *)(&b[0]))->init_arrays();
    ((TObjPlayer *)(&b[1]))->init_arrays();
    ((TObjPlayer *)(&b[2]))->init_arrays();
    ((TObjPlayer *)(&b[3]))->init_arrays();
    Counts_801A8868 counts = photon_blast_result_counts_init;
    for (n = 0; n < 4; n++) {
        ((TObjPlayer *)&b[n])->set_type(0xFFFF);
        ((TObjPlayer *)(&b[n]))->set_field_2(-1);
    }
    n = 0;
    k = 0;
    for (j = 0; j < 4; j++, players += 0x18) {
        p = get_player_by_client_id(((TObjPlayer *)players)->get_section_id());
        if (p != NULL && p->get_room() == ((TObjBase *)self)->get_room()
            && TObjPlayer__sub_80313114(players) != -1) {
            ((TObjPlayer *)&a[n])->set_type(((TObjPlayer *)players)->get_section_id());
            ((TObjPlayer *)(&a[n]))->set_field_2(TObjPlayer__sub_80313114(players));
            n++;
        }
    }
    for (i = n; i < 4; i++) {
        ((TObjPlayer *)&a[i])->set_type(0xFFFF);
        ((TObjPlayer *)(&a[i]))->set_field_2(-1);
    }
    for (m = 0; m < 4; m++) {
        if (m != 0) {
            if (TObjPlayer__sub_80313114((u8 *)&a[m]) != -1) {
                if (TObjPlayer__sub_80313114((u8 *)&b[k]) == TObjPlayer__sub_80313114((u8 *)((u8 *)&a[m]))) {
                    counts.v[k]++;
                } else {
                    k++;
                }
            } else {
                k++;
            }
        }
        TObjPlayer__sub_801AA66C(&b[k], &a[m]);
    }
    flag = 0;
    for (i = 0; i < 4; i++) {
        if (i != get_entity_id(self)) {
            q = get_player_by_client_id(i);
            if (q != NULL && q->get_room() == ((TObjBase *)self)->get_room()
                && photon_blast_sequence_table[get_entity_id(q)].f20 != 0) {
                flag = 1;
            }
        }
    }
    if (flag != 0) {
        TObjPlayer__sub_801AA528((s32)&b[3], -1);
        TObjPlayer__sub_801AA528((s32)&b[2], -1);
        TObjPlayer__sub_801AA528((s32)&b[1], -1);
        TObjPlayer__sub_801AA528((s32)&b[0], -1);
        TObjPlayer__sub_801AA528((s32)&a[3], -1);
        TObjPlayer__sub_801AA528((s32)&a[2], -1);
        TObjPlayer__sub_801AA528((s32)&a[1], -1);
        TObjPlayer__sub_801AA528((s32)&a[0], -1);
        return;
    }
    if (is_photon_blast_presentation_admitted(get_entity_id(self), b) != 0) {
        o = TObject::operator new(0x98);
        if (o != NULL) {
            TObjPlayer__sub_801A9E10(o, get_entity_id(self), b, &counts, 1, 0);
        }
    } else {
        idx = 0;
        for (i = 0; i < 4; i++) {
            if (TObjPlayer__sub_80313114((u8 *)&b[i]) == -1) {
                idx = i;
                break;
            }
        }
        delay = idx * 150 + 100;
        o = TObject::operator new(0x98);
        if (o != NULL) {
            TObjPlayer__sub_801A9E10(o, get_entity_id(self), b, &counts, 0, delay);
        }
    }
    TObjPlayer__sub_801AA528((s32)&b[3], -1);
    TObjPlayer__sub_801AA528((s32)&b[2], -1);
    TObjPlayer__sub_801AA528((s32)&b[1], -1);
    TObjPlayer__sub_801AA528((s32)&b[0], -1);
    TObjPlayer__sub_801AA528((s32)&a[3], -1);
    TObjPlayer__sub_801AA528((s32)&a[2], -1);
    TObjPlayer__sub_801AA528((s32)&a[1], -1);
    TObjPlayer__sub_801AA528((s32)&a[0], -1);
}
// Applies one queued blast. calc_photon_blast_power is a method of this sequence.
void deliver_photon_blast_results_animated(PhotonBlastSequence_801A9870 *seq) {
    s32 i;
    for (i = 0; i < photon_blast_hit_count; i++) {
        PhotonBlastHit *hit = &photon_blast_hit_queue[i];
        TObjChara *target = find_entity_by_id((u16)hit->identity);
        if (target == NULL) {
            continue;
        }
        s32 *kind = &hit->kind;
        DirectAttackPayload payload;
        f32 power = seq->calc_photon_blast_power(*kind, hit->value);
        payload.power = (f32)(0.01 * (f64)(seq->power_level * seq->summon_count) * (f64)power);
        if (*kind == 4) {
            payload.kind = 6;
            for (s32 j = 0; j < 4; j++) {
                TObjPlayer *player = get_player_by_client_id(seq->recipients[j]);
                if (player != NULL) {
                    player->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
                    TParticleCtrl *aura = spawn_particle_effect_with_flags(&player->body_center_position, 0x1F8, 0x10);
                    if (aura != NULL) {
                        aura->set_owner_id(get_entity_id(player));
                    }
                }
            }
            if (local_client_id == get_entity_id(target)) {
                play_sound_effect(0x4002AB0E, NULL, 0, 0);
            }
            target->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
            TParticleCtrl *aura = spawn_particle_effect_with_flags(&target->body_center_position, 0x1F8, 0x10);
            if (aura != NULL) {
                aura->set_owner_id(get_entity_id(target));
            }
            TParticleCtrl *effect = spawn_particle_effect_with_flags(&target->position, 0x16C, 0x10);
            if (effect != NULL) {
                effect->set_owner_id(get_entity_id(target));
            }
            effect = spawn_particle_effect_with_flags(&target->position, 0x16D, 0x10);
            if (effect != NULL) {
                effect->set_owner_id(get_entity_id(target));
            }
        } else if (*kind == 5) {
            for (s32 j = 0; j < 4; j++) {
                payload.kind = 7;
                TObjPlayer *player = get_player_by_client_id(seq->recipients[j]);
                if (player != NULL) {
                    if (player->actorFlags & 0x800) {
                        payload.kind = 8;
                    }
                    player->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
                    TParticleCtrl *aura = spawn_particle_effect_with_flags(&player->body_center_position, 0x1F8, 0x10);
                    if (aura != NULL) {
                        aura->set_owner_id(get_entity_id(player));
                    }
                }
            }
            payload.kind = 7;
            if (target->actorFlags & 0x800) {
                payload.kind = 8;
            }
            target->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
            TParticleCtrl *aura = spawn_particle_effect_with_flags(&target->body_center_position, 0x1F8, 0x10);
            if (aura != NULL) {
                aura->set_owner_id(get_entity_id(target));
            }
            payload.kind = 10;
            for (s32 j = 0; j < 4; j++) {
                TObjPlayer *player = get_player_by_client_id(seq->recipients[j]);
                if (player != NULL) {
                    player->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
                }
            }
            target->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
            payload.kind = 9;
            for (s32 j = 0; j < 4; j++) {
                TObjPlayer *player = get_player_by_client_id(seq->recipients[j]);
                if (player != NULL) {
                    player->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
                }
            }
            target->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
            if (local_client_id == get_entity_id(target)) {
                play_sound_effect(0x4002AB10, NULL, 0, 0);
                play_sound_effect(0x4002AD14, NULL, 0, 0);
                play_sound_effect(0x4002AA16, NULL, 0, 0);
            }
            TParticleCtrl *effect = create_timed_particle_emitter_with_flags(&target->position, 0x16E, 0, 0xF, 0x10);
            if (effect != NULL) {
                effect->set_owner_id(get_entity_id(target));
            }
            effect = spawn_particle_effect_with_flags(&target->position, 0x16F, 0x10);
            if (effect != NULL) {
                effect->set_owner_id(get_entity_id(target));
            }
        } else {
            payload.kind = 4;
            target->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
        }
    }
    clear_photon_blast_donations();
}

void deliver_photon_blast_results_delayed(PhotonBlastSequence_801A9870 *seq) {
    s32 i;
    for (i = 0; i < deferred_photon_blast_hit_count; i++) {
        PhotonBlastHit *hit = &deferred_photon_blast_hit_queue[i];
        TObjChara *target = find_entity_by_id((u16)hit->identity);
        if (target == NULL) {
            continue;
        }
        s32 *kind = &hit->kind;
        DirectAttackPayload payload;
        f32 power = seq->calc_photon_blast_power(*kind, hit->value);
        payload.power = (f32)(0.01 * (f64)(seq->power_level * seq->summon_count) * (f64)power);
        if (*kind == 4) {
            payload.kind = 6;
            for (s32 j = 0; j < 4; j++) {
                TObjPlayer *player = get_player_by_client_id(seq->recipients[j]);
                if (player != NULL) {
                    player->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
                    TParticleCtrl *aura = spawn_particle_effect_with_flags(&player->body_center_position, 0x1F8, 0x10);
                    if (aura != NULL) {
                        aura->set_owner_id(get_entity_id(player));
                    }
                }
            }
            if (local_client_id == get_entity_id(target)) {
                play_sound_effect(0x4002AB0E, NULL, 0, 0);
            }
            target->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
            TParticleCtrl *aura = spawn_particle_effect_with_flags(&target->body_center_position, 0x1F8, 0x10);
            if (aura != NULL) {
                aura->set_owner_id(get_entity_id(target));
            }
            TParticleCtrl *effect = spawn_particle_effect_with_flags(&target->position, 0x16C, 0x10);
            if (effect != NULL) {
                effect->set_owner_id(get_entity_id(target));
            }
            effect = spawn_particle_effect_with_flags(&target->position, 0x16D, 0x10);
            if (effect != NULL) {
                effect->set_owner_id(get_entity_id(target));
            }
        } else if (*kind == 5) {
            for (s32 j = 0; j < 4; j++) {
                payload.kind = 7;
                TObjPlayer *player = get_player_by_client_id(seq->recipients[j]);
                if (player != NULL) {
                    if (player->actorFlags & 0x800) {
                        payload.kind = 8;
                    }
                    player->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
                    TParticleCtrl *aura = spawn_particle_effect_with_flags(&player->body_center_position, 0x1F8, 0x10);
                    if (aura != NULL) {
                        aura->set_owner_id(get_entity_id(player));
                    }
                }
            }
            payload.kind = 7;
            if (target->actorFlags & 0x800) {
                payload.kind = 8;
            }
            target->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
            TParticleCtrl *aura = spawn_particle_effect_with_flags(&target->body_center_position, 0x1F8, 0x10);
            if (aura != NULL) {
                aura->set_owner_id(get_entity_id(target));
            }
            payload.kind = 10;
            for (s32 j = 0; j < 4; j++) {
                TObjPlayer *player = get_player_by_client_id(seq->recipients[j]);
                if (player != NULL) {
                    player->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
                }
            }
            target->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
            payload.kind = 9;
            for (s32 j = 0; j < 4; j++) {
                TObjPlayer *player = get_player_by_client_id(seq->recipients[j]);
                if (player != NULL) {
                    player->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
                }
            }
            target->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
            if (local_client_id == get_entity_id(target)) {
                play_sound_effect(0x4002AB10, NULL, 0, 0);
                play_sound_effect(0x4002AD14, NULL, 0, 0);
                play_sound_effect(0x4002AA16, NULL, 0, 0);
            }
            TParticleCtrl *effect = create_timed_particle_emitter_with_flags(&target->position, 0x16E, 0, 0xF, 0x10);
            if (effect != NULL) {
                effect->set_owner_id(get_entity_id(target));
            }
            effect = spawn_particle_effect_with_flags(&target->position, 0x16F, 0x10);
            if (effect != NULL) {
                effect->set_owner_id(get_entity_id(target));
            }
        } else {
            payload.kind = 4;
            target->receive_direct_attack(seq->owner, payload, NULL, -1, -1);
        }
    }
    clear_photon_blast_donations();
}

void step_photon_blast_sequence(PhotonBlastSequence_801A9870 *seq) {
    PhotonSummonParams_801A9870 params;
    u8 *summon;
    s32 first_summon;
    s32 j;

    VecCopy(&params.position, &seq->position);
    if (seq->owner != NULL) {
        params.owner_id = get_entity_id(seq->owner);
    } else {
        params.owner_id = 0xFFFF;
    }
    switch (seq->state) {
    case 0:
        if (seq->summon_index != 0 && seq->summon->all_parents_unqueued_for_destruction() != 0) {
            break;
        }
        if (seq->summon_index == seq->summon_count) {
            seq->state = 2;
            break;
        }
        if (seq->summon_index != 0) {
            switch (seq->kinds[seq->summon_index]) {
            case 2:
            case 3: {
                TObjChara *anchor = find_entity_by_id(lbl_805D5D18);
                if (anchor != NULL) {
                    VecCopy(&seq->position, &anchor->position);
                }
                break;
            }
            }
        }
        first_summon = seq->summon_index == 0 ? 1 : 0;
        params.has_more = seq->summon_index != seq->summon_count - 1 ? 1 : 0;
        params.is_first = first_summon;
        params.count = seq->summon_count;
        params.level = seq->levels[seq->summon_index];
        switch (seq->kinds[seq->summon_index]) {
        case 2:
            summon = (u8 *)TObject::operator new(0x1CC);
            if (summon != NULL) {
                summon = TPhotonGolla__ct(summon, (u8 *)&params);
            }
            seq->summon = (TObject *)summon;
            break;
        case 3:
            summon = (u8 *)TObject::operator new(0x1AC);
            if (summon != NULL) {
                summon = TPhotonPilla__ct(summon, (u8 *)&params);
            }
            seq->summon = (TObject *)summon;
            break;
        case 4:
            summon = (u8 *)TObject::operator new(0x1B0);
            if (summon != NULL) {
                summon = (u8 *)TPhotonLeilla__ct((Leilla_801AC808 *)summon, (Pkt_801AC808 *)&params);
            }
            seq->summon = (TObject *)summon;
            for (j = 0; j < 4; j++) {
                if (seq->participants[j] < 4) {
                    queue_photon_blast_support(seq->participants[j], 4, 1);
                }
            }
            break;
        case 0:
            summon = (u8 *)TObject::operator new(0x1A8);
            if (summon != NULL) {
                summon = TPhotonFarlla__ct(summon, (u8 *)&params);
            }
            seq->summon = (TObject *)summon;
            break;
        case 1:
            summon = (u8 *)TObject::operator new(0x1A4);
            if (summon != NULL) {
                summon = TPhotonEstlla__ct(summon, (u8 *)&params);
            }
            seq->summon = (TObject *)summon;
            break;
        case 5:
            summon = (u8 *)TObject::operator new(0x1A8);
            if (summon != NULL) {
                summon = (u8 *)TPhotonMylla__ct((Mylla_801AD970 *)summon, (Pkt_801AD970 *)&params);
            }
            seq->summon = (TObject *)summon;
            for (j = 0; j < 4; j++) {
                if (seq->participants[j] < 4) {
                    queue_photon_blast_support(seq->participants[j], 5, 1);
                }
            }
            break;
        }
        seq->summon->suspend_update();
        seq->summon->disallow_rendering();
        seq->summon_index++;
        seq->state = 1;
        break;
    case 1:
        ((TQuestVmDownLoadServer *)seq->summon)->clear_flag4_bit4();
        seq->summon->allow_rendering();
        seq->state = 0;
        break;
    case 2:
        play_sound_effect(0x40021927, (const Vec *)(&seq->position), 0, 0);
        deliver_photon_blast_results_animated(seq);
        seq->queue_destruction();
        break;
    }
}

s32 photon_blast_donation_flags[4];
Rec_801A8868 photon_blast_sequence_table[4];
