#ifndef PSO_ITEM_TUNK_8049F40C_H
#define PSO_ITEM_TUNK_8049F40C_H
#include "types.h"
#include "pso/item/TUnk_8049F42C.h"

class TUnk_8049F40C : public TUnk_8049F42C {
public:
    virtual ~TUnk_8049F40C();
    virtual void vfunc_3();
    void start_load_with_id(s32 destination, s32 file);
    s32 construct_with_vtable(const char *filename, s32 partition_id, s32 file_count);
    void *dt(s16);
    s32 model_chunk(s32 index);
    s32 destination;
    void *texture_list;
    s32 chunks[4];
    void *model_data;
};

typedef char ItemModelLoaderSize[sizeof(TUnk_8049F40C) == 0x40 ? 1 : -1];

#endif
