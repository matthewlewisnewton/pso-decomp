#define TOBJECT_OUT_OF_LINE_HELPERS

#include "types.h"
#include <string.h>
#include <stdlib.h>
#include "pso/TObject.h"
#include "pso/TMainTask.h"
#include "pso/effect/TEffIndirectCtrl.h"
#include "pso/effect/TEffIndirectCtrl_802A88AC.h"
#include "pso/effect/TEffIndirectCtrl_802A9284.h"
#include "pso/unk/text_802A8210.h"
#include "pso/misc/TScene.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_802A8368.h"
#include "pso/player/TObjPlayer_803DC834.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/object/TObjFish.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/math/AngleLookup.h"
#include "pso/system/memory.h"
#include "pso/system/GinjaTextureInput.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/player/demo_mode.h"

struct Cell_802A8FD8
{
  u16 idx;
  u16 val;
};

extern "C" {
s32 GXSetNumIndStages(s32);
s32 GXSetTevDirect(s32);
void GXSetIndTexMtx(s32, f32 (*)[3], s32);
void Dolphin_GXSetIndTexCoordScale(s32, s32, s32);
void Dolphin_GXSetIndTexOrder(s32, s32, s32);
void GXSetTevIndWarp(s32, s32, s32, s32, s32);
s32 DCFlushRange(s32, s32);
s32 read_disc_file(const char *, void *);
void set_texture_name(void *, void *, void *, s32);
void load_texture_list(void *);
void release_texture_list(void *);
IndirectEffectRecipe *get_indirect_recipe(s32 i);
}
void load_list_texture(s32, s32, s32, s32);

const char *indirect_dat_filename = "indirect.dat";
const char *indinfo_dat_filename = "indinfo.dat";
const char *TEffIndirectCtrl__name = "TEffIndirectCtrl";

s32 TEffIndirectCtrl__source_buffers[8];
TEffIndirectCtrl *indirect_effect_ctrl_table[6];
IndirectEffectRecipe *indirect_recipe_buffer;
u8 indirect_effect_ctrl_count;
u16 *indirect_effect_tile_buffer;

// Built -inline off,deferred: functions come out in reverse source order.

IndirectEffectRecipe *get_indirect_recipe(s32 i) {
    if (i >= 0x40) return 0;
    return &indirect_recipe_buffer[i];
}

void TEffIndirectCtrl::sub_802A955C() { this->m_46 = 1; }

u8 TEffIndirectCtrl__sub_802A9554(TEffIndirectCtrl *ctrl) { return ctrl->m_25; }

void TEffIndirectCtrl__sub_802A9548(TEffIndirectCtrl *ctrl) { ctrl->m_46 = 0; }

void load_indirect_info(void) {
    s32 i;
    s32 j;
    indirect_recipe_buffer = (IndirectEffectRecipe *)xmalloc(0x200);
    memset((void *)indirect_recipe_buffer, 0, 0x200);
    indirect_effect_tile_buffer = (u16 *)xmalloc(0x2000);
    if (indirect_effect_tile_buffer != NULL) {
        i = 0;
        do {
            j = 0;
            do {
                indirect_effect_tile_buffer[i * 0x40 + j] = calc_i8_tiled_texel_offset(j, i, 0x40);
                j++;
            } while (j < 0x40);
            i++;
        } while (i < 0x40);
    }
    read_disc_file(indinfo_dat_filename, (void *)indirect_recipe_buffer);
}

u32 get_indirect_tile_coord(u8 arg0, u8 arg1, s32 width) {
    if (indirect_effect_tile_buffer != NULL) {
        return indirect_effect_tile_buffer[arg0 + ((arg1 << 6) & 0x3FC0)];
    }
    return 0U;
}

void TEffIndirectCtrl::free_buffers() {
    if (indirect_recipe_buffer != NULL) {
        xfree(indirect_recipe_buffer);
        indirect_recipe_buffer = NULL;
    }
    if (indirect_effect_tile_buffer != NULL) {
        xfree(indirect_effect_tile_buffer);
        indirect_effect_tile_buffer = NULL;
    }
}

void load_indirect_dat(void) {
    s32 i;
    s32 fail;
    s32 j;
    u8 *buf;
    u8 *p;
    s32 k;
    fail = 0;
    for (i = 0; i < 8; i++) {
        TEffIndirectCtrl__source_buffers[i] = 0;
    }
    for (i = 0; i < 8; i++) {
        TEffIndirectCtrl__source_buffers[i] = (s32)xmalloc(0x1020);
        if ((u32)TEffIndirectCtrl__source_buffers[i] == 0) {
            fail = 1;
        }
    }
    if (fail != 0) {
        for (j = 0; j < 8; j++) {
            if ((u32)TEffIndirectCtrl__source_buffers[j] != 0) {
                xfree((void *)TEffIndirectCtrl__source_buffers[j]);
                TEffIndirectCtrl__source_buffers[j] = 0;
            }
        }
    }
    p = (u8 *)xmalloc(0x8100);
    if (p != NULL) {
        buf = p;
        if (read_disc_file(indirect_dat_filename, p) == 0x8100) {
            for (k = 0; k < 8; k++) {
                memcpy((void *)TEffIndirectCtrl__source_buffers[k], p, 0x1020);
                p += 0x1020;
            }
            if (buf != NULL) {
                xfree(buf);
            }
            load_indirect_info();
            TObjPlayer__sub_802A841C();
        }
    }
}

