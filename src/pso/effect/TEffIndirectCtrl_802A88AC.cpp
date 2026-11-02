#include "pso/system/GinjaTextureInput.h"
#include "types.h"
#include <stdlib.h>
#include "pso/player/demo_mode.h"
#include "pso/effect/TEffIndirectCtrl.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/system/memory.h"

#include "pso/player/TObjPlayer.h"
#include "pso/effect/TUnk_804DDF04.h"
#include "pso/unk/text_802A8210.h"
#include "pso/player/TObjPlayer_802A8368.h"
#include "pso/effect/TEffIndirectCtrl_802A88AC.h"

// Original table entries are native PMFs with this controller as their receiver.
typedef void (TEffIndirectCtrl::*IndirectTask)();
struct IndirectTaskTable { IndirectTask entries[3]; };
typedef char IndirectTask_size[sizeof(IndirectTask) == 12 ? 1 : -1];
typedef char IndirectTaskTable_size[sizeof(IndirectTaskTable) == 36 ? 1 : -1];
extern "C" {
extern s32 actor_frame_tick;
}

struct RecoveredGlobal_802A9234_TEffIndirectCtrl__data_80540AF0 {
    s32 value;
    u8 remaining[0x1C];
};

struct RecoveredGlobal_802A925C_TEffIndirectCtrl__data_80540AF0 {
    s32 value;
    u8 remaining[0x1C];
};

struct P2C_802A8B58 { void *a; s32 b; };

struct Ctrl_802A8B58 {
    s32 f0;
    u8 pad4[0x18 - 4];
    void *vt;
    u32 f1c;
    u8 *f20;
    u8 f24;
    u8 f25;
    u8 pad26[2];
    void *f28;
    P2C_802A8B58 *f2c;
    u8 f30[0xC];
    s32 f3c;
    s32 f40;
    s16 f44;
    s16 f46;
    f32 f48;
    f32 f4c;
    f32 f50;
};

struct Cell_802A8FD8
{
  u16 idx;
  u16 val;
};

extern RecoveredGlobal_802A9234_TEffIndirectCtrl__data_80540AF0 TEffIndirectCtrl__source_buffers;
extern "C" {
f32 sin_table_lookup(s32);
void __ct__7TObjectFP7TObject(void *, void *);
u8 *get_indirect_recipe(u8);
void set_texture_name(void *, void *, void *, s32);
void load_texture_list(void *);
extern s32 __vt__16TEffIndirectCtrl[];
extern s32 TEffIndirectCtrl__name;
extern const f32 lbl_805DE024;
Ctrl_802A8B58 *TEffIndirectCtrl__ct(Ctrl_802A8B58 *self, s32 kind, void *parent);
s32 DCFlushRange(s32, s32);
void release_texture_list(void *);
s32 memcpy(s32, s32, s32);

}

typedef char RecoveredGlobal_802A9234_TEffIndirectCtrl__data_80540AF0_size[sizeof(RecoveredGlobal_802A9234_TEffIndirectCtrl__data_80540AF0) == 0x20 ? 1 : -1];

typedef struct Cell_802A8FD8 Cell_802A8FD8;

typedef char RecoveredGlobal_802A925C_TEffIndirectCtrl__data_80540AF0_size[sizeof(RecoveredGlobal_802A925C_TEffIndirectCtrl__data_80540AF0) == 0x20 ? 1 : -1];

#include "pso/system/CurrentTextureList.h"
#include "types.h"
#include "pso/effect/TEffIndirectCtrl.h"
#include "pso/player/TObjPlayer.h"
#include "pso/object/TObjFish.h"

struct Ctrl_802A8728 {
    u8 pad0[0x1C];
    s32 buf;
    u8 *recipe;
    u8 index;
    u8 pad25[0x3C - 0x25];
    s32 amp;
    s32 period;
    u16 phase;
    u8 pad46[2];
    f32 rate;
};

#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
struct Tbl5_802A85F0 { s32 v[5]; };

struct Owner_802A85F0 {
    u8 pad[0x2C];
    s32 list;
};

#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
struct Tbl5_802A8448 { s32 v[5]; };

struct Owner_802A8448 {
    u8 pad[0x2C];
    s32 list;
};

