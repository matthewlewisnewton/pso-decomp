#include "pso/TMainTask.h"
#include "pso/misc/ParticleFactory.h"
#include "pso/misc/PhotonBlastSummon.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TFogCtrl.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TPhotonMagicSquare.h"
#include "pso/misc/TPhotonRainbow_801AE640.h"
#include "pso/misc/TPhotonYoulla.h"
#include "pso/network/client_id.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/player/TObjPlayer_801AADE8.h"
#include "pso/player/TObjPlayer_801AB608.h"
#include "pso/player/TObjPlayer_801AC0D8.h"
#include "pso/player/TObjPlayer_801ACA6C.h"
#include "pso/player/TObjPlayer_801AD47C.h"
#include "pso/player/TObjPlayer_801ADC6C.h"
#include "pso/player/TObjPlayer_801AE48C.h"
#include "pso/player/TObjPlayer_801AF2F0.h"
#include "pso/player/TObjPlayer_803130BC.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/system/SoundEffect.h"
#include "pso/system/vector.h"
#include "pso/unk/TUnk_804C349C.h"
#include "pso/unk/text_801AA3B4.h"
#include "pso/unk/text_8024AB98.h"

// The startup and resource routines follow the sequence task in .text. Keeping
// them together places the resource tables before the generated vtable in .data.
extern "C" {
s32 restore_player_cameras();
void release_photon_blast_player_holds(u16 *holds);
}

void reset_cameras_to_actor(void *actor, s32 arg1);
void freeze_players_for_photon_blast(s16 room, u16 *holds);

TUnk_804C349C::~TUnk_804C349C() {
    if (animated != 0) {
        TLobby::set_and_notify_default();
        release_photon_blast_player_holds(holds);
        if (get_player_by_client_id(local_client_id) != NULL) {
            TLobby__sub_8024AC20(local_client_id);
            TCameraCtrl::release_photon_blast_camera();
            restore_player_cameras();
            reset_cameras_to_actor(get_player_by_client_id(local_client_id), 0);
        }
    } else {
        TFogCtrl::restore_fog_for_player(owner_client_id, 0);
    }
    if (owner_client_id != 0xFFFF && owner_client_id < 4) {
        for (s32 i = 0; i < 4; i++) {
            if (participants[i] < 4) {
                for (s32 j = 0; j < 4; j++) {
                    photon_blast_sequence_table[participants[i]].kinds[j] = -1;
                    photon_blast_sequence_table[participants[i]].participants[j] = 0xFFFF;
                }
                photon_blast_sequence_table[participants[i]].state = 0;
            }
        }
    }
}

TUnk_804C349C::TUnk_804C349C(s32 client, PhotonBlastSlot *slots, const s32 *counts, s32 animated, s32 delay)
    : TObject(tl_07) {
    owner_client_id = client;
    this->delay = delay;
    elapsed = 0;
    this->animated = animated;
    for (s32 i = 0; i < 4; i++) {
        levels[i] = counts[i] + 1;
        kinds[i] = -1;
        holds[i] = 0xFFFF;
    }

    power_level = 0;
    TObjPlayer *player = get_player_by_client_id(client);
    if (player != NULL) {
        power_level = player->get_photon_blast_charge();
    }

    for (s32 i = 0; i < 4; i++) {
        participants[i] = 0xFFFF;
    }
    summon_count = 4;
    // Advance the slot cursor first to reproduce the original loop schedule.
    for (s32 i = 0; i < 4; slots++, i++) {
        if (TObjPlayer__sub_80313114(slots->data) == -1) {
            summon_count = i;
            break;
        }
        kinds[i] = TObjPlayer__sub_80313114(slots->data);
        participants[i] = ((TObjPlayer *)slots)->get_section_id();
    }

    owner = get_player_by_client_id(client);
    apply_photon_blast_action_hold(this, summon_count * 150 + 100, client);
    if (this->animated != 0) {
        TLobby::send_neg30();
        TObjPlayer__sub_8024ABDC(local_client_id);
        if (owner != NULL) {
            VecCopy(&position, &owner->position);
            play_sound_effect(0x40021927, &position, 0, 0);
        }
        clear_photon_blast_hits();
    } else {
        clear_deferred_photon_blast_hits();
        TFogCtrl::select_fog_for_viewport(owner_client_id, 62, 0);
    }

    for (s32 i = 0; i < 4; i++) {
        if (participants[i] < 4) {
            if (photon_blast_sequence_table[participants[i]].state != 2) {
                for (s32 j = 0; j < 4; j++) {
                    photon_blast_sequence_table[participants[i]].kinds[j] = kinds[j];
                    photon_blast_sequence_table[participants[i]].participants[j] = participants[j];
                }
            }
            photon_blast_sequence_table[participants[i]].state = 2;
        }
    }
    state = 0;
    summon = NULL;
    summon_index = 0;
    for (s32 i = 0; i < 4; i++) {
        recipients[i] = 0xFFFF;
    }

    if (owner != NULL && get_player_by_client_id(local_client_id) != NULL) {
        u8 *recipient = TObjPlayer::find_photon_blast_by_section_id(get_entity_id(owner));
        if (recipient != NULL) {
            for (s32 i = 0; i < 4; i++) {
                if (((TObjPlayer *)recipient)->get_entity_type() != 0xFFFF
                    && ((TObjPlayer *)recipient)->get_entity_type() != owner_client_id) {
                    recipients[i] = ((TObjPlayer *)recipient)->get_entity_type();
                }
                recipient += 4;
            }
        }
    }
    if (this->animated != 0) {
        TObjPlayer *player = get_player_by_client_id(owner_client_id);
        if (player != NULL) {
            freeze_players_for_photon_blast(player->get_room(), holds);
        }
    }
}

