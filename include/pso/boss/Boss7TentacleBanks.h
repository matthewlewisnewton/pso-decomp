#ifndef PSO_BOSS_BOSS7_TENTACLE_BANKS_H
#define PSO_BOSS_BOSS7_TENTACLE_BANKS_H

#include "pso/system/NinjaTypes.h"
#include "pso/system/vector.h"

// Runtime copies of the tentacle model's 14 nodes and their rest positions and
// z angles, owned by the Boss7 tentacle unit.
extern "C" {
extern NJS_OBJECT lbl_80541528[14];
extern Vec TBoss7Tentacle__segment_offsets[14];
extern u32 TBoss7Tentacle__needle_offsets[14];
}

typedef char Boss7NodeBankSize[sizeof(lbl_80541528) == 0x310 ? 1 : -1];
typedef char Boss7PositionBankSize[sizeof(TBoss7Tentacle__segment_offsets) == 0xA8 ? 1 : -1];
typedef char Boss7AngleBankSize[sizeof(TBoss7Tentacle__needle_offsets) == 0x38 ? 1 : -1];

#endif
