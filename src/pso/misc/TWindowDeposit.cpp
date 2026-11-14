#include "pso/misc/WindowLayoutDescriptor.h"
#include "types.h"
#include "pso/misc/TWindowSubStatusDisp_80144B14.h"
#include "pso/misc/TWindowSubStatusDisp_8025A9B4.h"
#include "pso/misc/TWindowSubStatusDisp_80287570.h"
#include "pso/ui/TObjBagWarnWin_8006EF24.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TWindowMainMenu.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowDeposit.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowSubStatusDisp.h"

extern "C" {
s32 draw_visible_window_entries(void *, void *, int);
s32 get_window_layout_position(int);
extern u8 lbl_804CEB30[];
WindowLayoutDescriptor window_deposit_layout = { {160.0f, 27.0f}, 50100.0f, lbl_804CEB30, 0x82BU };
extern s32 TWindowDeposit__name;
static const f32 lbl_805DCC60 = 96.0f;
static const f32 lbl_805DCC64 = 12.0f;
static const f32 lbl_805DCC68 = 8.0f;
static const f32 lbl_805DCC6C = 0.75f;
extern const f32 lbl_805DCC70;
s32 draw_window_tab(s32, s32, s32, f32);
void __dl__7TObjectFPv(void *);
int initialize_subwindow__9TWindowDDFv(void*);

void TWindowDeposit::render_status(s32 arg1) {
    draw_window_tab(arg1, arg1 + 0x10, 3, this->m_60);
}

void TWindowDeposit::render() {
    s32 context = setup_window_draw_context((s32)&m_64);
    render_status(context);
    draw_visible_window_entries(this, &m_24, context);
}

void TWindowDeposit::run_task() { initialize_subwindow__9TWindowDDFv(this); update_window_entry_list((char*)this + 0x24); }

TWindowDeposit::~TWindowDeposit() {}
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_dead_assignments off
TWindowDeposit::TWindowDeposit(s16 arg1)
    : TWindowBase((u8 *)&window_deposit_layout, arg1, (u8 *)get_window_layout_position(0x29)) {
  u8 *temp_r30;
  u32 spC;
  s32 sp8;
  f32 temp_f31;
  s32 str;
  u32 temp_r3_2;
  u8 *temp_r31;
  *((s32 *) (((s8 *) ((u8 *)this)) + 0)) = (s32) TWindowDeposit__name;
  str = TQuestVmDownLoadServer__sub_8006EF6C(2);
  temp_r3_2 = calc_text_width((char *)str);
  spC = temp_r3_2;
  sp8 = 0x43300000;
  temp_f31 = (f32) temp_r3_2;
  ((TWindowDeposit *)((u8 *)this))->m_60 = TWindowSubStatusDisp__sub_802877A4(lbl_805DCC60 + (lbl_805DCC64 + temp_f31));
  temp_r30 = (u8 *) ((u8 *)((TWindowBase *)((u8 *)this))->get_array_entry(0));
  temp_r31 = (u8 *) ((u8 *)((TWindowBase *)((u8 *)this))->get_array_entry(1));
  set_text_entry_string(temp_r30, str, 0);
  *((f32 *) (((s8 *) temp_r31) + 8)) = (f32) (lbl_805DCC60 + (lbl_805DCC64 + (lbl_805DCC68 + temp_f31)));
  ((TWindowDeposit *)((u8 *)this))->m_38 = TWindowSubStatusDisp::get_base_y(((TWindowDeposit *)((u8 *)this))->m_60);
  ((TWindowBase *)((u8 *)this))->save_position();
  if (TCameraCtrl::get_camera_id() > 2)
  {
    *((f32 *) (((s8 *) ((u8 *)this)) + 0x64)) = (f32) lbl_805DCC6C;
    *((f32 *) (((s8 *) ((u8 *)this)) + 0x68)) = (f32) lbl_805DCC6C;
  }
  else
  {
    *((f32 *) (((s8 *) ((u8 *)this)) + 0x64)) = (f32) lbl_805DCC70;
    *((f32 *) (((s8 *) ((u8 *)this)) + 0x68)) = (f32) lbl_805DCC70;
  }

}

}
