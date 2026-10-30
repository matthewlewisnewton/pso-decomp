#ifndef PSO_MISC_POSITIONSOUNDEFFECTS_H
#define PSO_MISC_POSITIONSOUNDEFFECTS_H

struct Vec;
extern "C" {
void play_area_sound_and_particles_a(const Vec *position);
void play_area_sound_and_particles_b(const Vec *position);
void spawn_position_particles(const Vec *position);
}

#endif
