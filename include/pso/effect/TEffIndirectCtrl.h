#ifndef PSO_MISC_TEFFINDIRECTCTRL_H
#define PSO_MISC_TEFFINDIRECTCTRL_H

#include "types.h"
#include "pso/TObject.h"
#include "pso/system/GinjaMaterialState.h"

struct GinjaTextureInput;

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

// One source image from indirect.dat: a 0x20-byte header, then 64x64 I8
// texels.
struct TEffIndirectSource {
    u8 _pad0[0x8];
    s32 texture_id;
    u8 _padC[0x14];
    u8 pixels[0x1000];
};

typedef char TEffIndirectSource_size[sizeof(TEffIndirectSource) == 0x1020 ? 1 : -1];

struct TEffIndirectCtrl : public TObject {
    TEffIndirectCtrl(s32 kind, TObject *parent);
    virtual ~TEffIndirectCtrl();
    void sub_802A955C();
    virtual void run_task();
    u8 *m_1c;
    TEffIndirectRecipe* m_20;
    u8 m_24;
    u8 m_25;
    u8 _pad26[0x2];
    GinjaTextureInput *m_28;
    GinjaTextureList *m_2c;
    GinjaTextureEntry m_30;
    u32 m_3c;
    u32 m_40;
    u16 m_44;
    u16 m_46;
    static void free_buffers();
    virtual void render();
    void copy_and_flush_texture(u8 *src);
    static void free_all();
    void update_scroll_mode();
    void eff_indirect_update_and_flush();
    void update_eff_indirect();
    f32 m_48;
    f32 m_4c;
    f32 m_50;
};

typedef char TEffIndirectCtrl_size[sizeof(TEffIndirectCtrl) == 0x54 ? 1 : -1];

// Scene object that registers the indirect controller for its kind.
// Only the destructor is its own virtual.
struct TUnk_804DDF04 : public TObject {
    u8 m_kind;
    TUnk_804DDF04(s32 kind, TObject *parent);
    virtual ~TUnk_804DDF04();
};

typedef char TUnk_804DDF04_size[sizeof(TUnk_804DDF04) == 0x20 ? 1 : -1];

// Sets up the indirect TEV stage of the controller for obj's kind.
void enable_indirect_tev(TUnk_804DDF04 *obj, s32 sampler, s32 scale, s32 arg3);
// Goes back to direct TEV. obj is not read.
void disable_indirect_tev(TUnk_804DDF04 *obj, s32 direct);

extern "C" {
TEffIndirectRecipe *get_indirect_recipe(s32 i);
void TEffIndirectCtrl__sub_802A9548(TEffIndirectCtrl *ctrl);
u8 TEffIndirectCtrl__sub_802A9554(TEffIndirectCtrl *ctrl);
u32 get_indirect_tile_coord(u8 x, u8 y, s32 width);
}
void load_indirect_info(void);

#endif
