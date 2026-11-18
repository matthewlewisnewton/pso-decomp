#ifndef PSO_OBJECT_TOBJMAPWARPFOREST_H
#define PSO_OBJECT_TOBJMAPWARPFOREST_H
#include "types.h"
#include "pso/object/TObjMapWarp.h"
struct ForestWarpMotion { u32 data,frameCount; };
struct TObjMapWarpForest : public TObjMapWarp {
    f32 frame;
    void* baseModel;
    void* beamModel;
    ForestWarpMotion* motion;
    void* textures;
    virtual void run_task();
    virtual void render();
    // run_task is the first virtual definition in the unit that owns the table.
    virtual ~TObjMapWarpForest();
};
typedef char ForestWarpSize[sizeof(TObjMapWarpForest)==0x110?1:-1];
#endif
