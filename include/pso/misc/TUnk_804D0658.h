#ifndef PSO_MISC_TUNK_804D0658_H
#define PSO_MISC_TUNK_804D0658_H
#include "types.h"
#include "pso/misc/TWindowAddition.h"

class TUnk_804D0658 : public TWindowAddition {
public:
    TUnk_804D0658(void *position, u32 count);
    virtual ~TUnk_804D0658();
    virtual void render();
    virtual void run_task();
    void initialize_entries(u32 count);
    void draw();
    void draw_setting(s32);
    void clamp_scroll();
    void update_scroll_offset();
    void move_cursor_prev();
    void move_next_choice();
    void request_close();
    int is_selected();
    int is_open();
    u16 m_70;
    u8 unk_72[0x2];
    s16 m_74;
    u8 unk_76[0x2];
    u32 m_78;
    u8 unk_7C[0x4];
};
typedef char TUnk_804D0658_size[sizeof(TUnk_804D0658) == 0x80 ? 1 : -1];

typedef char TUnk_804D0658_fields_begin[offsetof(TUnk_804D0658, m_70) == 0x70 ? 1 : -1];
typedef char TUnk_804D0658_auxiliary[offsetof(TUnk_804D0658, unk_7C) == 0x7C ? 1 : -1];

#endif
