#ifndef PSO_OBJECT_TOBJLABOMAPWARP_H
#define PSO_OBJECT_TOBJLABOMAPWARP_H

#include "types.h"
#include "pso/object/TObjMapWarp.h"

struct TObjLaboMapWarp : public TObjMapWarp {
    virtual ~TObjLaboMapWarp();
    virtual void draw_debug_destinations();
    virtual void run_task();
    virtual void render();
    int is_field88_zero();
    void clamp_index();
    static void release_static_resource();
    static void load_static_resource();
    static void *create(void *arg0);
    u8 unk_FC[0x4];
};

typedef char TObjLaboMapWarp_size[sizeof(TObjLaboMapWarp) == 0x100 ? 1 : -1];
#endif
