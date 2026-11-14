#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/misc/TPhotonLine.h"
#include "pso/misc/ParticleFactory.h"
#include "pso/misc/PhotonBlastSummon.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/system/MatrixOps.h"
#include "pso/system/vector.h"
#include "pso/TParticleCtrl.h"

extern "C" {
extern const char photon_line_class_name[];
const char *lbl_805D3500 = photon_line_class_name;
CollisionBody photon_line_collision_body_part = {
    { 0.0f, 0.0f, 0.0f }, 30.0f, 30.0f, 1, 0x8007,
    { 0.0f, 0.0f, 0.0f }, 0.0f
};
s32 check_path_obstructed(void *, Vec *);
u16 get_entity_id(TObjBase *);
}

void TPhotonLine::render() {
    TParticleCtrl::begin_effect_render();
    TParticleCtrl::end_effect_render();
}

void TPhotonLine::run_task() {
    Vec next_position = position;
    s32 i;
    TObjBase *player;
    s32 j;
    vec3_add_to(&next_position, &velocity);
    VecCopy(&body_center_position, &position);
    body_center_position.y += 60.0f;
    next_position.y += 60.0f;
    if (check_path_obstructed(this, &next_position) == 1) {
        queue_destruction();
        return;
    }
    TObjPlayer::init_all_slots();
    mark_enemy_body_contacts();
    if (bodies->flags & 0x100000) {
        for (i = 0; i < 16; i++) {
            player = (TObjBase *)TObjPlayer::get_battle_param(i);
            if (player == NULL) {
                break;
            }
            for (j = 0; j < hit_count; j++) {
                if (hit_ids[j] == get_entity_id(player)) {
                    break;
                }
            }
            if (j == hit_count) {
                hit_ids[hit_count++] = get_entity_id(player);
                // The original inserts the ninth ID before stopping damage dispatch.
                if ((s32)hit_count >= 9) {
                    break;
                }
                queue_photon_blast_hit(get_entity_id(player), 1, 0, hit_scale);
                spawn_particle_effect(&player->position, 0x162);
                spawn_particle_effect(&player->position, 0x163);
            }
        }
    }
    position.x += velocity.x;
    position.z += velocity.z;
}

TPhotonLine::~TPhotonLine() {
    unregister_object_by_id();
    free_collision_body_parts(this);
}

TPhotonLine::TPhotonLine(PhotonLineParams *params, TObject *parent, u16 owner_id)
    : TObjChara(parent) {
    s32 i;
    m_name = lbl_805D3500;
    VecCopy(&home_position, VecCopy(&position, &params->position));
    VecCopy(&velocity, &params->direction);
    velocity.x *= params->speed;
    velocity.y *= params->speed;
    velocity.z *= params->speed;
    hit_scale = params->hit_scale;
    owner = find_entity_by_id(owner_id);
    init_collision_body_parts(this, &photon_line_collision_body_part, 1);
    refresh_collision_body_centers();
    register_object_by_id();
    for (i = 0; i < 10; i++) {
        hit_ids[i] = 0xFFFF;
    }
    hit_count = 0;
}

extern "C" const char photon_line_class_name[] = "TPhotonLine";
