#include "pso/TAdTimeSetGC.h"
#include "pso/TMath.h"
#include "types.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowSubComCard_80244774.h"
#include "pso/misc/TWindowSubStatusDisp_80144B14.h"
#include "pso/ui/TAdPlyStatusGC_802E1128.h"
#include "pso/system/date.h"
#include "pso/menu/T_ATS_DrawCalendar.h"
#include "pso/ui/TAdPlyStatusGC.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/ui/Language.h"
#include "pso/misc/TWindowMenu.h"
#include "pso/misc/TLanguage.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TWindowMessage.h"
#include "pso/TAdMultiChgGameModeGC.h"
#include "pso/TAdPlayerLoadGC.h"
#include "pso/misc/TWindowOptionCtrl.h"
#include "pso/misc/TWindowSubComCardList.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/misc/TWindowSubSymbolChatPartsSet.h"
#include "pso/TObject.h"
#include "pso/menu/TAdTimeSetGC.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/ui/TAdSinglePlyChrSelectGC_802E13C8.h"

extern vec2f time_set_message_pos;
extern vec2f time_set_option_pos;
extern vec2f time_set_calendar_pos;
extern f32 time_set_option_extent;
extern TAdTimeSetGCStateActions time_set_state_actions[25];

struct Pt_802E11D4 { f32 x, y; };

struct Date_802E11D4 { u16 year; u8 month; u8 day; u8 hour; u8 min; u8 sec; u8 wday; u32 pad8; };

struct Clock_802E11D4 { u8 pad0[0x1C]; s32 visible; Pt_802E11D4 pos; };

extern "C" {
s32 get_localized_text_entry(s32 arg0, s32 arg1);
s32 sprintf(void *, const void *, ...);
extern const char time_set_class_name_text[] = "TAdTimeSetGC";
extern const vec2f time_set_dialog_size = {540.0f, 260.0f};
extern const char calendar_class_name_text[] = "T_ATS_DrawCalendar";
// A weak date format keeps the renderer's three independent format loads.
#ifdef __MWERKS__
__declspec(weak)
#endif
extern const char ply_status_date_format[] = "%d/%02d/%02d %s";
extern const char ply_status_date_format_mdy[] = "%02d/%02d/%d %s";
extern const char time_set_time_format[] = "%02d:%02d:%02d";
const char *TAdTimeSetGC_class_name = time_set_class_name_text;
const char *time_set_calendar_class_name = calendar_class_name_text;

s32 TAdPlyStatusGC::get_field_498() { return *(s32*)((char*)this + 0x498); }
void*TAdPlyStatusGC::get_chara_making_data() { return (char*)this + 0x1b8; }
s32 TAdPlyStatusGC::get_field_49c() { return *(s32*)((char*)this + 0x49c); }
s32 TAdPlyStatusGC::get_field_4a0() { return *(s32*)((char*)this + 0x4a0); }
void*TAdPlyStatusGC::get_status_data() { return (char*)this + 0x324; }
s32 TAdPlyStatusGC::get_field_4a4() { return *(s32*)((char*)this + 0x4a4); }
void*TAdPlyStatusGC::get_status_sub() { return (char*)this + 0x490; }

    extern int ply_status_chcr_load_afs;
void TAdPlyStatusGC::set_status_param(int a0, int a1) { ply_status_chcr_load_afs = a1; }

    extern int ply_status_gc_instance;
int TAdPlyStatusGC::get_index() {  return ply_status_gc_instance; }

    extern int ply_status_index;
void TAdPlyStatusGC::set_status_index(int a0, int a1) { ply_status_index = a1; }

extern s32 TAdPlyStatusGC__window_offset_index;

void TAdPlyStatusGC::close_window(s32 arg1) {
    TAdPlyStatusGC__window_offset_index = arg1;
    if ((u32) this->m_6c != 0U) {
        ((TWindowBase *)this->m_6c)->close();
        this->m_6c = 0U;
    }
}

void TAdPlyStatusGC__sub_802E11BC(void* p) { *(s32*)((char*)p + 0x1c) = 0; }
void TAdPlyStatusGC__sub_802E11C8(void* p) { *(s32*)((char*)p + 0x1c) = 1; }
void T_ATS_DrawCalendar::render() {
    Clock_802E11D4 *self = (Clock_802E11D4 *)this;
    char buf[0x24];
    Date_802E11D4 date;
    char *s;
    f32 w;
    s32 wd;
    if (self->visible != 0) {
        Pt_802E11D4 pos = self->pos;
        s = (char *)get_localized_text_entry(0x1C, 0xC);
        ((TAdSinglePlyChrSelectGC *)s)->render_status_disp(-(0.5f * (f32)calc_text_width(s) - pos.x), pos.y);
        pos.y += 30.0f;
        getDateStamp((DateStamp *)&date);
        wd = date.wday + 13;
        switch (current_language) {
        case LANGUAGE_JAPANESE:
            sprintf(buf, ply_status_date_format, date.year, date.month, date.day, get_localized_text_entry(0x1C, wd));
            s = buf;
            w = -0.5f * (f32)calc_text_width(s);
            break;
        default:
            sprintf(buf, ply_status_date_format_mdy, date.month, date.day, date.year, get_localized_text_entry(0x1C, wd));
            s = buf;
            w = -0.5f * (f32)TWindowSubStatusDisp__sub_80144E9C(s);
            break;
        }
        ((TAdSinglePlyChrSelectGC *)s)->render_status_disp(pos.x + w, pos.y);
        pos.y += 22.0f;
        sprintf(buf, time_set_time_format, date.hour, date.min, date.sec);
        ((TAdSinglePlyChrSelectGC *)buf)->render_status_disp(-(0.5f * (f32)calc_text_width(buf) - pos.x), pos.y);
    }
}

}

extern "C" {
s32 TAdSinglePlyChrSelectGC__sub_802E1868(void);
int TAdSinglePlyChrSelectGC__sub_802E18C8(void);
void sub_802E1F14__12TAdTimeSetGCFv(u8 *arg0);
void apply_settings__23TAdSinglePlyChrSelectGCFi(s32 arg0);
void change_state__12TAdTimeSetGCFl(u8 *arg0, s32 arg1);
void close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv(void* p, void* a1, void* a2, void* a3, void* a4);
void close_and_next__23TAdSinglePlyChrSelectGCFPvPvPvPvPv(void* p, void* a1, void* a2, void* a3, void* a4);
void close_windows__23TAdSinglePlyChrSelectGCFPv(void *arg0);
void create_backgrounds__23TAdSinglePlyChrSelectGCFPv(void *arg0);
s32 get_localized_text_entry(s32, s32);
extern u8 lbl_804C88C0[];
extern u8 lbl_804C89BC[];
}

#define sub_802E1F14__12TAdTimeSetGCFv ((s32 (*)(void *))sub_802E1F14__12TAdTimeSetGCFv)

struct RecoveredGlobal_802E14B8_lbl_804C89BC {
    s32 value;
    u8 remaining[0x74];
};

struct RecoveredGlobal_802E14F0_lbl_804C88C0 {
    s32 value;
    u8 remaining[0x50];
};

struct RecoveredGlobal_802E1560_lbl_804C89BC {
    s32 value;
    u8 remaining[0x74];
};

struct RecoveredGlobal_802E1594_lbl_804C88C0 {
    s32 value;
    u8 remaining[0x50];
};

struct RecoveredGlobal_802E1868_lbl_8050E208 {
    s32 value;
    u8 remaining[0x1AC];
};

struct RecoveredGlobal_802E1868_lbl_8050E3B8 {
    s32 value;
    u8 remaining[0x1AC];
};

struct Self_802E1A8C {
    u8 pad[0x50];
    void *x50;
    void *x54;
};

