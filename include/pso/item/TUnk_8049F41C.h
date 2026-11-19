#ifndef PSO_ITEM_TUNK_8049F41C_H
#define PSO_ITEM_TUNK_8049F41C_H
#include "types.h"
#include "pso/item/TUnk_8049F42C.h"

class TUnk_8049F41C : public TUnk_8049F42C {
public:
    virtual ~TUnk_8049F41C();
    virtual void vfunc_3();
    void begin_load_if_pending(s32 destination, s32 file);
    void *construct(const char *filename, s32 partition_id, s32 file_count);
    s32 destination;
};

typedef char ItemTextureLoaderSize[sizeof(TUnk_8049F41C) == 0x28 ? 1 : -1];

#endif
