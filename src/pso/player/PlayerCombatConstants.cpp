#include "pso/player/PlayerCombatConstants.h"

// The original split leaves this constant pool between the player and ADX logo units.
const f64 player_distance_accuracy_scale = 0.01;
const f64 player_rsqrt_half = 0.5;
const f64 player_rsqrt_three = 3.0;
const char player_meseta_popup_label[] = "MESETA";
const char player_miss_popup_label[] = "MISS";
// Game angles use 65536 units per revolution.
const f64 player_radians_to_game_angle = 10430.38043493439;
