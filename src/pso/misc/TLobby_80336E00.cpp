#include "types.h"
#include "pso/misc/TLobby_80336E00.h"
#include "pso/unk/TUnk_804EEF80.h"
#include "pso/misc/TLobby.h"

    extern int lobby_global_flags;
extern "C" {
void __ct__7TObjectFP7TObject(void *);

extern s32 __vt__13TUnk_804EEF80[];

void *TUnk_804EEF80::construct(void *arg1) {
    __ct__7TObjectFP7TObject(this);
    *(s32 **)((s8 *)this + 0x18) = __vt__13TUnk_804EEF80;
    *(void * *)&this->unk_1C = arg1;
    return this;
}

void TLobby__sub_80336E44(void) {  }
}
void clear_lobby_global_flags(void) { lobby_global_flags = 0; }

void TLobby::set_global_flags(s32 arg0) {
    (*(s32 *)&lobby_global_flags) |= arg0;
}
void TLobby__sub_80336E64(void) {  }
void TLobby__sub_80336E68(void) {  }
