#ifndef PSO_TITEMMENUCTRL_H
#define PSO_TITEMMENUCTRL_H

#include "pso/TObject.h"
#include "types.h"
#include "pso/system/FlagWord.h"
#include <stddef.h>

class TItemMenuCtrl : public TObject {
public:
    virtual ~TItemMenuCtrl();
public:
    static s32 query_flag(s32 arg0);
    static void open_menu(u32 arg0);
    void set_menu_flags(u32 mask);

    FlagWord menu_flags;
};

typedef char TItemMenuCtrlLayout[(sizeof(TItemMenuCtrl) == 0x20 &&
    offsetof(TItemMenuCtrl, menu_flags) == 0x1C) ? 1 : -1];

#endif
