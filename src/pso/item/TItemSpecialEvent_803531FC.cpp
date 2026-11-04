#include "types.h"
#include "pso/item/TItemSpecialEvent.h"

typedef void (TItemSpecialEvent::*Handler)();

// Technique index selects one of nine use-effect steps on this item. Each
// step only uses TObjPlayer *owner.
void TItemSpecialEvent::apply_use_effect() {
    Handler handlers[9] = {
        &TItemSpecialEvent::sub_803531F8,
        &TItemSpecialEvent::sub_803531D0,
        &TItemSpecialEvent::sub_80353194,
        &TItemSpecialEvent::sub_80353158,
        &TItemSpecialEvent::sub_80353134,
        &TItemSpecialEvent::sub_80353110,
        &TItemSpecialEvent::sub_803530C4,
        &TItemSpecialEvent::sub_803530A0,
        &TItemSpecialEvent::sub_8035307C,
    };
    u8 technique = get_technique();
    if (technique < 9) {
        Handler handler = handlers[technique];
        (this->*handler)();
    }
}
