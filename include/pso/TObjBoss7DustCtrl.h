#ifndef PSO_TOBJBOSS7DUSTCTRL_H
#define PSO_TOBJBOSS7DUSTCTRL_H

#include "pso/TObject.h"
#include "types.h"

class TObjBoss7DustCtrl : public TObject {
public:
    TObjBoss7DustCtrl(TObject *parent);
    virtual ~TObjBoss7DustCtrl();
    virtual void run_task();
    static void create();
};

typedef char Boss7DustCtrlSize[sizeof(TObjBoss7DustCtrl) == 0x1C ? 1 : -1];

#endif
