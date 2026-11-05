#include "types.h"
#include "pso/player/TObjPlayer_8023E480.h"
#include "pso/ui/TAdMcSelectCursorGC_8032A610.h"
#include "pso/ui/TAdMcSelectCursorGC.h"

extern "C" {
s32 release_texture_list(void *, s32);
extern int TAdMcSelectCursorGC__texture_entry;
u32 TAdMcSelectCursorGC__ct(u32, s32);
u32 __nw__7TObjectFUl(s32);

extern u32 TAdMcSelectCursorGC__instance;

u32 TAdMcSelectCursorGC::get_instance(s32 arg0) {
    u32 var_r0;

    if ((u32) TAdMcSelectCursorGC__instance == 0U) {
        var_r0 = __nw__7TObjectFUl(0x140);
        if (var_r0 != 0U) {
            var_r0 = TAdMcSelectCursorGC__ct(var_r0, arg0);
        }
        TAdMcSelectCursorGC__instance = var_r0;
    }
    return TAdMcSelectCursorGC__instance;
}

    extern unsigned char lbl_80477118[];
    extern unsigned char mc_select_cursor_texture_list[];

void TAdMcSelectCursorGC::release_cursor_entry() {
    u8 *temp_r4;
    if ((void **) (*(void ** *)&TAdMcSelectCursorGC__texture_entry) != NULL) {
        temp_r4 = (u8 *)(*(*(void ** *)&TAdMcSelectCursorGC__texture_entry));
        if ((u32) *(u32 *)((s8 *)temp_r4 + 8) != 0U) {
            release_texture_list((*(void ** *)&TAdMcSelectCursorGC__texture_entry), (s32) temp_r4);
        }
    }
}

void TAdMcSelectCursorGC::init_resource() { TAdMcSelectCursorGC__texture_entry = (int)mc_select_cursor_texture_list; TLobby__sub_8023E4B4((s32)lbl_80477118, (s32)mc_select_cursor_texture_list); }

s32 TAdMcSelectCursorGC__sub_8032A6D8(void* p) { return *(s32*)((char*)p + 0x1c); }

    extern int memcard_cursor_instance_table[];
int TAdMcSelectCursorGC::get_cursor_type(int a0) {  return memcard_cursor_instance_table[a0]; }

}
