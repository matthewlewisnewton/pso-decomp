#include "types.h"
struct Obj_803D64F8 {
    f32 a, b, c, d, e, f;
    s32 g;
    s32 h;
    f32 i, j;
};

extern "C" {
extern const f32 lbl_805E0DF0;
extern const f32 lbl_805E0DF4;
extern const f32 lbl_805E0DF8;
void fn_803D64F8(Obj_803D64F8 *p);
#pragma push
#pragma scheduling off
void fn_803D64F8(Obj_803D64F8 *p) {
    p->a = lbl_805E0DF0;
    p->b = lbl_805E0DF0;
    p->c = lbl_805E0DF0;
    p->d = lbl_805E0DF0;
    p->e = lbl_805E0DF0;
    p->f = lbl_805E0DF4;
    p->g = 0;
    p->h = 0x2aaa;
    p->i = lbl_805E0DF4;
    p->j = lbl_805E0DF8;
}
#pragma pop

}
