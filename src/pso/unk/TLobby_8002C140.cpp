#include "pso/system/memory.h"
#include "pso/system/BmlResource.h"
#include "types.h"
#include "pso/unk/TLobby.h"

extern "C" {

s32 release_texture_list(void*);

extern s32 lbl_805D4B50;
extern u32 dragon_common_texture_list;

void TLobby::free_char_select() {
    if ((u32) dragon_common_texture_list != 0U) {
        release_texture_list((void*)dragon_common_texture_list);
        safe_free((void *)dragon_common_texture_list);
        dragon_common_texture_list = 0U;
    }
    delete (BmlResource *)lbl_805D4B50;
    lbl_805D4B50 = 0;
}

}
