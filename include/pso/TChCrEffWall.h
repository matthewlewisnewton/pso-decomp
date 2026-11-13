#ifndef PSO_TCHCREFFWALL_H
#define PSO_TCHCREFFWALL_H
#include "pso/TObject.h"
#include "types.h"

class TChCrEffWall : public TObject {
public:
    TChCrEffWall(TObject *parent);
    virtual ~TChCrEffWall();
    virtual void render();
};

#endif
