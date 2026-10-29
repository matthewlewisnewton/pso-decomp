#ifndef PSO_ENEMY_TOBJENEME1CANADINLEADER_H
#define PSO_ENEMY_TOBJENEME1CANADINLEADER_H

#include "pso/enemy/TObjEneMe1Canadin.h"

struct TObjEneMe1CanadinLeader : public TObjEneMe1Canadin
{
    void run_task();
    s32 m_4cc;
    s32 m_4d0;
    TObjEneMe1Canadin *m_4d4[8];
    s32 m_4f4;
    static void update_formation_state(void *arg0);
    static void *create(void *arg0);
    void set_flag3c8_bit40();
    void set_flag3c8_bit20();
    void set_flag3c8_bit8();
    void set_attack_flag();
    void set_leader_index(s32 arg1, s32 arg2);
    static void update_fade_sequence(void *pv);
    static f32 get_status_value_f32();
    static void *create_canadin(void *arg0, void *arg1, void *arg2, void *arg3);
};

typedef char CanadinLeaderSize[sizeof(TObjEneMe1CanadinLeader) == 0x4F8 ? 1 : -1];
typedef char CanadinLeaderMembersOffset[offsetof(TObjEneMe1CanadinLeader, m_4d4) == 0x4D4 ? 1 : -1];

#endif