extern "C" {
void TAdSinglePlyChrSelectGC__sub_802E1A04(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 test_flag_4c__23TAdSinglePlyChrSelectGCFv(void *, int);
s32 TWindowShortListCtrl__check_controller_button(void *, int);
extern RecoveredGlobal_802E1868_lbl_8050E208 controller_input_state;
extern RecoveredGlobal_802E1868_lbl_8050E3B8 controller_physical_port_bank;
extern RecoveredGlobal_802E14B8_lbl_804C89BC pso_system_card_filename;
s32 TAdSinglePlyChrSelectGC__sub_802E1528(void);
s32 TAdSinglePlyChrSelectGC__sub_802E15C8(void);
int align_menu_entry_positions(void *);
int forward_trade_action_default__16TObjCityMainWarpFPviii(void *p, int a1, int a2, int a3);
void *check_room_seq_4__16TAdChrSelASlotGCFl(void *, int);
int append_line__14TWindowMessageFii(void *, void *, int);
void *update_window_mode_from_progress__6TLobbyFPv(void *, const vec2f *);
void *__dt__18T_ATS_DrawCalendarFv(void *arg0, s16 arg1);
void * create__23TAdSinglePlyChrSelectGCFv(void);
s32 TAdPlayerLoadGC__sub_801E1B50(s32);
s32 TAdPlayerLoadGC__sub_801E24F8(s32, s32, s32, s32, s32);
void TAdPlyStatusGC__sub_802E11BC(void *p);
s32 load_system_file_blocking__23TAdSinglePlyChrSelectGCFv();
s32 load_character_and_wait__23TAdSinglePlyChrSelectGCFv();
s32 load_player_and_wait__23TAdSinglePlyChrSelectGCFv();
int TKeyBoardControl__sub_8000F9CC(void*);
void TLobby__sub_8022614C(s32 arg0);
void update_music_stream_gain(s32 user);
void *__ct__12TAdBackTxtGCFv(void *, void *);
void __ct__7TObjectFP7TObject(void *);
void *__ct__9TAdBackGCFv(void *, void *);
void __dl__7TObjectFPv(void *);
void __dt__7TObjectFv(void *, int);
void *__nw__7TObjectFUl(int);
void fn_8023F160(void);
void fn_8023F18C(void);
void * get_global_state__23TAdSinglePlyChrSelectGCFv(void);

extern void *lbl_804E34FC[6];

void *__dt__18T_ATS_DrawCalendarFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(void ***)((s8 *)arg0 + 0x18) = lbl_804E34FC;
        __dt__7TObjectFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

void *T_ATS_DrawCalendar::init_object(void *) {
    __ct__7TObjectFP7TObject(this);
    *(void ***)((s8 *)this + 0x18) = lbl_804E34FC;
    this->m_name = time_set_calendar_class_name;
    *(u32 *)((s8 *)this + 0x1C) = 0;
    ((TWindowSubSymbolChatPartsSet *)((char *)this + 32))->copy_vec2(&time_set_calendar_pos);
    return this;
}

extern void *tl_clipout;

void *create__23TAdSinglePlyChrSelectGCFv(void) {
    void *o = __nw__7TObjectFUl(0x28);
    if (o != NULL) {
        o = ((T_ATS_DrawCalendar *)o)->init_object(tl_clipout);
    }
    return o;
}

typedef char RecoveredGlobal_802E14B8_lbl_804C89BC_size[sizeof(RecoveredGlobal_802E14B8_lbl_804C89BC) == 0x78 ? 1 : -1];
s32 TAdSinglePlyChrSelectGC::is_card_file_missing_a() {
    return (u8) (TAdPlayerLoadGC::find_card_file(0, (const char *)((s32) &(*(RecoveredGlobal_802E14B8_lbl_804C89BC *)&lbl_804C89BC).value)) == -0xBF);
}

typedef char RecoveredGlobal_802E14F0_lbl_804C88C0_size[sizeof(RecoveredGlobal_802E14F0_lbl_804C88C0) == 0x54 ? 1 : -1];
s32 TAdSinglePlyChrSelectGC::is_card_file_missing_b() {
    return (u8) (TAdPlayerLoadGC::find_card_file(0, (const char *)((s32) &(*(RecoveredGlobal_802E14F0_lbl_804C88C0 *)&lbl_804C88C0).value)) == -0xBF);
}

typedef char RecoveredGlobal_802E1560_lbl_804C89BC_size[sizeof(RecoveredGlobal_802E1560_lbl_804C89BC) == 0x78 ? 1 : -1];

s32 TAdSinglePlyChrSelectGC__sub_802E1528(void) {
    return (u8) (TAdPlayerLoadGC::find_card_file(0, (const char *)&pso_system_card_filename.value) == -0xBF);
}

s32 TAdSinglePlyChrSelectGC::is_card_file_absent_a() {
    return (u8) (TAdPlayerLoadGC::find_card_file(0, (const char *)((s32) &(*(RecoveredGlobal_802E1560_lbl_804C89BC *)&(*(RecoveredGlobal_802E14B8_lbl_804C89BC *)&lbl_804C89BC)).value)) == 0);
}

typedef char RecoveredGlobal_802E1594_lbl_804C88C0_size[sizeof(RecoveredGlobal_802E1594_lbl_804C88C0) == 0x54 ? 1 : -1];
s32 TAdSinglePlyChrSelectGC::is_card_file_absent_b() {
    return (u8) (TAdPlayerLoadGC::find_card_file(0, (const char *)((s32) &(*(RecoveredGlobal_802E1594_lbl_804C88C0 *)&(*(RecoveredGlobal_802E14F0_lbl_804C88C0 *)&lbl_804C88C0)).value)) == 0);
}

s32 TAdSinglePlyChrSelectGC__sub_802E15C8(void) {
    return (u8) (TAdPlayerLoadGC::find_card_file(0, (const char *)((s32) &(*(RecoveredGlobal_802E1560_lbl_804C89BC *)&pso_system_card_filename).value)) == 0);
}

s32 TAdSinglePlyChrSelectGC::is_load_complete() {
    return (u32) __cntlzw((u32) TAdPlayerLoadGC__sub_801E24F8(0, 0, 0, 0, 0)) >> 5;
}

s32 TAdTimeSetGC::poll_load_status() {
    s32 load_result;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r3;

    if (TAdPlayerLoadGC__sub_801E1B50(0) != 0) {
        *(s32 *)&this->unk_40 = (s32) (*(s32 *)&this->unk_40 + 1);
        return 2;
    }
    *(s32 *)&this->unk_40 = 0;
    if (TAdPlayerLoadGC::probe_card_slot(0) == 0) {
        sub_802E1F14__12TAdTimeSetGCFv(this);
        return 1;
    }
    if (TAdPlayerLoadGC::probe_and_check_card(0) == 0) {
        load_result = TAdPlayerLoadGC::get_load_result(0);
        switch (load_result) {
        case -125:
            return 4;
        case -127:
            return 8;
        case -223:
            return 0x10;
        default:
            return 0x20;
        }
    } else {
        if (TAdPlayerLoadGC::check_memcard_status(0) != 0) {
            return 0x40;
        }
        if (TAdSinglePlyChrSelectGC__sub_802E1528() != 0) {
            return 0x80;
        }
        var_r31_2 = 0;
        if (TAdSinglePlyChrSelectGC::is_card_file_missing_b() != 0) {
            var_r31_2 |= 0x100;
        }
        if (TAdSinglePlyChrSelectGC::is_card_file_missing_a() != 0) {
            var_r31_2 |= 0x200;
        }
        if (var_r31_2 != 0) {
            return var_r31_2;
        }
        if ((s32) this->m_24 == -1) {
            this->m_24 = 0;
            if (load_system_file_blocking__23TAdSinglePlyChrSelectGCFv() != 0) {
                this->m_24 = 1;
            }
        }
        if ((s32) this->m_24 == 1) {
            return 0x80;
        }
        if (TAdSinglePlyChrSelectGC__sub_802E15C8() != 0) {
            if ((s32) *(s32 *)((s8 *)this + 0x28) == -1) {
                *(s32 *)((s8 *)this + 0x28) = 0;
                if (load_character_and_wait__23TAdSinglePlyChrSelectGCFv() != 0) {
                    *(s32 *)((s8 *)this + 0x28) = 1;
                }
            }
            if ((s32) this->m_2c == -1) {
                this->m_2c = 0;
                if (load_player_and_wait__23TAdSinglePlyChrSelectGCFv() != 0) {
                    this->m_2c = 1;
                }
            }
            var_r3 = 0;
            if ((s32) *(s32 *)((s8 *)this + 0x28) == 1) {
                var_r3 |= 0x100;
            }
            if ((s32) this->m_2c == 1) {
                var_r3 |= 0x200;
            }
            if (var_r3 != 0) {
                return var_r3;
            }
            goto block_43;
        }
block_43:
        var_r31 = 0;
        if (TAdSinglePlyChrSelectGC__sub_802E15C8() == 0) {
            var_r31 |= 0x400;
        }
        if (TAdSinglePlyChrSelectGC::is_card_file_absent_b() == 0) {
            var_r31 |= 0x800;
        }
        if (TAdSinglePlyChrSelectGC::is_card_file_absent_a() == 0) {
            var_r31 |= 0x1000;
        }
        return var_r31;
    }
}

typedef char RecoveredGlobal_802E1868_lbl_8050E208_size[sizeof(RecoveredGlobal_802E1868_lbl_8050E208) == 0x1B0 ? 1 : -1];
typedef char RecoveredGlobal_802E1868_lbl_8050E3B8_size[sizeof(RecoveredGlobal_802E1868_lbl_8050E3B8) == 0x1B0 ? 1 : -1];
s32 TAdSinglePlyChrSelectGC__sub_802E1868(void) {
    if ((TWindowShortListCtrl__check_controller_button((void *) ((u8 *)&controller_physical_port_bank.value + 0x20), 4) != 0) || (test_flag_4c__23TAdSinglePlyChrSelectGCFv((void *) ((u8 *)&controller_input_state.value + 0x160), 4) != 0)) {
        return 1;
    }
    return 0;
}

int TAdSinglePlyChrSelectGC__sub_802E18C8(void) { return TKeyBoardControl__sub_8000F9CC((void*)(0)); }
void apply_settings__23TAdSinglePlyChrSelectGCFi(s32 arg0) {
    void *temp_r3;

    temp_r3 = get_global_state__23TAdSinglePlyChrSelectGCFv();
    if (temp_r3 == NULL) {
        ((s32 (*)(s32, s32))change_state__12TAdTimeSetGCFl)(arg0, 1);
        return;
    }
    TLanguage::set_language(*(s8 *)((s8 *)temp_r3 + 7));
    update_music_stream_gain(*(s16 *)((s8 *)temp_r3 + 4));
    TLobby__sub_8022614C(*(s8 *)((s8 *)temp_r3 + 6));
    TLobby::init_sound_mode();
    fn_8023F160();
    fn_8023F18C();
    TAdMultiChgGameModeGC::init_change_mode();
}
void close_and_next__23TAdSinglePlyChrSelectGCFPvPvPvPvPv(void* p, void* a1, void* a2, void* a3, void* a4) { close_windows__23TAdSinglePlyChrSelectGCFPv(p); TAdSinglePlyChrSelectGC__sub_802E1A04((s32)p, (s32)a1, (s32)a2, (s32)a3, (s32)a4); }
void close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv(void* p, void* a1, void* a2, void* a3, void* a4) { close_windows__23TAdSinglePlyChrSelectGCFPv((void *)p); ((TAdSinglePlyChrSelectGC *)p)->open_message_choice((void *)a1, (s32)a2, (void *)a3, (void *)a4); }

void TAdSinglePlyChrSelectGC__sub_802E1A04(s32 arg0, s32 arg1, s32 sel, s32 arg3, s32 arg4) {
    s32 localized_text_entry;
    s32 var_r6;
    localized_text_entry = get_localized_text_entry(0x1C, arg1);
    var_r6 = 0;
    if (arg3 >= 0) {
        var_r6 = get_localized_text_entry(0x1C, arg3);
    }
    if (arg4 >= 0) {
        var_r6 = get_localized_text_entry(0x1C, arg4);
    }
    ((TAdSinglePlyChrSelectGC *)arg0)->open_message_choice((void *)localized_text_entry, (s32)sel, (void *)var_r6, (void *)((void*)(0)));
}

void TAdSinglePlyChrSelectGC::open_message_choice(void *arg1, s32 sel, void *arg3, void *arg4) {
    if (((Self_802E1A8C *)this)->x50 != NULL || ((Self_802E1A8C *)this)->x54 != NULL) {
        return;
    }
    ((Self_802E1A8C *)this)->x50 = update_window_mode_from_progress__6TLobbyFPv(&time_set_message_pos, &time_set_dialog_size);
    if (((Self_802E1A8C *)this)->x50 == NULL) {
        return;
    }
    if (arg1 != NULL) {
        append_line__14TWindowMessageFii(((Self_802E1A8C *)this)->x50, arg1, 3);
    }
    ((TWindowMessage *)(((Self_802E1A8C *)this)->x50))->complete_reveal();
    if (sel == -1) {
        return;
    }
    ((Self_802E1A8C *)this)->x54 = check_room_seq_4__16TAdChrSelASlotGCFl(&time_set_option_pos, 2);
    if (((Self_802E1A8C *)this)->x50 == NULL) {
        return;
    }
    void *m;
    void *m2;
    m = arg3;
    if (m == NULL) {
        m = TWindowSubStatusDisp::get_message_10(0x5B);
    }
    if (sel != -2) {
        forward_trade_action_default__16TObjCityMainWarpFPviii((void *)(((Self_802E1A8C *)this)->x54), (int)m, 5, 0);
        m2 = arg4;
        if (m2 == NULL) {
            m2 = TWindowSubStatusDisp::get_message_10(0x5C);
        }
        forward_trade_action_default__16TObjCityMainWarpFPviii((void *)(((Self_802E1A8C *)this)->x54), (int)m2, 5, 1);
    } else {
        forward_trade_action_default__16TObjCityMainWarpFPviii((void *)(((Self_802E1A8C *)this)->x54), (int)m, 5, 1);
    }
    ((TWindowSubComCardList *)(((Self_802E1A8C *)this)->x54))->update_layout_height(time_set_option_extent);
    align_menu_entry_positions(((Self_802E1A8C *)this)->x54);
    if (sel == -2) {
        ((TWindowSubComCardList *)(((Self_802E1A8C *)this)->x54))->set_selected_index(0);
    } else {
        ((TWindowSubComCardList *)(((Self_802E1A8C *)this)->x54))->set_selected_index(sel);
    }
    ((TWindowOptionCtrl *)(((Self_802E1A8C *)this)->x54))->clear_flag70_bit4();
}

void close_windows__23TAdSinglePlyChrSelectGCFPv(void *arg0) {
    if ((u32) *(u32 *)((s8 *)arg0 + 0x50) != 0U) {
        ((TWindowBase *)(*(void **)((s8 *)arg0 + 0x50)))->close();
        *(u32 *)((s8 *)arg0 + 0x50) = 0U;
        *(s32 *)((s8 *)arg0 + 0x60) = 7;
    }
    if ((u32) *(u32 *)((s8 *)arg0 + 0x54) != 0U) {
        ((TWindowBase *)(*(void **)((s8 *)arg0 + 0x54)))->close();
        *(u32 *)((s8 *)arg0 + 0x54) = 0U;
        *(s32 *)((s8 *)arg0 + 0x60) = 7;
    }
    if ((u32) *(u32 *)((s8 *)arg0 + 0x58) != 0U) {
        TAdPlyStatusGC__sub_802E11BC(*(void **)((s8 *)arg0 + 0x58));
    }
}

void create_backgrounds__23TAdSinglePlyChrSelectGCFPv(void *arg0) {
    void *o;
    void *o2;
    if (*(void **)((s8 *)arg0 + 0x48) == NULL) {
        o = __nw__7TObjectFUl(0x24);
        if (o != NULL) {
            o = __ct__9TAdBackGCFv(o, arg0);
        }
        *(void **)((s8 *)arg0 + 0x48) = o;
    }
    if (*(void **)((s8 *)arg0 + 0x4C) == NULL) {
        o2 = __nw__7TObjectFUl(0x28);
        if (o2 != NULL) {
            o2 = __ct__12TAdBackTxtGCFv(o2, arg0);
        }
        *(void **)((s8 *)arg0 + 0x4C) = o2;
    }
}

s32 TAdPlayerLoadGC__sub_801E0FA4(s32);
s32 count_flags__23TAdSinglePlyChrSelectGCFPv(void *arg0);

s32 TAdTimeSetGC::check_capacity() {
    s32 arg0 = (s32)this;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r3;

    temp_r29 = ((s32 (*)())count_flags__23TAdSinglePlyChrSelectGCFPv)();
    temp_r30 = count_selected_flags();
    temp_r31 = TAdPlayerLoadGC__sub_801E0FA4(0);
    temp_r3 = TAdPlayerLoadGC::query_memcard_capacity(0, 0);
    if ((temp_r29 > temp_r31) || (temp_r30 > temp_r3)) {
        return 0;
    }
    return 1;
}

}

extern "C" {

s32 TAdSinglePlyChrSelectGC__sub_8001C5F0();

s32 TAdTimeSetGC::count_selected_flags() {
    s32 selected_count;

    selected_count = 0;
    if (load_status & 0x400) {
        selected_count = TAdSinglePlyChrSelectGC::get_selected_count();
    }
    if (load_status & 0x800) {
        selected_count += TAdSinglePlyChrSelectGC::get_flag_count();
    }
    if (load_status & 0x1000) {
        selected_count += TAdSinglePlyChrSelectGC__sub_8001C5F0();
    }
    return selected_count;
}

s32 count_flags__23TAdSinglePlyChrSelectGCFPv(void *arg0) {
    s32 temp_r4;
    s32 var_r3;

    temp_r4 = *(s32 *)((s8 *)arg0 + 0x44);
    var_r3 = 0;
    if (temp_r4 & 0x400) {
        var_r3 = 1;
    }
    if (temp_r4 & 0x800) {
        var_r3 += 1;
    }
    if (temp_r4 & 0x1000) {
        return var_r3 + 1;
    }
    return var_r3;
}
void TAdTimeSetGC::change_state(s32 next_state) {
    if (state_index != next_state) {
        state_index = next_state;
        TAdTimeSetGCStateAction enter = time_set_state_actions[state_index].enter;
        if (enter != 0) {
            (this->*enter)();
        }
    }
}

void init__23TAdSinglePlyChrSelectGCFPv(void *ad_time_set_gc) {
    ((s32 (*)())sub_802E1F14__12TAdTimeSetGCFv)();
    *(s32 *)((s8 *)ad_time_set_gc + 0x48) = 0;
    ((TAdTimeSetGC *)ad_time_set_gc)->m_4c = 0;
    *(s32 *)((s8 *)ad_time_set_gc + 0x50) = 0;
    *(s32 *)((s8 *)ad_time_set_gc + 0x54) = 0;
    *(s32 *)((s8 *)ad_time_set_gc + 0x58) = ((s32 (*)())create__23TAdSinglePlyChrSelectGCFv)();
    *(s32 *)((s8 *)ad_time_set_gc + 0x20) = 0;
    ((TAdTimeSetGC *)ad_time_set_gc)->unknown_5c = 0;
    ((TAdTimeSetGC *)ad_time_set_gc)->timer = 0;
    *(s32 *)((s8 *)ad_time_set_gc + 0x40) = 0;
    ((TAdTimeSetGC *)ad_time_set_gc)->load_status = ((TAdTimeSetGC *)ad_time_set_gc)->poll_load_status();
    ((TAdTimeSetGC *)ad_time_set_gc)->state_index = -1;
    if ((s32) ((TAdTimeSetGC *)ad_time_set_gc)->load_status == 0) {
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(ad_time_set_gc, 1);
        return;
    }
    ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(ad_time_set_gc, 0);
}

#undef sub_802E1F14__12TAdTimeSetGCFv

#define TAdSinglePlyChrSelectGC__sub_802E18C8 ((s32 (*)(void))TAdSinglePlyChrSelectGC__sub_802E18C8)
#define apply_settings__23TAdSinglePlyChrSelectGCFi ((s32 (*)(void))apply_settings__23TAdSinglePlyChrSelectGCFi)
#define change_state__12TAdTimeSetGCFl ((s32 (*)(void *, int))change_state__12TAdTimeSetGCFl)
#define close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv ((s32 (*)(void *, void *, int, int, int))close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv)
#define close_windows__23TAdSinglePlyChrSelectGCFPv ((int (*)(void*))close_windows__23TAdSinglePlyChrSelectGCFPv)
#define create_backgrounds__23TAdSinglePlyChrSelectGCFPv ((s32 (*)(void *))create_backgrounds__23TAdSinglePlyChrSelectGCFPv)
#define get_localized_text_entry ((s32 (*)(int, int))get_localized_text_entry)

extern const char time_set_summary_format[] = "%s\n%s\n%s";

void TAdTimeSetGC::sub_802E1F14() {
    u8 *arg0 = (u8 *)this;
    this->m_24 = -1;
    *(s32 *)((s8 *)arg0 + 0x28) = -1;
    this->m_2c = -1;
    *(s32 *)((s8 *)arg0 + 0x30) = 0;
    this->m_34 = 0;
    *(s32 *)((s8 *)arg0 + 0x38) = 0;
    this->m_3c = 0;
}

void TAdTimeSetGC::finish_settings() {
    TAdTimeSetGC *arg0 = this;
    if ((s32) *(s32 *)((s8 *)arg0 + 0x60) <= 0) {
        switch (*(s32 *)((s8 *)arg0 + 0x5C)) {
        case 0:
            apply_settings__23TAdSinglePlyChrSelectGCFi();
            return;
        default:
        case 1:
            TAdSinglePlyChrSelectGC__sub_802E18C8();
            break;
        }
    }
}

void TAdTimeSetGC::sub_802E1F8C() {
    close_windows__23TAdSinglePlyChrSelectGCFPv(this);
}
void TAdTimeSetGC::sub_802E1FAC() {
    u8 *ad_time_set_gc = reinterpret_cast<u8 *>(this);
    s32 temp_r3;
    if (*(u32 *)((s8 *)ad_time_set_gc + 0x54) == 0U || ((TWindowMenu *)(*(u32 *)((s8 *)ad_time_set_gc + 0x54)))->is_decided() == 0) {
        return;
    }
    switch (((TWindowMenu *)(*(u32 *)((s8 *)ad_time_set_gc + 0x54)))->get_selected_value()) {
    case 0:
        ((TAdTimeSetGC *)ad_time_set_gc)->unknown_5c = 1;
        change_state__12TAdTimeSetGCFl(ad_time_set_gc, 0x18);
        break;
    case 1:
        sub_802E1F14__12TAdTimeSetGCFv(ad_time_set_gc);
        change_state__12TAdTimeSetGCFl(ad_time_set_gc, 0);
        break;
    }
}
void TAdTimeSetGC::show_confirm_dialog() {
    s32 str;
    s32 t;
    s32 t2;
    s32 flags;
    str = get_localized_text_entry(0x1C, 0x18);
    flags = load_status;
    if (!(flags & 0x400)) {
        switch (flags & 0x1800) {
        case 0x1800:
            str = get_localized_text_entry(0x1C, 0x19);
            break;
        case 0x800:
            str = get_localized_text_entry(0x1C, 0x1A);
            break;
        case 0x1000:
            str = get_localized_text_entry(0x1C, 0x1B);
            break;
        }
    }
    sprintf(message_text, time_set_summary_format, get_localized_text_entry(0x1C, 0x17), str, get_localized_text_entry(0x1C, 0x14));
    create_backgrounds__23TAdSinglePlyChrSelectGCFPv(this);
    close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv(this, message_text, 1, get_localized_text_entry(0x1C, 0x15), get_localized_text_entry(0x1C, 0x16));
}

#undef TAdSinglePlyChrSelectGC__sub_802E18C8
#undef apply_settings__23TAdSinglePlyChrSelectGCFi
#undef change_state__12TAdTimeSetGCFl
#undef close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv
#undef close_windows__23TAdSinglePlyChrSelectGCFPv
#undef create_backgrounds__23TAdSinglePlyChrSelectGCFPv
#undef get_localized_text_entry

#define TAdSinglePlyChrSelectGC__sub_802E1868 ((s32 (*)(void *))TAdSinglePlyChrSelectGC__sub_802E1868)
#define sub_802E1F14__12TAdTimeSetGCFv ((s32 (*)(void *))sub_802E1F14__12TAdTimeSetGCFv)
#define change_state__12TAdTimeSetGCFl ((s32 (*)(void *, int))change_state__12TAdTimeSetGCFl)
#define close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv ((s32 (*)(s32, s32, s32, s32, s32))close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv)
#define close_and_next__23TAdSinglePlyChrSelectGCFPvPvPvPvPv ((int (*)(void*, void*, void*, void*, void*))close_and_next__23TAdSinglePlyChrSelectGCFPvPvPvPvPv)
#define close_windows__23TAdSinglePlyChrSelectGCFPv ((s32 (*)(void *))close_windows__23TAdSinglePlyChrSelectGCFPv)
#define create_backgrounds__23TAdSinglePlyChrSelectGCFPv ((s32 (*)())create_backgrounds__23TAdSinglePlyChrSelectGCFPv)

void TAdTimeSetGC::sub_802E2158() {  }
void TAdTimeSetGC::create_result_bg() {
    s32 arg0 = reinterpret_cast<s32>(this);
    create_backgrounds__23TAdSinglePlyChrSelectGCFPv();
    close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv(arg0, get_localized_text_entry(0x1C, 0x1C), -1, 0, 0);
}

void TAdSinglePlyChrSelectGC__sub_801FBB1C(void);
void TAdSinglePlyChrSelectGC__sub_801FBB7C(void);
s32 strcat(void *, const void *);

const char summary_newline[] = "\n";

void TAdTimeSetGC::build_selection_summary() {
    u8 *arg0 = (u8 *)this;
    ((s32 (*)())create_backgrounds__23TAdSinglePlyChrSelectGCFPv)();
    *(s8 *)((s8 *)arg0 + 0x68) = 0;
    if (this->load_status & 0x80) {
        strcat(arg0 + 0x68, (void *) (((s32 * (*)(s32, s32))get_localized_text_entry)(0x1C, 0x1D)));
        strcat(arg0 + 0x68, summary_newline);
    }
    if (this->load_status & 0x100) {
        strcat(arg0 + 0x68, (void *) (((s32 * (*)(s32, s32))get_localized_text_entry)(0x1C, 0x1E)));
        strcat(arg0 + 0x68, summary_newline);
    }
    if (this->load_status & 0x200) {
        strcat(arg0 + 0x68, (void *) (((s32 * (*)(s32, s32))get_localized_text_entry)(0x1C, 0x1F)));
        strcat(arg0 + 0x68, summary_newline);
    }
    ((s32 (*)(void *, void *, int, int, int))close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv)(arg0, arg0 + 0x68, 1, (int) (((s32 * (*)(s32, s32))get_localized_text_entry)(0x1C, 0x2A)), (int) (((s32 * (*)(s32, s32))get_localized_text_entry)(0x1C, 0x2B)));
}
void TAdTimeSetGC::sub_802E22A4() {
    u8 *ad_time_set_gc = reinterpret_cast<u8 *>(this);
    s32 selected_menu_value;
    u32 temp_r3_2;
    temp_r3_2 = *(u32 *)((s8 *)ad_time_set_gc + 0x54);
    if (temp_r3_2 == 0U || ((TWindowMenu *)temp_r3_2)->is_decided() == 0) {
        return;
    }
    selected_menu_value = ((TWindowMenu *)(*(u32 *)((s8 *)ad_time_set_gc + 0x54)))->get_selected_value();
        switch (selected_menu_value) {
        case 0:
            if (((TAdTimeSetGC *)ad_time_set_gc)->load_status & 0x80) {
                TAdSinglePlyChrSelectGC::try_load_system_file();
            }
            if (((TAdTimeSetGC *)ad_time_set_gc)->load_status & 0x100) {
                TAdSinglePlyChrSelectGC__sub_801FBB1C();
            }
            if (((TAdTimeSetGC *)ad_time_set_gc)->load_status & 0x200) {
                TAdSinglePlyChrSelectGC__sub_801FBB7C();
            }
            TAdPlayerLoadGC::poll_card_load(0);
            sub_802E1F14__12TAdTimeSetGCFv(ad_time_set_gc);
            change_state__12TAdTimeSetGCFl(ad_time_set_gc, 0);
            break;
        case 1:
            TAdPlayerLoadGC::poll_card_load(0);
            sub_802E1F14__12TAdTimeSetGCFv(ad_time_set_gc);
            change_state__12TAdTimeSetGCFl(ad_time_set_gc, 0);
            break;
        }
}

s32 strcpy(s32, s32);

void TAdTimeSetGC::init_menu_window() {
    s32 arg0 = (s32)this;
    ((s32 (*)())create_backgrounds__23TAdSinglePlyChrSelectGCFPv)();
    strcpy(arg0 + 0x68, ((s32 (*)(s32, s32))get_localized_text_entry)(0x1C, 1));
    ((s32 (*)(s32, const char *))strcat)(arg0 + 0x68, summary_newline);
    ((s32 (*)(s32, s32, s32, s32, s32))close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv)(arg0, arg0 + 0x68, -2, ((s32 (*)(s32, s32))get_localized_text_entry)(0x1C, 0x16), 0);
}

}

struct RecoveredGlobal_802E2A88_lbl_804C89BC {
    s32 value;
    u8 remaining[0x74];
};

typedef struct S_802E24B8 { u8 pad0[0x54]; void *f54; } S_802E24B8;

typedef struct S_802E2588 { u8 pad0[0x54]; void *f54; u8 pad58[4]; s32 f5C; } S_802E2588;

extern "C" {

int TAdSinglePlyChrSelectGC__sub_801FD990(s32 a0);
void reset_save_header__23TAdSinglePlyChrSelectGCFv(void);

s32 check_ready__23TAdSinglePlyChrSelectGCFv();
s8 get_chr_select_state__23TAdSinglePlyChrSelectGCFv();
void init_timestamped_data(void);
s32 setup__23TAdSinglePlyChrSelectGCFi(s32);
int start_load__23TAdSinglePlyChrSelectGCFv(void*);
s32 try_confirm_selection__23TAdSinglePlyChrSelectGCFv();

void TAdTimeSetGC::sub_802E23E8() {
    u8 *arg0 = reinterpret_cast<u8 *>(this);
    ((int (*)(void *))create_backgrounds__23TAdSinglePlyChrSelectGCFPv)(arg0);
    ((s32 (*)(s32, s32))strcpy)((s32)((void *)(arg0 + 0x68)), (s32)((int) (((u8 *)get_localized_text_entry(0x1C, 0x26)))));
    close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv((s32)arg0, (s32)(arg0 + 0x68), (s32)((void *)-2), (s32)(((u8 *)get_localized_text_entry(0x1C, 0x16))), (s32)NULL);
}

void TAdTimeSetGC::sub_802E2450() {
    u8 *arg0 = reinterpret_cast<u8 *>(this);
    ((int (*)(void *))create_backgrounds__23TAdSinglePlyChrSelectGCFPv)(arg0);
    ((s32 (*)(s32, s32))strcpy)((s32)((void *)(arg0 + 0x68)), (s32)((int) (((u8 *)get_localized_text_entry(0x1C, 0x27)))));
    close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv((s32)arg0, (s32)(arg0 + 0x68), (s32)((void *)-2), (s32)(((u8 *)get_localized_text_entry(0x1C, 0x16))), (s32)NULL);
}

void TAdTimeSetGC::sub_802E24B8() {
    S_802E24B8 * arg0 = reinterpret_cast<S_802E24B8 *>(this);
    if (arg0->f54 == 0 || ((TWindowMenu *)arg0->f54)->is_decided() == 0) {
        return;
    }
    ((TWindowMenu *)arg0->f54)->get_selected_value();
    TAdPlayerLoadGC::poll_card_load(0);
    ((void (*)(void *))sub_802E1F14__12TAdTimeSetGCFv)(arg0);
    ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(arg0, 0);
}

void TAdTimeSetGC::sub_802E2520() {
    u8 *arg0 = reinterpret_cast<u8 *>(this);
    ((int (*)(void *))create_backgrounds__23TAdSinglePlyChrSelectGCFPv)(arg0);
    ((s32 (*)(s32, s32))strcpy)((s32)((void *)(arg0 + 0x68)), (s32)((int) (((u8 *)get_localized_text_entry(0x1C, 0x25)))));
    close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv((s32)arg0, (s32)(arg0 + 0x68), (s32)((void *)-2), (s32)(((u8 *)get_localized_text_entry(0x1C, 0x16))), (s32)NULL);
}

void TAdTimeSetGC::sub_802E2588() {
    S_802E2588 * arg0 = reinterpret_cast<S_802E2588 *>(this);
    if (arg0->f54 == 0 || ((TWindowMenu *)arg0->f54)->is_decided() == 0) {
        return;
    }
    switch (((TWindowMenu *)arg0->f54)->get_selected_value()) {
    case 0:
        arg0->f5C = 1;
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(arg0, 0x18);
        return;
    case 1:
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(arg0, 0xC);
        break;
    }
}

void TAdTimeSetGC::sub_802E2610() {
    u8 *arg0 = reinterpret_cast<u8 *>(this);
    ((s32)((int (*)(void *))create_backgrounds__23TAdSinglePlyChrSelectGCFPv)(arg0));
    ((s32)close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv((s32)arg0, (s32)((int) (get_localized_text_entry(0x1C, 0xB))), 1, 0, 0));
    if ((u32) *(u32 *)((s8 *)arg0 + 0x58) != 0U) {
        TAdPlyStatusGC__sub_802E11C8(*(void **)((s8 *)arg0 + 0x58));
    }
}

void TAdTimeSetGC::update_close_on_load() {
    if (!(this->load_status & 2) && (TAdPlayerLoadGC::get_instance() == 0)) {
        close_windows__23TAdSinglePlyChrSelectGCFPv(this);
        if ((s32) *(s32 *)((s8 *)this + 0x60) == 0) {
            this->m_3c = 1;
            ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0);
        }
    }
}
void TAdTimeSetGC::try_setup() {
    s32 arg0 = (s32)this;
    if (setup__23TAdSinglePlyChrSelectGCFi(get_chr_select_state__23TAdSinglePlyChrSelectGCFv()) == 0) {
        TAdSinglePlyChrSelectGC::set_player_index(0xC);
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)((void *)arg0, 0xF);
    }
}
void TAdTimeSetGC::start_settings() {
    s32 arg0 = reinterpret_cast<s32>(this);
    init_timestamped_data();
    if (check_ready__23TAdSinglePlyChrSelectGCFv() == 0) {
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)((void *)arg0, 0);
        return;
    }
    ((int (*)(void *))create_backgrounds__23TAdSinglePlyChrSelectGCFPv)((void*)arg0);
    close_and_next__23TAdSinglePlyChrSelectGCFPvPvPvPvPv((void*)arg0, (void*)(5), (void*)(-1), (void*)(-1), (void*)(-1));
}
void TAdTimeSetGC::update_close_timer() {
    *(s32 *)((s8 *)this + 0x64) = (s32) (*(s32 *)((s8 *)this + 0x64) - 1);
    if ((s32) *(s32 *)((s8 *)this + 0x64) < 0) {
        *(s32 *)((s8 *)this + 0x64) = 0;
    }
    if (!(this->load_status & 2) && (TAdPlayerLoadGC::get_instance() == 0)) {
        if (((s32) *(s32 *)((s8 *)this + 0x64) < 0xF) && (TAdSinglePlyChrSelectGC__sub_802E1868(this) != 0)) {
            *(s32 *)((s8 *)this + 0x64) = 0;
        }
        if ((s32) *(s32 *)((s8 *)this + 0x64) == 0) {
            close_windows__23TAdSinglePlyChrSelectGCFPv(this);
            if ((s32) *(s32 *)((s8 *)this + 0x60) == 0) {
                *(s32 *)&this->unk_38 = 1;
                ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0);
            }
        }
    }
}
void TAdTimeSetGC::sub_802E2848() {
    TAdTimeSetGC *p = this;
    start_load__23TAdSinglePlyChrSelectGCFv(p); ((int (*)(void *))create_backgrounds__23TAdSinglePlyChrSelectGCFPv)(p); close_and_next__23TAdSinglePlyChrSelectGCFPvPvPvPvPv(p, (void*)4, (void*)-1, (void*)-1, (void*)-1); *(int*)((char*)p + 0x64) = 30;
}
void TAdTimeSetGC::sub_802E289C() {
    TAdTimeSetGC *ad_single_ply_chr_select_gc = this;
    *(s32 *)((s8 *)ad_single_ply_chr_select_gc + 0x64) = (s32) (*(s32 *)((s8 *)ad_single_ply_chr_select_gc + 0x64) - 1);
    if ((s32) *(s32 *)((s8 *)ad_single_ply_chr_select_gc + 0x64) < 0) {
        *(s32 *)((s8 *)ad_single_ply_chr_select_gc + 0x64) = 0;
    }
    if (!(((TAdSinglePlyChrSelectGC *)ad_single_ply_chr_select_gc)->m_44 & 2) && (TAdPlayerLoadGC::get_instance() == 0)) {
        if (((s32) *(s32 *)((s8 *)ad_single_ply_chr_select_gc + 0x64) < 0xF) && (TAdSinglePlyChrSelectGC__sub_802E1868(ad_single_ply_chr_select_gc) != 0)) {
            *(s32 *)((s8 *)ad_single_ply_chr_select_gc + 0x64) = 0;
        }
        if ((s32) *(s32 *)((s8 *)ad_single_ply_chr_select_gc + 0x64) == 0) {
            close_windows__23TAdSinglePlyChrSelectGCFPv(ad_single_ply_chr_select_gc);
            if ((s32) *(s32 *)((s8 *)ad_single_ply_chr_select_gc + 0x60) == 0) {
                ((TAdSinglePlyChrSelectGC *)ad_single_ply_chr_select_gc)->m_34 = 1;
                ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(ad_single_ply_chr_select_gc, 0);
            }
        }
    }
}
void TAdTimeSetGC::init_screen() {
    reset_save_header__23TAdSinglePlyChrSelectGCFv();
    if (try_confirm_selection__23TAdSinglePlyChrSelectGCFv() == 0) {
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0);
        return;
    }
    TAdSinglePlyChrSelectGC__sub_801FD990(get_chr_select_state__23TAdSinglePlyChrSelectGCFv());
    TAdSinglePlyChrSelectGC::set_player_index(0xF);
    ((int (*)(void *))create_backgrounds__23TAdSinglePlyChrSelectGCFPv)(this);
    close_and_next__23TAdSinglePlyChrSelectGCFPvPvPvPvPv(this, (void*)(3), (void*)(-1), (void*)(-1), (void*)(-1));
    *(s32 *)((s8 *)this + 0x64) = 0x1E;
}
void TAdTimeSetGC::update_char_timer() {
    *(s32 *)((s8 *)this + 0x64) = (s32) (*(s32 *)((s8 *)this + 0x64) - 1);
    if ((s32) *(s32 *)((s8 *)this + 0x64) < 0) {
        *(s32 *)((s8 *)this + 0x64) = 0;
    }
    if (!(this->load_status & 2)) {
        if (((s32) *(s32 *)((s8 *)this + 0x64) < 0xF) && (TAdSinglePlyChrSelectGC__sub_802E1868(this) != 0)) {
            *(s32 *)((s8 *)this + 0x64) = 0;
        }
        if ((s32) *(s32 *)((s8 *)this + 0x64) == 0) {
            close_windows__23TAdSinglePlyChrSelectGCFPv(this);
            if ((s32) *(s32 *)((s8 *)this + 0x60) == 0) {
                ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0);
            }
        }
    }
}
void TAdTimeSetGC::sub_802E2A7C() {
    TAdTimeSetGC *p = this;
    *(s32*)((char*)p + 0x64) = 30;
}
typedef char RecoveredGlobal_802E2A88_lbl_804C89BC_size[sizeof(RecoveredGlobal_802E2A88_lbl_804C89BC) == 0x78 ? 1 : -1];
void TAdTimeSetGC::advance_when_load_done() {
    if (TAdPlayerLoadGC::poll_load_status(0, (const char *)(&(*(RecoveredGlobal_802E2A88_lbl_804C89BC *)&lbl_804C89BC).value)) == 0) {
        change_state(0xB);
    }
}

}

