#ifndef PSO_TCHCRTAGINFORMATIONSTR_H
#define PSO_TCHCRTAGINFORMATIONSTR_H
#include "pso/TObject.h"
#include "types.h"

class TChCrTagInformationStr : public TObject {
public:
    TChCrTagInformationStr(TObject *parent, s32 index);
    virtual ~TChCrTagInformationStr();
    virtual void render();
    virtual void run_task();
    static TChCrTagInformationStr *create(TObject *parent, s32 index);

    s32 state;
    s32 index;
    s32 text_group;
    s32 first_line;
    s32 delay;
    f32 opacity;
    u32 frame;
};
typedef char TChCrTagInformationStr_size[sizeof(TChCrTagInformationStr) == 0x38 ? 1 : -1];
#endif
