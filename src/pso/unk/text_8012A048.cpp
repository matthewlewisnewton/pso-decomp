#include "types.h"
#include "pso/player/TObjPlayer_80128A70.h"
#include "pso/item/TUnk_804A4748.h"
#include "pso/player/TObjPlayer.h"

struct VBase_18 { char pad[0x18]; };
struct VObj_18 : VBase_18 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual s32 m49(void *, s32, s32, s32);
};

void TUnk_804A4748::emit_marker_effects() {
    u8 *arg0 = (u8 *)this;
    TObjPlayer__sub_80128A70();
    if (((VObj_18 *)(arg0))->m49(arg0 + 0x1FC, 0, 0, 1) != 0) {
        ((VObj_18 *)(arg0))->m49(arg0 + 0x208, 0, 0, 0);
        return;
    }
    ((VObj_18 *)(arg0))->m49(arg0 + 0x208, 0, 0, 1);
}
void TUnk_804A4748::reserved_53() {
    u8 *arg0 = (u8 *)this;
    ((TObjPlayer *)arg0)->draw_status_icons(arg0 + 0x1FC, arg0 + 0x208);
}
