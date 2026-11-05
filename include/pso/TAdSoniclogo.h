#ifndef PSO_TADSONICLOGO_H
#define PSO_TADSONICLOGO_H
#include "pso/TObject.h"
#include "types.h"

class TAdSoniclogo : public TObject {
public:
    virtual void render();
    virtual ~TAdSoniclogo();
    virtual void run_task();
public:
    static void request_destroy();
};

#endif
