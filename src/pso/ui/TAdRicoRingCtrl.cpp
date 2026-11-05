#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/ui/TAdRicoRingCtrl.h"
#include "pso/TAdRicoRing.h"
#include "pso/player/TObjPlayer.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct RecoveredGlobal_8001BE80_lbl_804809C0 { s32 value; u8 remaining[0xC]; };
typedef char RecoveredGlobal_8001BE80_lbl_804809C0_size[sizeof(RecoveredGlobal_8001BE80_lbl_804809C0) == 0x10 ? 1 : -1];

extern "C" {
extern RecoveredGlobal_8001BE80_lbl_804809C0 TAdRicoRingCtrl__resource_descriptor;
extern u32 TAdRicoRing__resource_bundle;
void *__ct__11TAdRicoRingFv(void *, void *);
void *__nw__7TObjectFUl(int);

void *TAdRicoRingCtrl::create(void *arg0) {
    void *o = __nw__7TObjectFUl(0x70);
    if (o != NULL) {
        o = __ct__11TAdRicoRingFv(o, arg0);
    }
    return o;
}

void TAdRicoRingCtrl::release_global_805D4A00() {
    if ((u32) TAdRicoRing__resource_bundle != 0U) {
        delete (BmlResource *)((void*)TAdRicoRing__resource_bundle);
        TAdRicoRing__resource_bundle = 0U;
    }
}

void TAdRicoRingCtrl::load_static_resource() {
    s32 temp_r3;
    s32 var_r0;
    temp_r3 = (int)new BmlResource(1, (BmlResourceDescriptor *)(&TAdRicoRingCtrl__resource_descriptor.value), 0, 0, (void *)(0));
    var_r0 = temp_r3;
    (*(s32 *)&TAdRicoRing__resource_bundle) = var_r0;
}

void TAdRicoRingCtrl__sub_8001BED0(void* p, f32 v) { *(f32*)((char*)p + 0x34) = v; }

}
