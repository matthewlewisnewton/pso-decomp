#include "pso/boss/Boss7TentacleBanks.h"

// One storage-only link contribution for the three Boss7 tentacle banks.
// Declaration order preserves offsets 0, 0x310 and 0x3B8 within the 0x3F0-byte
// range. This is not a claim that the original game used a separate data TU.
// The original code remains on fallback; its recovery is a separate follow-up.
extern "C" {
DragonModelNode lbl_80541528[14];
Vec TBoss7Tentacle__segment_offsets[14];
u32 TBoss7Tentacle__needle_offsets[14];
}
