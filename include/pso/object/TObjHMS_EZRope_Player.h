#ifndef PSO_OBJECT_TOBJHMS_EZROPE_PLAYER_H
#define PSO_OBJECT_TOBJHMS_EZROPE_PLAYER_H
#include "types.h"
#include "pso/TObjEZRopeBase.h"

class TObjPlayer;

struct RopePlayerSegmentSource {
    s8 type;
    u8 pad1[0x13];
    u8 *data;
};

struct RopePlayerSphereSource {
    s8 type;
    u8 pad1[0x13];
};

class TObjHMS_EZRope_Player : public TObjEZRopeBase {
public:
    TObjHMS_EZRope_Player(TObjPlayer *player, void *segment_sources, void *sphere_sources);
    virtual ~TObjHMS_EZRope_Player();
    virtual void run_task();
    virtual void render();
    void sub_800FF2D0();
    TObjPlayer *player;
    RopePlayerSegmentSource *segment_sources;
    RopePlayerSphereSource *sphere_sources;
    RopeSegment *segment_storage;
    RopeAnchor *anchor_storage;
    RopeCollisionSphere *sphere_storage;
};
typedef char TObjHMS_EZRope_Player_size[sizeof(TObjHMS_EZRope_Player) == 0x48 ? 1 : -1];

#endif
