#ifndef PSO_ENEMY_BALCLAW_TOBJENEBALCLAWBODY_H
#define PSO_ENEMY_BALCLAW_TOBJENEBALCLAWBODY_H

#include "types.h"
#include "pso/enemy/balclaw/TObjEneBalClaw.h"

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
    virtual void render();
    virtual void vfunc_60();
    virtual void vfunc_58();
    int get_flag_0x388_b24();
    int reset_enemy_state();
    void update_move_to_target();
    void run_death_sequence();
    void sub_8008DC90();
    void sub_8008FC0C();
    void sub_8008FC10();
    void sub_8008FF50();
    void update_dragon_boss_state();
    static void *create(void *set_data);
    u8 pad_3c0[0x4];
    u32 child_ids[4];      // entity ids; the dtor destroys the first m_3d8 of them
    u8 pad_3d4[0x4];
    s16 m_3d8;             // how many of child_ids are in use (the ctor sets 4)
    u8 pad_3da[0x2];
    TObject *parts[4];     // queue_destruction'd by the dtor
    u8 pad_3ec[0x18];
};

typedef char TObjEneBalClawBody_size[sizeof(TObjEneBalClawBody) == 0x404 ? 1 : -1];
#endif
