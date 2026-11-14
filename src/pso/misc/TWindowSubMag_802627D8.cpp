#include "pso/item/TItemTexLoad.h"
#include "pso/misc/TWindowSubMag_802627D8.h"
#include "pso/misc/TWindowKeyBoardSoft.h"

#include "types.h"
#include "pso/misc/TWindowLoadItemTexture.h"

extern "C" {
int TWindowSubMag__sub_802627D8(void* p) { return *(u32*)((char*)p + 0x60) & 0x1; }
int TWindowKeyBoardSoft::is_cursor_locked() { return (this->m_60 >> 7) & 0x1; }
int TWindowKeyBoardSoft::get_flag_bit6() { return (this->m_60 >> 6) & 0x1; }
int TWindowKeyBoardSoft::get_flag_bit5() { return (this->m_60 >> 5) & 0x1; }
int TWindowSubMag__sub_80262808(void* p) { return *(u16*)((char*)p + 0x62) & 0x8; }

void TWindowLoadItemTexture::sub_80262814(s32 item) {

    *(u16 *)get_array_entry(0) |= 2;
    if (m_6c->load_item_icon((TItemData*)item) != 0) {
        m_60 = 1;
        return;
    }
    m_60 = 2;
}
void fn_8026287C(TWindowLoadItemTexture *arg0) {
    u8 *temp_r3;
    temp_r3 = (u8 *)(((s32)arg0->get_array_entry(0)));
    *(u8 **)((s8 *)temp_r3 + 0x30) = (u8 *)&arg0->m_70;
    *(u16 *)((s8 *)temp_r3 + 0) = (u16) (*(u16 *)((s8 *)temp_r3 + 0) & 0xFFFFFFFD);
}

}
