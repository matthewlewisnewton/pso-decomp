#include "types.h"
#include "pso/misc/TWindowSubComCardList.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowShortListCtrl.h"
#include "pso/misc/TWindowSubStatusDisp.h"
struct TWindowDrawContext;
void draw_selection_bar(TWindowDrawContext *arg0, u8 *arg1, s32 arg2);
extern "C" {
extern s32 actor_frame_tick;
void TWindowSubComCardList::draw_card_list_selection(u8 *window_key_board_soft) {
  s16 temp_r0;
  u16 *array_entry;
  if (!(actor_frame_tick & 0x10))
  {
    temp_r0 = (this->get_selected_index()) - (((PageIndicator *)m_8c)->get_type() * 7);
    if ((temp_r0 >= 0) && (temp_r0 < 7))
    {
      array_entry = (u16 *) this->get_array_entry((s32) temp_r0);
      if ((*array_entry) & 1)
      {
        draw_selection_bar((TWindowDrawContext *)window_key_board_soft, (u8 *)array_entry, 1);
      }
    }
  }
}
}
