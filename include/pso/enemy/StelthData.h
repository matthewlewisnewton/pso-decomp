#ifndef PSO_ENEMY_STELTH_STELTHDATA_H
#define PSO_ENEMY_STELTH_STELTHDATA_H
#include "types.h"
#include "pso/system/vector.h"
#include "pso/system/NinjaTypes.h"
#include "pso/boss/TBoss3VoloptP01.h"
#include "pso/enemy/DelDepthData.h"

// Shared Stelth resources, tuning parameters and render colors.
struct IVec_800F1098 { s32 a, b, c; };

extern "C" {
// TObjEneMe3Stelth.cpp .data; both attack bindings point at it.
extern TObjMotionAction TObjEneMe3Stelth__animation_descriptors[13];
extern const NJS_ARGB stelth_fade_color;
extern const TBoss3VoloptBreakupParams me3_stelth_breakup_params;
// TLobby kind ids, one list per TLobby table load_shared_resources registers them with.
extern const s32 lbl_8043D47C[2];
extern const s32 lbl_8043D484[2];
extern const s32 lbl_8043D48C[2];
extern const s32 lbl_8043D494[2];
extern const char stelth_model[];
extern const char stelth_t_wait_motion[];
extern const char stelth_apper_motion[];
extern const char stelth_backstep_motion[];
extern const char stelth_bareta_motion[];
extern const char stelth_damage_motion[];
extern const char stelth_death_motion[];
extern const char stelth_f_attack_motion[];
extern const char stelth_sword_motion[];
extern const char stelth_transform_motion[];
extern const char stelth_wait_motion[];
extern const char stelth_walk_motion[];
extern const char stelth_bml[];
extern const char stelth_low_model[];
extern const char stelth_low_bml[];
extern const char stelth_class_name[];
extern const char stelth_real_class_name[];
extern const DelDepthAnimationBinding stelth_attack_binding_desc_a;
extern const DelDepthAnimationBinding stelth_attack_binding_desc_b;
// set_constant_material colors of TObjEneMe3Stelth::render.
extern const NJS_ARGB stelth_render_color_a;
extern const NJS_ARGB stelth_render_color_b;
extern const NJS_ARGB me3_stelth_render_color;
extern const NJS_ARGB me3_stelth_secondary_render_color;
extern const IVec_800F1098 lbl_8043D680;
extern const char stelth_debug_stelth_enable[];
extern const char stelth_debug_stelth_disable[];
extern const char stelth_debug_appear_ground[];
extern const char stelth_debug_appear_roof[];
extern const char stelth_debug_tecniq_attack[];
extern const char stelth_debug_stelth_on[];
extern const char stelth_debug_stelth_off[];
extern const char stelth_debug_warp[];
extern const char stelth_debug_tex_spigell[];
extern const char stelth_debug_tex_berill[];
}
#endif
