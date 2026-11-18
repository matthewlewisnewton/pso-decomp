#ifndef PSO_MISC_TWINDOWFUKIDASI_H
#define PSO_MISC_TWINDOWFUKIDASI_H

#include "types.h"
#include <stddef.h>

struct TWindowFukidasi
{
    // Borrowed placement view of the window constructed as TUnk_804CF0B8.
    u8 pad00[0x0C];
    TWindowFukidasi *next;
    u8 pad10[0x10];
    u16 m_20;
    u8 pad22[0x0E];
    f32 position[2];
    f32 size[2];
    f32 m_40; // Left edge tested at 0x80244D98.
    u8 pad44[0x14];
    f32 rise;
    u8 pad5C[0x14];
    u8 m_70;
    u8 m_71;
    u8 m_72;
    u8 m_73;
    u8 _pad74[0x2];
    u16 m_76;
    u32 m_78;
    TWindowFukidasi *find_viewport_overlap(const f32 *position, const f32 *size, s32 viewport);
    TWindowFukidasi *find_overlapping_balloon(const f32 *position, const f32 *size, TWindowFukidasi *first);
    void hide();
    int get_visible_flag();
    int is_bit10_set();
    s32 check_card_match_enabled(s32 arg1);
    void sync_display_pos();
    s32 approach(f32 farg0);
    void get_boundary_offset(s32 angle, f32 *out);
    TWindowFukidasi *find_balloon_overlap_for(TWindowFukidasi *first);
    void rearm_balloon(s32 arg1);
};

typedef char BalloonOverlapNextOffset[offsetof(TWindowFukidasi, next) == 0x0C ? 1 : -1];
typedef char BalloonOverlapPositionOffset[offsetof(TWindowFukidasi, position) == 0x30 ? 1 : -1];
typedef char BalloonOverlapSizeOffset[offsetof(TWindowFukidasi, size) == 0x38 ? 1 : -1];
typedef char BalloonOverlapRiseOffset[offsetof(TWindowFukidasi, rise) == 0x58 ? 1 : -1];

extern "C" {
void sub_802504A8__13TUnk_804CF0B8Fv(void *arg0);
s32 clamp_position__13TUnk_804CF0B8FPvf(void *arg0, void *arg1, f32 farg0);
void complete_speech_balloon(u8 *arg0);
void init_flags__15TWindowFukidasiFPvi(void *arg0, s32 arg1);
s32 is_speech_balloon_ready(u8 *arg0);
void open__15TWindowFukidasiFPvPvi(u8 *arg0, u32 *arg1, s32 arg2);
void set_color__13TUnk_804CF0B8FUs(void *arg0, u16 arg1);
void set_text__15TWindowFukidasiFPvii(u8 *arg0, s32 str, s32 arg2);
}

#endif
