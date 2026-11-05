#ifndef PSO_MISC_TOBOSS4BIRD_H
#define PSO_MISC_TOBOSS4BIRD_H

#include "types.h"
#include "pso/misc/TOBoss4.h"

struct TOBoss4Bird : public TOBoss4 {
    virtual ~TOBoss4Bird();
    u32 m_98;
    u8 _pad9C[0x18];
    u32 m_b4;
    u32 m_b8;
    u32 m_bc;
    u32 m_c0;
    void* m_c4;
    u8 _padC8[0x14];
    u32 m_dc;
    u32 m_e0;
    u32 m_e4;
    virtual void run_task();
    virtual void render();
    static void *create(void *arg0);
};

typedef char TOBoss4Bird_size[sizeof(TOBoss4Bird) == 0xE8 ? 1 : -1];
#endif
