#ifndef PSO_MISC_TUNK_80488B38_H
#define PSO_MISC_TUNK_80488B38_H
#include "types.h"
#include <stddef.h>
#include "pso/misc/TUnk_80488A28.h"

class TUnk_80488B38 : public TUnk_80488A28 {
public:
    TUnk_80488B38();
    virtual ~TUnk_80488B38();
    virtual void run_task();
    f32 distance;
};
typedef char TUnk_80488B38_size[sizeof(TUnk_80488B38) == 0x70 ? 1 : -1];

typedef char TUnk_80488B38_distance_offset[offsetof(TUnk_80488B38, distance) == 0x6C ? 1 : -1];
typedef char TUnk_80488B38_heading_offset[offsetof(TUnk_80488B38, m_30) == 0x30 ? 1 : -1];

#endif
