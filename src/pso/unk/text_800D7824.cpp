#include "types.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/unk/TUnk_80494968.h"
struct P_800D78CC { u8 b[0x10]; };

struct Obj_800D78CC { u8 pad0[0x1C]; s32 count; P_800D78CC a[2]; };

struct Vec_800D7824 { f32 x, y, z; };

struct P_800D7824 { Vec_800D7824 v; s32 w; };

struct B_800D7824 { u8 pad0[0x18]; };

struct Obj_800D7824 : B_800D7824 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void flush();
    s32 count;
    P_800D7824 a[16];
    s32 w120;
    s32 w124;
};

void TUnk_80494968::vfunc_6(void *p0_arg, void *p1_arg) {
    Obj_800D7824 *self = (Obj_800D7824 *)this;
    Vec_800D7824 *p0 = (Vec_800D7824 *)p0_arg;
    Vec_800D7824 *p1 = (Vec_800D7824 *)p1_arg;
    P_800D7824 *e;
    if (self->count >= 0x10) {
        self->flush();
    }
    e = &self->a[self->count * 2];
    e[0].v.x = p0->x;
    e[0].v.y = p0->y;
    e[0].v.z = p0->z;
    e[0].w = self->w120;
    e[1].v.x = p1->x;
    e[1].v.y = p1->y;
    e[1].v.z = p1->z;
    e[1].w = self->w124;
    self->count++;
}

void TUnk_80494968::shift_line_buffer_down() {
    Obj_800D78CC *arg0 = (Obj_800D78CC *)this;
    P_800D78CC *p;
    P_800D78CC *q;
    s32 lim;
    s32 i;
    s32 n = arg0->count;
    if (n <= 1) {
        arg0->count = 0;
        return;
    }
    p = arg0->a;
    q = arg0->a + 2;
    lim = (n - 1) * 2;
    for (i = 0; i < lim; i++) {
        TAdDrawLineTask__sub_80019A8C(p++, q++);
    }
    arg0->count = arg0->count - 1;
}
