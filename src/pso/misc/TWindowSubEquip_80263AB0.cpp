#include "pso/misc/TWindowSubEquip_80263AB0.h"
#include "pso/misc/TWindowMainMenu.h"
#include "pso/misc/TWindowSubEquip.h"

extern "C" {
// Provisional ABI aliases retained from the surrounding menu units. Explicit
// receiver calls change register allocation; resolving this shared boundary
// requires the caller/owner recovery as a separate change.
s32 create_submenu__15TWindowMainMenuFUl(s32, s16);
s32 destroy_submenu__15TWindowMainMenuFv();
s32 fn_802449E0(u32 object);
s32 is_split_screen();

void call_if_split_screen(u32 object) {
    if (is_split_screen() != 0 && object != 0) {
        fn_802449E0(object);
    }
}

void TWindowSubEquip__sub_80263AF4() {}

f32 TWindowSubEquip__sub_80263AF8(u8* window, u32 value) {
    // Preserve the unsigned conversion: its native double bias is emitted
    // by the compiler. The concrete owner of the +0x58 field is unresolved.
    return *(f32*)(window + 0x58) - (f32)value;
}

} // extern "C"

void TWindowMainMenu::set_scale_f() {
    *(f32*)((u8*)this + 0x58) = 50300.0f;
}

void TWindowSubEquip::open_submenu(s32 object, s32 entry) {
    destroy_submenu__15TWindowMainMenuFv();
    create_submenu__15TWindowMainMenuFUl(object, (s16)entry);
}
