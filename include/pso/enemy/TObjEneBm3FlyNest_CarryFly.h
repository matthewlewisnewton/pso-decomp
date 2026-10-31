#ifndef PSO_ENEMY_TOBJENEBM3FLYNEST_CARRYFLY_H
#define PSO_ENEMY_TOBJENEBM3FLYNEST_CARRYFLY_H

#include "pso/TObject.h"
#include "pso/system/vector.h"
#include "pso/animation/ActorAnimationState.h"

struct TObjEneBm3FlyNest;

class TObjEneBm3FlyNest_CarryFly : public TObject {
public:
    TObjEneBm3FlyNest_CarryFly(TObjEneBm3FlyNest *parent, const Vec *attachment,
        const Vec *destination, const Vec *, const s32 *counter, s32 order);
    virtual ~TObjEneBm3FlyNest_CarryFly();
    virtual void run_task();
    virtual void render();

    Vec position;
    s32 order;
    s32 state;
    const Vec *attachment;
    const Vec *destination;
    const s32 *release_counter;
    f32 unknown_3c;
    s32 rotation_y;
    s32 unknown_44;
    AnimationMotion *motion;
    f32 frame;
    Vec direction;
    f32 distance;
    f32 curvature;
    f32 flight_height;
};

typedef char CarryFlySize[sizeof(TObjEneBm3FlyNest_CarryFly) == 0x68 ? 1 : -1];

#endif
