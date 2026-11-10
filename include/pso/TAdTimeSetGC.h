#ifndef PSO_TADTIMESETGC_H
#define PSO_TADTIMESETGC_H

#include "pso/TObject.h"
#include "types.h"

class TAdTimeSetGC : public TObject {
public:
    virtual ~TAdTimeSetGC();
    void sub_802E1F14();
    void change_state(s32);
    s32 poll_load_status();
    s32 check_capacity();
    s32 count_selected_flags();
    virtual void run_task();
    void advance_when_load_done();
    void build_selection_summary();
    void close_and_next_cancel();
    void close_scene();
    void create_backgrounds();
    void create_result_bg();
    void ensure_player_loaded();
    void ensure_system_file_loaded();
    void finish_settings();
    void handle_confirm_menu();
    void init_menu_window();
    void init_screen();
    void open_char_select();
    void poll_loaded_player();
    void rebuild_and_maybe_close();
    void report_card_status();
    void reset_on_load_complete();
    void show_confirm_dialog();
    void start_settings();
    void sub_802E1F8C();
    void sub_802E1FAC();
    void sub_802E2158();
    void sub_802E22A4();
    void sub_802E23E8();
    void sub_802E2450();
    void sub_802E24B8();
    void sub_802E2520();
    void sub_802E2588();
    void sub_802E2610();
    void sub_802E2848();
    void sub_802E289C();
    void sub_802E2A7C();
    void sub_802E2BC8();
    void sub_802E2BD4();
    void sub_802E2D3C();
    void sub_802E2F20();
    void sub_802E2F68();
    void sub_802E2FEC();
    void sub_802E3038();
    void try_setup();
    void update_char_timer();
    void update_close_on_load();
    void update_close_timer();
    void update_load_countdown();
    void update_load_state();
    void update_timer();

    s32 state_index;
    u8 unk_20[0x4];
    s32 m_24;
    u8 unk_28[0x4];
    s32 m_2c;
    u8 unk_30[0x4];
    s32 m_34;
    u8 unk_38[0x4];
    s32 m_3c;
    u8 unk_40[0x4];
    s32 load_status;
    u8 unk_48[0x4];
    s32 m_4c;
    TObject *owned_object;
    void *window;
    TObject *queued_object;
    u32 unknown_5c;
    s32 timer;
    s32 message_timer;
    char message_text[0x400];
};

typedef void (TAdTimeSetGC::*TAdTimeSetGCStateAction)();
struct TAdTimeSetGCStateActions {
    TAdTimeSetGCStateAction enter;
    TAdTimeSetGCStateAction task;
};

#include <stddef.h>
typedef char TAdTimeSetGC_owned_object_offset[offsetof(TAdTimeSetGC, owned_object) == 0x50 ? 1 : -1];
typedef char TAdTimeSetGC_window_offset[offsetof(TAdTimeSetGC, window) == 0x54 ? 1 : -1];
typedef char TAdTimeSetGC_queued_object_offset[offsetof(TAdTimeSetGC, queued_object) == 0x58 ? 1 : -1];
typedef char TAdTimeSetGC_state_index_offset[offsetof(TAdTimeSetGC, state_index) == 0x1c ? 1 : -1];
typedef char TAdTimeSetGC_load_status_offset[offsetof(TAdTimeSetGC, load_status) == 0x44 ? 1 : -1];
typedef char TAdTimeSetGC_timer_offset[offsetof(TAdTimeSetGC, timer) == 0x60 ? 1 : -1];
typedef char TAdTimeSetGC_message_text_offset[offsetof(TAdTimeSetGC, message_text) == 0x68 ? 1 : -1];
typedef char TAdTimeSetGC_size[sizeof(TAdTimeSetGC) == 0x468 ? 1 : -1];
typedef char TAdTimeSetGCActionSize[sizeof(TAdTimeSetGCStateAction) == 12 ? 1 : -1];
typedef char TAdTimeSetGCEntrySize[sizeof(TAdTimeSetGCStateActions) == 24 ? 1 : -1];
typedef char TAdTimeSetGCStateTaskOffset[offsetof(TAdTimeSetGCStateActions, task) == 12 ? 1 : -1];

#endif
