#ifndef PSO_ITEM_TUNK_8049F42C_H
#define PSO_ITEM_TUNK_8049F42C_H
#include "pso/item/ItemArchiveReader.h"

class ItemAfsArchive : public ItemArchiveReader {
public:
    virtual ~ItemAfsArchive();
    ItemAfsArchive *initialize(const char *filename, s32 partition_id, s32 file_count);
};

class TUnk_8049F42C : public ItemAfsArchive {
public:
    virtual ~TUnk_8049F42C();
    virtual void vfunc_3();
    int update_item();
    void reset_ring_state();
    void update_state();
    s32 begin_load(s32 file);
    void reset_state();
    void update_ring();
    void update_load_state();
    void advance_load_state();
    s32 state;
    s32 flags;
    s32 file_id;
    void *init(const char *filename, s32 partition_id, s32 file_count);
    void *sub_80110010(s16);
};

typedef char ItemAfsArchiveSize[sizeof(ItemAfsArchive) == 0x18 ? 1 : -1];
typedef char ItemArchiveLoaderSize[sizeof(TUnk_8049F42C) == 0x24 ? 1 : -1];

#endif
