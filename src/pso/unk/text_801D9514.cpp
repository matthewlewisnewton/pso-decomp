#include "types.h"
#include "pso/player/TObjPlayer_801D9E08.h"
#include "pso/unk/text_801D9514.h"

struct RecoveredGlobal_801D9514_lbl_804C49F0
{
  s32 value;
  u8 remaining[0x2C];
};

extern "C" {
char TObjPlayer__sub_801AFDBC();
extern RecoveredGlobal_801D9514_lbl_804C49F0 class_technique_cap_table;
typedef struct RecoveredGlobal_801D9514_lbl_804C49F0 RecoveredGlobal_801D9514_lbl_804C49F0;
typedef char RecoveredGlobal_801D9514_lbl_804C49F0_size[((sizeof(RecoveredGlobal_801D9514_lbl_804C49F0)) == 0x30) ? (1) : (-1)];
u8 TObjPlayer__sub_801D9514(s32 arg0, s16 arg1) {
  u8 *new_var;
  new_var = ((u8 *)&class_technique_cap_table.value) + (TObjPlayer__sub_801AFDBC() * 4);
  return *((u8 *) (((s8 *) ((*((s32 *) (((s8 *) new_var) + 0))) + arg1)) + 0));
}

void TObjPlayer__sub_801D955C(u8 *arg0, void *arg1) {
    s32 i;
    s32 n = TObjPlayer__sub_801D9E08();
    for (i = 0; i < n; ) {
        arg0[i + 0x5C] = ((u8 (*)(void *, s16))TObjPlayer__sub_801D9514)(arg1, i);
        i++;
    }
}

}
