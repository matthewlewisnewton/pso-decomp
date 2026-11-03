#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/unk/text_80103674.h"
extern "C" {
extern u32 item_buffer_temp_mode;
extern u32 item_buff_buffer;
extern u32 item_nj_chunk_buffer_table[];
void fn_80103674(void) {
    s32 i;
    item_buffer_temp_mode = 0;
    item_buff_buffer = 0;
    for (i = 0; i != 2; i++) {
        item_nj_chunk_buffer_table[i] = (u32)::operator new[](0x200);
    }
}

}
