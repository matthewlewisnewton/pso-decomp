#ifndef PSO_MISC_TWINDOWSUBSYMBOLCHATPARTSSET_H
#define PSO_MISC_TWINDOWSUBSYMBOLCHATPARTSSET_H

#include "types.h"
#include "pso/misc/TWindowChatSymbol.h"

struct TWindowSubSymbolChatPartsSet : public TWindowChatSymbol {
    TWindowSubSymbolChatPartsSet(void *position, s16 index, s32 *first, s32 *second);
    virtual ~TWindowSubSymbolChatPartsSet();
    void sub_8028625C();
    s32 is_active();
    void set_selection(u32);
    void update_visibility();
    virtual void render();
    u8 m_68;
    u8 _pad69[0x1];
    u16 m_6a;
    u16 m_6c;
    u16 m_6e;
    u32 m_70;
    u8 _pad74[0x8];
    s32 *m_7c;
    s32 *m_80;
    u8 _pad84[0x4];
    void *m_88;
    void copy_vec2(void* q);
    s32 draw_selected_part_cursor(int arg1);
    void handle_cancel();
    void handle_decide();
    void toggle_selected_part();
    void handle_cursor_input();
    virtual void run_task();
    f32 m_8c;
    f32 m_90;
    f32 m_94;
    static int get_parts_entry(int a0);
    void set_pos(s16 arg1, s16 arg2);
    static void set_part_sprite(void *arg0, s16 id, s32 a, s32 b);
    void get_entry_offset_d(s32 arg1);
    void get_parts_entry(s32 arg1);
};

typedef char TWindowSubSymbolChatPartsSet_size[sizeof(TWindowSubSymbolChatPartsSet) == 0x98 ? 1 : -1];
#endif
