#ifdef __MWERKS__
#pragma dont_inline off
#pragma inline_depth(2)
#endif
#include "pso/ui/WarningWindowUpdate.h"
#include "pso/TObjBagWarnWin4P.h"
#include "pso/misc/TWindowBase.h"

#include "types.h"
#include "pso/misc/TRaderMapCore.h"
#include "pso/misc/TWindowCtrl.h"
#include "pso/player/TObjPlayer.h"

extern "C" {
s32 TWindowCtrlMain__sub_8024CE58();
void *__ct__16TObjBagWarnWin4PFv(void *arg0);
u32 create__14TWindowMessageFlPCvUll(s32, void *, s32, s32);
void *get_player_by_client_id(s32 i);
s32 TQuestVmDownLoadServer__sub_8006EF6C(s32);
s32 has_player_active_menu__11TWindowCtrlFv(u16);
s32 is_slot_visible__11TWindowCtrlFv(u16);
s32 get_window_layout_position(s32);
void __ct__7TObjectFP7TObject(void *);
s32 get_character_save_record(u32 arg0);
s32 is_active__19THunterGuildWarningFv();
s32 is_level_capped__23TAdSinglePlyChrSelectGCFv();
s32 get_entity_id();
s32 append_line__14TWindowMessageFii(u32, void *, s32);
s32 strncpy(void *, s32, s32);

s32 TObjBagWarnWin4P::check_can_open(void * _w0) {
    s32 i;
    s32 var_r30;

    for (i = 0; i < 4; i++) {
        if ((get_player_by_client_id(i) != 0U) && (has_player_active_menu__11TWindowCtrlFv(get_entity_id()) != 0)) {
            return 0;
        }
    }
    for (i = 0; i < 4; i++) {
        if ((get_player_by_client_id(i) != 0U) && (is_slot_visible__11TWindowCtrlFv(get_entity_id()) != 0)) {
            return 0;
        }
    }
    if (is_active__19THunterGuildWarningFv() != 0) {
        return 0;
    }
    i = 0;
    var_r30 = 0;
    do {
        if ((get_player_by_client_id(var_r30) != 0U) && (get_character_save_record(var_r30) != 0U) && (is_level_capped__23TAdSinglePlyChrSelectGCFv() != 0)) {
            i = 1;
        }
        var_r30 += 1;
    } while (var_r30 < 4);
    return i;
}

extern s32 TObjBagWarnWin4P__message_window_size[];

struct TObjBagWarnWin4PPolicy {
    static s32 should_show(TObjBagWarnWin4P *self) { return TObjBagWarnWin4P::check_can_open(self); }
    static void open(TObjBagWarnWin4P *self) { self->create_window(); }
};

void TObjBagWarnWin4P::run_task() {
    update_warning_window<TObjBagWarnWin4P, TObjBagWarnWin4PPolicy>(this);
}


void TObjBagWarnWin4P::create_window() {
    s32 r3 = get_window_layout_position(0x5B);
    warning.window = (TWindowBase *)create__14TWindowMessageFlPCvUll(r3, TObjBagWarnWin4P__message_window_size, 1, 4);
    if (warning.window != NULL) {
        strncpy(warning.text, TQuestVmDownLoadServer__sub_8006EF6C(0x69), 0x7F);
        warning.text[0x7F] = 0;
        append_line__14TWindowMessageFii((u32)warning.window, warning.text, 0);
    }
}

extern s32 __vt__16TObjBagWarnWin4P[];
extern void *lbl_805D284C;

TObjBagWarnWin4P::~TObjBagWarnWin4P() {}
void *__ct__16TObjBagWarnWin4PFv(void *bag_warn_win4_p) {
    __ct__7TObjectFP7TObject(bag_warn_win4_p);
    *(s32 **)((s8 *)bag_warn_win4_p + 0x18) = __vt__16TObjBagWarnWin4P;
    *(void * *)&((TObjBagWarnWin4P *)bag_warn_win4_p)->m_name = lbl_805D284C;
    ((TObjBagWarnWin4P *)bag_warn_win4_p)->warning.window = NULL;
    ((TObjBagWarnWin4P *)bag_warn_win4_p)->warning.countdown = 0;
    return bag_warn_win4_p;
}

}
