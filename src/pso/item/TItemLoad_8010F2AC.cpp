#include "pso/item/TUnk_8049F41C.h"
#include "pso/item/TUnk_8049F40C.h"
#include "types.h"
#include "pso/item/TItemLoad_801105AC.h"
#include "pso/item/TUnk_8049F3F4.h"
#include "pso/item/TItemLoad.h"

extern "C" {

extern TUnk_8049F41C *item_texture_archive_loader;
extern TUnk_8049F40C *item_model_chunk_loader;
extern s32 item_load_model_buffer;

void TUnk_8049F3F4::run_task() {
    u8 *arg0 = (u8 *)this;
    s32 temp_r3;
    s32 var_r31;
    s32 i;

    switch (this->m_20) {
    case 1:
        if ((item_model_chunk_loader != NULL) && (item_texture_archive_loader != NULL)) {
            item_model_chunk_loader->start_load_with_id(item_load_model_buffer + (*(s32 *)&this->unk_1C * 0x2C00), *(s32 *)&this->unk_24);
            this->m_20 = 2;
        }
        return;
    case 2:
        if (item_model_chunk_loader->update_item() == 1) {
            i = 0;
            var_r31 = 0;
            do {
                temp_r3 = item_model_chunk_loader->model_chunk(i);
                i += 1;
                *(s32 *)(arg0 + var_r31 + 0x2C) = temp_r3;
                var_r31 += 4;
            } while (i != 4);
            this->m_3c = TItemLoad__sub_80110748((void *)item_model_chunk_loader);
            *(s32 *)&this->unk_40 = TItemLoad__sub_80110740((void *)item_model_chunk_loader);
            if ((u32) this->m_3c != 0U) {
                this->m_20 = 3;
                item_texture_archive_loader->begin_load_if_pending(this->m_3c, this->m_28);
                return;
            }
            this->m_20 = 0;
            return;
        }
        break;
    case 3:
        if (item_texture_archive_loader->update_item() == 1) {
            this->m_20 = 0;
        }
        break;
    }
}

}
