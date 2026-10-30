#ifndef PSO_ENEMY_TUNK_804E14E8_H
#define PSO_ENEMY_TUNK_804E14E8_H

#include "types.h"
#include "pso/object/TObjMotion.h"

class TParticleCtrl;
struct GiGueProjectileAngles { s32 x, y, z; };

class TUnk_804E14E8 : public TObjCollidable {
public:
    TUnk_804E14E8(Vec *origin, u16 target, GiGueProjectileAngles *angles,
                  s32 delay, s32 special_attack, u16 source);
    virtual ~TUnk_804E14E8();
    virtual void run_task();

    Vec projectile_position;
    Vec previous_projectile_position;
    Vec velocity;
    u8 unk_D0[0x18];
    f32 m_e8;
    s32 timer;
    Vec *origin;
    f32 homing_acceleration;
    TParticleCtrl *particle0;
    TParticleCtrl *particle1;
    s32 state;
    s32 special_attack;
    u16 target_id;
    u16 source_id;
};

typedef char TUnk_804E14E8_size[sizeof(TUnk_804E14E8) == 0x10C ? 1 : -1];
#endif
