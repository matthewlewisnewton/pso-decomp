#ifndef PSO_TCHCREFFTAGSTR_H
#define PSO_TCHCREFFTAGSTR_H
#include "pso/TObject.h"
#include "types.h"

class TChCrEffTagStr : public TObject {
public:
    TChCrEffTagStr(TObject *object, void *sprite, void *pos);
    virtual ~TChCrEffTagStr();
    virtual void run_task();
    virtual void render();

    s32 fade_state;
    s32 sprite_id;
    f32 fade;
    f32 position[2];
};

typedef char TChCrEffTagStr_size[sizeof(TChCrEffTagStr) == 0x30 ? 1 : -1];

#endif
