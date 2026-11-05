#include "types.h"
#include "pso/npc/TObjNpcBase.h"
#include "pso/misc/TLobby.h"

extern u32 npc_town_motion_data;

void TObjNpcBase::free_static() {
    if ((u32) npc_town_motion_data != 0U) {
        TLobby::free_nodes_with_id((u32)((void*)npc_town_motion_data));
        npc_town_motion_data = 0U;
    }
}
