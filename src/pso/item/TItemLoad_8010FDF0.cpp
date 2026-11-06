#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/item/TItemAttacker.h"
#include "pso/item/TItemLoad_8010FDF0.h"
#include "pso/system/memory.h"
#include "pso/item/TUnk_8049C658.h"
#include "pso/TItemLoad.h"
#include "pso/item/TItemDrop.h"
#include "pso/item/ItemArchiveReader.h"

extern "C" {

struct Sp8Buf_8010fe6c_8010FDF0 {
    s32 field00;
    s32 field04;
    s32 field08;
    s32 field0c;
    s32 field10;
    s32 field14;
    s32 field18;
    u32 field1c;
    s32 field20;
    s32 field24;
    s32 field28;
    s32 field2c;
    s32 field30;
    s32 field34;
    s32 field38;
    s32 field3c;
};

s32 apply_rel_relocations(s32 *);
s32 read_disc_file(u32, s32);
s32 read_checked_align__6TLobbyFPvlPv(AdxfHandle *, s32, s32, void *);
s32 prs_decompress_alloc(s32, u32, s32);

    extern int item_load_compressed_work_buffer;
    extern int item_load_work_buffer_busy;
void TItemLoad::alloc_work_buffer() { item_load_compressed_work_buffer = (int)::operator new[]((u32)((void*)24576)); item_load_work_buffer_busy = 0; }

RelocatedFile::~RelocatedFile() {
    ::operator delete[](buffer);
}

RelocatedFile::RelocatedFile(const char *path, s32 size) {
    struct Sp8Buf_8010fe6c_8010FDF0 sp8;
    s32 temp_r31;
    s32 item_buff;

    buffer = NULL;
    root = NULL;
    if ((size != 0) && (path != NULL)) {
        buffer = ::operator new[](size);
        item_buff = create_item_buff(size);
        if ((item_buff != 0) && (buffer != NULL) && (read_disc_file((u32)path, item_buff) > 0)) {
            temp_r31 = prs_decompress_alloc(item_buff, (u32)buffer, size);
            ((TUnk_8049C658 *)((s32 *)&sp8))->construct();
            sp8.field1c = (u32)buffer;
            sp8.field20 = temp_r31;
            root = (void *)apply_rel_relocations((s32 *)&sp8);
            ((TUnk_8049C658 *)((s32 *)&sp8))->destroy(-1);
        }
        TItemBuff__ct();
    }
}

void ItemArchiveReader::read(s32 arg1) {
    read_checked_align__6TLobbyFPvlPv(handle, sectors, arg1, this);
}

}
