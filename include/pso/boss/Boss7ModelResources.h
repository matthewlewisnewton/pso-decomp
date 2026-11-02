#ifndef PSO_BOSS7_MODEL_RESOURCES_H
#define PSO_BOSS7_MODEL_RESOURCES_H
#include "types.h"
struct AnimationMotion;
// Preserve the existing exported identities while correcting the actual index
// arguments. Models remain serialized, pointer-fixed resource bytes; this
// getter does not establish a live DragonModelNode. Neither routine has a
// TObjPlayer receiver.
extern "C" {
u8 *queue_boss_effect__10TObjPlayerFPv(s32 index);
AnimationMotion *notify_fish_obj__10TObjPlayerFPv(s32 index);
// Legacy particle APIs carry the borrowed texture-list address as an integer.
s32 TObjPlayer__sub_802E80A0(void);
}
#endif
