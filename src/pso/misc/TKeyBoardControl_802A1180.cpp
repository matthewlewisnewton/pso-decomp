#include "types.h"
#include "pso/TMainTask.h"
#include "pso/misc/TKeyBoardControl_802A1180.h"
#include "pso/system/main_loop.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/misc/TQuestVmDownLoadServer.h"
#include "pso/misc/TUnk_804DCB64.h"
#include "pso/misc/TKeyBoardControl.h"
#include "pso/misc/TLobby.h"

struct RecoveredGlobal_802A1180_main_task {
    s32 value;
    u8 remaining[0x30];
};

extern "C" {
s32 TKeyBoardControl__sub_8000F92C();
s32 request_queued_main_phase();
void TKeyBoardControl__sub_8000F9CC(s32 arg0);
s8 func_801A5E54__Fv();
extern s8 movie_finished_flag;
void __dl__7TObjectFPv(void *);
void __dt__7TObjectFv(void *, int);
extern s32 lbl_804DCB64[];
s32 init_fresh_character_card();
void TKeyBoardControl__sub_8000F90C(s32 arg0);
void TKeyBoardControl__sub_8000F91C(s32 arg0);
void reset_controller_input_state(void);
s32 set_copy_clear_color_argb(s32, s32, s32);
u32 __nw__7TObjectFUl(s32);
s32 create_opening_movie_sequence();
}
void process_async_file_reads(void);
void update_sound_request_slots(void);
extern u8 opening_movie_purpose;

typedef char RecoveredGlobal_802A1180_main_task_size[sizeof(RecoveredGlobal_802A1180_main_task) == 0x34 ? 1 : -1];
void update_movie_phase(void) {
    s32 *var_r3;
    controller_stuff();
    TKeyBoardControl::update_input_frame();
    var_r3 = (s32 *)(&(*(RecoveredGlobal_802A1180_main_task *)&main_task).value);
    var_r3 = (s32 *)(&(*(RecoveredGlobal_802A1180_main_task *)&main_task).value);
    main_task.begin_frame();
    var_r3 = (s32 *)(&(*(RecoveredGlobal_802A1180_main_task *)&main_task).value);
    var_r3 = (s32 *)(&(*(RecoveredGlobal_802A1180_main_task *)&main_task).value);
    main_task.run_task();
    var_r3 = (s32 *)(&(*(RecoveredGlobal_802A1180_main_task *)&main_task).value);
    var_r3 = (s32 *)(&(*(RecoveredGlobal_802A1180_main_task *)&main_task).value);
    main_task.render();
    var_r3 = (s32 *)(&(*(RecoveredGlobal_802A1180_main_task *)&main_task).value);
    var_r3 = (s32 *)(&(*(RecoveredGlobal_802A1180_main_task *)&main_task).value);
    main_task.render_screen_overlay();
    process_async_file_reads();
    update_sound_request_slots();
    TAdSinglePlyChrSelectGC::noop();
    if ((s32) (*(u8 *)&movie_finished_flag) == 1) {
        request_queued_main_phase();
    }
    if (func_801A5E54__Fv() != 0) {
        TKeyBoardControl__sub_8000F92C();
    }
    if (TQuestVmDownLoadServer::is_ready() != 0) {
        var_r3 = NULL;
        TKeyBoardControl__sub_8000F9CC(0);
    }
    render_tick();
}

void TKeyBoardControl::update_menu_scene() {
    set_copy_clear_color_argb(0, 0, 0);
    reset_controller_input_state();
    TKeyBoardControl__sub_8000F90C(2);
    switch ((s8) opening_movie_purpose) {
    case 0:
        TKeyBoardControl__sub_8000F91C(1);
        TKeyBoardControl__sub_8000F90C(9);
        break;
    case 1:
        TLobby::update_keyboard_menu();
        init_fresh_character_card();
        TLobby::free_keyboard_soft_resources();
        TKeyBoardControl__sub_8000F91C(5);
        break;
    }
    movie_finished_flag = 0;
    if (__nw__7TObjectFUl(0x24) != 0U) {
        create_opening_movie_sequence();
    }
    render_tick();
}

void TUnk_804DCB64::render() {  }
void TUnk_804DCB64::run_task() {  }
void set_movie_finished_flag(void) { (*(unsigned char *)&movie_finished_flag) = 1; }
void *__dt__13TUnk_804DCB64Fv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = lbl_804DCB64;
        __dt__7TObjectFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}
