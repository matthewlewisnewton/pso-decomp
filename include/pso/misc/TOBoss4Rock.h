#ifndef PSO_MISC_TOBOSS4ROCK_H
#define PSO_MISC_TOBOSS4ROCK_H

#include "types.h"
#include "pso/system/ArrayAllocation.h"
#include "pso/misc/TOBoss4.h"

struct TOBoss4Rock : public TOBoss4 {
    virtual ~TOBoss4Rock();
    u8 unk_98[0x4];
    u32 m_9c;
    u32 m_a0;
    u32 m_a4;
    u32 m_a8;
    u32 m_ac;
    u32 m_b0;
    u32 m_b4;
    virtual void run_task();
    virtual void render();
    static void *create(void *arg0);
};

typedef char TOBoss4Rock_size[sizeof(TOBoss4Rock) == 0xB8 ? 1 : -1];
#endif
