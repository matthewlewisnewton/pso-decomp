#ifndef PSO_BOSS_BOSS7_TENTACLE_BANKS_H
#define PSO_BOSS_BOSS7_TENTACLE_BANKS_H

#include "pso/boss/TBoss1Dragon.h"
#include "pso/system/vector.h"
#include <stddef.h>

// Runtime destination banks owned by the Boss7 tentacle system. These are live
// objects, not views of the serialized resource's 52-byte node records.
extern "C" {
extern DragonModelNode lbl_80541528[14];
extern Vec TBoss7Tentacle__segment_offsets[14];
extern u32 TBoss7Tentacle__needle_offsets[14];
}

typedef char Boss7NodeSize[sizeof(DragonModelNode) == 0x38 ? 1 : -1];
typedef char Boss7NodePositionOffset[offsetof(DragonModelNode, position) == 8 ? 1 : -1];
typedef char Boss7NodeRotationOffset[offsetof(DragonModelNode, rotation) == 0x14 ? 1 : -1];
typedef char Boss7NodeChildOffset[offsetof(DragonModelNode, child) == 0x2C ? 1 : -1];
typedef char Boss7NodeSiblingOffset[offsetof(DragonModelNode, sibling) == 0x30 ? 1 : -1];
typedef char Boss7NodeTailOffset[offsetof(DragonModelNode, unknown34) == 0x34 ? 1 : -1];
typedef char Boss7NodeBankSize[sizeof(lbl_80541528) == 0x310 ? 1 : -1];
typedef char Boss7PositionBankSize[sizeof(TBoss7Tentacle__segment_offsets) == 0xA8 ? 1 : -1];
typedef char Boss7AngleBankSize[sizeof(TBoss7Tentacle__needle_offsets) == 0x38 ? 1 : -1];

#endif
