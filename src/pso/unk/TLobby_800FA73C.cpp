#include "pso/system/memory.h"
#include "types.h"
#include "pso/unk/text_800FA260.h"
#include "pso/unk/TLobby.h"

extern "C" {

int __dt__5THeapFv(void*, void*);

    extern int async_file_read_sector_buffer;
    extern int game_heap;
void TLobby::destroy_game_heap() { process_pending_resources(); safe_free((void *)async_file_read_sector_buffer); TLobby::free_chr_select_data(); __dt__5THeapFv((void*)game_heap, (void*)1); }

}
