#ifndef PSO_MISC_TUNK_804EFBAC_H
#define PSO_MISC_TUNK_804EFBAC_H
#include "types.h"
#include "pso/misc/TWindowBase.h"

class TUnk_804EFBAC : public TWindowBase {
public:
    virtual ~TUnk_804EFBAC();
    // Selection state read by the three-row renderer at 0x8034055C.
    s32 selection_disabled;
    s32 first_enabled_row;
    s32 selected_row;
};
typedef char TUnk_804EFBAC_size[sizeof(TUnk_804EFBAC) == 0x6C ? 1 : -1];

typedef char TUnk_804EFBAC_selection_disabled[offsetof(TUnk_804EFBAC, selection_disabled) == 0x60 ? 1 : -1];
typedef char TUnk_804EFBAC_first_enabled_row[offsetof(TUnk_804EFBAC, first_enabled_row) == 0x64 ? 1 : -1];
typedef char TUnk_804EFBAC_selected_row[offsetof(TUnk_804EFBAC, selected_row) == 0x68 ? 1 : -1];

#endif
