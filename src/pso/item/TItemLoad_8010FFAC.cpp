#include "pso/system/Adxf.h"
#include "types.h"
#include "pso/unk/text_803CC294.h"
#include "pso/item/TItemLoad.h"

extern "C" {

s32 free_texture__9TItemLoadFv();

u32 TItemLoad::load_data(s32 arg1) {
    AdxfHandle *file;
    if ((s32) *(s32 *)&this->m_up == 1) {
        free_texture__9TItemLoadFv();
        *(AdxfHandle **)&this->m_flags = ADXF_OpenAfs(*(s32 *)&this->m_prev, arg1);
        file = *(AdxfHandle **)&this->m_flags;
        if (file != NULL) {
            *(s32 *)&this->m_next = ADXF_GetFsizeSct(file);
        }
    }
    return *(u32 *)&this->m_flags;
}

}
