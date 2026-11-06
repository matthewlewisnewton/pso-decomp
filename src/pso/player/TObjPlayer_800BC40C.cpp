#include "pso/player/TUnk_804928CC.h"

extern "C" void free_collision_body_parts(void *);

CollisionBody construct_collision_body_parts = {
    {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f, 0, 0x9D03, {0.0f, 0.0f, 0.0f}, 0.0f
};

TUnk_804928CC::~TUnk_804928CC() {
    free_collision_body_parts(this);
}
