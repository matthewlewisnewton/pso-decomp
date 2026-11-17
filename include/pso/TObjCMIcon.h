#ifndef PSO_TOBJCMICON_H
#define PSO_TOBJCMICON_H
#include "pso/TObject.h"
#include "types.h"
#include <stddef.h>

struct CreationIconState {
    s32 hidden;
    f32 fade;
    f32 x;
};

struct CreationIconGroup {
    s32 count;
    s32 sprite_ids[4];
};

extern "C" {
extern CreationIconState creation_icon_states[7];
extern CreationIconState creation_initial_icon_state;
extern f32 TObjCMIcon__horizontal_scroll_offset;
extern CreationIconGroup TObjCMIcon__icon_group_table[7];
}

typedef char CreationIconStateSize[sizeof(CreationIconState) == 12 ? 1 : -1];
typedef char CreationIconStateHiddenOffset[offsetof(CreationIconState, hidden) == 0 ? 1 : -1];
typedef char CreationIconStateFadeOffset[offsetof(CreationIconState, fade) == 4 ? 1 : -1];
typedef char CreationIconStateXOffset[offsetof(CreationIconState, x) == 8 ? 1 : -1];
typedef char CreationIconGroupSize[sizeof(CreationIconGroup) == 20 ? 1 : -1];
typedef char CreationIconGroupIdsOffset[offsetof(CreationIconGroup, sprite_ids) == 4 ? 1 : -1];

class TObjCMIcon : public TObject {
public:
    virtual ~TObjCMIcon();
    virtual void render();
    virtual void run_task();
public:
    static void *create(void *arg0);
    static void reset_icon_flags();
    static void init_icon_table();
};

#endif
