#ifndef PSO_ENEMY_TUNK_804EF130_H
#define PSO_ENEMY_TUNK_804EF130_H

#include "pso/object/TObjMotion.h"

class TObjChara;
class TParticleCtrl;

class TUnk_804EF130 : public TObjCollidable {
public:
    TUnk_804EF130(const Vec *position, s32 heading, TObjChara *owner);
    virtual ~TUnk_804EF130();
    virtual void run_task();
    void hit_target(TObjChara *target, TObjChara *owner);
    s32 snap_to_ground(Vec *position);

    Vec projectile_position;
    Vec velocity;
    u8 unknown_c4[0x18];
    f32 distance;
    TParticleCtrl *effect;
    Vec ground_position;
    s32 update_ground;
    s32 ground_timer;
    u16 owner_id;
    u8 unknown_fa[2];
};

typedef char TUnk_804EF130_size[sizeof(TUnk_804EF130) == 0xFC ? 1 : -1];

#endif
