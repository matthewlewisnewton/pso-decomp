#ifndef PSO_MISC_TTECRAFOIE_H
#define PSO_MISC_TTECRAFOIE_H

#include "types.h"
#include "pso/effect/TUnk_804CC148.h"

struct TTecRaFoie : public TUnk_804CC148 {
    virtual ~TTecRaFoie();
    virtual void vfunc_6(void *);
    virtual void vfunc_8(void *);
    virtual void vfunc_9();
    virtual void run_task();
    u32 m_ec;
    u16 m_f0;
    u8 _padF2[0x56];
    u32 m_148;
    void calc_area_parameters();
    virtual void render();
    void update_detonation(void *arg1);
    static void create(TObject *parent, void *arg1, void *arg2, void *arg3);
    void create_ex(void *arg1, void *arg2, void *arg3);
};

typedef char TTecRaFoie_size[sizeof(TTecRaFoie) == 0x14C ? 1 : -1];
#endif