struct RecoveredGlobal_802E2BD4_lbl_804C88C0 {
    s32 value;
    u8 remaining[0x50];
};

extern "C" {

s32 load_player__23TAdSinglePlyChrSelectGCFv();
s32 load_system_file(s32);

void TAdTimeSetGC::create_backgrounds() {
    s32 arg0 = reinterpret_cast<s32>(this);
    create_backgrounds__23TAdSinglePlyChrSelectGCFPv();
    close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv(arg0, get_localized_text_entry(0x1C, 0xA), -1, 0, 0);
}
void TAdTimeSetGC::update_timer() {
    *(s32 *)((s8 *)this + 0x64) = (s32) (*(s32 *)((s8 *)this + 0x64) - 1);
    if ((s32) *(s32 *)((s8 *)this + 0x64) < 0) {
        *(s32 *)((s8 *)this + 0x64) = 0;
    }
    if (!(this->load_status & 2)) {
        if (((s32) *(s32 *)((s8 *)this + 0x64) < 0xF) && (TAdSinglePlyChrSelectGC__sub_802E1868(this) != 0)) {
            *(s32 *)((s8 *)this + 0x64) = 0;
        }
        if ((s32) *(s32 *)((s8 *)this + 0x64) == 0) {
            ((int (*)(void *))close_windows__23TAdSinglePlyChrSelectGCFPv)(this);
            if ((s32) *(s32 *)((s8 *)this + 0x60) == 0) {
                ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0);
            }
        }
    }
}
void TAdTimeSetGC::sub_802E2BC8() {
    TAdTimeSetGC *p = this;
    *(s32*)((char*)p + 0x64) = 30;
}

