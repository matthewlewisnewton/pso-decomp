#ifndef PSO_TBOSS6CRUSHPTCL_H
#define PSO_TBOSS6CRUSHPTCL_H

#include "pso/TObject.h"
#include "pso/system/vector.h"
#include "types.h"

class TBoss6CrushPtcl : public TObject {
public:
    virtual ~TBoss6CrushPtcl();
    virtual void run_task();

    s32 m_1C;
    u32 m_20;
    u32 m_24;
public:
    static void *create(Vec *point);
};

#endif