void TEffIndirectCtrl::free_all() {
    s32 i;

    TObjPlayer__sub_802A83F4();
    TEffIndirectCtrl::free_buffers();
    for (i = 0; i < 8; i++) {
        if ((u32)TEffIndirectCtrl__source_buffers[i] != 0U) {
            xfree((void *)TEffIndirectCtrl__source_buffers[i]);
            TEffIndirectCtrl__source_buffers[i] = 0;
        }
    }
}

s32 get_indirect_source_id(u8 arg0) {
    u8 index;
    index = arg0;
    if (index >= 8U) {
        index = 0;
    }
    return ((IndirectSourceImage *)TEffIndirectCtrl__source_buffers[index])->id;
}

s32 get_indirect_source_pixels(u8 arg0) {
    u8 index;
    index = arg0;
    if (index >= 8U) {
        index = 0;
    }
    return (s32)((IndirectSourceImage *)TEffIndirectCtrl__source_buffers[index])->pixels;
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
  offset = (s32) (((f32) (u8) amp) * sin_table_lookup((s32) (182.04445f * ((f32) phase))));
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
      at = start;
      for (k = 0; k < 64; k++)
      {
        off16 = offset;
        if (first)
        {
          idx = get_indirect_tile_coord(at, line, 64);
        }
        else
        {
          idx = get_indirect_tile_coord(line, at, 64);
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

s32 update_indirect_texture_wave(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5) {
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
            i = get_indirect_tile_coord(x, y, 0x40);
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

TEffIndirectCtrl::TEffIndirectCtrl(s32 kind, TObject *parent) : TObject(parent) {
    u8 *tex;
    u8 k;
    m_name = TEffIndirectCtrl__name;
    m_28 = (GinjaTextureInput *)::operator new(0x24);
    m_2c = (GinjaTextureList *)::operator new(8);
    if (m_2c == NULL || m_28 == NULL) {
        queue_destruction();
        return;
    }
    m_46 = 0;
    m_48 = 0.0f;
    m_4c = 0.0f;
    m_3c = 0;
    m_40 = 0;
    m_44 = 0;
    m_50 = 0.0f;
    k = kind;
    m_25 = kind;
    m_20 = get_indirect_recipe(k);
    if (m_20 == NULL) {
        return;
    }
    m_24 = m_20->source;
    tex = (u8 *)get_indirect_source_id(m_24) + k * 1000;
    m_2c->entries = &m_30;
    m_2c->count = 1;
    m_28->configure((void *)0, 1, 0x40, 0x40);
    set_texture_name(&m_30, m_28, tex, 0x8800000);
    load_texture_list(m_2c);
    m_1c = (u32)m_2c->entries->texture->surface->pixels;
    copy_and_flush_texture(get_indirect_source_pixels(m_24));
}

TEffIndirectCtrl::~TEffIndirectCtrl() {
    if (m_2c != NULL) {
        release_texture_list(m_2c);
        ::operator delete(m_2c);
    }
    if (m_28 != NULL) {
        ::operator delete(m_28);
    }
}

void TEffIndirectCtrl::copy_and_flush_texture(s32 arg1) {
    memcpy((void *)this->m_1c, (void *)arg1, 0x1000);
    DCFlushRange(this->m_1c, 0x1000);
}

void TEffIndirectCtrl::run_task() {
    if (check_demo_mode() != 0 || m_46 == 0) {
        m_3c += m_20->dx;
        m_40 += m_20->dy;
        m_48 = m_20->amplitude;
        m_4c = m_20->period;
        void (TEffIndirectCtrl::*modes[3])() = {
            &TEffIndirectCtrl::update_scroll_mode,
            &TEffIndirectCtrl::eff_indirect_update_and_flush,
            &TEffIndirectCtrl::update_eff_indirect,
        };
        if ((actor_frame_tick & 0x1F) == 0) {
            m_50 = m_20->scroll * (3.0517578e-05f * rand());
        }
        if (m_20->mode < 3) {
            (this->*modes[m_20->mode])();
        }
        m_24 = m_20->source;
        sub_802A955C();
    }
}

void TEffIndirectCtrl::render() {  }

void TEffIndirectCtrl::eff_indirect_update_and_flush() {
    copy_and_flush_texture(get_indirect_source_pixels(m_24));
    update_indirect_texture_wave(m_1c, (s32)m_48, m_4c, m_3c, m_40, m_20->wave);
    DCFlushRange(m_1c, 0x1000);
}

void TEffIndirectCtrl::update_eff_indirect() {
    copy_and_flush_texture(get_indirect_source_pixels(m_24));
    deform_indirect_texture_wave(m_1c, (s32)m_48, m_4c, m_3c, m_40, m_20->wave);
    DCFlushRange(m_1c, 0x1000);
}

void TEffIndirectCtrl::update_scroll_mode() {
    s32 rate;
    copy_and_flush_texture(get_indirect_source_pixels(m_24));
    rate = (s32)m_48;
    m_44 = m_44 + (s8)m_20->scroll;
    deform_indirect_texture_scroll((u8 *)m_1c, m_3c, m_40, rate, m_44);
    DCFlushRange(m_1c, 0x1000);
}

s32 setup_indirect_tev_alternate(s32 arg0, s32 unused, s32 sampler, s32 arg3) {
    if ((u8)arg3 < 5) {
        u8 scale = arg3;
        s32 coords[5] = {0, 1, 2, 3, 4};
        s32 scales[5] = {0, 1, 2, 3, 4};
        f32 mtx[2][3];
        GXSetNumIndStages(1);
        Dolphin_GXSetIndTexOrder(0, coords[2], 5);
        Dolphin_GXSetIndTexCoordScale(0, scales[scale], scales[scale]);
        GXSetTevIndWarp(1, 0, 0, 0, 1);
        mtx[0][0] = 0.5f;
        mtx[0][1] = 0.0f;
        mtx[0][2] = 0.0f;
        mtx[1][0] = 0.0f;
        mtx[1][1] = 0.5f;
        mtx[1][2] = 0.0f;
        GXSetIndTexMtx(1, mtx, 1);
        set_current_texture_list(((TEffIndirectCtrl *)arg0)->m_2c);
        load_list_texture(0, sampler, sampler, 5);
    }
}


s32 setup_indirect_tev_ordinary(s32 arg0, s32 sampler, s32 scale, s32 second) {
    s32 scales[5] = {0, 1, 2, 3, 4};
    f32 m0[2][3];
    f32 m1[2][3];
    GXSetNumIndStages(1);
    Dolphin_GXSetIndTexOrder(0, 0, 5);
    Dolphin_GXSetIndTexCoordScale(0, scales[(u8)scale], scales[(u8)scale]);
    if (second != 0) {
        static s32 shift = -2;
        static s32 unused = 0;
        static f32 k = 0.5f;
        GXSetTevIndWarp(1, 0, 0, 0, 1);
        m0[0][0] = k;
        m0[0][1] = 0.0f;
        m0[0][2] = 0.0f;
        m0[1][0] = 0.0f;
        m0[1][1] = k;
        m0[1][2] = 0.0f;
        GXSetIndTexMtx(1, m0, (s8)shift);
    } else {
        GXSetTevIndWarp(0, 0, 0, 0, 1);
        m1[0][0] = 0.5f;
        m1[0][1] = 0.0f;
        m1[0][2] = 0.0f;
        m1[1][0] = 0.0f;
        m1[1][1] = 0.5f;
        m1[1][2] = 0.0f;
        GXSetIndTexMtx(1, m1, 1);
    }
    set_current_texture_list(((TEffIndirectCtrl *)arg0)->m_2c);
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
    if ((indirect_effect_ctrl != -1) && (indirect_effect_ctrl_table[indirect_effect_ctrl] != NULL)) {
        if (arg3 != 0) {
            setup_indirect_tev_alternate((s32)indirect_effect_ctrl_table[indirect_effect_ctrl], unused, sampler, arg2);
            return;
        }
        setup_indirect_tev_ordinary((s32)indirect_effect_ctrl_table[indirect_effect_ctrl], sampler, arg2, second);
    }
}

s8 find_indirect_effect_ctrl(s32 kind) {
    s32 i;
    for (i = 0; i < indirect_effect_ctrl_count; i++) {
        if (indirect_effect_ctrl_table[i] != 0) {
            u8 id = TEffIndirectCtrl__sub_802A9554(indirect_effect_ctrl_table[i]);
            if (id == (u8)kind) {
                if (check_demo_mode() == 0) {
                    TEffIndirectCtrl__sub_802A9548(indirect_effect_ctrl_table[i]);
                }
                return i;
            }
        }
    }
    return -1;
}

void register_indirect_effect_ctrl(s32 kind) {
    TEffIndirectCtrl *p;
    if (find_indirect_effect_ctrl(kind) < 0 && indirect_effect_ctrl_count < 6) {
        p = new TEffIndirectCtrl(kind, tl_01);
        indirect_effect_ctrl_table[indirect_effect_ctrl_count] = p;
        indirect_effect_ctrl_count++;
    }
}

TUnk_804DDF04::TUnk_804DDF04(s32 kind, TObject *parent) : TObject(parent) {
    indirect_kind = kind;
    register_indirect_effect_ctrl(kind);
}

TUnk_804DDF04::~TUnk_804DDF04() {
}

void TScene::draw_field_1c(s32 sampler, s32 arg2, s32 arg3) {
    TObjPlayer::play_particle_at_active_slot(m_1c_byte, sampler, arg2, 0, arg3, 0);
}

void TScene::set_indirect_tev(s32 ignored, s32 arg1) {
    if (arg1 != 0) {
        GXSetTevDirect(1);
    } else {
        GXSetTevDirect(0);
    }
    GXSetNumIndStages(0);
    set_ginja_post_texgen_count(0);
}
