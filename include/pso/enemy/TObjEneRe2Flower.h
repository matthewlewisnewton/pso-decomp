#ifndef PSO_ENEMY_TOBJENERE2FLOWER_H
#define PSO_ENEMY_TOBJENERE2FLOWER_H

#include "types.h"
#include "pso/enemy/TObjEneDD_ST.h"
#include "pso/misc/MaterialOpacityFade.h"

struct TObjEneRe2Flower : public TObjEneDD_ST {
    TObjEneRe2Flower(TObject *parent, void *setData);
    virtual ~TObjEneRe2Flower();
    virtual void run_task();
    virtual void render();
    virtual void vfunc_88();
    virtual void vfunc_105();
    virtual void vfunc_106();
    void sub_800C3DC4();
    s32 sub_800C3B8C();
    void dispatch_action(s32);
    virtual void dispatch_action(u32 state, s32 reason);
    void vfunc_63();
    void vfunc_62();
    void vfunc_61();
    void vfunc_28();
    s32 renderRotationY;
    u32 flowerFlags;
    f32 renderOffsetY;
    u32 m_3cc;
    u32 m_3d0;
    u32 m_3d4;
    u32 m_3d8;
    Vec renderAnchors[2];
    MaterialOpacityFade fade;
    u32 m_410;
    u32 m_414;
    u32 m_418;
    u32 m_41c;
    u32 m_420;
    f32 m_424;
    TObject *m_428;
    void handle_event(s32 arg1);
    void begin_state_242();
    s32 check_hit_flag();
    void clear_child_flags();
    void set_child_flags();
    u8 *find_target_in_range();
    static void initialize_resources();
    static void destroy_instance();
    static void *create(void *arg0);
    int get_flag_11();
};

typedef char TObjEneRe2Flower_size[sizeof(TObjEneRe2Flower) == 0x42C ? 1 : -1];
typedef char FlowerRotationOffset[offsetof(TObjEneRe2Flower, renderRotationY) == 0x3C0 ? 1 : -1];
typedef char FlowerFlagsOffset[offsetof(TObjEneRe2Flower, flowerFlags) == 0x3C4 ? 1 : -1];
typedef char FlowerAnchorsOffset[offsetof(TObjEneRe2Flower, renderAnchors) == 0x3DC ? 1 : -1];
typedef char FlowerFadeOffset[offsetof(TObjEneRe2Flower, fade) == 0x3F4 ? 1 : -1];
typedef char FlowerChildOffset[offsetof(TObjEneRe2Flower, m_428) == 0x428 ? 1 : -1];
#endif
