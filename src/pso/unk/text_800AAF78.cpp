#include "types.h"
#include "pso/enemy/TObjEneDubchik.h"

struct RecoveredGlobal_800AAF78_lbl_805009B8 {
    s32 value;
    u8 remaining[0x134];
};

struct T_800AAF98 { u8 pad[0x18]; s32 arr[1]; };

struct O_800AAF98 { u8 pad[0x368]; s32 x368; };

extern "C" {
extern RecoveredGlobal_800AAF78_lbl_805009B8 lbl_805009B8;
s32 TObjPlayer__sub_800AAF98(O_800AAF98 *self, s32 i);
typedef char RecoveredGlobal_800AAF78_lbl_805009B8_size[sizeof(RecoveredGlobal_800AAF78_lbl_805009B8) == 0x138 ? 1 : -1];
f32 TObjEneDubchik::sub_800AAF78(s32 arg1) {
    return *(f32 *)((s8 *)(*(s32 *)((s8 *)((u8 *)&lbl_805009B8.value + (this->variant * 4)) + 0) + (arg1 * 4)) + 0);
}
s32 TObjPlayer__sub_800AAF98(O_800AAF98 *self, s32 i) {
    return ((T_800AAF98 * *)&lbl_805009B8)[self->x368]->arr[i];
}

}
