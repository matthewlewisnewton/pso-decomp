#include "types.h"
#include "pso/system/NinjaUtil.h"
#include "pso/object/TObjBgmCol.h"

extern "C" {

void *get_player_by_client_id(s32 i);

extern s32 local_client_id;

s32 TObjBgmCol::is_within_distance(f32 farg0) {
    s32 arg0 = (s32)this;
    u32 player;

    player = (u32)get_player_by_client_id(local_client_id);
    if ((player != 0U) && (xyz_distance_squared((Vec *)(player + 0x38), (Vec *)(arg0 + 0x38)) < farg0)) {
        return 1;
    }
    return 0;
}

}
