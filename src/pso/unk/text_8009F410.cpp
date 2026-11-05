#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/unk/text_8009F410.h"

#include <stddef.h>

struct RecoveredGlobal_803626A8_lbl_80479FBC {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_803626A8_lbl_8058D490 {
    s32 value;
    u8 remaining[0x2C];
};

struct RecoveredGlobal_80362B48___vt__14TObjEneEpsilon {
    s32 value;
    u8 remaining[0x1A0];
};

struct VBase_18_c22f9c
{
  char pad[0x18];
};

struct VObj_18_c22f9c : VBase_18_c22f9c {
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
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual void m63(s32, void *);
};

struct T_80362C80
{
  u8 pad0[0xF0];
  VObj_18_c22f9c *obj;
};

struct S_80362C80
{
  s32 v;
};

class V_8036274C {
public:
    u8 pad[0xC];
    virtual ~V_8036274C();
};

extern "C" {
extern u8 *lbl_805D4FD0;
extern u8 *lbl_805D4FE0;
extern u8 *lbl_805D4FDC;
typedef char RecoveredGlobal_803626A8_lbl_80479FBC_size[sizeof(RecoveredGlobal_803626A8_lbl_80479FBC) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_803626A8_lbl_8058D490_size[sizeof(RecoveredGlobal_803626A8_lbl_8058D490) == 0x30 ? 1 : -1];
typedef char RecoveredGlobal_80362B48___vt__14TObjEneEpsilon_size[sizeof(RecoveredGlobal_80362B48___vt__14TObjEneEpsilon) == 0x1A4 ? 1 : -1];
void fn_8009F410(void) {
    if ((*(V_8036274C * *)&lbl_805D4FE0) != NULL) {
        delete (*(V_8036274C * *)&lbl_805D4FE0);
        (*(V_8036274C * *)&lbl_805D4FE0) = NULL;
    }
    if ((*(V_8036274C * *)&lbl_805D4FDC) != NULL) {
        delete (*(V_8036274C * *)&lbl_805D4FDC);
        (*(V_8036274C * *)&lbl_805D4FDC) = NULL;
    }
    if ((*(u32 *)&lbl_805D4FD0) != 0) {
        delete (BmlResource *)((void *)(*(u32 *)&lbl_805D4FD0));
        (*(u32 *)&lbl_805D4FD0) = 0;
    }
}
typedef struct S_80362C80 S_80362C80;
typedef struct T_80362C80 T_80362C80;
typedef struct VBase_18_c22f9c VBase_18_c22f9c;
typedef struct VObj_18_c22f9c VObj_18_c22f9c;

}
