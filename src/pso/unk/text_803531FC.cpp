#include "types.h"
#include "pso/item/TUnk_804F112C.h"

typedef void (TUnk_804F112C::*Handler)();

// Technique index selects one of nine use-effect steps on this item. Each
// step only reads the owner pointer at +0xF0.
void TUnk_804F112C::apply_use_effect() {
    Handler handlers[9] = {
        &TUnk_804F112C::sub_803531F8,
        &TUnk_804F112C::sub_803531D0,
        &TUnk_804F112C::sub_80353194,
        &TUnk_804F112C::sub_80353158,
        &TUnk_804F112C::sub_80353134,
        &TUnk_804F112C::sub_80353110,
        &TUnk_804F112C::sub_803530C4,
        &TUnk_804F112C::sub_803530A0,
        &TUnk_804F112C::sub_8035307C,
    };
    u8 technique = get_technique();
    if (technique < 9) {
        Handler handler = handlers[technique];
        (this->*handler)();
    }
}
