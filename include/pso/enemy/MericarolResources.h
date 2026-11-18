#ifndef PSO_ENEMY_MERICAROL_RESOURCES_H
#define PSO_ENEMY_MERICAROL_RESOURCES_H

#include "types.h"
#include "pso/system/vector.h"
#include "pso/npc/NpcAnimationBinding.h"
#include "pso/object/TObjMotion.h"

struct SampledMotionPoints;

extern "C" {
extern const u32 mericarol_phase_effect_colors[3];
extern const char mericarol_body_model_name[];
extern const char mericarol_attack_motion_name[];
extern const char mericarol_damage_motion_name[];
extern const char mericarol_dead_motion_name[];
extern const char mericarol_fire_motion_name[];
extern const char mericarol_laugh_motion_name[];
extern const char mericarol_wait_motion_name[];
extern const char mericarol_wait2_motion_name[];
extern const char mericarol_wake_motion_name[];
extern const char mericarol_archive_name[];
extern const char mericarol_low_detail_body_model_name[];
extern const char mericarol_low_detail_archive_name[];

extern const char mericarol_class_name_string[];
extern TObjMotionAction mericarol_motion_actions[9];
extern const NpcAnimationBinding mericarol_animation_binding;

extern const Vec lbl_80472490;
extern const Vec lbl_8047249C;
extern const Vec player_sub_802ce68c_zero_vec;
extern SampledMotionPoints *TBoss4Type3_shared_instance;
extern SampledMotionPoints *mericarol_sampled_motion_points;
}

#endif
