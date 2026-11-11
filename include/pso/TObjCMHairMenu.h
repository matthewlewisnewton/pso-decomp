#ifndef PSO_TOBJCMHAIRMENU_H
#define PSO_TOBJCMHAIRMENU_H
#include "pso/TObject.h"
#include "types.h"
#include "pso/misc/CharacterAppearance.h"

class TObjCMHairMenu : public TObject {
public:
    CharacterAppearanceFields* appearance;
    s32 initialized, selection, count, ticks, active;
    f32 fade;
    s32 trailing[3];
    virtual ~TObjCMHairMenu();
    virtual void render();
    virtual void run_task();
public:
    void *create();
};

#endif
