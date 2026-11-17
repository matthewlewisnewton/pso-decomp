#include "pso/TObjBoss2RaftSplash.h"
#include "pso/system/vector.h"

extern const f32 lbl_805D85B0;

void TObjBoss2RaftSplash::run_task() {
    Vec position;
    m_elapsed += *m_step;
    f32 elapsed = m_elapsed;
    f32 interval = m_interval;
    if (elapsed >= interval) {
        m_elapsed = elapsed - interval;
        VecCopy(&position, &m_position);
        position.y += *m_step - lbl_805D85B0;
        spawn_splash((s32)&position, 0x170, (s32)&m_splash_offset);
    }
}

TObjBoss2RaftSplash::~TObjBoss2RaftSplash() {}

#ifdef __MWERKS__
__declspec(section ".sdata2")
#endif
const f32 lbl_805D85B0 = 9.259259f;
