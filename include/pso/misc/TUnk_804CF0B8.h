#ifndef PSO_MISC_TUNK_804CF0B8_H
#define PSO_MISC_TUNK_804CF0B8_H
#include "types.h"
#include <stddef.h>
#include "pso/misc/TUnk_804CDFE8.h"

// Prefix of the speech-balloon entry list. draw_visible_window_entries reads
// count, then the item pointer, from the address passed as the list.
struct TWindowEntryList {
    u32 count;
    void **items;
};

class TUnk_804CF0B8 : public TUnk_804CDFE8 {
public:
    virtual ~TUnk_804CF0B8();
    void draw_body(void *, u32, f32 *, f32);
    void draw_body_row(void *, void *, f32, f32, f32, f32);
    void draw_tail(void *, u32, f32 *, f32);
    void sub_80251DF0(s16, s32, s16, f32);
    s32 clamp_position(void *, f32);
    void set_color(u16);
    void follow_anchor();
    s32 is_speaker_far_or_offscreen();
    s32 project_anchor(f32 *, f32 *);
    void place_rect_at_head_or_slot();
    void sub_802504A8();
    void calc_text_size(f32 *);
    virtual void render();
    void clear_flag();
    s16 get_field_20();
    int get_flag_bit1();
    s8 alloc_nearest_free_slot();
    int is_balloon_visible();
    int is_active();
    void clear_flag_20();
    int is_flag_set();
    void sub_80252C68();
    void set_flag();
    void clear_visible_flag();
    void clear_flag2c_bit100();
    void set_flag2c_bit200();
    void clear_flag2c_bit200();
    void set_flag2c_bit100();
    u8 unk_1C[0x4];
    u16 m_20;
    u8 unk_22[0x2];
    TWindowEntryList entries;
    u32 m_2c;
    f32 rect[2];
    f32 anchor[2];
    u8 unk_40[0x8];
    f32 m_48;
    f32 unk_4C;
    u8 unk_50[0x4];
    f32 m_54;
    f32 m_58;
    u8 unk_5C[0x14];
    s8 m_70;
    u8 m_71;
    u8 unk_72[0x1];
    s8 m_73;
    u8 unk_74[0x2];
    s16 m_76;
    char *name;
    f32 m_7c;
    f32 tail;
    s32 m_84;
    f32 center[2];
    f32 head[2];
};
typedef char TUnk_804CF0B8_entries_offset[offsetof(TUnk_804CF0B8, entries) == 0x24 ? 1 : -1];
typedef char TUnk_804CF0B8_rect_offset[offsetof(TUnk_804CF0B8, rect) == 0x30 ? 1 : -1];
typedef char TUnk_804CF0B8_anchor_offset[offsetof(TUnk_804CF0B8, anchor) == 0x38 ? 1 : -1];
typedef char TUnk_804CF0B8_m_54_offset[offsetof(TUnk_804CF0B8, m_54) == 0x54 ? 1 : -1];
typedef char TUnk_804CF0B8_name_offset[offsetof(TUnk_804CF0B8, name) == 0x78 ? 1 : -1];
typedef char TUnk_804CF0B8_next_offset[offsetof(TUnk_804CF0B8, m_7c) == 0x7c ? 1 : -1];
typedef char TUnk_804CF0B8_tail_offset[offsetof(TUnk_804CF0B8, tail) == 0x80 ? 1 : -1];
typedef char TUnk_804CF0B8_center_offset[offsetof(TUnk_804CF0B8, center) == 0x88 ? 1 : -1];
typedef char TUnk_804CF0B8_head_offset[offsetof(TUnk_804CF0B8, head) == 0x90 ? 1 : -1];
typedef char TUnk_804CF0B8_pointer_size[sizeof(char *) == 4 ? 1 : -1];
typedef char TUnk_804CF0B8_size[sizeof(TUnk_804CF0B8) == 0x98 ? 1 : -1];

#endif
