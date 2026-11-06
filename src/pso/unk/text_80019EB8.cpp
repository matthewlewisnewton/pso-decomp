#include "types.h"
struct V_80019EB8 { f32 x; f32 y; f32 z; f32 w; };

struct O_80019EB8 { u8 pad[0x2c]; f32 f2c; u8 pad2[0x3c - 0x30]; f32 f3c; u8 pad3[0x5c - 0x40]; f32 f5c; u8 pad4[0x6c - 0x60]; V_80019EB8 v[4]; };

extern "C" {
extern const f32 lbl_805D7DDC;
extern const f32 lbl_805D7DE0;
void fn_80019EB8(O_80019EB8 *self, f32 f);
void fn_80019EB8(O_80019EB8 *self, f32 f) {
    s32 i;
    f32 s;
    if (lbl_805D7DDC == f) {
        return;
    }
    s = lbl_805D7DE0 / f;
    self->f2c = s;
    self->f3c = s;
    self->f5c = lbl_805D7DDC;
    for (i = 0; i < 4; i++) {
        self->v[i].x = s;
    }
}

}
