#ifndef PSO_MISC_TUNK_804CE018_H
#define PSO_MISC_TUNK_804CE018_H
#include "types.h"
#include <stddef.h>
#include "pso/TObject.h"

// Shared window image from 0x1C through 0x5F. Descendants used to declare this
// prefix themselves; it lives here so setup_window_draw_context can name the
// floats it passes to open_singleton. The class ends at 0x60.
class TUnk_804CE018 : public TObject {
public:
    virtual ~TUnk_804CE018();
    void draw_window_frame(void *);
    void draw_window_frame_strips(void *, void *);
    void draw_message_frame_row(void *, void *);
    void resort_window_order();
    void calc_inner_rect(u8 *);
    void sub_8026CC28();
    void update_window_entry_list(void *);
    void update_fade();
    void draw_quest_message_frame(void *);
    void sub_80244F2C(u8 *, u8 *, s16);
    s32 setup_window_draw_context(s32);
    s32 is_window_reveal_complete();
    s32 sub_80244994();
    void save_position();
    f32 get_scale();
    s32 sub_80246948();
    void *get_array_entry(int);
    virtual void render();
    virtual void run_task();

    // get_scale and resort_window_order read 0x1C as the window's depth;
    // TWindowSubStatusDisp keeps byte state in the same word.
    union { f32 m_depth; s8 frame_pad_1c[4]; };
    union { s16 m_20; u16 m_20u; };
    s16 unk_22;
    void *m_24;
    u8 frame_pad_28[2];
    s16 m_2a;
    union { s32 m_2c; u32 m_2cu; };
    f32 m_30;
    union { s32 m_34; f32 m_34f; u32 m_34u; };
    f32 m_38;
    union { f32 m_3c; f32 unk_3c; s32 *m_3cp; };
    union { f32 m_40; u32 m_40u; };
    union { f32 m_44; u32 m_44u; };
    f32 m_48;
    union { f32 m_4c; void *m_4cp; };
    union { u32 unk_50; u32 m_50; };
    union { f32 m_54; u32 m_54u; };
    f32 m_58;
    union { s32 m_5c; u32 m_5cu; };
};

typedef char TUnk_804CE018_size[sizeof(TUnk_804CE018) == 0x60 ? 1 : -1];
typedef char TUnk_804CE018_unk22[offsetof(TUnk_804CE018, unk_22) == 0x22 ? 1 : -1];
typedef char TUnk_804CE018_m2c[offsetof(TUnk_804CE018, m_2c) == 0x2C ? 1 : -1];
typedef char TUnk_804CE018_m40[offsetof(TUnk_804CE018, m_40) == 0x40 ? 1 : -1];
typedef char TUnk_804CE018_m48[offsetof(TUnk_804CE018, m_48) == 0x48 ? 1 : -1];
typedef char TUnk_804CE018_m54[offsetof(TUnk_804CE018, m_54) == 0x54 ? 1 : -1];
typedef char TUnk_804CE018_m5c[offsetof(TUnk_804CE018, m_5c) == 0x5C ? 1 : -1];

#endif
