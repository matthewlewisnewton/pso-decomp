#include "types.h"
#include "pso/misc/TWindowSubEquip.h"
#include "pso/misc/TWindowShortListCtrl.h"

extern "C" {
s32 select_cursor_entry__22TWindowSubShortCutListFv(int);
void TWindowSubEquip::apply_slot_selection() {
    s32 temp_r31;
    temp_r31 = select_cursor_entry__22TWindowSubShortCutListFv(this->m_34);
    TWindowShortListCtrl::assign_shortcut(temp_r31, (int) (select_cursor_entry__22TWindowSubShortCutListFv(this->m_38)), this->m_28);
}

}
