#include "pso/misc/TOWreckAncientResources.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "types.h"
#include "pso/misc/TOWreckAncient03.h"
#include "pso/unk/text_8017E0D0.h"
#include "pso/player/TObjPlayer.h"


struct RecoveredGlobal_8017E0D0___vt__16TOWreckAncient03 {
    s32 value;
    u8 remaining[0x34];
};

extern "C" {
u8 *TOWreckAncient__ct(u8 *arg0, s32 arg1);
extern RecoveredGlobal_8017E0D0___vt__16TOWreckAncient03 __vt__16TOWreckAncient03;
extern s32 TOWreckAncient03__name;
typedef char RecoveredGlobal_8017E0D0___vt__16TOWreckAncient03_size[sizeof(RecoveredGlobal_8017E0D0___vt__16TOWreckAncient03) == 0x38 ? 1 : -1];
u8 *TOWreckAncient03__ct(u8 *wreck_ancient, s32 arg1) {
    TOWreckAncient__ct(wreck_ancient, 2);
    *(s32 **)((s8 *)wreck_ancient + 0x18) = &__vt__16TOWreckAncient03.value;
    *(s32 *)((s8 *)wreck_ancient + 0) = (s32) TOWreckAncient03__name;
    ((TOWreckAncient03 *)(wreck_ancient))->apply_object_set_data((void *)arg1);
    init_collision_body_parts((TObjCollidable *)wreck_ancient, &TOWreckAncient__collision_body_templates[2], 1);
    ((TObjPlayer *)wreck_ancient)->register_object_by_id();
    return wreck_ancient;
}

}
