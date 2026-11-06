#include "types.h"
#include "pso/misc/TOContainerAncientItemRare.h"
#include "pso/player/TUnk_804B08BC.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

void __dl__7TObjectFPv(void *);

extern s32 __vt__26TOContainerAncientItemRare[];

void *__dt__26TOContainerAncientItemRareFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__26TOContainerAncientItemRare;
        ((TUnk_804B08BC *)arg0)->destroy_ancient_container(0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

}
