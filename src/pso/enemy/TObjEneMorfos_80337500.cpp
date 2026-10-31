#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/enemy/TUnk_804EF130.h"
#include "pso/system/vector.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/math/AngleLookup.h"
#include "pso/system/MatrixOps.h"
#include "pso/system/NinjaUtil.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/unk/text_800870BC.h"
#include "pso/map/CsnGroundQuery.h"
#include "pso/map/CsnQuery.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjChara.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/TParticleCtrl.h"

#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off

extern "C" {
extern const DirectAttackPayload lbl_80477B70[];
extern f32 morfos_projectile_speed;
extern f32 morfos_projectile_power;
extern const f32 lbl_805DF988;
extern const f32 lbl_805DF98C;
extern const f32 lbl_805DF990;
extern const f32 lbl_805DF994;
extern TObject *tl_06;
}

void TUnk_804EF130::hit_target(TObjChara *target, TObjChara *owner) {
    Vec position = projectile_position;
    subtract_vector(&position, &velocity);
    if (target != NULL && target != owner && !(target->actorFlags & 0x04000A00)) {
        if (!(xz_distance_squared(&position, &target->body_center_position) >
              (lbl_805DF988 * morfos_projectile_speed) * (lbl_805DF988 * morfos_projectile_speed))) {
            DirectAttackPayload temporary = lbl_80477B70[0];
            temporary.power = morfos_projectile_power;
            DirectAttackPayload attack = temporary;
            target->receive_direct_attack(owner, attack, NULL, -1, -1);
        }
    }
}

s32 TUnk_804EF130::snap_to_ground(Vec *position) {
    CsnHit *hit = csnVecterUnder(position, 0x16EF);
    if (hit == NULL) {
        return 0;
    }
    VecCopy(position, &hit->contact->point);
    return 1;
}

void TUnk_804EF130::run_task() {
    TObjChara *owner;
    s32 i;
    Vec previous_position = projectile_position;
    vec3_add_to(&projectile_position, &velocity);
    if (effect != NULL) {
        effect->set_position(&projectile_position);
    }
    distance += morfos_projectile_speed;
    if (update_ground != 0) {
        VecCopy(&ground_position, &projectile_position);
        ground_timer++;
        if (ground_timer > 4) {
            ground_timer = 0;
            snap_to_ground(&ground_position);
        }
    }
    if (distance >= lbl_805DF98C) {
        queue_destruction();
        return;
    }
    if (csnVector(&previous_position, &projectile_position, -1) != NULL) {
        queue_destruction();
        return;
    }
    owner = (TObjChara *)find_entity_by_id(owner_id);
    if (owner != NULL) {
        for (i = 0; i < registered_player_count; i++) {
            TObjPlayer *player = TObjPlayer::get_player_data(i);
            if (TObjPlayer::is_valid_and_active((u32)player) != 0 &&
                fabs_float(projectile_position.y - player->body_center_position.y) < lbl_805DF990) {
                hit_target(player, owner);
            }
        }
    }
}

TUnk_804EF130::~TUnk_804EF130() {
    if (effect != NULL) {
        effect->queue_destruction();
    }
}

TUnk_804EF130::TUnk_804EF130(const Vec *position, s32 heading, TObjChara *owner)
    : TObjCollidable(tl_06) {
    s32 angles[3];
    VecCopy(&projectile_position, position);
    distance = lbl_805DF994;
    owner_id = get_entity_id(owner);
    angles[0] = 0;
    angles[1] = heading - 0x4000;
    angles[2] = 0x4000;
    velocity.x = morfos_projectile_speed * sin_table_lookup(heading);
    velocity.y = lbl_805DF994;
    velocity.z = morfos_projectile_speed * cos_table_lookup(heading);
    effect = (TParticleCtrl *)spawn_particle_effect_with_rotation((void *)position, angles, 0x213, 2);
    VecCopy(&ground_position, &projectile_position);
    snap_to_ground(&ground_position);
    ground_timer = 0;
}

extern "C" {
__declspec(section ".rodata") extern const DirectAttackPayload lbl_80477B70[1] = {{0, 0.0f}};
__declspec(section ".sdata2") extern const f32 lbl_805DF988 = 1.5f;
__declspec(section ".sdata2") extern const f32 lbl_805DF98C = 500.0f;
__declspec(section ".sdata2") extern const f32 lbl_805DF990 = 20.0f;
__declspec(section ".sdata2") extern const f32 lbl_805DF994 = 0.0f;
}
