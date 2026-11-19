#include "pso/system/SoundEffect.h"
#include "types.h"
#include "pso/unk/text_800D8830.h"
#include "pso/object/trap/TOTrapAncient01_80226534.h"
#include "pso/map/FloorArea.h"
#include "pso/player/TObjPlayer_80011014.h"

extern "C" {

void play_floor_area_persistent_sound(void *owner, void *pos) {
    switch (get_current_floor_area()) {
    case AREA_CENTRAL_CONTROL_AREA:
    case AREA_JUNGLE_NORTH:
    case AREA_JUNGLE_EAST:
    case AREA_MOUNTAIN:
    case AREA_SEASIDE:
        play_persistent_sound(0x3A842, (s32)owner, (u32)pos, 0, 0);
        break;
    case AREA_SEASIDE_NIGHT:
        play_persistent_sound(0x4003B22D, (s32)owner, (u32)pos, 0, 0);
        break;
    case AREA_SEABED_UPPER:
    case AREA_SEABED_LOWER:
        play_persistent_sound(0x4003A835, (s32)owner, (u32)pos, 0, 0);
        break;
    }
}

void play_floor_area_sound_effect(void *pos) {
    switch (get_current_floor_area()) {
    case AREA_CENTRAL_CONTROL_AREA:
    case AREA_JUNGLE_NORTH:
    case AREA_JUNGLE_EAST:
    case AREA_MOUNTAIN:
    case AREA_SEASIDE:
        play_sound_effect(0x3A840, (const Vec *)pos, 0, 0);
        break;
    case AREA_SEASIDE_NIGHT:
        play_sound_effect(0x4003B22B, (const Vec *)pos, 0, 0);
        break;
    case AREA_SEABED_UPPER:
    case AREA_SEABED_LOWER:
        play_sound_effect(0x4003A833, (const Vec *)pos, 0, 0);
        break;
    }
}
}
