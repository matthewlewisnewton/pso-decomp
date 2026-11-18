#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/player/TUnk_80491460.h"

#include "pso/TMainTask.h"
#include "pso/TParticleCtrl.h"
#include "pso/map/WallQuery.h"
#include "pso/math/MatrixVector.h"
#include "pso/misc/ParticleFactory.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_801AF2F0.h"
#include "pso/system/MatrixOps.h"
#include "pso/system/NinjaUtil.h"
#include "pso/system/vector.h"
#include "pso/unk/text_800870BC.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/unk/text_803D96A8.h"

static const Vec initial_step = {0.0f, 0.0f, 7.0f};

void TUnk_80491460::try_hit_target(TObjPlayer *player) {
    if (player != NULL && !(player->actorFlags & 0xA00) &&
        !(xz_distance_squared(&position, &player->body_center_position) > 49.0f)) {
        DirectAttackPayload hit = {0, 0.0f};
        hit.power = power;
        player->receive_direct_attack((void *)source, hit, NULL, -1, -1);
        spawn_particle_effect(&player->body_center_position, 0xFB);
        queue_destruction();
    }
}

void TUnk_80491460::run_task() {
    vec3_add_to(&position, &velocity);
    frame++;
    if (!(frame & 3)) {
        if (csnVector(&previous_position, &position, -1) != NULL) {
            queue_destruction();
            return;
        }
        VecCopy(&previous_position, &position);
    }

    if (particle != NULL) {
        particle->set_position(&position);
    }
    distance_traveled += 7.0f;
    if (distance_traveled >= 150.0f) {
        queue_destruction();
        return;
    }

    for (s32 client = 0; client < 12; client++) {
        TObjPlayer *player = get_player_by_client_id(client);
        try_hit_target(player);
    }
}

TUnk_80491460::~TUnk_80491460() {
    if (particle != NULL) {
        particle->queue_destruction();
    }
}

TUnk_80491460::TUnk_80491460(void *start, s32 angle, s32 source, s32 power) : TObject(tl_06) {
    VecCopy(&position, (const Vec *)start);
    VecCopy(&previous_position, (const Vec *)start);
    distance_traveled = 0.0f;

    push_matrix_from(&identity_matrix);
    Vec step = initial_step;
    rotate_matrix_y(NULL, angle);
    rotate_vector_by_matrix(0, &step, &velocity);
    pop_matrix();

    this->source = source;
    s32 rotation[3];
    rotation[0] = 0;
    rotation[1] = angle + 0x4000;
    rotation[2] = 0x4000;
    particle = (TParticleCtrl *)spawn_particle_effect_with_rotation(start, rotation, 0x6D, 2);
    frame = 0;
    this->power = power;
}
