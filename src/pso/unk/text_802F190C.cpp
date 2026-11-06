#include "types.h"
#include "pso/TObject.h"

struct Obj_8003B1FC { u8 pad[0x14]; Obj_8003B1FC *child; u8 pad2[0x3c - 0x18]; u8 xf[0xC]; };

struct Ch_802F1960 { u8 pad[0x44]; f32 f; };

struct Obj_802F1960 { u8 pad0[0x14]; Ch_802F1960 *child; };

extern "C" {
s32 vec3_add_to(void *, void *);
extern void *lbl_805D6960;
void fn_802F190C(Obj_8003B1FC *self, void *arg);
void fn_802F1960(Obj_802F1960 *o, f32 d);
void fn_802F190C(Obj_8003B1FC *self, void *arg) {
    Obj_8003B1FC *c;
    while ((c = self->child) != 0) {
        vec3_add_to(c->xf, arg);
        ((TObject *)c)->set_parent((TObject *)lbl_805D6960);
    }
}
void fn_802F1960(Obj_802F1960 *o, f32 d) {
    Ch_802F1960 *c;
    while ((c = o->child) != 0) {
        c->f = c->f + d;
        ((TObject *)c)->set_parent((TObject *)lbl_805D6960);
    }
}

}