typedef char RecoveredGlobal_802E2BD4_lbl_804C88C0_size[sizeof(RecoveredGlobal_802E2BD4_lbl_804C88C0) == 0x54 ? 1 : -1];
void TAdTimeSetGC::sub_802E2BD4() {
    if (TAdPlayerLoadGC::poll_load_status(0, (const char *)(&(*(RecoveredGlobal_802E2BD4_lbl_804C88C0 *)&lbl_804C88C0).value)) == 0) {
        change_state(9);
    }
}

void TAdTimeSetGC::close_scene() {
    s32 arg0 = reinterpret_cast<s32>(this);
    create_backgrounds__23TAdSinglePlyChrSelectGCFPv();
    close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv(arg0, get_localized_text_entry(0x1C, 9), -1, 0, 0);
}
void TAdTimeSetGC::update_load_countdown() {
    if (((TAdPlayerLoadGC *)0)->check_card_result_code() == 0) {
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0x16);
        return;
    }
    *(s32 *)((s8 *)this + 0x64) = (s32) (*(s32 *)((s8 *)this + 0x64) - 1);
    if ((s32) *(s32 *)((s8 *)this + 0x64) < 0) {
        *(s32 *)((s8 *)this + 0x64) = 0;
    }
    if (!(this->load_status & 2)) {
        if (((s32) *(s32 *)((s8 *)this + 0x64) < 0xF) && (TAdSinglePlyChrSelectGC__sub_802E1868(this) != 0)) {
            *(s32 *)((s8 *)this + 0x64) = 0;
        }
        if ((s32) *(s32 *)((s8 *)this + 0x64) == 0) {
            *reinterpret_cast<s32 *>(this->unk_30) = 1;
            ((int (*)(void *))close_windows__23TAdSinglePlyChrSelectGCFPv)(this);
            if ((s32) *(s32 *)((s8 *)this + 0x60) == 0) {
                ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0);
            }
        }
    }
}
void TAdTimeSetGC::sub_802E2D3C() {
    TAdTimeSetGC *p = this;
    *(s32*)((char*)p + 0x64) = 30;
}

