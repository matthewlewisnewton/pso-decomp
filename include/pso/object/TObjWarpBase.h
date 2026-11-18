#ifndef PSO_OBJECT_TOBJWARPBASE_H
#define PSO_OBJECT_TOBJWARPBASE_H

#include "types.h"
#include "pso/object/TObjMotion.h"

struct TObjWarpBase : public TObjCollidable {
    virtual ~TObjWarpBase();
    virtual void vfunc_14();
    virtual void open_confirm_window(s32 client_id) = 0;
    virtual s32 is_warp_enabled();
    virtual s32 vfunc_17();
    virtual s32 vfunc_18(s32);
    static void free_globals();
};

#endif