extern "C" s32 get_photon_blast_chain(void *output, s32 player) {
    PhotonBlastChain *chain = static_cast<PhotonBlastChain *>(output);
    s32 i;
    if (photon_blast_sequence_table[player].state == 0) {
        return 0;
    }
    if (photon_blast_sequence_table[player].state == 2) {
        for (i = 0; i < 4; i++) {
            chain->kinds[i] = photon_blast_sequence_table[player].kinds[i];
            chain->participants[i] = photon_blast_sequence_table[player].participants[i];
        }
        return 2;
    }
    if (photon_blast_sequence_table[player].state == 1) {
        for (i = 0; i < 4; i++) {
            chain->kinds[i] = photon_blast_sequence_table[player].kinds[i];
            chain->participants[i] = photon_blast_sequence_table[player].participants[i];
        }
        return 1;
    }
    return 0;
}

extern "C" s32 is_locally_controlled__10TObjPlayerFPv(TObjPlayer *);

void TObjPlayer::start_photon_blast(s32 kind, s32 client) {
    TObjPlayer *player;
    void *photon_blast_entry;
    TPhotonMagicSquare *magic_square;

    player = get_player_by_client_id(client);
    if (player != NULL) {
        photon_blast_entry = TObjPlayer::get_photon_blast_entry(kind);
        if (is_locally_controlled__10TObjPlayerFPv(player) != 0) {
            play_effect_default(player, *(s16 *)((s8 *)photon_blast_entry + 0x20));
        }
        spawn_particle_effect(&player->position, 0x13D);
        TCameraCtrl::set_shake_preset(0);
        switch (kind) {
        case 2:
            magic_square = static_cast<TPhotonMagicSquare *>(TObject::operator new(sizeof(TPhotonMagicSquare)));
            if (magic_square != NULL) {
                magic_square->construct_at_owner(tl_07, 2, static_cast<u16>(client));
                return;
            }
            break;
        case 3:
            magic_square = static_cast<TPhotonMagicSquare *>(TObject::operator new(sizeof(TPhotonMagicSquare)));
            if (magic_square != NULL) {
                magic_square->construct_at_owner(tl_07, 3, static_cast<u16>(client));
                return;
            }
            break;
        case 4:
            magic_square = static_cast<TPhotonMagicSquare *>(TObject::operator new(sizeof(TPhotonMagicSquare)));
            if (magic_square != NULL) {
                magic_square->construct_at_owner(tl_07, 4, static_cast<u16>(client));
                return;
            }
            break;
        case 0:
            magic_square = static_cast<TPhotonMagicSquare *>(TObject::operator new(sizeof(TPhotonMagicSquare)));
            if (magic_square != NULL) {
                magic_square->construct_at_owner(tl_07, 0, static_cast<u16>(client));
                return;
            }
            break;
        case 1:
            magic_square = static_cast<TPhotonMagicSquare *>(TObject::operator new(sizeof(TPhotonMagicSquare)));
            if (magic_square != NULL) {
                magic_square->construct_at_owner(tl_07, 1, static_cast<u16>(client));
                return;
            }
            break;
        case 5:
            magic_square = static_cast<TPhotonMagicSquare *>(TObject::operator new(sizeof(TPhotonMagicSquare)));
            if (magic_square != NULL) {
                magic_square->construct_at_owner(tl_07, 5, static_cast<u16>(client));
            }
            break;
        }
    }
}

extern "C" u8 photon_blast_entry_table[];

void *TObjPlayer::get_photon_blast_entry(int kind) {
    return photon_blast_entry_table + kind * 44;
}

typedef void (*PhotonBlastResourceCallback)();

