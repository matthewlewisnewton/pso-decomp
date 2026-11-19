#ifndef PSO_ENEMY_DD_TOBJENEDD_ST_H
#define PSO_ENEMY_DD_TOBJENEDD_ST_H
#include "types.h"
#include "pso/enemy/dd/TObjEneDD.h"

class TObjEneDD_ST : public TObjEneDD {
public:
    u16 target_entity_id;
    TObjChara *current_target;
    Vec target_destination;
    Vec target_direction;
    f32 target_distance;
    s32 acquisition_counter;
    s32 acquisition_period;
    s32 validation_counter;
    s32 validation_period;

    TObjEneDD_ST(TObject *parent);
    virtual ~TObjEneDD_ST();
    f32 get_motion_frame();
    void draw_with_alt_model(s32);
    void set_active();
    void init_float_params();
    void set_target_player(void *);
    void enemy_clear_target(u16);
    void enemy_init_acquire_period(s32);
    s32 select_and_apply_target(f32);
    s32 select_nearest_target(f32);
    s32 enemy_tick_target_acquisition(s32 *, s32, f32);
    s32 update_linked_position(f32);
    void enemy_copy_target_destination();
    void enemy_init_validate_period(s32);
    virtual s32 vfunc_83();
    virtual s32 vfunc_104(f32);
    void sub_800F5874(s32);
    void sub_800F5864(s32);
    s32 check_target_validity();
    s32 enemy_check_target_valid();
    s32 enemy_has_live_target();
};


typedef char TObjEneDD_ST_size_check[sizeof(TObjEneDD_ST) == 0x3C0 ? 1 : -1];

extern "C" s32 enemy_validate_retained_target(TObjEneDD_ST *enemy);

#endif
