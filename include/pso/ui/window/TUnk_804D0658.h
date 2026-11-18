#ifndef PSO_UI_WINDOW_TUNK_804D0658_H
#define PSO_UI_WINDOW_TUNK_804D0658_H
#include "types.h"
#include "pso/ui/window/TWindowAddition.h"

class TUnk_804D0658 : public TWindowAddition {
public:
    TUnk_804D0658(void *position, u32 count);
    virtual ~TUnk_804D0658();
    virtual void run_task();
    virtual void render();
    void draw();
    void draw_setting(s32);
    void clamp_scroll();
    void update_scroll_offset();
    void move_cursor_prev();
    void move_next_choice();
    void request_close();
    void initialize_entries(u32 count);
    int is_selected();
    int is_open();
    u8 unk_1C[0x10];
    s32 m_2c;
    u8 unk_30[0xC];
    f32 m_3c;
    u8 unk_40[0xC];
    f32 m_4c;
    u8 unk_50[0xC];
    s32 m_5c;
    u8 unk_60[0x10];
    u16 m_70;
    s16 entry_offset;
    s16 m_74;
    s16 entry_count;
    u32 m_78;
    u32 scrollbar;
};
typedef char TUnk_804D0658_size[sizeof(TUnk_804D0658) == 0x80 ? 1 : -1];

#endif
