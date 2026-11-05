#ifndef PSO_BOSS_BOSS6SCROLLSTRIPS_H
#define PSO_BOSS_BOSS6SCROLLSTRIPS_H

#include "types.h"

struct StripBufferPair;

// One strip: a model, a node in it, and the texture filter build_tables
// passes to the StripBufferPair constructor.
struct Boss6StripDesc {
    s32 model;
    s32 node;
    s32 c;
};

// UV-scrolled strips owned by TBoss6Type1, TBoss6Type2 and the type-1
// appearance demo. The functions are in TBoss6PlotFalz.cpp.
struct Boss6ScrollStrips {
    s32 count;
    u8 unk_04[0x4];
    s32 u;
    s32 v;
    StripBufferPair **items;
    void scroll_strips_uv(s32 du, s32 dv);
    void free_buffer_pairs();
    void build_tables(Boss6StripDesc *descs, s32 n);
};

#endif
