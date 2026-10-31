#include "pso/math/VectorNormalize.h"
#include "types.h"
#include "pso/enemy/TObjEneDD_800B9B84.h"
#include "pso/misc/TKeyBoardControl_8000F764.h"
#include "pso/system/vector.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/boss/TObjBoss2Tunnel.h"

extern "C" {
s32 vec3_add_to(void *, void *, f32);
s32 subtract_vector(void *, void *);
extern s32 camera_ctrl_instance;
int is_local_client_floor_leader(void*);
int TObjPlayer__sub_801BA42C(void*);
int freeze_all_players__10TObjPlayerFv(void*);
int is_any_teammate_in_state__10TObjPlayerFv(void*);

extern s32 enable_v2_features;
extern s32 game_difficulty_selection;

s32 TObjEneDD::check_v2_mode() {
    if (((s32) enable_v2_features != 0) && ((s32) game_difficulty_selection == 3)) {
        return 1;
    }
    return 0;
}

int TObjEneDD::get_target_state_a() { return TObjPlayer__sub_801BA42C(this); }
int TObjEneDD::get_target_state_b() { return freeze_all_players__10TObjPlayerFv(this); }

void project_sound_origin_from_camera(s32 arg0, u8 *arg1, f32 farg0) {
    f32 temp_f1;
    VecCopy((Vec *)(arg1), (const Vec *)(arg0));
    subtract_vector(arg1, (void *)(camera_ctrl_instance + 0x178));
    { f32 s = normalize_vector_checked((Vec *)arg1); temp_f1 = s * farg0; }
    *(f32 *)((s8 *)arg1 + 0) = (f32) (*(f32 *)((s8 *)arg1 + 0) * temp_f1);
    *(f32 *)((s8 *)arg1 + 4) = (f32) (*(f32 *)((s8 *)arg1 + 4) * temp_f1);
    *(f32 *)((s8 *)arg1 + 8) = (f32) (*(f32 *)((s8 *)arg1 + 8) * temp_f1);
    vec3_add_to(arg1, (void *)(camera_ctrl_instance + 0x178), temp_f1);
}

int TObjEneDD::query_teammate_state() { return is_any_teammate_in_state__10TObjPlayerFv(this); }
int TObjEneDD::update_lobby_state() { return is_local_client_floor_leader(this); }
u8 TObjEneDD::is_phase_e() {
    return (u8) (get_main_phase() == 0xE);
}
s32 TObjEneDD::is_main_phase_15() {
    return (s32) (get_main_phase() == 0xF);
}

}
