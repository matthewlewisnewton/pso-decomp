#include "types.h"
struct O_80362638 { u8 pad0[4]; u8 b4; u8 b5; u8 b6; u8 b7; };

struct A_80362638 { u8 pad0[4]; f32 f4; f32 f8; f32 fC; };

extern "C" {
extern O_80362638 *epsilon_guard_part_color_table[];
void set_guard_part_colors(void *arg0, A_80362638 *arg1);
void set_guard_part_colors(void *arg0, A_80362638 *arg1) {
    s32 i;
    for (i = 0; i < 9; i++) {
        epsilon_guard_part_color_table[i]->b7 = (u8)arg1->f4;
        epsilon_guard_part_color_table[i]->b4 = (u8)arg1->f8;
        epsilon_guard_part_color_table[i]->b5 = (u8)arg1->fC;
    }
}

}
