#include "pso/player/TUnk_804928CC.h"

extern "C" void init_collision_body_parts(void *, const CollisionBody *, s32);
extern CollisionBody construct_collision_body_parts;

TUnk_804928CC::TUnk_804928CC(TObject *parent, TObjBase *owner)
    : TObjCollidable(parent) {
    init_collision_body_parts(this, &construct_collision_body_parts, 1);
    if (owner != NULL) {
        sub_800BC3E8((u8 *)owner);
    } else {
        m_ac = 0;
    }
}
