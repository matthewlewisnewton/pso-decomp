#ifndef PSO_TOBJBOSS2RAFTSPLASH_H
#define PSO_TOBJBOSS2RAFTSPLASH_H

#include "pso/TObject.h"
#include "types.h"
#include <dolphin/mtx.h>

class TObjBoss2RaftSplash : public TObject {
public:
    virtual ~TObjBoss2RaftSplash();
    virtual void run_task();

private:
    f32 m_elapsed;
    f32 m_interval;
    const f32 *m_step;
    Vec m_position;
    Vec m_splash_offset;

public:
    // The existing spawn ABI passes vector addresses as 32-bit integers.
    static void spawn_splash(s32 position, s32 particle_index, s32 splash_offset);
};

#endif