extern "C" {

void TAdTimeSetGC::update_load_state() {
    s32 arg0 = (s32)this;
    if (TAdSinglePlyChrSelectGC::is_load_complete() != 0) {
        if (((TAdPlayerLoadGC *)0)->check_card_result_code() == 0) {
            ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)((void *)arg0, 0x16);
            return;
        }
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)((void *)arg0, 7);
    }
}

}

void TAdTimeSetGC::close_and_next_cancel() { ((int (*)(void *, int, int, int, int))close_and_next__23TAdSinglePlyChrSelectGCFPvPvPvPvPv)(this, 2, -1, -1, -1); }

void TAdTimeSetGC::handle_confirm_menu() {
    if (*(void * *)&this->window == 0 || ((TWindowMenu *)(*(void * *)&this->window))->is_decided() == 0) {
        return;
    }
    switch (((TWindowMenu *)(*(void * *)&this->window))->get_selected_value()) {
    case 0:
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 6);
        break;
    case 1:
        this->state_index = -1;
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 5);
        break;
    }
}

void TAdTimeSetGC::open_char_select() {
    s32 arg0 = (s32)this;
    create_backgrounds__23TAdSinglePlyChrSelectGCFPv();
    ((s32 (*)(s32, s32))strcpy)(arg0 + 0x68, get_localized_text_entry(0x1C, 8));
    close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv(arg0, arg0 + 0x68, 1, get_localized_text_entry(0x1C, 0x29), get_localized_text_entry(0x1C, 0x16));
}
void TAdTimeSetGC::reset_on_load_complete() {
    if (TAdPlayerLoadGC::get_instance() == 0) {
        this->unknown_5c = 0;
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0x18);
    }
}
void TAdTimeSetGC::sub_802E2F20() {  }
void TAdTimeSetGC::ensure_player_loaded() {
    if (!(this->load_status & 2)) {
        load_player__23TAdSinglePlyChrSelectGCFv();
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 4);
    }
}
void TAdTimeSetGC::sub_802E2F68() {
    close_windows__23TAdSinglePlyChrSelectGCFPv(this);
}
void TAdTimeSetGC::poll_loaded_player() {
    TAdTimeSetGC *arg0 = this;
    if (TAdPlayerLoadGC::get_instance() == 0) {
        *(s32 *)((s8 *)arg0 + 0x20) = 1;
        if ((s32) *(s32 *)((s8 *)arg0 + 0x44) == 0) {
            ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(arg0, 3);
            return;
        }
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(arg0, 0);
    }
}
void TAdTimeSetGC::sub_802E2FEC() {  }
void TAdTimeSetGC::ensure_system_file_loaded() {
    if (!(this->load_status & 2)) {
        load_system_file(0);
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 2);
    }
}
void TAdTimeSetGC::sub_802E3038() {
    close_windows__23TAdSinglePlyChrSelectGCFPv(this);
}

