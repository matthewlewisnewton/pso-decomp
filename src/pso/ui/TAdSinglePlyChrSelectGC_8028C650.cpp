#include "types.h"
#include "pso/object/TObjFish_8001ED90.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/misc/TLobby.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

extern "C" {

void TAdSinglePlyChrSelectGC::start_character_load_task() {
    BmlResource *loaded;

    if ((TLobby__sub_8001EEF4() != 0) && (this->try_acquire_slot() != 0)) {
        loaded = (BmlResource *)::operator new(0x440);
        if (loaded != NULL) {
            loaded = init_from_id_lists(loaded, 6, &this->model_ids, &this->motion_ids, 0, 0,
                                        this->m_24->start_load_default());
        }
        this->loaded_bml = loaded;
        if (loaded != NULL) {
            this->load_timeout = 0x12C;
            this->m_2c = 1;
        }
    }
}

}
