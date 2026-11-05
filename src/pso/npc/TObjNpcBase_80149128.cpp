#include "pso/npc/TObjNpcBase_80149128.h"

extern "C" {
    int load_encrypted_archive_data(void*);
    extern unsigned char lbl_8043F560[];
    extern int npc_town_motion_data;
void load_ply_motion_npc_town(void) { npc_town_motion_data = load_encrypted_archive_data(lbl_8043F560); }
}
