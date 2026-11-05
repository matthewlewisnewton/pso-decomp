#define TOBJECT_OUT_OF_LINE_HELPERS
#include "types.h"
#include "pso/TBoss7PhotonPad.h"
#include "pso/system/vector.h"

#include "pso/TObject.h"
#include "pso/object/TObjMotion.h"
#include "pso/boss/TObjBoss2Tunnel_8007E418.h"
#include "pso/boss/TBoss7PhotonBullet_802EF26C.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/unk/text_800BC4C8.h"
#include "pso/boss/TBoss7PhotonBullet.h"
#include "pso/player/TUnk_804928CC.h"

#include "pso/boss/TBoss7Joint.h"
#include "pso/boss/TBoss7DeRolLeC.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/misc/TNowLoading.h"
#include "pso/player/TObjPlayer.h"
#include "pso/TParticleCtrl.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/unk/text_80087278.h"

struct Boss7PhotonLevel {
    s32 shots;
    s32 interval;
    s32 spread;
    f32 speed;
};

extern "C" {
extern const char *lbl_805D3FD4;
extern DirectAttackPayload lbl_80474038[];
extern s32 lbl_80474040[];
extern const f32 lbl_805DEA00;
extern const f32 lbl_805DEA04;
extern Boss7PhotonLevel boss7_photon_bullet_level_table[];
extern const char *lbl_805D3FD0;
}

// Definitions run bottom to top. -inline off,deferred emits .text in address
// order and the compiler vtables as bullet then pad.
TBoss7PhotonPad::TBoss7PhotonPad(TObject *parent, const Vec *shot_origin, const Vec *direction, s32 shot_level)
    : TObject(parent) {
    m_name = lbl_805D3FD0;
    origin = shot_origin;
    level = shot_level;
    VecCopy(&pos, direction);
    rotate_xz_pair_by_angle(&pos.x, &pos.z, (s32)(-(boss7_photon_bullet_level_table[level].spread / 2)));
    shots = boss7_photon_bullet_level_table[level].shots;
    timer = 0;
}

TBoss7PhotonPad::~TBoss7PhotonPad() {}

void TBoss7PhotonPad::run_task() {
    timer--;
    if (timer <= 0) {
        TBoss7DeRolLeC *st = TBoss7Joint::get_state();
        if (st != NULL) {
            new TBoss7PhotonBullet(m_up, st, origin, &pos, 1.5f * boss7_photon_bullet_level_table[level].speed);
        }
        timer = boss7_photon_bullet_level_table[level].interval;
        rotate_xz_pair_by_angle(&pos.x, &pos.z, (s32)(boss7_photon_bullet_level_table[level].spread / boss7_photon_bullet_level_table[level].shots));
        shots--;
        if (shots == 0) {
            queue_destruction();
        }
    }
}

void TBoss7PhotonPad::render() {  }

TBoss7PhotonBullet::TBoss7PhotonBullet(TObject *parent, TObjBase *owner, const Vec *origin, const Vec *aim, f32 scale)
    : TUnk_804928CC(parent, owner) {
    m_name = lbl_805D3FD4;
    VecCopy(&position, VecCopy(&travel, origin));
    VecCopy(&this->aim, aim);
    bodies->radius = 3.0f;
    shadow_pos.x = 0.0f;
    shadow_pos.y = 0.0f;
    shadow_pos.z = 0.0f;
    shadow_scale.x = 1.0f;
    shadow_scale.y = 1.0f;
    shadow_scale.z = 1.0f;
    speed = scale;
    age = 0;
    grounded = 0;
    fall = 0.0f;
    effects[0] = spawn_continuous_particle_effect_with_flags(&travel, 0x202, 0x40);
    effects[1] = spawn_continuous_particle_effect_with_flags(&travel, 0x203, 0x40);
}

TBoss7PhotonBullet::~TBoss7PhotonBullet() {
    if (effects[0] != NULL) {
        effects[0]->queue_destruction();
    }
    if (effects[1] != NULL) {
        effects[1]->queue_destruction();
    }
}

void TBoss7PhotonBullet::run_task() {
    s32 i;
    if (travel.y > 18.7f) {
        fall += 0.05f;
        if (fall >= 3.0f) {
            fall = 3.0f;
        }
        travel.y -= fall;
        travel.x = (2.0f) * aim.x + travel.x;
        travel.z = (2.0f) * aim.z + travel.z;
    } else {
        travel.y = 18.7f;
        travel.x = aim.x * speed + travel.x;
        travel.z = aim.z * speed + travel.z;
    }
    position.x = travel.x;
    position.z = travel.z;
    for (i = 0; i != 2; i++) {
        if (effects[i] != NULL) {
            effects[i]->set_position(&travel);
        }
    }
    if (age % 16 == 0) {
        if (project_actor_to_ground(this, &position, &shadow_pos) != 0) {
            grounded |= 1;
        } else {
            grounded &= ~1;
        }
    }
    if (position.x <= lbl_805DEA00 && position.x >= lbl_805DEA04) {
        DirectAttackPayload attack = lbl_80474038[0];
        attack.power = TBoss7PhotonBullet::get_target_pos_y();
        if (vfunc_16(lbl_80474040, &attack) != 0) {
            queue_destruction();
            return;
        }
    }
    age++;
    if (age >= 0x78) {
        queue_destruction();
    }
}

void TBoss7PhotonBullet::render() {
    if (grounded & 1) {
        TObjEneDD::draw_oriented_shadow(&position, &shadow_pos, 0, &shadow_scale);
    }
}
