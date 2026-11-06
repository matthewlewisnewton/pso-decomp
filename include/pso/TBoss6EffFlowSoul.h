#ifndef PSO_TBOSS6EFFFLOWSOUL_H
#define PSO_TBOSS6EFFFLOWSOUL_H

#include "pso/TObject.h"
#include "types.h"

class TBoss6EffFlowSoul : public TObject {
public:
    u8 _pad1C[0x4];
 void* m_20;
public:
    virtual ~TBoss6EffFlowSoul();
    virtual void run_task();
};

#endif
