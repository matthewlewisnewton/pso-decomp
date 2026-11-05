#ifndef PSO_MISC_TTECGIBARTA_H
#define PSO_MISC_TTECGIBARTA_H

#include "types.h"
#include "pso/effect/TUnk_804CCC68.h"

struct TTecGiBarta : public TUnk_804CCC68 {
    virtual ~TTecGiBarta();
    virtual void vfunc_8(void *);
    u8 unk_130[0x44];
    u32 m_174;
    void update_technique_by_phase();
    void create_particles();
    void calc_params();
    // Spawn a Gi-Barta cast by owner at pos, aimed at target or along angle.
    static void create(void *owner, Vec *pos, Vec *target, s32 level);
    static void create_ex(void *owner, Vec *pos, s32 angle, s32 level);
    void run_task();
    u8 *construct_facing(void *owner, Vec *pos, s32 angle, s32 level);
    void render();
};
typedef char TTecGiBarta_size[sizeof(TTecGiBarta)==0x178?1:-1];

#endif
