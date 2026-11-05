#include "types.h"
#include "pso/misc/TPlyPtclObjectLeftHand.h"

struct VBase_PTR18_8030A400 { char pad[0x18]; };
struct VObj_PTR18_8030A400 : VBase_PTR18_8030A400 {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
    virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27();
    virtual void m28(); virtual void m29(); virtual void m30(); virtual void m31();
    virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35();
    virtual void m36(); virtual void m37(); virtual void m38(); virtual void m39();
    virtual void m40(); virtual void m41(); virtual void m42(); virtual void m43();
    virtual void m44(); virtual void m45(); virtual void m46(); virtual void m47();
    virtual void m48(); virtual void m49(); virtual void m50(); virtual void m51();
    virtual void m52(); virtual void m53(); virtual void m54(); virtual void m55();
    virtual void m56(); virtual void m57(); virtual void m58(); virtual void m59();
    virtual void m60(); virtual void m61(); virtual void m62();
    virtual s32 m63(s32, s32);
};

extern "C" {

void *__dt__22TPlyPtclObjectLeftHandFv(void *arg0, s16 arg1);
void *get_player_by_client_id(s32 i);
void __dl__7TObjectFPv(void *);
void *__dt__22TPlyFollowParticleCtrlFv(void *arg0, s16 arg1);
u16 get_lifetime__22TPlyFollowParticleCtrlFv();
s32 get_position_ptr__10TObjPlayerFv(s32);

s32 TPlyPtclObjectLeftHand::update_attachment(s32 arg0) {
    void *player;

    player = get_player_by_client_id((u16) get_lifetime__22TPlyFollowParticleCtrlFv());
    if (player == NULL) {
        return 0;
    }
    ((VObj_PTR18_8030A400 *) player)->m63(0x23, get_position_ptr__10TObjPlayerFv(arg0));
    return get_position_ptr__10TObjPlayerFv(arg0);
}

extern s32 __vt__22TPlyPtclObjectLeftHand[];

void *__dt__22TPlyPtclObjectLeftHandFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__22TPlyPtclObjectLeftHand;
        __dt__22TPlyFollowParticleCtrlFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

}
