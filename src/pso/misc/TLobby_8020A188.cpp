#include "types.h"
#include "pso/map/ChallengeEnemySet.h"
#include "pso/misc/TLobby_8020A188.h"
#include "pso/system/memory.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TQuestVmDownLoadServer.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

extern "C" {

int free_boss4rock__6TLobbyFs(void*, void*);
u32 find_type5_header__6TLobbyFPvi(s32, s32);
u32 find_chunk_by_id__6TLobbyFPvi(s32, s32);
u32 find_header_by_id__6TLobbyFPvi(s32, s32);

extern u32 lbl_805D60AC;
extern u32 TLobby__item_data_table_buffer;

void init_buffers__6TLobbyFii(s32 id, s32 arg1) {
    u32 temp_r3;

    challenge_event_source = reinterpret_cast<u8 *>(find_header_by_id__6TLobbyFPvi(arg1, id));
    lbl_805D60AC = find_chunk_by_id__6TLobbyFPvi(arg1, id);
    temp_r3 = find_type5_header__6TLobbyFPvi(arg1, id);
    TLobby__item_data_table_buffer = temp_r3;
    if ((challenge_event_source != NULL) && ((u32) lbl_805D60AC != 0U) && (temp_r3 != 0U)) {
        challenge_enemy_buffer = static_cast<u8 *>(TQuestVmDownLoadServer::alloc(ChallengeEnemyBufferSize));
        challenge_event_buffer = static_cast<ChallengeFixedEvent *>(TQuestVmDownLoadServer::alloc(ChallengeEventBufferSize));
        challenge_event_count = 0;
        challenge_action_buffer = static_cast<u8 *>(TQuestVmDownLoadServer::alloc(ChallengeCommandBufferSize));
        challenge_action_size = 0;
        build_challenge_enemy_set(id);
        TAdSinglePlyChrSelectGC::safe_free((void *)challenge_action_buffer);
        TAdSinglePlyChrSelectGC::safe_free((void *)challenge_event_buffer);
        challenge_event_buffer = NULL;
        TAdSinglePlyChrSelectGC::safe_free((void *)challenge_enemy_buffer);
        challenge_enemy_buffer = NULL;
    }
}

    extern int item_drop_rng;
    extern int lbl_805D60A4;
void TLobby::free_boss4rock() { free_boss4rock__6TLobbyFs((void*)lbl_805D60A4, (void*)1); lbl_805D60A4 = 0; ::operator delete((void *)item_drop_rng); item_drop_rng = 0; }

}
