#include "types.h"
#include "pso/unk/text_803CC294.h"
#include "pso/TItemLoad.h"

extern "C" {

s32 free_texture__9TItemLoadFv();
TLobby *adxf_open_afs__6TLobbyFii(s32, s32);

u32 TItemLoad::load_data(s32 arg1) {
    TLobby *file;
    if ((s32) *(s32 *)&this->m_up == 1) {
        free_texture__9TItemLoadFv();
        *(TLobby **)&this->m_flags = adxf_open_afs__6TLobbyFii(*(s32 *)&this->m_prev, arg1);
        file = *(TLobby **)&this->m_flags;
        if (file != NULL) {
            *(s32 *)&this->m_next = TLobby__sub_803CC53C(file);
        }
    }
    return *(u32 *)&this->m_flags;
}

}
