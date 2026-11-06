#include "pso/TItemReverseTechPart1.h"
#include "pso/ui/TAdRicoRingCtrl_8001B4A0.h"
#include "pso/item/TItemReverseTechPart1.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/ui/TAdRicoRingCtrl.h"

#include "types.h"

extern "C" {

struct Self_80119DA0 {
    u8 pad0[0x1C];
    s32 state;
    s32 timer;
    s32 t1;
    s32 t2;
    s32 t3;
    void *ring;
};

void TAdRicoRingCtrl__sub_8001B4A0(void *, f32);
void *__nw__7TObjectFUl(int);

void TItemReverseTechPart1::run_task() {
    Self_80119DA0 *self = (Self_80119DA0 *)this;
    void *p;

    switch (self->state) {
    case 0:
        break;
    case 1:
        if (self->ring == NULL) {
            p = __nw__7TObjectFUl(0x2C);
            if (p != NULL) {
                p = TAdRicoRingCtrl__ct((TAdRicoRingCtrl *)((u8 *)p), (s32)self);
            }
            self->ring = p;
            if (self->ring != NULL) {
                ((TAdRicoRingCtrl *)(self->ring))->start_fade_all(self->t1);
            }
        }
        if (self->timer == self->t1) {
            self->state = 2;
            self->timer = 0;
        } else {
            self->timer++;
        }
        break;
    case 2:
        if (self->timer == self->t2) {
            self->state = 3;
            self->timer = 0;
            if (self->ring != NULL) {
                TAdRicoRingCtrl__sub_8001B4A0(self->ring, self->t1);
                self->ring = NULL;
            }
        } else {
            self->timer++;
        }
        break;
    case 3:
        if (self->timer == self->t3) {
            self->state = 4;
            self->timer = 0;
        } else {
            self->timer++;
        }
        break;
    case 4:
        queue_destruction__7TObjectFv(self);
        break;
    }
}

}

TItemReverseTechPart1::~TItemReverseTechPart1() {}

#include "pso/misc/TLobby.h"

extern "C" {

void __ct__7TObjectFP7TObject(void *);

extern s32 __vt__21TItemReverseTechPart1[];
extern void *lbl_805D2C4C;
extern void * TItemReverseTechPart1__instance;
extern void *tl_00;
extern s32 destroy_and_flag__21TItemReverseTechPart2Fv[];

void *TItemReverseTechPart1__ct(void *item_reverse_tech_part1) {
    void *o;
    __ct__7TObjectFP7TObject(item_reverse_tech_part1);
    *(s32 **)((s8 *)item_reverse_tech_part1 + 0x18) = __vt__21TItemReverseTechPart1;
    *(void * *)&((TItemReverseTechPart1 *)item_reverse_tech_part1)->m_name = lbl_805D2C4C;
    *(u32 *)((s8 *)item_reverse_tech_part1 + 0x1C) = 0;
    *(u32 *)((s8 *)item_reverse_tech_part1 + 0x20) = 0;
    *(u32 *)((s8 *)item_reverse_tech_part1 + 0x24) = 150;
    *(u32 *)((s8 *)item_reverse_tech_part1 + 0x28) = 3900;
    *(u32 *)((s8 *)item_reverse_tech_part1 + 0x2C) = 150;
    *(u32 *)((s8 *)item_reverse_tech_part1 + 0x30) = 0;
    TItemReverseTechPart1__instance = item_reverse_tech_part1;
    o = __nw__7TObjectFUl(0x28);
    if (o != NULL) {
        ((TLobby *)o)->init_fade(tl_00, destroy_and_flag__21TItemReverseTechPart2Fv);
    }
    return item_reverse_tech_part1;
}

}
