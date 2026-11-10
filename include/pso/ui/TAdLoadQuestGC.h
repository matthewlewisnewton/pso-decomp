#ifndef PSO_UI_TADLOADQUESTGC_H
#define PSO_UI_TADLOADQUESTGC_H
#include "pso/TObject.h"
#include "pso/misc/TWindowCost.h"
#include <stddef.h>

class TAdLoadQuestGC : public TObject {
public:
    virtual ~TAdLoadQuestGC();
    virtual void run_task();
    virtual void render();
    TObject *quest_display;
};
typedef char TAdLoadQuestGCDisplayOffset[offsetof(TAdLoadQuestGC, quest_display) == 0x1C ? 1 : -1];

#endif
