#ifndef PSO_TTECCTRL_H
#define PSO_TTECCTRL_H
#include "pso/TObject.h"
#include "types.h"

class TTecCtrl : public TObject {
public:
    virtual ~TTecCtrl();
    virtual void run_task();
    virtual void render();
public:
    static s32 classify_distance_band(s32 arg0, s32 arg1, s32 arg2);
    static s32 is_technique_ready();
};

#endif
