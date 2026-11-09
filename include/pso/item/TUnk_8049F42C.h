#ifndef PSO_ITEM_TUNK_8049F42C_H
#define PSO_ITEM_TUNK_8049F42C_H
#include "types.h"
#include "pso/item/ItemArchiveReader.h"

class TUnk_8049F42C : public ItemArchiveReader {
public:
    virtual ~TUnk_8049F42C();
    virtual void vfunc_3();
    void *init();
    void *sub_80110010(s16);
    void reset_ring_state();
    void update_state();
    s32 begin_load(s32 file);
    void reset_state();
    void update_ring();
    void update_load_state();
    void advance_load_state();
    int update_item();
    void start_load_with_id(s32 id, s32 arg2);
    void begin_load_if_pending(s32 arg1, s32 arg2);
    void reload_item();
};

#endif
