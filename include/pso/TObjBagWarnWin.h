#ifndef PSO_TOBJBAGWARNWIN_H
#define PSO_TOBJBAGWARNWIN_H
#include "pso/TObject.h"
#include "types.h"
#include "pso/ui/WarningWindowState.h"

class TObjBagWarnWin : public TObject {
public:
    WarningWindowState warning;
    virtual ~TObjBagWarnWin();
    virtual void run_task();
public:
    static s32 should_show_warning(void *arg0);
    void open_message_window();
    static void *create(void *arg0);
};

typedef char TObjBagWarnWin_WarningOffset[offsetof(TObjBagWarnWin, warning) == 0x1C ? 1 : -1];
typedef char TObjBagWarnWin_Size[sizeof(TObjBagWarnWin) == 0xA4 ? 1 : -1];

#endif
