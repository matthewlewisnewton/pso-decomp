#ifndef PSO_PLAYER_PLAYERLEVELTABLE_H
#define PSO_PLAYER_PLAYERLEVELTABLE_H
#include "types.h"
#include "pso/TPlyDispData.h"
#include "pso/player/StatsCopy.h"

// One row in PlyLevelTbl: six growth bytes, two reserved bytes and total EXP.
struct PlayerLevelTableRow {
    u8 growth[6];
    u8 reserved[2];
    s32 experience;
};
typedef char PlayerLevelTableRowSize[sizeof(PlayerLevelTableRow) == 12 ? 1 : -1];

// Class interfaces use plain char with the native build's signed-char setting.
extern "C" s32 get_class_starting_inventory(char class_index);

PlayerLevelTableRow *get_ply_level_table_row(char class_index, s32 level);
extern "C" {
struct stats *get_class_base_stats(char class_index);
const player_stats *get_class_stat_caps(char class_index);
void apply_class_level_growth(char class_index, s32 level, struct stats *out);
s32 get_level_row_exp_threshold(const PlayerLevelTableRow *row);
// Preserve the historical export labels at this recovered record boundary.
// These entry points read level rows, rather than player objects.
u8 get_char_class__10TObjPlayerFv(const PlayerLevelTableRow *row);
u8 get_team_id__10TObjPlayerFv(const PlayerLevelTableRow *row);
u8 TObjPlayer__sub_801C2134(const PlayerLevelTableRow *row);
u8 TObjPlayer__sub_801C212C(const PlayerLevelTableRow *row);
u8 get_byte_4__10TObjPlayerFv(const PlayerLevelTableRow *row);
u8 get_field_5__10TObjPlayerFv(const PlayerLevelTableRow *row);
}
#endif
