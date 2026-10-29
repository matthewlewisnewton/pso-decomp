#ifndef PSO_ENEMY_TOBJENEBALCLAWBODY_H
#define PSO_ENEMY_TOBJENEBALCLAWBODY_H

#include "types.h"
#include "pso/enemy/TObjEneBalClaw.h"

struct BalClawSetData {
    s16 set_index;
    u8 unknown02[4];
    u16 entity_id;
    s16 room;
    s16 wave;
    u8 unknown0c[4];
    Vec position;
    s32 rotation[3];
    f32 parameters[5];
    s16 variant;
    s16 unknown3e;
};

typedef char BalClawSetData_size[sizeof(BalClawSetData) == 0x40 ? 1 : -1];

struct TObjEneBalClawBody : public TObjEneBalClaw {
    TObjEneBalClawBody(TObject *parent, BalClawSetData *set_data);
    virtual ~TObjEneBalClawBody();
    virtual void run_task();
    virtual void vfunc_60();
    int get_flag_0x388_b24();
    void set_form(s32 form);
    void fn_8008FC0C();
    void reset_enemy_state();
    void update_move_to_target();
    void run_death_sequence();
    void fn_8008DD14();
    void fn_8008E254();
    void fn_8008E310();
    void fn_8008EC3C();
    void fn_8008EDE8();
    void fn_8008F1DC();
    void fn_8008F910();
    void fn_8008FAD0();

    void sub_8008FC10();
    virtual void render();
    void sub_8008FF50();
    void update_dragon_boss_state();
    virtual void vfunc_58();
    f32 m_3c0;
    s32 claw_ids[4];
    s32 action_timer;
    s16 m_3d8;
    s16 m_3da;
    TObject *effects[4];
    u8 unk_3ec[0x18];
    static void *create(void *arg0);
};

typedef char TObjEneBalClawBody_size[sizeof(TObjEneBalClawBody) == 0x404 ? 1 : -1];
#endif
