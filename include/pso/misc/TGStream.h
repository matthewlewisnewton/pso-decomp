#ifndef PSO_MISC_TGSTREAM_H
#define PSO_MISC_TGSTREAM_H

#include "types.h"

struct TGStream
{
    static s32 load_file(s32 arg0);
    static s32 read_whole_file(s32 arg0, u8 *arg1);
    static s32 load_sct_file(s32 name, s32 dst);
    void read_sectors_sync(s32 arg1, s32 arg2);
    static void reset();
    s32 read_data(s32 dst, s32 size);
};

#endif
