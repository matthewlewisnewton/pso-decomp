#include "types.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/unk/text_80197F74.h"
#include "pso/misc/TLobby.h"

struct RecoveredGlobal_80197F78_lbl_8050DD24 {
    u8 * value;
    u8 remaining[0x28];
};

extern "C" {
void **release_texture_list();
extern RecoveredGlobal_80197F78_lbl_8050DD24 signboard_texture_list;
extern int TObjSinBoard__texture_buffer;

void TLobby__sub_80197F74(void) {  }

typedef char RecoveredGlobal_80197F78_lbl_8050DD24_size[sizeof(RecoveredGlobal_80197F78_lbl_8050DD24) == 0x2C ? 1 : -1];
void **TLobby::free_global_buffer() {
    void **var_r3;
    var_r3 = (void **)((u8 *)((*(void ** *)&TObjSinBoard__texture_buffer)));
    if (var_r3 != NULL) {
        TAdSinglePlyChrSelectGC::safe_free(var_r3);
        (*(void ** *)&TObjSinBoard__texture_buffer) = NULL;
        var_r3 = (void **)(&signboard_texture_list.value);
        if ((u32) *(u32 *)((s8 *)signboard_texture_list.value + 8) != 0U) {
            var_r3 = (void **)(release_texture_list());
        }
    }
    return var_r3;
}
}

void clear_signboard_texture_buffer_pointer(void) { TObjSinBoard__texture_buffer = 0; }
