#ifndef PSO_TBOSS5GRYPHONLIGHTNING_H
#define PSO_TBOSS5GRYPHONLIGHTNING_H

#include "pso/TObject.h"
#include "pso/system/vector.h"
#include <stddef.h>

struct GryphonLightningPoint {
    Vec position;
    f32 field_c;
};

class TBoss5GryphonLightning : public TObject {
public:
    TBoss5GryphonLightning(TObject *parent, f32 parameter, const Vec *source);
    virtual ~TBoss5GryphonLightning();
    void spawn_gryphon_lightning();

    f32 m_1c;
    Vec position_a;
    Vec position_b;
    void *m_38;
    void *m_3c;
    void *m_40;
    void *m_44;
    GryphonLightningPoint points[4];
    f32 m_88;
    f32 m_8c;
    s32 m_90;
    s32 m_94;
};

typedef char GryphonLightningPointSize[sizeof(GryphonLightningPoint) == 0x10 ? 1 : -1];
typedef char GryphonLightningParameter[offsetof(TBoss5GryphonLightning, m_1c) == 0x1C ? 1 : -1];
typedef char GryphonLightningPositionA[offsetof(TBoss5GryphonLightning, position_a) == 0x20 ? 1 : -1];
typedef char GryphonLightningPositionB[offsetof(TBoss5GryphonLightning, position_b) == 0x2C ? 1 : -1];
typedef char GryphonLightningParticles[offsetof(TBoss5GryphonLightning, m_38) == 0x38 ? 1 : -1];
typedef char GryphonLightningPoints[offsetof(TBoss5GryphonLightning, points) == 0x48 ? 1 : -1];
typedef char GryphonLightningProgressA[offsetof(TBoss5GryphonLightning, m_88) == 0x88 ? 1 : -1];
typedef char GryphonLightningProgressB[offsetof(TBoss5GryphonLightning, m_8c) == 0x8C ? 1 : -1];
typedef char GryphonLightningPointCount[offsetof(TBoss5GryphonLightning, m_90) == 0x90 ? 1 : -1];
typedef char GryphonLightningCounter[offsetof(TBoss5GryphonLightning, m_94) == 0x94 ? 1 : -1];
typedef char GryphonLightningSize[sizeof(TBoss5GryphonLightning) == 0x98 ? 1 : -1];

#endif
