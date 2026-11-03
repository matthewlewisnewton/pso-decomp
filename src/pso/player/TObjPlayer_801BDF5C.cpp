#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/player/TObjPlayer_801C1FF8.h"
#include "pso/player/TObjPlayer.h"

extern "C" {


extern u32 TObjPlayer__shared_photon_blast_state;
extern u32 TObjPlayer__shared_model_buffer;
extern u32 player_shared_buffer_base;

void TObjPlayer::free_shared_data() {
    if ((u32) TObjPlayer__shared_photon_blast_state != 0U) {
        fn_801C2308((void *)TObjPlayer__shared_photon_blast_state, 1);
        TObjPlayer__shared_photon_blast_state = 0U;
    }
    if ((u32) player_shared_buffer_base != 0U) {
        ::operator delete[]((void*)player_shared_buffer_base);
        player_shared_buffer_base = 0U;
    }
    if ((u32) TObjPlayer__shared_model_buffer != 0U) {
        ::operator delete[]((void*)TObjPlayer__shared_model_buffer);
        TObjPlayer__shared_model_buffer = 0U;
    }
}

}
