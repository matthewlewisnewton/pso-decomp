#include "types.h"
#include "pso/system/StripBufferPair.h"
#include "pso/player/TObjPlayer_801AE48C.h"
#include "pso/unk/text_800F5BC0.h"
#include "pso/player/TObjPlayer.h"
#include "pso/misc/TLobby.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

extern u8 *photon_blast_shared_resource;
extern void *pilla_photon_buffer_pair;

void TObjPlayer::free_buffer_pair() {
    if ((u32) pilla_photon_buffer_pair != 0U) {
        destroy_buffer_pair((void *)pilla_photon_buffer_pair, 1);
    }
    pilla_photon_buffer_pair = 0U;
}
void create_pilla_photon_blast_model(void) {
    pilla_photon_buffer_pair = new StripBufferPair(*(s32 *)((s8 *)(*(void **)((s8 *)(*(u8 **)((s8 *)photon_blast_shared_resource + 0x42C)) + 8)) + 0x2C), 0);
}
