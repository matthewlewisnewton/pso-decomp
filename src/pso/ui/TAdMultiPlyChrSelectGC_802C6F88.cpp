#include "types.h"
#include "pso/misc/TLobby_8001D6A0.h"
#include "pso/ui/TAdMultiPlyChrSelectGC_802C6F88.h"
#include "pso/ui/TAdMultiPlyChrSelectGC.h"

extern "C" {

s32 TAdMultiPlyChrSelectGC::get_field_20() { return this->m_20; }

    extern u8 *TAdMultiPlyChrSelectGC__instance;
int TAdMultiPlyChrSelectGC::get_state() {  return (int)TAdMultiPlyChrSelectGC__instance; }

    extern int plyplt_anim_ctrl_instance;
int TAdMultiPlyChrSelectGC::get_selected_slot() {  return plyplt_anim_ctrl_instance; }

    extern int menu_selection_cursor_texture_list;
int TAdMultiPlyChrSelectGC::get_global_6700() {  return menu_selection_cursor_texture_list; }

    extern int lbl_805D6668;
int TAdMultiPlyChrSelectGC__sub_802C6FA8(void) {  return lbl_805D6668; }

extern u32 lbl_805D67E8;

void TAdMultiPlyChrSelectGC::update_transition_anim_if_active() {
    if ((u32) lbl_805D67E8 != 0U) {
        ((TAdMultiPlyChrSelectGC *)lbl_805D67E8)->update_transition_anim();
    }
}

extern const f32 lbl_805DE5A8;
extern const f32 lbl_805DE5AC;
extern const f32 lbl_805DE5B0;

void TAdMultiPlyChrSelectGC::update_transition_anim() {
    f32 var_f31;
    f32 var_f4;
    s32 temp_r3;
    s32 temp_r3_2;

    temp_r3 = *(s32 *)&this->grid.m_40;
    if (temp_r3 <= 0x96) {
        var_f4 = lbl_805DE5A8;
        var_f31 = (lbl_805DE5AC - (f32) temp_r3) / lbl_805DE5AC;
    } else {
        temp_r3_2 = temp_r3 - 0x96;
        var_f31 = lbl_805DE5A8;
        var_f4 = (lbl_805DE5AC - (f32) temp_r3_2) / lbl_805DE5AC;
    }
    TLobby__sub_8001EA5C(*(f32 *)&this->m_1c, *(f32 *)&this->m_20, lbl_805DE5B0, var_f4);
    TLobby__sub_8001E998(this->grid.m_2c, *(f32 *)&this->grid.unk_30, lbl_805DE5B0, var_f31);
}

}
