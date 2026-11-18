#include "pso/system/BmlResource.h"
#include "pso/ui/charcreate/CharacterLoadBuffer.h"
#include "pso/ui/charcreate/TChCrLoadGmNjReq.h"
#include "pso/unk/TLobby.h"

void TChCrLoadGmNjReq::start_character_load_task() {
    if (TLobby::tmp_buf_is_free() != 0 && try_acquire_slot() != 0) {
        BmlResource *loaded = (BmlResource *)::operator new(sizeof(BmlResource));
        if (loaded != NULL) {
            loaded = init_from_id_lists(loaded, 6, model_ids, &model_ids[1], 0, 0, get_character_load_buffer(load_slot));
        }
        loaded_bml = loaded;
        if (loaded != NULL) {
            load_timer = 0x12C;
            state = 1;
        }
    }
}
