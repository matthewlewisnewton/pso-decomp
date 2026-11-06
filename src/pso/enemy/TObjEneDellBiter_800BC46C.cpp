#include "pso/player/TUnk_804928CC.h"

extern "C" void init_collision_body_parts(void *, const CollisionBody *, s32);

TUnk_804928CC::TUnk_804928CC(TObject *parent, TObjBase *owner,
                           const CollisionBody *parts, s32 count)
    : TObjCollidable(parent) {
    init_collision_body_parts(this, parts, count);
    m_ac = (u32)owner;
}