void TAdTimeSetGC::report_card_status() {
    s32 f;
    f = this->load_status;
    if (f & 2) {
        return;
    }
    if (f & 1) {
        if (owned_object == 0) {
            ((int (*)(void *, int, int, int, int))close_and_next__23TAdSinglePlyChrSelectGCFPvPvPvPvPv)(this, 0, -1, -1, -1);
        }
        return;
    }
    if (f & 4) {
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0x11);
        return;
    }
    if (f & 8) {
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0x12);
        return;
    }
    if (f & 0x10) {
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0x13);
        return;
    }
    if (f & 0x20) {
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0x14);
        return;
    }
    if (f & 0x40) {
        if (*(s32 *)&this->unk_30 != 0) {
            ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0x14);
            return;
        }
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 5);
        return;
    }
    if (f & 0x380) {
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0x15);
        return;
    }
    if (*(s32 *)&this->unk_20 == 0 && !(f & 0x400)) {
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 1);
        return;
    }
    if (this->load_status == 0) {
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 3);
        return;
    }
    if (f & 0x400) {
        switch (f & 0x1800) {
        case 0x800:
            ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0xA);
            return;
        case 0x1800:
            break;
        case 0x1000:
        default:
            ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 8);
            return;
        }
    }
    if (check_capacity() == 0) {
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0x17);
        return;
    }
    f = this->load_status;
    if (f & 0x400) {
        if (*(s32 *)&this->m_34 != 0) {
            ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0x14);
            return;
        }
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0x10);
        return;
    }
    if (f & 0x800) {
        if (*(s32 *)&this->unk_38 != 0) {
            ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0x14);
            return;
        }
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0xD);
        return;
    }
    if (f & 0x1000) {
        if (this->m_3c != 0) {
            ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0x14);
            return;
        }
        ((s32 (*)(void *, s32))change_state__12TAdTimeSetGCFl)(this, 0xE);
    }
}