extern u8 *indirect_effect_ctrl_table[];
extern u8 indirect_effect_ctrl_count;
extern "C" {
void TObjPlayer__sub_802A841C(void);
void TObjPlayer__sub_802A83F4(void);
s32 DCFlushRange(s32, s32);
void deform_indirect_texture_scroll(u8 *, u32, u32, s32, u32);
s32 get_indirect_source_pixels(u8);
void GXSetIndTexMtx(s32, f32 (*)[3], s32);
void Dolphin_GXSetIndTexCoordScale(s32, s32, s32);
void Dolphin_GXSetIndTexOrder(s32, s32, s32);
void GXSetNumIndStages(s32);
void GXSetTevIndWarp(s32, s32, s32, s32, s32);
}
void load_list_texture(s32, s32, s32, s32);
extern Tbl5_802A85F0 indirect_tev_alternate_coord_table;
extern Tbl5_802A85F0 indirect_tev_scale_table;
extern const f32 lbl_805DE020;
extern const f32 lbl_805DE024;
void setup_indirect_tev_alternate(s32 arg0, s32 unused, s32 sampler, s32 arg3);
extern Tbl5_802A8448 indirect_tev_ordinary_scale_table;
void setup_indirect_tev_ordinary(s32 arg0, s32 sampler, s32 scale, s32 second);
void deform_indirect_texture_wave(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5);
void update_indirect_texture_wave(s32, s32, s32, s32, s32, u8);
extern "C" {
s8 find_indirect_effect_ctrl(s32);

}

u32 indirect_effect_tile_buffer;

extern "C" {
u8 *__nw__7TObjectFUl(u32);
extern s32 tl_01;
void register_indirect_effect_ctrl(s32 kind);
s8 find_indirect_effect_ctrl(s32 arg0);
}

// Deferred generation reverses these definitions while retaining native
// initializer, conversion-pool and vtable emission order.

s32 get_indirect_source_id(u8 arg0) {
    u8 var_r3;
    var_r3 = arg0;
    if (var_r3 >= 8U) {
        var_r3 = 0;
    }
    return *(s32 *)((s8 *)(*(s32 *)((s8 *)(&(*(RecoveredGlobal_802A925C_TEffIndirectCtrl__data_80540AF0 *)&TEffIndirectCtrl__source_buffers).value) + ((var_r3 * 4) & 0x3FC))) + 8);
}

s32 get_indirect_source_pixels(u8 arg0) {
    u8 var_r3;
    var_r3 = arg0;
    if (var_r3 >= 8U) {
        var_r3 = 0;
    }
    return *(s32 *)((s8 *)&TEffIndirectCtrl__source_buffers.value + ((var_r3 * 4) & 0x3FC)) + 0x20;
}

u32 calc_i8_tiled_texel_offset(u8 x, u8 y, u32 w) {
    u32 r = (((x >> 3) & 0x1F) << 5) + (x & 7);
    r += (((y >> 2) & 0x3F) * w) << 2;
    r += (y & 3) << 3;
    return r;
}

void deform_indirect_texture_scroll(u8 *p, u32 px, u32 py, s32 amp, u32 phase) {
  Cell_802A8FD8 buf[64];
  s32 pxm;
  s32 pym;
  s16 off16;
  u32 first;
  u32 flags;
  s32 count;
  u32 start;
  u32 at;
  s32 axis;
  s32 line;
  s32 k;
  s32 offset;
  s32 i;
  s32 j;
  s32 v;
  u32 idx;
  u32 w;
  flags = 0;
  count = 0;
  offset = (s32) (((f32) (u8)amp) * sin_table_lookup((s32) (182.04445f * ((f32) phase))));
  if (px != 0)
  {
    flags |= 1;
    count = 1;
  }
  if (py != 0)
  {
    flags |= 2;
    count++;
  }
  if (flags == 0)
  {
    for (i = 0; i < 64; i++)
    {
      for (j = 0; j < 64; j++)
      {
        v = *p;
        if (((s16) v) != 0xFF)
        {
          v += offset;
          if (((s16) v) >= 0xFF)
          {
            v = 0xFE;
          }
          if (((s16) v) <= 0)
          {
            v = 0;
          }
        }
        *(p++) = v;
      }
    }
    return;
  }
  pxm = px & 63;
  pym = py & 63;
  off16 = offset;
  for (axis = 0; axis < count; axis++)
  {
    first = flags & 1;
    start = (u32) ((first) ? (pxm) : (pym));
    for (line = 0; line < 64; line++)
    {
      off16++;
      off16--;
      at = start;
      for (k = 0; k < 64; k++)
      {
        if (first)
        {
          idx = ((u32 (*)(u8, u8, s32)) get_indirect_tile_coord)(at, line, 64);
        }
        else
        {
          idx = ((u32 (*)(u8, u8, s32)) get_indirect_tile_coord)(line, at, 64);
        }
        w = p[idx];
        if (w != 0xFF)
        {
          w += off16;
          if (w >= 0xFF)
          {
            w = 0xFE;
          }
          if (w <= 0)
          {
            w = 0;
          }
        }
        buf[k].val = w;
        buf[at].idx = idx;
        at++;
        if (at >= 64)
        {
          at -= 64;
        }
      }
      for (k = 0; k < 64; k++)
      {
        p[buf[k].idx] = buf[k].val;
      }
    }
    if (first)
    {
      flags &= ~1;
    }
    else
    {
      flags &= ~2;
    }
  }
}

