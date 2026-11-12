#include "types.h"
#include "pso/unk/text_800FA260.h"
#include "pso/misc/TLobby.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

extern "C" {

int __dt__5THeapFv(void*, void*);

    extern int async_file_read_sector_buffer;
    extern int game_heap;
void TLobby::destroy_game_heap() { process_pending_resources(); TAdSinglePlyChrSelectGC::safe_free((void *)((void*)async_file_read_sector_buffer)); TLobby::free_chr_select_data(); __dt__5THeapFv((void*)game_heap, (void*)1); }

}
