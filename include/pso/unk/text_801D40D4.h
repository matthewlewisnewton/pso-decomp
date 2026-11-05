#ifndef PSO_UNK_TEXT_801D40D4_H
#define PSO_UNK_TEXT_801D40D4_H

#include "types.h"

struct TObjPlayer;
class TPlyItem;
struct TItem;
class TPlyInventoryItem;

// Defined in text_801D40D4.cpp; the original gave these plain C names.
extern "C" {
s32 TObjPlayer__sub_801D4368(TPlyItem *ply);
void TObjPlayer__sub_801D45B0(u32 *arg0, TItem *arg1);
s32 TObjPlayer__sub_801D47EC(TPlyItem *arg0, s32 arg1, s32 arg2);
s32 check_player_action_allowed(void);
s32 fn_801D4270(s32 arg0);
void remove_list_entry_by_id(s32 arg0);
// Clears one inventory entry.
TPlyInventoryItem *reset(TPlyInventoryItem *entry);
}

#endif
