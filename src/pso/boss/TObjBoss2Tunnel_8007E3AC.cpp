#include "types.h"
#include "pso/quest/TQuestListVM_8007EAF8.h"
#include "pso/boss/DragonCoord9.h"

extern "C" void reset_coords__15TObjBoss2TunnelFv();

// Destructor first: this unit's .text is maybe_delete, then reset_coords_pass.
DragonCoord9::~DragonCoord9() {}

DragonCoord9::DragonCoord9() { reset_coords__15TObjBoss2TunnelFv(); }
