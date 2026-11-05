#include "types.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/system/memory.h"
#include "pso/system/vector.h"
#include "pso/boss/TObjBoss8PillerCtrl.h"

struct RecoveredGlobal_8035C22C_lbl_804799DC {
    s32 value;
    u8 remaining[0x148];
};

struct RecoveredGlobal_8035C22C___vt__19TObjBoss8PillerCtrl {
    s32 value;
    u8 remaining[0x14];
};

struct Vec_8035C03C { f32 x, y, z; };

struct Ent_8035C03C { s32 x; s32 y; };

struct Self_8035C03C {
    u8 pad0[0x1c];
    Vec_8035C03C pos;
    s32 f28;
    u16 f2C;
    u8 pad2e[0x34 - 0x2e];
    Ent_8035C03C *list;
};

extern "C" {
s32 __ct__7TObjectFP7TObject();
extern RecoveredGlobal_8035C22C_lbl_804799DC boss8_piller_ctrl_params;
extern s32 __vt__19TObjBoss8PillerCtrl[];
extern s32 TObjBoss8PillerCtrl__class_name;
extern const f32 lbl_805E017C;
void *__nw__7TObjectFUl(u32);
void __ct__15TObjBoss8PillerFv(void *, s32, Vec_8035C03C *, f32, u16);
s32 fn_8035BFF8(void *, Vec_8035C03C *);
extern s32 tl_05;
extern const f32 lbl_805E016C;
extern const f32 lbl_805E0170;
extern const f32 lbl_805E0174;
extern const f32 lbl_805E0178;
void run_task__19TObjBoss8PillerCtrlFv(Self_8035C03C *self);
void __dl__7TObjectFPv(void *);
void __dt__7TObjectFv(void *, int);

void TObjBoss8PillerCtrl__sub_8035C034(void * _w0, void * _w1) {  }
void TObjBoss8PillerCtrl::render() {  }

#pragma fp_contract on
void run_task__19TObjBoss8PillerCtrlFv(Self_8035C03C *self) {
    Vec_8035C03C v;
    void *p;
    switch (self->f28) {
    case 0:
    case 5:
    case 10:
    case 15:
        while (self->list->y != 0xFFFF) {
            VecCopy((Vec *)&v, (const Vec *)&self->pos);
            v.x = lbl_805E016C * self->list->y + v.x;
            v.z = lbl_805E0170 * self->list->x + v.z;
            if (self->list->y & 1) {
                v.z += lbl_805E0174;
            }
            if (fn_8035BFF8(self, &v) == 0) {
                p = __nw__7TObjectFUl(0x34);
                if (p != NULL) {
                    __ct__15TObjBoss8PillerFv(p, tl_05, &v, lbl_805E0178, self->f2C);
                }
            }
            self->list++;
        }
        self->list++;
        break;
    }
    if (self->f28++ > 0x32) {
        queue_destruction__7TObjectFv(self);
    }
}

void *__dt__19TObjBoss8PillerCtrlFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__19TObjBoss8PillerCtrl;
        if (*(void **)((s8 *)arg0 + 0x30) != NULL) { ::operator delete(*(void **)((s8 *)arg0 + 0x30)); ((TObjBoss8PillerCtrl *)arg0)->m_30 = 0; }
        __dt__7TObjectFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}
typedef char RecoveredGlobal_8035C22C_lbl_804799DC_size[sizeof(RecoveredGlobal_8035C22C_lbl_804799DC) == 0x14C ? 1 : -1];
typedef char RecoveredGlobal_8035C22C___vt__19TObjBoss8PillerCtrl_size[sizeof(RecoveredGlobal_8035C22C___vt__19TObjBoss8PillerCtrl) == 0x18 ? 1 : -1];
u8 *TObjBoss8PillerCtrl__ct(u8 *boss8_piller_ctrl, s32 arg1, s32 arg2, s16 arg3) {
    __ct__7TObjectFP7TObject();
    *(s32 **)((s8 *)boss8_piller_ctrl + 0x18) = &(*(RecoveredGlobal_8035C22C___vt__19TObjBoss8PillerCtrl *)&__vt__19TObjBoss8PillerCtrl).value;
    *(s32 *)((s8 *)boss8_piller_ctrl + 0) = (s32) TObjBoss8PillerCtrl__class_name;
    VecCopy((Vec *)(boss8_piller_ctrl + 0x1C), (const Vec *)(arg2));
    TObjBoss8PillerCtrl__sub_8035C034(boss8_piller_ctrl, boss8_piller_ctrl + 0x1C);
    *(f32 *)((s8 *)boss8_piller_ctrl + 0x20) = (f32) lbl_805E017C;
    ((TObjBoss8PillerCtrl *)boss8_piller_ctrl)->m_28 = 0;
    ((TObjBoss8PillerCtrl *)boss8_piller_ctrl)->m_2c = arg3;
    ((TObjBoss8PillerCtrl *)boss8_piller_ctrl)->m_30 = 0;
    *(s32 **)((s8 *)boss8_piller_ctrl + 0x34) = &boss8_piller_ctrl_params.value;
    return boss8_piller_ctrl;
}

}