void TAdTimeSetGC::rebuild_and_maybe_close() {
    create_backgrounds__23TAdSinglePlyChrSelectGCFPv();
    ((int (*)(void *))close_windows__23TAdSinglePlyChrSelectGCFPv)(this);
    if (this->load_status & 1) {
        ((int (*)(void *, int, int, int, int))close_and_next__23TAdSinglePlyChrSelectGCFPvPvPvPvPv)(this, 0, -1, -1, -1);
    }
}

}

#undef TAdSinglePlyChrSelectGC__sub_802E1868
#undef sub_802E1F14__12TAdTimeSetGCFv
#undef change_state__12TAdTimeSetGCFl
#undef close_and_dispatch__23TAdSinglePlyChrSelectGCFPvPvPvPvPv
#undef close_and_next__23TAdSinglePlyChrSelectGCFPvPvPvPvPv
#undef close_windows__23TAdSinglePlyChrSelectGCFPv
#undef create_backgrounds__23TAdSinglePlyChrSelectGCFPv

#pragma opt_common_subs off
void TAdTimeSetGC::run_task() {
    TAdTimeSetGCStateAction *entry_action;
    load_status = poll_load_status();
    if (load_status & 1) {
        change_state(0);
    }
    TAdTimeSetGCStateAction action = *(entry_action = &time_set_state_actions[state_index].task);
    if (action != 0) {
        (this->*action)();
    }
    --timer;
    if (timer < 0) {
        timer = 0;
    }
}
#pragma opt_common_subs reset

