#ifndef PSO_OBJECT_TOBJMAPFORCEWARP_H
#define PSO_OBJECT_TOBJMAPFORCEWARP_H

#include "types.h"
#include "pso/object/TObjMapWarp.h"

struct TObjMapForceWarp : public TObjMapWarp {
    virtual ~TObjMapForceWarp();
    virtual void run_task();
    void create_warp_id_string(void *);
    virtual void open_confirm_window(s32 client_id);
    virtual s32 vfunc_18(s32 client_id);
    virtual void draw_debug_destinations();
    u32 m_fc;
    virtual void render();
    static void register_warp(void* a0);
};

typedef char TObjMapForceWarp_size[sizeof(TObjMapForceWarp) == 0x100 ? 1 : -1];
#endif
