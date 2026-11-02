#ifndef PSO_TENDINGPIC_H
#define PSO_TENDINGPIC_H
#include "pso/TObject.h"
#include "types.h"

class TEndingPic : public TObject {
public:
    virtual ~TEndingPic();
    virtual void run_task();
    virtual void render();
public:
    void advance_animation_state();
    void draw_current_pic();
    void init_positions();
    void send_obj_position_event(s32 arg1);
    void set_phase_18();
    void update_player_object();
    void update_shield();
    // Ending item use-effect steps, dispatched by technique index through a
    // member-function-pointer table in TUnk_804F112C::apply_use_effect.
    void sub_803530A0();
    void sub_80353110();
    void sub_80353134();
    void sub_80353194();
    void sub_803531D0();
    void sub_803531F8();
};

#endif
