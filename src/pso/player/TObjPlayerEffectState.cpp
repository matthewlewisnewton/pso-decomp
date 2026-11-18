#include "pso/player/TObjPlayer.h"

extern s8 scene_fog_enable_flag;

void TObjPlayer::set_effect_active() {
    scene_fog_enable_flag = 1;
}


void TObjPlayer::reset_particle_counter() {
    scene_fog_enable_flag = 0;
}
