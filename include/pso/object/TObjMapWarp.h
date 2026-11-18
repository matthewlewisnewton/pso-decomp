#ifndef PSO_OBJECT_TOBJMAPWARP_H
#define PSO_OBJECT_TOBJMAPWARP_H
#include "types.h"
#include "pso/object/TObjWarpBase.h"
struct TObjMapWarp : public TObjWarpBase {
    virtual ~TObjMapWarp();
    virtual void vfunc_14();
    virtual void draw_debug_destinations();
    virtual void closePlayerWindow(u16);
    u8 unk_AC[0x4];
    void * m_b0;
    u32 m_b4;
    u8 unk_B8[0x4];
    f32 destinations[4][3];
    void* playerPopups[4];
    static u8 can_warp(s32 arg0, u16 arg1);
    virtual void open_confirm_window(s32 client_id);
    void process_player_warps();
};
#endif
