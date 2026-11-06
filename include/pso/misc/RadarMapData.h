#ifndef PSO_MISC_RADARMAPDATA_H
#define PSO_MISC_RADARMAPDATA_H

#include "types.h"
#include <stddef.h>
#include <dolphin/mtx.h>

// Three 0x28-byte view records are owned by the original map-state BSS.
struct RadarMapViewState {
    Vec position;
    f32 field0c, field10, field14;
    s32 field18, field1c;
    f32 field20, field24;
};

typedef char RadarMapViewSize[(sizeof(RadarMapViewState) == 0x28) ? 1 : -1];
typedef char RadarMapViewPosition[(offsetof(RadarMapViewState, position) == 0) ? 1 : -1];
typedef char RadarMapViewField18[(offsetof(RadarMapViewState, field18) == 0x18) ? 1 : -1];
typedef char RadarMapViewField24[(offsetof(RadarMapViewState, field24) == 0x24) ? 1 : -1];

extern "C" {
extern RadarMapViewState TRaderMapCore__map_view_state[3];
s32 add_radar_scaled_gate(Vec *position, u32 color, u16 rotation, s16 kind, s32 flags, f32 scale);
}
#endif
