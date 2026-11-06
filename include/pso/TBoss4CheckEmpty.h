#ifndef PSO_TBOSS4CHECKEMPTY_H
#define PSO_TBOSS4CHECKEMPTY_H
#include "pso/TObject.h"
#include "types.h"

class TBoss4CheckEmpty : public TObject {
public:
    virtual ~TBoss4CheckEmpty();
    virtual void run_task();
    virtual void render();
public:
    static void render();
    static void *create();
};

#endif