TAdTimeSetGC::~TAdTimeSetGC() {
    if (owned_object != NULL) {
        delete owned_object;
        owned_object = NULL;
    }
    if (window != NULL) {
        ((TWindowBase *)window)->close();
        window = NULL;
    }
    if (queued_object != NULL) {
        queue_destruction__7TObjectFv(queued_object);
        queued_object = NULL;
    }
}

extern "C" {

void __ct__7TObjectFP7TObject(void *);

extern s32 __vt__12TAdTimeSetGC[];

void *TAdTimeSetGC__ct(void *ad_time_set_gc) {
    __ct__7TObjectFP7TObject(ad_time_set_gc);
    *(s32 **)((s8 *)ad_time_set_gc + 0x18) = __vt__12TAdTimeSetGC;
    ((TAdTimeSetGC *)ad_time_set_gc)->m_name = TAdTimeSetGC_class_name;
    init__23TAdSinglePlyChrSelectGCFPv(ad_time_set_gc);
    TLobby::stop_audio_streams();
    return ad_time_set_gc;
}

void TAdTimeSetGC__sub_802E34A4(void) {  }
void TAdTimeSetGC__sub_802E34A8(void) {  }

}

// The window coordinates and callback table share the startup initializer.
vec2f time_set_message_pos = {
    0.5f * (640.0f - time_set_dialog_size.x), 90.0f,
};
vec2f time_set_option_pos = {
    20.0f + time_set_message_pos.x,
    10.0f + (time_set_message_pos.y + time_set_dialog_size.y),
};
f32 time_set_option_extent = time_set_dialog_size.x - 40.0f;
vec2f time_set_calendar_pos = {
    time_set_message_pos.x + 0.5f * time_set_dialog_size.x,
    time_set_message_pos.y + time_set_dialog_size.y - 85.0f,
};

TAdTimeSetGCStateActions time_set_state_actions[25] = {
    { &TAdTimeSetGC::rebuild_and_maybe_close, &TAdTimeSetGC::report_card_status },
    { &TAdTimeSetGC::sub_802E3038, &TAdTimeSetGC::ensure_system_file_loaded },
    { &TAdTimeSetGC::sub_802E2FEC, &TAdTimeSetGC::poll_loaded_player },
    { &TAdTimeSetGC::sub_802E2F68, &TAdTimeSetGC::ensure_player_loaded },
    { &TAdTimeSetGC::sub_802E2F20, &TAdTimeSetGC::reset_on_load_complete },
    { &TAdTimeSetGC::open_char_select, &TAdTimeSetGC::handle_confirm_menu },
    { &TAdTimeSetGC::close_and_next_cancel, &TAdTimeSetGC::update_load_state },
    { &TAdTimeSetGC::sub_802E2D3C, &TAdTimeSetGC::update_load_countdown },
    { &TAdTimeSetGC::close_scene, &TAdTimeSetGC::sub_802E2BD4 },
    { &TAdTimeSetGC::sub_802E2BC8, &TAdTimeSetGC::update_timer },
    { &TAdTimeSetGC::create_backgrounds, &TAdTimeSetGC::advance_when_load_done },
    { &TAdTimeSetGC::sub_802E2A7C, &TAdTimeSetGC::update_char_timer },
    { &TAdTimeSetGC::init_screen, &TAdTimeSetGC::sub_802E289C },
    { &TAdTimeSetGC::sub_802E2848, &TAdTimeSetGC::update_close_timer },
    { &TAdTimeSetGC::start_settings, &TAdTimeSetGC::try_setup },
    { 0, &TAdTimeSetGC::update_close_on_load },
    { &TAdTimeSetGC::sub_802E2610, &TAdTimeSetGC::sub_802E2588 },
    { &TAdTimeSetGC::sub_802E2520, &TAdTimeSetGC::sub_802E24B8 },
    { &TAdTimeSetGC::sub_802E2450, &TAdTimeSetGC::sub_802E24B8 },
    { &TAdTimeSetGC::sub_802E23E8, &TAdTimeSetGC::sub_802E22A4 },
    { &TAdTimeSetGC::init_menu_window, &TAdTimeSetGC::sub_802E22A4 },
    { &TAdTimeSetGC::build_selection_summary, &TAdTimeSetGC::sub_802E22A4 },
    { &TAdTimeSetGC::create_result_bg, &TAdTimeSetGC::sub_802E2158 },
    { &TAdTimeSetGC::show_confirm_dialog, &TAdTimeSetGC::sub_802E1FAC },
    { &TAdTimeSetGC::sub_802E1F8C, &TAdTimeSetGC::finish_settings },
};

extern "C" void render__18T_ATS_DrawCalendarFv();
extern "C" void render_shadows__7TObjectFv();
extern "C" void run_task__7TObjectFv();

void *lbl_804E34FC[6] = {
    (void *)0x0, (void *)0x0, (void *)&__dt__18T_ATS_DrawCalendarFv, (void *)&run_task__7TObjectFv,
    (void *)&render__18T_ATS_DrawCalendarFv, (void *)&render_shadows__7TObjectFv,
};