#pragma push
#pragma fp_contract on
void update_indirect_texture_wave(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5) {
    s32 off;
    s32 x;
    s32 i;
    s32 v;
    s16 row;
    s32 y;
    for (y = 0; y < 64; y++) {
        row = (s32)((f32)(u8)arg2 * sin_table_lookup((s32)(182.04445f * (f32)(u32)(arg4 + y * arg5))));
        for (x = 0; x < 64; x++) {
            off = (s32)((f32)(u8)arg1 * sin_table_lookup((s32)(182.04445f * (f32)(u32)(arg3 + x * arg5))) + (f32)row);
            i = ((s32 (*)(u8, u8, s32))get_indirect_tile_coord)(x, y, 0x40);
            v = ((u8 *)arg0)[i];
            v += off;
            if ((s16)v >= 0xFF) {
                v = 0xFE;
            }
            if ((s16)v <= 0) {
                v = 0;
            }
            ((u8 *)arg0)[i] = v;
        }
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
void deform_indirect_texture_wave(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5) {
    s32 v;
    s32 off;
    s32 y;
    s16 row;
    s32 x;
    for (y = 0; y < 64; y++) {
        row = (s32)((f32)(u8)arg2 * sin_table_lookup((s32)(182.04445f * (f32)(u32)(arg4 + y * arg5))));
        for (x = 0; x < 64; x++) {
            off = (s32)((f32)(u8)arg1 * sin_table_lookup((s32)(182.04445f * (f32)(u32)(arg3 + x * arg5))) + (f32)row);
            v = *(u8 *)arg0;
            if ((s16)v != 0xFF) {
                v = v + off;
                if ((s16)v >= 0xFF) {
                    v = 0xFE;
                }
                if ((s16)v <= 0) {
                    v = 0;
                }
            }
            *(u8 *)arg0 = v;
            arg0++;
        }
    }
}
#pragma pop

Ctrl_802A8B58 *TEffIndirectCtrl__ct(Ctrl_802A8B58 *self, s32 kind, void *parent) {
    u8 *tex;
    u8 k;
    __ct__7TObjectFP7TObject(self, parent);
    self->vt = ((s32 *)&__vt__16TEffIndirectCtrl);
    self->f0 = TEffIndirectCtrl__name;
    self->f28 = ::operator new(0x24);
    self->f2c = (P2C_802A8B58 *)::operator new(8);
    {
    void *obj = self;
    if (self->f2c == NULL || self->f28 == NULL) {
        queue_destruction__7TObjectFv(obj);
        return self;
    }
    }
    self->f46 = 0;
    self->f48 = lbl_805DE024;
    self->f4c = lbl_805DE024;
    self->f3c = 0;
    self->f40 = 0;
    self->f44 = 0;
    self->f50 = lbl_805DE024;
    k = kind;
    self->f25 = kind;
    self->f20 = get_indirect_recipe(k);
    if (self->f20 == NULL) {
        return self;
    }
    self->f24 = self->f20[7];
    tex = (u8 *)get_indirect_source_id(self->f24) + k * 1000;
    self->f2c->a = self->f30;
    self->f2c->b = 1;
    ((GinjaTextureInput *)(self->f28))->configure(0, 1, 0x40, 0x40);
    set_texture_name(self->f30, self->f28, tex, 0x8800000);
    load_texture_list(self->f2c);
    self->f1c = *(u32 *)(*(u8 **)(*(u8 **)((u8 *)self->f2c->a + 8) + 0xC) + 0x20);
    ((TEffIndirectCtrl *)self)->copy_and_flush_texture(get_indirect_source_pixels(self->f24));
    return self;
}

TEffIndirectCtrl::~TEffIndirectCtrl() {
    if (*(void **)((s8 *)this + 0x2C) != NULL) { release_texture_list(*(void **)((s8 *)this + 0x2C)); ::operator delete(*(void **)((s8 *)this + 0x2C)); }
    if (*(void **)((s8 *)this + 0x28) != NULL) { ::operator delete(*(void **)((s8 *)this + 0x28)); }
}

void TEffIndirectCtrl::copy_and_flush_texture(s32 arg1) {
    memcpy(this->m_1c, arg1, 0x1000);
    DCFlushRange(this->m_1c, 0x1000);
}

void TEffIndirectCtrl::run_task() {
    if (!check_demo_mode() && m_46 != 0) {
        return;
    }
    m_3c += ((s8 *)m_20)[4];
    m_40 += ((s8 *)m_20)[5];
    m_48 = ((s8 *)m_20)[1];
    m_4c = ((s8 *)m_20)[2];
    // The original snapshots the native PMFs on the stack before dispatch.
    IndirectTask tasks[3] = {
        &TEffIndirectCtrl::update_scroll_mode,
        &TEffIndirectCtrl::eff_indirect_update_and_flush,
        &TEffIndirectCtrl::update_eff_indirect
    };
    if ((actor_frame_tick & 31) == 0) {
        m_50 = ((s8 *)m_20)[3] * ((1.0f / 32768.0f) * rand());
    }
    if (((u8 *)m_20)[0] < 3) {
        (this->*tasks[((u8 *)m_20)[0]])();
    }
    m_24 = ((u8 *)m_20)[7];
    sub_802A955C();
}

void TEffIndirectCtrl::render() {  }

void TEffIndirectCtrl::eff_indirect_update_and_flush() {
    TEffIndirectCtrl *eff_indirect_ctrl = this;
    eff_indirect_ctrl->copy_and_flush_texture(get_indirect_source_pixels(eff_indirect_ctrl->m_24));
    update_indirect_texture_wave(eff_indirect_ctrl->m_1c, (s32) *(f32 *)((s8 *)eff_indirect_ctrl + 0x48), eff_indirect_ctrl->m_4c, eff_indirect_ctrl->m_3c, eff_indirect_ctrl->m_40, *(u8 *)((s8 *)(*(void **)((s8 *)eff_indirect_ctrl + 0x20)) + 6));
    DCFlushRange(eff_indirect_ctrl->m_1c, 0x1000);
}

void TEffIndirectCtrl::update_eff_indirect() {
    TEffIndirectCtrl *eff_indirect_ctrl = this;
    eff_indirect_ctrl->copy_and_flush_texture(get_indirect_source_pixels(eff_indirect_ctrl->m_24));
    deform_indirect_texture_wave(eff_indirect_ctrl->m_1c, (s32) *(f32 *)((s8 *)eff_indirect_ctrl + 0x48), eff_indirect_ctrl->m_4c, eff_indirect_ctrl->m_3c, eff_indirect_ctrl->m_40, *(u8 *)((s8 *)(*(void **)((s8 *)eff_indirect_ctrl + 0x20)) + 6));
    DCFlushRange(eff_indirect_ctrl->m_1c, 0x1000);
}

void TEffIndirectCtrl::update_scroll_mode() {
    Ctrl_802A8728 *self = (Ctrl_802A8728 *)this;
    s32 rate;
    ((TEffIndirectCtrl *)self)->copy_and_flush_texture(get_indirect_source_pixels(self->index));
    rate = (s32) self->rate;
    self->phase = self->phase + (s8) self->recipe[3];
    deform_indirect_texture_scroll((u8 *)self->buf, self->amp, self->period, rate, self->phase);
    DCFlushRange(self->buf, 0x1000);
}

void setup_indirect_tev_alternate(s32 arg0, s32 unused, s32 sampler, s32 arg3) {
    if ((u8)arg3 < 5) {
        u8 scale = arg3;
        Tbl5_802A85F0 coords = {{0, 1, 2, 3, 4}};
        Tbl5_802A85F0 scales = {{0, 1, 2, 3, 4}};
        f32 mtx[2][3];
        GXSetNumIndStages(1);
        Dolphin_GXSetIndTexOrder(0, coords.v[2], 5);
        Dolphin_GXSetIndTexCoordScale(0, scales.v[scale], scales.v[scale]);
        GXSetTevIndWarp(1, 0, 0, 0, 1);
        mtx[0][0] = lbl_805DE020;
        mtx[0][1] = lbl_805DE024;
        mtx[0][2] = lbl_805DE024;
        mtx[1][0] = lbl_805DE024;
        mtx[1][1] = lbl_805DE020;
        mtx[1][2] = lbl_805DE024;
        GXSetIndTexMtx(1, mtx, 1);
        set_current_texture_list((GinjaTextureList *)(((Owner_802A85F0 *)arg0)->list));
        load_list_texture(0, sampler, sampler, 5);
    }
}

void setup_indirect_tev_ordinary(s32 arg0, s32 sampler, s32 scale, s32 second) {
    Tbl5_802A8448 scales = {{0, 1, 2, 3, 4}};
    f32 m0[2][3];
    f32 m1[2][3];
    GXSetNumIndStages(1);
    Dolphin_GXSetIndTexOrder(0, 0, 5);
    Dolphin_GXSetIndTexCoordScale(0, scales.v[(u8)scale], scales.v[(u8)scale]);
    if (second != 0) {
        static s32 shift = -2;
        static s32 unused = 0;
        static f32 k = lbl_805DE020;
        GXSetTevIndWarp(1, 0, 0, 0, 1);
        m0[0][0] = k;
        m0[0][1] = lbl_805DE024;
        m0[0][2] = lbl_805DE024;
        m0[1][0] = lbl_805DE024;
        m0[1][1] = k;
        m0[1][2] = lbl_805DE024;
        GXSetIndTexMtx(1, m0, (s8)shift);
    } else {
        GXSetTevIndWarp(0, 0, 0, 0, 1);
        m1[0][0] = lbl_805DE020;
        m1[0][1] = lbl_805DE024;
        m1[0][2] = lbl_805DE024;
        m1[1][0] = lbl_805DE024;
        m1[1][1] = lbl_805DE020;
        m1[1][2] = lbl_805DE024;
        GXSetIndTexMtx(1, m1, 1);
    }
    set_current_texture_list((GinjaTextureList *)(((Owner_802A8448 *)arg0)->list));
    load_list_texture(0, sampler, sampler, 5);
}

void TObjPlayer__sub_802A841C(void) {
    s32 i;
    indirect_effect_ctrl_count = 0;
    for (i = 0; i < 6; i++) indirect_effect_ctrl_table[i] = 0;
}

void TObjPlayer__sub_802A83F4(void) {
    s32 i;
    for (i = 0; i < 6; i++) indirect_effect_ctrl_table[i] = 0;
}

void TObjPlayer::play_particle_at_active_slot(s32 arg0, s32 sampler, s32 arg2, s32 arg3, s32 unused, s32 second) {
    s32 indirect_effect_ctrl;

    indirect_effect_ctrl = (s32)(s8) find_indirect_effect_ctrl(arg0);
    if ((indirect_effect_ctrl != -1) && ((u32) indirect_effect_ctrl_table[indirect_effect_ctrl] != 0U)) {
        if (arg3 != 0) {
            setup_indirect_tev_alternate((s32)indirect_effect_ctrl_table[indirect_effect_ctrl], unused, sampler, arg2);
            return;
        }
        setup_indirect_tev_ordinary((s32)indirect_effect_ctrl_table[indirect_effect_ctrl], sampler, arg2, second);
    }
}

s8 find_indirect_effect_ctrl(s32 arg0) {
    s32 i;
    for (i = 0; i < indirect_effect_ctrl_count; i++) {
        if (indirect_effect_ctrl_table[i] != 0) {
            u8 id = TEffIndirectCtrl__sub_802A9554((void *)indirect_effect_ctrl_table[i]);
            if (id == (u8)arg0) {
                if (check_demo_mode() == 0) {
                    TEffIndirectCtrl__sub_802A9548((void *)indirect_effect_ctrl_table[i]);
                }
                return i;
            }
        }
    }
    return -1;
}
void register_indirect_effect_ctrl(s32 kind) {
    u8 *p;
    if (find_indirect_effect_ctrl(kind) < 0 && indirect_effect_ctrl_count < 6) {
        p = __nw__7TObjectFUl(0x54);
        if (p != NULL) {
            p = (u8 *)TEffIndirectCtrl__ct((Ctrl_802A8B58 *)p, kind, (void *)tl_01);
        }
        indirect_effect_ctrl_table[indirect_effect_ctrl_count] = p;
        indirect_effect_ctrl_count++;
    }
}
TUnk_804DDF04::TUnk_804DDF04(s32 kind, TObject *parent)
    : TObject(parent), kind(kind) {
    // The registration consumes the full incoming kind, before byte comparison.
    register_indirect_effect_ctrl(kind);
}
TUnk_804DDF04::~TUnk_804DDF04() {}
