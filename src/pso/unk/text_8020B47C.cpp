#include "types.h"
#include "pso/system/byteswap.h"
#include "pso/unk/text_8020E08C.h"
#include "pso/unk/text_8020B47C.h"

extern "C" void TLobby__sub_8020B47C(FloorFlagsBuffer *buffer) {
    const s16 *values2;
    const s16 *values;
    s32 i2;
    fn_8020B588(buffer);
    values = (const s16 *)((u8 *)buffer + buffer->object_offset);
    for (s32 floor = 0; floor < 18; ++floor) {
        if (TLobby__floor_enemy_group_table[floor].objects > 0) {
            Saved_8020E08C *records = TLobby__floor_enemy_group_table[floor].objectRows;
            s32 count = TLobby__floor_enemy_group_table[floor].objects;
            for (s32 i = 0; i < count;) {
                s16 flags = *values;
                bswap_16((u16 *)&flags);
                ++values;
                ++i;
                records->flags = flags;
                ++records;
            }
        }
    }
    values2 = (const s16 *)((u8 *)buffer + buffer->enemy_offset);
    for (s32 floor2 = 0; floor2 < 18; ++floor2) {
        if (TLobby__floor_enemy_group_table[floor2].enemies > 0) {
            Saved_8020E08C *records2 = TLobby__floor_enemy_group_table[floor2].enemyRows;
            s32 count2 = TLobby__floor_enemy_group_table[floor2].enemies;
            for (i2 = 0; i2 < count2;) {
                s16 flags = *values2;
                bswap_16((u16 *)&flags);
                ++values2;
                ++i2;
                records2->flags = flags;
                ++records2;
            }
        }
    }
}
