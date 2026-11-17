#ifndef PSO_PLAYER_TOBJPLAYER_802C367C_H
#define PSO_PLAYER_TOBJPLAYER_802C367C_H

#include "types.h"

extern "C" {
int init_new_character_data(void *p);
void init_new_character_stats(void *arg0);
void init_character_stats_for_level(char class_index, void *character_data, s32 level);
void init_technique_levels(s32 flags, s8 *counts);
}

#endif
