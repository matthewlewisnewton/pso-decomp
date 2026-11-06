#include "types.h"
#include "pso/misc/TLobby_80243370.h"
#include "pso/system/memory.h"
#include "pso/misc/TLobby.h"

extern "C" {
int TAdPlayerLoadGC__sub_801E263C(void*, void*, void*, void*);
extern int player_data_load_buffer;
int TLobby::get_global_63e0() {  return player_data_load_buffer; }
void TLobby::load_player_data() { TAdPlayerLoadGC__sub_801E263C((void*)0, (void*)0, (void*)player_data_load_buffer, (void*)0); }
void TLobby__sub_802433A8(void) {
    if ((u32) (*(u32 *)&player_data_load_buffer) != 0U) {
        xfree((void *)(*(u32 *)&player_data_load_buffer));
        (*(u32 *)&player_data_load_buffer) = 0U;
    }
}

}
