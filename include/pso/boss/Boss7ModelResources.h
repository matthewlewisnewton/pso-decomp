#ifndef PSO_BOSS7_MODEL_RESOURCES_H
#define PSO_BOSS7_MODEL_RESOURCES_H
#include "types.h"
struct DragonModelNode;
struct AnimationMotion;
// Preserve the existing exported identities while correcting the actual index
// arguments and model return. Neither routine has a TObjPlayer receiver.
extern "C" {
DragonModelNode *queue_boss_effect__10TObjPlayerFPv(s32 index);
AnimationMotion *notify_fish_obj__10TObjPlayerFPv(s32 index);
}
#endif
