#ifndef PSO_TEFFSTARLIGHTCHILD_H
#define PSO_TEFFSTARLIGHTCHILD_H
#include "pso/TObject.h"
#include "types.h"
#include "pso/render/ColorLineList.h"
#include <stddef.h>

class TEffStarLightChild : public TObject {
public:
    TEffStarLightChild(ColorLineVertex *a, ColorLineVertex *b, TObject *parent, f32 width, f32 speed);
    virtual ~TEffStarLightChild();
    virtual void run_task();
public:
    virtual void render();
    f32 shrink_distance;
    ColorLineVertex edges[2];
};

typedef char TEffStarLightChildSize[sizeof(TEffStarLightChild) == 0x30 ? 1 : -1];

typedef char StarLightChildOffsets[(offsetof(TEffStarLightChild, shrink_distance) == 0x1C &&
    offsetof(TEffStarLightChild, edges) == 0x20) ? 1 : -1];

#endif
