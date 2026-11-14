#ifndef PSO_TOBJBAGWARNWIN4P_H
#define PSO_TOBJBAGWARNWIN4P_H
#include "pso/TObject.h"
#include "types.h"
#include "pso/ui/WarningWindowState.h"

class TObjBagWarnWin4P : public TObject {
public:
    WarningWindowState warning;
    virtual ~TObjBagWarnWin4P();
    virtual void run_task();
public:
    static s32 check_can_open(void * _w0);
    void create_window();
};

typedef char TObjBagWarnWin4P_WarningOffset[offsetof(TObjBagWarnWin4P, warning) == 0x1C ? 1 : -1];
typedef char TObjBagWarnWin4P_Size[sizeof(TObjBagWarnWin4P) == 0xA4 ? 1 : -1];

#endif
