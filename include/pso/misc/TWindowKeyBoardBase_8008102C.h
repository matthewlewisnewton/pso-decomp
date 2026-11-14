#ifndef PSO_MISC_TWINDOWKEYBOARDBASE_8008102C_H
#define PSO_MISC_TWINDOWKEYBOARDBASE_8008102C_H

#include "types.h"

extern "C" {
// Historical export; receives a 24-byte text-holder prefix, not a window.
s32 *init_text_buffer_holder__19TWindowKeyBoardBaseFv(void *storage);
u8 *TEF_LensFlare__create(s32 arg0);
u32 *destroy__19TWindowKeyBoardBaseFPvs(u32 *arg0, s16 arg1);
}
void init_keyboard_text_buffer(u8 *arg0, u32 arg1, u32 arg2);

#endif
