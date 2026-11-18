#include "pso/misc/PageIndicator.h"
#include "pso/misc/TWindowDrawContext.h"
#include "types.h"
#include "pso/misc/TWindowMessage.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowHelpItem_80255AB4.h"
#include "pso/misc/TWindowSubComCard_8007A810.h"
#include "pso/misc/TWindowSubCustomEquip_80275D9C.h"
#include "pso/misc/TWindowSubCustomSelect_80275D84.h"
#include "pso/misc/TWindowSubStatusDisp_80228CC0.h"
#include "pso/unk/text_80076E84.h"
#include "pso/unk/text_80263A20.h"
#include "pso/misc/TWindowMenu.h"
#include "pso/misc/TUnk_804D1160.h"
#include "pso/misc/TWindowSubComCardList.h"
#include "pso/misc/TWindowSubCustomEquip.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TWindowOptionCtrl.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowSubCustomSelect.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/object/TObjCityMainWarp.h"
#include "pso/ui/Language.h"

#pragma readonly_strings on

extern "C" {
const char *TWindowSubComCardList__class_name = "TWindowSubComCardList";
}


extern "C" {
s32 TWindowSubComCardList__sub_80275360(void *);
extern s32 local_client_id;
s32 count_leading_active__17TWindowSubComCardFPvi(s32, s32);
s32 draw_visible_window_entries(void *, void *, s32);
s32 forward_render__20TWindowSubStatusDispFv(s32, s32);

void TWindowSubComCardList::render() {
    TWindowSubComCardList *arg0 = this;
    s32 temp_r3;

    temp_r3 = (s32)get_draw_context__11TWindowBaseFPv(arg0);
    ((TWindowBase *)arg0)->draw_window_frame((void *)temp_r3);
    draw_visible_window_entries(arg0, (u8 *)arg0 + 0x24, temp_r3);
    ((TWindowMenu *)arg0)->render_selected_entry(temp_r3);
    arg0->draw_card_list_selection((u8 *)temp_r3);
    if ((u32) arg0->m_88 != 0U) {
        forward_render__20TWindowSubStatusDispFv(arg0->m_88, temp_r3);
    }
    if ((u32) arg0->m_8c != 0U) {
        draw_list_page_indicator((PageIndicator *)(arg0->m_8c), (TWindowDrawContext *)(temp_r3));
    }
}

void TWindowSubComCardList::run_task() {
    TWindowMenu::run_task();
    if ((is_decided() == 0) && (handle_list_page_flip_input((PageIndicator *)(this->m_8c)) != 0)) {
        set_selected_index(0);
        TWindowSubComCardList__sub_80275360(this);
    }
}

TWindowSubComCardList::~TWindowSubComCardList() {
    delete_if_allocated((void *)m_8c, 1);
}

TWindowSubComCardList::TWindowSubComCardList(void *position)
    : TWindowMenu(7, 4, position) {
    m_name = TWindowSubComCardList__class_name;
    s32 pages = TWindowSubStatusDisp::round_away_from_zero((f32)TWindowSubComCard::count_active_cards() / 7.0f);
    if (pages <= 0) pages = 1;
    m_8c = (u32)new PageIndicator(0, (s8)pages, local_client_id);
    m_90 = 0;
    m_94 = get_card_entry__17TWindowSubComCardFi(0);
    m_98 = 0xD2;
    m_9c = 0;
    set_flag70_bit100();
    set_selected_index(0);
    TWindowSubComCardList__sub_80275360(this);
    set_flag70_bit10();
    set_scroll_target(223.0f, 184.0f);
}

TWindowSubComCardList::TWindowSubComCardList(void *position, s32 records, s32 count, s32 mode)
    : TWindowMenu(7, 4, position) {
    m_name = TWindowSubComCardList__class_name;
    s32 pages = TWindowSubStatusDisp::round_away_from_zero((f32)count_leading_active__17TWindowSubComCardFPvi(records, count) / 7.0f);
    if (pages <= 0) pages = 1;
    m_8c = (u32)new PageIndicator(0, (s8)pages, local_client_id);
    m_90 = records;
    m_94 = 0;
    m_98 = count;
    m_9c = (u8)mode;
    set_flag70_bit100();
    set_selected_index(0);
    TWindowSubComCardList__sub_80275360(this);
    set_flag70_bit10();
    set_scroll_target(223.0f, 184.0f);
}

}
