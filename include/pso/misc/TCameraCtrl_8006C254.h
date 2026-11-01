#ifndef PSO_MISC_TCAMERACTRL_8006C254_H
#define PSO_MISC_TCAMERACTRL_8006C254_H

#include "types.h"

struct CameraMotionData;
struct CameraMotionDirectory { CameraMotionData **entries; };
struct E_8006C668 { CameraMotionDirectory *directory; void *p; };

struct G_8006C668 { E_8006C668 e[8]; };

struct Entry_8006C6CC {
    s32 id;
    s32 f4;
};

struct Bank_8006C6CC {
    Entry_8006C6CC *entries;
    u32 count;
};

extern G_8006C668 TCameraCtrl__camera_banks;
extern Bank_8006C6CC camera_path_bank_table[];

#endif
