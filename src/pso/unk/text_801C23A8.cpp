#include "types.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/unk/text_801C23A8.h"
#include "pso/unk/TUnk_804C3E60.h"
#include "pso/misc/TLobby.h"

extern "C" {
extern const f32 lbl_805DC2E0;
extern TObject *tl_00;

void fn_801C23A8(s32 gain, s32 duration) {
    if (lbl_805D5D90 != NULL) {
        lbl_805D5D90->countdown = duration;
        lbl_805D5D90->gain_offset = gain;
        TLobby::set_and_notify(gain);
        return;
    }
    lbl_805D5D90 = new TUnk_804C3E60(tl_00, gain, duration);
}

TUnk_804C3E60::~TUnk_804C3E60() {
    lbl_805D5D90 = NULL;
}

void TUnk_804C3E60::run_task() {
    u8 *arg0 = (u8 *)this;
  s32 temp_r0;
  s32 temp_r0_2;
  int new_var;
  temp_r0 = (*((s32 *) (((s8 *) arg0) + 0x1C))) - 1;
  *((s32 *) (((s8 *) arg0) + 0x1C)) = temp_r0;
  if (temp_r0 <= 0)
  {
    TLobby::set_and_notify(0);
    queue_destruction__7TObjectFv(arg0);
    return;
  }
  temp_r0_2 = *((s32 *) (((s8 *) arg0) + 0x1C));
  new_var = 0x20;
  if (temp_r0_2 <= 0xF)
  {
    TLobby::set_and_notify((s32) ((lbl_805DC2E0 * ((f32) temp_r0_2)) * ((f32) (*((s32 *) (((s8 *) arg0) + new_var))))));
  }
}

}