extern char lbl_80446A78[];
extern char lbl_80446A88[];
extern char lbl_80446A98[];
extern char lbl_80446AAC[];
extern char lbl_80446ABC[];
extern char lbl_80446ACC[];
extern char lbl_80446AE0[];
extern char lbl_80446AF4[];
extern char lbl_80446B08[];
extern char lbl_80446B1C[];
extern char lbl_80446B30[];
extern char lbl_80446B44[];
extern char lbl_80446B58[];
extern char lbl_80446B68[];
extern char lbl_80446B78[];
extern char lbl_80446B8C[];
extern char lbl_80446BA4[];
extern char lbl_80446BBC[];
extern char lbl_80446BD4[];
extern char lbl_80446BE8[];
extern char lbl_80446C00[];
extern char lbl_80446C18[];
extern char lbl_80446C30[];
extern char lbl_80446C44[];
extern char lbl_80446C58[];
extern char lbl_80446C74[];
extern char lbl_80446C90[];
extern char lbl_80446CAC[];
extern const char *pm_mdl_model_names[13];
extern const char *pm_mdl_motion_names[16];
extern BmlResourceDescriptor photon_blast_resource_descriptor;

extern PhotonBlastResourceCallback photon_blast_load_callback_table[20];
extern s32 photon_blast_donation_flags[4];

extern "C" {
void call_funcs_reverse__6TLobbyFPvUi(void *, int);
extern u32 photon_blast_shared_resource;
s32 run_load_callback_table(void *, int);
void TObjPlayer__sub_801AC440();
void TObjPlayer__sub_801AC43C();

void TObjPlayer__sub_801AA3B4(void) {
    s32 i;
    call_funcs_reverse__6TLobbyFPvUi(photon_blast_load_callback_table, sizeof(photon_blast_load_callback_table));
    if (photon_blast_shared_resource != 0U) {
        delete (BmlResource *)(photon_blast_shared_resource);
        photon_blast_shared_resource = 0U;
    }
    for (i = 0; i < 4; i++) {
        photon_blast_donation_flags[i] = 0;
    }
    TObjPlayer::clear_photon_blast_slots();
}
void TObjPlayer::clear_photon_blast_slots() {
    s32 i;
    s32 j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            photon_blast_sequence_table[i].kinds[j] = -1;
            photon_blast_sequence_table[i].participants[j] = 0xFFFF;
        }
        photon_blast_sequence_table[i].state = 0;
    }
}
}
void load_photon_blast_resources(void) {
    s32 i;
    BmlResource *resource = new BmlResource(1, &photon_blast_resource_descriptor, 0, 0, NULL);
    photon_blast_shared_resource = reinterpret_cast<u32>(resource);
    run_load_callback_table(photon_blast_load_callback_table, sizeof(photon_blast_load_callback_table));
    for (i = 0; i < 4; i++) {
        photon_blast_donation_flags[i] = 0;
    }
    TObjPlayer::clear_photon_blast_slots();
}
extern "C" {

const char *pm_mdl_model_names[13] = {
    lbl_80446A78, lbl_80446A88, lbl_80446A98, lbl_80446AAC, lbl_80446ABC, lbl_80446ACC,
    lbl_80446AE0, lbl_80446AF4, lbl_80446B08, lbl_80446B1C, lbl_80446B30, lbl_80446B44, NULL,
};

const char *pm_mdl_motion_names[16] = {
    lbl_80446B58, lbl_80446B68, lbl_80446B78, lbl_80446B8C, lbl_80446BA4, lbl_80446BBC,
    lbl_80446BD4, lbl_80446BE8, lbl_80446C00, lbl_80446C18, lbl_80446C30, lbl_80446C44,
    lbl_80446C58, lbl_80446C74, lbl_80446C90, NULL,
};
}
BmlResourceDescriptor photon_blast_resource_descriptor = {
    lbl_80446CAC, pm_mdl_model_names, pm_mdl_motion_names, 12, 15,
};

// The resource loader walks this table forward for initialization and
// backward for release. Each pair is one load and one release callback.
PhotonBlastResourceCallback photon_blast_load_callback_table[] = {
    create_golla_photon_blast_model, TObjPlayer::destroy_static_buffer_pair,
    create_pilla_photon_blast_model, TObjPlayer::free_buffer_pair,
    create_leilla_photon_blast_model, TObjPlayer::destroy_buffer_pair_instance,
    create_farlla_photon_blast_model, TObjPlayer::destroy_buffers,
    create_estlla_photon_blast_model, TObjPlayer::destroy_global_buffer,
    TObjPlayer__sub_801AEB80, TObjPlayer__sub_801AEB74,
    TObjPlayer__sub_801ADC78, TObjPlayer__sub_801ADC6C,
    TObjPlayer__sub_801AD480, TObjPlayer__sub_801AD47C,
    TObjPlayer__sub_801AE728, TObjPlayer__sub_801AE724,
    TObjPlayer__sub_801AC440, TObjPlayer__sub_801AC43C,
};
