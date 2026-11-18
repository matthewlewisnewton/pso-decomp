#ifndef PSO_TOBJEZROPEBASE_H
#define PSO_TOBJEZROPEBASE_H

#include "pso/TObject.h"
#include "types.h"
#include <dolphin/mtx.h>

struct RopeSegment {
    s8 point_count;
    Vec step;
    void *segment_model;
    void *end_model;
};

struct RopeAnchor {
    s32 yaw;
    Vec position;
};

struct RopeCollisionSphere {
    f32 radius;
    Vec center;
};

class TObjEZRopeBase : public TObject {
public:
    TObjEZRopeBase(TObject *parent);
    virtual ~TObjEZRopeBase();
    void sub_800FF8CC(RopeSegment *segments, RopeAnchor *anchors, RopeCollisionSphere *spheres);
    void sub_800FF788(const Vec *offset);

    s32 segment_count;
    RopeSegment *segments;
    RopeAnchor *anchors;
    RopeCollisionSphere *collision_spheres;
    Vec *points;

private:
    void sub_800FF580(Vec *point, f32 segment_length);
};

#endif
