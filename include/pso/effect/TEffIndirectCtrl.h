#ifndef PSO_MISC_TEFFINDIRECTCTRL_H
#define PSO_MISC_TEFFINDIRECTCTRL_H

#include "types.h"
#include "pso/TObject.h"
#include "pso/system/GinjaMaterialState.h"
#include "pso/system/GinjaTextureInput.h"

// One 8-byte record from indinfo.dat. run_task reads the bytes in this order.
struct IndirectEffectRecipe {
    u8 mode;
    s8 amplitude;
    s8 period;
    s8 scroll;
    s8 dx;
    s8 dy;
    u8 wave;
    u8 source;
};

typedef char IndirectEffectRecipe_size[sizeof(IndirectEffectRecipe) == 8 ? 1 : -1];

// One 0x1020-byte record from indirect.dat: a 0x20 header and a 64x64 I8 image.
struct IndirectSourceImage {
    u8 prefix[8];
    s32 id;
    u8 reserved[0x14];
    u8 pixels[0x1000];
};

typedef char IndirectSourceImage_size[sizeof(IndirectSourceImage) == 0x1020 ? 1 : -1];

// Scene-side handle of an indirect effect: its constructor registers a TEffIndirectCtrl for `kind`
// (register_indirect_effect_ctrl). Class name is the placeholder of the vtable it installs (0x804DDF04).
struct TUnk_804DDF04 : public TObject {
    TUnk_804DDF04(s32 kind, TObject *parent);
    virtual ~TUnk_804DDF04();
    u8 indirect_kind; // inferred: the kind passed to register_indirect_effect_ctrl
};

typedef char TUnk_804DDF04_size[sizeof(TUnk_804DDF04) == 0x20 ? 1 : -1];

struct TEffIndirectCtrl : public TObject {
    virtual ~TEffIndirectCtrl();
    TEffIndirectCtrl(s32 kind, TObject *parent);
    void sub_802A955C();
    virtual void run_task();
    u32 m_1c;
    IndirectEffectRecipe *m_20;
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
    void copy_and_flush_texture(s32 arg1);
    static void free_all();
    void update_scroll_mode();
    void update_eff_indirect();
    void eff_indirect_update_and_flush();
    f32 m_48;
    f32 m_4c;
    f32 m_50;
};

typedef char TEffIndirectCtrl_size[sizeof(TEffIndirectCtrl) == 0x54 ? 1 : -1];


extern "C" {
void TEffIndirectCtrl__sub_802A9548(TEffIndirectCtrl *ctrl);
u8 TEffIndirectCtrl__sub_802A9554(TEffIndirectCtrl *ctrl);
u32 get_indirect_tile_coord(u8 x, u8 y, s32 width);
}
void load_indirect_info(void);

#endif
