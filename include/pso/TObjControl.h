#ifndef PSO_TOBJCONTROL_H
#define PSO_TOBJCONTROL_H

#include "pso/TObject.h"
#include "types.h"

class TObjControl : public TObject {
public:
    TObjControl(TObject *parent);
    s16 m_decision_mode;
    u16 m_reserved;

    virtual ~TObjControl();
    virtual void run_task();
};

#endif
