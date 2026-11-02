#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/object/TObjMotion.h"

extern "C" f32 normalize_vector(Vec *);

// Keep the callback boundary provisional while using the established hit/body
// layout internally. The incoming vector is copied before normalization.
// Preserve x/y/z store order: output may overlap a body center.
typedef char HitTargetOffset[offsetof(ActorBodyHit,target)==0 ? 1 : -1];
typedef char HitBodyOffset[offsetof(ActorBodyHit,body)==4 ? 1 : -1];
typedef char BodiesOffset[offsetof(TObjCollidable,bodies)==0xA4 ? 1 : -1];
typedef char BodyRadiusOffset[offsetof(CollisionBody,radius)==0xC ? 1 : -1];
typedef char BodyCenterOffset[offsetof(CollisionBody,center)==0x1C ? 1 : -1];
typedef char BodyStride[sizeof(CollisionBody)==0x2C ? 1 : -1];
typedef char VectorSize[sizeof(Vec)==12 ? 1 : -1];

#pragma push
#pragma fp_contract on
extern "C" void TObjPlayer__sub_802D5B78(void *arg0, void *arg1, const void *arg2) {
    ActorBodyHit *hit = static_cast<ActorBodyHit *>(arg0);
    Vec *output = static_cast<Vec *>(arg1);
    Vec normalized = *static_cast<const Vec *>(arg2);
    (void)normalize_vector(&normalized);
    CollisionBody *body = &hit->target->bodies[hit->body];
    f32 radius = body->radius;
    output->x = body->center.x - normalized.x * radius;
    output->y = body->center.y - normalized.y * radius;
    output->z = body->center.z - normalized.z * radius;
}
#pragma pop
