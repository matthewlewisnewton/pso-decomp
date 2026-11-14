#ifndef PSO_MISC_TPHOTONLINE_H
#define PSO_MISC_TPHOTONLINE_H

#include "pso/player/TObjChara.h"

struct PhotonLineParams {
    Vec position;
    Vec direction;
    f32 speed;
    f32 hit_scale;
};

struct TPhotonLine : public TObjChara {
    TPhotonLine(PhotonLineParams *params, TObject *parent, u16 owner_id);
    virtual ~TPhotonLine();
    virtual void run_task();
    virtual void render();

    Vec velocity;
    u8 unk_340[4];
    f32 hit_scale;
    u8 unk_348[8];
    TObjCollidable *owner;
    u16 hit_ids[10];
    u16 hit_count;
    u8 unk_36A[0xE];
};

typedef char PhotonLineParams_size[sizeof(PhotonLineParams) == 0x20 ? 1 : -1];
typedef char TPhotonLine_size[sizeof(TPhotonLine) == 0x378 ? 1 : -1];
typedef char TPhotonLine_velocity_offset[offsetof(TPhotonLine, velocity) == 0x334 ? 1 : -1];
typedef char TPhotonLine_hit_scale_offset[offsetof(TPhotonLine, hit_scale) == 0x344 ? 1 : -1];
typedef char TPhotonLine_owner_offset[offsetof(TPhotonLine, owner) == 0x350 ? 1 : -1];
typedef char TPhotonLine_hit_ids_offset[offsetof(TPhotonLine, hit_ids) == 0x354 ? 1 : -1];
typedef char TPhotonLine_hit_count_offset[offsetof(TPhotonLine, hit_count) == 0x368 ? 1 : -1];
#endif
