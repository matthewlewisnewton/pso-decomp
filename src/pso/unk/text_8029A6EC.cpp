#include "types.h"
#include "pso/TAdBackGC.h"
#include "pso/TObjCMHairMenu.h"

struct Fan_8029A6EC { f32 *pos; u32 *col; s32 first; s32 count; };


extern const f32 lbl_805DDC58;
extern const f32 lbl_805DDC5C;
extern const f32 lbl_805DDC60;
extern const f32 lbl_805DDC64;
void TAdBackGC::sub_8029A6EC() {
    f32 pos[8];
    Fan_8029A6EC fan;
    u32 col[4];

    fan.pos = pos;
    fan.col = col;
    fan.first = 0;
    fan.count = 4;
    fan.pos[0] = lbl_805DDC58;
    fan.pos[1] = lbl_805DDC58;
    fan.col[0] = 0xFF;
    fan.pos[2] = lbl_805DDC58;
    fan.pos[3] = lbl_805DDC5C;
    fan.col[1] = 0xFF;
    fan.pos[4] = lbl_805DDC60;
    fan.pos[5] = lbl_805DDC5C;
    fan.col[2] = 0xFF;
    fan.pos[6] = lbl_805DDC60;
    fan.pos[7] = lbl_805DDC58;
    fan.col[3] = 0xFF;
    ((TObjCMHairMenu *)&fan)->draw_tri_fan_2d(4, 3, *(f32 *)((u8 *)this + 0x1C) - lbl_805DDC64);
}
