#ifndef PSO_TBOSS4ZAKODRAW_H
#define PSO_TBOSS4ZAKODRAW_H
#include "pso/TObject.h"
#include "types.h"

class TBoss4ZakoDraw : public TObject {
public:
    TBoss4ZakoDraw(TObject *parent);
    virtual ~TBoss4ZakoDraw();
    virtual void run_task();
    virtual void render();
};

#endif
