#include "types.h"
#include "pso/unk/text_800D8830.h"
#include "pso/misc/TOTrapAncient01_80226534.h"
#include "pso/map/FloorArea.h"

enum FloorAreaSoundRequest {
    FLOOR_SOUND_CCA_JUNGLE_MOUNTAIN_SEASIDE_PERSISTENT = 0x3A842,
    FLOOR_SOUND_SEASIDE_NIGHT_PERSISTENT = 0x4003B22D,
    FLOOR_SOUND_SEABED_PERSISTENT = 0x4003A835,
    FLOOR_SOUND_CCA_JUNGLE_MOUNTAIN_SEASIDE_ONCE = 0x3A840,
    FLOOR_SOUND_SEASIDE_NIGHT_ONCE = 0x4003B22B,
    FLOOR_SOUND_SEABED_ONCE = 0x4003A833,
};

extern "C" {
s32 play_sound_effect(int, void *, int, int);

void play_floor_area_persistent_sound(TObject *owner, Vec *pos) {
    switch (get_current_floor_area()) {
    case AREA_CENTRAL_CONTROL_AREA:
    case AREA_JUNGLE_NORTH:
    case AREA_JUNGLE_EAST:
    case AREA_MOUNTAIN:
    case AREA_SEASIDE:
        play_persistent_sound(FLOOR_SOUND_CCA_JUNGLE_MOUNTAIN_SEASIDE_PERSISTENT, (s32)owner, (u32)pos, 0, 0);
        break;
    case AREA_SEASIDE_NIGHT:
        play_persistent_sound(FLOOR_SOUND_SEASIDE_NIGHT_PERSISTENT, (s32)owner, (u32)pos, 0, 0);
        break;
    case AREA_SEABED_UPPER:
    case AREA_SEABED_LOWER:
        play_persistent_sound(FLOOR_SOUND_SEABED_PERSISTENT, (s32)owner, (u32)pos, 0, 0);
        break;
    }
}

s32 play_floor_area_sound_effect(Vec *pos) {
    s32 area = get_current_floor_area();
    switch (area) {
    case AREA_CENTRAL_CONTROL_AREA:
    case AREA_JUNGLE_NORTH:
    case AREA_JUNGLE_EAST:
    case AREA_MOUNTAIN:
    case AREA_SEASIDE:
        return play_sound_effect(FLOOR_SOUND_CCA_JUNGLE_MOUNTAIN_SEASIDE_ONCE, pos, 0, 0);
    case AREA_SEASIDE_NIGHT:
        return play_sound_effect(FLOOR_SOUND_SEASIDE_NIGHT_ONCE, pos, 0, 0);
    case AREA_SEABED_UPPER:
    case AREA_SEABED_LOWER:
        return play_sound_effect(FLOOR_SOUND_SEABED_ONCE, pos, 0, 0);
    }
    return area;
}
}
