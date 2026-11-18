#ifndef PSO_UI_WINDOW_TWINDOWBASE_H
#define PSO_UI_WINDOW_TWINDOWBASE_H
#include "types.h"
#include <stddef.h>
#include "pso/system/task/TObject.h"

struct WindowLayoutEntries {
    u32 count;
    void **items;

    void clear();
};

typedef char WindowEntriesSize[sizeof(WindowLayoutEntries) == 8 ? 1 : -1];
typedef char WindowEntriesItemsOffset[offsetof(WindowLayoutEntries, items) == 4 ? 1 : -1];

class TWindowBase : public TObject {
public:
    TWindowBase(u8 *descriptor, s16 client, u8 *parent);
    virtual ~TWindowBase();
    void draw_window_frame(void *);
    void draw_window_frame_strips(void *, void *);
    void draw_message_frame_row(void *, void *);
    void resort_window_order();
    void close();
    void set_depth(f32 depth);
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
    u8 sub_80246948();
    s32 get_array_entry(int);
    virtual void render();
    virtual void run_task();

    f32 sort_depth;
    s16 client_index;
    s16 closing_tick;
    WindowLayoutEntries entry_list;
    s32 window_flags;
};

typedef char WindowSortDepthOffset[offsetof(TWindowBase, sort_depth) == 0x1C ? 1 : -1];
typedef char WindowClientOffset[offsetof(TWindowBase, client_index) == 0x20 ? 1 : -1];
typedef char WindowClosingTickOffset[offsetof(TWindowBase, closing_tick) == 0x22 ? 1 : -1];

typedef char WindowEntriesOffset[offsetof(TWindowBase, entry_list) == 0x24 ? 1 : -1];
typedef char WindowFlagsOffset[offsetof(TWindowBase, window_flags) == 0x2C ? 1 : -1];

#endif
