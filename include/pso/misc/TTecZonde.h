#ifndef PSO_MISC_TTECZONDE_H
#define PSO_MISC_TTECZONDE_H

#include "types.h"
#include "pso/effect/TUnk_804CCC68.h"

struct TTecZonde : public TUnk_804CCC68 {
    virtual ~TTecZonde();
    virtual void vfunc_8(void *);
    void init_parameters();
    void render();
    void run_task();
    u8 unk_130[0x5C];
};

typedef char TTecZonde_size[sizeof(TTecZonde) == 0x18C ? 1 : -1];
#endif
