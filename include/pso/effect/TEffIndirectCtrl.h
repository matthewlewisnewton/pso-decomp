#ifndef PSO_MISC_TEFFINDIRECTCTRL_H
#define PSO_MISC_TEFFINDIRECTCTRL_H

#include "types.h"
#include "pso/TObject.h"

struct TEffIndirectRecipe {
    u8 m_0;
    s8 m_1;
    s8 m_2;
    s8 m_3;
    s8 m_4;
    s8 m_5;
    u8 m_6;
    u8 m_7;
};

typedef char TEffIndirectRecipe_size[sizeof(TEffIndirectRecipe) == 0x8 ? 1 : -1];

struct TEffIndirectCtrl : public TObject {
    virtual ~TEffIndirectCtrl();
    void sub_802A955C();
    virtual void run_task();
    u32 m_1c;
    TEffIndirectRecipe* m_20;
    u8 m_24;
    u8 m_25;
    u8 _pad26[0x2];
    u32 m_28;
    u32 m_2c;
    void* m_30;
    u8 _pad34[0x8];
    u32 m_3c;
    u32 m_40;
    u16 m_44;
    u16 m_46;
    static void free_buffers();
    virtual void render();
    void copy_and_flush_texture(s32 arg1);
    static void free_all();
    void update_scroll_mode();
    void eff_indirect_update_and_flush();
    void update_eff_indirect();
    f32 m_48;
    f32 m_4c;
    f32 m_50;
};

typedef char TEffIndirectCtrl_size[sizeof(TEffIndirectCtrl) == 0x54 ? 1 : -1];

// Scene object that registers the indirect controller for its kind
// (constructed by fn_802A8210). Only the destructor is its own virtual.
struct TUnk_804DDF04 : public TObject {
    s8 m_kind;
    virtual ~TUnk_804DDF04();
};

extern "C" {
void TEffIndirectCtrl__sub_802A9548(void *p);
u8 TEffIndirectCtrl__sub_802A9554(void *p);
u16 get_indirect_tile_coord(u8 arg0, s32 arg1);
}
void load_indirect_info(void);

#endif
