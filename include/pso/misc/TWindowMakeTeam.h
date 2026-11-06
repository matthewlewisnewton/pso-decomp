#ifndef PSO_MISC_TWINDOWMAKETEAM_H
#define PSO_MISC_TWINDOWMAKETEAM_H

#include "types.h"
#include "pso/TObject.h"

struct TWindowMakeTeam : public TObject {
    virtual ~TWindowMakeTeam();
    u8 m_1c;
    u8 m_1d;
    u8 m_1e;
    u8 m_1f;
    u32 m_20;
    u32 m_24;
    u32 m_28;
    u32 m_2c;
    u32 m_30;
    u32 m_34;
    static s32 draw_entry_0x110(s8 arg0);
    s32 is_enabled();
    u8 get_mode();
    u8 read_mode();
    s32 get_field_20();
    int test_flag_1d_bit1();
    int test_flag_1d_bit0();
    void set_state(s32 arg1);
    void send_state();
    void update_ok_button();
    s32 create_status_menu_window();
    s32 create_entry_menu_window();
    int set_keyboard_flag62_bit2();
    int get_lobby_field_20();
    void set_sub_position(u8 *arg1);
    int get_keyboard_field_6c();
    static s32 create_menu();
    virtual void render();
    virtual void run_task();
    void set_entry_string_by_id(void *arg1, s32 arg2);
};

typedef char TWindowMakeTeam_size[sizeof(TWindowMakeTeam) == 0x38 ? 1 : -1];
#endif
