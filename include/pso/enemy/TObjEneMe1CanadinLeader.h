#ifndef PSO_ENEMY_TOBJENEME1CANADINLEADER_H
#define PSO_ENEMY_TOBJENEME1CANADINLEADER_H

#include "types.h"

struct TObjEneMe1CanadinLeader
{
    void run_task();
    u16 m_1c;
    u8 _pad1E[0x6];
    u32 m_24;
    u8 _pad28[0x4];
    s16 m_2c;
    u8 _pad2E[0x2];
    u32 m_30;
    u32 m_34;
    void* m_38;
    u8 _pad3C[0x24];
    u32 m_60;
    u8 _pad64[0x298];
    void* m_2fc;
    u8 _pad300[0x90];
    u32 m_390;
    u8 _pad394[0x2C];
    u32 m_3c0;
    u8 _pad3C4[0x4];
    u32 m_3c8;
    u8 _pad3CC[0x34];
    u32 m_400;
    u8 _pad404[0x64];
    u32 m_468;
    u32 m_46c;
    u32 m_470;
    u8 _pad474[0x40];
    u32 m_4b4;
    u32 m_4b8;
    u8 _pad4BC[0xC];
    u16 m_4c8;
    u8 _pad4CA[0x2];
    u32 m_4cc;
    u32 m_4d0;
    u8 _pad4D4[0x20];
    u32 m_4f4;
    static void update_formation_state(void *arg0);
    static void *create(void *arg0);
    void set_flag3c8_bit40();
    void set_flag3c8_bit20();
    void set_flag3c8_bit8();
    void set_attack_flag();
    void set_leader_index(s32 arg1, s32 arg2);
    static void update_fade_sequence(void *pv);
    static void *create_canadin(void *arg0, void *arg1, void *arg2, void *arg3);
};

#endif
