#ifndef PSO_UNK_TEXT_8036BDA0_H
#define PSO_UNK_TEXT_8036BDA0_H

#include "types.h"
#include "pso/protocol/protocol_types.h"
#include "pso/player/TechniqueCastState.h"

struct G_CastTechnique_6x47 {
    G_ClientIDHeader header;
    s8 technique_number;
    u8 unused;
    u8 level;
    s8 target_count;
    TechniqueTarget targets[10];
    G_CastTechnique_6x47 *init();
    void bswap();
};

s32 validate_6x47_cast_technique(G_CastTechnique_6x47 *packet);

#endif
