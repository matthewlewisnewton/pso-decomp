#include "types.h"
#include "pso/map/CsnQuery.h"
#include "pso/unk/text_80355970.h"
#include "pso/system/vector.h"

#include <stddef.h>
extern "C" {
s32 __nw__7TObjectFUl(int);
s32 TBoss5GryphonTornado__ct(int, void *, void *, void *, void *);
extern const f32 lbl_805D8D48;
s32 spawn_gryphon_tornado(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Vec position;
    f32 temp_f1;
    s32 boss5_gryphon_tornado;
    s32 var_r0;
    CsnHit *hit;
    VecCopy(&position, (const Vec *)(arg2));
    position.y = lbl_805D8D48;
    hit = csnVecterUnder(&position, 0x16EF);
    if (hit == NULL) {
        return 0;
    }
    temp_f1 = hit->contact->point.y;
    if (temp_f1 > lbl_805D8D48) {
        return 0;
    }
    position.y = temp_f1;
    boss5_gryphon_tornado = __nw__7TObjectFUl(0x5C);
    var_r0 = boss5_gryphon_tornado;
    if (var_r0 != 0) {
        var_r0 = TBoss5GryphonTornado__ct((int)boss5_gryphon_tornado, (void *)arg0, (void *)arg1, &position, (void *)arg3);
    }
    return var_r0;
}

}
