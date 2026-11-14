#ifndef PSO_MISC_TUNK_804D0618_H
#define PSO_MISC_TUNK_804D0618_H
#include "types.h"
#include "pso/misc/TWindowAddition.h"

struct Scroll_8026D790;

class TUnk_804D0618 : public TWindowAddition {
public:
    virtual ~TUnk_804D0618();
    virtual void run_task();
    virtual void render();
    virtual void vfunc_6(u32, s32);
    void draw_selected_list_entry(s32);
    void update_scroll_offset();
    void clamp_item_list_scroll();
    void center_list_selection();
    void ensure_status_display(s32);
    void create_menu_scroll_bar();
    void move_cursor();
    void move_cursor_next();
    void handle_open();
    void set_flag4();
    int get_flag();
    int get_status_flag();
    u16 m_70;
    s16 m_72;
    s16 unk_74;
    s16 m_76;
    s16 m_78;
    u8 unk_7A[0x2];
    s32 m_7c;
    void * m_80;
    Scroll_8026D790 *unk_84;
};
typedef char TUnk_804D0618_size[sizeof(TUnk_804D0618) == 0x88 ? 1 : -1];

typedef char TUnk_804D0618_fields_begin[offsetof(TUnk_804D0618, m_70) == 0x70 ? 1 : -1];

#endif
