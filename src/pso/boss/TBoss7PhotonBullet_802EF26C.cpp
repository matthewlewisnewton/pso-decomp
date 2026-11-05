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

struct VBase_18_39be15 { char pad[0x18]; };

struct VObj_18_39be15 : VBase_18_39be15 {
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
    virtual s32 m14(s32 *, void *);
};

struct V2_802EF2AC { s32 x; f32 y; };

struct Bullet_802EF2AC {
    u8 pad0[0x38];
    f32 pos[3];
    u8 pad44[0xB0 - 0x44];
    f32 b0, b4, b8, bc;
    f32 c0, c4, c8;
    f32 cc[3];
    u8 padD8[0xE4 - 0xD8];
    s32 e4;
    u32 e8;
    f32 ec;
    void *f0[2];
};

struct Ent_802EF74C { s32 a; s32 b; s32 c; f32 d; };

extern "C" {
TParticleCtrl *spawn_continuous_particle_effect_with_flags(const Vec *pos, s32 idx, s32 flags);
extern const char *lbl_805D3FD4;
s32 project_actor_to_ground(void *, void *, void *);
extern V2_802EF2AC lbl_80474038[];
extern s32 lbl_80474040[];
extern const f32 lbl_805DEA00;
extern const f32 lbl_805DEA04;
void __dl__7TObjectFPv(void *);
extern Ent_802EF74C boss7_photon_bullet_level_table[];
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
    rotate_xz_pair_by_angle(&pos.x, &pos.z, (s32)(-(boss7_photon_bullet_level_table[level].c / 2)));
    shots = boss7_photon_bullet_level_table[level].a;
    timer = 0;
}

TBoss7PhotonPad::~TBoss7PhotonPad() {}

void TBoss7PhotonPad::run_task() {
    timer--;
    if (timer <= 0) {
        TBoss7DeRolLeC *st = TBoss7Joint::get_state();
        if (st != NULL) {
            new TBoss7PhotonBullet(m_up, st, origin, &pos, 1.5f * boss7_photon_bullet_level_table[level].d);
        }
        timer = boss7_photon_bullet_level_table[level].b;
        rotate_xz_pair_by_angle(&pos.x, &pos.z, (s32)(boss7_photon_bullet_level_table[level].c / boss7_photon_bullet_level_table[level].a));
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
    trail = spawn_continuous_particle_effect_with_flags(&travel, 0x202, 0x40);
    glow = spawn_continuous_particle_effect_with_flags(&travel, 0x203, 0x40);
}

TBoss7PhotonBullet::~TBoss7PhotonBullet() {
    if (trail != NULL) {
        trail->queue_destruction();
    }
    if (glow != NULL) {
        glow->queue_destruction();
    }
}

void TBoss7PhotonBullet::run_task() {
    Bullet_802EF2AC *arg0 = (Bullet_802EF2AC *)this;
    s32 i;
    if (arg0->c4 > 18.7f) {
        arg0->ec += 0.05f;
        if (arg0->ec >= 3.0f) {
            arg0->ec = 3.0f;
        }
        arg0->c4 -= arg0->ec;
        arg0->c0 = (2.0f) * arg0->b4 + arg0->c0;
        arg0->c8 = (2.0f) * arg0->bc + arg0->c8;
    } else {
        arg0->c4 = 18.7f;
        arg0->c0 = arg0->b4 * arg0->b0 + arg0->c0;
        arg0->c8 = arg0->bc * arg0->b0 + arg0->c8;
    }
    arg0->pos[0] = arg0->c0;
    arg0->pos[2] = arg0->c8;
    for (i = 0; i != 2; i++) {
        if (arg0->f0[i] != 0) {
            ((TParticleCtrl *)arg0->f0[i])->set_position(&arg0->c0);
        }
    }
    if (arg0->e4 % 16 == 0) {
        if (project_actor_to_ground(arg0, arg0->pos, arg0->cc) != 0) {
            arg0->e8 |= 1;
        } else {
            arg0->e8 &= ~1;
        }
    }
    if (arg0->pos[0] <= lbl_805DEA00 && arg0->pos[0] >= lbl_805DEA04) {
        V2_802EF2AC v = lbl_80474038[0];
        v.y = TBoss7PhotonBullet::get_target_pos_y();
        if (((VObj_18_39be15 *)(arg0))->m14(lbl_80474040, &v) != 0) {
            queue_destruction();
            return;
        }
    }
    arg0->e4++;
    if (arg0->e4 >= 0x78) {
        queue_destruction();
    }
}

void TBoss7PhotonBullet::render() {
    u8 *arg0 = (u8 *)this;
    if (*(s32 *)((s8 *)arg0 + 0xE8) & 1) {
        ((TObjEneDD *)(arg0 + 0x38))->draw_oriented_shadow((s32)(arg0 + 0xCC), 0, (u32)(arg0 + 0xD8));
    }
}
