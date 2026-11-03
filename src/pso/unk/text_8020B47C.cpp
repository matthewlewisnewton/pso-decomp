#include "types.h"
#include "pso/system/byteswap.h"
#include "pso/misc/TLobby.h"

#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off

struct EnemyGroupEntry_8020B47C {
    s32 m_0;
    s32 m_4;
    u8 pad_8[8];
    u8 *m_10;
    u8 *m_14;
};

struct EnemyGroupEnt_8020B47C {
    u8 pad_0[2];
    s16 m_2;
    u8 pad_4[4];
};

extern EnemyGroupEntry_8020B47C TLobby__floor_enemy_group_table[];

extern "C" {

void TLobby__sub_8020B47C(void *arg0) {
    u8 *self = (u8 *)arg0;
    ((TLobby *)self)->bswap_4_words();
    {
        u8 *table;
        s32 n;
        s16 *src;
        s32 i;
        EnemyGroupEnt_8020B47C *d;
        s32 k;
        s32 j;
        EnemyGroupEntry_8020B47C *e;
        table = (u8 *)TLobby__floor_enemy_group_table;
        src = (s16 *)(self + *(u32 *)(self + 0));
        for (i = 0; i < 0x12; i++) {
            e = &((EnemyGroupEntry_8020B47C *)table)[i];
            if (e->m_0 > 0) {
                n = e->m_0;
                d = (EnemyGroupEnt_8020B47C *)e->m_10;
                for (k = 0; k < n; k++) {
                    s16 tmp = *src;
                    bswap_16((u16 *)&tmp);
                    d->m_2 = tmp;
                    d = d + 1;
                    src = src + 1;
                }
            }
        }
    }
    {
        s32 i;
        u8 *table;
        EnemyGroupEnt_8020B47C *d;
        s32 k;
        s16 *src;
        s32 n;
        s32 j;
        EnemyGroupEntry_8020B47C *e;
        table = (u8 *)TLobby__floor_enemy_group_table;
        src = (s16 *)(self + *(u32 *)(self + 8));
        for (i = 0; i < 0x12; i++) {
            e = &((EnemyGroupEntry_8020B47C *)table)[i];
            if (e->m_4 > 0) {
                n = e->m_4;
                d = (EnemyGroupEnt_8020B47C *)e->m_14;
                for (k = 0; k < n; k++) {
                    s16 tmp = *src;
                    bswap_16((u16 *)&tmp);
                    d->m_2 = tmp;
                    d = d + 1;
                    src = src + 1;
                }
            }
        }
    }
}

}
