#ifndef PSO_TBOSS6CRUSHROCK_H
#define PSO_TBOSS6CRUSHROCK_H

#include "pso/TObject.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <stddef.h>

struct GinjaTextureList;

class TBoss6CrushRock : public TObject {
public:
    virtual ~TBoss6CrushRock();
    virtual void run_task();
    virtual void render();

    static s32 is_falz_alive();

    struct Angles { s32 x, y, z; };
    void *model;                      // 0x1C
    GinjaTextureList *texture_list;    // 0x20
    Vec position;                     // 0x24
    Vec velocity;                     // 0x30
    Angles angles;                    // 0x3C
    Angles angular_velocity;          // 0x48
};

typedef char CrushRockSize[sizeof(TBoss6CrushRock) == 0x54 ? 1 : -1];
typedef char CrushRockPosition[offsetof(TBoss6CrushRock, position) == 0x24 ? 1 : -1];
typedef char CrushRockVelocity[offsetof(TBoss6CrushRock, velocity) == 0x30 ? 1 : -1];
typedef char CrushRockAngles[offsetof(TBoss6CrushRock, angles) == 0x3C ? 1 : -1];
typedef char CrushRockAngularVelocity[offsetof(TBoss6CrushRock, angular_velocity) == 0x48 ? 1 : -1];

#endif
