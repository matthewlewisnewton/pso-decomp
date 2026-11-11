#include "types.h"
#include "pso/object/TObjFish_8001ED90.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/misc/TLobby.h"
#include "pso/TChCrLoadGmNjReq.h"
#include "pso/misc/CharacterLoadBuffer.h"

extern "C" {

void TChCrLoadGmNjReq::start_character_load_task() {
    BmlResource *loaded;

    if ((TLobby::tmp_buf_is_free() != 0) && (this->try_acquire_slot() != 0)) {
        loaded = (BmlResource *)::operator new(0x440);
        if (loaded != NULL) {
            loaded = init_from_id_lists(loaded, 6, &this->model_ids, &this->motion_ids, 0, 0,
                                        get_character_load_buffer(this->load_slot));
        }
        this->loaded_bml = loaded;
        if (loaded != NULL) {
            this->load_timer = 0x12C;
            this->load_state = 1;
        }
    }
}

}
