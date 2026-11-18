#include "types.h"
#include "pso/player/TObjChara.h"
#include "pso/misc/CameraDistanceFade.h"
#include "pso/player/TUnk_804B6C24.h"
#include "pso/player/TObjPlayer.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TOAirconCave01.h"

extern "C" {

void __dl__7TObjectFPv(void *);

extern s32 __vt__13TUnk_804B6C24[];

void *__dt__13TUnk_804B6C24Fv(TUnk_804B6C24 *container, s16 deleting) {
    if (container != NULL) {
        *(s32 **)((s8 *)container + 0x18) = __vt__13TUnk_804B6C24;
        ((CameraDistanceFade *)((s8 *)container + 0x340))->CameraDistanceFade::~CameraDistanceFade();
        __dt__9TObjCharaFv(container, 0);
        if (deleting > 0) {
            __dl__7TObjectFPv(container);
        }
    }
    return container;
}

void TUnk_804B6C24::vfunc_6(s16 *, s32) {  }

}
