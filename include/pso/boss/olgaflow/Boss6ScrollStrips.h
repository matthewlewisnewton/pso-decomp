#ifndef PSO_BOSS_OLGAFLOW_BOSS6SCROLLSTRIPS_H
#define PSO_BOSS_OLGAFLOW_BOSS6SCROLLSTRIPS_H

#include "types.h"

// UV-scrolled strips owned by TBoss6Type1, TBoss6Type2 and the type-1
// appearance demo. The functions are in TBoss6PlotFalz.cpp.
struct Boss6ScrollStrips {
    void scroll_strips_uv(s32 du, s32 dv);
    void free_buffer_pairs();
};

#endif
