#include "types.h"
#include "pso/unk/text_8012175C.h"

extern "C" {
s32 init_item_shoot_model__13TUnk_804A0AA8Fv(int, void *, void *, void *, f32);
s32 __nw__7TObjectFUl(int);
s32 create_item_shoot_model__10TObjPlayerFiiif(s32 arg0, s32 arg1, s32 arg2, f32 farg0) {
    s32 temp_r3;
    s32 var_r0;
    s32 var_r3;
    var_r3 = 0;
    if (arg0 != 0) {
        temp_r3 = __nw__7TObjectFUl(0x6C);
        var_r0 = temp_r3;
        if (var_r0 != 0) {
            var_r0 = init_item_shoot_model__13TUnk_804A0AA8Fv((int)temp_r3, (void *)arg0, (void *)arg1, (void *)arg2, (f32)farg0);
        }
        var_r3 = var_r0;
    }
    return var_r3;
}

}
