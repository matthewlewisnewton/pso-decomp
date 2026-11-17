#ifndef PSO_MISC_TQUADSPRITENORMAL_H
#define PSO_MISC_TQUADSPRITENORMAL_H

#include "types.h"
#include "pso/unk/TUnk_804C57F0.h"

struct TQuadSpriteNormal : public TUnk_804C57F0 {
    virtual ~TQuadSpriteNormal();
    virtual void render();
};

struct ParticleDefinition;

extern "C" void *TQuadSpriteNormal__ct(void *storage, TObject *parent, ParticleDefinition *definition);

typedef char TQuadSpriteNormal_size[sizeof(TQuadSpriteNormal) == 0x2C ? 1 : -1];
#endif
