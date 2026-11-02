#include "types.h"
#include "pso/item/TUnk_804F112C.h"
#include "pso/TEndingPic.h"

typedef void (TEndingPic::*Handler)();

// The ending item's use effect advances the ending sequence one step for each
// technique index. The handlers live on TEndingPic; the item shares the object
// prefix they use (including the +0xF0 owner/player slot), so the original
// code invokes them on this after reinterpretation.
void TUnk_804F112C::apply_use_effect() {
    Handler handlers[9] = {
        &TEndingPic::sub_803531F8,
        &TEndingPic::sub_803531D0,
        &TEndingPic::sub_80353194,
        &TEndingPic::update_shield,
        &TEndingPic::sub_80353134,
        &TEndingPic::sub_80353110,
        &TEndingPic::update_player_object,
        &TEndingPic::sub_803530A0,
        &TEndingPic::set_phase_18,
    };
    u8 technique = get_technique();
    if (technique < 9) {
        Handler handler = handlers[technique];
        (reinterpret_cast<TEndingPic *>(this)->*handler)();
    }
}
