#ifndef PSO_UI_TADMULTIPLYCHRSELECTGC_H
#define PSO_UI_TADMULTIPLYCHRSELECTGC_H

#include "types.h"
#include "pso/TObject.h"

/* One selection cell: position, then the page of texture coordinates sub_802C5F1C fills. */
struct TAdMultiPlyChrSelectGC_Quad {
    f32 x, y, z, w, u0, v0, u1, v1;
};
struct TAdMultiPlyChrSelectGC_V2 { f32 x, y; };

/* Selects the placement form of operator new. The retail allocator is still __nw(0xA0). */
enum ChrSelectStorage { chr_select_storage };

struct TAdMultiPlyChrSelectGC : public TObject {
    void *operator new(size_t, void *storage, ChrSelectStorage) { return storage; }
    TAdMultiPlyChrSelectGC(TObject *parent, s32 mode);
    virtual ~TAdMultiPlyChrSelectGC();
    void create_widgets();
    void sub_802DC118(s32);
    virtual void render();
    u32 m_1c;
    u32 m_20;
    /* The 4x3 grid (and the four extra rows the draw pass reads) occupies 0x24..0x324.
       The same bytes are the integer fields below: initialize_selection_state stores
       s32/u32 there, and sub_802C5F1C stores the cell texture floats. Each function
       names the member it actually stores. */
    union {
        struct {
            u32 m_24;
            u8 unk_28[0x4];
            f32 m_2c;
            u8 unk_30[0x4];
            s32 m_34;
            u8 unk_38[0x4];
            u32 m_3c;
            u32 m_40;
            u8 _pad44[0x4];
            u32 m_48;
            u32 m_4c;
            u8 unk_50[0x4];
            s32 m_54;
            u8 unk_58[0x4];
            s32 m_5c;
            u8 unk_60[0x4];
            u32 m_64;
            u8 unk_68[0x4];
            s32 m_6c;
            u8 unk_70[0x4];
            u32 m_74;
            u8 unk_78[0x4];
            s32 m_7c;
            u8 unk_80[0x4];
            u32 m_84;
            u8 unk_88[0x4];
            s32 m_8c;
            u8 unk_90[0x4];
            u32 m_94;
            u8 unk_98[0x4];
            s32 m_9c;
        } grid;
        TAdMultiPlyChrSelectGC_Quad quad[8][3];
    };
    f32 cursor[3][8];
    TAdMultiPlyChrSelectGC_V2 home[4][3];
    u8 pad3e4[0x444 - 0x3E4];
    s32 a[4][3];
    u8 pad474[0x4A4 - 0x474];
    f32 ox;
    f32 oy;
    s32 sel[4][3];
    s32 f4DC[4];
    s32 f4EC;
    u8 pad4f0[8];
    s32 f4F8;
    u8 pad4fc[4];
    s32 b[4][3];
    void set_index_and_close_status(s32 arg1);
    void set_status_value(s32 arg1);
    void handle_event(s32 arg1);
    void initialize_selection_state(s32 arg1);
    static int get_instance();
    void set_state_ready();
    s32 get_cursor();
    void set_state(s32 v);
    s32 get_card_index();
    static int get_card_instance();
    s32 get_selection();
    static void set_select_mode(int a0, int a1);
    void set_entry_value(s32 arg1, u32 arg2);
    void draw_selection_cursors();
    void update();
    void reset_cursor_state();
    void init_slot_position(s32 arg1, s32 arg2, s32 arg3);
    void clear_slot_entries(s32 arg1);
    static void reset_slot_selection_table();
    static void split_slot_index(s32 arg0, s32 *arg1, s32 *arg2);
    static void find_first_open_cell(s32 arg0, u32 *arg1);
    void move_cursor(s32 x_, s32 y_, s32 dx, s32 dy, s32 depth);
    void update_option_cursor();
    void handle_dpad_input();
    void sub_802C5F1C();
    static void init();
    static s32 get_status();
    static s32 is_selection_confirmed();
    static s32 count_ready();
    static void remove_selected_slot(s32 arg0);
    static void add_selected_slot();
    static s32 get_clamped_cursor();
    static void reset_slot_selections();
    s32 get_field_20();
    static int get_state();
    static int get_selected_slot();
    static int get_global_6700();
    static void update_transition_anim_if_active();
    void update_transition_anim();
    s32 get_player_index();
    void set_cursor_index(s32 v);
    void set_field_100(s32 v);
    static void render(void *self);
    static s32 create_confirm_window();
    static s32 create_choice_menu();
    static void collect_player_slots();
    s32 get_state_result();
    static u8 *format_player_number_text(s32 arg0, s32 arg1);
    int request_scene_change();
    void check_cancel_input();
    void handle_input();
    void update_input_state();
    void close_and_reset();
    void update_idle_timer();
    void update_confirm_start();
    void handle_cancel_state();
    void update_state_move();
    void handle_confirm_state();
    void update_state();
    void update_card_select_state();
    void update_state_wait_card();
    void update_select();
    void reset_to_select();
    void update_button_input();
    virtual void run_task();
    void set_field_4ec(s32 v);
    static void restore_selection();
    void update_field_4E8();
    s32 get_field_0x530();
    void set_field_1c(s32 v);
    s32 get_mode();
    s32 is_state_closing();
    static int get_global_state();
    static int get_select_flag();
    static int get_chr_select_state();
    s32 get_ready_state();
    static u32 get_move_effect(s32 arg0);
    static s32 dispatch_draw_command(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
    void update_selection();
    void open_windows();
    void init_windows();
    void open_char_select();
    void close_windows();
    void update_card_select();
    void update_state_option();
    void update_card_confirm();
};

typedef char TAdMultiPlyChrSelectGC_size[sizeof(TAdMultiPlyChrSelectGC) == 0x530 ? 1 : -1];
#endif
