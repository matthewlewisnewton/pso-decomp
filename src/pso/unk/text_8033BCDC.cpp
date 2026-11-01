#include "types.h"
#include "pso/misc/TCheckMemoryCard.h"
#include "pso/misc/TLobby_80132ED0.h"
#include "pso/misc/TKeyBoardControl_8000F764.h"

struct ComCardText_8033BCDC {
    s32 group;
    s32 entry;
    s32 keyboard_entry;
};


extern "C" {
extern const ComCardText_8033BCDC lbl_80477DC4[];
void fn_8033BCDC(TCheckMemoryCard *card, s32 kind, s32 menu_kind, s32 sub_entry, s32 alt_sub_entry);
}

void fn_8033BCDC(TCheckMemoryCard *card, s32 kind, s32 menu_kind, s32 sub_entry, s32 alt_sub_entry) {
    s32 text;
    s32 sub_text;
    s32 group;
    s32 entry;

    group = lbl_80477DC4[kind].group;
    entry = lbl_80477DC4[kind].entry;
    sub_text = 0;

    if ((s32)card->m_4c != 0) {
        entry = 0x6E;
    }
    if (TKeyBoardControl__sub_8000F8EC() == 0xF) {
        entry = lbl_80477DC4[kind].keyboard_entry;
    }
    text = get_localized_text_entry(group, entry);
    if (sub_entry >= 0) {
        sub_text = get_localized_text_entry(0x1C, sub_entry);
    }
    if (alt_sub_entry >= 0) {
        sub_text = get_localized_text_entry(0x1C, alt_sub_entry);
    }
    card->create_message_and_menu(text, menu_kind, sub_text, 0);
}
